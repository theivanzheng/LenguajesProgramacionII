#include <stdio.h>
#include <stdlib.h>
struct tipoInfo{
    int key;
    double value;
};
struct tipoNodo{
    struct tipoInfo information;
    struct tipoNodo *siguiente;
};
void addInfo(struct tipoInfo *information); //paso por referencia porque quiero cambiar lo que contiene
void visualizarLista(struct tipoNodo * primero);
void addNode(struct tipoNodo ** primero); //le paso la lista por referencia
void addNodeEnd(struct tipoNodo ** primero); //le paso la lista por referencia
struct tipoNodo * buscarDevolviendoTbAnterior(struct tipoNodo *primero, int keyBuscar,struct tipoNodo ** anterior);
//devuelve el nodo que tiene la key a buscar si existe, sino null
//además devuelve en el tercer parámetro un puntero que localiza el anterior al buscado
void modificarInformacionNodo(struct tipoNodo *primero);
void eliminarNodo(struct tipoNodo **primero);
void insertarOrdenado(struct tipoNodo **primero, int keyInsertar);
struct tipoNodo *buscarOrdenado(struct tipoNodo *primero, int keyBuscar);
void eliminarNodoEnListaOrdenada(struct tipoNodo **primero, int keyBorrar);
void eliminarTodosLosNodosDeLaLista(struct tipoNodo **primero );


int menu(void);
int main() {
    struct tipoNodo *primero = NULL; //lista vacía
    int opc;
    int keyBuscar;
    struct tipoNodo *anterior, *buscado;
    do{
        opc= menu();
        switch (opc) {
            case 1:
                addNode(&primero);
                break;
            case 2:
                visualizarLista(primero);
                break;
            case 3:
                addNodeEnd(&primero);
                break;

            case 5:
                printf("Introduce la key a buscar");
                scanf("%d",&keyBuscar);
                buscado=buscarDevolviendoTbAnterior(primero,keyBuscar,&anterior);
                if(buscado!=NULL){
                    printf("Se ha encontrado la clave\n");
                }else{
                    printf("La clave %d no está en la lista\n",keyBuscar);
                }
            case 6:
                modificarInformacionNodo(primero);
                break;
            case 7:
                eliminarNodo(&primero);//siempre qeu añado o elimino se pasa por referencia
                break;
            default:
                break;
        }
    }while(opc!=0);
}

int menu(void){
    int opc;
    do{
        printf("\n 1.- Aniadir al principio de la lista");
        printf("\n 2.- Visualizar la lista");
        printf("\n 3.- Visualizar el número de elementos");
        printf("\n 4.- Aniadir al final de la lista");
        printf("\n 5.- Buscar un elemento");
        printf("\n 6.- Modificar un elemento");
        printf("\n 7.- Eliminar un elemento");

        scanf("%d",&opc);
    }while(opc==0);
    return opc;
}
void addNode(struct tipoNodo ** primero){
    struct tipoNodo *nuevo;
    //1.- Reservo memoria para la información que no tengo
    nuevo = (struct tipoNodo*) malloc(sizeof (struct tipoNodo));
        if(nuevo == NULL){
            printf("\nERROR DE MEMORIA"); //En el 99% d elso casos malloc va bien, esto es en caso de que no salga bien
            return;
        }
    //2.- Relleno la información
    addInfo(&nuevo->information); //la función espera un puntero, para enviar un puntero pasamos &

    //3.- Lo conecto con la lista
    /*nuevo->siguiente=NULL;
    *primero=nuevo;*/
    nuevo->siguiente = *primero;
    *primero = nuevo;

}

void addInfo(struct tipoInfo *information){
    printf("Introduce la key(int)\n");
    scanf("%d",&information->key);
    printf("Introduce el valor(double)\n");
    scanf("%lf",&information->value);

}
void visualizarLista(struct tipoNodo * primero){
    struct tipoNodo *recorre = primero; //Esto los pongo por si acaso se me pira y paso por referencia
    while(recorre != NULL){
        printf("\n key: %d, Value: %lf",recorre->information.key,recorre->information.value);
        recorre=recorre->siguiente;
    }
}

void addNodeEnd(struct tipoNodo ** primero){
    struct tipoNodo *nuevo;
    struct tipoNodo *ultimo = *primero;

    //1.- Reservo memoria para la información que no tengo
    nuevo = (struct tipoNodo*) malloc(sizeof (struct tipoNodo));
    if(nuevo == NULL){
        printf("\nERROR DE MEMORIA"); //En el 99% d elso casos malloc va bien, esto es en caso de que no salga bien
        return;
    }
    //2.- Relleno la información
    addInfo(&nuevo->information); //la función espera un puntero, para enviar un puntero pasamos &

    //3.- Lo conecto con la lista

    if(*primero == NULL){
        nuevo->siguiente=NULL;
        *primero=nuevo;
    }else{
        while(ultimo->siguiente !=NULL){
            ultimo = ultimo->siguiente;
        }
        nuevo->siguiente=NULL;
        ultimo->siguiente=nuevo;
    }
}

struct tipoNodo * buscarDevolviendoTbAnterior(struct tipoNodo *primero, int keyBuscar,struct tipoNodo ** anterior){
    //primero inicializo los punteros que voy a utilizar
    struct tipoNodo *recorre;
    recorre = primero;
    anterior = NULL;

    while(recorre!=NULL && recorre->information.key != keyBuscar){
        *anterior=recorre;
        recorre = recorre->siguiente;
    }
    return recorre;
}
void modificarInformacionNodo(struct tipoNodo *primero){
    int keyNodoAModificar;
    struct tipoNodo *buscado, *anteroir;
    printf("Introduce la key que quieres modificar: ");
    scanf("%d",&keyNodoAModificar);
    buscado = buscarDevolviendoTbAnterior(primero,keyNodoAModificar,&anteroir);
    if(buscado!=NULL){
        //Lo ha encontradom le pido el nuevo valor
        printf("\n Introduce el nuevo valor para el nodo con la key %d: ",keyNodoAModificar);
        scanf("%lf",&buscado->information.value);
    }else{
        printf("Imposible de modificar no existe el nodo con esa key\n");
    }
}

void eliminarNodo(struct tipoNodo **primero){
    struct tipoNodo *borrar, *anterior;
    int keyAborrar;
    printf("Introduce la key que quieres borrar: ");
    scanf("%d",&keyAborrar);
    borrar= buscarDevolviendoTbAnterior(*primero,keyAborrar,&anterior);
    if(borrar==NULL){
        printf("Imposible borrar el nodo no existe\n");
        return;
    }
        //Tengo dos casos: borrar el primero o alguno del medio
    if(borrar==*primero){
        *primero=(*primero)->siguiente;
    }else{
        //Borro otro
        anterior->siguiente=borrar->siguiente;
    }
    free(borrar);

}

void insertarOrdenado(struct tipoNodo **primero, int keyInsertar){
    struct tipoNodo*anterior,*recorre,*nuevo;

    anterior = NULL;
    recorre= *primero;
    //Siempre la primera condición es la misma
    while((recorre!=NULL) && (recorre->information.key<keyInsertar)){
        anterior=recorre;
        recorre=recorre->siguiente;
    }
    //Ojo que me ha parado en el sitio que debería de estar
    if(recorre->information.key == keyInsertar){
        //Tengo que pensar: Aluna vez puede valer recorre NULL?
        //Sí, puede valer null cuando el número a entrar sea mayor que el que tengo
        printf("La key repetida");
        return;
    }
}
struct tipoNodo *buscarOrdenado(struct tipoNodo *primero, int keyBuscar){
    struct tipoNodo *recorre = primero;
    while(recorre !=NULL && (recorre->information.key<keyBuscar)){
        recorre=recorre->siguiente;
    }
    if(recorre!=NULL && recorre->information.key==keyBuscar){
        return recorre;
    }
    else{
        return NULL;    //NO está en la lista
    }
}

void eliminarNodoEnListaOrdenada(struct tipoNodo **primero, int keyBorrar){
    struct tipoNodo *anterior,*borrar;
    anterior=NULL;
    borrar=*primero;
    while (borrar!=NULL && borrar->information.key<keyBorrar){
        anterior=borrar;
        borrar= borrar->siguiente;
    }
    //compruebo que esa clave está en la lista
    if(borrar!=NULL && (borrar->information.key == keyBorrar)){
        //lo tengo que borrar
        if(anterior == NULL){
            //borro el primero
            *primero = borrar->siguiente;
        }
    }else{
        printf("La clave no existe y no se puede borrar\n");
    }
}

void eliminarTodosLosNodosDeLaLista(struct tipoNodo **primero ){
    struct tipoNodo *borrar = primero;
    struct tipoNodo *siguiente;

    while(borrar!=NULL){
        siguiente=borrar->siguiente;
        free(borrar);
        borrar=siguiente;
    }
    *primero=NULL;
}
