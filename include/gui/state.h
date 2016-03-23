#ifndef STATE_H
#define STATE_H

#include <string>
#include <vector>

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
        
    public:
        static const int EXITMODE = 0;
        static const int SELECTMODE = 1;
        static const int CLONEMODE = 2;
        static const int OVERLAYMODE = 3;
        static const int MULTIPLESELECTMODE = 4;
        static const int MULTIPLECLONEMODE = 5;
        static const int EDITABLEOVERLAYMODE = 6;
        
        static const int IMPORTEOV = 0;
        
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
};

#endif /* STATE_H */

