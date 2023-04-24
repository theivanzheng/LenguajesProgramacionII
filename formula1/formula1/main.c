//
//  main.c
//  formula1
//
//  Created by Ivan Zheng on 20/4/23.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct listaEquipos{
    struct nodoEquipo *primero;
    struct nodoEquipo *ultimo;
};



struct listaPilotos{
    struct nodoPiloto *primero;
    struct nodoPiloto *ultimo;
};

struct nodoEquipo{
    char nombre[30];
    int anno;
    float presupuestoCoche;
    struct listaPilotos listaPilotos;
    struct nodoEquipo *siguiente;
    struct nodoEquipo *anterior;
};

struct nodoPiloto{
    char nombrePiloto[20];
    int edad;
    float sueldoPiloto;
    struct nodoPiloto *siguiente;
    struct nodoPiloto *anterior;
};


//****  MIS FUNCIONES   ***
void addEquipo( struct listaEquipos *listaEquipos);
void addPiloto( struct listaEquipos *listaEquipos);
void calcularSueldoMedio(  struct listaEquipos *listaEquipos);
void traspasarPiloto( struct listaEquipos *listaEquipos);
void visualizarTodo( struct listaEquipos *listaEquipos);

//****  MIS FUNCIONES SECUNDARIAS  ***
void crearListaDeListas( struct listaEquipos *listaEquipos);
struct nodoEquipo *checkEquipo( struct listaEquipos *listaEquipos, char nombre[]);
struct nodoPiloto *checkPiloto( struct listaPilotos *listaPilotos, char nombre[]);
void eliminarPiloto( struct listaEquipos *listaEquipos, struct nodoEquipo *equipo, struct nodoPiloto *piloto);
void showPilot(struct listaPilotos *listaPilotos);

int menu(void);
void addNodoPiloto(struct listaPilotos *listaPilotos);


int main(int argc, const char * argv[]) {
    struct listaEquipos listaEquipos;
    int opc;
    
    
    crearListaDeListas(&listaEquipos);
    do{
       opc=menu();
        
        switch (opc) {
            case 1:
                printf("\n 1. Aniadir equipo  ");
                addEquipo(&listaEquipos);
                break;
            case 2:
                printf("\n 2. Aniadir piloto  ");
                addPiloto(&listaEquipos);
                break;
            case 3:
                printf("\n 3. Calcula sueldo medio de un equipo  ");
                calcularSueldoMedio(&listaEquipos);
        
                break;
            case 4:
                printf("\n 4. Traspasar piloto  ");
                traspasarPiloto(&listaEquipos);
                break;
            case 5:
                printf("\n 5. Visualizar todo  ");
                visualizarTodo(&listaEquipos);
                break;
            case 6:
                printf("\nHas salido del programa");

                break;
            default:
                break;
        }
    }while(opc!=7);
    
    return 0;
}


//****  MIS FUNCIONES   ***
void addPiloto( struct listaEquipos *listaEquipos){
    char equipo[20];
    
    if(listaEquipos->primero==NULL){
        printf("\n La lista de quipos está vacía ");
        return;
    }
    
    printf("\nPara qué equipo quieres introducir piloto: ");    scanf("%s", equipo);
    struct nodoEquipo *equipoChecked =checkEquipo(listaEquipos, equipo);
    
    if(equipoChecked==NULL){
        printf("\nEse equipo no existe");
        return;
    }
    addNodoPiloto(&equipoChecked->listaPilotos);
    
}

void calcularSueldoMedio(  struct listaEquipos *listaEquipos){
    char nomEquipo[20];
    struct nodoPiloto *recorre;
    float sueldoTotal=0;
    int numJugadores=0;
    
    printf("\n\tIntroduce el nombre del equipo: "); fflush(stdin);
    scanf("%s",nomEquipo);
    struct nodoEquipo *equipo= checkEquipo(listaEquipos, nomEquipo);
    
    if(equipo==NULL){
        printf("\nEl equipo que has introducido no existe");
        return;
    }
    recorre=equipo->listaPilotos.primero;
    
    while (recorre!=NULL) {
        sueldoTotal= sueldoTotal+recorre->sueldoPiloto;
        numJugadores++;
        recorre=recorre->siguiente;
    }
    sueldoTotal = sueldoTotal/numJugadores;
    printf("\nEl sueldo medio de %s es de %.2f", equipo->nombre, sueldoTotal);
}

void traspasarPiloto( struct listaEquipos *listaEquipos){
    char equipoDestino[20];
    char equipoOrigen[20];
    char piloto[20];
    
    struct nodoEquipo *origen, *destino;
    struct nodoPiloto *pilotoStruct;
    
    printf("\nIntroduce el quipo donde está el pilot.: ");
    scanf("%s",equipoOrigen);
    origen= checkEquipo(listaEquipos, equipoOrigen);
    
    if(origen==NULL){
        printf("\nEl quipo introducido no está en la lista ");
        return;
    }
    printf("\nIntroduce el nombre del pilot: ");
    scanf("%s",piloto);
    pilotoStruct= checkPiloto(&origen->listaPilotos, piloto);
    
    if(pilotoStruct==NULL){
        printf("\nEl pilot introducido no está en la lista ");
        return;
    }
    printf("\nIntroduce el quipo donde quires mover el pilot.: ");
    scanf("%s",equipoDestino);
    destino= checkEquipo(listaEquipos, equipoDestino);
    
    if(origen==NULL){
        printf("\nEl quipo introducido no está en la lista ");
        return;
    }
    
    //elimino de la lista origen
    while (pilotoStruct!=NULL) {
        eliminarPiloto(listaEquipos, origen, pilotoStruct);
        pilotoStruct=pilotoStruct->siguiente;
    }
    
    //añado en la lista
    if(destino->listaPilotos.primero==NULL){
        destino->listaPilotos.primero=pilotoStruct;
        destino->listaPilotos.ultimo=pilotoStruct;
        
    }else{
        destino->listaPilotos.ultimo->siguiente=pilotoStruct;
    }
    pilotoStruct->anterior=destino->listaPilotos.ultimo;
    pilotoStruct->siguiente=NULL;
    destino->listaPilotos.ultimo=pilotoStruct;
    printf("\nEl piloto se ha movido con exito");
    
}
void visualizarTodo( struct listaEquipos *listaEquipos){
    struct nodoEquipo *recorre = listaEquipos->primero;
    while (recorre!=NULL) {
        printf("\n%s",recorre->nombre);
        showPilot(&recorre->listaPilotos);
        recorre=recorre->siguiente;
    }
}


//****  MIS FUNCIONES SECUNDARIAS  ***
int menu(void){
    int opc;
    
    do{
        printf("\n*** MENU ***");
        printf("\n\t 1. Adniadir equipo  ");
        printf("\n\t 2. Aniadir piloto  ");
        printf("\n\t 3. Calcula sueldo medio de un equipo  ");
        printf("\n\t 4. Traspasar piloto  ");
        printf("\n\t 5. Visualizar todo  ");
        printf("\n\t 6. Salir  ");
        printf("\nEscoge una de las opciones:   ");
        
        scanf("%d",&opc);
        
    }while(opc<0||opc>7);
    return opc;
}

void crearListaDeListas( struct listaEquipos *listaEquipos){
    
    int numEquipos;
    printf("\nIntroduce El número de equipos que quieres crear: ");
    scanf("%d", &numEquipos);
    
    listaEquipos->primero=listaEquipos->ultimo=NULL;
    
    for (int i =0; i<numEquipos; i++) {
        addEquipo(listaEquipos);
    }
}

void addEquipo( struct listaEquipos *listaEquipos){
    struct nodoEquipo *nuevo= listaEquipos->primero;
    
    //1.- reservo espacio
    nuevo=(struct nodoEquipo *)malloc(sizeof(struct nodoEquipo));
    if(nuevo==NULL){
        printf("\n** ERROR DE MEMORIA**");
    }
    
    //2.- RELLENO INFORMACIÓN
    printf("\n\tIntroduce el nombre del equipo: ");
    scanf("%s",nuevo->nombre);
    struct nodoEquipo *equipo= checkEquipo(listaEquipos, nuevo->nombre);
    
    if(equipo!=NULL){
        printf("\nUn equipo con el mismo nombre ya ha sido introducido ");
        return;
    }
    printf("\n\tIntroduce el anio: ");
    scanf("%d",&nuevo->anno);
    printf("\n\tIntroduce el presupuesto del coche: ");
    scanf("%f",&nuevo->presupuestoCoche);
    
    nuevo->listaPilotos.primero  =NULL;
    
    //3.- enlazo con la lista
    if(listaEquipos->primero==NULL){
        listaEquipos->primero=nuevo;
    }else{
        listaEquipos->ultimo->siguiente=nuevo;
    }
    nuevo->anterior=  listaEquipos->ultimo;
    nuevo->siguiente=NULL;
    listaEquipos->ultimo=nuevo;
    
}

struct nodoEquipo *checkEquipo( struct listaEquipos *listaEquipos, char nombre[]){
    struct nodoEquipo *recorre = listaEquipos->primero;
    
    while (recorre!=NULL) {
        if(strcmp(nombre, recorre->nombre)==0){
            return recorre;
        }
           recorre=recorre->siguiente;
    }
    return recorre;
}

void addNodoPiloto(struct listaPilotos *listaPilotos){
    struct nodoPiloto *nuevo = listaPilotos->primero;
    //1.- reservo espacio
    nuevo=(struct nodoPiloto *)malloc(sizeof(struct nodoPiloto));
    if(nuevo==NULL){
        printf("\n** ERROR DE MEMORIA**");
    }
    
    //2.- RELLENO INFORMACIÓN
    printf("\n\tIntroduce el nombre del piloto: ");
    scanf("%s",nuevo->nombrePiloto);
    struct nodoPiloto *piloto= checkPiloto(listaPilotos, nuevo->nombrePiloto);
    
    if(piloto!=NULL){
        printf("\nYa existe un piloto con el mismo nombre");
        return;
    }
    printf("\nIntroduce el sueldo del piloto");
    scanf("%f",&nuevo->sueldoPiloto);
    printf("\nIntroduce la edad del piloto");
    scanf("%d",&nuevo->edad);
    
    //3.- enlazo con la lista
    if(listaPilotos->primero==NULL){
        listaPilotos->primero=nuevo;
    }else{
        listaPilotos->ultimo->siguiente=nuevo;
    }
    nuevo->anterior=  listaPilotos->ultimo;
    nuevo->siguiente=NULL;
    listaPilotos->ultimo=nuevo;
}

struct nodoPiloto *checkPiloto( struct listaPilotos *listaPilotos, char nombre[]){
    struct nodoPiloto *recorre = listaPilotos->primero;
    
    while (recorre!=NULL) {
        if(strcmp(nombre, recorre->nombrePiloto)==0){
            return recorre;
        }
           recorre=recorre->siguiente;
    }
    return recorre;
}

void eliminarPiloto( struct listaEquipos *listaEquipos, struct nodoEquipo *equipo, struct nodoPiloto *piloto){
    struct nodoPiloto *primero = equipo->listaPilotos.primero;
    struct nodoPiloto *ultimo = equipo->listaPilotos.ultimo;
    struct nodoPiloto *siguiente= piloto->siguiente;
    struct nodoPiloto *anterior= piloto->anterior;
    
    
    if(equipo->listaPilotos.primero==NULL){    //que la lista esté vacía
        printf("\nLa lista está ya vacía");
        return;
    }else if (primero==ultimo){     //que sea el único
        primero=ultimo=NULL;
        
    }else if (primero==piloto){     //que sea el primero
        primero->siguiente->anterior=NULL;
        primero=primero->siguiente;
        piloto->siguiente=NULL;
    }else if( ultimo==piloto  ){    //que sea el ultimo
        ultimo->siguiente=piloto;
        piloto->anterior=ultimo;
        piloto->siguiente=NULL;
        ultimo=piloto;
    }else{                          //que sea el del medio
        siguiente->anterior=anterior;
        anterior->siguiente=siguiente;
        piloto->siguiente=NULL;
        piloto->anterior=NULL;
    }

}

void showPilot(struct listaPilotos *listaPilotos){
    struct nodoPiloto *recorre = listaPilotos->primero;
    
    while (recorre!=NULL) {
        printf("\n Piloto: %s",recorre->nombrePiloto);
        printf("\n\t Sueldo: %.2f",recorre->sueldoPiloto);
        printf("\n\t Edad: %d",recorre->edad);
        recorre=recorre->siguiente;
    }
}
