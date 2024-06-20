#include"analy.h"

using namespace std;


//串的基本操作ADT
//检测是否为空串
BOOL StrEmpty(char* s)
{
	if (s[0] == '\0')
		return TRUE;
	return FALSE;
}
//查看S1中是否有值为S2的子串,若有则返回第一个子串的位置，若无则返回-1；
int Find(char* s1, const char* s2)
{
	int i = 0, j = 0;
	if (strlen(s1) < strlen(s2))
		return -1;
	while (s1[i] != '\0')
	{
		if (s1[i] == s2[j])
		{
			i++;
			j++;
			if (s2[j] == '\0')
				return i - j;
			continue;
		}
		i++;
		j = 0;
	}
	return -1;
}
//读取文件中的一行字符
void HaveLine(FILE* fp, char* s)
{
	while (!feof(fp))
	{
		*s = fgetc(fp);
		if (*s == '\n') { //若是一行的结尾则表示取完了一行
			*s = '\0';
			return;
		}
		s++;
	}
	*s = '\0';
}
//忽略一行字符开头的空格和tab，返回截断后上的串指针
char* IgnoreB(char* s)
{
	while (*s == ' ' || *s == ' ')
		s++;
	return s;
}
//判断一行字符是不是注释
int IsCom(char* s)
{
	int posc, pos1, pos2;
	s = IgnoreB(s);//去空白
	posc = Find(s, "//");
	if (posc == 0)//此行仅有注释，无代码；
		return 1;
	if (posc == -1)
		return 0;
	pos1 = Find(s, "\"");
	pos2 = Find(&s[pos1 + 1], "\"");
	if (posc > pos1 && posc < pos2)
		return 0;
	return 2;
}
//判断一行字符是不是空白
BOOL IsBlank(char* s)
{
	s = IgnoreB(s);
	if (*s == '\0')
		return TRUE;
	return FALSE;
}
int IsFunB(char* s)//判断函数
{
	int i, j, pos, pos2;
	//有分号,if while for的不是函数开头
	if (Find(s, ";") != -1 || Find(s, "if") != -1 || Find(s, "for") != -1 || Find(s, "while") != -1 || Find(s, "switch") != -1)
		return FALSE;
	//没有小括号的不是函数开头
	if ((pos = Find(s, "(")) == -1)
		return FALSE;
	i = Find(s, " ");//开头空格
	s = IgnoreB(s);
	j = Find(s, " ");//int add间空格
	if (i != -1 && j != -1)//都有空格，将i变成int add间空格下标
		i = i > j ? j : i;
	else if (i == -1 && j == -1)//没空格
		return FALSE;
	else if (i == -1)//开头没有空格
		i = j;
	if (i > pos)//如果空格在左括号后面，一定不是
		return FALSE;
	s = &s[i];//去掉int 
	s = IgnoreB(s);//去掉空格 只留函数名（）
	pos2 = Find(s, "(");
	if (*s == '\0' || *s == '(' || pos2 > pos)//如果函数名为空，函数名括号开头，函数的括号出现在int中，一定不是
		return FALSE;
	return TRUE;
}
void printR(int aver, int comc, int blanks)
{
	//按代码级别判定标准输出分析结果
	int i;
	char Grade[4][15] = { "A","B","C","D" };//定义四个级别段
	//判定代码的级别
	if (aver <= 15 && aver >= 10)
		i = 0;
	else if ((aver <= 20 && aver >= 16) || aver <= 9 && aver >= 8)
		i = 1;
	else if ((aver <= 7 && aver >= 5) || aver <= 24 && aver >= 21)
		i = 2;
	else if ((aver < 5) || (aver > 24))
		i = 3;
	printf(" 代码级别为 %s \n", Grade[i]);
	//判定注释的级别
	if (comc <= 25 && comc >= 15)
		i = 0;
	else if ((comc <= 14 && comc >= 10) || comc <= 30 && comc >= 26)
		i = 1;
	else if ((comc <= 9 && comc >= 5) || comc <= 35 && comc >= 31)
		i = 2;
	else if ((comc < 5) || (comc > 35))
		i = 3;
	printf(" 注释级别为 %s \n", Grade[i]);
	//判定空行的级别
	if (blanks <= 25 && blanks >= 15)
		i = 0;
	else if ((blanks <= 14 && blanks >= 10) || blanks <= 30 && blanks >= 26)
		i = 1;
	else if ((blanks <= 9 && blanks >= 5) || blanks <= 35 && blanks >= 31)
		i = 2;
	else if ((blanks < 5) || (blanks > 35))
		i = 3;
	printf(" 空行级别为 %s \n", Grade[i]);
}
//打印输出结果
void print(Analy* An)
{
	int sum = 0, funcode = 0;//总代码 函数代码行数
	int i, comc, blanks, aver, code;
	for (i = 0; i < An->funcount; i++)//求函数的代码总数
		funcode += An->fun[i].length;
	//求所有的代码总数
	sum += An->blank;
	sum += An->comments;
	sum += An->comment;
	sum += An->others;
	sum += funcode;
	if (sum == 0)//防止除数sum为0
		sum = 1;
	if (An->funcount == 0)//防止除数m为0
		aver = 0;
	else
		aver = funcode / An->funcount;
	comc = (An->comments + An->comment) * 100 / sum;//求百分比
	blanks = ((An->blank) * 100) / sum;
	code = 100 - comc - blanks; //((funcode + An->others)*100)/sum;
	printf(" 程序源代码分析结果如下所示\n\n");
	printf(" 代码行数: %d\n", sum - An->blank - An->comment - An->comments);//代码中包含混合注释的长度
	printf(" 注释行数: %d\n", An->comments + An->comment);
	printf(" 空行数: %d\n", An->blank);
	printf(" 代码 注释 空行\n");
	printf(" **** **** ****\n");
	printf(" **** **** ****\n");
	printf(" %3d%% %3d%% %3d%%\n", code, comc, blanks);//%%表示百分号
	printf(" 代码包含函数个数为 %d \n", An->funcount);
	printf(" 函数的平均长度为 %d\n", aver);
	printf("\n");
	//按代码级别判定标准输出分析结果
	printR(aver, comc, blanks);
}

void analy(char filename[COUNT][LEN])
{
	FILE* fp;//分析源文件指针
	Analy An;//程序统计结构体
	char s[2000];//存储每行的文件
	BOOL begin = 0, start = 0;//设置函数开始标记
	//设置函数开始结束标记 begin为是否出现函数 start为是否出现大括号
	int i=0, j = -1, pos = 0;//函数的位置 长度信息 j为函数个数-1
	//c检测函数内大括号的匹配,comtype是注释的类型
	int c = 0, comtype;//c判断大括号个数 comtye判断一行是非注释 纯注释 混合注释
	An.blank = 0;
	An.comments = 0;
	An.comment = 0;
	An.others = 0;
	An.funcount = 0;
	if ((fp = fopen(filename[i], "r")) == NULL)
	{
		printf("无法打开文件%s\n", filename[i]); //输出filename[i]
		getchar();//清除缓存
		exit(0);
	}
	pos = 0; //函数在新一个文件中的位置初始化
	while (!feof(fp))
	{
		HaveLine(fp, s); //从文件中读取一行数据
		pos++; //每个函数在文件中开始的位置
		//分类统计文件中的代码个数
		comtype = IsCom(s);//判断该行是非注释 纯注释 混注释
		if (comtype == 1)
		{
			An.comment++;
			continue;
		}
		if (comtype == 2)//混注释
			An.comments++;

		//if (Find(s, "/*") != -1)
		//{
		//	s=IgnoreB(s);

		//	while (1)
		//	{
		//		if (Find(s, "*/") == -1)
		//		{
		//			HaveLine(fp, s);
		//			An.comment++;
		//		}
		//	}
		//}

		if (IsFunB(s))
		{
			j++; //j为函数的个数-1;
			c = 0;//大括号个数初始化为0
			begin = TRUE;
			An.fun[j].pos = pos;//函数位置初始化
			An.fun[j].length = 1;
		}
		else if (IsBlank(s))//判断空白行
			An.blank++;
		else if (begin) {//要求函数的左大括号必须写在下一行，不能和函数名同一行
			An.fun[j].length++;//还在函数内，函数长度自增
			if (Find(s, "{") != -1) //检测是否进入到了函数体内
			{
				c++;
				start = TRUE;//扫描到函数的左大括号
			}
			if (Find(s, "}") != -1)//检测是否一个函数的结束
				c--;
			if (c == 0 && start)
			{
				begin = FALSE;
				start = FALSE;
			}
		}
		else
			An.others++;
	}
	fclose(fp);//关闭分析文件
	An.funcount = j + 1; //把函数的个数保存
	print(&An); //打印分析结果
}