#include <cstring>
#include <stdlib.h>
#include <3ds.h>

#include "pokemon.h"

Pokemon::Pokemon(const int boxnumber, const int indexnumber, Savefile* save) {
    this->save = save;
    this->boxnumber = boxnumber;
    this->indexnumber = indexnumber;
    this->save->getPkmn(this->boxnumber, this->indexnumber, data);
}

std::wstring Pokemon::getNickname() {
    u16 buffer[NICKNAMELENGTH/2];
    memcpy(buffer, &data[NICKNAMEPOS], NICKNAMELENGTH);
    uint32_t nkname[NICKNAMELENGTH/2];
    int length = utf16_to_utf32(nkname, buffer, NICKNAMELENGTH/2);
    nkname[length] = 0x0;
    std::wstring nickname((wchar_t*)nkname);
    return nickname;
}

std::wstring Pokemon::getOT() {
    u16 buffer[OTNAMELENGTH/2];
    memcpy(buffer, &data[OTNAMEPOS], OTNAMELENGTH);
    uint32_t nkname[OTNAMELENGTH/2];
    int length = utf16_to_utf32(nkname, buffer, OTNAMELENGTH/2);
    nkname[length] = 0x0;
    std::wstring nickname((wchar_t*)nkname);
    return nickname;
}

u16 Pokemon::getPokedexNumber() {
    u16 pokedexnumber;
    memcpy(&pokedexnumber, &data[POKEDEXNUMBERPOS], POKEDEXNUMBERLENGTH);
    return pokedexnumber;
}

u8 Pokemon::getNature() {
    u8 nature;
    memcpy(&nature, &data[NATUREPOS], NATURELENGTH);
    return nature;
}

u8 Pokemon::getLevel() {
    u32 exppoint;
    u8 iterlev = 0;
    memcpy(&exppoint, &data[EXPPOINTPOS], EXPPOINTLENGTH);
    
    while(iterlev < 100 && exppoint >= expTableLookup(iterlev, ExtDataManager::getLevelType(getPokedexNumber())))
        iterlev++;
    
    return iterlev;
}

bool Pokemon::isEgg() {
    u32 eggbuffer;
    memcpy(&eggbuffer, &data[IVPOS], IVLENGTH);
    eggbuffer = eggbuffer >> 30;
    eggbuffer = eggbuffer & 0x1;
    if(eggbuffer == 1) 
        return true;
    
    else return false;
}

u8 Pokemon::isFemale() {
    u8 buffergender;
    memcpy(&buffergender, &data[GENDERPOS], GENDERLENGTH);
    buffergender = (buffergender >> 1) & 0x3;
    return buffergender;
}

u8 Pokemon::getAbility() {
    u8 abilitybuffer;
    memcpy(&abilitybuffer, &data[ABILITYNUMPOS], ABILITYNUMLENGTH);
    
    std::vector<u8> resultset = ExtDataManager::getAbilitySet(getPokedexNumber());
    
    if( abilitybuffer == 1 )
        abilitybuffer = 0;
    
    if( abilitybuffer == 2 )
        abilitybuffer = 1;
    
    if( abilitybuffer == 4 )
        abilitybuffer = 2;
    
    return resultset[abilitybuffer];
}

std::vector<std::string> Pokemon::getAbilitySet() {
    std::vector<std::string> result;
    u16 tempspecies = getPokedexNumber();
    /*if( getForm() )
        tempspecies = 721 + ExtDataManager::getFormData(tempspecies) + getForm() - 1;*/
    
    std::vector<u8> resultset = ExtDataManager::getAbilitySet(tempspecies);
    for(int i = 0; i < 3; i++) {
        result.push_back(ExtDataManager::getAbilityName(resultset[i]));
    }
    
    return result;
}

u16 Pokemon::getItem() {
    u16 itembuffer;
    memcpy(&itembuffer, &data[ITEMPOS], ITEMLENGTH);
    
    return itembuffer;
}

u8 Pokemon::getBall() {
    u8 ballbuffer;
    memcpy(&ballbuffer, &data[POKEBALLPOS], POKEBALLLENGTH);
    
    return ballbuffer;
}

u16 Pokemon::getOTID() {
    u16 otidbuffer;
    memcpy(&otidbuffer, &data[OTIDPOS], OTIDLENGTH);
    
    return otidbuffer;
}

u16 Pokemon::getSOTID() {
    u16 sotidbuffer;
    memcpy(&sotidbuffer, &data[SOTIDPOS], SOTIDLENGTH);
    
    return sotidbuffer;
}

u32 Pokemon::getPID() {
    u32 pidbuffer;
    memcpy(&pidbuffer, &data[PIDPOS], PIDLENGTH);
    
    return pidbuffer;
}

u16 Pokemon::getMove(const int nmove) {
    u16 movebuffer[4];
    
    memcpy(&movebuffer, &data[MOVEPOS], MOVELENGTH*4);
    
    return movebuffer[nmove];
}

u16 Pokemon::getEggmove(const int nmove) {
    u16 eggmovebuffer[4];
    
    memcpy(&eggmovebuffer, &data[EGGMOVEPOS], EGGMOVELENGTH*4);
    
    return eggmovebuffer[nmove];
}

u8 Pokemon::getIV(const int stat) {
    u32 buffer;
    u8 toreturn;
    
    memcpy(&buffer, &data[IVPOS], IVLENGTH);
    buffer = buffer >> 5*stat;
    buffer = buffer & 0x1F;
    memcpy(&toreturn, &buffer, 1);
    
    return toreturn;
}

u8 Pokemon::getEV(const int stat) {
    u8 evbuffer[6];
    
    memcpy(evbuffer, &data[EVPOS], EVLENGTH*6);
    
    return evbuffer[stat];
}

bool Pokemon::isEVMAX() {
    int buffer = 0;
    for(int i = 0; i < 6; i++)
        buffer = buffer + getEV(i);
        
    if(buffer == 510) return true;
    else return false;
}

bool Pokemon::isShiny() {
    u16 trainersv = (getOTID() ^ getSOTID()) >> 4;
    u16 pkmnv = ((getPID() >> 16) ^ (getPID() & 0xFFFF)) >> 4;
    
    if( trainersv == pkmnv) return true;
    else return false;
}

bool Pokemon::isGenderless() {
    u8 buffergender;
    memcpy(&buffergender, &data[GENDERPOS], GENDERLENGTH);
    buffergender = (buffergender >> 2) & 0x1;
    return buffergender;
    
}

u8 Pokemon::getForm() {
    u8 bufferform;
    memcpy(&bufferform, &data[GENDERPOS], GENDERLENGTH);
    bufferform = (bufferform >> 3);
    return bufferform;
}

u8 Pokemon::getHPType() {
    return 15 * ((getIV(HP)& 1) + 2 * (getIV(ATK) & 1) + 4 * (getIV(DEF) & 1) + 8 * (getIV(SPE) & 1) + 16 * (getIV(SPA) & 1) + 32 * (getIV(SPD) & 1)) / 63;
}    

u16 Pokemon::getStat(const int stat) {
    u16 tempspecies = getPokedexNumber();
    if( getForm() )
        tempspecies = ExtDataManager::getFormData(tempspecies) + getForm() - 1;
    
    u8 mult = 10;
    u16 final;
    u8 basestat;
    if(stat == Pokemon::HP) basestat = ExtDataManager::getBaseHP(tempspecies);
    if(stat == Pokemon::ATK) basestat = ExtDataManager::getBaseATK(tempspecies);
    if(stat == Pokemon::DEF) basestat = ExtDataManager::getBaseDEF(tempspecies);
    if(stat == Pokemon::SPE) basestat = ExtDataManager::getBaseSPE(tempspecies);
    if(stat == Pokemon::SPA) basestat = ExtDataManager::getBaseSPA(tempspecies);
    if(stat == Pokemon::SPD) basestat = ExtDataManager::getBaseSPD(tempspecies);
    
    if(stat == Pokemon::HP)
         final = 10 + ((2 * basestat) + getIV(stat) + getEV(stat) / 4 + 100) * getLevel() / 100;
    else
        final = 5 + (2 * basestat + getIV(stat) + getEV(stat) / 4) * getLevel() / 100; 
    
    if (getNature() / 5 + 1 == stat)
        mult++;
    if (getNature() % 5 + 1 == stat)
        mult--;
  
    final = final * mult / 10;
    return final;
}

void Pokemon::setNickname(std::string nick) {
    u8 toinsert[NICKNAMELENGTH];
    for(int i = 0; i < NICKNAMELENGTH; i++)
        toinsert[i] = 0;
    
    for(unsigned int i = 0; i < nick.size(); i++)
        toinsert[i*2] = nick.c_str()[i];
    
    memcpy(&data[NICKNAMEPOS], toinsert, NICKNAMELENGTH);
    setPkmn();
}

void Pokemon::setNature(const u8 nature) {
    memcpy(&data[NATUREPOS], &nature, NATURELENGTH);
    setPkmn();
}

void Pokemon::setAbility(const u8 ability) {
    setAbilityNum(ability);
    
    std::vector<u8> resultset = ExtDataManager::getAbilitySet(getPokedexNumber());
    
    u8 abilitytemp;
    if( ability == 1 )
        abilitytemp = 0;
    
    if( ability == 2 )
        abilitytemp = 1;
    
    if( ability == 4 )
        abilitytemp = 2;
    
    u8 toset = resultset[abilitytemp];
    
    memcpy(&data[ABILITYPOS], &toset, ABILITYLENGTH);
    setPkmn();
}

void Pokemon::setAbilityNum(const u8 abilitynum) {
    memcpy(&data[ABILITYNUMPOS], &abilitynum, ABILITYNUMLENGTH);
    //setPkmn();
}

void Pokemon::setItem(const u16 item) {
    memcpy(&data[ITEMPOS], &item, ITEMLENGTH);
    setPkmn();
}

void Pokemon::setBall(const u8 ball) {
    memcpy(&data[POKEBALLPOS], &ball, POKEBALLLENGTH);
    setPkmn();
}

void Pokemon::setShiny(const bool shiny) {
    while(isShiny() != shiny)
        rerollPID();
        
    setPkmn();
}

void Pokemon::setMove(const u16 move, const int nmove) {
    memcpy(&data[MOVEPOS+(MOVELENGTH*nmove)], &move, MOVELENGTH);
    setPkmn();
}

void Pokemon::setEggmove(const u16 move, const int nmove) {
    memcpy(&data[EGGMOVEPOS+(EGGMOVELENGTH*nmove)], &move, EGGMOVELENGTH);
    setPkmn();
}

void Pokemon::setIV(const u8 val, const int stat) {
  u32 nval = val;
  u32 mask = 0xFFFFFFFF;
  mask ^= 0x1F << (5 * stat);
  
  u32 buffer;
  memcpy(&buffer, &data[IVPOS], IVLENGTH);

  buffer &= mask;
  buffer ^= ((nval & 0x1F) << (5 * stat));
  memcpy(&data[IVPOS], &buffer, IVLENGTH);
  setPkmn();
}

void Pokemon::setEV(const u8 val, const int stat) {
    memcpy(&data[EVPOS+(EVLENGTH*stat)], &val, EVLENGTH);
    setPkmn();
}

void Pokemon::setLevel(const int lv) {
    u32 towrite = expTableLookup(lv-1, ExtDataManager::getLevelType(getPokedexNumber()));
    memcpy(&data[EXPPOINTPOS], &towrite, EXPPOINTLENGTH);
    setPkmn();
}

void Pokemon::setPokedexNumber(const u16 val) {
    memcpy(&data[POKEDEXNUMBERPOS], &val, POKEDEXNUMBERLENGTH);
    setPkmn();
}

void Pokemon::setGender(const u8 val) {
    u8 buffergender;
    memcpy(&buffergender, &data[GENDERPOS], GENDERLENGTH);
    
    buffergender &= 0xF9;
    buffergender ^= (val & 0x3) << 1;
    
    memcpy(&data[GENDERPOS], &buffergender, GENDERLENGTH);
    setPkmn();
}

void Pokemon::setForm(const u8 val) {
    u8 bufferform;
    memcpy(&bufferform, &data[GENDERPOS], GENDERLENGTH);
    
    bufferform &= 0x7;
    bufferform ^= val << 3;
    
    memcpy(&data[GENDERPOS], &bufferform, GENDERLENGTH);
    setPkmn();
}

void Pokemon::setHPType(const int val) {
    u8 ivstat[6];
    for(int i = 0; i < 6; i++)
        ivstat[i] = getIV(i);
    
    u8 hpivs[16][6] = {
        { 1, 1, 0, 0, 0, 0 }, //Fighting
        { 0, 0, 0, 1, 0, 0 }, //Flying
        { 1, 1, 0, 1, 0, 0 }, // Poison
        { 1, 1, 1, 1, 0, 0 }, // Ground
        { 1, 1, 0, 0, 1, 0 }, // Rock
        { 1, 0, 0, 1, 1, 0 }, // Bug
        { 1, 0, 1, 1, 1, 0 }, // Ghost
        { 1, 1, 1, 1, 1, 0 }, // Steel
        { 1, 0, 1, 0, 0, 1 }, // Fire
        { 1, 0, 0, 1, 0, 1 }, // Water
        { 1, 0, 1, 1, 0, 1 }, // Grass
        { 1, 1, 1, 1, 0, 1 }, // Electric
        { 1, 0, 1, 0, 1, 1 }, // Psychic
        { 1, 0, 0, 1, 1, 1 }, // Ice
        { 1, 0, 1, 1, 1, 1 }, // Dragon
        { 1, 1, 1, 1, 1, 1 }, // Dark
    };
    
    for(int i = 0; i < 6; i++)
         ivstat[i] = (ivstat[i] & 0x1E) + hpivs[val][i];
    
    for(int i = 0; i < 6; i++) {
        setIV(ivstat[i], i);
        this->save->getPkmn(this->boxnumber, this->indexnumber, data);
    }
}

bool Pokemon::isNicknamed() {
    u32 buffer;
    
    memcpy(&buffer, &data[IVPOS], IVLENGTH);
    return (buffer >> 31) & 1;
}

void Pokemon::setPkmn() {
    if( boxnumber >= 31 )
        fillBattleSection();
    
    save->setPkmn(boxnumber, indexnumber, data);
}

void Pokemon::setDataPtr(char* dat) {
    memcpy(this->data, dat, 232);
    setPkmn();
}

bool Pokemon::clone(const int boxdestination, const int indexdestination, const bool commit) {
    this->boxnumber = boxdestination;
    this->indexnumber = indexdestination;
    setPkmn();
    
    if( commit )
        return savePkmn();
    
    else return 0;
}

bool Pokemon::importPK6(std::string path) {
    if( save->getPkmn(path, data) != 0 )
        return 1;
    
    setPkmn();
    savePkmn();
    return 0;
}

bool Pokemon::exportPK6(std::string path) {
    return save->setPkmn(path, data);
}

bool Pokemon::savePkmn() {
    return this->save->writeSaveFile();
}

void Pokemon::rerollPID() {
    srand(getPID());
    u32 pidbuffer = rand();
    
    memcpy(&data[PIDPOS], &pidbuffer, PIDLENGTH);
    //setPkmn();
}

void Pokemon::fillBattleSection() {
    u8 battle = 0;
    memcpy(&data[BATTLEPOS], &battle, BATTLELENGTH);
    
    u8 level = getLevel();
    memcpy(&data[BATTLELEVELPOS], &level, BATTLELEVELLENGTH);
    
    u16 currenthp = getStat(Pokemon::HP);
    memcpy(&data[BATTLEHPCURRENTPOS], &currenthp, BATTLEHPCURRENTLENGTH);
    memcpy(&data[BATTLEHPMAXPOS], &currenthp, BATTLEHPMAXLENGTH);
    
    u16 atk = getStat(Pokemon::ATK);
    memcpy(&data[BATTLEATKPOS], &atk, BATTLEATKLENGTH);
    
    u16 def = getStat(Pokemon::DEF);
    memcpy(&data[BATTLEDEFPOS], &def, BATTLEDEFLENGTH);
    
    u16 spe = getStat(Pokemon::SPE);
    memcpy(&data[BATTLESPEEDPOS], &spe, BATTLESPEEDLENGTH);
    
    u16 satk = getStat(Pokemon::SPA);
    memcpy(&data[BATTLESATKPOS], &satk, BATTLESATKLENGTH);
    
    u16 sdef = getStat(Pokemon::SPD);
    memcpy(&data[BATTLESDEFPOS], &sdef, BATTLESDEFLENGTH);
}

u32 Pokemon::expTableLookup(const int level, const int exptype) {
    u32 expTable[100][6] = {
  {0, 0, 0, 0, 0, 0},
  {8, 15, 4, 9, 6, 10},
  {27, 52, 13, 57, 21, 33},
  {64, 122, 32, 96, 51, 80},
  {125, 237, 65, 135, 100, 156},
  {216, 406, 112, 179, 172, 270},
  {343, 637, 178, 236, 274, 428},
  {512, 942, 276, 314, 409, 640},
  {729, 1326, 393, 419, 583, 911},
  {1000, 1800, 540, 560, 800, 1250},
  {1331, 2369, 745, 742, 1064, 1663},
  {1728, 3041, 967, 973, 1382, 2160},
  {2197, 3822, 1230, 1261, 1757, 2746},
  {2744, 4719, 1591, 1612, 2195, 3430},
  {3375, 5737, 1957, 2035, 2700, 4218},
  {4096, 6881, 2457, 2535, 3276, 5120},
  {4913, 8155, 3046, 3120, 3930, 6141},
  {5832, 9564, 3732, 3798, 4665, 7290},
  {6859, 11111, 4526, 4575, 5487, 8573},
  {8000, 12800, 5440, 5460, 6400, 10000},
  {9261, 14632, 6482, 6458, 7408, 11576},
  {10648, 16610, 7666, 7577, 8518, 13310},
  {12167, 18737, 9003, 8825, 9733, 15208},
  {13824, 21012, 10506, 10208, 11059, 17280},
  {15625, 23437, 12187, 11735, 12500, 19531},
  {17576, 26012, 14060, 13411, 14060, 21970},
  {19683, 28737, 16140, 15244, 15746, 24603},
  {21952, 31610, 18439, 17242, 17561, 27440},
  {24389, 34632, 20974, 19411, 19511, 30486},
  {27000, 37800, 23760, 21760, 21600, 33750},
  {29791, 41111, 26811, 24294, 23832, 37238},
  {32768, 44564, 30146, 27021, 26214, 40960},
  {35937, 48155, 33780, 29949, 28749, 44921},
  {39304, 51881, 37731, 33084, 31443, 49130},
  {42875, 55737, 42017, 36435, 34300, 53593},
  {46656, 59719, 46656, 40007, 37324, 58320},
  {50653, 63822, 50653, 43808, 40522, 63316},
  {54872, 68041, 55969, 47846, 43897, 68590},
  {59319, 72369, 60505, 52127, 47455, 74148},
  {64000, 76800, 66560, 56660, 51200, 80000},
  {68921, 81326, 71677, 61450, 55136, 86151},
  {74088, 85942, 78533, 66505, 59270, 92610},
  {79507, 90637, 84277, 71833, 63605, 99383},
  {85184, 95406, 91998, 77440, 68147, 106480},
  {91125, 100237, 98415, 83335, 72900, 113906},
  {97336, 105122, 107069, 89523, 77868, 121670},
  {103823, 110052, 114205, 96012, 83058, 129778},
  {110592, 115015, 123863, 102810, 88473, 138240},
  {117649, 120001, 131766, 109923, 94119, 147061},
  {125000, 125000, 142500, 117360, 100000, 156250},
  {132651, 131324, 151222, 125126, 106120, 165813},
  {140608, 137795, 163105, 133229, 112486, 175760},
  {148877, 144410, 172697, 141677, 119101, 186096},
  {157464, 151165, 185807, 150476, 125971, 196830},
  {166375, 158056, 196322, 159635, 133100, 207968},
  {175616, 165079, 210739, 169159, 140492, 219520},
  {185193, 172229, 222231, 179056, 148154, 231491},
  {195112, 179503, 238036, 189334, 156089, 243890},
  {205379, 186894, 250562, 199999, 164303, 256723},
  {216000, 194400, 267840, 211060, 172800, 270000},
  {226981, 202013, 281456, 222522, 181584, 283726},
  {238328, 209728, 300293, 234393, 190662, 297910},
  {250047, 217540, 315059, 246681, 200037, 312558},
  {262144, 225443, 335544, 259392, 209715, 327680},
  {274625, 233431, 351520, 272535, 219700, 343281},
  {287496, 241496, 373744, 286115, 229996, 359370},
  {300763, 249633, 390991, 300140, 240610, 375953},
  {314432, 257834, 415050, 314618, 251545, 393040},
  {328509, 267406, 433631, 329555, 262807, 410636},
  {343000, 276458, 459620, 344960, 274400, 428750},
  {357911, 286328, 479600, 360838, 286328, 447388},
  {373248, 296358, 507617, 377197, 298598, 466560},
  {389017, 305767, 529063, 394045, 311213, 486271},
  {405224, 316074, 559209, 411388, 324179, 506530},
  {421875, 326531, 582187, 429235, 337500, 527343},
  {438976, 336255, 614566, 447591, 351180, 548720},
  {456533, 346965, 639146, 466464, 365226, 570666},
  {474552, 357812, 673863, 485862, 379641, 593190},
  {493039, 367807, 700115, 505791, 394431, 616298},
  {512000, 378880, 737280, 526260, 409600, 640000},
  {531441, 390077, 765275, 547274, 425152, 664301},
  {551368, 400293, 804997, 568841, 441094, 689210},
  {571787, 411686, 834809, 590969, 457429, 714733},
  {592704, 423190, 877201, 613664, 474163, 740880},
  {614125, 433572, 908905, 636935, 491300, 767656},
  {636056, 445239, 954084, 660787, 508844, 795070},
  {658503, 457001, 987754, 685228, 526802, 823128},
  {681472, 467489, 1035837, 710266, 545177, 851840},
  {704969, 479378, 1071552, 735907, 563975, 881211},
  {729000, 491346, 1122660, 762160, 583200, 911250},
  {753571, 501878, 1160499, 789030, 602856, 941963},
  {778688, 513934, 1214753, 816525, 622950, 973360},
  {804357, 526049, 1254796, 844653, 643485, 1005446},
  {830584, 536557, 1312322, 873420, 664467, 1038230},
  {857375, 548720, 1354652, 902835, 685900, 1071718},
  {884736, 560922, 1415577, 932903, 707788, 1105920},
  {912673, 571333, 1460276, 963632, 730138, 1140841},
  {941192, 583539, 1524731, 995030, 752953, 1176490},
  {970299, 591882, 1571884, 1027103, 776239, 1212873},
  {1000000, 600000, 1640000, 1059860, 800000, 1250000} };
    
  return expTable[level][exptype];
}