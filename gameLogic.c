#include "gameLogic.h"

/*
 * MÓDULO EN EL QUE SE DEFINEN LAS REGLAS DEL JUEGO 3 EN RAYA
 */

extern int tablero[];
extern const int NCOL;

/*
 * Función que devuelve:
 * 0 si NO ha acabado el juego
 * 1 si ha ganado el jugador 1
 * 2 si ha ganado el jugador 2
 * 3 si han quedado empate
 */
int comprobarFinDelJuego(){
	int fin = 0; // fin = 0 significa que no ha acabado el juego
	int lleno = 0; //lleno = 0 significa que aún hay sitios vacíos
	//Primero comprobamos si el tablero está lleno
	int i;
	int cont = 0;
	for(i = 0; i < NCOL*NCOL; i++ ){
		if(tablero[i] != 0){
			cont = cont + 1;
		}
	}
	if(cont == NCOL*NCOL){
		lleno = 1;
	}

	int ganador = 0; //ganador = 0 significa que aún no hay ganador.

	ganador = comprobarGanador();

	if(ganador != 0){
		fin = ganador;
	}
	else if (lleno == 1){
		fin = 3;
	}
	else {
		fin = 0;
	}

	return fin;
}

int comprobarGanador(){

	int ganador = 0; // 0 si no hay ganador
	int fin = 0; // 0 si no ha acabado de comprobar
	int i = 0;

	//Comprobamos si hay tres en raya en alguna fila
	for(i = 0; i < NCOL*NCOL; i += NCOL ){ //Num filas
		int j = 0;
		int ant = tablero[i+j];
		if (ant != 0){
			while (ant == tablero[i+j] && j < NCOL){
				j++;
			}
			if (j == NCOL){
				ganador = tablero[i];
			}
		}
	}
	// Comprobamos las columnas
	if (ganador == 0){
		for (i = 0; i < NCOL; i++){
			int j = 0;
			int ant = tablero[i+j];
			if (ant != 0){
				while(ant == tablero[i+j] && j < NCOL*NCOL){
					j += NCOL;
				}
				if (j == NCOL*NCOL){
					ganador = tablero[i];
				}
			}
		}
	}

	//Comprobamos las diagonales
	if (ganador == 0){
		int valor = -1;
		int contador = 0;
		//primera diagonal se forma siempre (0, 1*NCOL+1, 2*NCOL+1 ... )
		for(i = 0; i < NCOL; i++){
			if(valor == -1){
				valor = tablero[i*(NCOL+1)];
				contador = 1;
			}
			else if (valor == tablero[i*(NCOL+1)]){
				contador++;
			}
		}
		if(contador == NCOL){
			ganador = valor;
		}
		if(ganador == 0){
			valor = -1;
			contador = 0;
			//segunda diagonal se forma siempre (1*NCOL-1, 2*NCOL-1, 3*NCOL ...)
			for (i = 1; i <= NCOL; i++){
				if(valor == -1){
					valor = tablero[i*(NCOL-1)];
					contador = 1;
				}
				else if( valor == tablero[i*(NCOL-1)]){
					contador++;
				}
			}
			if(contador == NCOL){
				ganador = valor;
			}
		}
	}

	return ganador;
}

