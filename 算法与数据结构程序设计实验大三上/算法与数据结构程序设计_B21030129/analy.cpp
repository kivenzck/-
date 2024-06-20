#include"analy.h"

using namespace std;


//���Ļ�������ADT
//����Ƿ�Ϊ�մ�
BOOL StrEmpty(char* s)
{
	if (s[0] == '\0')
		return TRUE;
	return FALSE;
}
//�鿴S1���Ƿ���ֵΪS2���Ӵ�,�����򷵻ص�һ���Ӵ���λ�ã������򷵻�-1��
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
//��ȡ�ļ��е�һ���ַ�
void HaveLine(FILE* fp, char* s)
{
	while (!feof(fp))
	{
		*s = fgetc(fp);
		if (*s == '\n') { //����һ�еĽ�β���ʾȡ����һ��
			*s = '\0';
			return;
		}
		s++;
	}
	*s = '\0';
}
//����һ���ַ���ͷ�Ŀո��tab�����ؽضϺ��ϵĴ�ָ��
char* IgnoreB(char* s)
{
	while (*s == ' ' || *s == ' ')
		s++;
	return s;
}
//�ж�һ���ַ��ǲ���ע��
int IsCom(char* s)
{
	int posc, pos1, pos2;
	s = IgnoreB(s);//ȥ�հ�
	posc = Find(s, "//");
	if (posc == 0)//���н���ע�ͣ��޴��룻
		return 1;
	if (posc == -1)
		return 0;
	pos1 = Find(s, "\"");
	pos2 = Find(&s[pos1 + 1], "\"");
	if (posc > pos1 && posc < pos2)
		return 0;
	return 2;
}
//�ж�һ���ַ��ǲ��ǿհ�
BOOL IsBlank(char* s)
{
	s = IgnoreB(s);
	if (*s == '\0')
		return TRUE;
	return FALSE;
}
int IsFunB(char* s)//�жϺ���
{
	int i, j, pos, pos2;
	//�зֺ�,if while for�Ĳ��Ǻ�����ͷ
	if (Find(s, ";") != -1 || Find(s, "if") != -1 || Find(s, "for") != -1 || Find(s, "while") != -1 || Find(s, "switch") != -1)
		return FALSE;
	//û��С���ŵĲ��Ǻ�����ͷ
	if ((pos = Find(s, "(")) == -1)
		return FALSE;
	i = Find(s, " ");//��ͷ�ո�
	s = IgnoreB(s);
	j = Find(s, " ");//int add��ո�
	if (i != -1 && j != -1)//���пո񣬽�i���int add��ո��±�
		i = i > j ? j : i;
	else if (i == -1 && j == -1)//û�ո�
		return FALSE;
	else if (i == -1)//��ͷû�пո�
		i = j;
	if (i > pos)//����ո��������ź��棬һ������
		return FALSE;
	s = &s[i];//ȥ��int 
	s = IgnoreB(s);//ȥ���ո� ֻ������������
	pos2 = Find(s, "(");
	if (*s == '\0' || *s == '(' || pos2 > pos)//���������Ϊ�գ����������ſ�ͷ�����������ų�����int�У�һ������
		return FALSE;
	return TRUE;
}
void printR(int aver, int comc, int blanks)
{
	//�����뼶���ж���׼����������
	int i;
	char Grade[4][15] = { "A","B","C","D" };//�����ĸ������
	//�ж�����ļ���
	if (aver <= 15 && aver >= 10)
		i = 0;
	else if ((aver <= 20 && aver >= 16) || aver <= 9 && aver >= 8)
		i = 1;
	else if ((aver <= 7 && aver >= 5) || aver <= 24 && aver >= 21)
		i = 2;
	else if ((aver < 5) || (aver > 24))
		i = 3;
	printf(" ���뼶��Ϊ %s \n", Grade[i]);
	//�ж�ע�͵ļ���
	if (comc <= 25 && comc >= 15)
		i = 0;
	else if ((comc <= 14 && comc >= 10) || comc <= 30 && comc >= 26)
		i = 1;
	else if ((comc <= 9 && comc >= 5) || comc <= 35 && comc >= 31)
		i = 2;
	else if ((comc < 5) || (comc > 35))
		i = 3;
	printf(" ע�ͼ���Ϊ %s \n", Grade[i]);
	//�ж����еļ���
	if (blanks <= 25 && blanks >= 15)
		i = 0;
	else if ((blanks <= 14 && blanks >= 10) || blanks <= 30 && blanks >= 26)
		i = 1;
	else if ((blanks <= 9 && blanks >= 5) || blanks <= 35 && blanks >= 31)
		i = 2;
	else if ((blanks < 5) || (blanks > 35))
		i = 3;
	printf(" ���м���Ϊ %s \n", Grade[i]);
}
//��ӡ������
void print(Analy* An)
{
	int sum = 0, funcode = 0;//�ܴ��� ������������
	int i, comc, blanks, aver, code;
	for (i = 0; i < An->funcount; i++)//�����Ĵ�������
		funcode += An->fun[i].length;
	//�����еĴ�������
	sum += An->blank;
	sum += An->comments;
	sum += An->comment;
	sum += An->others;
	sum += funcode;
	if (sum == 0)//��ֹ����sumΪ0
		sum = 1;
	if (An->funcount == 0)//��ֹ����mΪ0
		aver = 0;
	else
		aver = funcode / An->funcount;
	comc = (An->comments + An->comment) * 100 / sum;//��ٷֱ�
	blanks = ((An->blank) * 100) / sum;
	code = 100 - comc - blanks; //((funcode + An->others)*100)/sum;
	printf(" ����Դ����������������ʾ\n\n");
	printf(" ��������: %d\n", sum - An->blank - An->comment - An->comments);//�����а������ע�͵ĳ���
	printf(" ע������: %d\n", An->comments + An->comment);
	printf(" ������: %d\n", An->blank);
	printf(" ���� ע�� ����\n");
	printf(" **** **** ****\n");
	printf(" **** **** ****\n");
	printf(" %3d%% %3d%% %3d%%\n", code, comc, blanks);//%%��ʾ�ٷֺ�
	printf(" ���������������Ϊ %d \n", An->funcount);
	printf(" ������ƽ������Ϊ %d\n", aver);
	printf("\n");
	//�����뼶���ж���׼����������
	printR(aver, comc, blanks);
}

void analy(char filename[COUNT][LEN])
{
	FILE* fp;//����Դ�ļ�ָ��
	Analy An;//����ͳ�ƽṹ��
	char s[2000];//�洢ÿ�е��ļ�
	BOOL begin = 0, start = 0;//���ú�����ʼ���
	//���ú�����ʼ������� beginΪ�Ƿ���ֺ��� startΪ�Ƿ���ִ�����
	int i=0, j = -1, pos = 0;//������λ�� ������Ϣ jΪ��������-1
	//c��⺯���ڴ����ŵ�ƥ��,comtype��ע�͵�����
	int c = 0, comtype;//c�жϴ����Ÿ��� comtye�ж�һ���Ƿ�ע�� ��ע�� ���ע��
	An.blank = 0;
	An.comments = 0;
	An.comment = 0;
	An.others = 0;
	An.funcount = 0;
	if ((fp = fopen(filename[i], "r")) == NULL)
	{
		printf("�޷����ļ�%s\n", filename[i]); //���filename[i]
		getchar();//�������
		exit(0);
	}
	pos = 0; //��������һ���ļ��е�λ�ó�ʼ��
	while (!feof(fp))
	{
		HaveLine(fp, s); //���ļ��ж�ȡһ������
		pos++; //ÿ���������ļ��п�ʼ��λ��
		//����ͳ���ļ��еĴ������
		comtype = IsCom(s);//�жϸ����Ƿ�ע�� ��ע�� ��ע��
		if (comtype == 1)
		{
			An.comment++;
			continue;
		}
		if (comtype == 2)//��ע��
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
			j++; //jΪ�����ĸ���-1;
			c = 0;//�����Ÿ�����ʼ��Ϊ0
			begin = TRUE;
			An.fun[j].pos = pos;//����λ�ó�ʼ��
			An.fun[j].length = 1;
		}
		else if (IsBlank(s))//�жϿհ���
			An.blank++;
		else if (begin) {//Ҫ������������ű���д����һ�У����ܺͺ�����ͬһ��
			An.fun[j].length++;//���ں����ڣ�������������
			if (Find(s, "{") != -1) //����Ƿ���뵽�˺�������
			{
				c++;
				start = TRUE;//ɨ�赽�������������
			}
			if (Find(s, "}") != -1)//����Ƿ�һ�������Ľ���
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
	fclose(fp);//�رշ����ļ�
	An.funcount = j + 1; //�Ѻ����ĸ�������
	print(&An); //��ӡ�������
}