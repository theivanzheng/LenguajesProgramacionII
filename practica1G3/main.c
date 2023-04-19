#include <stdio.h>
#include <stdlib.h>
struct datosPoint{
    double x;
    double y;
};
void modifyValue(int *ptr);
void inicializarPtro(struct datosPoint **ptro);
void inicializarPunto(struct datosPoint *ptro);
void visualizar(int *ptro); //prototipo
int main() {
    int number;
    int *ptroInt;
    struct datosPoint point;
    struct datosPoint *ptroPoint;

    printf("EJERCICIO 1: \n");
    printf("\tLa memoria utilizada por number: %ld bytes\n",sizeof(number));
    printf("\tLa memoria utilizada por *ptroInt (de number): %ld bytes\n",sizeof(ptroInt));
    printf("\tLa memoria utilizada por point: %ld bytes\n",sizeof (point));
    printf("\tLa memoria utilizada por ptroPoint: %ld bytes\n",sizeof (ptroInt));

    /*
     * a) La variable que ocupa más es la de point, una varibale tipo estructura que contiene 2 int
     *    En cambio los punteros sólo tienen que guardar una dirección de memoria, así que ocupan lo mismo.
     *    Y después la int sólo va a contener valores que ocupen hasta 4 bytes
     * b) Sí, una variable double más o menos utiliza el doble de memoria que una variable int
     * c) No sabría cuanto ocupa *ptroInt en bytes, pero sí que se puede deducir que todos los punteros de este
     *    tipo ocupan lo mismo, ya que sólo tienen que guardar una dirección de memoria, por lo que por regla
     *    general sería de 4 bytes, el tamaño más pequeño.
     */


    printf("EJERCICIO 2: \n");
    number=100;
    ptroInt=&number;
    *ptroInt=33;
    printf("\tEl valor de number: %d\n",number);
    printf("\tLa dirección de number: %p\n",number);
    printf("\tEl valor de *ptroInt: %d\n",*ptroInt);
    printf("\tLa dirección que apunta *ptroInt: %p\n",*ptroInt);
    /*
     * El valor se ha cambiado ya que uno está apuntando a la dirección de
     * almacenamiento del otro, entonces cuando cambias el valor de cualquiera de
     * los dos el otro tambien se verá afectado. Y tienen la misma dirección de
     * memoria porque están apuntando a la misma dirección, que es lo que hemos
     * hecho con el puntero
     */
    printf("EJERCICIO 3: \n");
    printf("\tEl valor de number es: %d\n",number);
    modifyValue(ptroInt);
    printf("\tEl valor de number es: %d\n",number);
    printf("\tEl valor de number es: %d\n",number);
    /*
     * Dado que ptroInt apunta al mismo lugar de memoria que num, el valor almacenado en ese
     * lugar de memoria se modificará, y por lo tanto el valor de num también se modificará. Por
     * eso, cuando imprimimos el valor de num después de la llamada, veremos el nuevo valor que
     * el usuario ingresó, en lugar del valor original de 33.
     */
    printf("EJERCICIO 4: \n");
    //printf("\tLa dirección que alamacena *ptroInt: %p\n",ptroInt);
    inicializarPtro(&ptroPoint);
    printf("\tLa dirección que alamacena *ptroInt: %p\n",ptroPoint);
    /*
     * No podría, ya que apunta a la "nada" entonces no puedes meterle un valor
     * a un sitio que no sabes donde está
     * (No es la nada, es peor que nada)
     */

    printf("EJERCICIO 5: \n");
    inicializarPunto(&point);
    ptroPoint=(struct datosPoint *)malloc(sizeof(struct datosPoint));
    *ptroPoint=point;
    printf("\tEl valor x de point: %lf\n",point.x);
    printf("\tEl valor y de point: %lf\n",point.y);
    printf("\tEl valor x de ptroPoint: %lf\n",ptroPoint->x);
    printf("\tEl valor y de ptroPoint: %lf\n",ptroPoint->y);
    /*
     * los valores se han modificado, ya que hemos apuntado nuestro putnero a la dirección
     * de la variable point, entonces cada vez que queramos imprimir un valor de ptroPoint va a dirigirnos
     * a la variable point (para entendernos). Entonces si modificamos cualquier valor de point, se va a
     * mostrar en ptroPoint, que simplemente nos saca una "proyección" de lo que hay en point.
     */

   printf("EJERCICIO 6: \n");
    int i;
    int a[10] = {0,1,2,3,4,5,6,7,8,9};
    int *ptro;
    ptro = a;
    /*
     * No da ningún error, ya que la asignación está bien hecha, estoy haciendo que mi puntero
     * apunte hacia "a". En caso de haber puesto *ptr la cosa habría sido diferente
     *
     */
    printf("\tLa dirección que almacena a: %p\n",a);
    printf("\tLa dirección que almacena *ptro: %p\n",ptro);

    /*
     * Aquí obtengo que la dirección es la misma, porque he declarado que ptro apunte hacia a
     * entonces te va a salir que la dirección que almacena ptro es la de a.
     */
    printf("\n a es %p",a);
    /*
     * Aquí nos dice la dirección de memoria en la que tenemos a, no nos va a mostrar
     * el contenido que tiene, para ello tendríamos que hacerloa  través de un bucle for
     * recorriendo cada una de las posiciones.
     */

    /*
     * ANTES DE RECORRER EL CÓDIGO:
     * -----------------------------
     * Lo que veo a primera vista es un bucle for que nos va a mostrar la cadena almacenada en "a"
     * Y en el siguiente for tenemos otra forma de recorrer el bucle form, que por cada iteración
     * incrementa i y como ptro apunta a "a" el bucle va a mostrar cada una de las posiciones
     * de a incrementando hasta que se deje de cumplir la condición dada en el bucle
     */
    printf("\n\n");
        for (i=0;i<10;i++) {
            printf("[%d]", ptro[i]); //acceso con sintaxis de array
            }
            printf("\n");

          for (i = 0; i < 10; i++, ptro++) {
            printf("[%d]", *ptro);
            }
            printf("\n");


      /*
       * Después de ejecutar podemos ver que el valor de ptro SÍ cambia
       * ya que por cada vez que pasamos por el segundo bucle for, nos movemos una posición
       * más adelante de la inicial, llegando al final a una posición de 10*4 bytes por delante
       * de la posición original
       */
    printf("\nDirección ptro después de los for: %p \n",ptro);

    visualizar(ptro);
      /*
       *Aquí puede parecer que da error, pero no, ya que como hemos visto antes la dirección
       * original en la que conteníamos la información donde apuntaba el puntero ya no existe,
       * ya que hemos movido la posición en memoria de nuestro puntero
       */
    printf("Dirección ptro después de la función: %p \n",ptro);
    return 0;
}

void modifyValue(int *ptr) {
    printf("\tintroduce un nuevo valor: ");
    scanf("%d", ptr);
}
void inicializarPtro(struct datosPoint **ptro){
    *ptro=NULL;
}
void inicializarPunto(struct datosPoint *ptro){
    printf("\tIntroduce un valor para X");
    scanf("%lf",&ptro->x);
    printf("\tIntroduce un valor para Y");
    scanf("%lf",&ptro->y);
}
void visualizar(int *ptro){
    int i;
    printf("Dirección ptro dentro de la función: %p\n",ptro);
    printf("\t");
    for (i=0;i<10;i++,ptro++){ //aritmética de punteros
        printf("[%d]",*ptro);
    }
    printf("\n");
}
