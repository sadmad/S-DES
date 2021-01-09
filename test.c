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

const int p8[] = {6, 3, 7, 4, 8, 5, 10, 9};        //8 bits of permuted input
const int p1[] = {3, 5, 2, 7, 4, 10, 1, 9, 8, 6};  //10 bit of permuted input
const int ip[] = {2, 6, 3, 1, 4, 8, 5, 7};         //inverse permutation
const int ipRev[] = {4, 1, 3 , 5, 7, 2, 8, 6};     //reverse of inverse permutation
const int sw[] = {4, 5, 6, 7, 0, 1, 2, 3};         //sw used in the fk function2
const int EP[8] = {4, 1, 2, 3, 2, 3, 4, 1};
const int P4[4] ={2, 4, 3, 1};
int n = 0;                                         //used as a permanent holder for LS-2
int i;                                             //use for for loops
char inputKey[11] = {'1','0','1','0','0','0','0','0','1','0','\0'};                                 //The variable for storing the 10 bit input key from the user
char temp[11];                                     //is a temporary var for all of our calculation 
char temp8[8];
char temp4[5];                                     //8bits temo var 
char ext[4];                                       //extra variable for permutation
char k1[9];                                        //first 8 bit key - I added a null at the end of the key
char k2[9];                                        //second 8 bit key
char plainText[9] = {'0','1','1','1','0','0','1','0', '\0'};                                 //the plaintext
char l[5];		
char r[5];
char swR[5];
char lXor[5];
char rXor[5];
int S0[4][4] = {{1, 0, 3, 2}, {3, 2, 1, 0}, {0, 2, 1, 3}, {3, 1, 3, 2}};                                   
int S1[4][4] = {{0, 1, 2, 3}, {2, 0, 1, 3}, {3, 0, 1, 0}, {2, 1, 0, 3}};
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

void initialPermutation();

void devideLeftRight();

void expandpermutateR();

void XOR();

void devideLeftRightXor();

int binaryToDecimal();

void fk();

void decToBi();

void XOR4();

void switchHalf();

//-----------------main------------------
int main(){

    //get the inputKey from user
    //getInput();

    
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
    //plaintextInput();
    
    printf("Your input was: ");
    puts(plainText);

    //initial Permutation
    initialPermutation();

    devideLeftRight();
    printf("--------------------------------------fk1---------------------------------------");
    fk(1);

    //step 7
    XOR4();
    printf("--------------------------------------fk2---------------------------------------");
    //step 8
    switchHalf();

    fk(2);
    XOR4();

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

void initialPermutation(){

    for(i=0;i<8;++i){
        temp8[i] = plainText[ip[i]-1];
    };
    temp8[8] = '\0';
    printf("Plain text after initial Permutation: ");
    puts(temp8);
    for(i=0;i<8;++i){
        
    };

};

void devideLeftRight(){
    int j=4;
    for(i=0;i<8;++i){
        if(i<4){
            l[i] = temp8[i];
        }else{
            n = i - j;
            r[n] = temp8[i];
        };
    };

    l[4] = '\0';
    r[4] = '\0';

    printf("Left: ");
    puts(l);

    printf("Right: ");
    puts(r);
    
};

void expandpermutateR(char *str){

    for(i=0;i<8;++i){
        temp8[i] = str[EP[i] - 1];
    };
    temp8[8] = '\0';
    printf("EP-R: ");
    puts(temp8);

};

void XOR(char *k, int *ki){
    
    if(i==1){
        printf("k1: ");
        puts(k1);
    }else{
        printf("k2: ");
        puts(k2);
    }

    for(i=0;i<8;++i){
        if(k[i] == temp8[i])
            temp8[i] = '0';
        else
            temp8[i] = '1';
        
        
    }
    temp8[8] = '\0';
    printf("XOR%i: ", i);
    puts(temp8);
};

void devideLeftRightXor(){
    int j=4;
    for(i=0;i<8;++i){
        if(i<4){
            lXor[i] = temp8[i];
        }else{
            n = i - j;
            rXor[n] = temp8[i];
        };
    };

    lXor[4] = '\0';
    rXor[4] = '\0';

    printf("Left of XOR: ");
    puts(lXor);

    printf("Right of XOR: ");
    puts(rXor);
    
};

/*
int binaryToDecimal(int num){
    
    int dec_value = 0;
 
    // Initializing base value to 1, i.e 2^0
    int base = 1;
 
    int temp = num;
    while (temp) {
        int last_digit = temp % 10;
        temp = temp / 10;
 
        dec_value += last_digit * base;
 
        base = base * 2;
    };
 
    return dec_value;
};
*/
int biToStr(char *n){

    if( strcmp(n, "00") == 0) return 0;
    else if( strcmp(n, "01") == 0) return 1;
    else if( strcmp(n, "10") == 0) return 2;
    else  return 3;

    return -1;
};


void s0Box(){

    char num[3];
    int pos[2]; //pos[o is the row and pos[1] is the col of S0_box

    //1-4
    num[0] = lXor[0];
    num[1] = lXor[3];
    num[2] = '\0';

    printf("lxor 1-4: ");
    puts(num);

    
    pos[0] = biToStr(num);
    printf("row in S0: %i\n", pos[0]);
    
    //2-3
    num[0] = lXor[1];
    num[1] = lXor[2];
    num[2] = '\0';

    printf("lxor 2-3: ");
    puts(num);
    
    pos[1] = biToStr(num);
    printf("Col in S0: %i\n", pos[1]);

    ext[0] = S0[pos[0]][pos[1]];
    printf("S0: %d\n", ext[0]);
    //printf("test S0: %d\n", S0[0][3]);

    
};

void s1Box(){

    char num[3];
    int pos[2]; //pos[o is the row and pos[1] is the col of S0_box

    //1-4
    num[0] = rXor[0];
    num[1] = rXor[3];
    num[2] = '\0';

    printf("rxor 1-4: ");
    puts(num);

    
    pos[0] = biToStr(num);
    printf("row in S1: %i\n", pos[0]);
    
    //2-3
    num[0] = rXor[1];
    num[1] = rXor[2];
    num[2] = '\0';

    printf("rxor 2-3: ");
    puts(num);
    
    pos[1] = biToStr(num);
    printf("Col in S1: %i\n", pos[1]);

    ext[1] = S1[pos[0]][pos[1]];
    printf("S1: %d\n", ext[1]);
    //printf("test S0: %d\n", S0[0][3]);
    decToBi();

};

void decToBi(){
    printf("S0: %i\n", ext[0]);
    if(ext[0] == 0){
        temp4[0] = '0';
        temp4[1] = '0';
    }else if (ext[0] == 1){
        temp4[0] = '0';
        temp4[1] = '1';
    }else if (ext[0] == 2){
        temp4[0] = '1';
        temp4[1] = '0';
    }else{
        temp4[0] = '1';
        temp4[1] = '1';
    }

    if(ext[1] == 0){
        temp4[2] = '0';
        temp4[3] = '0';
    }else if (ext[1] == 1){
        temp4[2] = '0';
        temp4[3] = '1';
    }else if (ext[1] == 2){
        temp4[2] = '1';
        temp4[3] = '0';
    }else{
        temp4[2] = '1';
        temp4[3] = '1';
    }
    temp4[4] = '\0';

    printf("S-Box: ");
    puts(temp4);
}

void p4(){

    printf("P4: ");
    for(i=0;i<4;++i){
        ext[i] = temp4[P4[i]-1];      
    }
    for(i=0;i<4;++i){
        temp4[i] = ext[i];      
    }
    temp4[4] = '\0';
    printf("Ressult: ");
    puts(temp4);

};

void fk(int *ki){
     
    //mapping---
    //leftnright
   

    //Expand and permutate R using E/P
    expandpermutateR(r);

    //Xor ----
    if(ki==1) XOR(k1, 1); 
    else XOR(k2, 2);
       

    //devide the result of XOR to left and right 4 bits
    devideLeftRightXor();
    
    //get the position in S0
    s0Box();

    //get the position in S1
    s1Box();

    p4();

};

void XOR4(){

    for(i=0;i<4;++i){
        if(temp4[i] == l[i])
            temp4[i] = '0';
        else
            temp4[i] = '1';   
    }
    temp4[4] = '\0';
    printf("XOR with l: ");
    puts(temp4);
};

void switchHalf(){
    
    
    for(i=0;i<4;++i){
        l[i] = r[i];
    }
    l[4] = '\0';

    printf("SW-L: ");
    puts(l);

    for(i=0;i<4;++i){
        swR[i] = temp4[i];
    }
    swR[4] = '\0';

    printf("SW-R: ");
    puts(swR);

}

