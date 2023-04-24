//
//  main.c
//  extareasMoodle2
//
//  Created by Ivan Zheng on 20/4/23.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct fecha{
    int dia;
    int mes;
    int anio;
};

struct nodoTarea{
    char login[10];
    char titulo[40];
    struct fecha fecha;
};

struct listaTarea{
    struct nodoTarea *primero;
    struct nodoTarea *ultimo;
};


//*** MIS FUNCIONES PRINCIPALES
void subirTareaMoodle(struct listaTarea *listaTareas);

//*** MIS FUNCIONES SECUNDARIAS
int menu(void);


int main(int argc, const char * argv[]) {

    int opc;
    do{
        opc=menu();
        
        switch (opc) {
            case 1:
                
                break;
                
            default:
                break;
        }
    }while (opc != 5);
    
    return 0;
}



//*** MIS FUNCIONES PRINCIPALES


//*** MIS FUNCIONES SECUNDARIAS
int menu(void){
    int opc;
    do{
        printf("\n*** MENU ***");
        printf("\n\t1. Subir tarea a moodle ");
        printf("\n\t2. Visualizar el numero de obligatorias y voluntarias de un alumno ");
        printf("\n\t3. Listado de alumnos ");
        printf("\n\t4. Eliminar todas las tareas obligatorias de un alumno ");
        
        scanf("%d",&opc);
    }while(opc<0 || opc > 5);
    
    return  opc;
}
