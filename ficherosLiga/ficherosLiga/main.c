//
//  main.c
//  ficherosLiga
//
//  Created by Ivan Zheng on 10/5/23.
//

#include <stdio.h>

struct datosEquipo {
    char nombre[30]; //nombre del equipo
    char estadio[30]; //estadio
    
};

struct datosJugador {
char nombre[40]; //nombre del jugador
char equipo[30]; //nombre del equipo en el que juega int dorsal;
int dorsal; //dorsal

};


// ** MIS FUNCIONES **
int menu(void);
void visualizarJugadores(char nombreFich[]);
void visualizarEquipos(char nombreFich[]);
void modificarEstadio(char nombreFichero[]);

int main(int argc, const char * argv[]) {
    int opcion;
    do{
    opcion = menu();
    switch(opcion){
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
        visualizarEquipos("equipos.bin");
            break;
        case 5:
        visualizarJugadores("jugadores.bin");
            break;
        case 0:
            printf("Fin del programa... \n");
            break;
    }
    }while(opcion != 0);
    return 0;
}

// ** MIS FUNCIONES **
int menu(void){
int opcion;
do{
    printf("\n*********** MENU ********** \n");
    printf("\t 1. Modificar el estadio de un equipo \n");
    printf("\t 2. Generar un fichero de texto con la informacion de los equipos y sus jugadores \n");
    printf("\t 3. Anadir un jugador a un equipo \n");
    printf("\t 4. Visualizar equipos \n");
    printf("\t 5. Visualizar jugadores \n");
    printf("\t 0. SALIR \n");
    printf("\nEscoja una opcion: ");
    scanf("%d", &opcion);
    printf("\n");
}while((opcion < 0) || (opcion > 5));
return opcion;
}


void visualizarJugadores(char nombreFich[]){
    FILE *fichero;
    struct datosJugador jug;
    
    //1.- Inicializar el fichero
    fichero = fopen(nombreFich, "rb");  //rb = read binary
    
    if(fichero == NULL){
        printf("\n ** ERROR DE APERTURA **");
        return;
    }
    
    //2.- Leo el fichero
    fread(&jug, sizeof(struct datosJugador), 1, fichero);
    while (!feof(fichero)) {
        printf("Equipo: %s || Nombre: %s || Dorsal: %d \n", jug.equipo, jug.nombre, jug.dorsal);
        fread(&jug, sizeof(struct datosJugador), 1, fichero);
    }
    //3.- Cierro el fichero
    fclose(fichero);
}

void visualizarEquipos(char nombreFich[]){
    FILE *fichero;
    struct datosEquipo equip;
    
    //1.- Inicializar el fichero
    fichero = fopen(nombreFich, "rb");  //rb = read binary
    
    if(fichero == NULL){
        printf("\n ** ERROR DE APERTURA **");
        return;
    }
    
    //2.- Leo el fichero
    fread(&equip, sizeof(struct datosEquipo), 1, fichero);
    while (!feof(fichero)) {
        printf("Nombre: %s || Estadio: %s \n", equip.nombre, equip.estadio);
        fread(&equip, sizeof(struct datosEquipo), 1, fichero);
    }
    
    //3.- Cierro el fichero
    fclose(fichero);
}


void modificarEstadio(char nombreFichero[]){
    FILE *fichero;
    struct datosEquipo equipoCambio;
    char equipoCambiar[20];
    
    printf("\n Introduce el nombre del equipo que quieres cambiar: ");
    fpurge(stdin);
    scanf("%s",equipoCambio.nombre);
    
    //1.- Abro el fichero
    fichero=fopen(nombreFichero, "r+b");
    if(fichero==NULL ){
        printf("\n ERROR DE APERTURA ");
        return;
    }
    //2.- Busco en el fichero
    fseek(fichero,sizeof(struct datosEquipo), SEEK_SET);
    fread(&equipoCambio, <#size_t __size#>, <#size_t __nitems#>, <#FILE *restrict __stream#>)
    
}
