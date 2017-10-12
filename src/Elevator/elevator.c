#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>

/* ȫ�ֳ��� */
//¥����
#define MaxFloor 6
//�����Ա
#define MaxPsg 30
//���Ⱥ����
#define MaxWait 30
//�˿��������ֵ
#define MaxSize (MaxPsg + MaxPsg*MaxFloor)
//��Ļ��ʾ������
#define Column (MaxPsg + MaxWait + 17)
//��Ļ��ʾ������
#define Row (MaxFloor * 5 + 1)

/*����ģ��*/
//�˿�
typedef struct
{
	//����¥��
	int Start;
	//��ǰ¥��
	int Current;
	//Ŀ��¥��
	int Dest;
	//�ڵ�����
	bool OnBoard;
	int Arrive;
	int Leave;
} Passenger;
//����
typedef struct
{
	//��ǰ¥��
	int CurrentFloor;
	//��ǰ������
	int Y;
	//��ǰ���з���
	int Direction;
	//������״̬
	bool DoorIsOpen;
} Elevator;
//����
typedef struct
{
	int Start;
	int Dest;
	int Arrive;
	int Leave;
} Order;

/*ȫ�ֲ���*/
//�˿�
Passenger P[MaxSize];
int PsgNum;
//����
Elevator Elv;
//����
Order O[MaxSize];
int Clock;

/*��������*/
//��ʼ�趨
void Init();
//��������
void Input();
//����ִ�ж����е�ָ��
void Run();
//��Ļ��ʾָ��ִ�н��
void Show();
/*
//���в���
void InitQueue(Queue *q);
void JoinQueue(Queue *q, const Order x);
Order LeaveQueue(Queue *q);
Order QueueFront(Queue *q);
Order QueueRear(Queue *q);
*/

/*������*/
int main(void)
{
	Init();
	while (1)
	{
		Input();
		Run();
		Show();
	}
	return 0;
}

void Init()
{
	int i;
	Clock = 0;
	Elv.CurrentFloor = 1;
	Elv.DoorIsOpen = false;
	Elv.Y = 0;
	Elv.Direction = 0;
	return;
}

void Input()
{
	int i;
	printf("������ָ��(����¥�� Ŀ��¥�� ����ʱ�� �뿪ʱ��)\n\n");
	printf("-1��ͷ��ʾ��������,0��ͷ��ʾ�˳�����\n");
	for (i = 0;i<MaxSize; i++)
	{
		scanf("%d %d %d %d", &P[i].Start, &P[i].Dest,&P[i].Arrive,&P[i].Leave);
		if (P[i].Start == -1)
		{
			break;
		}
		else if (P[i].Start==0)
		{
			exit(0);
		}
		P[i].Current = P[i].Start;
		P[i].OnBoard = false;
		PsgNum++;
	}
	qsort(P, PsgNum, sizeof(P[0]), ByArrive);
	return;
}

void Run()
{
	while (Elv.Y == Elv.(CurrentFloor - 1) * 5 && PsgNum>=0)
	{
		int i,n;
		Passenger *p, *q;
		n = Elv.CurrentFloor - 1;
		qsort(P, PsgNum, sizeof(P[0]), ByDest);
		for (i = 0; i < PsgNum; i++)
		{
			if (P[i].Dest == n && P[i].OnBoard == true)
			{
				p = &P[i];
				break;
			}
		}
		qsort(P, PsgNum, sizeof(P[0]), ByStart);
		for (i = 0; i < PsgNum; i++)
		{
			if (P[i].Start == n && P[i].OnBoard == false)
			{

			}
		}
	}
	int i, j;
	bool Stop,GoOut, GoUp, GoDown, IsTop, IsBottom;
	int PrevDirection = Elv.Direction��
	//����ִ�ж�����;
	do
	{
		//��鵱ǰ����״̬ 
		//1-
		for (i = Elv.CurrentFloor,GoUp = false; i < MaxFloor; i++)
		{
			
		}
		//���ݵ���ĳһ���ѡ��ִ�еĶ���
		if (Elv.Y == (Elv.CurrentFloor - 1) * 5)
		{
			Stop = (Elv.ButtonInside[Elv.CurrentFloor - 1] == true) ||
				(Elv.Direction==1 && 
			Elv.ButtonInside[Elv.CurrentFloor - 1] = false;
			//ִ�и�����Ҫ���������
			//����Ҫ�µ���
			GoOut = Elv.ButtonInside[Elv.CurrentFloor - 1];
			//����Ҫ�ϵ���
			GoUp = (Elv.Direction == 1 || Elv.nPsgInside==0) && (Elv.ButtonOutside[Elv.CurrentFloor - 1][0] == true);
			GoDown = (Elv.Direction == -1 || Elv.nPsgInside == 0) && (Elv.ButtonOutside[Elv.CurrentFloor - 1][1] == true);
			//���ݵ��ﶥ���ײ�
			IsTop = (Elv.CurrentFloor == MaxFloor);
			IsBottom = (Elv.CurrentFloor == 1);

			//������ĳ��ͣ��
			if ((GoOut || GoUp || GoDown || IsTop || IsBottom) && (Elv.Y == (Elv.CurrentFloor - 1) * 4))
			{
				Elv.Direction = 0;
				Show();
			}
			//����
			if ((GoOut || GoUp || GoDown) && (Elv.DoorIsOpen==false))
			{
				Elv.DoorIsOpen = true;
				Show();
			}
			//�µ���
			if (GoOut)
			{
				//�ҵ�Ҫ�µ��ݵĳ˿�
				for (i = 0; i < Elv.nPsgInside; i++)
				{
					if (Elv.PsgInside[i].Dest == Elv.CurrentFloor)
					{
						//�ӵ������Ƶ�������
						PsgOutside[Elv.CurrentFloor - 1][1][nPsgOutside[Elv.CurrentFloor - 1][1]] = Elv.PsgInside[i];
						for (j = i; j < Elv.nPsgInside; j++)
						{
							Elv.PsgInside[j] = Elv.PsgInside[j + 1];
						}
						Elv.nPsgInside--;
						nPsgOutside[Elv.CurrentFloor - 1][1]++;
						Show();
					}
				}
				Elv.ButtonInside[Elv.CurrentFloor - 1] = false;
				//�µ��ݵĳ˿��뿪
				PsgNum -= nPsgOutside[Elv.CurrentFloor - 1][1];
				nPsgOutside[Elv.CurrentFloor - 1][1] = 0;
				Show();
				GoOut = false;
			}
			//����Ҫ��¥
			if (GoUp)
			{
				GoUp = false;
				Elv.ButtonOutside[Elv.CurrentFloor - 1][0] = false;
				//�ҵ�Ҫ�ϵ��ݵĳ˿�
				for (i = 0; i < nPsgOutside[Elv.CurrentFloor - 1][0]; i++)
				{
					if (PsgOutside[Elv.CurrentFloor - 1][0][i].Dest > PsgOutside[Elv.CurrentFloor - 1][0][i].Current)
					{
						//�ӵ������Ƶ�������
						Elv.PsgInside[Elv.nPsgInside] = PsgOutside[Elv.CurrentFloor - 1][0][i];
						Elv.nPsgInside++;
						for (j = i; j < nPsgOutside[Elv.CurrentFloor - 1][0]; j++)
						{
							Elv.PsgInside[j] = Elv.PsgInside[j + 1];
						}
						nPsgOutside[Elv.CurrentFloor - 1][0]--;
						Show();
						//���¶�Ӧ����İ�ť
						Elv.ButtonInside[Elv.PsgInside[Elv.nPsgInside].Dest - 1] = true;
						GoUp = true;
					}
				}
			}
			else
			{
				//��������������Ҫ��¥
				Elv.ButtonOutside[Elv.CurrentFloor - 1][1] = false;
				//�ҵ�Ҫ�ϵ��ݵĳ˿�
				for (i = 0; i < nPsgOutside[Elv.CurrentFloor - 1][0]; i++)
				{
					if (PsgOutside[Elv.CurrentFloor - 1][0][i].Dest < PsgOutside[Elv.CurrentFloor - 1][0][i].Current)
					{
						//�ӵ������Ƶ�������
						Elv.PsgInside[Elv.nPsgInside] = PsgOutside[Elv.CurrentFloor - 1][0][i];
						Elv.nPsgInside++;
						for (j = i; j < nPsgOutside[Elv.CurrentFloor - 1][0]; j++)
						{
							Elv.PsgInside[j] = Elv.PsgInside[j + 1];
						}
						nPsgOutside[Elv.CurrentFloor - 1][0]--;
						Show();
						//���¶�Ӧ����İ�ť
						Elv.ButtonInside[Elv.PsgInside[Elv.nPsgInside].Dest - 1] = true;
					}
				}
			}
			//����
			if (Elv.DoorIsOpen == true)
			{
				Elv.DoorIsOpen = false;
				Show();
			}
			//ȷ����һ�����з���
			for (i = Elv.CurrentFloor+1,Elv.Direction=-1; i < MaxFloor; i++)
			{
				if (Elv.ButtonInside[i - 1] == true)
				{
					Elv.Direction = 1;
					break;
				}
				if (Elv.ButtonOutside[i - 1][0] == true || Elv.ButtonOutside[i - 1][1] == true)
				{
					Elv.Direction = 1;
					break;
				}
			}
		}
		Elv.Y += Elv.Direction;
		Elv.CurrentFloor = Elv.Y / 5 + 1;
		Show();
	} while (PsgNum!=0);
}

void Show()
{
	int i, j;
	system("cls");
	char Buffer[Row][Column];
	//��ʼ��
	memset(Buffer, ' ', sizeof(char)*Row*Column);
	for (i = 0; i < Row; i++)
	{
		Buffer[i][Column - 1] = '\0';
	}
	//��ƽ��
	for (i = 4; i < Column - 2; i++)
	{
		Buffer[0][i] = '-';
	}
	//����
	for (i = 0 ; i < MaxFloor; i++)
	{
		//¥���ע
		Buffer[i * 5 + 2][0] = i + 1 + '0';
		Buffer[i * 5 + 2][1] = 'F';
		//��ֱǽ��
		for (j = 1; j < 6; j++)
		{
			Buffer[i * 5 + j][3] = Buffer[i * 5 + j][MaxPsg + 4] = '|';
			Buffer[i * 5 + j][MaxPsg + MaxWait + 5] = Buffer[i * 5 + j][Column - 2] = '|';
		}
		//ˮƽ��
		for (j = MaxPsg + 5; j < MaxPsg + MaxWait + 5; j++)
		{
			Buffer[i * 5 + 5][j] = '-';
		}
	}
	//�ݶ�
	Buffer[MaxFloor * 5][3] = Buffer[MaxFloor * 5][Column - 2] = ' ';
	for (i = 4; i < Column - 2; i++)
	{
		Buffer[MaxFloor * 5][i] = '-';
	}
	//����
	if (Elv.DoorIsOpen == false)
	{
		for (i = 5; i < MaxPsg + 3; i++)
		{
			//���ݵ�
			Buffer[Elv.Y+1][i] = '-';
			//���ݶ�
			Buffer[Elv.Y+4][i] = '-';
		}
		//���ݱ�
		Buffer[Elv.Y + 2][4] = Buffer[Elv.Y + 2][MaxPsg + 3] = '|';
		Buffer[Elv.Y + 3][4] = Buffer[Elv.Y + 3][MaxPsg + 3] = '|';
	}
	else
	{
		for (i = 5; i < MaxPsg + 4; i++)
		{
			Buffer[Elv.Y + 1][i] = '-';
			Buffer[Elv.Y + 4][i] = '-';
		}
		Buffer[Elv.Y + 2][MaxPsg + 4] = Buffer[Elv.Y + 3][MaxPsg + 4] = ' ';
		Buffer[Elv.Y * 5 + 2][4] = Buffer[Elv.Y * 5 + 3][4] = '|';
	}
	//��ť��״̬��ʾ
	for (i = 0; i < MaxFloor; i++)
	{
		//�ⲿ��������¥����ʾ
		Buffer[i * 5 + 4][MaxPsg + 5] = Elv.CurrentFloor + '0';
		//�ⲿ�������з�����ʾ
		Buffer[i * 5 + 3][MaxPsg + 5] = Elv.Direction == -1 ? '2' : (Elv.Direction == 1 ? '1' : '0');
		//�ⲿ��������ť
		Buffer[i * 5 + 2][MaxPsg + 5] = Elv.ButtonOutside[i][0] == true ? '*' : ' ';
		//�ⲿ��������ť
		Buffer[i * 5 + 1][MaxPsg + 5] = Elv.ButtonOutside[i][1] == true ? '*' : ' ';
		//�ڲ�ȥ��¥�㰴ť
		Buffer[i + 1][MaxPsg + MaxWait + 8] = i + 1 + '0';
		if (Elv.ButtonInside[i] == true)
		{
			Buffer[i + 1][MaxPsg + MaxWait + 10] = '*';
		}
	}
	//�ڲ���������¥����ʾ
	Buffer[i + 1][MaxPsg + MaxWait + 8] = Elv.CurrentFloor + '0';
	//�ڲ��������з�����ʾ
	Buffer[i + 1][MaxPsg + MaxWait + 10] = Elv.Direction == -1 ? '2' : (Elv.Direction == 1 ? '1' : '0');
	//�˿�
	for (i = 0; i < Elv.nPsgInside; i++)
	{
		Buffer[Elv.Y + 2][i + 6] = '%';
	}
	for (i = 0; i < MaxFloor; i++)
	{
		for (j = 0; j < nPsgOutside[i][0]; j++)
		{
			Buffer[i * 5 + 2][MaxPsg + j + 6] = '%';
		}
	}
	printf("����ģ��״̬ͼ\n\n");
	for (i = Row - 1; i >-1; i--)
	{
		printf("%s\n", Buffer[i]);
	}
	Sleep(1000);
}

int ByDest(const void *a, const void *b)
{
	return (*(Passenger *)a).Dest > (*(Passenger *)b).Dest ? 1 : -1;
}

int ByStart(const void *a, const void *b)
{
	return (*(Passenger *)a).Start > (*(Passenger *)b).Start ? 1 : -1;
}

int ByArrive(const void *a, const void *b)
{
	return (*(Passenger *)a).Arrive > (*(Passenger *)b).Arrive ? 1 : -1;
}

/*
1 3 
2 5
-1 -1
*/