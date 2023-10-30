#ifndef __BATALLA_H__
#define __BATALLA_H__
#define MAX_TERRENO_FIL 10
#define MAX_TERRENO_COL 10
#define MAX_PERSONAJES  50
int posicion_personaje;
typedef struct personaje {
	char codigo;
	int vida;
	int ataque;
	int fila;
	int columna;
	// Pueden agregar los campos que deseen
} personaje_t;

typedef struct juego {
	char terreno[MAX_TERRENO_FIL][MAX_TERRENO_COL];
	
	personaje_t rohan[MAX_PERSONAJES];
	int cantidad_rohan;
	int llegadas_rohan;
	int plus_rohan;
	
	char modo_de_juego;
	
	char bando_de_primer_jugador;
	char turno;
	personaje_t isengard[MAX_PERSONAJES];
	int cantidad_isengard;
	int llegadas_isengard;
	int plus_isengard;
	int energia_rohan;
	int energia_isengard;
	// Pueden agregar los campos que deseen
} juego_t;

/*
 * Inicializará todos los valores del juego, dejándolo en un estado 
 * inicial válido.
 */
void inicializar_juego(juego_t* juego);
void preguntar_usario(juego_t* juego, personaje_t* personaje);
void elegir_modo(juego_t* juego, char* modo_de_juego);
void terreno(juego_t* juego);
void un_jugador(juego_t* juego);
void dos_jugadores(juego_t* juego);
char jugador_decide_si_agregar_personaje();
void jugar_segun_turno(juego_t* juego, char contrincante);
/*
 * Recibirá un personaje, con todos sus campos correctamente cargados y
 * lo dará de alta en el juego, sumándolo al vector correspondiente,
 * posicionándolo también en la matriz.
 */
void posicionar_personaje(juego_t* juego, personaje_t personaje);

/*
 * Realizará la jugada del personaje del bando recibido que
 * se encuentra en la posición posicion_personaje.
 * Se moverá o atacará dependiento lo que corresponda.
 * Actualizará el juego según los efectos del movimiento del
 * personaje, matar rivales, actualizar la matriz, restar vida, etc.
 */
void jugar(juego_t* juego, char bando, int posicion_personaje);

#endif /* __BATALLA_H__ */