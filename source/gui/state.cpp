#include "state.h"

int State::mode = State::SELECTMODE;
int State::ciaselected = 0;
int State::indexnumber = 0;
int State::boxnumber = 0;

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
    if( val >= 0 && val < 31 )
        boxnumber = val;
}