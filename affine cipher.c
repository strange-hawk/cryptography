// name - ANIMESH GUPTA
// roll no. - 201851153
// batch - CSE

#include<stdio.h>
#include<string.h>
#include<ctype.h>
char* encryption(char* str, int a, int b){
  // printf("%s\n", str);
  int n = (int)strlen(str);
  
  for(int i=0;i<n;i++){
    if(islower(str[i])){
      str[i] = 'a'+ (((str[i]-'a')*a+b)%26);
    }
    else if(isspace(str[i])){
      continue;
    }
    else{
      str[i] = 'A'+ (((str[i]-'A')*a+b)%26);
    }
  }
  return str;
}

char* decryption(char str[], int a, int b){
  int n = (int)strlen(str);
  int inv_a=1;
  while((inv_a*a) % 26 != 1){
    inv_a++;
  }

  
  for(int i=0;i<n;i++){
    if(islower(str[i])){
      if((str[i]-'a' - b) < 0){
        str[i] = 'a'+ ((inv_a*(str[i]-'a' - b+26))%26);
      }
      else{
        str[i] = 'a'+ ((inv_a*(str[i]-'a' - b))%26);
      }
      
    }
    else if(isspace(str[i])){
      continue;
    }
    else{
      if((str[i]-'A' - b) < 0){
        str[i] = 'A'+ ((inv_a*(str[i]-'A' - b+26))%26);
      }
      else{
        str[i] = 'A'+ ((inv_a*(str[i]-'A' - b))%26);
      }
    }
  }
  // printf("%s", str);
  return str;
}

int main(){
  char str[200];
  int a = 9, b=25;
  printf("enter a : ");
  scanf("%d",&a);
  printf("enter b : ");
  scanf("%d",&b);
  getchar();
  printf("enter string : ");
  fgets(str, 200, stdin);
  char* enc_str = encryption(str, a, b);
  printf("encryption is %s \n", enc_str);
  int inv_a=1;
  while((inv_a*a) % 26 != 1){
    inv_a++;
  }
  printf("inverse a : %d\n", inv_a);
  char* dec_str = decryption(str, a, b);
  printf("decryption is %s \n", dec_str);


}