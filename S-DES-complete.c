/* 

    Approach to Simplified Data Encryption Standard (S-DES)
    Fallowed the instruction by Prof. William Stallings
    You find the pdf here:
    http://mercury.webster.edu/aleshunas/COSC%205130/G-SDES.pdf

    You can use this examples for text the code:

    • Plaintext: 11010101; Key: 0111010001; Ciphertext: 01110011
    • Plaintext: 01001100; Key: 1111111111; Ciphertext: 00100010
    • Plaintext: 00000000; Key: 0000000000; Ciphertext: 11110000
    • Plaintext: 11111111; Key: 1111111111; Ciphertext: 00001111


*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>



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
int i;
int j;
int row;
int col;                                             //use for for loops
int len;
char inputKey[11];                                 //The variable for storing the 10 bit input key from the user
char temp[11];                                     //is a temporary var for all of our calculation 
char temp8[8];
char temp4[5];                                     //8bits temo var 
char ext[4];                                       //extra variable for permutation
char k1[9];                                        //first 8 bit key - I added a null at the end of the key
char k2[9];                                        //second 8 bit key
char plainText[200];
char binaryPlainText[200][8];
char cipherText[200][9];
char output[200][9];                                 //the plaintext                                 //the plaintext
char l[5];		
char r[5];
char swR[5];
char lXor[5];
char rXor[5];
int phase;
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

void divideLeftRight();

void expandpermutateR();

void XOR();

void divideLeftRightXor();

int binaryToDecimal();

void fk();

void decToBi();

void XOR4();

void switchHalf();

void combine();

void initialPermutationRev();

void enAndDecryption();

bool continueencrypt();

void plainTextToBi();
//-----------------main------------------

int main(){

    phase = 1;

    

    while(true){
        //get the inputKey from user
        getInput();

        //it will do the whole en-decryption
        enAndDecryption();
        enAndDecryption();
        
        printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
        printf("|                                                                   |\n");
        printf("|                              S-DES                                |\n");
        printf("|                                                                   |\n");
        printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
        printf("|                                                                   |\n");
        printf("|                       Text that you entered                       |\n");
        printf("|                                                                   |\n");
        printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
        printf("Plaintext: ");       
        puts(plainText);
        printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
        printf("|                                                                   |\n");
        printf("|                         Binary representation                     |\n");
        printf("|                                                                   |\n");
        printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
        for(i=0;i<len;++i){
            for(j=0;j<8;++j)
                printf("%c",binaryPlainText[i][j]);
            printf("\n");
        }
        printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
        printf("|                                                                   |\n");
        printf("|                            10 bit key was                         |\n");
        printf("|                                                                   |\n");
        printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
        puts(inputKey);
        printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
        printf("|                                                                   |\n");
        printf("|                            Ciphertext                             |\n");
        printf("|                                                                   |\n");
        printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
        for(i=0;i<len;++i)
            puts(cipherText[i]);
        printf("\nCiphertext: ");
        for(i=0;i<len;++i){
            char Binary[9];
            strcpy(Binary, cipherText[i]);
            //Binary[9] = '\0';
            int x, out;
            x=strtol(Binary, (char **)NULL, 2);
            out = x;
            printf("%c", out);
        }
        printf("\n");
        printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
        printf("|                                                                   |\n");
        printf("|                        decrypted plaintext                        |\n");
        printf("|                                                                   |\n");
        printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
        for(i=0;i<len;++i){
            char Binary[9];
            strcpy(Binary, output[i]);
            //Binary[9] = '\0';
            int x, out;
            x=strtol(Binary, (char **)NULL, 2);
            out = x;
            printf("%c", out);
        }
        printf("\n");
        printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
        
            
        //ask user if they want to continue the process
        bool again = continueencrypt();
        if(again){
            phase=1;
            continue;
        }else break;

    }
    

    return 0;
    
};

//---------------end-of-main--------------

void getInput () {

    printf("Please enter 10 bits as key: ");
    scanf("%s", &inputKey);
    inputKey[10] = '\0';
    
    printf("input: ");
    puts(inputKey);
    
    /*
    At first I wrote this code to get the key bit by bit, but it become pain in the ass in the procedure of debuging the code!
    I decided to keep it for future changes.
    -------------------------------------------------------------------------------------
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
    ---------------------------------------------------------------------------------------
    */
      
};

void enAndDecryption(){

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
    if(phase == 1){
        plaintextInput();
        len = strlen(plainText);
        printf("---------\n");
        for(row=0;row<len;++row){
            for(col=7; col>=0; --col)
                binaryPlainText[row][7-col] = (plainText[row] & (1 << col)) ? '1' : '0';
            binaryPlainText[row][8] = '\0';
            //printf("!!!!%c: ", plainText[row]);
            //puts(binaryPlainText[row]);

            //initial Permutation
            initialPermutation();
            divideLeftRight();
            fk(1);
            XOR4();
            switchHalf();
            fk(2);
            XOR4();
            combine();
            initialPermutationRev();
            //printf("------------------------------encription phase is done-------------------------------\n");
        }
        
    }else{
        //printf("The Ciphertext was: ");
        //puts(cipherText);
        for(row=0;row<len;++row){
            //initial Permutation
            initialPermutation();
            divideLeftRight();
            fk(2);
            XOR4();
            switchHalf();
            fk(1);
            XOR4();
            combine();
            initialPermutationRev();
            //printf("------------------------------decription phase is done-------------------------------\n");
            
        }
    }

   
    phase = phase == 1 ? 2 : 1;
    

}

void appllyP1 (){

    for(i=0 ; i<=9; ++i){
        temp[i] = inputKey[p1[i] - 1];
    };
    //add a null bit at the end of temp
    temp[10] = '\0';
   
    //printf("P1: ");
    //puts(temp);
    //printf("len: %i\n",  strlen(temp));
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

    //printf("LS-1: ");
    //puts(temp);

};

void P8K1(){
    
    /*
    printf("P8: ");
    for (i = 0; i<8;++i) {
        if(i==7)
            printf("%d\n",p8[i]);
        else
            printf("%d", p8[i]);
    };
    */
    for (i=0; i<8; i++) {
        n = p8[i];
        k1[i] = temp[n-1];
    };

    k1[8] = '\0';
    //printf("k1: ");
    //puts(k1);

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

    //printf("LS-2: %s\n", temp);
    //printf("len: %i\n",  strlen(temp));

};

void P8K2(){

    for (i=0; i<8; ++i) {
        n = p8[i];
        k2[i] = temp[n-1];  
    };
    k2[8] = '\0';
    //printf("k2: ");
    //puts(k2);

};

void printK2(){
    //printf("k2 just for test: ");
    //puts(k2);
    //printf("test 2: %s", k2);
};

void plaintextInput(){

    printf("Please enter the plaintext: ");
    scanf (" %[^\n]%*c", plainText);
    
};

void plainTextToBi(){

    int len = strlen(plainText);
    printf("---------\n");
    for(row=0;row<len;++row){
        for(col=7; col>=0; --col)
            binaryPlainText[row][col] = (plainText[row] & (1 << col)) ? '1' : '0';
        binaryPlainText[row][8] = '/0';
        printf("%c: ", plainText[row]);
        puts(binaryPlainText[row]);
    }
}

void initialPermutation(){
    if(phase ==1){
        for(i=0;i<8;++i){
            temp8[i] = binaryPlainText[row][ip[i]-1];
        };
    }else{
        for(i=0;i<8;++i){
            temp8[i] = cipherText[row][ip[i]-1];
        };
    }
    temp8[8] = '\0';
    //printf("Plain text after initial Permutation: ");
    //puts(temp8);

};

void divideLeftRight(){
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

    /*
    printf("Left: ");
    puts(l);

    printf("Right: ");
    puts(r);
    */
};

void expandpermutateR(char *str){

    for(i=0;i<8;++i){
        temp8[i] = str[EP[i] - 1];
    };
    temp8[8] = '\0';
    //printf("EP-R: ");
    //puts(temp8);

};

void XOR(int ki){
    
    if((ki==1 && phase == 1) || (ki ==1 && phase==2)){
        //printf("k1: ");
        //puts(k1);

        for(i=0;i<8;++i){
            if(k1[i] == temp8[i])
                temp8[i] = '0';
            else
                temp8[i] = '1';    
        }
    }else{
        //printf("k2: ");
        //puts(k2);

        for(i=0;i<8;++i){
            if(k2[i] == temp8[i])
                temp8[i] = '0';
            else
                temp8[i] = '1';  
        }
    }
 
    temp8[8] = '\0';
    //printf("XOR%i: ", i);
    //puts(temp8);
};

void divideLeftRightXor(){
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

    /*
    printf("Left of XOR: ");
    puts(lXor);

    printf("Right of XOR: ");
    puts(rXor);
    */
};

/*
I wanted to do the S-boxes part with this function but then I realized it will just make the code more complex!
so I just ket it here for furure change.
----------------------------------------------------

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

-----------------------------------------------------
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

    //printf("lxor 1-4: ");
    //puts(num);

    
    pos[0] = biToStr(num);
    //printf("row in S0: %i\n", pos[0]);
    
    //2-3
    num[0] = lXor[1];
    num[1] = lXor[2];
    num[2] = '\0';

    //printf("lxor 2-3: ");
    //puts(num);
    
    pos[1] = biToStr(num);
    //printf("Col in S0: %i\n", pos[1]);

    ext[0] = S0[pos[0]][pos[1]];
    //printf("S0: %d\n", ext[0]);
    //printf("test S0: %d\n", S0[0][3]);

    
};

void s1Box(){

    char num[3];
    int pos[2]; //pos[o is the row and pos[1] is the col of S0_box

    //1-4
    num[0] = rXor[0];
    num[1] = rXor[3];
    num[2] = '\0';

    //printf("rxor 1-4: ");
    //puts(num);

    
    pos[0] = biToStr(num);
    //printf("row in S1: %i\n", pos[0]);
    
    //2-3
    num[0] = rXor[1];
    num[1] = rXor[2];
    num[2] = '\0';

    //printf("rxor 2-3: ");
    //puts(num);
    
    pos[1] = biToStr(num);
    //printf("Col in S1: %i\n", pos[1]);

    ext[1] = S1[pos[0]][pos[1]];
    //printf("S1: %d\n", ext[1]);
    //printf("test S0: %d\n", S0[0][3]);
    decToBi();

};

void decToBi(){
    //printf("S0: %i\n", ext[0]);
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

    //printf("S-Box: ");
    //puts(temp4);
}

void p4(){

    //printf("P4: ");
    for(i=0;i<4;++i){
        ext[i] = temp4[P4[i]-1];      
    }
    for(i=0;i<4;++i){
        temp4[i] = ext[i];      
    }
    temp4[4] = '\0';
    //printf("Ressult: ");
    //puts(temp4);

};

void fk(int ki){
     
    //mapping---
    //leftnright
   

    //Expand and permutate R using E/P
    if (ki==1 && phase == 1 || ki==2 && phase ==2){
        expandpermutateR(r);
    }else{
        expandpermutateR(swR);
    }
    

    //Xor ----
    if(ki==1) XOR(1); 
    else XOR(2);
       

    //divide the result of XOR to left and right 4 bits
    divideLeftRightXor();
    
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
    //printf("XOR with l: ");
    //puts(temp4);
};

void switchHalf(){
      
    for(i=0;i<4;++i){
        l[i] = r[i];
    }
    l[4] = '\0';

    //printf("SW-L: ");
    //puts(l);

    for(i=0;i<4;++i){
        swR[i] = temp4[i];
    }
    swR[4] = '\0';

    //printf("SW-R: ");
    //puts(swR);

}

void initialPermutationRev(){

    if(phase == 1){
        for(i=0;i<8;++i){
            cipherText[row][i] = temp8[ipRev[i]-1];
        };
        cipherText[row][8] = '\0';
        //printf("Ciphertext%i: ", row);
        //puts(cipherText[row]);
    }else{
        for(i=0;i<8;++i){
            output[row][i] = temp8[ipRev[i]-1];
        };
        output[row][8] = '\0';
        //printf("PlainText In binary: ");
        //puts(output[row]);
    }
    
};

void combine(){
    int j=4;
    for(i=0;i<8;++i){
        if(i<4){
            temp8[i] = temp4[i];
        }else{
            n = i - j;
            temp8[i] = swR[n];
        };
    }
    temp8[8]='\0';
    
}

bool continueencrypt(){
    char ans;
    
    printf("Do you want to encrypt another plaintext?(y/n) ");

    do{
        scanf("%c", &ans);
        if(ans == 'y'){
            return true;
        }else if(ans == 'n'){
            return false;
        }
    }while(true);   
    
}