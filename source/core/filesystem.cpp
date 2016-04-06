#include <fstream>
#include <dirent.h>
#include <3ds.h>
#include <3ds/services/fs.h>
#include <3ds/srv.h>
#include <3ds/svc.h>
#include <3ds/ipc.h>
#include <vector>

#include "filesystem.h"
#include "compileoptions.h"

FS_Archive FileSystem::savearchive;
Handle FileSystem::fsHandle;
int FileSystem::gamemode;

int FileSystem::initialize(const int game, const int mediatype) {
#ifndef DEBUG

    #ifdef __cia
    int gameid = 0x00000000;
    if( game == X )
        gameid = 0x00055D00;
    
    else if( game == Y )
        gameid = 0x00055E00;
    
    else if( game == OR )
        gameid = 0x0011C400;
    
    else if( game == AS )
        gameid = 0x0011C500;
    
    else if( mediatype == FileSystem::CART ) {
        u64 cartid;
        amInit();
        AM_GetTitleIdList(MEDIATYPE_GAME_CARD, 1, &cartid);
        
        if( cartid == FileSystem::X_ID ) gameid = 0x00055D00;
        if( cartid == FileSystem::Y_ID ) gameid = 0x00055E00;
        if( cartid == FileSystem::OR_ID ) gameid = 0x0011C400;
        if( cartid == FileSystem::AS_ID ) gameid = 0x0011C500;
        amExit();
    }
    
    u32 path_a[3];

    path_a[0] = mediatype;
    path_a[1] = gameid;
    path_a[2] = 0x00040000;

    savearchive = (FS_Archive){ARCHIVE_USER_SAVEDATA, (FS_Path){PATH_BINARY, 12, path_a}};
    
    #else
    if( srvGetServiceHandleDirect(&fsHandle, "fs:USER") )
        return 0x111;

    if( FSUSER_Initialize(fsHandle) )
        return 0x112;

    fsUseSession(fsHandle, false);

    savearchive = (FS_Archive) { ARCHIVE_SAVEDATA, fsMakePath(PATH_EMPTY, NULL), fsHandle };
    
    #endif
    
    if( FSUSER_OpenArchive(&savearchive) )
        return 0x113;
#endif

    return 0;
}

int FileSystem::createDirectory(const std::string path) {
    if( !mkdir(path.c_str(), 0777) )
        return 0x134;
    
    return 0;
}

int FileSystem::readSaveFile(char* destination) {
#ifdef DEBUG
    int size;
    int ret = readFileSpecial("/main", destination, size);
    if( ret != 0 )
        return ret;
    
#else
    u32 size;
    int ret = readFileArchive("/main", destination, size, &savearchive);
    if( ret != 0 )
        return ret;
#endif
    
    if( size == XYLENGTH )
        gamemode = XY;
    else if( size == ORASLENGTH )
        gamemode = ORAS;
    else
        return 0x125;
    
    return 0;
}

int FileSystem::readFile(const std::string path, char* destination) {
    std::streampos size;
    
    std::ifstream file(path, std::ios::in | std::ios::binary | std::ios::ate);
    if( !file.is_open() )
        return 0x121;
    
    size = file.tellg();
    file.seekg(0, std::ios::beg);
    file.read(destination, size);
    file.close();
    
    return 0;
}

int FileSystem::readFileArchive(std::string path, char* destination, u32& bytesread, FS_Archive* archive) {
    Handle filehandle;
    
    if( FSUSER_OpenFile(&filehandle, *archive, fsMakePath(PATH_ASCII, path.c_str()), FS_OPEN_READ, FS_ATTRIBUTE_DIRECTORY) )
        return 0x121;
    
    u64 size;
    
    if( FSFILE_GetSize(filehandle, &size) ) {
        FSFILE_Close(filehandle);
        return 0x122;
    }
    
    if( FSFILE_Read(filehandle, &bytesread, 0x0, destination, size) ) {
        FSFILE_Close(filehandle);
        return 0x123;
    }
    
    if(bytesread < size) {
        FSFILE_Close(filehandle);
        return 0x124;
    }
    
    FSFILE_Close(filehandle);
    return 0;
}

int FileSystem::readFileSpecial(std::string path, char* destination, int& buffersize) {
    std::streampos size;
    
    std::ifstream file(path, std::ios::in | std::ios::binary | std::ios::ate);
    if( !file.is_open() )
        return 0x121;
    
    size = file.tellg();
    file.seekg(0, std::ios::beg);
    file.read(destination, size);
    file.close();
    buffersize = size;
    
    return 0;
}

int FileSystem::writeFile(const std::string path, char* source, const unsigned int size) {
    std::ofstream file(path, std::ios::out | std::ios::binary);
    if( !file.is_open() )
        return 0x131;
    
    file.write(source, size);
    file.close();
    return 0;
}

int FileSystem::writeFileArchive(std::string path, char* source, u64 size, FS_Archive* archive) {
    Handle fileHandle;
    if( FSUSER_OpenFile(&fileHandle, *archive, fsMakePath(PATH_ASCII, path.c_str()), FS_OPEN_WRITE | FS_OPEN_CREATE, 0) ) 
        return 0x131;
    
    u32 byteswritten;
    if( FSFILE_Write(fileHandle, &byteswritten, 0L, source, size, FS_WRITE_FLUSH) )
        return 0x132;
    
    FSFILE_Close(fileHandle);
    return 0;
}

int FileSystem::backupSaveFile(const std::string path, char* source) {
    int size;
    if(gamemode == XY)
        size = XYLENGTH;
    else size = ORASLENGTH;
    
    return writeFile(path, source, size);
}

int FileSystem::writeSaveFile(char* source) {
#ifdef DEBUG
    unsigned int size;
    if( gamemode == XY )
        size = XYLENGTH;
    else size = ORASLENGTH;
    
   return writeFile("/main", source, size);
#else    
    u64 size;
    if( gamemode == XY )
        size = XYLENGTH;
    else size = ORASLENGTH;
    
    int ret = writeFileArchive("/main", source, size, &savearchive);
    if( ret != 0 )
        return ret;
        
    if( FSUSER_ControlArchive(savearchive, ARCHIVE_ACTION_COMMIT_SAVE_DATA, NULL, 0, NULL, 0) )
        return 0x133;
    
     return 0;
#endif
}

int FileSystem::loadTextFile(const std::string path, std::vector<std::string>& destination) {
    std::ifstream file(path.c_str(), std::ios::in);
    if( !file.is_open() )
        return 0x121;
    
    std::string dummy;
    while(getline(file,dummy)) {
        dummy.erase(dummy.end()-1);
        destination.push_back(dummy);
    }
    
    file.close();
    return 0;
}

bool FileSystem::isDirectory(const std::string path) {
    DIR* result = opendir(path.c_str());
    bool toreturn;
    
    if( result == NULL ) toreturn = false;
    else toreturn = true;
    
    closedir(result);
    
    return toreturn;
    
}

std::vector<std::string> FileSystem::obtainFileList(std::string directory, std::string extension) {
    std::vector<std::string> result;
    DIR* dir = opendir(directory.c_str());
    if(dir == NULL) 
        return result;
    
    dirent* ent = NULL;
    do {
        //bool toadd = true;
        ent = readdir(dir);
        if(ent != NULL) {
            std::string toinsert(ent->d_name);
            std::string::size_type dotPos = toinsert.rfind('.');
            /*if(dotPos == std::string::npos && !isdirectory) 
                toadd = false;*/
    
            if( extension == toinsert.substr(dotPos+1) || dotPos == std::string::npos )
                result.push_back(toinsert);
        }
    }while(ent != NULL);
    
    closedir(dir);
    return result;
}

int FileSystem::romFsInit() {
    if( romfsInit() != 0 )
        return 0x111;
    
    return 0;
}

void FileSystem::closeFileSystem() {
#ifndef DEBUG
    #ifdef __cia
    romfsExit();
    #endif
    FSUSER_CloseArchive(&savearchive);
    fsEndUseSession();
    svcCloseHandle(fsHandle);
#endif
}