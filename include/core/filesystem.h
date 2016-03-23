#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <3ds/services/fs.h>
#include <string>
#include <vector>

class FileSystem {
    private:
        static const int XYLENGTH = 0x65600;
        static const int ORASLENGTH = 0x76000;

        static FS_Archive savearchive;
        static Handle fsHandle;
        static int gamemode;
        
        static int readFileArchive(std::string path, char* destination, u32& bytesread, FS_Archive* archive);
        static int readFileSpecial(std::string path, char* destination, int& buffersize);
        static int writeFileArchive(std::string path, char* source, u64 size, FS_Archive* archive);
        
    public:
        static const int XY = 0;
        static const int ORAS = 1;
        static const int X = 1;
        static const int Y = 2;
        static const int OR = 3;
        static const int AS = 4;
        static const int CIA = 1;
        static const int CART = 2;
        
        static int initialize(const int game, const int mediatype);
        static int createDirectory(const std::string path);
        static int readSaveFile(char* destination);
        static int writeSaveFile(char* source);
        static int readFile(const std::string path, char* destination);
        static int writeFile(const std::string path, char* source, const unsigned int size);
        static int backupSaveFile(const std::string path, char* source);
        static int getGame() { return gamemode; }
        static int loadTextFile(const std::string path, std::vector<std::string>& destination);
        static std::vector<std::string> obtainFileList(std::string directory, std::string extension);
        static void closeFileSystem();
        static bool isDirectory(const std::string path);
};

#endif /* FILESYSTEM_H */

