/* 

    Approach to Simplified Data Encryption Standard (S-DES)
    Fallowed the instruction by Prof. William Stallings
    You find the pdf here:
    http://mercury.webster.edu/aleshunas/COSC%205130/G-SDES.pdf


*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//initializing the variables
//--------------------------

int p8[] = {6, 3, 7, 4, 8, 5, 10, 9};        //8 bits of permuted input
int p1[] = {3, 5, 2, 7, 4, 10, 1, 9, 8, 6};  //10 bit of permuted input
int ip[] = {2, 6, 3, 1, 4, 8, 5, 7};         //inverse permutation
int ipRev[] = {4, 1, 3 , 5, 7, 2, 8, 6};     //reverse of inverse permutation
int n = 0;                                   //used as a permanent holder for LS-2
int i;                                       //use for for loops
char inputKey[11];                           //The variable for storing the 10 bit input key from the user
char temp[11];                               //is a temporary var for all of our calculation 
char ext[2];                                 //extra variable for permutation
char k1[9];                                  //first 8 bit key - I added a null at the end of the key
char k2[9];                                  //second 8 bit key
char plainText[9];                           //the plaintext      

//............................


//get the input key from user
void getInput();

//function for applying P1
void appllyP1();

//function for shifting the bits LS-1
void LS1();

//function for applying P8
void P8K1();

//function for shifting 2 bits to left LS-2
void LS2();

//function for applying P8 on k2
void P8K2();

//just for testing k2
void printK2();

//get the plain text from user 
void plaintextInput();
//-----------------main------------------
int main(){

    //get the inputKey from user
    getInput();
    
    //starting to build k1
    //applying p1
    appllyP1();

    //LS-1
    LS1();

    //applying P8
    P8K1();

    //starting to build k2
    //Performing LS2
    LS2();
    
    //applying P8 on K2
    P8K2();
    
    //start to encript
    plaintextInput();
    printf("Your input was: ");
    puts(plainText);

    return 0;
    
};
//---------------end-of-main--------------

void getInput () {

    printf("Please enter 10 bits as key: ");
    /*
    printf("Please enter 10 bits as input it will ask you a bit eachtime(10 times): ");
    for(i = 0; i < 10; ++i){      
        
        printf("%i\n", i);
        scanf("%i", &n);
        if(n == 1 || n == 0) { 
            inputKey[i] = n + '0';
            
            printf("Please enter the next bit(it will be ");
            if(i==0){
                printf("second bit): ");
            }else if(i=1){ 
                printf("third bit): ");
            }else{ 
                printf("%ith bit): ", i);
            };
            
        }else{
            printf("Please choose between 0 and 1!!!");
            i--;
        };

    };
    */
    scanf("%s", &inputKey);
    inputKey[10] = '\0';
    printf("input: ");
    puts(inputKey);
    
};

void appllyP1 (){

    for(i=0 ; i<=9; ++i){
        temp[i] = inputKey[p1[i] - 1];
    };
    //add a null bit at the end of temp
    temp[10] = '\0';
   
    printf("P1: ");
    puts(temp);
    printf("len: %i\n",  strlen(temp));
};

void LS1(){

    //first half
    for(i=0; i<5; ++i){

        if( i == 0 ){
            ext[0] = temp[0];
            temp[i]=temp[i+1];
        }else if( i == 4 ){
            temp[i] = ext[0];
        }else{
            temp[i]=temp[i+1];
        }
        
    };

    //second half
    for(i=5; i<10; ++i){

        if(i==5){
            ext[0] = temp[5];
            temp[i]=temp[i+1];
        }else if( i == 9 ){
            temp[i] = ext[0];
        }else{
            temp[i]=temp[i+1];
        }  

    };

    printf("LS-1: ");
    puts(temp);

};

void P8K1(){
    
    printf("P8: ");
    for (i = 0; i<8;++i) {
        if(i==7)
            printf("%d\n",p8[i]);
        else
            printf("%d", p8[i]);
    };

    for (i=0; i<8; i++) {
        n = p8[i];
        k1[i] = temp[n-1];
    };

    k1[8] = '\0';
    printf("k1: ");
    puts(k1);

};

void LS2(){

    //first half
    for(i=0; i<5; ++i){

        if( i == 0 ){
            ext[0] = temp[0];
            temp[i]=temp[i+2];
        }else if( i == 1 ){
            ext[1] = temp[i];
            temp[i]=temp[i+2];
        }else if( i == 3 ){
            temp[i] = ext[0];
        }else if( i == 4 ){
            temp[i] = ext[1];
        }else{
            temp[i]=temp[i+2];
        }
        
    };

    //second half
    for(i=5; i<10; ++i){

        if(i==5){
            ext[0] = temp[5];
            temp[i]=temp[i+2];
        }else if( i == 6 ){
            ext[1] = temp[6];
            temp[i]=temp[i+2];
        }else if( i == 8 ){
            temp[i] = ext[0];
        
        }else if( i == 9 ){
            temp[i] = ext[1];
        }else{
            temp[i]=temp[i+2];
        }  

    };

    printf("LS-2: %s\n", temp);
    printf("len: %i\n",  strlen(temp));

};

void P8K2(){

    for (i=0; i<8; ++i) {
        n = p8[i];
        k2[i] = temp[n-1];  
    };
    k2[8] = '\0';
    printf("k2: ");
    puts(k2);
};

void printK2(){
    printf("k2 just for test: ");
    puts(k2);
    printf("test 2: %s", k2);
};

void plaintextInput(){

    printf("Please enter the 8 bit plain text: ");
    scanf("%s", &plainText);
    plainText[8] = '\0';


};