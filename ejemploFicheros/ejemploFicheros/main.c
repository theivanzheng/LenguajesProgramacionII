//
//  main.c
//  ejemploFicheros
//
//  Created by Ivan Zheng on 24/4/23.
//

#include <stdio.h>

struct datosAsignatura{
    char codigo[8];
    char nombre[20];
    char titulacion[20];
    int curso;
};

void generarFichero( char nombre[]);
void introdcirInformacion(struct datosAsignatura *asignatura);
void visualizarInformacionFichero(char nombre[]);
void mostrarInformacion( struct datosAsignatura asignatura);

int main(int argc, const char * argv[]) {
    char nombreFichero[20];
    
    printf("\n Introduce el nombre del fichero: "); fpurge(stdin);
    scanf("%s",nombreFichero);
    
   // generarFichero(nombreFichero);
    visualizarInformacionFichero(nombreFichero);
    printf("\n ");
    return 0;
}


void generarFichero( char nombre[]){
    struct datosAsignatura reg;
    int numAsignaturas, i;
    FILE *f;
    f= fopen(nombre, "wb");
    
    printf("\n Cuantas asignaturas quieres: ");
    scanf("%d",&numAsignaturas);
    
    for (i=0; i<numAsignaturas; i++) {
        printf("\n Rellenando para la Asignatura %d",i);
        //relleno la información
        introdcirInformacion(&reg);
        //escribo
        fwrite(&reg, sizeof(struct datosAsignatura), 1, f); //siempre se escirbe de uno en uno
    }
    
    fclose(f);
}

void introdcirInformacion(struct datosAsignatura *asignatura){
    printf("\n\t introduce el código: "); fpurge(stdin);
        scanf("%s",asignatura->codigo);
    printf("\n\t introduce el nombre: "); fpurge(stdin);
        scanf("%s",asignatura->nombre);
    printf("\n\t introduce la titulacion : "); fpurge(stdin);
        scanf("%s",asignatura->titulacion);
    printf("\n\t introduce el curso: ");
        scanf("%d",&asignatura->curso);

}

void visualizarInformacionFichero(char nombre[]){
    struct datosAsignatura reg;
    FILE *f;
    
    f= fopen(nombre,"rb");
    if(f ==NULL){
        printf("\n *** ERROR DE APERTURA ***");
        return;
    }
    
    fread(&reg, sizeof(struct datosAsignatura), 1, f);
        // si el fichero está vacío lo lee igualmente y dice que estás al final
    while (!feof(f)) {
        //hago el tratamiento con reg
        mostrarInformacion(reg);
        //leo el siguiente
        fread(&reg, sizeof(struct datosAsignatura), 1, f);
    }
    fclose(f);
}

void mostrarInformacion( struct datosAsignatura asignatura){
    printf("\n Código: %s, Nombre: %s, Titulacion: %s, Curso %d. ",asignatura.codigo, asignatura.nombre,asignatura.titulacion, asignatura.curso);
}
