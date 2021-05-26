// Name - Animesh Gupta
// Roll no. - 201851153

#include<stdio.h>
#define ull unsigned long long
#define ul unsigned long
#define max28 268435456
#define bitat28 134217728
#define max32 4294967296

void print(ull temp, int k){
    for(int i=0;i<k;i++){
        printf("%d", (temp & 1ULL<<(k-1-i))!=0);
    }
}



ull bit_64_to_56(ull key){
    int arr[56]={57,49,41,33,25,17,9,1,58,50,42,34,26,18,10,2,59,51,43,35,27,19,11,3,60,52,44,36,63,55,47,39,31,23,15,7,62,54,46,38,30,22,14,6,61,53,45,37,29,21,13,5,28,20,12,4};
    ull new_key = 0ULL;
    // printf("\norig -> ");
    // print(key,64);
    for(int i=0,j=55;i<56 && j>=0;i++,j--){
        if ((key & (1ULL<<(64-arr[i])))>0){
            new_key = new_key | (1ULL<<j);
        }
    }
    return new_key;
}

ul left_key(ull t){
    ul temp = ((t>>28) & (max28-1));
    return (unsigned long)temp;
}

ul right_key(ull t){
    ul temp = (((t<<28)>>28) & (max28-1));
    return (unsigned long)temp;
}

ul round_key(ul key){
    key = (key<<1 & 268435455) | ((key & bitat28) > 1 ? 1UL : 0UL);
    return key;
}

ull combined_key(ul left, ul right){
    right = right<<4;
    left = (unsigned long long)left;
    left = left<<32;
    left = left | (unsigned long long)right;
    left = left>>4;
    return left;
}

ull bit_56_to_48(ull key){
    int arr[48]={14,17,11,24,1,5,3,28,15,6,21,10,23,19,12,4,26,8,16,7,27,20,13,2,41,52,31,37,47,55,30,40,51,45,33,48,44,49,39,56,34,53,46,42,50,36,29,32};
    ull new_key = 0ULL;
    for(int i=0,j=47;i<48 && j>=0;i++,j--){
        if ((key & (1ULL<<(56-arr[i])))>0){
            new_key = new_key | (1ULL<<j);
        }
    }
    return new_key;
}



// methods for plain_text


ull initial_permutation(ull plain){
    int arr[64]={58,50,42,34,26,18,10,2,60,52,44,36,28,20,12,4,62,54,46,38,30,22,14,6,64,56,48,40,32,24,16,8,57,49,41,33,25,17,9,1,59,51,43,35,27,19,11,3,61,53,45,37,29,21,13,5,63,55,47,39,31,23,15,7};
    ull new_key = 0ULL;
    for(int i=0,j=63;i<64 && j>=0;i++,j--){
        if ((plain & (1ULL<<(64-arr[i])))>0){
            new_key = new_key | (1ULL<<j);
        }
    }
    return new_key;
}
ul left(ull t){
    ul temp = ((t>>32) & (max32-1));
    return (unsigned long)temp;
}
ul right(ull t){
    ul temp = (((t<<32)>>32) & (max32-1));
    return (unsigned long)temp;
}

ull bit_32_to_48(ul right){
    int arr[48]= {32,1,2,3,4,5,4,5,6,7,8,9,8,9,10,11,12,13,12,13,14,15,16,17,16,17,18,19,20,21,20,21,22,23,24,25,24,25,26,27,28,29,28,29,30,31,32,1};
    ull new_right = 0ULL;
    for(int i=0,j=47;i<48 && j>=0;i++,j--){
        if ((right & (1ULL<<(32-arr[i])))>0){
            new_right = new_right | (1ULL<<j);
        }
    }
    return new_right;
}


ul S_box(ull text){
    int arr[][4][16]= {
                        {
                            {14,4,13,1, 2, 15,11,8, 3, 10, 6, 12, 5,9, 0,7},
                            {0, 15, 7,4,14,2,13,1,10,6,12, 11, 9,5, 3,8},
                            {4,1,14,8,13,6, 2, 11,15, 12, 9,7, 3, 10, 5,0},
                            {15, 12, 8,2, 4,9, 1,7, 5, 11, 3, 14,10,0, 6, 13}
                        },
                        {
                            {15,  1,   8, 14 ,  6, 11,   3,  4,   9,  7,   2, 13,  12,  0,  5, 10},
                            {3 ,13   ,4  ,7  ,15  ,2   ,8,14  ,12  ,0   ,1 ,10,   6,  9,  11,  5},
                            {0 ,14 ,  7, 11 , 10,  4,  13,  1 ,  5 , 8 , 12 , 6  , 9 , 3 ,  2, 15},
                            {13,  8 , 10 , 1  , 3 ,15 ,  4 , 2 , 11 , 6  , 7 ,12  , 0 , 5  ,14  ,9}
                        },
                        {
                            {10,  0 ,  9, 14 ,  6 , 3 , 15 , 5 ,  1, 13,  12,  7,  11,  4 ,  2,  8},
                            {13,  7 ,  0,  9,   3,  4,   6, 10 ,  2 , 8 ,  5, 14 , 12, 11 , 15,  1},
                            {13,  6  , 4 , 9,   8 ,15 ,  3 , 0 , 11,  1 ,  2, 12 ,  5, 10,  14,  7},
                            {1, 10,  13,  0,   6,  9,   8,  7,   4, 15 , 14 , 3  ,11 , 5  , 2, 12}
                        },
                        {
                            {7, 13 , 14 , 3 ,  0 , 6 ,  9 ,10  , 1 , 2  , 8 , 5 , 11 ,12 ,  4, 15},
                            {13 , 8,  11,  5 ,  6, 15 ,  0 , 3 ,  4 , 7,   2, 12,   1, 10,  14,  9},
                            {10  ,6 ,  9,  0,  12, 11,   7, 13 , 15  ,1  , 3 ,14  , 5 , 2 ,  8,  4},
                            {3, 15 ,  0,  6 , 10 , 1 , 13 , 8  , 9 , 4  , 5 ,11  ,12 , 7 ,  2 ,14}
                        },
                        {
                            {2, 12 ,  4 , 1 ,  7 ,10 , 11  ,6  , 8  ,5  , 3 ,15 , 13,  0,  14,  9},
                            {14, 11,   2, 12,   4,  7 , 13,  1 ,  5,  0 , 15 ,10  , 3 , 9  , 8 , 6},
                            {4,  2 ,  1, 11,  10, 13 ,  7 , 8,  15,  9,  12  ,5,   6,  3,   0, 14},
                            {11 , 8 , 12 , 7 ,  1, 14 ,  2, 13  , 6, 15 ,  0,  9 , 10,  4 ,  5 , 3}
                        },
                        {
                            {12,  1,  10, 15,   9,  2,   6,  8 ,  0 ,13  , 3,  4,  14 , 7 ,  5 ,11},
                            {10, 15,   4,  2,   7, 12 ,  9,  5,   6,  1 , 13, 14,   0, 11  , 3,  8},
                            {9, 14,  15 , 5  , 2 , 8  ,12 , 3   ,7,  0 ,  4, 10 ,  1, 13,  11,  6},
                            { 4 , 3 ,  2 ,12   ,9,  5 , 15, 10  ,11, 14 ,  1,  7 ,  6 , 0  , 8 ,13}
                        },
                        {
                            {4, 11 ,  2 ,14 , 15  ,0   ,8, 13,   3, 12 ,  9,  7 ,  5 ,10  , 6 , 1},
                            {13 , 0 , 11 , 7 ,  4 , 9 ,  1, 10 , 14,  3,   5, 12 ,  2 ,15 ,  8 , 6},
                            {1  ,4  ,11 ,13 , 12,  3,   7, 14,  10, 15 ,  6 , 8  , 0 , 5  , 9 , 2},
                            {6 ,11  ,13  ,8 ,  1,  4 , 10 , 7 ,  9 , 5  , 0 ,15 , 14,  2 ,  3, 12}
                        },
                        {
                            {13 , 2  , 8  ,4  , 6 ,15 , 11 , 1 , 10 , 9   ,3 ,14,   5,  0 , 12,  7},
                            {1, 15,  13,  8 , 10 , 3 ,  7,  4,  12 , 5  , 6, 11 ,  0 ,14 ,  9,  2},
                            {7 ,11   ,4 , 1 ,  9, 12  ,14 , 2 ,  0 , 6,  10, 13 , 15 , 3 ,  5 , 8},
                            {2 , 1 , 14 , 7 ,  4, 10  , 8, 13,  15, 12 ,  9 , 0  , 3 , 5  , 6 ,11}
                        }
                     
                    };
    printf("\n\n");
    // text = text<<16;
    int ind[8][2];
    for(int i=0;i<8;i++){
        ull temp = text & 63ULL;
        print(temp,6);
        temp = (unsigned long)temp;
        int row = temp & 1;
        temp = temp>>1;
        int column = temp & 15;
        temp = temp>>4;
        row = (((temp&1)<<1) | (row));
        ind[7-i][0]=row;
        ind[7-i][1]=column;
        // printf("  %d %d", row, column);
        printf("\n");
        text = text>>6;
    }
    ul new_text = 0UL;
    for(int i=0;i<8;i++){
        printf("  %d %d %d", ind[i][0], ind[i][1],arr[i][ind[i][0]][ind[i][1]]);
        printf("\n");
        ul temp = (unsigned int)arr[i][ind[i][0]][ind[i][1]];
        new_text = new_text | (temp<<((7-i)*4));
    }
    return new_text;
}

ul permutation_after_s_box(ul text){
    int arr[32] = {16,7,20,21,29,12,28,17,1,15,23,26,5,18,31,10,2,8,24,14,32,27,3,9,19,13,30,6,22,11,4,25};
    ul new_text = 0UL;
    for(int i=0,j=31;i<32 && j>=0;i++,j--){
        if ((text & (1ULL<<(32-arr[i])))>0){
            new_text = new_text | (1UL<<j);
        }
    }
    return new_text;
}




int main(){
    ull key;
    printf("enter key : ");
    scanf("%llu",&key);
    key = bit_64_to_56(key);
    ul key_left=left_key(key), key_right=right_key(key);



    // 1st round key generation
    key_left = round_key(key_left);
    key_right = round_key(key_right);
    key = combined_key(key_left, key_right);
    key = bit_56_to_48(key);

    // plain text processing
    ull plaintext;
    printf("enter plaintext : ");
    scanf("%llu", &plaintext);
    plaintext = initial_permutation(plaintext);
    ul l0 = left(plaintext), init_r0 = right(plaintext);
    ull r0 = bit_32_to_48(init_r0);

    ull key_xor_e = key ^ r0;

    // applying S box on 48 bit output to convert 48 bit to 32 bit
    ul s_box = (unsigned long)S_box(key_xor_e);
    printf("\n");
    print(s_box,32);
    printf("\n");

    // permutation on 32 bit
    ul f_r0_k = permutation_after_s_box(s_box);
    ul r1 = l0 ^ f_r0_k;
    ul l1 = init_r0;


    // combined cipher text
    ull cipher = 1ull;
    cipher = cipher | (unsigned long long)l1;
    cipher = cipher <<32;
    cipher = cipher | (unsigned long long)r1;
    printf("\ncipher in bits -> ");
    print(cipher,64);
    printf("\n\nciphertext -> %llu\n", cipher);
    

}

// plaintext = 81985529216486895
// key = 1383827165325090801

