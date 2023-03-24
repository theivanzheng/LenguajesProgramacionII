#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>


struct publicacion{
    char username[20];
    char content[100];
    int  mg;
};

struct tipoNodo{
    struct publicacion info;
    struct tipoNodo *next;      //cuidado con el tipo de struct que pones
};

void addInfo (struct tipoNodo **primero, char newUser[]);
void giveLike(struct tipoNodo *primero);
void findLast(struct tipoNodo *primero);
void showAll(struct tipoNodo *primero);
void findPopular(struct tipoNodo *primero);
void show(struct tipoNodo *recorre);
void removeInfo (struct tipoNodo **primero, char newUser[]);
void countAll(struct tipoNodo *primero);


int main(int argc, const char * argv[]) {
    int opt=0;
    char newUser[20];
    
    struct tipoNodo* primero = NULL;
    
    do{
        printf("\nMENU:");
        printf("\n\t1.- Add info(principio)");
        printf("\n\t2.- Dar like");
        printf("\n\t3.- Buscar la última publicación");
        printf("\n\t4.- Mostrar publicaciones más populares");
        printf("\n\t5.- Listar");
        printf("\n\t6.- Eliminar todas las publicaciones de un usuario");
        printf("\n\t7.- Mostrar el numero de uso de la red social");
        printf("\n\t0.- Salir");
        printf("\n\nElige una opción: ");
        scanf("%d",&opt);
        
        switch (opt) {
            case 1:
                printf("\n\tEscribe el nombre de usuario");
                scanf("%s",newUser);
           
                addInfo(&primero, newUser);
                break;
            case 2:
                giveLike(primero);
                break;
            case 3:
                findLast(primero);
                break;
            case 4:
                findPopular(primero);
                break;
            case 5:
                showAll(primero);
                break;
            case 6:
                printf("\n\tEscribe el nombre de usuario");
                scanf("%s",newUser);
                removeInfo(&primero, newUser);
                break;
            default:
                printf("**Has salido del programa**");
                break;
        };
    }while(opt != 0);
    
    
    return 0;
}
void show(struct tipoNodo *recorre){
    printf("\n\t\tUsuario: %s",recorre->info.username);
    printf("\n\t\tPublicacion: %s",recorre->info.content);
    printf("\n\t\tNumLikes: %d",recorre->info.mg);
}

void addInfo (struct tipoNodo **primero, char newUser[]){
    struct tipoNodo* new;
    
    //1.- Reservo Memoria
    new=(struct tipoNodo* ) malloc(sizeof(struct tipoNodo));
        if(new==NULL){
            printf("**ERROR, NO SE HA PODIDO RESERVAR MEMORIA");
        }
    
    //2.- RELLENAR INFORMACIÓN
    strcpy(new->info.username, newUser);
    printf("\n\tTu usuario es: %s", new->info.username);
    printf("\n\tIntroduce el contenido de tu publicación: ");
    fpurge(stdin);
    scanf("%[^\n]",new->info.content);
    printf("\n\tIntroduce los mg de tu publicacion: ");
    scanf("%d",&new->info.mg);
    
    //3.- CONECTAR A LA LISTA
    new->next= *primero;
    *primero=new;
    }

void giveLike(struct tipoNodo *primero){
    struct publicacion found;
    struct tipoNodo *recorre = primero;
    printf("\n\tIntroduce el nombre de usuario");
    fpurge(stdin);
    scanf("%s",found.username);
    printf("\n\tIntroduce el contenido de la publicacion");
    fpurge(stdin);
    scanf("%s",found.content);
    
    if(primero==NULL){
        printf("\n**LA LISTA ESTA VACIA**");
        return;
    }
    
    while (recorre!=NULL && (strcmp(found.username, recorre->info.username)!=0 || strcmp(found.content, recorre->info.content)!=0)){
        recorre=recorre->next;
    }
    if(recorre==NULL){
        printf("\n\t**NO SE HA ENCONTRADO EL USUARIO O LA PUBLICACION**");
        return;
    }
    (recorre->info.mg)++;
    
    printf("\n\t Has dado like a la publicación : \n\t '%s'",recorre->info.content);
    printf("\n\t Me gustas : %d",recorre->info.mg);

}

void findLast(struct tipoNodo *primero){
    
    struct tipoNodo *recorre = primero;
    struct tipoNodo *ultimo = NULL;
    char lastUser[30];
    int opc=0;
    
    printf("\nEL primero");
    show(primero);
    if(primero==NULL){
        printf("\n**LA LISTA ESTA VACIA**");
        return;
    }
    printf("\n\tIntroduce el usuario del que quieres buscar la última publicacion: ");
    fflush(stdin);
    scanf("%s",lastUser);
    
    //Si tomo ultimo el que está al final de la lista el código sería así
    while (recorre!=NULL) {
        if( strcmp(lastUser, recorre->info.username)==0){
            printf("\nHa encontrado uno igual");
            ultimo = recorre;
            show(recorre);
        }
        recorre=recorre->next;
    }
    
    if(ultimo==NULL){
        printf("\nEl usuario no existe o no ha hecho ninguna publicación");
        return;
    }else{
        show(ultimo);
        printf("\nQuieres darle un like a esta publicación? \n1)SI \n2)No");
        scanf("%d",&opc);
        if(opc==1){
            (ultimo->info.mg)++;
        }else{
            printf("\nOkay amargado");
        }
    }
    /*
    //Si; tomo como último el que es más reciente sólo hay que encontrar el más proximo al primero(el más reciente que se haya metido vaya)
    while (recorre!=NULL) {
        if( strcmp(lastUser, recorre->info.username)==0){
            ultimo = recorre;
        }
        recorre=recorre->next;
    }
        show(recorre);*/
}

void showAll(struct tipoNodo *primero){
    struct tipoNodo *recorre=primero;
    do{
        printf("\n\t\tUsuario: %s",recorre->info.username);
        printf("\n\t\tPublicacion: %s",recorre->info.content);
        printf("\n\t\tNumLikes: %d\n",recorre->info.mg);
        recorre=recorre->next;
        
    }while (recorre!=NULL);
}

void findPopular(struct tipoNodo *primero){
    struct tipoNodo *recorre =primero;
    struct tipoNodo *max=primero;//por defecto es el primero

    
    while (recorre!=NULL) {
        /* printf("\n\nRECORRE: %s",recorre->info.username);
         printf("\nValor de recorre: %d",recorre->info.mg);
         printf("\nValor de max: %d",max->info.mg);*/
        
        //Voy comparando con una auxiliar, si es mayor la meto ahí
        if(recorre->info.mg > max->info.mg){
            max=recorre;
        }
        //Voy recorriendo my lista hasta llegar al final
            recorre=recorre->next;
    }
        
    //show(max);
    recorre=max;
    while (recorre!=NULL) {
        //mi segunda barrida
       // printf("\nEntro en la segunda barrida");
        
        if(max->info.mg > recorre->info.mg){
            recorre=recorre->next;
        }else if(max->info.mg == recorre->info.mg){
            printf("\nEncuentro uno igual");
                show(recorre);
                recorre=recorre->next;
            }
        }
    return;
    }
        
    


void removeInfo (struct tipoNodo **primero, char newUser[]){
    struct tipoNodo *borrar, *anterior;
    printf("Hello");
    //1. localizo el nodo a borrar y el anterior a borrar
    borrar=*primero;
    anterior=NULL;
    while (borrar->next!=NULL) {
        if(borrar->info.username==newUser){
            if (borrar == *primero){//borro el primero
                //muevo el primero para que apunte al segundo que ahora será el primero
                *primero = borrar->next;
                printf("\nBorrado con éxito");
            }else{//borro otro distinto del primero
                anterior->next = borrar->next;
                //4. Libero la memoria asociada al nodo a borrar
                free(borrar);
                printf("\nBorrado con éxito");
            }
        }
        anterior=borrar;
        borrar=borrar->next;
    }
    //2. compruebo que lo ha encontrado y por tanto voy a borrar
    if (borrar == NULL){
    printf("\n imposible borrar no está en la lista"); return;
    }
    
}
void find(struct tipoNodo *primero, char find[]){
    
    struct tipoNodo *recorre = primero;
    while (recorre!=NULL) {
        if(strcmp(find, recorre->info.username)==0){
            
        }
    }
}

void countAll(struct tipoNodo *primero){
    struct tipoNodo *recorre=primero;
    int publicaciones=0;
    char user[30];
   
    
    //Recorro toda la lista para contar todas las publicaciones, ya que no me pide las publicaciones de cada usuario
    if(primero!=NULL){
        while (recorre!=NULL) {
            publicaciones++;
            recorre=recorre->next;
        }
        printf("Hay un total de %d publicaciones",publicaciones);
    }else{
        printf("\n*LA LISTA ESTA VACIA*");
    }
    
    //Ahora voy a contar todos los usuarios únicos que haya
    
}
;
