//
//  main.c
//  ex_AbrilFIcheros21_A
//
//  Created by Ivan Zheng on 18/5/23.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct datosRegistro{
    char persona[30]; //identificador de la persona
    char aula[30]; //nombre del aula
    int hora; //valor entre 8 y 21 que registra la hora en la que estuvo
    char tarea[50]; //tarea que realiza en el aula
};



//  ** MIS FUNCIONES ***
void addRegistro(char nombreFichero[]);
void mostrarContactos(char nombreFichero[]);
void cambiarTarea(char nombreFichero[]);

//  ** MIS FUNCIONES SECUENDARIAS ***
int menu(void);
void visualizarFichero(char nombreFichero[]);
int buscarRegistro(char nombreFichero[], struct datosRegistro datos);
void printError(void);
void volcar(char nombreFichero[], char nombreAux[]);


int main() {
    int opcion;

    do {
        opcion = menu();

        switch (opcion) {
            case 0:
                printf("\n Visualizar fichero");
                visualizarFichero("registroAulas.bin");
                break;
            case 1:
                printf("Añadir un registro.\n");
                addRegistro("registroAulas.bin");
                // Lógica para la opción 1
                break;
            case 2:
                printf("Localizar contactos.\n");
                mostrarContactos("registroAulas.bin");
                // Lógica para la opción 2
                break;
            case 3:
                printf("Cambiar tarea realizada.\n");
                cambiarTarea("registroAulas.bin");
                // Lógica para la opción 3
                break;
            case 4:
                printf("Comprobar aforo de un aula.\n");
                // Lógica para la opción 4
                break;
            case 5:
                printf("Salir.\n");
                // Lógica para la opción 5
                break;
            default:
                printf("Opción inválida.\n");
                break;
        }

        printf("\n");
    } while (opcion != 5);

    return 0;
}


//  ** MIS FUNCIONES SECUENDARIAS ***
int menu(void) {
    int opc;

    do {
        printf("\n *** Menu ***\n");
        printf("\t 1. Añadir un registro.\n");
        printf("\t 2. Localizar contactos.\n");
        printf("\t 3. Cambiar tarea realizada.\n");
        printf("\t 4. Comprobar aforo de un aula.\n");
        printf("\t 5. Salir.\n");
        printf("Introduce una opción: ");
        scanf("%d", &opc);
        printf("\n");
    } while (opc < 0 || opc > 5);

    return opc;
}

void visualizarFichero(char nombreFichero[]){
    //0.- Creo mis ficheros
    FILE *f;
    struct datosRegistro reg;
    
    //1.- Inicializo
    f=fopen(nombreFichero, "rb");
    if(f==NULL){
        printf("\n ** ERROR DE APERTURA **");
        return;
    }
    //2.- Leo mi archivo
    fread(&reg, sizeof(struct datosRegistro), 1, f);
    while (!feof(f)) {
        printf("\n Per: %s  Aula: %s Hora: %d Tarea: %s", reg.persona, reg.aula, reg.hora, reg.tarea);
        fread(&reg, sizeof(struct datosRegistro), 1, f);

    }
    //3.- Cierro mi archivo
    printf("\n \n");
    fclose(f);
}
void printError(void){
    printf("\n ** ERROR DE APERTURA **");

}

void addRegistro(char nombreFichero[]){
    //0.- Creo mi fichero y mis structs
    FILE *f, *faux;
    struct datosRegistro reg, rellenado;

    
    
    //1.- Pido información al usuario
    printf("\n Introduce el id del ususario: "); fpurge(stdin);
    scanf("%s",rellenado.persona);
    printf("\n Introduce el aula: "); fpurge(stdin);
    scanf("%s",rellenado.aula);
    printf("\n Introduce la hora: ");
    scanf("%d",&rellenado.hora);
    strcpy(rellenado.tarea, "FPII teoria");
    
    //2.- Inicializo
    f=fopen(nombreFichero, "rb");
    faux=fopen("auxiliar", "wb");

    if(f==NULL){
        printError();
        return;
    }
    
    //3- Busco en mi lista
    fread(&reg, sizeof(struct datosRegistro), 1, f);
    while (!feof(f) && (reg.hora<=rellenado.hora)) {
        if(reg.hora==rellenado.hora){
            if( (strcmp(reg.persona, rellenado.persona) == 0 )   &&
               (strcmp(reg.aula, rellenado.aula) == 0 )){
                printf("\n Ese registro ya existe");
                
                fclose(f);
                fclose(faux);
                remove("auxiliar");
                return;
            }
        }
        fwrite(&reg, sizeof(struct datosRegistro), 1, faux);
        fread(&reg, sizeof(struct datosRegistro), 1, f);
    }
    
    //4.- Ya he salido no lo ha encontrado, entonces lo escribo
    fwrite(&rellenado, sizeof(struct datosRegistro), 1, faux);

    //5.- Creo un bucle para escribir todo lo que me queda
    while (!feof(f)) {
        fwrite(&reg, sizeof(struct datosRegistro), 1, faux);
        fread(&reg, sizeof(struct datosRegistro), 1, f);
    }
    
    //6.- Vuelco y cierro
    fclose(f);
    fclose(faux);
    volcar(nombreFichero, "auxiliar");
    printf("\n El registro se ha añadido con éxito");


}

void volcar(char nombreFichero[], char nombreAux[]){
    //1.- Creo mis archivos
    FILE *f, *faux;
    struct datosRegistro reg;
    
    //2.- Inicializo
    f=fopen(nombreFichero, "wb");
    faux=fopen(nombreAux, "rb");
    
    if(f==NULL || faux==NULL){
        printError();
        return;
    }
    //3- Busco en mi lista
    printf("\n Muestro mi lista original");
    fread(&reg, sizeof(struct datosRegistro), 1, faux);
    while (!feof(faux)) {
        fwrite(&reg, sizeof(struct datosRegistro), 1, f);
        fread(&reg, sizeof(struct datosRegistro), 1, faux);
    }
    //4.-Cierro y borro
    fclose(faux);
    fclose(f);
    remove("auxiliar");

}

void mostrarContactos(char nombreFichero[]){
    //0.- Creo mi fichero y mis structs
    FILE *f;
    struct datosRegistro reg, rellenado;
    int mensaje=0;
    int buscado;

    
    
    //1.- Pido información al usuario
    printf("\n Introduce el id del ususario: "); fpurge(stdin);
    scanf("%s",rellenado.persona);
    printf("\n Introduce el aula: "); fpurge(stdin);
    scanf("%s",rellenado.aula);
    printf("\n Introduce la hora: ");
    scanf("%d",&rellenado.hora);
    strcpy(rellenado.tarea, "FPII teoria");
    
    //2.- Inicializo
    f=fopen(nombreFichero, "rb");

    if(f==NULL){
        printError();
        return;
    }
   buscado= buscarRegistro(nombreFichero, rellenado);
    
    if(buscado == 0){
        printf("\n El usuario no se ha encontrado");
        fclose(f);
        return;
    }else if(buscado<0){
        printf("\n El archivo no se pudo abrir");
    }else{
        
        
        
        //3.- Leo entre mi archivo
        fread(&reg, sizeof(struct datosRegistro), 1, f);
        printf("\n *** CONTACTOS ***");
        while (!feof(f)) {
            if(reg.hora==rellenado.hora && (strcmp(reg.aula, rellenado.aula) == 0 )){
                printf("\n Per: %s  Aula: %s Hora: %d Tarea: %s", reg.persona, reg.aula, reg.hora, reg.tarea);
                mensaje++;
            }
            fread(&reg, sizeof(struct datosRegistro), 1, f);
        }
        
        if(mensaje==0){
            printf("\n No hay contactos que hayan tenido el mismo aula y hora");
        }
        fclose(f);
    }
}

int buscarRegistro(char nombreFichero[], struct datosRegistro datos){
    //0.- Creo mi fichero y mis structs
    FILE *f;
    struct datosRegistro reg;
    
    //2.- Inicializo
    f=fopen(nombreFichero, "rb");

    if(f==NULL){
        printError();
        return -1;
    }
    
    //3- Busco en mi lista
    fread(&reg, sizeof(struct datosRegistro), 1, f);
    while (!feof(f)) {
        if(reg.hora==datos.hora){
            if( (strcmp(reg.persona, datos.persona) == 0 )   &&
               (strcmp(reg.aula, datos.aula) == 0 )){
                printf("\n Ese registro existe");
                
                fclose(f);
                return 1;
            }
        }
        fread(&reg, sizeof(struct datosRegistro), 1, f);

    }
    

    fclose(f);
    printf("\n No existe este registro");
    return 0;
}

void cambiarTarea(char nombreFichero[]){
    //0.- Creo mi fichero y mis structs
    FILE *f, *faux;
    struct datosRegistro reg, rellenado, newRellenado;
    int buscado;

    
    
    //1.- Pido información al usuario
    printf("\n Introduce el id del ususario: "); fpurge(stdin);
    scanf("%s",rellenado.persona);
    printf("\n Introduce el aula: "); fpurge(stdin);
    scanf("%s",rellenado.aula);
    printf("\n Introduce la hora: ");
    scanf("%d",&rellenado.hora);
    
    //2.- Inicializo
    f=fopen(nombreFichero, "rb");
    faux=fopen("auxiliar", "wb");

    if(f==NULL){
        printError();
        return;
    }
   buscado= buscarRegistro(nombreFichero, rellenado);
    
    if(buscado == 0){
        printf("\n El usuario no se ha encontrado");
        fclose(f);
        return;
    }else if(buscado<0){
        printf("\n El archivo no se pudo abrir");
    }else{
        //Relleno mi nuevo struct
        printf("\n Introduce la nueva tarea: "); fpurge(stdin);
        scanf("%s",newRellenado.tarea);
        strcpy(newRellenado.persona, rellenado.persona);
        strcpy(newRellenado.aula, rellenado.aula);
        newRellenado.hora=rellenado.hora;
        
        fread(&reg, sizeof(struct datosRegistro), 1, f);
        //busco la posición
        while (!feof(f)){
            if((strcmp(reg.persona, rellenado.persona) != 0 )   &&
            (strcmp(reg.aula, rellenado.aula) != 0 )         &&
            (reg.hora!= rellenado.hora)) {
         //escribo hasta encontrarlo
         fwrite(&reg, sizeof(struct datosRegistro), 1, faux);
         fread(&reg, sizeof(struct datosRegistro), 1, f);

            }else{
                fread(&reg, sizeof(struct datosRegistro), 1, f);

            }
        }
                   
               
        //ahora ya sale del bucle y lo ha encontrado, me lo salto y escribo el 
        fwrite(&newRellenado, sizeof(struct datosRegistro), 1, faux);

        //vuelvo a escribir
        while (!feof(f)) {
            fwrite(&reg, sizeof(struct datosRegistro), 1, faux);
            fread(&reg, sizeof(struct datosRegistro), 1, f);
            }
        }
    //Vuelco y cierro
    fclose(f);
    fclose(faux);
    volcar(nombreFichero, "auxiliar");
    printf("\n El cambio se ha añadido con éxito");

}
