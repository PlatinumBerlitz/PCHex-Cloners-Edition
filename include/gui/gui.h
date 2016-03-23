#ifndef GUI_H
#define GUI_H

#include <string>

void initializationError(const int err);
void ciaConsole(int& game, int& mediatype);
void inputHandler();
void drawTopScreen();

void changeBox(const int val);
void selectClone();
void clone();
void multipleSelectClone();
void multipleClone();
void selectImport();
void import();
#endif /* GUI_H */

