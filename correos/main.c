#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct tipoInfo{
    char mail[30];
    char pass[16];
};
struct nodo{
    struct tipoInfo info;
    struct nodo *siguiente; //este es un puntero a nodo
};
struct nodo comprobar(struct nodo *primero,char mail[]);
void addInfo(struct nodo **primero,char newMail[]);
int menu(void);

int main(){
    char newMail[30];
    int optMenu=menu();
    struct nodo *primero;
    switch(optMenu){
        case 1:
            printf("\t\nIntroduce un correo electrónico: ");
            scanf("%s",newMail);
            addInfo(primero,newMail);
            break;
        case 2:
            break;
        case 3:
            break;
    }

    return 0;
}

int menu(void){
    int opc;
    do{
        printf("MENU");
        printf("\n\t 1.- Registrar usuario");
        printf("\n\t 2.- Cambiar contraseña");
        printf("\n\t 3.- Visualizar usuarios");
        printf("\n\t 4.- Darse de baja");
        printf("\n\t 0.- Salir");

        scanf("%d",&opc);
    }while(opc!=0);
    return opc;
}
struct nodo comprobar(struct nodo *primero,char mail[]){
    struct nodo *run=primero;   //run es un puntero que me indica donde apunta primero
    while (run!=NULL){  //Si recorre es NULL es porque todavía no hay nada en lista
        if(strcmp(mail,run->info.mail)==0){//Si el mail es igual
            return *run;
        }else{
            printf("\n\tEse correo no ha sido utilizado todavía");
        }
        run = run->siguiente;
    }
    printf("**ha llegado al final de la lista**\n");
    return *run; //nos devuelve la información almacenada en primero
}

void addInfo(struct nodo **primero,char newMail[]){
    struct tipoNodo *nuevo;
    //1.- Reservo memoria para la información que no tengo
    nuevo = (struct tipoNodo*) malloc(sizeof(struct tipoNodo));
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
}
