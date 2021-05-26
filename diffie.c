#include <stdio.h>
#define p 353
#define g 3


int square_and_multiply(unsigned int a, unsigned int n){
  int t = 1;
  while(n>0){
    if((n&1)!=0){
      t=t*a;
      t=t%p;
    }
    a=a*a;
    a = a%p;
    n=n>>1;
  }
  return t;
}

int main()
{
  
  unsigned int key1, key2;
  // scanf("%d", &key1);
  // scanf("%d", &key2);
  int ka = square_and_multiply(3, 97);
  int kb = square_and_multiply(3, 233);

  int ka_final = square_and_multiply(ka, key2);
  int kb_final = square_and_multiply(kb, key1);
  printf("shared key with alice : %d\n", ka);
  printf("shared key with bob : %d\n", kb);


}