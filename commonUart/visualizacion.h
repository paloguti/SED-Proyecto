#ifndef VISUALIZACION_H_
#define VISUALIZACION_H_

#include "lcd.h"
#include <stdlib.h>

#define Wall	(0x2)
#define Dirt	(0x1)
#define NoNe	(0x0)

#define NUMBER_OF_DIRT (0x60) // 96

void init_visualizacion(void);
void init_welcomeBoom(void);
void drawMap16x16(void);
void drawWall16x16(int x, int y);
void drawDirt16x16(int x, int y);
void drawExit16x16(int x,int y);
void drawSprite16x16(int posX, int posY,  uint8* sprite);
void drawPlayer16x16(void);
void drawPlayerF16x16(int posX, int posY, int aux);
void clear16x16(int posX, int posY);
void drawBomb16x16(int posX, int posY);
void redrawChanging();
void drawWin();
void drawLose();

#endif /* VISUALIZACION_H_ */
