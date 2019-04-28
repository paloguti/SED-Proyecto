#ifndef PLAYERMOVEMENT_H_
#define PLAYERMOVEMENT_H_

#include <stdlib.h>
#include "visualizacion.h"
#include "gameLogic.h"
#include "uart.h"

void initPlayerPosition16x16(int isMine);
int isValidPos(int x, int y);
void checkWinGame(void);
void movePlayerUp(void);
void movePlayerDown(void);
void movePlayerLeft(void);
void movePlayerRight(void);


#endif /* PLAYERMOVEMENT_H_ */
