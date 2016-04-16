#ifndef STATE_H
#define STATE_H

#include <string>
#include <vector>
#include <hbkb.h>

#include "Pokemon.h"

class State {
    private:
        static int mode;
        static int ciaselected;
        static int indexnumber;
        static int boxnumber;
        static int indexcloneorigin;
        static int boxcloneorigin;
        static std::string overlaymsg;
        static int backupmode;
        static int multipleselectiontick;
        static bool tick;
        static unsigned int eovselected;
        static std::vector<std::string> eovvector;
        static int eovmode;
        static std::string currentfolder;
        static int keyboardstate;
        static int skip;
        static int keyboarddelay;
        static int touchid;
        static int buttondelay;
        static int keepbuttondelay;
        static char tempbackup[232];
        static int tab;
        static int tabkeyboarddelay;
        static bool shoulderless;
        
    public:
        static const int EXITMODE = 0;
        static const int SELECTMODE = 1;
        static const int CLONEMODE = 2;
        static const int OVERLAYMODE = 3;
        static const int MULTIPLESELECTMODE = 4;
        static const int MULTIPLECLONEMODE = 5;
        static const int EDITABLEOVERLAYMODE = 6;
        static const int EDITMODE = 7;
        
        static const int IMPORTEOV = 0;
        static const int NATUREEOV = 1;
        static const int ABILITYEOV = 2;
        static const int ITEMEOV = 3;
        static const int BALLEOV = 4;
        static const int SPECIESEOV = 5;
        static const int MOVE1EOV = 12;
        static const int MOVE2EOV = 13;
        static const int MOVE3EOV = 14;
        static const int MOVE4EOV = 15;
        static const int EGGMOVE1EOV = 16;
        static const int EGGMOVE2EOV = 17;
        static const int EGGMOVE3EOV = 18;
        static const int EGGMOVE4EOV = 19;
        static const int HIDDENPOWEREOV = 20;
        
        static const int SPECIESBUTTON = 1;
        static const int NATUREBUTTON = 2;
        static const int ABILITYBUTTON = 3;
        static const int ITEMBUTTON = 4;
        static const int BALLBUTTON = 5;
        static const int SHINYBUTTON = 6;
        static const int GENDERBUTTON = 7;
        static const int LVBUTTONDOWN = 8;
        static const int LVBUTTONUP = 9;
        static const int OTBUTTON = 10;
        static const int TABBUTTON = 11;
        static const int MOVE1BUTTON = 12;
        static const int MOVE2BUTTON = 13;
        static const int MOVE3BUTTON = 14;
        static const int MOVE4BUTTON = 15;
        static const int EGGMOVE1BUTTON = 16;
        static const int EGGMOVE2BUTTON = 17;
        static const int EGGMOVE3BUTTON = 18;
        static const int EGGMOVE4BUTTON = 19;
        static const int HPIVBUTTONDOWN = 20;
        static const int ATKIVBUTTONDOWN = 21;
        static const int DEFIVBUTTONDOWN = 22;
        static const int SPAIVBUTTONDOWN = 24;
        static const int SPDIVBUTTONDOWN = 25;
        static const int SPEIVBUTTONDOWN = 23;
        static const int HPIVBUTTONUP = 26;
        static const int ATKIVBUTTONUP = 27;
        static const int DEFIVBUTTONUP = 28;
        static const int SPAIVBUTTONUP = 30;
        static const int SPDIVBUTTONUP = 31;
        static const int SPEIVBUTTONUP = 29;
        static const int HPEVBUTTONDOWN = 32;
        static const int ATKEVBUTTONDOWN = 33;
        static const int DEFEVBUTTONDOWN = 34;
        static const int SPAEVBUTTONDOWN = 36;
        static const int SPDEVBUTTONDOWN = 37;
        static const int SPEEVBUTTONDOWN = 35;
        static const int HPEVBUTTONUP = 38;
        static const int ATKEVBUTTONUP = 39;
        static const int DEFEVBUTTONUP = 40;
        static const int SPAEVBUTTONUP = 42;
        static const int SPDEVBUTTONUP = 43;
        static const int SPEEVBUTTONUP = 41;
        static const int LSHOULDERLESSBUTTON = 42;
        static const int RSHOULDERLESSBUTTON = 43;
        static const int HIDDENPOWERBUTTON = 44;
        
        static const int GENERALTAB = 0;
        static const int COMBATTAB = 1;
        
        static HB_Keyboard keyboard;
        
        static int getMode() { return mode; } 
        static void setMode(const int val) { mode = val; }
        static unsigned int getCiaSelected() { return ciaselected; }
        static void setCiaSelected(const int val);
        static int getIndexNumber() { return indexnumber; }
        static void setIndexNumber(const int val);
        static int getBoxNumber() { return boxnumber; }
        static void setBoxNumber(const int val);
        static int getBoxCloneOrigin() { return boxcloneorigin; }
        static int getIndexCloneOrigin() { return indexcloneorigin; }
        static void setCloneOrigin(const int box, const int index) { boxcloneorigin = box; indexcloneorigin = index; }
        static int getBackupMode() { return backupmode; }
        static void setBackupMode(const int val) { backupmode = val; }
        static std::string getOverlayMsg() { return overlaymsg; }
        static void setOverlayMsg(const std::string val) { overlaymsg = val; } 
        static bool getMultipleSelectionTick();
        static unsigned int getEovSelected() { return eovselected; }
        static void setEovSelected(const unsigned int val );
        static std::vector<std::string> getEovVector() { return eovvector; }
        static void setEovVector(const std::vector<std::string> val) { eovvector = val; }
        static int getEovMode() { return eovmode; }
        static void setEovMode(const int val) { eovmode = val; }
        static std::string getCurrentFolder() { return currentfolder; }
        static void setCurrentFolder(std::string val) { currentfolder = val; }
        static int getKeyboardState() { return keyboardstate; }
        static void setKeyboardState(const int val) { keyboardstate = val; }
        static int getSkip() { return skip; }
        static void setSkip(const int val) { if( val >= 0 ) skip = val; }
        static int getKeyboardDelay() { return keyboarddelay; }
        static void setKeyboardDelay(const int val) { keyboarddelay = val; }
        static int getTouchId() { return touchid; }
        static void setTouchId(const int val) { touchid = val; } 
        static int getButtonDelay() { return buttondelay; }
        static void setButtonDelay(const int val) { buttondelay = val; } 
        static int getKeepButtonDelay() { return keepbuttondelay; }
        static void setKeepButtonDelay(const int val) { keepbuttondelay = val; }
        static void getTempBackup(Pokemon* pika);
        static void setTempBackup(Pokemon* pika);
        static int getTab() { return tab; }
        static void setTab(const int val) { tab = val; }
        static int getTKDelay() { return tabkeyboarddelay; }
        static void setTKDelay(const int val) { tabkeyboarddelay = val; }
        static bool getShoulderless() { return shoulderless; }
        static void setShoulderless(const bool val) { shoulderless = val; }
};

#endif /* STATE_H */

