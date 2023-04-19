#include <stdio.h>
#include <string.h>

#define MAX_USUARIOS 30
#define MAX_MENSAJES 20
#define MAX_CARACTERES 30

struct datosMensaje{
    int numMensajes;
    char num[10];//esto es lo mismo que el num
    char text0[MAX_CARACTERES]; //contenido del mensaje
};
struct mensajes{
    struct datosMensaje mensaje[MAX_MENSAJES];
};
struct datosUsuario{
    char num[10]; //identificados con num de telefono
    int numEnviados;
    int numRecibidos;
    struct datosMensaje enviado[MAX_MENSAJES];
    struct datosMensaje recibido[MAX_MENSAJES];
};
int verifyUser (int numUsuarios, struct datosUsuario user[], char numFind[]);
void addUser(int *numUsuarios, struct datosUsuario user[]);
void showUsers(int numUsuarios, struct datosUsuario user[]);
void sendMessage(int numUsuarios, struct datosUsuario user[]);
void deleteUser(int *numUsuarios, struct datosUsuario user[]);
int main() {
    int opt=0; //selector de mi menu
    int numUser=0;
    struct datosUsuario users[MAX_USUARIOS];

    do {
        printf("MENU\n");
        printf("--------\n");
        printf("\t1) Aniadir un nuevo usuario\n");
        printf("\t2) Enviar un mensaje\n");
        printf("\t3) Eliminar usuario\n");
        printf("\t4) Mostrar todos los usuarios\n");
        printf("\t5) Salir del programa\n");
        printf("---->Selecciona una accion: ");

        scanf("%d", &opt);

        switch (opt) {
            case 1:
                addUser(&numUser, users);
                break;
            case 2:
                sendMessage(numUser,users);
                break;
            case 3:
                deleteUser(&numUser,users);
                break;
            case 4:
                showUsers(numUser,users);
                break;
            case 5:
                printf("Has salido del programa, hasta pronto!\n");
                break;
            default:
                printf("Introduce una opcion valida: ");

        }


    }while (opt != 5);
    return 0;
}
int verifyUser (int numUsuarios, struct datosUsuario user[], char numFind[]){
    for (int i = 0; i < numUsuarios; ++i) {
       if(strcmp(user[i].num,numFind)==0){    //la busqueda coincide
           return i;
       }
    }
    return -1;  //si no encuentra el número responderá -1
}

void addUser(int *numUsuarios, struct datosUsuario user[]){
    char numFind[10];

    if(*numUsuarios<MAX_USUARIOS){
        printf("Introduce un número de teléfono: ");
        fpurge(stdin);
        scanf("%s", numFind); //Voy a guardar en la posición, pero todavía no hago numUsuarios++
        int posUser=verifyUser(*numUsuarios, user, numFind);
        if(posUser==-1){
           // printf("\nEl usuario no está registrado todavía\n");
            strcpy(user[*numUsuarios].num,numFind);
            printf("\tEl usuario se ha registrado correctamente\n");
            user[*numUsuarios].numRecibidos=0;
            user[*numUsuarios].numEnviados=0;
          /*  printf("El numero de mensajes enviados: %d\n",user[*numUsuarios].numRecibidos);
            printf("El numero de mensajes recibidos: %d\n",user[*numUsuarios].numEnviados);*/

            (*numUsuarios)++;
        }else{
            printf("\nEl usuario ya está registrado \n");
        }
    }
}
void showUsers(int numUsuarios, struct datosUsuario user[]){
    for (int i = 0; i <numUsuarios ; ++i) {
        printf("\tUser %d) %s\n", i+1,user[i].num);
        printf("\t\tSus mensajes enviados:\n");

        for (int j = 0; j < user[i].numEnviados; ++j) {
            printf("\t\t%s\n",user[i].enviado[j].text0);
        }
        printf("\t\tSus mensajes recibidos:\n");

        for (int j = 0; j < user[i].numRecibidos; ++j) {
            printf("\t\t%s\n",user[i].recibido[j].text0);
        }
    }
}
void sendMessage(int numUsuarios, struct datosUsuario user[]){
    char numFind[10];
    char numFind2[10];

    int posUser=0;
    int posUser2=0;

    printf("Introduce tu número de teléfono: ");
    fpurge(stdin);
    scanf("%s", numFind); //Voy a guardar en la posición, pero todavía no hago numUsuarios++
    posUser=verifyUser(numUsuarios,user,numFind);

    if(user[posUser].numEnviados> MAX_MENSAJES ){
            printf("\t***Has enviado el máximo de mensajes***\n");
            return;
        }else if(posUser ==-1){
        printf("***Usuario no encontrado***\n");
        return;
        }
    printf("Introduce el número de teléfono destinatario: ");
    fpurge(stdin);
    scanf("%s", numFind2);
    posUser2=verifyUser(numUsuarios,user,numFind2);
    if(user[posUser2].numRecibidos> MAX_MENSAJES ){
            printf("\t***El usuario ha recibido el máximo de mensajes: %d***\n", user[posUser2].numRecibidos);
            return;
        }else if(posUser2 ==-1){
        printf("***Usuario no encontrado***\n");
        return;
        }
    printf("Introduce tu mensaje (%d caracteres maximo): ",MAX_CARACTERES);
    fpurge(stdin);
    scanf("%[^\n]",user[posUser].enviado[user[posUser].numEnviados].text0);;

    strcpy(user[posUser2].recibido[user[posUser2].numRecibidos].text0, user[posUser].enviado[user[posUser].numEnviados].text0);
    (user[posUser].numEnviados)++;
    (user[posUser2].numRecibidos)++;
    printf("\tSe ha enviado tu mensaje correctamente\n");

}
void deleteUser(int *numUsuarios, struct datosUsuario user[]){
    char deleteUser[10];
    printf("\tQué usuario quieres eliminar? : ");
    scanf("%s",deleteUser);
    int posUser=verifyUser(*numUsuarios,user,deleteUser);
    if(posUser == -1){
        printf("\t El usuario no existe\n");
    }else{
        user[*numUsuarios-1]=user[posUser];

        (*numUsuarios)--;
        printf("**El usuario fue eliminado correctamente**\n");
    }

}
