//
//  main.c
//  practica5FicherosBinarios
//
//  Created by Administrador on 09/05/2023.
//  Copyright © 2023 Administrador. All rights reserved.
//


#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0

struct datosAlumno
{
    int nExp; //número de expediente del alumno
    char nombre[50]; //nombre del alumno
    char apellidos[100]; //apellidos de alumno
};

struct datosAsignatura
{
    int codigo; //código de la asignatura
    char nombreAsig[40]; //nombre de la asignatura
    int curso; //curso en que se imparte
};
struct datosMatriculado
{
    int nExp; //número de expediente del alumno matriculado
    int codigo; //código de la asignatura
    
};

//  ** MIS FUNCIONES **
int menu(void);
void visualizarAlumnos(char nombre[]);
void visualizarAsignaturas(char nombre[]);
void visualizarMatriculados(char nombre[]);
void viewAlumnoConcreto(char nombre[]);
void viewAsignaturaConcreta(char nombre[]);
void addAlumno(char nombre[]);
void generarFicheroTexto (char nombreFAlumnos[], char nombreFasignaturas[], char nombreFmatriculados[]);
void eliminarALumno(char nombreFicheroAlumno[], char nombreFicheroMatriculados[]);
void matricularAlumno (char nombreFAlumnos[], char nombreFasignaturas[], char nombreFmatriculados[]);
void addMatricula(char nombre[],struct datosMatriculado alumnoMatricular);

//  ** MIS FUNCIONES SECUNDARIAS  **
int buscarAlumno(char nombre[], int expedienteBuscar, struct datosAlumno *alumno);
int buscarAsignatura(char nombre[], int codAsignatura, struct datosAsignatura *asignatura);
void rellenarInfoAlumno(struct datosAlumno *alum);
void volcar(char auxiliar[], char nombre[]);
void eliminarMatriculas(char nombreFmatriculados[], int nExpediente);
void volcarMatriculados(char auxiliar[], char nombre[]);


// ** MI Main**
int main(){
    
    int opc=0;
    do{
        opc=menu();
        switch (opc) {
            case 1:
                printf("\n 1. Visualizar fichero alumnos");
                visualizarAlumnos("alumnos.bin");
                break;
            case 2:
                printf("\n 2. Visualizar fichero asignaturas");
                visualizarAsignaturas("asignaturas.bin");
                break;
            case 3:
                printf("\n 3. Visualizar fichero matriculados");
                visualizarMatriculados("matriculados.bin");
                break;
            case 4:
                printf("\n 4. Visualizar un alumno concreto");
                viewAlumnoConcreto("alumnos.bin");
                break;
            case 5:
                printf("\n 5. Visualizar asignatura concreta");
                viewAsignaturaConcreta("asignaturas.bin");
                break;
            case 6:
                printf("\n 6. Añadir un alumno");
                addAlumno("alumnos.bin");
                break;
            case 7:
                printf("\n 7. Crear un fichero de texto");
                generarFicheroTexto("alumnos.bin", "asignaturas.bin", "matriculados.bin");
                break;
            case 8:
                printf("\n 8. Eliminar a un alumno");
                eliminarALumno("alumnos.bin", "matriculados.bin");
                break;
            case 9:
                printf("\n 9. Matricualar a un alumno en una asignatura");
                matricularAlumno("alumnos.bin", "asignaturas.bin", "matriculados.bin");
                break;
            default:
                break;
        }
    }while (opc!=0);

}


//  ** MIS FUNCIONES **
int menu(void){
    int opc;
    do{
        printf("\n\n *** MENU ***");
        printf("\n 1. Visualizar fichero alumnos");
        printf("\n 2. Visualizar fichero asignaturas");
        printf("\n 3. Visualizar fichero matriculados");
        printf("\n");
        printf("\n 4. Visualizar información de un alumno");
        printf("\n 5. Visualizar información de una asignatura");
        printf("\n 6. Añadir un alumno");
        printf("\n 7. Fichero texto con asignaturas de un alumno");
        printf("\n 8. Eliminar a un alumno");
        printf("\n 9. Matricualar a un alumno en una asignatura");
        printf("\n 0. SALIR");
        printf("\nIntroduce una opcion: ");
        scanf("%d",&opc);
    }while(opc<0 || opc>9);

    return opc;
}

void visualizarAlumnos(char nombre[]){
    //0- Creo un fichero
    FILE *f;
    struct datosAlumno alumno;
    
    //1.- Abro el fichero
    f=fopen(nombre, "rb");
    
    if(f==NULL){
        printf("\n ERROR DE APERTURA ");
    
    //2.- Leo el archivo y abro el bucle
    }else{
        fread(&alumno, sizeof(struct datosAlumno), 1, f); //pongo mi dedo en el primero de la lista
        while (!feof(f)) {
            printf("\n\t Exp: %d\t Nombre: %s %s",alumno.nExp, alumno.nombre, alumno.apellidos);
            fread(&alumno, sizeof(struct datosAlumno), 1, f); //leo el siguiente
        }
    //3.- Cierro mi archivo
        printf("\n\n");
        fclose(f);
    }
  
}

void visualizarAsignaturas(char nombre[]){
    //0.- Creo un fichero
    FILE *f;
    struct datosAsignatura asig;
    
    //1.- Abro mi fichero
    f=fopen(nombre, "rb");
    if(f==NULL){
        printf("\n ** ERROR DE APERTURA ** ");
        
    //2.- Leo mi fichero y paso al siguiente
    }else{
        fread(&asig, sizeof(struct datosAsignatura), 1, f);
        while (!feof(f)) {
            printf("\nCodigo: %d\t NombreAsignatura: %s\t Curso: %d", asig.codigo, asig.nombreAsig, asig.curso);
            fread(&asig, sizeof(struct datosAsignatura), 1, f);   //Paso al siguiente
        }
    //3.- Cierro mi documento
        printf("\n\n");
        fclose(f);
    }
}

void visualizarMatriculados(char nombre[]){
    //0.- Creo mi fichero
    struct datosMatriculado matriculado;
    FILE *f;
    
    //1.- Abro mi fichero
    f= fopen(nombre, "rb");
    if(f==NULL){
        printf("\n ** ERROR DE APERTURA **");
        
    //2.- Leo mi archivo y paso al siguiente
    }else{
        fread(&matriculado, sizeof(struct datosMatriculado), 1, f);
        while (!feof(f)) {
            printf("\nExp: %d\t CodigoAsignatura: %d", matriculado.nExp, matriculado.codigo);
            //paso al siguiente
            fread(&matriculado, sizeof(struct datosMatriculado), 1, f);
        }
    //3.- Cierro mi archivo
        printf("\n\n");
        fclose(f);
    }
}

void viewAlumnoConcreto(char nombre[]){
    //0.- Creo mi archivo
    struct datosAlumno alumnoBuscar;
    int expediente;
    int buscar;
    FILE *f;
    
    //1.- Abro mi archivo
    f=fopen(nombre, "rb");
    if(f==NULL){
        printf("\n ** ERROR DE APERTURA **");
    
    //2.- Leo mi archivo
    }else{
        printf("\n\t Introduce el expediente del alumno: "); fpurge(stdin);
        scanf("%d", &expediente);
        buscar=buscarAlumno(nombre, expediente, &alumnoBuscar);
        if(buscar==-1){
            printf("\n ERROR DE APERTURA");
        }else if(buscar==0){
            printf("\n No se ha encontrado el alumno");
        }else{
            printf("\n Se ha mostrado la información del alumno");

        }
    }
}

int buscarAlumno(char nombre[], int expedienteBuscar, struct datosAlumno *alumno){
    //0.- Creo mi fichero
    FILE *f;
    
    //1.- Abro mi fichero
    f=fopen(nombre, "rb");
    if(f==NULL){
        printf("\n  **  ERROR DE APERTURA **");
        return -1;
    }
    //2.- Leo mi fichero
    fread(alumno, sizeof(struct datosAlumno), 1, f);
    while (!feof(f) && (alumno->nExp < expedienteBuscar)) {   //creo la condición
        fread(alumno, sizeof(struct datosAlumno), 1, f);    //paso al siguiente
    }
        
    //2.1 Las condiciones en el que se para mi bucle
    if(!feof(f) && (alumno->nExp == expedienteBuscar)){ //Lo ha encontrado
        printf("\n\t Exp: %d\t Nombre: %s %s",alumno->nExp, alumno->nombre, alumno->apellidos);
        fclose(f);
        return 1;
    }else{                                              //NO lo encuentra
        fclose(f);
        return 0;
    }
}

void viewAsignaturaConcreta(char nombre[]){
    //0.- Creo mi fichero
    FILE *f;
    int codAsginaturaBuscar;
    int buscado;
    struct datosAsignatura asignatura;
    
    //1.- Inicializo mi fichero
    f=fopen(nombre, "rb");
    if(f==NULL){
        printf("\n ** ERROR DE APERTURA **");
    
    //2.- Leo mi fichero
    }else{
        printf("\n \tIntroduce el código de asignatura: ");
        scanf("%d",&codAsginaturaBuscar);
        buscado=buscarAsignatura(nombre, codAsginaturaBuscar, &asignatura);
       
     //3.- Miro las condiciones que hay
        if(buscado==-1){
            printf("\n ** ERROR DE APERTURA **");
        }else if(buscado ==0){
            printf("\n No se ha encontrado la asignatura");
        }
        
    }
}


int buscarAsignatura(char nombre[], int codAsignatura, struct datosAsignatura *asignatura){
    //0.- Creo mi fichero
    FILE *f;
    
    //1.- Inicializo mi fichero
    f=fopen(nombre, "rb");
    
    if(f==NULL){
        printf("\n ** ERROR DE APERTURA **");
        return -1;
        
    //2.- Leo mi archivo
    }
    fread(asignatura, sizeof(struct datosAsignatura), 1, f);
    while (!feof(f) && (asignatura->codigo < codAsignatura) ) {         //establezco mi condicion
            fread(asignatura, sizeof(struct datosAsignatura), 1, f);       //paso al siguiente
        }
    //3.- Analizo mis resultados
    if(!feof(f) && (asignatura->codigo == codAsignatura)){
        printf("\nCodigo: %d\t NombreAsignatura: %s\t Curso: %d", asignatura->codigo, asignatura->nombreAsig,asignatura->curso);
        fclose(f);
        return 1;
    }else{
        
        fclose(f);
        return 0;
    }
    
}


void addAlumno(char nombre[]){
    //0.- Declaro mis structs y creo mi fichero
    struct datosAlumno alumno, registro;
    FILE *f, *faux;
    
    //1.- Pregunto al usuario y compruebo
    printf("\n Introduce el numero de expediente a añadir: ");
    scanf("%d", &alumno.nExp);
    
    if(buscarAlumno(nombre, alumno.nExp, &registro)==1){
        printf("\n EL alumno ya existe");
        return;
    }
    
    //2.- Abro mi archivo, el usuario no existe
    f=fopen(nombre, "rb");
    faux=fopen("basura", "wb");   //Creo un fichero auxiliar
    
    if(f==NULL || faux ==NULL){
        printf("\n ** ERROR DE MEMORIA **");
        return;
    }
    //3.- Relleno a mi alumno
    rellenarInfoAlumno(&alumno);
    
    //4.- Busco el sitio donde colocarle
    fread(&registro, sizeof(struct datosAlumno), 1, f);
    while (!feof(f) && registro.nExp<alumno.nExp) {
        fwrite(&registro, sizeof(struct datosAlumno), 1, faux); // por qué pasa por &
        fread(&registro, sizeof(struct datosAlumno), 1, f);
    }
    
    //5.- He encontrado els itio donde escribir
    fwrite(&alumno, sizeof(struct datosAlumno), 1, faux);
    
    while (!feof(f)) {
        fwrite(&registro, sizeof(struct datosAlumno), 1, faux); // por qué pasa por &
        fread(&registro, sizeof(struct datosAlumno), 1, f);
    }
    fclose(f);
    fclose(faux);
    volcar("basura",nombre);
    printf("\n El alumno se ha añadido con éxito");

}

void rellenarInfoAlumno(struct datosAlumno *alum){
    printf("\n*********** INFO ALUMNO ***********\n");
    
    printf("Nombre: ");     fpurge(stdin);
    scanf("%[^\n]", alum->nombre);
    printf("Apellidos: ");  fpurge(stdin);
    scanf("%[^\n]", alum->apellidos);
    
}
void volcarMatriculados(char auxiliar[], char nombre[]) {
    FILE *faux, *f;
    struct datosMatriculado matriculado;

    // Abre los archivos auxiliar y original
    faux = fopen(auxiliar, "rb");
    f = fopen(nombre, "wb");  // Abre el archivo en modo de añadir ("ab")

    if (faux == NULL || f == NULL) {
        printf("\n ** ERROR DE APERTURA **");
        return;
    }

    // Lee los registros del archivo auxiliar y los vuelca en el archivo original
    fread(&matriculado, sizeof(struct datosMatriculado), 1, faux);
    while (!feof(faux)) {
        fwrite(&matriculado, sizeof(struct datosMatriculado), 1, f);
        fread(&matriculado, sizeof(struct datosMatriculado), 1, faux);
    }

    // Cierra los archivos y elimina el archivo auxiliar
    fclose(faux);
    fclose(f);
    remove(auxiliar);  // Elimina el archivo auxiliar
}



void volcar(char auxiliar[], char nombre[]) {
    FILE *faux, *f;
    struct datosAlumno alumno;

    // Abre los archivos auxiliar y original
    faux = fopen(auxiliar, "rb");
    f = fopen(nombre, "wb");  // Abre el archivo en modo de añadir ("ab")

    if (faux == NULL || f == NULL) {
        printf("\n ** ERROR DE APERTURA **");
        return;
    }

    // Lee los registros del archivo auxiliar y los vuelca en el archivo original
    fread(&alumno, sizeof(struct datosAlumno), 1, faux);
    while (!feof(faux)) {
        fwrite(&alumno, sizeof(struct datosAlumno), 1, f);
        fread(&alumno, sizeof(struct datosAlumno), 1, faux);
    }

    // Cierra los archivos y elimina el archivo auxiliar
    fclose(faux);
    fclose(f);
    remove(auxiliar);  // Elimina el archivo auxiliar
}

void generarFicheroTexto (char nombreFAlumnos[], char nombreFasignaturas[], char nombreFmatriculados[]){
    
    //0.- Creo mi fichero y mis variables
    FILE *f, *fTexto;
    int expediente;
    struct datosMatriculado reg;
    struct datosAlumno alumno;
    struct datosAsignatura asignatura;
    
    //1.- Pido al usuario la información
    printf("\n Introduce el numero de expediente: ");
    scanf("%d",&expediente);
    
    //2.- Buscamos a nuestro alumno
    if(buscarAlumno(nombreFAlumnos, expediente, &alumno)==0){
        printf("\n El alumno no existe");
        return;
    }
    
    //El alumno existe
    //3-. Abro mi archivo
    f = fopen(nombreFmatriculados, "rb");
    fTexto = fopen("matriculasAlumno.txt", "w");
    if(f==NULL || fTexto ==NULL){
        printf("\n ERROR de apertura");
        return;
    }
    
    //4.- Escribo en mi fichero
    fprintf(fTexto, "Nombre: %s %s", alumno.nombre, alumno.apellidos);
    fread(&reg, sizeof(struct datosMatriculado), 1, f);
    
    while (!feof(f) && (reg.nExp < expediente)) {
        fread(&reg, sizeof(struct datosMatriculado), 1, f);
    }
    
    if(!feof(f) && (reg.nExp == expediente) ){
        fprintf(fTexto, "\n ** Asignaturas Matricualdas ** \n");
        //el alumno tiene asignaturas matriculadas
        while (!feof(f) && reg.nExp == expediente) {
            if(buscarAsignatura(nombreFasignaturas, reg.codigo, &asignatura) == 1){
                fprintf(fTexto,"\t%s Curso: %d",asignatura.nombreAsig,asignatura.curso);
            }
            fread(&reg, sizeof(struct datosMatriculado), 1, f);
        }
    }
    fclose(f);
    fclose(fTexto);
}

void eliminarALumno(char nombreFicheroAlumno[], char nombreFicheroMatriculados[]){
    //0.- Creo mi fichero
    FILE *falumno, *fauxAlumno;
    struct datosAlumno alumno;
    int nExpediente;
    
    //1.- Inicializo y pido info al usuario
    falumno=fopen(nombreFicheroAlumno, "rb");
    fauxAlumno=fopen("alumnosTemporal", "wb");
    
    printf("\n Introudce el expediente del alumno: ");
    scanf("%d", &nExpediente);
    
    if(fauxAlumno==NULL || falumno==NULL){
        printf("\n ** ERROR DE APERTURA **");
        return;
    }
    
    //2.- Leo mi archivo
    fread(&alumno, sizeof(struct datosAlumno), 1, falumno);
    while (!feof(falumno) && alumno.nExp <nExpediente) {
        fwrite(&alumno, sizeof(struct datosAlumno), 1, fauxAlumno);
        fread(&alumno, sizeof(struct datosAlumno), 1, falumno);
        //cuando encuentra uno igual se sale del bucle
    }
    
    if(!feof(falumno) && (alumno.nExp==nExpediente)){
        //el alumno está, pero no lo escribo
        fread(&alumno, sizeof(struct datosAlumno), 1, falumno);
        
        //Continuo escribiendo lo que haya en el fichero hasta el final habiéndome saltado el que quería buscar
        while (!feof(falumno)) {
            fwrite(&alumno, sizeof(struct datosAlumno), 1, fauxAlumno);
            fread(&alumno, sizeof(struct datosAlumno), 1, falumno);
            //cuando encuentra uno igual se sale del bucle
        }
        fclose(fauxAlumno);
        fclose(falumno);
        volcar("alumnosTemporal", nombreFicheroAlumno);
        eliminarMatriculas(nombreFicheroMatriculados, nExpediente);
        printf("\n El alumno se ha eliminado con éxito");
    }else{
        printf("\n Imposible borrar el alumno, no existe");
        fclose(fauxAlumno);
        fclose(falumno);
        remove("alumnosTemporal");
    }
}

void eliminarMatriculas(char nombreFmatriculados[], int nExpediente){
    //0.- Creo mis ficheros y mis estructuras
    FILE *fMatricula, *FMatriculaAux;
    struct datosMatriculado reg;
    
    //1.- Inicializo
    fMatricula = fopen(nombreFmatriculados, "rb");
    FMatriculaAux = fopen("matriculadosAux", "wb");
    
    if(fMatricula ==NULL || FMatriculaAux == NULL){
        printf("\n ** ERROR DE MEMORIA **");
        return;
    }
    
    //2.- Leo mi archivo
    fread(&reg, sizeof(struct datosMatriculado), 1, fMatricula);
    while (!feof(fMatricula) && (reg.nExp<nExpediente)) {
        fwrite(&reg, sizeof(struct datosMatriculado), 1, FMatriculaAux);
        fread(&reg, sizeof(struct datosMatriculado), 1, fMatricula);
    }
        //Aquí ya he llegado a mi matriculado
    if(!feof(fMatricula)&& (reg.nExp == nExpediente)){
        //tengo que eliminar todos sus expedientes
        while (!feof(fMatricula) && (reg.nExp == nExpediente)) {
            fread(&reg, sizeof(struct datosMatriculado), 1, fMatricula);
        }
        
        //Ya no tengo nada de este expediente y vuelvo a escribir lo que queda
        while (!feof(fMatricula)) {
            fwrite(&reg, sizeof(struct datosMatriculado), 1, FMatriculaAux);
            fread(&reg, sizeof(struct datosMatriculado), 1, fMatricula);
        }
        fclose(fMatricula);
        fclose(FMatriculaAux);
        volcarMatriculados("matriculadosAux", nombreFmatriculados);
    }else{
        printf("\n El alumno no tiene ninguna asignatura matriculada ");
        fclose(fMatricula);
        fclose(FMatriculaAux);
        
    }
    remove("matriculadosAux");
    
}

void matricularAlumno (char nombreFAlumnos[], char nombreFasignaturas[], char nombreFmatriculados[]){
    //0.- Creo mis ficheros y mis structuras
    FILE *fAlumnos;
    FILE *fAsignaturas;
    FILE *fMatriculados;
    
    struct datosAlumno regAlumno;
    struct datosMatriculado matriculado, regMatricualdo;
    struct datosAsignatura  regAsigntaura;
    
    int findAlumno;
    int findAsignatura;
    
    //1.- Inicializo mis ficheros
    fAlumnos = fopen(nombreFAlumnos, "rb");
    fAsignaturas = fopen(nombreFasignaturas, "rb");
    fMatriculados = fopen(nombreFmatriculados, "rb");
    
    if((fAlumnos == NULL) || (fAsignaturas == NULL) || (fMatriculados==NULL)){
        printf("\n ** ERROR DE MEMORIA, NO SE PUDO ACCEDER A LOS FICHEROS **");
        return;
    }
    
    //2.- Pregunto al usuario y compruebo
    printf("\n Introduce el numero de expediente a añadir: ");
    scanf("%d", &matriculado.nExp);
    
    findAlumno =buscarAlumno(nombreFAlumnos, matriculado.nExp, &regAlumno);
    
    if(findAlumno==1){
        //printf("\n EL alumno ya existe");
        printf("\n Introduce el codigo de asignatura que quieres matricular: ");
        scanf("%d", &matriculado.codigo);
        
        //busco la asignatura
        findAsignatura=buscarAsignatura(nombreFasignaturas, matriculado.codigo, &regAsigntaura);
        
        if(findAsignatura == 1){
            printf("\n Se ha encontrado la asignatura");
            
            //busco a mi alumno en las matriculas de las asignaturas
            fread(&regMatricualdo, sizeof(struct datosMatriculado), 1, fMatriculados);
            
            while (!feof(fMatriculados) && (regMatricualdo.nExp <= matriculado.nExp)){
                printf("\n Matriculado nExp: %d", matriculado.nExp);
                printf("\n Matriculado Codigo: %d", matriculado.codigo);
                printf("\n Reg nExp: %d", regMatricualdo.nExp);
                printf("\n Reg Codigo: %d", regMatricualdo.codigo);
                printf("\n");
                if(matriculado.nExp == regMatricualdo.nExp && matriculado.codigo == regMatricualdo.codigo){
                    printf("\n El alumno ya está matriculado en la asignatura");
                    return;
                }
                fread(&regMatricualdo, sizeof(struct datosMatriculado), 1, fMatriculados);
                
            }
            //sale del bucle, si el nExp es mayor es que no hay asignatura matriculada
            
            if(matriculado.nExp < regMatricualdo.nExp){
                printf("\n El alumno no está matriculado en la asignatura %d", matriculado.codigo);
                addMatricula(nombreFmatriculados, matriculado);
            }else{
                printf("\n Else");
                fclose(fAlumnos);
                fclose(fAsignaturas);
                fclose(fMatriculados);
            }
            
        }else if(findAsignatura == 0){
            printf("\n No se ha encontrado la asignatura");
            fclose(fAlumnos);
            fclose(fAsignaturas);
            fclose(fMatriculados);
            return;
        }else{
            printf("\n ** ERROR DE MEMORIA, NO SE PUDO ACCEDER AL FICHERO **");
            fclose(fAlumnos);
            fclose(fAsignaturas);
            fclose(fMatriculados);
            return;
        }
        
    }else if(findAlumno == 0){
        printf("\n El alumno no se ha encontrado");
        fclose(fAlumnos);
        fclose(fAsignaturas);
        fclose(fMatriculados);
        return;
    }else{
        printf("\n ** ERROR DE MEMORIA, NO SE PUDO ACCEDER AL FICHERO **");
        fclose(fAlumnos);
        fclose(fAsignaturas);
        fclose(fMatriculados);
        return;
    }
}

void addMatricula(char nombre[],struct datosMatriculado alumnoMatricular){
    //0.- Creo mi fichero y mis struct
    FILE *file, *faux;
    struct datosMatriculado reg;
    
    //1.- Inicializo mi fichero
    file=fopen(nombre, "rb");
    faux=fopen("auxiliarMatriculado", "wb");
    
    if(file==NULL || faux==NULL){
        printf("\n Error de memoria ");
        return;
    }
    
    //2.- Leo y abro mi fichero
    fread(&reg, sizeof(struct datosMatriculado), 1, file);
    while (!feof(file) && reg.nExp <= alumnoMatricular.nExp) {
        fwrite(&reg, sizeof(struct datosMatriculado), 1, faux);
        fread(&reg, sizeof(struct datosMatriculado), 1, file);
    }
    
    //3.- Ya he encontrado el sitio entonces escribo
    fwrite(&alumnoMatricular, sizeof(struct datosMatriculado), 1, faux);
    
    //4.- Hago otro bucle para escribir el resto del codigo
    while (!feof(file)) {
        fwrite(&reg, sizeof(struct datosMatriculado), 1, faux);
        fread(&reg, sizeof(struct datosMatriculado), 1, file);
    }
    
    //5.- Cierro mis fopen y vuelvo y borro
    fclose(file);
    fclose(faux);
    volcarMatriculados("auxiliarMatriculado", nombre);
    
    printf("\n Se ha añadido la matricula con éxito");
    
}
