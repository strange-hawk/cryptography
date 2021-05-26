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

void loadlfsr(){
     int i;
     for(i=0; i<80; i++) s[i] = myrand64();
}

ull lfsr(){
    ull out, feed;
    int i;
    feed = s[62] ^ s[51] ^ s[38] ^ s[23] ^ s[13] ^ s[0];
    out = s[0];
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
    
	for(j=0; j<64; j++){
	   b = (z >> j)&0x1;
	   printf("%d ",b);
	}
	printf("\n");
    }
}
// 110001  & 1 