#ifndef BOMBLOGIC_H_
#define BOMBLOGIC_H_

#include "visualizacion.h"
#include "gameLogic.h"
#include "uart.h"

void setBomb(int posX, int posY);
void boomBomb(int mineOrFriends);

#endif /* BOMBLOGIC_H_ */
