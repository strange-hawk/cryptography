// NAME - ANIMESH GUPTA
// ROLL NO. - 201851153




#include <stdio.h>
#include <stdint.h>
#include <stdint.h>


const uint8_t sBox[256] =   { 
	0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76, 
	0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0, 
	0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15, 
	0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75, 
	0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84, 
	0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf, 
	0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8, 
	0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2, 
	0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73, 
	0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb, 
	0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79, 
	0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08, 
	0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a, 
	0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e, 
	0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf, 
	0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16 }; 

const uint8_t Rcon[4][10] = {
    {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x1b,0x36},
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
};
u_int8_t mat[4][4] = {
                        {2, 3, 1, 1}, 
                        {1, 2, 3, 1}, 
                        {1, 1, 2, 3}, 
                        {3, 1, 1, 2}
                    };







void subByte(u_int8_t output[4][4], u_int8_t state[4][4]){
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            output[i][j]=sBox[state[i][j]];
        }
    }
}


void shiftRows(u_int8_t output[4][4],u_int8_t state[4][4]){
    for(u_int8_t i=0;i<4;i++){
        for(u_int8_t j=0;j<4;j++){
            if(i==0){
                output[i][j]=state[i][j];
            }
            else{
                output[i][j]=state[i][(j+i)%4];
            }
        }
    }
}

u_int8_t x_mul_f(u_int8_t elem)
{
    u_int8_t a = elem << 1;
    u_int8_t temp = a;
    u_int8_t c1 = (u_int8_t)(128);
    if((elem & c1) > 0){
        temp = a ^ (u_int8_t)27;
    }
    return (u_int8_t)temp;
}



u_int8_t x_plus_one_mul_f(u_int8_t elem)
{
    u_int8_t temp = x_mul_f(elem) ^ (u_int8_t)elem;
    return (u_int8_t)temp;
}



void mixedColumn(u_int8_t output[4][4],u_int8_t state[4][4]){
    for (int c = 0; c < 4; c++) {
      for (int d = 0; d < 4; d++) {
        for (int k = 0; k < 4; k++) {
          if (mat[c][k]==1){
              output[c][d] = output[c][d] ^ (u_int8_t)state[k][d];
          }
          else if(mat[c][k]==2){
              output[c][d] = output[c][d] ^ (x_mul_f(state[k][d]));
          }
          else if(mat[c][k]==3){
              output[c][d] = output[c][d] ^ (x_plus_one_mul_f(state[k][d]));
          }
        }
      }
    }
}


void nextRoundKey(u_int8_t state[4][4], u_int8_t key[4][4]){
    int i,j;
	for(j=0;j<4;j++) {
		for(i=0;i<4;i++) {
			state[i][j]=state[i][j]^key[i][j];
		}
	}
}




void keyExpansion(int iteration, u_int8_t key[4][4]){
    int i,j;
	u_int8_t mtx[4];
	for(i=0;i<4;i++) { 
		mtx[i]=key[(i+1)%4][3];
	}

	for(i=0;i<4;i++) { 
		mtx[i]=sBox[mtx[i]];
	}

	for(i=0;i<4;i++) { 
		key[i][0]=key[i][0]^mtx[i]^Rcon[i][iteration];
	}

	for(j=1;j<4;j++) {  
		for(i=0;i<4;i++) {
			key[i][j]=key[i][j]^key[i][j-1];
		}
	}
}


void print(u_int8_t txt[4][4])
{
    printf("");
    for(int i=0;i<4;i++) {
		for(int j=0;j<4;j++) {
            printf("%x ",txt[i][j]);
        }
        printf("\n");
	}
	printf("\n\n");
}


void add_key_to_global(u_int8_t globl_key[11][4][4], u_int8_t key[4][4], int index){
    for(int i=0;i<4;i++){
        for(int j=0;j<4; j++){
            globl_key[index][i][j]=key[i][j];
        }
    }
}

int main()
{

    u_int8_t global_key[11][4][4];


    u_int8_t message[4][4] = {
        {0x00, 0x44, 0x88, 0xcc},
        {0x11, 0x55, 0x99, 0xdd},
        {0x22, 0x66, 0xaa, 0xee},
        {0x33, 0x77, 0xbb, 0xff}

    };

    // u_int8_t key[4][4] = {
    //     {0x00, 0x4, 0x8, 0xc},
    //     {0x01, 0x5, 0x9, 0xd},
    //     {0x2, 0x6, 0xa, 0xe},
    //     {0x3, 0x7, 0xb, 0xf}
    // };

    u_int8_t key[4][4] = {
        {0x0, 0x0, 0x0, 0x0},
    {0x0, 0x0, 0x0, 0x0},
    {0x0, 0x0, 0x0, 0x0},
    {0x0, 0x0, 0xf, 0x8e}
    };

    
    // printf("enter 16 8-bit message blocks in hexadecimal format\n");
    // for(int i=0;i<4;i++){
    //     for(int j=0;j<4;j++){
    //         int temp ;
    //         scanf("%x", &temp);
    //         message[j][i]= (u_int8_t)(temp);
    //     }
    // }
    // printf("enter 16 8-bit key blocks in hexadecimal format\n");
    // for(int i=0;i<4;i++){
    //     for(int j=0;j<4;j++){
    //         int temp ;
    //         scanf("%x", &temp);
    //         key[j][i]= (u_int8_t)(temp);
    //     }
    // }

    // printf("\nInput: \n");
	// print(message);

	// printf("\nKey: \n");
	// print(key);

    u_int8_t sub_byte[4][4];
    u_int8_t shift_rows[4][4];

    nextRoundKey(message, key);
    add_key_to_global(global_key, key, 0);
    print(key);
    

    for(int i=0;i<9;i++){
        printf("---------------------------------\n\n");
        print(message);
        subByte(sub_byte, message);
        print(sub_byte);
        shiftRows(shift_rows, sub_byte);
        printf("target-> ");
        print(shift_rows);

        u_int8_t col_op_mat[4][4] = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};

        mixedColumn(col_op_mat, shift_rows);
        print(col_op_mat);
        keyExpansion(i, key);
        add_key_to_global(global_key, key, i+1);
        print(key);
        nextRoundKey(col_op_mat, key);
        // print(col_op_mat);
        // print(key);

        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                message[i][j] = col_op_mat[i][j];
            }
        }
    }
    printf("---------------------------------\n\n");
    // nextRoundKey(message,key);
    print(message);
    subByte(sub_byte, message);
    print(sub_byte);
    shiftRows(shift_rows, sub_byte);
    print(shift_rows);
	keyExpansion(9, key);
    print(key);
    add_key_to_global(global_key, key, 10);
	nextRoundKey(shift_rows, key);

    printf("encoded data -> ");
    print(shift_rows);
    printf("\n");

    // for(int i=0;i<11;i++){
    //     for(int j=0;j<4;j++){
    //         for(int k=0;k<4;k++){
    //             printf("%x ", global_key[i][j][k]);
    //         }
    //         printf("\n");
    //     }
    //     printf("\n\n");
    // }

}

// genereal routine to get output 
    // get_istart(global_i_start, encrypted_data, 1);
    // print(encrypted_data);
    // copy_arr(col_op_mat , encrypted_data);
    // invShiftRows(shift_rows,col_op_mat );
    // print(shift_rows);
    // invsubByte(sub_byte, shift_rows);
    // copy_arr(encrypted_data, sub_byte);
    // print(encrypted_data);
    // inv_key_wrt_index(global_key, key, 1);
    // print(key);
    // nextRoundKey(encrypted_data, key);
    // print(encrypted_data);