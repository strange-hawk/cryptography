#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ull unsigned long long
#define loop 1024

// 80-bit LFSR with feedback polynomial 1 + x^18 + x^29 + x^42 + x^57 + x^67 + x^80.

ull s[80];

ull myrand64(){
    ull temp = (ull) 0;
    int i;
    for (i=0; i<64; i++) {
        temp = ((temp << (ull) 1) | !(drand48() < 0.5));
    }
    return temp;
}
// temp = 0
// temp = (temp << 1) | 1 = 0000...0001 {63 zeros then a one}
// temp = (temp << 1) | 0/1 = 000...00010 | 0/1
// ...

void loadlfsr(){
     int i;
     for(i=0; i<80; i++) s[i] = myrand64();
}

ull lfsr(){
    ull out, feed;
    int i;
    feed = s[62] ^ s[51] ^ s[38] ^ s[23] ^ s[13] ^ s[0];
    /*
    S[62] = 11100...1001
    S[51] = 01010...0110
    S[38] = 01000...0001
    S[23] = 11101...1100
    S[13] = 10001...0000
    S[0]  = 00010...1111
    --------------------
    feed  = 10000...1101
     */
    // out = s[0]; // LFSR without non-linear filter function
    out = s[1] & s[39] ^ s[42]; // LFSR with non-linear filter function
    // out = 11100...11100 {64 bits}
    for (i = 0; i < 79; i++) s[i] = s[i+1];
    s[79] = feed;
    return(out);
}

int main(){
    int i, j, b;
    ull z;
    srand48(time(NULL));
    loadlfsr();
    for(i=0; i<loop; i++){
        z = lfsr();
        // z = 11100...11100 {64 bits}
    for(j=0; j<64; j++){
       b = (z >> j)&0x1;
       /*
       output from lsfr1 = (z >> 0) & 1 = 0
       output from lsfr2 = (z >> 1) & 1 = 0
       output from lsfr3 = (z >> 2) & 1 = 1
       .
       .
       .
       output from lsfr64 = (z >> 63) & 1 = 1
        */
       printf("%d ",b);
    }
    printf("\n");
    }
}