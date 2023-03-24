#include <stdlib.h>
#include <stdio.h>

int main(int argc, const char * argv[]) {
    int age = 5;
    printf("The direction of age: %p\n", &age);

    
    int* ptr = &age;
    printf("The direction of ptr: %p\n",ptr);
    return 0;
}
