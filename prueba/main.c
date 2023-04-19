#include <stdio.h>
#include <stdlib.h>

struct tipoInfo{ int key;
    double value; };
struct tipoNodo{
    struct tipoInfo information; struct tipoNodo *siguiente;
};
int main() {
    struct tipoNodo *primero = NULL; //lista vacía
  return 0;
}