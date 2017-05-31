#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#define N 23
void FileIn();
void FileOut();
void HideCursor();
void ShowCursor();
void Color(int cl);
void Gotoxy(int x, int y);
void Initialize();
void Manual();
void Menu();
void ClsScr();
void Game();
void Rank();
char KeyPress(char c);
int Draw(char c);

struct record
{
	char name[10];
	int score;
}r[5];
int		count = 0;
int		score = 0;
int		plate[N][N] = {0};
int		apple[2];
int		head[2] = {N/2, N/2};
int		tail[2] = {N/2, N/2};

int main()		//���ø�������
{
	FileIn();
	Initialize();
	Manual();
	Menu();
	Gotoxy(0, N);
	FileOut();
}

void FileIn()		//�ļ���ȡ
{
	FILE *fp;

	if((fp=fopen("record.txt","a+"))==NULL)		//���ļ�record.txt
	{
		printf("File open error!\n");
		exit(0);
	}
	printf("File reading...\n");

	while(!feof(fp))
	{
		if(fscanf(fp,"%s %d\n", r[count].name, &r[count].score)!=-1)		//��ȡ����
		{
			count++;
		}
	}

	printf("succeed.\n");
	if(fclose(fp))		//�ر��ļ�������ļ�д������
	{
		printf("can't close the file!\n");
		exit(0);
	}
	system("pause");
	system("cls");
}

void FileOut()		//�ļ�д��
{
	FILE *fp;
	int i;
	if((fp=fopen("record.txt","w"))==NULL)		//���ļ�
	{
		printf("File open error!\n");
		exit(0);
	}
	for(i = 0; i<count; i++)		//д������
	{
		fprintf(fp,"%s %d\n", r[i].name, r[i].score);
	}
	printf("thanks for using!\n");

	if(fclose(fp))		//�ر��ļ�
	{
		printf("can't close the file!\n");
		exit(0);
	}
}

void HideCursor()		//������ʹ��꡾��˸�����ɼ�
{
	CONSOLE_CURSOR_INFO		cursor_info = {1, 0};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void ShowCursor()		//������ʹ��꡾��˸�����ɼ�
{
	CONSOLE_CURSOR_INFO		cursor_info = {1, 1};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void Color(int cl)         //��ɫ����
{
    HANDLE		hConsole = GetStdHandle((STD_OUTPUT_HANDLE)) ;
    SetConsoleTextAttribute(hConsole,cl);
}

void Gotoxy(int x, int y)		//�ƶ���굽ָ��λ��
{
	CONSOLE_SCREEN_BUFFER_INFO		csbiInfo;
    HANDLE		hConsoleOut;

    hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsoleOut,&csbiInfo);

    csbiInfo.dwCursorPosition.X = x;
    csbiInfo.dwCursorPosition.Y = y;
    SetConsoleCursorPosition(hConsoleOut,csbiInfo.dwCursorPosition);
}

void Initialize()		//��ʼ��
{
	Gotoxy(0, 0);
	int		i, j;
	srand((unsigned)time(NULL));
	HideCursor();
	SetConsoleTitle("̰����___by:YY");

	for(i = 1; i < N-1; i++)		//�滭���̣�������plate��ֵ��1Ϊ'  '��0Ϊ'��'
	{
		for(j = 1; j < N-1; j++)
		{
			plate[i][j] = 1;
		}
	}
	for(i = 0; i < N; i++)
	{
		for(j = 0; j < N; j++)
		{
			if(plate[i][j] == 0)
			{
				Color(4);
				printf("��");
			}
			else
			{
				printf("  ");
			}
		}
		printf("\n");
	}

	Color(8|1|2|4);		//��ƻ��
	do
	{
		apple[0] = rand()%(N-2)+1;
		apple[1] = rand()%(N-2)+1;
	}while(apple[0]==N/2 && apple[1]==N/2);
	Gotoxy(apple[0]*2, apple[1]);
	printf("��");

	Gotoxy((N/2)*2, N/2);		//����
	printf("��");
	Gotoxy(0, N+1);
}

void Manual()		//ʹ��˵����������ʾ
{
	Gotoxy(N*2+6, 2);
	Color(10);
	printf("�� W S A D �ƶ�����");
	Gotoxy(N*2+6, 4);
	printf("�� space ��ѡ��");
	Gotoxy(N*2+6, 8);
	Color(8);
	printf("�����ڵĵ÷�Ϊ: 0");
}

void Menu()		//ѡ��˵�
{
	char	c;
	int		i;

	do
	{
		i = 12;
		Gotoxy(N*2+8, 12);
		Color(8);
		printf("��ʼ��Ϸ");
		Gotoxy(N*2+9, 14);
		printf("���а�");
		Gotoxy(N*2+8, 16);
		printf("�˳���Ϸ");
		Gotoxy(N*2+6, i);
		printf("��");
		Gotoxy(N*2+16, i);
		printf("��");
		do		//�ƶ�"��"��"��"
		{
			c = getch();
			switch(c)
			{
			case 'w':case 'W':
				if(i > 12)
				{
					Gotoxy(N*2+6, i);
					printf("  ");
					Gotoxy(N*2+16, i);
					printf("  ");
					i-=2;
					Gotoxy(N*2+6, i);
					printf("��");
					Gotoxy(N*2+16, i);
					printf("��");
				}
				break;
			case 's':case 'S':
				if(i < 16)
				{
					Gotoxy(N*2+6, i);
					printf("  ");
					Gotoxy(N*2+16, i);
					printf("  ");
					i+=2;
					Gotoxy(N*2+6, i);
					printf("��");
					Gotoxy(N*2+16, i);
					printf("��");
				}
				break;
			}
		}while(c != ' ');

		if(i == 12)		//�ж�ѡ��Ĺ���
		{
			ClsScr();
			Game();
			Initialize();
		}
		else if(i == 14)
		{
			ClsScr();
			Rank();
		}
	}while(i != 16);
}

void ClsScr()		//����˵�
{
	Gotoxy(N*2+6, 12);
	printf("            ");
	Gotoxy(N*2+6, 14);
	printf("            ");
	Gotoxy(N*2+6, 16);
	printf("            ");
}

void Game()		//��ʼ��Ϸ
{
	int		i, j;
	char	c;
	int		live = 1;
	while(1)		//��Ϸ����
	{
		c = KeyPress(c);
		live = Draw(c);
		Sleep(300-score/2);
		setbuf(stdin, NULL);	//�������WASD���ﵽ��ʱ������Ч��
		if(live == -1)
			break;
	}

	for(i = 0; i <= count; i++)		//�жϷ����Ƿ���ڼ�¼
	{
		if(score > r[i].score)
		{
			for(j = count; j >= i; j--)
			{
				if(j < 5)
					r[j] = r[j-1];
			}
			Gotoxy(N*2+6, 12);
			printf("You break the record!");
			ShowCursor();
			Gotoxy(N*2+6, 13);
			printf("Input your name: ");
			scanf("%s", r[i].name);
			r[i].score = score;
			Gotoxy(N*2+6, 12);
			printf("                     ");
			Gotoxy(N*2+6, 13);
			printf("                           ");
			if(count < 5)
				count++;
			break;
		}
	}

	for(i = 1; i < N-1; i++)		//������Ϸ����ʼ����Ϸ���漰����
	{
		for(j = 1; j< N-1; j++)
		{
			plate[i][j] = 1;
		}
	}
	for(i = 0; i < 2; i++)
	{
		head[i] = N/2;
		tail[i] = N/2;
	}
	score = 0;
	Gotoxy(N*2+22, 8);
	printf("%-4d", score);
	Gotoxy(0, N);
}

void Rank()		//���а�
{
	int		i, j = 12;
	char	c;
	for(i = 0; i < 5; i++)
	{
		Gotoxy(N*2+6, j);
		printf("%d. %-10s %-4d", i+1, r[i].name, r[i].score);
		j++;
	}

	do		//���ز˵�
	{
		Gotoxy(N*2+8, j);
		printf("�����ء�");
		c = getch();
	}while(c != ' ');

	for(i = 0; i < 6; i++)		//������а�
	{
		Gotoxy(N*2+6, 12+i);
		printf("                  ");
	}
}

char KeyPress(char c)		//��ⰴ��
{
	char	temp;
	if(kbhit())		//�ж��Ƿ��а���
	{
		Gotoxy(0, N+1);
		temp = getch();
	}
	if(temp=='w' || temp=='W' || temp=='s' || temp=='S' || temp=='a' || temp=='A' || temp=='d' || temp=='D')		//��ֹ��һ�����ߺ�������
	{
		switch(temp)
		{
		case 'w':case 'W':
			if(c=='s' || c=='S')break;
			else
				return temp;
		case 's':case 'S':
			if(c=='w' || c=='W')break;
			else
				return temp;
		case 'a':case 'A':
			if(c=='d' || c=='D')break;
			else
				return temp;
		case 'd':case 'D':
			if(c=='a' || c=='A')break;
			else
				return temp;
		}
	}
	return c;
}

int Draw(char c)		//���ƶ���ͼ
{
	switch(c)		//������ͷ����Ԫ�ص�ֵ���Ա���β��ȡ
	{
	case 'w':case 'W':plate[head[0]][head[1]] = 2;head[1]--;break;
	case 's':case 'S':plate[head[0]][head[1]] = 3;head[1]++;break;
	case 'a':case 'A':plate[head[0]][head[1]] = 4;head[0]--;break;
	case 'd':case 'D':plate[head[0]][head[1]] = 5;head[0]++;break;
	}

	if(plate[head[0]][head[1]] == 1)		//�߲���ײ��ǽ�Լ����Ե��Լ�ʱ��
	{
		if(head[0]!=apple[0] || head[1]!=apple[1])		//û�Ե�ƻ��
		{
			Gotoxy(tail[0]*2, tail[1]);
			printf("  ");
			switch(plate[tail[0]][tail[1]])
			{
			case 2:plate[tail[0]][tail[1]] = 1;tail[1]--;break;
			case 3:plate[tail[0]][tail[1]] = 1;tail[1]++;break;
			case 4:plate[tail[0]][tail[1]] = 1;tail[0]--;break;
			case 5:plate[tail[0]][tail[1]] = 1;tail[0]++;break;
			}
		}
		else		//�Ե�ƻ��ʱ��
		{
			score+=10;
			do
			{
				apple[0] = rand()%(N-2)+1;
				apple[1] = rand()%(N-2)+1;
			}while(plate[apple[0]][apple[1]]==2 || plate[apple[0]][apple[1]]==3 || plate[apple[0]][apple[1]]==4 || plate[apple[0]][apple[1]]==5);
			Gotoxy(apple[0]*2, apple[1]);
			Color(8|1|2|4);
			printf("��");
			Gotoxy(N*2+22, 8);
			printf("%d", score);
		}
		Gotoxy(head[0]*2, head[1]);
		Color(8|1|2|4);
		printf("��");
		return 1;
	}
	return -1;
}


