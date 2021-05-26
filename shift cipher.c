// name - ANIMESH GUPTA
// roll no. - 201851153
// batch - CSE

#include<stdio.h>
#include<string.h>
#include<ctype.h>
char* encryption(char* str, int displace){
  // printf("%s\n", str);
  int n = (int)strlen(str);
  
  for(int i=0;i<n;i++){
    if(islower(str[i])){
      str[i] = 'a'+ ((str[i]-'a' + displace)%26);
    }
    else if(isspace(str[i])){
      continue;
    }
    else{
      str[i] = 'A'+ ((str[i]-'A' + displace)%26);
    }
  }
  return str;
}

char* decryption(char str[], int displace){
  int n = (int)strlen(str);
  
  for(int i=0;i<n;i++){
    if(islower(str[i])){
      if((str[i]-'a' - displace) < 0){
        str[i] = 'a'+ ((str[i]-'a' - displace+26)%26);
      }
      else{
        str[i] = 'a'+ ((str[i]-'a' - displace)%26);
      }
      
    }
    else if(isspace(str[i])){
      continue;
    }
    else{
      if((str[i]-'A' - displace) < 0){
        str[i] = 'A'+ ((str[i]-'A' - displace+26)%26);
      }
      else{
        str[i] = 'A'+ ((str[i]-'A' - displace)%26);
      }
    }
  }
  // printf("%s", str);
  return str;
}

int main(){
  char str[200];
  int key;
  printf("enter key : ");
  scanf("%d",&key);
  getchar();
  printf("enter string : ");
  fgets(str, 200, stdin);
  char* enc_str = encryption(str, key);
  printf("encryption is %s \n", enc_str);
  char* dec_str = decryption(str, key);
  printf("decryption is %s \n", dec_str);


}
