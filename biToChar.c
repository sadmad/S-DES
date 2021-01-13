#include <stdio.h>
#include <stdlib.h>

int main(){
    char Binary[]="01100001";
    int x;
    x=strtol(Binary, (char **)NULL, 2);
    printf("%c\n", x);
}
