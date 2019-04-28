#include "visualizacion.h"

extern const int NCOL;

//TABLERO 320x240
// Pinta una linea al completo
/*	lcd_draw_hline(0,320,80,0xffffff,5);
lcd_draw_hline(0,320,160,0xffffff,5);
lcd_draw_vline(240,0,105,0xffffff,5);
lcd_draw_vline(240,0,210,0xffffff,5);

lcd_puts_x2(40,20,0xffffff,"X");
lcd_puts_x2(40,20,0xffffff,"X");
lcd_puts_x2(40,20,0xffffff,"X");*/

void init_visualizacion(void){
	lcd_init();
	lcd_clear();
	//init_welcome3R();
	//drawTab3x3();
}

void drawTab(void){
	int i, j;
	int nCol=NCOL;
	int xMax=320, yMax=240;

	for (i = 1; i<nCol; i++)
	{
		lcd_draw_hline(0,xMax,(yMax/nCol)*i,0xffffff,5);
		lcd_draw_vline(yMax,0,(xMax/nCol)*i,0xffffff,5);
	}
}

void init_welcome3R(void){
	lcd_puts_x2( 0, 20, BLACK, "     3 EN RAYA     " );
	lcd_puts( 0, 60, BLACK, "   Comienza el juego!   " );
}

void drawX(int posicion){

	if (posicion == 0){
		lcd_puts_x2(25,20,0xffffff,"X");
	}
	else if (posicion == 1){
		lcd_puts_x2(80,20,0xffffff,"X");
	}
	else if (posicion == 2){
		lcd_puts_x2(120,20,0xffffff,"X");
	}
	else if (posicion == 3){
		lcd_puts_x2(25,110,0xffffff,"X");
	}
	else if (posicion == 4){
		lcd_puts_x2(80,110,0xffffff,"X");
	}
	else if (posicion == 5){
		lcd_puts_x2(120,110,0xffffff,"X");
	}
	else if (posicion == 6){
		lcd_puts_x2(25,200,0xffffff,"X");
	}
	else if (posicion == 7){
		lcd_puts_x2(80,200,0xffffff,"X");
	}
	else if (posicion == 8){
		lcd_puts_x2(120,200,0xffffff,"X");
	}

}

void drawO(int posicion){

	if (posicion == 0){
		lcd_puts_x2(25,20,0xffffff,"O");
	}
	else if (posicion == 1){
		lcd_puts_x2(80,20,0xffffff,"O");
	}
	else if (posicion == 2){
		lcd_puts_x2(120,20,0xffffff,"O");
	}
	else if (posicion == 3){
		lcd_puts_x2(25,110,0xffffff,"O");
	}
	else if (posicion == 4){
		lcd_puts_x2(80,110,0xffffff,"O");
	}
	else if (posicion == 5){
		lcd_puts_x2(120,110,0xffffff,"O");
	}
	else if (posicion == 6){
		lcd_puts_x2(25,200,0xffffff,"O");
	}
	else if (posicion == 7){
		lcd_puts_x2(80,200,0xffffff,"O");
	}
	else if (posicion == 8){
		lcd_puts_x2(120,200,0xffffff,"O");
	}

}

void drawFin(int fin){
	if (fin == 1){
		lcd_clear();
		lcd_puts_x2( 0, 20, BLACK, "      GANA O      " );
	}
	else if (fin == 2){
		lcd_clear();
		lcd_puts_x2( 0, 20, BLACK, "      GANA X      " );
	}
	else if (fin == 3){
		lcd_clear();
		lcd_puts_x2( 0, 20, BLACK, "      EMPATE      " );
	}
}
