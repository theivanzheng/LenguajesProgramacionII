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

//FUNCIONES AUXILIARES
struct tipoNodoApp *checkAppName(struct listaApps listaApp, char appName[]);
void crearApp (struct listaApps *listaApps, char appName[]);

int main(int argc, const char * argv[]) {
    
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
                
            default:
                printf("\nHAS SALIDO DEL PROGRAMA");
                break;
        }
        
    }while(opt != 0);
    
    return 0;
}




int menu(void){
    int opc=-1;
    
    do {
        printf("\n--------------------------------------------------------");
        printf("\nMENU:");
        printf("\n1. Usar una app");
        printf("\n2. Actualizar tiempo de uso");
        printf("\n3. Desinstalar una aplicación");
        printf("\n4. Obtener un listado de aplicaciones ordenada por uso");
        printf("\n0. Salir del programa");
        printf("\n-->Escoge una opción: ");
        scanf("%d", &opc);
        printf("\n--------------------------------------------------------");
        if(opc <0|| opc>4){
            printf("\nLA OPCIÓN ESCOGIDA NO EXISTE, PRUEBA OTRA VEZ");
        }
    }while (opc<0|| opc>4);
    printf("%d", opc);
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
        if(recorre->info.nombre==listaApp.primero->info.nombre){
            return recorre;
        }else{
            recorre=recorre->siguiente;
        }
    }
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
