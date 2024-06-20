#pragma warning(disable:4996)
#include<stdlib.h>
#include<string.h>

#define TRUE 1
#define FALSE 0
#define BOOL int
#define MAXSIZE 5000
#define COUNT 20 // 可以统计的最大的文件个数
#define LEN 20 // 文件名的最大长度


#include<stdio.h>
#include<stdlib.h>
#include<conio.h>


//函数属性结构
typedef struct {
	int length; //每一个函数的长度
	int pos; //每一个函数的位置
}Fun;

//统计结构的声明
typedef struct {
	int comments; //纯注释的个数
	int comment; //混合注释个数
	int blank; //空行的个数
	Fun fun[MAXSIZE]; //函数的属性
	int others; //除去函数中代码外其余的代码个数
	int funcount; //函数的个数
}Analy;

//串的基本操作ADT
//检测是否为空串
BOOL StrEmpty(char* s);
//查看S1中是否有值为S2的子串,若有则返回第一个子串的位置，若无则返回-1；
int Find(char* s1, const char* s2);
//读取文件中的一行字符
void HaveLine(FILE* fp, char* s);
//忽略一行字符开头的空格和tab，返回截断后上的串指针
char* IgnoreB(char* s);
//判断一行字符是不是注释
int IsCom(char* s);
//判断一行字符是不是空白
BOOL IsBlank(char* s);
int IsFunB(char* s);
void printR(int aver, int comc, int blanks);
//打印输出结果
void print(Analy* An);
void analy(char filename[COUNT][LEN]);
