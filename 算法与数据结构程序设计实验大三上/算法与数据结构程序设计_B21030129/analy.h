#pragma warning(disable:4996)
#include<stdlib.h>
#include<string.h>

#define TRUE 1
#define FALSE 0
#define BOOL int
#define MAXSIZE 5000
#define COUNT 20 // ����ͳ�Ƶ������ļ�����
#define LEN 20 // �ļ�������󳤶�


#include<stdio.h>
#include<stdlib.h>
#include<conio.h>


//�������Խṹ
typedef struct {
	int length; //ÿһ�������ĳ���
	int pos; //ÿһ��������λ��
}Fun;

//ͳ�ƽṹ������
typedef struct {
	int comments; //��ע�͵ĸ���
	int comment; //���ע�͸���
	int blank; //���еĸ���
	Fun fun[MAXSIZE]; //����������
	int others; //��ȥ�����д���������Ĵ������
	int funcount; //�����ĸ���
}Analy;

//���Ļ�������ADT
//����Ƿ�Ϊ�մ�
BOOL StrEmpty(char* s);
//�鿴S1���Ƿ���ֵΪS2���Ӵ�,�����򷵻ص�һ���Ӵ���λ�ã������򷵻�-1��
int Find(char* s1, const char* s2);
//��ȡ�ļ��е�һ���ַ�
void HaveLine(FILE* fp, char* s);
//����һ���ַ���ͷ�Ŀո��tab�����ؽضϺ��ϵĴ�ָ��
char* IgnoreB(char* s);
//�ж�һ���ַ��ǲ���ע��
int IsCom(char* s);
//�ж�һ���ַ��ǲ��ǿհ�
BOOL IsBlank(char* s);
int IsFunB(char* s);
void printR(int aver, int comc, int blanks);
//��ӡ������
void print(Analy* An);
void analy(char filename[COUNT][LEN]);
