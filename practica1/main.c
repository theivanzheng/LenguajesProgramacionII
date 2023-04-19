#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct usuario{
    char mail[30];
    char contrasena[16];
};

struct tipoNodo{
    struct usuario informacion;
    struct usuario *siguiente;
};

struct tipoNodo * comprobar (struct tipoNodo *primero,char mailNuevo[]);
void addInfo (struct tipoNodo **primero, char mailNuevo[]);
void visualizarLista(struct tipoNodo *primero);
void modificarCorreo(struct tipoNodo *primero);

int main() {
    int opc;
    char mailNuevo[30];
    struct usuario *primero = NULL;

    do {
        printf("MENU");
        printf("\n---------------------------");
        printf("\n\t1.- Registrar un nuevo usuario");
        printf("\n\t2.- Cambiar contrasena");
        printf("\n\t3.- Visualizar toda la lista");
        printf("\n\t4.- Dar de baja un usuario");
        printf("\n\t0.- Salir");
        printf("\nIntroduce una opción para el menu->  ");
        scanf("%d", &opc);

        switch (opc) {
            case 1:
                printf("\tIntroduce el nuevo mail");
                scanf("%s", mailNuevo);

                if (comprobar(primero, mailNuevo) == NULL) {
                    addInfo(&primero, mailNuevo);
                }
                break;
            case 2:
                modificarCorreo(primero);
                break;
            case 3:
                visualizarLista(primero);
                break;
            case 4:
                break;
            case 0:
                printf("\n**HAS SALIDO DEL PROGRAMA**");
                break;
        }
    }while (opc != 0);
    return 0;
}

struct tipoNodo * comprobar (struct tipoNodo *primero,char mailNuevo[]){
    int valor = 0;
    struct  tipoNodo *recorre = primero;
    //comprabación si hay cosas
    if (primero == NULL){
        printf("\tLa lista se encuentra vacia");
        return NULL;
    }
    //comparamos con los otros
    while (recorre != NULL){
        if (strcmp(recorre->informacion.mail, mailNuevo)==0){
            return  recorre;
        }
        recorre = recorre->siguiente;
    }
    return NULL;
}

void addInfo (struct tipoNodo **primero, char mailNuevo[]) {
    struct tipoNodo *nuevo;

    //1 reservo memoria
    nuevo = (struct tipoNodo *) malloc(sizeof(struct tipoNodo));
    if (nuevo == NULL) {
        printf("\n **ERROR EN MEMORIA**");
        return;
    }
    //2 relleno informacion
    strcpy(nuevo->informacion.mail, mailNuevo);
    printf("\n\tTu correo: %s", nuevo->informacion.mail);
    printf("\n\tintroduce tu contrasena-> ");
    scanf("%s", nuevo->informacion.contrasena);

    //3 conecto con la lista
    nuevo->siguiente = *primero;
    *primero = nuevo;
}

void visualizarLista(struct tipoNodo *primero){
    struct tipoNodo *recorre = primero;
    if (primero == NULL){
        printf("\n\t La lista está vacia");
        return;
    }
    while(recorre != NULL){
        printf("\n\t Correo: %s, Contrasenna: %s",recorre->informacion.mail, recorre->informacion.contrasena);
        recorre = recorre->siguiente;
    }
}

void modificarCorreo(struct tipoNodo *primero){
    struct tipoNodo *modificado;
    struct usuario usuario;

    printf("\n\t Introduce el correo de la contraseña a modificar-> ");
    scanf("%s", usuario.mail);

    modificado = comprobar(primero, &usuario);

    if(modificado != NULL){
        printf("\n\t Introduce su actual contraseña-> ");
        scanf("%s", modificado->informacion.mail);
        printf("\n\t La nueva contraseña-> ");
        scanf("%s", modificado->informacion.contrasena);
    }else{
        printf("\nNo se ha podido cambiar la contrasenna \n");
    }
}