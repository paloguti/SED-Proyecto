#ifndef GAMELOGIC_H_
#define GAMELOGIC_H_

#include "visualizacion.h"
#include "uart.h"

void initExitPosition16x16(void);
void generateDirt16x16(void);

void _gameOver(void);
void gameOver(void);
void _gameWin(void);
void gameWin(void);


#endif /* GAMELOGIC_H_ */
