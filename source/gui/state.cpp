#include <cstring>

#include "state.h"

int State::mode = State::SELECTMODE;
int State::ciaselected = 0;
int State::indexnumber = 0;
int State::boxnumber = 0;
int State::boxcloneorigin;
int State::indexcloneorigin;
std::string State::overlaymsg;
int State::backupmode;
int State::multipleselectiontick = 0;
bool State::tick = false;
unsigned int State::eovselected = 0;
std::vector<std::string> State::eovvector;
int State::eovmode;
std::string State::currentfolder;
HB_Keyboard State::keyboard;
int State::keyboardstate;
int State::skip = 0;
int State::keyboarddelay = 0;
int State::touchid = 0;
int State::buttondelay = 0;
int State::keepbuttondelay = 0;
char State::tempbackup[232];
int State::tab = 0;

void State::setCiaSelected(const int val) {
    if(val < 0 )
        ciaselected = 4;
    
    else ciaselected = val % 5;
}

void State::setIndexNumber(const int val) {
    if( val >= 0 && val < 30 )
        indexnumber = val;
}

void State::setBoxNumber(const int val) {
    if( val > 30 )
        boxnumber = 0;
    
    else if( val < 0 )
        boxnumber = 30;
    
    else boxnumber = val;
}

bool State::getMultipleSelectionTick() {
    multipleselectiontick++;
    
    if( multipleselectiontick / 50 > 0 ) {
        tick = !tick;
        multipleselectiontick = 0;
    }
    
    return tick;
}

void State::setEovSelected(const unsigned int val) {
    if( val >= 0 && val < eovvector.size() )
        eovselected = val;
}

void State::getTempBackup(Pokemon* pika) {
    pika->setDataPtr(tempbackup);
}

void State::setTempBackup(Pokemon* pika) {
    memcpy(tempbackup, pika->getDataPtr(), 232);
}