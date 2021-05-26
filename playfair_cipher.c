// name - ANIMESH GUPTA
// roll no. - 201851153
// batch - CSE

#include<stdio.h>
#include<string.h>
#include<ctype.h>
char arr[5][5];

struct index{
    int a;
    int b;
};

void generate_table(char* text){
    int capital = isupper(text[0]) ? 1 : 0;
    int n=(int)strlen(text);
    char string_arr[(int)strlen(text) + 26];
    for(int i=0;i<n;i++){
        if(isupper(text[i])){
            text[i]=tolower(text[i]);
        }
        string_arr[i]=text[i];
    }
    for(int i=0;i<26;i++){
        string_arr[n+i]='a'+i;
    }
    string_arr[n+26]='\0';
    // printf("%s", string_arr);
    int carr[25]={0};
    char new_str[25];
    int j =0;
    for(int i=0;i<(n+26);i++){
        if(string_arr[i]=='i' || string_arr[i]=='j'){
            string_arr[i]='i';
        }
        if(carr[string_arr[i]-'a']==0){
            new_str[j]=string_arr[i];
            carr[string_arr[i]-'a']=1;
            j++;
        }
    }
    int str_ind=0;
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            arr[i][j]=new_str[str_ind++];
        }
    }
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            if(capital){
                printf("%c ", toupper(arr[i][j]));
            }
            else{
                printf("%c ", arr[i][j]);
            }
            
        }
        printf("\n");
    }
}

struct index get_index( char c){
    struct index ind;
    int i,j;
    for(i=0;i<5;i++){
        for(j=0;j<5;j++){
            if(arr[i][j]==c){
                ind.a=i;
                ind.b=j;
                break;
            }
        }
    }
    return ind;
}


char* encryption(char* str, int capital){
    int n = strlen(str);
    // char encoded_str[200];
    printf("string to encode --> ");
    for(int i=0;i<n;i+=2){
        printf("%c%c", str[i], str[i+1]);
        if(isupper(str[i])){
            str[i]=tolower(str[i]);
        }
        if(isupper(str[i+1])){
            str[i+1]=tolower(str[i+1]);
        }

        struct index index_a = get_index(str[i]);
        struct index index_b = get_index(str[i+1]);

        if(index_a.a==index_b.a){
            str[i]=arr[(index_a.a)%5][(index_a.b+1)%5];
            str[i+1]=arr[(index_b.a)%5][(index_b.b+1)%5];
        }
        else if(index_a.b==index_b.b){
            str[i]=arr[(index_a.a+1)%5][(index_a.b)%5];
            str[i+1]=arr[(index_b.a+1)%5][(index_b.b)%5];
        }
        else{
            str[i]=arr[index_a.a][index_b.b];
            str[i+1]=arr[index_b.a][index_a.b];
        }
        


    }
    // printf("\n");
    if(capital){
        for(int i=0;i<strlen(str);i++)
            printf("%c",toupper(str[i]));
    }
    printf("\nencoded string = %s\n", str);


    
    return str;

}

void decryption(char* str, int capital){
    // printf("string to decrypt is %s", str);
    int n = strlen(str);
    printf("decrypted string --> ");
    char encoded_str[200];
    for(int i=0;i<n;i+=2){
        // printf("%c %c ", str[i], str[i+1]);
        if(isupper(str[i])){
            str[i]=tolower(str[i]);
        }
        if(isupper(str[i+1])){
            str[i+1]=tolower(str[i+1]);
        }
        struct index index_a = get_index(str[i]);
        struct index index_b = get_index(str[i+1]);

        if(index_a.a==index_b.a){
            str[i]=arr[(index_a.a)%5][(index_a.b-1)%5];
            str[i+1]=arr[(index_b.a)%5][(index_b.b-1)%5];
        }
        else if(index_a.b==index_b.b){
            str[i]=arr[(index_a.a-1)%5][(index_a.b)%5];
            str[i+1]=arr[(index_b.a-1)%5][(index_b.b)%5];
        }
        else{
            str[i]=arr[index_a.a][index_b.b];
            str[i+1]=arr[index_b.a][index_a.b];
        }
        if(capital==1){
            printf("%c%c",toupper(str[i]),toupper(str[i+1]));
        }
        else{
            printf("%c%c",str[i],str[i+1]);
        }


    }
    printf("\n");
    


    
    // return str;

}



int main(){
    char str[200];
    printf("enter the key : ");
    scanf("%s", str);
    generate_table(str);
    
    printf("enter string to encode : ");
    char str_to_encode[200];
    scanf("%s", str_to_encode);
    if((int)strlen(str_to_encode)%2==1){
        char ch = 'x'; 
        strncat(str_to_encode, &ch,1);
    }
    int capital = isupper(str_to_encode[0]) ? 1 : 0;
    char* enc_str = encryption(str_to_encode, capital);
    decryption(enc_str, capital);
    // printf("\n%s\n", dec);

}