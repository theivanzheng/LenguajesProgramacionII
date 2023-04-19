#include <stdio.h>
#include <string.h>
#define MAX_USUARIOS 30
#define MAX_MENSAJES 20

struct datosMensaje{
    char telefono[10];
    char text[30];
};

struct datosMensajes{
    int numMensajes;
    struct datosMensaje mensaje[MAX_MENSAJES];
};
struct datosUsuario{
    char telefono[10];
    struct datosMensajes mensajesEnviados[20];
    struct datosMensajes mensajesRecibidos[20];
};
//Opcion 1
void addUsuario(int *numUsuarios, struct datosUsuario usuario[]);
int findUser(int numUsuarios, struct datosUsuario usuario[], char telefonoBuscar[]);
/*Esto me va a devolver un número negativo en caso de que no encuentre el teléfono*/

//Opcion 2
void addMensaje(struct datosMensaje *mensajes, struct datosMensaje mensaje,int numUsuarios, struct datosUsuario usuario[]);
void sendMensaje(int numUsuarios, struct datosUsuario usuarios[]);

//Opcion 3
void deleteUser(int *numUsuarios, struct datosUsuario usuarios[]);

//Opcion 4
void printInfor(int numUsuarios, struct datosUsuario usuarios[]);
void printMessage(struct datosMensajes mensajes);

//Opcion 6
void mostrarTodo(int numUsuarios, struct datosUsuario usuario[]);

int main() {
    int numeroUsuarios=0;
    int numMensajes=0;
    int opt=0;
    struct datosUsuario usuarios[MAX_USUARIOS];
    struct datosMensaje mensaje[MAX_MENSAJES];
    struct datosMensajes mensajes[100];

    printf("PRACTICA 0\n");


    do{
        printf("Menu de opciones\n"
               "\t1) Aniadir usuario\n \t2) Enviar mensaje\n \t6) Mostrar Todo ");
        scanf("%d",&opt);
        switch(opt) {
            case 1:
                addUsuario(&numeroUsuarios,usuarios);
                break;
            case 2:
                addMensaje(&mensajes,mensaje[MAX_MENSAJES]);
            case 5:
                printf("Has salido del programa");
                break;
            case 6:
                mostrarTodo(numeroUsuarios,usuarios);
        }
    }while(opt != 5);

    return 0;
}
int findUser(int numUsuarios, struct datosUsuario usuario[], char telefonoBuscar[]){
    /*printf("Entro en find user\n");
    printf("telefonoBuscar: %s\n", telefonoBuscar);*/

    for (int i = 0; i < numUsuarios; ++i) {
        if( strcmp(telefonoBuscar,usuario[i].telefono) == 0){
           // printf("Son iguales\n");
            return i;
        }
    }
    return -1;
}
void addUsuario(int *numUsuarios, struct datosUsuario usuario[]){
   // printf("Entro en addUsuario y numusuario = %d\n",*numUsuarios);
    if(*numUsuarios < (MAX_USUARIOS-1)){
        printf("\tIntroduce un número de teléfono: ");
        fpurge(stdin);
        scanf("%s",&usuario[*numUsuarios].telefono);
        if( findUser(*numUsuarios, usuario,usuario[*numUsuarios].telefono) == -1){
            //printf("el valor de find user %d\n",findUser(numUsuarios, usuario,usuario[*numUsuarios].telefono));
            printf("\tUsuario añadido correctamente\n");
            usuario[*numUsuarios].mensajesEnviados.numMensajes=0;
            usuario[*numUsuarios].mensajesRecibidos.numMensajes=0;

            *numUsuarios=*numUsuarios+1;
        }else{
            //printf("el valor de find user %d\n",findUser(numUsuarios, usuario,usuario[*numUsuarios].telefono));
            printf("El usuario con el teléfono %s ya existe\n",usuario[*numUsuarios].telefono);
        }
    }else{
        printf("Ya se ha alcanzado el máximo de ususarios\n");
    }
}
void mostrarTodo(int numUsuarios, struct datosUsuario usuario[]){
    printf("El numero de usuarios: %d\n",numUsuarios);
    printf("Lista de numeros registrados: \n");
    for (int i = 0; i < numUsuarios; ++i) {
        printf("\t%s\n",usuario[i].telefono);
    }
}
void sendMensaje(int numUsuarios, struct datosUsuario usuarios[]){

}

void addMensaje(struct datosMensaje *mensajes, struct datosMensaje mensaje,int numUsuarios, struct datosUsuario usuario[]){
    char recibidor[10];
    char emisor[10];
    int numMensajesEmisor=0;
    printf("introduce tu teléfono para enviar el mensaje: ");
    scanf("%s", &emisor);
    int posUsuario=findUser(numUsuarios, usuario,emisor);
    //comprueba y saca la posicion de mi usuario
        if(posUsuario == -1){
            printf("El usuario %s no se ha encontrado\n", emisor);
            return;
        }else if( usuario[posUsuario].mensajesEnviados.numMensajes < MAX_MENSAJES){
            printf("El usuario ha superado el máximo de mensajes enviados\n");
            return;
        }
    printf("introduce el mensaje: ");
    scanf("%[^\n]", usuario[posUsuario].mensajesEnviados[numMensajesEmisor].mensaje);
}
