//
//  main.c
//  ficheros_Biblioteca
//
//  Created by Ivan Zheng on 27/4/23.
//

#include <stdio.h>
#include <stdlib.h>

struct datosLibro{
    char titulo[50];
    char autor[50];
    char editorial[15];
    int anno;
    int disponible;
    int veces;
};

//  *** MIS FUNCIONES ****
void generarFichero( char nombre[]);
void introducirInformacion( struct datosLibro *libro);
void visualizarInformacionFichero(char nombre[]);
void mostrarInformacion( struct datosLibro libro);

int main(int argc, const char * argv[]) {
    // insert code here...
    char nombreFichero[20];
    
    printf("\n Introduce el nombre del fichero: "); fpurge(stdin);
    scanf("%s",nombreFichero);
    
    // generarFichero(nombreFichero);

    return 0;
}

//  *** MIS FUNCIONES ****
void generarFichero( char nombre[]){
    struct datosLibro libro;
    int numLibros, i;
    FILE *biblioteca;
    
    biblioteca= fopen(nombre, "wb");
    
    printf("\n Cuantos ficheros libros quieres: ");
    scanf("%d",&numLibros);
    
    for (i=0; i<numLibros; i++) {
        printf("\n Relleno para el libro %d -> ",i);
        //relleno la información
        introducirInformacion(&libro);
        fwrite(&libro, sizeof(struct datosLibro), 1, biblioteca);
    }
    fclose(biblioteca);
}

void introducirInformacion( struct datosLibro *libro){
    printf("\n\t Introudce el titulo del libro: "); fpurge(stdin);
    scanf("%s",libro->titulo);
    printf("\n\t Introudce el autor del libro: ");  fpurge(stdin);
    scanf("%s",libro->autor);
    printf("\n\t Introudce la editorial del libro: ");  fpurge(stdin);
    scanf("%s",libro->editorial);
    printf("\n\t Introudce el annio del libro: ");
    scanf("%d",&libro->anno);
    printf("\n\t Introudce si el libro está libre (1.-si|| 0.- no): ");
    scanf("%d",&libro->disponible);
    printf("\n\t Introudce las veces que se ha utilizado el libro: ");
    scanf("%d",&libro->veces);
}

void visualizarInformacionFichero(char nombre[]){
    struct datosLibro libro;
    FILE *f;
    f=fopen(nombre, "rb");
    
    if(f ==NULL){
        printf("\n *** ERROR DE APERTURA ***");
        return;
    }
    //lo lee
    fread(&libro,sizeof(struct datosLibro),1,f);
        // si el fichero está vacío lo lee igualmente y dice que estás al final

    //recorre
    while (!feof(f)) {
        
    }
}

void mostrarInformacion( struct datosLibro libro){
    printf("Título: %s, Autor: %s, Editorial: %s, Anio: %d, Disponible: %d, Veces: %d", libro.titulo, libro.autor, libro.editorial,libro.anno, libro.disponible, libro.veces);
}
