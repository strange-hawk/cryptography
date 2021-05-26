#include<stdio.h>
#include<math.h>
#define P 187
#define ull unsigned long long

int gcd(a,b){
    if(a==0){
        return b;
    }
    return gcd(b%a,a);
}

int extendedGCD(a,b){
    int x1=0, y1=1;
    int x,y;
    while(a>0){
        y=x1;
        x=y1 - floor(b/a)*x1;
        x1=x;
        y1=y;
        a = b%a;
        b=a;
    }
    return x;
}

int square_and_multiply(unsigned int a, unsigned int n){
  int t = 1;
  while(n>0){
    if((n&1)!=0){
      t=t*a;
      t=t%P;
    }
    a=a*a;
    a = a%P;
    n=n>>1;
  }
  return t;
}

int main(){

    printf("%d", square_and_multiply(88,23));
    int p,q;
    scanf("%d %d", &p,&q);
    unsigned long long n = p*q;
    unsigned long long Qn = (p-1)*(q-1);
    unsigned long long int ek = 1;
    for(unsigned long long i =2;i<Qn ;i++){
        int g=gcd(i,Qn);
        if(g == 1){
            ek = i;
            break;
        }
    }
    printf("e -> %llu\n", ek);
    int d = extendedGCD(ek,Qn);
    printf("d -> %d\n", d);
    int message = 34;
    int ciphertext = square_and_multiply(message,ek);
    int decryptedmessage = square_and_multiply(ciphertext,d);
    printf("%d\n", decryptedmessage);
}