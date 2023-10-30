#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "perfil.h"
#include <math.h>
#include <stdbool.h>
#include "batalla.h"
const int VIDAELFO = 200;
const int VIDAHUM = 100;
const int ATQELFO = 10;
const int ATQHUM = 50;
const int MAX_FILA_E = 5;
const int ENERGIA_INICIAL = 5;
const int MIN_FILA_E = 0;
const int MAX_FILA_U = 10;
const int MIN_FILA_U = 5;
const int FILA_HUMANO = 9;
const int FILA_ORK = 0;
const char ELFO = 'E';
const char HUMANO = 'H';
const char URUK_HAI = 'U';
const char ORK = 'O';
const char VACIO = '.';
const char ROHAN = 'D';
const char ISENGARD = 'O';
const char COMPU = 'C';
const char JUGADOR = 'J';
const char SI = 'S';
const char NO = 'X';
const int TOPE_INTENSIDAD = 10;
const int MIN_H_O_ENERGIA = 3;
const int MIN_E_U_ENERGIA = 8;

void calcular_plus(int intensidad,char tipo,int *plus_rohan,int *plus_isengard){
	int num_aleat1=rand()%6;
    int num_aleat2=rand()%6;
    if(tipo == ROHAN){
    	*plus_rohan =  intensidad * num_aleat1;
    	*plus_isengard = (TOPE_INTENSIDAD - intensidad)*num_aleat2;
    }else if(tipo == ISENGARD){
    	*plus_isengard =  intensidad * num_aleat2;
    	*plus_rohan = (TOPE_INTENSIDAD - intensidad)*num_aleat1;
    }
}
void limpiar_terreno(juego_t* juego){
    int i;
    int j;
    for(i=0; i<MAX_TERRENO_FIL; i++){
        for(j=0;j<MAX_TERRENO_COL; j++){
           juego->terreno[i][j] = VACIO;
        }
    }
}

void terreno(juego_t* juego){
    int i;
    int j;
 
    printf("\n+ ");
        for(i=1 ; i<MAX_TERRENO_COL+1 ; i++){
            printf("-");
        }
    printf("+ \n");
    for(i=0;i<MAX_TERRENO_FIL;i++){
        printf("| ");
        for(j=0;j<MAX_TERRENO_COL;j++){
            printf("%c", juego->terreno[i][j] );
        }
        printf("| \n");
    }
    printf("+ ");
    for(i=1;i<MAX_TERRENO_COL+1;i++){
        printf("-");
    }
    printf("+ \n");
}
bool posicion_libre(char terreno[MAX_TERRENO_FIL][MAX_TERRENO_COL],int col,int fila){
	return(terreno[fila][col]==VACIO);
}
//este funcion para poner 3 elfos y 3 uruk-hai en el inicio
void posicion_uruk_inicial(char terreno[MAX_TERRENO_FIL][MAX_TERRENO_COL],personaje_t cargar_isengard[3],juego_t* juego){
 	int fila;
 	int columna;
 	for(int i=0;i<3;i++){
 		do{
 			fila = rand() % (MAX_TERRENO_FIL/2-1) + 1;
			columna = rand()% (MAX_TERRENO_COL-1);
 		}while(!posicion_libre(terreno,fila,columna));
 		cargar_isengard[i].fila = fila;
        cargar_isengard[i].columna = columna;
        cargar_isengard[i].codigo = URUK_HAI;
        cargar_isengard[i].vida = VIDAELFO - juego->plus_isengard;
		cargar_isengard[i].ataque = ATQELFO + juego->plus_isengard;
 		(juego->cantidad_isengard)++;
 		terreno[fila][columna] = URUK_HAI;
 	}
}
void posicion_elfo_inicial(char terreno[MAX_TERRENO_FIL][MAX_TERRENO_COL],personaje_t cargar_elfos[3],juego_t* juego){
	int fila;
	int columna;
	for(int i=0;i<3;i++){
 		do{
            fila = rand() % (MAX_TERRENO_FIL/2-1)+(MAX_TERRENO_FIL/2);
            columna = rand()% (MAX_TERRENO_COL-1);
        }while(!posicion_libre(terreno,fila,columna));
        cargar_elfos[i].fila = fila;
        cargar_elfos[i].columna = columna;
        cargar_elfos[i].codigo = ELFO;
        cargar_elfos[i].vida = VIDAELFO - juego->plus_rohan;
		cargar_elfos[i].ataque = ATQELFO + juego->plus_rohan;
		(juego->cantidad_rohan)++;
 		terreno[fila][columna] = ELFO;
    }
}

void ingresar_personaje_valido(char *respuesta){

	while(((*respuesta)!=ELFO) || ((*respuesta)!= URUK_HAI) || ((*respuesta)!=HUMANO)||((*respuesta)!=ORK)){
        printf("insertaste un valor incorrecto,elegi un personaje para posicionar %s \n",respuesta );
	    scanf(" %s",respuesta);
	}

}
char jugador_decide_si_agregar_personaje(){
	char respuesta;
	printf("jugador,queres posicionar un personaje (S),cualquier letra para no\n");
	scanf(" %c",&respuesta);
	return respuesta;

}
void que_personaje_quiere(char* respuesta){
	scanf(" %s",respuesta);
}
void elegir_columna_validar(int columna){
	printf("que columna desea posicionar al personaje");
	scanf(" %i",&columna);
	while(columna<0 || columna>=10){
		printf(" ingresaste un valor incorrecto,ingresa columna de nuevo\n");
    	scanf("%i",&columna);
	}

}
void elegir_columna_fila_validar(int columna,int fila,int max_fil,int min_fil,char terreno[MAX_TERRENO_FIL][MAX_TERRENO_COL]){
	do
	{
		elegir_columna_validar(columna);
    	printf("ingresa fila\n");    
    	scanf("%i",&fila);
	} while(!posicion_libre(terreno,fila,columna));
}

bool energia_suficiente(juego_t* juego,char personaje){
	bool es_energia_sufuciente = false;

	printf("elegiste un %c",personaje);
	if(personaje==ELFO|| personaje== HUMANO){
		if(juego->energia_rohan>=MIN_H_O_ENERGIA && personaje==HUMANO){
			 juego->energia_rohan-=MIN_H_O_ENERGIA;
			 es_energia_sufuciente = true;
		}else if(juego->energia_rohan>=MIN_E_U_ENERGIA && personaje==ELFO){
			 juego->energia_rohan-=MIN_E_U_ENERGIA;
			 es_energia_sufuciente = true;
		}else{
			printf("no tenes energia suficiente");
		}
	}else{
		if(juego->energia_isengard>=MIN_H_O_ENERGIA && personaje==ORK){
			 juego->energia_isengard-=MIN_H_O_ENERGIA;
			 es_energia_sufuciente = true;
		}else if(juego->energia_isengard>=MIN_E_U_ENERGIA && personaje==URUK_HAI){
			 juego->energia_isengard-=MIN_E_U_ENERGIA;
			 es_energia_sufuciente = true;
		}else{
			printf("no tenes energia suficiente");
		}
	}
	return es_energia_sufuciente;
}
void cargar_info_personaje(char codigo,int fila,int columna,personaje_t* personaje, juego_t* juego, int plus, int vida,int ataque){
		
	personaje->codigo = codigo;
	if (juego->modo_de_juego== COMPU){
		columna = rand()%10+0;
		personaje->columna = columna;
	}else{

		personaje->columna = columna;
	}
    personaje->fila = fila;		   
	personaje->vida = vida - plus;
    personaje->ataque = ataque + plus;
    posicionar_personaje(juego, *personaje);

}

void ingresar_peronajes(juego_t* juego){
    int columna = 0;
    int fila = 0;
	char respuesta_de_personaje;

	printf("que personaje deseas posicionar\n");
	scanf("  %c",&respuesta_de_personaje);
    que_personaje_quiere(&respuesta_de_personaje);

	ingresar_personaje_valido(&respuesta_de_personaje);

	if(energia_suficiente(juego,respuesta_de_personaje) && 
		((respuesta_de_personaje == HUMANO) || (respuesta_de_personaje == ORK))){

	    elegir_columna_validar(columna);	
		if(respuesta_de_personaje == HUMANO){

			cargar_info_personaje(respuesta_de_personaje,FILA_HUMANO,columna,(&juego->rohan[juego->cantidad_rohan]),juego,juego->plus_rohan,VIDAHUM,ATQHUM);
		}else{
			cargar_info_personaje(respuesta_de_personaje,FILA_ORK,columna,
				&(juego->isengard[juego->cantidad_isengard]),juego,juego->plus_isengard,VIDAHUM,ATQHUM);
		}
	}else if(energia_suficiente(juego,respuesta_de_personaje) && ((respuesta_de_personaje == ELFO) || (respuesta_de_personaje == URUK_HAI))){
       if(respuesta_de_personaje == ELFO){
       		elegir_columna_fila_validar(columna,fila,MIN_FILA_E,MAX_FILA_E,juego->terreno);
			cargar_info_personaje(respuesta_de_personaje,fila,columna,
				&(juego->rohan[juego->cantidad_rohan]),juego,juego->plus_rohan,VIDAELFO,ATQELFO);
		}else{
			elegir_columna_fila_validar(columna,fila,MIN_FILA_U,MAX_FILA_U,juego->terreno);
			cargar_info_personaje(respuesta_de_personaje,fila,columna,
			&(juego->isengard[juego->cantidad_isengard]),juego,juego->plus_isengard,VIDAELFO,ATQELFO);
	    }
	}
	
}
void elegir_modo(juego_t* juego, char* modo_de_juego){
	char respuesta;
	printf("Con quien queres jugar? compu o jugador (C) o (J)\n");
	scanf(" %c", &respuesta);
	while(respuesta != COMPU && respuesta != JUGADOR){
		printf("Insertaste un valor incorrecto, por favor corrijalo (C) o (J)\n");
		scanf(" %c", &respuesta);
	}
	juego->modo_de_juego = respuesta;
}
void jugar_segun_turno(juego_t* juego, char contrincante){
	char respuesta = jugador_decide_si_agregar_personaje();
	if (respuesta == SI){
    	ingresar_peronajes(juego);
    }
    
    juego->turno = contrincante;

}
void dos_jugadores(juego_t* juego){
    
    if(juego->turno == ROHAN){
    	jugar_segun_turno(juego,ISENGARD);
    	(juego->energia_rohan)++;
    }
    if (juego->turno == ISENGARD){
		jugar_segun_turno(juego,ROHAN);
		(juego->energia_isengard)++;
    }
}

void un_jugador(juego_t* juego){
    int columna = 0;
	if (juego->turno == COMPU){
		if (juego->turno == ISENGARD){
            cargar_info_personaje(HUMANO,FILA_HUMANO,columna,
			&(juego->rohan[juego->cantidad_rohan]),juego,juego->plus_rohan,VIDAHUM,ATQHUM);
			juego->turno=ISENGARD;
		}else{
			cargar_info_personaje(ORK,FILA_ORK,columna,
			&(juego->isengard[juego->cantidad_isengard]),juego,juego->plus_isengard,VIDAHUM,ATQHUM);
			juego->turno=ROHAN;
		}
	}else if(juego->turno== ISENGARD){
		jugar_segun_turno(juego,COMPU);
		(juego->energia_isengard)++;
	}else{
		jugar_segun_turno(juego,COMPU);
		(juego->energia_rohan)++;
	}
} 
void inicializar_juego(juego_t* juego){
	juego->cantidad_rohan = 0;
	juego->llegadas_rohan = 0;
	juego->cantidad_isengard = 0;
	juego->llegadas_isengard = 0;
	juego->energia_rohan = ENERGIA_INICIAL;
	juego->energia_isengard = ENERGIA_INICIAL;
	int intensidad = 0;
	char tipo = 'L' ;
	perfil(&tipo,&intensidad);
	juego->bando_de_primer_jugador = tipo;
	juego->turno = tipo;
	calcular_plus(intensidad,tipo,&juego->plus_rohan,&juego->plus_isengard);
	limpiar_terreno(juego);
	posicion_uruk_inicial((*juego).terreno,juego->isengard,juego);
	posicion_elfo_inicial((*juego).terreno,juego->rohan,juego);
	terreno(juego);	
}


void posicionar_personaje(juego_t* juego, personaje_t personaje){

	if(personaje.codigo == HUMANO || personaje.codigo == ELFO){
		juego->rohan[juego->cantidad_rohan] = personaje;
		(juego->cantidad_rohan)++;
	}else{
		juego->isengard[juego->cantidad_isengard] = personaje;
		(juego->cantidad_isengard)++;
	}
	juego->terreno[personaje.fila][personaje.columna] = personaje.codigo;
}

int calcular_distancia_manhattan(int fil_atacante,int col_atacante,int fil_victima,int col_victima){
  	return((abs(fil_victima-fil_atacante))+(abs(col_victima-col_atacante)));

}
void determinar_estado_victima(char bando,juego_t* juego,int ataque,int vida,int pos_1, int pos_sig){    
	if (bando == ROHAN){
        if (juego->isengard[pos_1].vida >= ataque)
        {
            juego->isengard[pos_1].vida -= ataque;
        }else{
            for(int i=pos_1;pos_sig < juego->cantidad_rohan;i++){
                 juego->rohan[pos_1] = juego->rohan[pos_sig];
             }
       }
       juego->cantidad_rohan--;
   }else if (bando == ISENGARD){        if (juego->rohan[pos_1].vida >= ataque)
        {
            juego->rohan[pos_1].vida -=ataque;
        
        }else{
             for(int i=pos_1;pos_sig < juego->cantidad_isengard;i++){
                 juego->isengard[pos_1] = juego->isengard[pos_sig];
            }
        }    juego->cantidad_isengard--;
   }
}
void ataque_elfos_urukhai(juego_t* juego,char bando,int pos_personaje, int* tope){
    int distancia_calculada = 0;
   if(bando == ROHAN){
       for(int i =0;i<juego->cantidad_rohan;i++){
           distancia_calculada = calcular_distancia_manhattan(juego->rohan[i].fila,juego->rohan[i].
                                 columna,juego->isengard[i].fila,juego->isengard[i].columna);
           if(distancia_calculada==3){
               determinar_estado_victima(bando,juego,juego->rohan[i].ataque,juego->isengard[i].vida,i,i+1);
               
           }
       }
   }else{
       for(int i =0;i<juego->cantidad_isengard;i++){
           distancia_calculada = calcular_distancia_manhattan(juego->isengard[i].fila,juego->isengard[i].
                                 columna,juego->rohan[i].fila,juego->rohan[i].columna);
           if(distancia_calculada==3){
               determinar_estado_victima(bando,juego,juego->isengard[i].ataque,juego->rohan[i].vida,i,i+1);
               
           }
       }
   }
}
//calcular distancia manhattan para humano y orko
bool puede_atacar(int fila_atacante,int columna_atacante,int fila_victima,int columna_victima){
	return(((fila_victima== fila_atacante)||(fila_victima==fila_atacante+1)||(fila_victima== fila_atacante-1)||
		(columna_victima==columna_atacante)||(columna_victima==columna_atacante+1)||(columna_victima==columna_atacante-1)));
}
void ataque_humano_orko(juego_t* juego,char bando, int posicion, int* tope, personaje_t atacante, personaje_t victima[MAX_PERSONAJES]){
   
    for(int i =0;i<(*tope);i++){
        	
       	determinar_estado_victima(bando,juego,juego->rohan[i].ataque,juego->isengard[i].vida,i,i+1);
    }
}
void actualizar(juego_t* juego){
    for(int i = 0; i < juego->cantidad_rohan; i++)
    {
        juego->terreno[juego->rohan[i].fila][juego->rohan[i].columna] = juego->rohan[i].codigo;
    
    }
   for(int i = 0; i < juego->cantidad_isengard; i++)
   {
        juego->terreno[juego->isengard[i].fila][juego->isengard[i].columna] = juego->isengard[i].codigo;
   }
}
bool llego_al_limite(int fila, int limite){
	return(fila > limite);
}
void eliminar_personaje(personaje_t victima[MAX_PERSONAJES], int pos_personaje, int*tope){

    for( int i=pos_personaje ; i< (*tope)-1; i++ ){
        victima[i] = victima[i+1];
    }
    (*tope)--;
}
void humano_ork_avanza(juego_t* juego,personaje_t personaje[MAX_PERSONAJES],int pos_personaje, int avanse,int limite,int tope){

    (personaje[pos_personaje].fila) += avanse;

	if(llego_al_limite(personaje[pos_personaje].fila,limite)){
                     
    	eliminar_personaje(personaje,pos_personaje,&tope);
        if (personaje[pos_personaje].codigo == HUMANO){
          	(juego->llegadas_rohan)++;
        } else{
        	(juego->llegadas_isengard)++;
        }
    }
    limpiar_terreno(juego);
    actualizar(juego);
}
void jugar(juego_t* juego,char tipo, int posicion_personaje){  
	//int posicion_personaje;
    if(tipo== ROHAN){        
    	if(juego->rohan[posicion_personaje].codigo == ELFO){
            ataque_elfos_urukhai(juego,tipo,posicion_personaje,&(juego->cantidad_isengard));
        }else{
        	if(puede_atacar(juego->rohan[posicion_personaje].fila,juego->rohan[posicion_personaje].columna,
        		juego->isengard[posicion_personaje].fila,juego->isengard[posicion_personaje].columna)){
				ataque_humano_orko(juego,tipo,posicion_personaje,&(juego->cantidad_isengard),juego->rohan[posicion_personaje],juego->isengard);
       		}else{
       			humano_ork_avanza(juego,juego->rohan,posicion_personaje,-1,9,juego->cantidad_rohan);
       		}
        }
    }else{
        if(juego->isengard[posicion_personaje].codigo ==URUK_HAI){
            ataque_elfos_urukhai(juego,tipo,posicion_personaje,&(juego->cantidad_rohan));
        }else{
        	if(puede_atacar(juego->isengard[posicion_personaje].fila,juego->isengard[posicion_personaje].columna,
        		juego->rohan[posicion_personaje].fila,juego->rohan[posicion_personaje].columna)){
				ataque_humano_orko(juego,tipo,posicion_personaje,&(juego->cantidad_rohan),juego->isengard[posicion_personaje],juego->rohan);
       		}else{
       			humano_ork_avanza(juego,juego->isengard,posicion_personaje,1,0,juego->cantidad_isengard);
       		}
       	}
    }
    limpiar_terreno(juego);
    actualizar(juego);
}
