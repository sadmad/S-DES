#include <stdio.h>
#include <string.h>

int main(){
    char msg[20];
    int len;
    char bichar[10][9];

    printf("Enter your char: ");
    scanf("%s", msg);

    len = strlen(msg);
    
    for(int i=0;i<len;++i){
        for(int j=7; j>=0; --j)
            bichar[i][j] = (msg[i] & (1 << j)) ? '1' : '0';
        
        bichar[i][8] = '/0';
        puts(bichar[i]);
    }
}