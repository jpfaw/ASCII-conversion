// gcc -o ascii ascii.c

#include <stdio.h>
#include <string.h>

#define DEBUG 0 // 0: false 1: true

void print_red_color(const char *text);
void print_green_color(const char *text);
void data_check(const long data, const long assumption);

int main(void){
    int i, j, k;
    char m[] = "abcdefghijklmnopqrstuvwxyz";
    int m_size = (sizeof(m) / sizeof(char))-1;
    print_green_color("Original: ");
    printf("%s\n", m);
    if(DEBUG) printf("文字数: %d\n", m_size);
    
    // 文字列を4つずつに分割
    int split_size = m_size/4 +1;
    char split_m[split_size][5];
    for(i=0;i<split_size;i++){
        for(j=0;j<4;j++){
            if(i*4+j<m_size) split_m[i][j] = m[i*4+j];
            else{split_m[i][j] = '\0'; break;}
        }
        split_m[i][4] = '\0';
    }
    // テスト出力
    if(DEBUG) for(i=0; i<split_size; i++) printf("%s\n", split_m[i]);

    // 平文mを16進数ASCII表記文字列へ変換
    char split_m_ascii[split_size][9];
    for(i=0; i<split_size; i++) {
        for(j=0; j<4;j++){
            if(i*4+j < m_size){
                int tmp = split_m[i][j];
                char str[3];
                sprintf(str,"%x",tmp); // int to char
                split_m_ascii[i][j*2] = str[0];
                split_m_ascii[i][j*2+1]=str[1];
            } else {
                split_m_ascii[i][j*2] = '\0';
                break;
            }
        }
        split_m_ascii[i][8]='\0';
    }
    // テスト出力
    if(DEBUG) for(i=0; i<split_size; i++) printf("%s\n", split_m_ascii[i]);

    // 16進数ASCII表記文字列を数値に変換
    long split_m_long[split_size];
    for(i=0; i<split_size; i++) {
        split_m_long[i] = strtol(split_m_ascii[i], NULL, 16);
    }
    // テスト出力
    if(DEBUG) for(i=0; i<split_size; i++) printf("%ld\n", split_m_long[i]);

/* ------------------------------------------------------------ */

    // 数値を16進数文字列に変換
    char long_to_ascii[split_size][9];
    for(i=0; i<split_size; i++) {
        snprintf(long_to_ascii[i], 9, "%x",split_m_long[i]);
    }
    // テスト出力
    if(DEBUG) for(i=0; i<split_size; i++) printf("%s\n", long_to_ascii[i]);

    // 16進数文字列をasciiで文字として出力
    print_green_color("Decoding: ");
    for(i=0; i<split_size; i++) {
        char y[9];
        for(j=0;j<4; j++){
            strcpy(y, &long_to_ascii[i][j*2]);
            y[2] = '\0';
            unsigned int a = strtol(y, NULL, 16);
            putchar(a);
        }
    }
    printf("\n");
    return 0;
}

/* -----------------------------------------------
 * 文字列を緑色で出力する関数
 * $0 出力したい文字列
 -----------------------------------------------*/
void print_green_color(const char *text) {
    printf("\x1b[32m%s\x1b[39m", text);
}
