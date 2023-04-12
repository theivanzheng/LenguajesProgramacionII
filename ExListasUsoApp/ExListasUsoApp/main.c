//
//  main.c
//  ExListasUsoApp
//
//  Created by Ivan Zheng on 11/4/23.
//

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

struct infoApp{
    char nombre[10];
    int numUsada;
    int timeUsed; //en segundos
};

struct tipoNodoApp{
    struct infoApp info;
    struct tipoNodoApp *siguiente;
    struct tipoNodoApp *anterior;
};

struct listaApps{
    struct tipoNodoApp *primero;
    struct tipoNodoApp *ultimo;
};

//MIS FUNCIONES
int menu(void);
void useApp(struct listaApps *listaApp);
void addTiempoUso(struct listaApps *listaApp, char appName[]);

//FUNCIONES AUXILIARES
struct tipoNodoApp *checkAppName(struct listaApps listaApp, char appName[]);
void crearApp (struct listaApps *listaApps, char appName[]);
void vistaGeneral(struct listaApps listaApp);

int main(int argc, const char * argv[]) {
    char appName[10];
    int opt;
    
    struct listaApps listaApps;
    listaApps.primero=NULL;
    listaApps.ultimo=NULL;
    
    do{
        opt=menu();
        
        switch (opt) {
            case 1:
                useApp(&listaApps);
                break;
            case 2:
                printf("\n2.- AÑADIR TIEMPO DE USO");
                printf("\nIntroduce el nombre de la app: ");
                fflush(stdin);
                scanf("%[^\n]",appName);
                addTiempoUso(&listaApps, appName);
                break;
            case  5:
                vistaGeneral(listaApps);
            default:
                printf("\nHAS SALIDO DEL PROGRAMA");
                break;
        }
        
    }while(opt != 0);
    
    return 0;
}

// ****** DESARROLLO DE MIS FUNCIONES *****
int menu(void){
    int opc=0;
    
    do {
        
        printf("\n\n******MENU******");
        printf("\n1. Usar una app");
        printf("\n2. Actualizar tiempo de uso");
        printf("\n3. Desinstalar una aplicación");
        printf("\n4. Obtener un listado de aplicaciones ordenada por uso");
        printf("\n5. Obtener una vista general de todo");
        printf("\n0. Salir del programa");
        printf("\n-->Escoge una opción: ");
        scanf("%d", &opc);
        
        if(opc <0|| opc>5){
            printf("\nLA OPCIÓN ESCOGIDA NO EXISTE, PRUEBA OTRA VEZ");
        }
    }while (opc<0|| opc>5);
    return opc;
}

void useApp(struct listaApps *listaApp){
    char appName[10];
    printf("\n1. Usar una app");
    printf("\nIntroduce el nombre de la app: ");
    fflush(stdin);
    scanf("%[^\n]",appName);
    struct tipoNodoApp *check =checkAppName(*listaApp, appName);
    
    if(check == NULL){
        printf("\nLa aplicación no ha sido creada,vamos a crearla");
        crearApp(listaApp, appName);
    }else{
        printf("\nLa aplicación ya ha sido creada, se va a incrementar su numero de uso");
        (check->info.numUsada)++;
    }
}

struct tipoNodoApp *checkAppName(struct listaApps listaApp, char appName[]){
    struct tipoNodoApp *recorre= listaApp.primero;
    
    while (recorre!=NULL) {
        if(strcmp(recorre->info.nombre, appName)==0){
            return recorre;
        }else{
            recorre=recorre->siguiente;
        }
    }
    printf("\nRECORRE CHECK SE HA QUEDADO EN %s", recorre->info.nombre);
    return recorre;
}

void crearApp (struct listaApps *listaApps, char appName[]){
    //1.- Reservo Memoria
    struct tipoNodoApp *nuevo;
    nuevo=(struct tipoNodoApp*)malloc(sizeof(struct tipoNodoApp));
        if(nuevo==NULL){
            printf("\nNO se ha podido resevar la memoria");
        }
    //2.- Relleno la información
    nuevo->info.numUsada=1;
    strcpy(nuevo->info.nombre, appName);
    
    //3.- Conecto con la lista
    if(listaApps->primero == NULL){
        listaApps->primero=nuevo;
    }else{
        listaApps->ultimo->siguiente=nuevo;
    }
    nuevo->siguiente=NULL;
    nuevo->anterior=listaApps->ultimo;
    listaApps->ultimo=nuevo;
    
    printf("\nSe ha añadido la aplicación con éxito");
}

void addTiempoUso(struct listaApps *listaApp, char appName[]){
    int segundos;
    struct tipoNodoApp *check =checkAppName(*listaApp, appName);
    
    if(check == NULL){
        printf("\nLa aplicación introducida no existe");
        return;
    }else{
        printf("Introduce el tiempo que le quieres añadir a la aplicación en segundos");
        scanf("%d",&segundos);
        check->info.timeUsed += segundos;
        printf("\nSe ha actualizado el tiempo de uso de %s a: %d segundos",check->info.nombre, check->info.timeUsed);
    }
    
}

void vistaGeneral(struct listaApps listaApp){
    struct tipoNodoApp *recorre = listaApp.primero;
    
    while (recorre!=NULL) {
        printf("\n %s", recorre->info.nombre);
        printf("\n\t Tiempo de uso: %d sec", recorre->info.timeUsed);
        printf("\n\t Num veces usada: %d", recorre->info.numUsada);
        recorre=recorre->siguiente;
    }
}
