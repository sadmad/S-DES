#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double *temp;
char a = 'a';
char biTemp[8][9];
int main(){
    int i = 0;
    int j = 0;
    temp = "asaa";
    printf("\n");

    for (temp; *temp; ++temp){
        
        int bit_index;

        for (bit_index = 7; bit_index >= 0; --bit_index){

            int bit = *temp >> bit_index & 1;
            printf("%d-", bit);
            biTemp[i][j] = bit + '0';
            printf("%c\n", biTemp[i][j]);
            ++j;
        }
        biTemp[i][8] = '\0'; 
        ++i;
        printf("\n");
    }
    int i2 = i;
    int j2 = j;
    for(i=0;i<i2;++i){
        printf("Binary of ascii code %i: ", i);
        for(j=0;j<j2;++j){
            printf("%c", biTemp[i][j]);
        }   
        printf("\n");
    }
}





