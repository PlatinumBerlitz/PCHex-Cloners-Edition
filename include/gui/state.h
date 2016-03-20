#ifndef STATE_H
#define STATE_H

class State {
    private:
        static int mode;
        static int ciaselected;
        static int indexnumber;
        static int boxnumber;
        
    public:
        static const int EXITMODE = 0;
        static const int SELECTMODE = 1;
        static const int CLONEMODE = 2;
        
        static int getMode() { return mode; } 
        static void setMode(const int val) { mode = val; }
        static unsigned int getCiaSelected() { return ciaselected; }
        static void setCiaSelected(const int val);
        static int getIndexNumber() { return indexnumber; }
        static void setIndexNumber(const int val);
        static int getBoxNumber() { return boxnumber; }
        static void setBoxNumber(const int val);
};

#endif /* STATE_H */

