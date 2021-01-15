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


//initializing the variables
//--------------------------

const int p8[] = {6, 3, 7, 4, 8, 5, 10, 9};        //8 bits of permuted input
const int p1[] = {3, 5, 2, 7, 4, 10, 1, 9, 8, 6};  //10 bit of permuted input
const int ip[] = {2, 6, 3, 1, 4, 8, 5, 7};         //inverse permutation
const int ipRev[] = {4, 1, 3 , 5, 7, 2, 8, 6};     //reverse of inverse permutation
const int sw[] = {4, 5, 6, 7, 0, 1, 2, 3};         //sw used in the fk function2
const int EP[8] = {4, 1, 2, 3, 2, 3, 4, 1};        //EP
const int P4[4] ={2, 4, 3, 1};                     //P4
int n = 0;                                         //used as a permanent holder for LS-2
int i;                                             //use for for loops
char inputKey[11] = {'1','0','1','0','0','0','0','0','1','0','\0'};   //The variable for storing the 10 bit input key from the user
char temp[11];                                     //is a temporary var for all of our calculation 
char temp8[8];
char temp4[5];                                     //8bits temo var 
char ext[4];                                       //extra variable for permutation
char k1[9];                                        //first 8 bit key - I added a null at the end of the key
char k2[9];                                        //second 8 bit key
char plainText[9] = {'0','1','1','1','0','0','1','0'};  //the plaintext
char cipherText[9];                                //the ciphertext - the output   
char l[5];		                                   //left
char r[5];                                         //right
char swR[5];                                       //switch
char lXor[5];                                      //xor of left
char rXor[5];                                      //xor of right
int S0[4][4] = {{1, 0, 3, 2}, {3, 2, 1, 0}, {0, 2, 1, 3}, {3, 1, 3, 2}};     //S0-Box                         
int S1[4][4] = {{0, 1, 2, 3}, {2, 0, 1, 3}, {3, 0, 1, 0}, {2, 1, 0, 3}};     //S1-Box
int err = 0;
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

    //initial Permutation
    initialPermutation();

    divideLeftRight();
    //printf("--------------------------------------fk1---------------------------------------\n");
    fk(1);

    //step 7
    XOR4();
    //printf("--------------------------------------fk2---------------------------------------\n");
    //step 8
    switchHalf();

    fk(2);
    XOR4();
    
    //printf("------------------------------------Output--------------------------------------\n");
    combine();
    initialPermutationRev();

    return 0;
    
};
//---------------end-of-main--------------

void getInput () {

    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("|                                                                 |\n");
    printf("|           The 10 bit key for the Test is: "); 
    for(i=0;i<10;++i)
        printf("%c", plainText[i]);
    printf("              |\n");
    printf("|                                                                 |\n");
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    
    

    
//---------------------------------------------------------------------------------------

    //scanf("%s", &inputKey);
    
};

void appllyP1 (){

    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("|                           Applying  P10                         |\n");
    printf("|                          P10: ");        
    for(i=0 ; i<10; ++i)
        printf("%i", p1[i]);
    printf("                       |\n");
    printf("|            The key after applying should be: 1000001100         |\n");
    printf("|                The program result is: ");  
    for(i=0 ; i<=9; ++i){
        temp[i] = inputKey[p1[i] - 1];
        printf("%C", temp[i]);
    };
    //add a null bit at the end of temp
    temp[10] = '\0';
    printf("                |\n");
    printf("|                                                                 |\n");
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("|          *** ");
    strcmp(temp, "1000001100") == 0 ? printf("The Test for this step was successful") : printf("The test was not successful");
    printf("***           |\n");
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    
    if(strcmp(temp, "0000111000") != 0) err++;
   
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
    temp[10] = '\0';
    
    printf("|                      Left shift by 1 position                   |\n");
    printf("|                  The result of this step must be                |\n");
    printf("|                            00001 11000                          |\n");
    printf("|                                                                 |\n");
    printf("|                   The result of this approach is                |\n");        
    printf("|                            ");
    for(i=0 ; i<10; ++i)
        printf("%c", temp[i]);
    printf("                           |\n");
    printf("|                                                                 |\n");
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("|          *** ");
    strcmp(temp, "0000111000") == 0 ? printf("The Test for this step was successful") : printf("The test was not successful");
    printf(" ***          |\n");
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    
    if(strcmp(temp, "0000111000") != 0) err++;

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

    
    printf("|            Rearrange the halves with P8 to produce K1           |\n");
    printf("|                 The result of this step must be                 |\n");
    printf("|                             10100100                            |\n");
    printf("|                                                                 |\n");
    printf("|                 The result of this approach is                  |\n");        
    printf("|                             ");
    for(i=0 ; i<8; ++i)
        printf("%c", k1[i]);
    printf("                            |\n");
    printf("|                                                                 |\n");
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("|          *** ");
    strcmp(k1, "10100100") == 0 ? printf("The Test for this step was successful") : printf("The test was not successful");
    printf("***           |\n");
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    
    if(strcmp(k1, "10100100") != 0) err++;
    
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

    printf("|       Left shift by 2 positions the left and right halves       |\n");
    printf("|                 The result of this step must be                 |\n");
    printf("|                    Left: 00100 Right: 00011                     |\n");
    printf("|                                                                 |\n");
    printf("|                 The result of this approach is                  |\n");        
    printf("|                            ");
    for(i=0 ; i<10; ++i)
        printf("%c", temp[i]);
    printf("                           |\n");
    printf("|                                                                 |\n");
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("|          *** ");
    strcmp(temp, "0010000011") == 0 ? printf("The Test for this step was successful") : printf("The test was not successful");
    printf("***           |\n");
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    
    if(strcmp(temp, "0010000011") != 0) err++;
    

};

void P8K2(){

    for (i=0; i<8; ++i) {
        n = p8[i];
        k2[i] = temp[n-1];  
    };
    k2[8] = '\0';

    printf("|            Rearrange the halves with P8 to produce K2           |\n");
    printf("|                 The result of this step must be                 |\n");
    printf("|                            01000011                             |\n");
    printf("|                                                                 |\n");
    printf("|                 The result of this approach is                  |\n");        
    printf("|                            ");
    for(i=0 ; i<8; ++i)
        printf("%c", k2[i]);
    printf("                             |\n");
    printf("|                                                                 |\n");
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("|          *** ");
    strcmp(k2, "01000011") == 0 ? printf("The Test for this step was successful") : printf("The test was not successful");
    printf("***           |\n");
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    
    if(strcmp(k2, "01000011") != 0) err++;
    
    


};

void printK2(){
    printf("k2 just for test: ");
    puts(k2);
    printf("test 2: %s", k2);
};

void plaintextInput(){

    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("|                                                                 |\n");
    printf("|                    Start to encrypt the text                    |\n");
    printf("|                                                                 |\n");
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    
    //scanf("%s", &plainText);
    //plainText[8] = '\0';


};

void initialPermutation(){

    for(i=0;i<8;++i){
        temp8[i] = plainText[ip[i]-1];
    };
    temp8[8] = '\0';

    printf("|          Apply the initial permutation, IP, on plaintext        |\n");
    printf("|                 The result of this step must be                 |\n");
    printf("|                            10101001                             |\n");
    printf("|                                                                 |\n");
    printf("|                 The result of this approach is                  |\n");        
    printf("|                            ");
    for(i=0 ; i<8; ++i)
    printf("%c", temp8[i]);
    printf("                             |\n");
    printf("|                                                                 |\n");
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("|          *** ");
    strcmp(temp8, "10101001") == 0 ? printf("The Test for this step was successful") : printf("The test was not successful");
    printf("***           |\n");
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    
    if(strcmp(temp8, "10101001") != 0) err++;
   
    
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
    printf("|           Assume the input from step 1 is in two halves         |\n");
    printf("|                 The result of this step must be                 |\n");
    printf("|                        L=1010, R=1001                           |\n");
    printf("|                                                                 |\n");
    printf("|                 The result of this approach is                  |\n");        
    printf("|                     Left: ");
    for(i=0 ; i<4; ++i) printf("%c", l[i]);
    printf(" Right: ");
    for(i=0 ; i<4; ++i) printf("%c", r[i]);
    printf("                      |\n");
    printf("|                                                                 |\n");
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("|          *** ");
    if (strcmp(l, "1010") == 0 && strcmp(r, "1001") == 0)
        printf("The Test for this step was successful");
    else
        printf("The test was not successful");
    printf("***           |\n");
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    
    if (strcmp(l, "1010") != 0 && strcmp(r, "1001") != 0) err++;
    
    
    
};

void expandpermutateR(char *str){

    for(i=0;i<8;++i){
        temp8[i] = str[EP[i] - 1];
    };
    temp8[8] = '\0';

    printf("|                 Expand and permutate R using E/P                |\n");
    printf("|                 The result of this step must be                 |\n");
    printf("|                            11000011                             |\n");
    printf("|                                                                 |\n");
    printf("|                 The result of this approach is                  |\n");        
    printf("|                            ");
    for(i=0 ; i<8; ++i)
    printf("%c", temp8[i]);
    printf("                             |\n");
    printf("|                                                                 |\n");
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("|          *** ");
    strcmp(temp8, "11000011") == 0 ? printf("The Test for this step was successful") : printf("The test was not successful");
    printf("***           |\n");
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    
    if(strcmp(temp8, "11000011") != 0) err++;
    scanf("%c", temp8);
    

};

void XOR(int ki){
    
    if(ki==1){
        printf("k1: ");
        puts(k1);
        for(i=0;i<8;++i){
        if(k1[i] == temp8[i])
            temp8[i] = '0';
        else
            temp8[i] = '1';
         }
    }else{
        printf("k2: ");
        puts(k2);
        for(i=0;i<8;++i){
        if(k2[i] == temp8[i])
            temp8[i] = '0';
        else
            temp8[i] = '1';
        }
    }
    temp8[8] = '\0';

    printf("|        XOR input from step 3 with K1: 10100100 XOR 11000011     |\n");
    printf("|                 The result of this step must be                 |\n");
    printf("|                            01100111                             |\n");
    printf("|                                                                 |\n");
    printf("|                 The result of this approach is                  |\n");        
    printf("|                            ");
    for(i=0 ; i<8; ++i)
    printf("%c", temp8[i]);
    printf("                             |\n");
    printf("|                                                                 |\n");
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("|          *** ");
    strcmp(temp8, "01100111") == 0 ? printf("The Test for this step was successful") : printf("The test was not successful");
    printf("***           |\n");
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    
    if(strcmp(temp8, "01100111") != 0) err++;
    scanf("%c", temp);
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
    printf("|             Input left halve of step 4 into S-Box S0            |\n");
    printf("|                 The result of this step must be                 |\n");
    printf("|                            01100111                             |\n");
    printf("|                                                                 |\n");
    printf("|                 The result of this approach is                  |\n");        
    printf("|                            ");
    for(i=0 ; i<8; ++i)
    printf("%c", temp8[i]);
    printf("                             |\n");
    printf("|                                                                 |\n");
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("|          *** ");
    strcmp(temp8, "01100111") == 0 ? printf("The Test for this step was successful") : printf("The test was not successful");
    printf("***           |\n");
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    
    if(strcmp(temp8, "01100111") != 0) err++;
    
};

void s1Box(){

    char num[3];
    int pos[2]; //pos[o is the row and pos[1] is the col of S0_box

    //1-4
    num[0] = rXor[0];
    num[1] = rXor[3];
    num[2] = '\0';

    
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

    printf("|    a. For S0: 0110 as input: b1,b4 for row, b2,b3 for column    |\n");
    printf("|             b. Row 00, column 11 -> output is 10                |\n");
    printf("|                                                                 |\n");
    printf("|                            result: ");
    printf("%c %c", num[0], num[1]);
    printf("                             |\n");
    printf("|                                                                 |\n");
    printf("|                 The result of this approach is                  |\n");        
    printf("|                            ");
    for(i=0 ; i<8; ++i)
    printf("%c", temp8[i]);
    printf("                             |\n");
    printf("|                                                                 |\n");
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("|          *** ");
    strcmp(temp8, "01100111") == 0 ? printf("The Test for this step was successful") : printf("The test was not successful");
    printf("***           |\n");
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    
    if(strcmp(temp8, "01100111") != 0) err++;
    //printf("test S0: %d\n", S0[0][3]);
    scanf("%c", temp);
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

void fk(int ki){
     
    //mapping---
    //leftnright
   

    //Expand and permutate R using E/P
    if (ki==1){
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

void initialPermutationRev(){

    for(i=0;i<8;++i){
        cipherText[i] = temp8[ipRev[i]-1];
    };
    cipherText[8] = '\0';
    printf("Ciphertext: ");
    puts(cipherText);

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
    printf("input: ");
    puts(temp8);
}