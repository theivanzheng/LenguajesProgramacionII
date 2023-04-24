//
//  main.c
//  zheng_fu_Ivan_parcial_abril
//
//  Created by Ivan Zheng on 21/4/23.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct infoPersona{
    int codUser;
    int premium;
    char motivo[40];
    int numVecesAtendido;
};

struct nodoPersona{
    int numPosicionEnLista;
    struct infoPersona info;
    struct nodoPersona *siguiente;
    struct nodoPersona *anterior;
};

struct listaDePersonas{
    char nombreLista[20];
    struct nodoPersona *primero;
    struct nodoPersona *ultimo;
};


//**** MIS FUNCIONES PRINIPALES
void addPersona(struct listaDePersonas *listaPersonas);
void atenderPersona(struct listaDePersonas *listaPersonas, struct nodoPersona *personaAatender);
void atenderPersonaPremium(struct listaDePersonas *listaPersonas);
void eliminarDeLaLista(struct listaDePersonas *listaPersonas);


//**** MIS FUNCIONES SECUNDARIAS
int menu(void);
struct nodoPersona *checkUser(struct listaDePersonas *listaPersonas, int codUser);
void restarPosicion ( struct listaDePersonas *listaPersonas, struct nodoPersona *referencia);
void enlazarListaHistorico(struct nodoPersona *persona, struct listaDePersonas *historico);
struct nodoPersona *primerPremium( struct listaDePersonas *listaPersonas);
void showLista( struct listaDePersonas listaPersonas);
void showListaHistorico( struct listaDePersonas historico);

int main(int argc, const char * argv[]) {
    struct listaDePersonas listaPersonas;
    struct listaDePersonas historicoPersonas;
    
    //incializo mis listas
    strcpy(listaPersonas.nombreLista, "ListaPersonas");
    strcpy(historicoPersonas.nombreLista, "HistoricoPersonas");
    listaPersonas.primero=listaPersonas.ultimo=NULL;
    historicoPersonas.primero=historicoPersonas.ultimo=NULL;
    
    int opc;
    do {
        opc=menu();
        
        switch (opc) {
            case 1:
                printf("\n 1. Aniadir persona al servicio ");
                addPersona(&listaPersonas);
                break;
            case 2:
                printf("\n 2. Atender a un cliente ");
                enlazarListaHistorico(listaPersonas.primero, &historicoPersonas);
                atenderPersona(&listaPersonas,listaPersonas.primero);
                break;
            case 3:
                printf("\n 3. Atender a un cliente premium ");
                enlazarListaHistorico(listaPersonas.primero, &historicoPersonas);
                atenderPersonaPremium(&listaPersonas);
                break;
            case 4:
                printf("\n 4. Abandonar la lista ");
                eliminarDeLaLista(&listaPersonas);
                break;;
            case 5:
                printf("\n 5. Historico de consultas ");
                showListaHistorico(historicoPersonas);
                break;
            case 6:
                printf("\n ** HAS SALIDO DEL PROGRAMA **");
                break;
            case 7:
                showLista(listaPersonas);
            default:
                break;
        }
    } while (opc!=6);
    
    return 0;
}






int menu(void){
    int opc;
    
    do{
        printf("\n\n****  MENU  *****");
        printf("\n\t 1. Aniadir persona al servicio ");
        printf("\n\t 2. Atender a un cliente ");
        printf("\n\t 3. Atender a un cliente premium ");
        printf("\n\t 4. Abandonar la lista ");
        printf("\n\t 5. Historico de consultas ");
        printf("\n\t 6. Salir ");
        printf("\nElige una de las opciones: ");
        scanf("%d",&opc);
        
    }while(opc<0||opc>7);
    return opc;
}

//**** MIS FUNCIONES PRINIPALES
void addPersona(struct listaDePersonas *listaPersonas){
    int codUsuario;
    struct nodoPersona *nuevo;
    
    //compruebo que no esté en la lista
    printf("\n\t Introduce el código de usuario: ");
    scanf("%d",&codUsuario);
    struct nodoPersona *persona= checkUser(listaPersonas, codUsuario);
    
    if(persona!=NULL){
        printf("\n\t Un usuario con el mismo código ya está en la lista");
        return;
    }
    
    //1.- reservo espacio
    nuevo=(struct nodoPersona *)malloc(sizeof(struct nodoPersona));
    if(nuevo==NULL){
        printf("\n***   ERRROR DE MEMORIA   ****");
        return;
    }
    
    //2.- Relleno informacion
    nuevo->info.codUser=codUsuario;
    printf("\n\t Tu usuario va a ser premium? (1. SI | 0. NO): ");
    scanf("%d",&nuevo->info.premium);
    printf("\n\t Introduce el motivo de la consulta: ");  fpurge(stdin);
    scanf("%[^\n]",nuevo->info.motivo);
    nuevo->info.numVecesAtendido=0;

    //3.- Enlazo con la lista
    if(listaPersonas->primero==NULL){
        listaPersonas->primero=nuevo;
        listaPersonas->ultimo=nuevo;
        nuevo->numPosicionEnLista=0;    //esto lo hago para saber la posición en la listas
    }else{
        listaPersonas->ultimo->siguiente=nuevo;
    }
    nuevo->anterior=listaPersonas->ultimo;
        nuevo->numPosicionEnLista=(nuevo->anterior->numPosicionEnLista)+1;
    nuevo->siguiente=NULL;
    listaPersonas->ultimo=nuevo;
    
    printf("\n Bienvenido a nuestro servicio de atención al publico, trabajamos para atenderte lo más rápido posible, te encuentras en el puesto %d ", nuevo->numPosicionEnLista);
}

void atenderPersona(struct listaDePersonas *listaPersonas, struct nodoPersona *personaAatender){
    struct nodoPersona *primero = listaPersonas->primero;
    struct nodoPersona *ultimo  = listaPersonas->ultimo;
    
    showLista(*listaPersonas);
    
    //verifico que no haya nadie en la lista para ahorrarme tiempo de ejcución
    if(listaPersonas->primero==NULL){
        printf("\n La lista está vacía, no hay nadie que atender ");
    }
    restarPosicion(listaPersonas, personaAatender);

    //caso 1: que sea el único de la lista
    if(personaAatender==primero && personaAatender==ultimo){
        listaPersonas->primero=NULL;
        listaPersonas->ultimo=NULL;
        printf("\n - La persona con código %d ha sido atendido", personaAatender->info.codUser);
    //Caso 2: que sea el primero de la lista
    }else if (listaPersonas->primero==personaAatender){
        restarPosicion(listaPersonas, personaAatender);
        printf("\n coduser: %d", personaAatender->info.codUser);
        personaAatender->siguiente->anterior=NULL;
        listaPersonas->primero=personaAatender->siguiente;
        personaAatender->siguiente=NULL;
        printf("\nLa persona con código %d ha sido atendido", personaAatender->info.codUser);
        //listaPersonas->primero->anterior=NULL;
        
    //cas0 3: es el del medio
    }else{
        restarPosicion(listaPersonas, personaAatender);
        printf("\n coduser: %d", personaAatender->info.codUser);
        //printf("\n coduser->siguiente: %d", personaAatender->siguiente->info.codUser);
        personaAatender->siguiente->anterior=personaAatender->anterior;
        personaAatender->anterior->siguiente=personaAatender->siguiente;
        personaAatender->siguiente=NULL;
        personaAatender->anterior=NULL;
        printf("\nLa persona con código %d ha sido atendido", personaAatender->info.codUser);
        
    }
    
}

void atenderPersonaPremium( struct listaDePersonas *listaPersonas){
    struct nodoPersona *premiumAtender=primerPremium(listaPersonas);
    
    if(premiumAtender==NULL){
        printf("\n No hay clientes premium en la lista ");
        return;
    }
    atenderPersona(listaPersonas, premiumAtender);
}

void eliminarDeLaLista(struct listaDePersonas *listaPersonas){
    int codeUser;
    printf("\n A quien quieres eliminar? Introduce su código de usuario: ");
    scanf("%d",&codeUser);
    struct nodoPersona *persona= checkUser(listaPersonas, codeUser);
    
    if(persona==NULL){
        printf("\n Ese usuario no se encuentra en la lista ");
        return;
    }
    
    //Desenlazo de la lista
    //1.- que sea el unico
    if(persona==listaPersonas->primero && persona==listaPersonas->ultimo){
        listaPersonas->primero=NULL;
        listaPersonas->ultimo=NULL;
        
    //2.- que sea el primero
    }else if (persona==listaPersonas->primero){
        persona->siguiente->anterior=NULL;
        listaPersonas->primero=persona->siguiente;
        persona->siguiente=NULL;
        
    //3.- que sea el ultimo
    }else if(persona==listaPersonas->ultimo){
        persona->anterior->siguiente=NULL;
        listaPersonas->ultimo=persona->anterior;
        persona->anterior=NULL;
        
    //4.- QUe sea del medio
    }else{
        persona->siguiente->anterior=persona->anterior;
        persona->anterior->siguiente=persona->siguiente;
        persona->siguiente=NULL;
        persona->anterior=NULL;
    }
    free(persona);
    
    printf("\n Sentimos no haber podido atenderle");
    
}

//**** MIS FUNCIONES SECUNDARIAS
struct nodoPersona *checkUser(struct listaDePersonas *listaPersonas, int codUser){
    struct nodoPersona *recorre=listaPersonas->primero;
    
    while (recorre!=NULL) {
        if(codUser == recorre->info.codUser){
            return recorre;
        }
        recorre=recorre->siguiente;
    }
    
    return recorre;
}

void restarPosicion ( struct listaDePersonas *listaPersonas, struct nodoPersona *referencia){
    struct nodoPersona *recorre=referencia;
    if(recorre==NULL){
        printf("\n La lista está vacía no se va a restar posiciones");
        return;
    }
    
    while (recorre!=NULL) {
        recorre->numPosicionEnLista=recorre->numPosicionEnLista-1;
        recorre=recorre->siguiente;
    }
}
    
void enlazarListaHistorico(struct nodoPersona *nuevo, struct listaDePersonas *historico){
    //antes compruebo si ya está en la lista
    struct nodoPersona *recorre=historico->primero;
    
    while (recorre!=NULL) {
        if(recorre->info.codUser==nuevo->info.codUser){
            (recorre->info.numVecesAtendido)++;
            return;
        }
        recorre=recorre->siguiente;
    }
    nuevo->info.numVecesAtendido=1;

    //3.- Enlazo con la lista
    if(historico->primero==NULL){
        historico->primero=nuevo;
        historico->ultimo=nuevo;
    }else{
        historico->ultimo->siguiente=nuevo;
        //nuevo->numPosicionEnLista=nuevo->anterior->numPosicionEnLista+1;
    }
    nuevo->anterior=historico->ultimo;
    nuevo->siguiente=NULL;
    historico->ultimo=nuevo;
}

struct nodoPersona *primerPremium( struct listaDePersonas *listaPersonas){
    //esta fucnion va a sacar el primer cliente premium
    struct nodoPersona *recorre=listaPersonas->primero;
    if(recorre==NULL){
        printf("\n Funcion sacarPremium, la lista está vacia ");
        return recorre;
    }
    
    while (recorre!=NULL) {
        if(recorre->info.premium==1){
            printf("\n hay premium");
            return recorre;
        }
        recorre=recorre->siguiente;
    }
    return recorre;
}

void showLista( struct listaDePersonas listaPersonas){
    struct nodoPersona *recorre=listaPersonas.primero;
    
    printf("\n ** %s **", listaPersonas.nombreLista);
    while (recorre!=NULL) {
        printf("\n\t Cliente: %d, Premium: %d",recorre->info.codUser, recorre->info.premium );
        
        recorre=recorre->siguiente;
    }
}

void showListaHistorico( struct listaDePersonas historico){
    struct nodoPersona *recorre=historico.primero;
    
    printf("\n ** %s **", historico.nombreLista);
    while (recorre!=NULL) {
        if(recorre->info.numVecesAtendido==0){
            printf("\n\t Cliente: %d, No ha sido atenddo ",recorre->info.codUser);

        }else{
            printf("\n\t Cliente: %d, NumVecesAtendido: %d ",recorre->info.codUser, recorre->info.numVecesAtendido);
        }
        recorre=recorre->siguiente;
    }
}
