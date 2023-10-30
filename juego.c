#include <stdio.h>
#include "perfil.h"
#include "batalla.h"
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#define COMPU  'C'
#define JUGADOR  'J'
#define ROHAN 'D'
#define ISENGARD  'O'


//para decidir si hay uno o dos jugadores

int main(){
    srand((unsigned int)time(NULL)); 
    juego_t juego;
    inicializar_juego(&juego);
    char modo_de_juego;
    elegir_modo(&juego,&modo_de_juego);
    int posicion = 0;
    do{
        jugar(&juego,juego.bando_de_primer_jugador,posicion);
        if (juego.modo_de_juego == COMPU){
             un_jugador(&juego);
        }else{
            dos_jugadores(&juego);

        }
    }while(juego.llegadas_rohan < 5 && juego.llegadas_isengard < 5);

    if(juego.llegadas_rohan > 5){
    	printf("rohan gano\n");
    }else{
    	printf("isengard gano\n");
    }

	return 0;
}



