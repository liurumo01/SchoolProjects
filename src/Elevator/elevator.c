#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>

/* 全局常量 */
//楼层数
#define MaxFloor 6
//最大载员
#define MaxPsg 30
//最大等候队列
#define MaxWait 30
//乘客数量最大值
#define MaxSize (MaxPsg + MaxPsg*MaxFloor)
//屏幕显示区行数
#define Column (MaxPsg + MaxWait + 17)
//屏幕显示区列数
#define Row (MaxFloor * 5 + 1)

/*数据模型*/
//乘客
typedef struct
{
	//出发楼层
	int Start;
	//当前楼层
	int Current;
	//目的楼层
	int Dest;
	//在电梯上
	bool OnBoard;
	int Arrive;
	int Leave;
} Passenger;
//电梯
typedef struct
{
	//当前楼层
	int CurrentFloor;
	//当前纵坐标
	int Y;
	//当前运行方向
	int Direction;
	//电梯门状态
	bool DoorIsOpen;
} Elevator;
//命令
typedef struct
{
	int Start;
	int Dest;
	int Arrive;
	int Leave;
} Order;

/*全局参数*/
//乘客
Passenger P[MaxSize];
int PsgNum;
//电梯
Elevator Elv;
//命令
Order O[MaxSize];
int Clock;

/*函数声明*/
//初始设定
void Init();
//接收命令
void Input();
//逐条执行队列中的指令
void Run();
//屏幕显示指令执行结果
void Show();
/*
//队列操作
void InitQueue(Queue *q);
void JoinQueue(Queue *q, const Order x);
Order LeaveQueue(Queue *q);
Order QueueFront(Queue *q);
Order QueueRear(Queue *q);
*/

/*主函数*/
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
	printf("请输入指令(所在楼层 目标楼层 到达时间 离开时间)\n\n");
	printf("-1开头表示结束输入,0开头表示退出程序\n");
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
	int PrevDirection = Elv.Direction；
	//电梯执行动作动;
	do
	{
		//检查当前请求状态 
		//1-
		for (i = Elv.CurrentFloor,GoUp = false; i < MaxFloor; i++)
		{
			
		}
		//电梯到达某一层后选择执行的动作
		if (Elv.Y == (Elv.CurrentFloor - 1) * 5)
		{
			Stop = (Elv.ButtonInside[Elv.CurrentFloor - 1] == true) ||
				(Elv.Direction==1 && 
			Elv.ButtonInside[Elv.CurrentFloor - 1] = false;
			//执行各动作要满足的条件
			//有人要下电梯
			GoOut = Elv.ButtonInside[Elv.CurrentFloor - 1];
			//有人要上电梯
			GoUp = (Elv.Direction == 1 || Elv.nPsgInside==0) && (Elv.ButtonOutside[Elv.CurrentFloor - 1][0] == true);
			GoDown = (Elv.Direction == -1 || Elv.nPsgInside == 0) && (Elv.ButtonOutside[Elv.CurrentFloor - 1][1] == true);
			//电梯到达顶层或底层
			IsTop = (Elv.CurrentFloor == MaxFloor);
			IsBottom = (Elv.CurrentFloor == 1);

			//电梯在某层停下
			if ((GoOut || GoUp || GoDown || IsTop || IsBottom) && (Elv.Y == (Elv.CurrentFloor - 1) * 4))
			{
				Elv.Direction = 0;
				Show();
			}
			//开门
			if ((GoOut || GoUp || GoDown) && (Elv.DoorIsOpen==false))
			{
				Elv.DoorIsOpen = true;
				Show();
			}
			//下电梯
			if (GoOut)
			{
				//找到要下电梯的乘客
				for (i = 0; i < Elv.nPsgInside; i++)
				{
					if (Elv.PsgInside[i].Dest == Elv.CurrentFloor)
					{
						//从电梯内移到电梯外
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
				//下电梯的乘客离开
				PsgNum -= nPsgOutside[Elv.CurrentFloor - 1][1];
				nPsgOutside[Elv.CurrentFloor - 1][1] = 0;
				Show();
				GoOut = false;
			}
			//有人要上楼
			if (GoUp)
			{
				GoUp = false;
				Elv.ButtonOutside[Elv.CurrentFloor - 1][0] = false;
				//找到要上电梯的乘客
				for (i = 0; i < nPsgOutside[Elv.CurrentFloor - 1][0]; i++)
				{
					if (PsgOutside[Elv.CurrentFloor - 1][0][i].Dest > PsgOutside[Elv.CurrentFloor - 1][0][i].Current)
					{
						//从电梯外移到电梯内
						Elv.PsgInside[Elv.nPsgInside] = PsgOutside[Elv.CurrentFloor - 1][0][i];
						Elv.nPsgInside++;
						for (j = i; j < nPsgOutside[Elv.CurrentFloor - 1][0]; j++)
						{
							Elv.PsgInside[j] = Elv.PsgInside[j + 1];
						}
						nPsgOutside[Elv.CurrentFloor - 1][0]--;
						Show();
						//按下对应方向的按钮
						Elv.ButtonInside[Elv.PsgInside[Elv.nPsgInside].Dest - 1] = true;
						GoUp = true;
					}
				}
			}
			else
			{
				//电梯下行且有人要下楼
				Elv.ButtonOutside[Elv.CurrentFloor - 1][1] = false;
				//找到要上电梯的乘客
				for (i = 0; i < nPsgOutside[Elv.CurrentFloor - 1][0]; i++)
				{
					if (PsgOutside[Elv.CurrentFloor - 1][0][i].Dest < PsgOutside[Elv.CurrentFloor - 1][0][i].Current)
					{
						//从电梯外移到电梯内
						Elv.PsgInside[Elv.nPsgInside] = PsgOutside[Elv.CurrentFloor - 1][0][i];
						Elv.nPsgInside++;
						for (j = i; j < nPsgOutside[Elv.CurrentFloor - 1][0]; j++)
						{
							Elv.PsgInside[j] = Elv.PsgInside[j + 1];
						}
						nPsgOutside[Elv.CurrentFloor - 1][0]--;
						Show();
						//按下对应方向的按钮
						Elv.ButtonInside[Elv.PsgInside[Elv.nPsgInside].Dest - 1] = true;
					}
				}
			}
			//关门
			if (Elv.DoorIsOpen == true)
			{
				Elv.DoorIsOpen = false;
				Show();
			}
			//确定下一步运行方向
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
	//初始化
	memset(Buffer, ' ', sizeof(char)*Row*Column);
	for (i = 0; i < Row; i++)
	{
		Buffer[i][Column - 1] = '\0';
	}
	//地平线
	for (i = 4; i < Column - 2; i++)
	{
		Buffer[0][i] = '-';
	}
	//房屋
	for (i = 0 ; i < MaxFloor; i++)
	{
		//楼层标注
		Buffer[i * 5 + 2][0] = i + 1 + '0';
		Buffer[i * 5 + 2][1] = 'F';
		//竖直墙壁
		for (j = 1; j < 6; j++)
		{
			Buffer[i * 5 + j][3] = Buffer[i * 5 + j][MaxPsg + 4] = '|';
			Buffer[i * 5 + j][MaxPsg + MaxWait + 5] = Buffer[i * 5 + j][Column - 2] = '|';
		}
		//水平面
		for (j = MaxPsg + 5; j < MaxPsg + MaxWait + 5; j++)
		{
			Buffer[i * 5 + 5][j] = '-';
		}
	}
	//屋顶
	Buffer[MaxFloor * 5][3] = Buffer[MaxFloor * 5][Column - 2] = ' ';
	for (i = 4; i < Column - 2; i++)
	{
		Buffer[MaxFloor * 5][i] = '-';
	}
	//电梯
	if (Elv.DoorIsOpen == false)
	{
		for (i = 5; i < MaxPsg + 3; i++)
		{
			//电梯底
			Buffer[Elv.Y+1][i] = '-';
			//电梯顶
			Buffer[Elv.Y+4][i] = '-';
		}
		//电梯壁
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
	//按钮和状态显示
	for (i = 0; i < MaxFloor; i++)
	{
		//外部电梯所在楼层显示
		Buffer[i * 5 + 4][MaxPsg + 5] = Elv.CurrentFloor + '0';
		//外部电梯运行方向显示
		Buffer[i * 5 + 3][MaxPsg + 5] = Elv.Direction == -1 ? '2' : (Elv.Direction == 1 ? '1' : '0');
		//外部上行请求按钮
		Buffer[i * 5 + 2][MaxPsg + 5] = Elv.ButtonOutside[i][0] == true ? '*' : ' ';
		//外部下行请求按钮
		Buffer[i * 5 + 1][MaxPsg + 5] = Elv.ButtonOutside[i][1] == true ? '*' : ' ';
		//内部去往楼层按钮
		Buffer[i + 1][MaxPsg + MaxWait + 8] = i + 1 + '0';
		if (Elv.ButtonInside[i] == true)
		{
			Buffer[i + 1][MaxPsg + MaxWait + 10] = '*';
		}
	}
	//内部电梯所在楼层显示
	Buffer[i + 1][MaxPsg + MaxWait + 8] = Elv.CurrentFloor + '0';
	//内部电梯运行方向显示
	Buffer[i + 1][MaxPsg + MaxWait + 10] = Elv.Direction == -1 ? '2' : (Elv.Direction == 1 ? '1' : '0');
	//乘客
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
	printf("电梯模拟状态图\n\n");
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