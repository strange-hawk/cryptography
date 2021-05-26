// Name - Animesh Gupta
// Roll no. - 201851153

#include<stdio.h>
#define ull unsigned long long
#define ul unsigned long
#define max32 4294967296

ul left(ull t){
    ul temp = ((t>>32) & (max32-1));
    return (unsigned long)temp;
}
ul right(ull t){
    ul temp = (((t<<32)>>32) & (max32-1));
    return (unsigned long)temp;
}

void print(ul t, int m){
    // printf("\n");
    for(int i=0;i<m;i++){
        printf("%d",(t & (1ul<<(m-1-i)))!=0);
        if(i%4==3){
            printf(" ");
        }
    }
    printf("\n");
}

ul f(ul r0_k){
    
    for(int i=0;i<8;i++){
        ul temp = 0ul;
        temp = (r0_k & 15ul);
        temp = (unsigned long)((temp+1) & 15ul);
        temp = temp<<28;
        r0_k = r0_k >>4;
        r0_k = r0_k | temp;
        // print(r0_k);
    }
    return r0_k;
}

int main(){

    // -------------------------------------- ENCRYPTION --------------------------------------
    unsigned long long plain, key;
    scanf("%llu %llu", &plain, &key);
    printf("plain -> ");
    print(plain,64);

    printf("key -> ");
    print(key,32);


    // dividing into l0 and r0
    ul l0 = left(plain), r0 = right(plain); 
    printf("l0 -> ");
    print(l0,32);

    printf("r0 -> ");
    print(r0,32);


    // computing r0 ^ key
    ul r0_k = r0^key;

    printf("r0_k -> ");
    print(r0_k, 32);

    // computing f function

    r0_k = f(r0_k);
    printf("f -> ");
    print(r0_k,32);

    // computing l1, r1
    ul r1 = l0^r0_k, l1 = r0;

    printf("l1 -> ");
    print(l1,32);

    printf("r1 -> ");
    print(r1,32);

    // generating cipher text
    ull cipher = 1ull;
    cipher = cipher | (unsigned long long)l1;
    cipher = cipher <<32;
    cipher = cipher | (unsigned long long)r1;

    printf("cipher -> ");
    print(cipher,64);
    

    // -------------------------------------- DECRYPTION --------------------------------------

    ul decrypt_r0 = l1;
    ul decrypt_l0 = r1^f(l1^key);
    ull decrypt = 1ull;
    decrypt = decrypt | (unsigned long long)decrypt_l0;
    decrypt = decrypt <<32;
    decrypt = decrypt | (unsigned long long)decrypt_r0;
    printf("decryption -> ");
    print(decrypt,64);

}