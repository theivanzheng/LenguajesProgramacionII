//
//  main.c
//  ejercicio1FicherosBinarios
//
//  Created by Administrador on 27/04/2023.
//  Copyright © 2023 Administrador. All rights reserved.
//


#include<stdio.h>
#include<string.h>



#define TRUE 1
#define FALSE 0


struct datosLibro
{
    char titulo[50];
    char autor[50];
    char editorial[15];
    int anno;
    int disponible;
    int veces;
};


int menu(void);
int buscarLibro(char nf[], char titulo[],struct datosLibro *libro,int *posicion);
//busca un libro con ese titulo, devuelve en el return información que le dice si lo ha encontrado o no
//si lo encuentra devuelve en libro la información del libro buscado y en posición su posición en bytes en el fichero


void datosLibro(char nf[]); //apartado 1. Visualiza la información de un libro
void añadirLibro(char nf[]); //apartado 2. Añade al fichero
void prestamo(char nf[]);    //apartado 3. Devuelve o saca un libro. Modifica el fichero

struct datosLibro introducirInfoLibro(void); //rellena la información del libro


void leerFicheroBinario(char nf[]); //visualiza el fichero.



int main(int argc, const char * argv[])
{
    
    int opc;
    
    
    do
    {
        opc = menu();
        switch (opc)
        {
            case 1: datosLibro("libros");
                break;
            case 2: añadirLibro("libros");
                break;
            case 3: prestamo("libros");
                break;
            case 4: leerFicheroBinario("libros");
                
        }
    }while(opc != 0);
    
    return 0;
}




int menu()
{
    int opc;
    do
    {
        printf("\n1. Datos de un libro");
        printf("\n2. Añadir un libro al fichero de la biblioteca");
        printf("\n3. Entrada/salida de un libro");
        printf("\n4. Visualizar fichero");
        printf("\n0. Salir");
        
        printf("\n\nIntroduce una opción: ");
        scanf("%d",&opc);
    }while ((opc<0) || (opc>4));
    return opc;
}

int buscarLibro(char nf[],char titulo[],struct datosLibro *libro,int *posicion)
{
    FILE *f;
    
    f = fopen(nf,"rb");
    if (f == NULL){
        printf("\n ERROR de apertura");
        return -1;
    }
    
    
    fread(libro,sizeof(struct datosLibro),1,f);
    while ((!feof(f)) && (strcmp(libro->titulo,titulo)!=0) ){
        fread(libro,sizeof(struct datosLibro),1,f);
    }
    
    *posicion = (int) ftell(f) - (sizeof(struct datosLibro));
    //necesito restar el tamaño de un libro porque una vez que lo ha encontrado el marcador del fichero ha avanzado también
    

    
    if (feof(f)){
        fclose(f);
        return FALSE;
    }
    else{
        fclose(f);
        return TRUE;
    }
    
}

void datosLibro(char nf[])
{
    int pos;
    struct datosLibro libro;
    char titulo[50];
    
    printf("\n Introduce el título del libro: "); fpurge(stdin);
    scanf("%[^\n]",titulo);
    
    if (buscarLibro(nf,titulo,&libro,&pos)==TRUE){
        printf("\n Autor %s, Editorial %s, Año %d",libro.autor,libro.editorial,libro.anno);
    }
    else {
        printf("\n El titulo introducido no está en la biblioteca");
    }
}


void prestamo(char nf[])
{
    int pos;
    struct datosLibro libro;
    FILE *f;
    char titulo[50];
    
    printf("\n Introduce el título del libro: "); fpurge(stdin);
    scanf("%[^\n]",titulo);
    
    if (buscarLibro(nf,titulo,&libro,&pos)==TRUE)
    {
        if (libro.disponible){ //si está disponible lo presto y pt incremento el número de veces que se ha prestado
            libro.veces++;
        }
        libro.disponible = !libro.disponible; //cambio su estado
        
        //lo escribo modificado
        f = fopen(nf,"r+b"); //lo abro en lectura escritura para que me permita posicionarme y modificarlo
        if (f == NULL){
            printf("\n ERROR de apertura");
            return;
        }
        fseek(f,pos,SEEK_SET);
        fwrite(&libro,sizeof(struct datosLibro),1,f);
        fclose(f);
        
    }
    else
        printf("\n El titulo no está en la biblioteca");
}

void añadirLibro(char nf[]){
    FILE *f;
    
    int pos;
    struct datosLibro libro,libroBuscado;
    
    libro = introducirInfoLibro();
    
    if (buscarLibro(nf,libro.titulo,&libroBuscado,&pos)==TRUE){
        printf("\n Ya existe en la biblioteca un libro con ese titulo");
    }
    else {
        //se añade al fichero
        f = fopen(nf,"ab");
        fwrite(&libro,sizeof(struct datosLibro),1,f);
        fclose(f);
    }
    
}

struct datosLibro introducirInfoLibro(){
    struct datosLibro libro;
    
    printf("\n Introduce el titulo: ");
    fpurge(stdin);
    scanf("%[^\n]",libro.titulo);
    
    printf("\n Introduce el autor: ");
    fpurge(stdin);
    scanf("%[^\n]",libro.autor);
    
    printf("\n Introduce la editorial: ");
    fpurge(stdin);
    scanf("%[^\n]",libro.editorial);
    
    printf("\n Introduce el año: ");
    fflush(stdin);
    scanf("%d",&libro.anno);
    libro.disponible = 1;
    libro.veces = 0;
    
    return libro;
}


void leerFicheroBinario(char nf[])
{
    struct datosLibro reg;
    FILE *f;
    
    f = fopen(nf,"rb");
    if (f == NULL){
        printf("\n ERROR de apertura");
        return;
    }
    
    
    fread(&reg, sizeof(struct datosLibro), 1, f);
    while (!feof(f))
    {
        printf("\n Autor: %s, Titulo: %s, Disponible: %s Veces: %d",reg.autor,reg.titulo,reg.disponible?"SI":"NO",reg.veces);
        fread(&reg, sizeof(struct datosLibro), 1, f);
    }
}




