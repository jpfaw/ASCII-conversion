// gcc -o ascii ascii.c

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ARRAY_SIZE 512

void print_red_color(const char *text);
void print_green_color(const char *text);
void data_check(const long data, const long assumption);

int main(void){
    char m[] = "hijk";
    int m_size = sizeof(m) / sizeof(char);
    print_green_color("original: ");
    printf("%s\n", m);
    printf("size: %d\n", m_size);

    // 平文mを16進数ASCII表記文字列へ変換
    char s[ARRAY_SIZE];
    int i;
    for(i=0; i<m_size-1;i++){
        int tmp = m[i];
        char s_copy[ARRAY_SIZE], str[10];
        if(i != 0) strcpy(s_copy, s);
        sprintf(str,"%x",tmp); // int to char
        strcat(s, str); // s += tmp
    }
    printf("%s\n", s);
    
    // 16進数ASCII表記文字列を数値に変換
    long v = strtol(s, NULL, 16);
    printf("v = %ld\n", v);

    
    /* ---------- */
    
    // 数値を16進数文字列に変換
    char x[ARRAY_SIZE];
    snprintf(x, ARRAY_SIZE, "%x", v);
    printf("x = %s\n", x);
    
    // 16進数文字列をasciiで文字として出力
    print_green_color("Decoding: ");
    for(i=0;i<m_size; i++){
        char y[ARRAY_SIZE];
        strcpy(y, &x[i*2]);
        y[2] = '\0';
        unsigned int a = strtol(y, NULL, 16);
        putchar(a);
    }
    printf("\n");
    return 0;
}

/* -----------------------------------------------
 * データをチェックする関数
 * $0 チェックしたいデータ
 * $1 理想の値
 -----------------------------------------------*/
void data_check(const long data, const long assumption) {
    printf("CHECK: ");
    if(data == assumption){
        print_green_color("OK\n");
    } else {
        print_red_color("NG\n");
    }
}

/* -----------------------------------------------
 * 文字列を緑色で出力する関数
 * $0 出力したい文字列
 -----------------------------------------------*/
void print_green_color(const char *text) {
    printf("\x1b[32m%s\x1b[39m", text);
}

/* -----------------------------------------------
 * 文字列を赤色で出力する関数
 * $0 出力したい文字列
 -----------------------------------------------*/
void print_red_color(const char *text) {
    printf("\x1b[31m%s\x1b[39m", text);
}
