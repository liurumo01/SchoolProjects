#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

/* 数据模型 */

//时间模型
typedef struct
{
	int hour;
	int min;
} time;
//汽车模型
typedef struct
{
	int num;
	time arrive_park;
	time depart_park;
	time arrive_wait;
	time depart_wait;
	int fee;
} car;
//栈模型
typedef struct
{
	car *base;
	car *top;
} stack;
//队列模型
typedef struct
{
	car *base;
	int front;
	int rear;
	int length;
} queue;
//命令模型
typedef struct
{
	char ch;
	int num;
	time t;
} order;

/* 全局参数 */

//停车场每块区域的空间
const int MAXSIZE = 20;
//执行命令的时间点
time t;
//开放时间和关闭时间
time open_time, close_time;
//停车区域
stack park;
//等候区域
queue wait;
//便道
stack temp;
//待处理的命令列表
order p[20];
//总收入
int money;
//停车总时长
time park_time;
//等待总时长
time wait_time;
//到达辆次
int arrive_amout;
//停车辆次
int park_amount;

/* 函数声明 */

//显示时间
void show_time(time t);
//求时间差
time last_time(time begin, time end);
//时间先后比较
int time_comp(time t1, time t2);

//初始化栈空间
void init_stack(stack *s);
//销毁栈空间
void destory_stack(stack *s);
//判断栈是否为空
int stack_empty(const stack *s);
//将元素压入栈中
void push(stack *s, const car n);
//弹出栈顶元素并返回其值
car pop(stack *s);
//栈中已有的元素数目
int stack_size(const stack *s);

//初始化队列空间
void init_queue(queue *q);
//销毁队列空间
void destory_queue(queue *q);
//判断队列是否已满
int queue_full(const queue *q);
//将元素插入队尾
void join_queue(queue *q, const car n);
//取出队首元素并返回其值
car leave_queue(queue *q);

//配置初始状态、分配空间
void init();
//界面显示
void show();
//读取指令输入
int input();
//指令处理
void deal(int i);
//释放空间
void del();
//命令排序
int comp(const void *a, const void *b);
//查找车辆
int search_car(int i);
//费用计算
void bill(car x);

/* 主函数 */
int main(void)
{
	int i, n;
	init();
	while ((t.hour < close_time.hour) || (t.hour == close_time.hour && t.min <= close_time.min))
	{
		show();
		n = input();
		for (i = 0; i < n; i++)
		{
			deal(i);
		}
	}
	del();
	return 0;
}

/* 函数实现 */

void show_time(time t)
{
	printf("%2d时%2d分\n", t.hour, t.min);
	return;
}

time last_time(time begin, time end)
{
	int x, y;
	time t;
	x = end.min - begin.min;
	y = end.hour - begin.hour;
	t.min = x >= 0 ? x : x + 60;
	y = x < 0 ? y - 1 : y;
	t.hour = y >= 0 ? y : y + 24;
	return t;
}

int time_comp(time t1, time t2)
{
	int cmp;
	if (t1.hour - t2.hour > 0 || (t1.hour == t2.hour && t1.min > t2.min))
	{
		cmp = 1;
	}
	else if (t1.hour == t2.hour && t1.min == t2.min)
	{
		cmp = 0;
	}
	else
	{
		cmp = -1;
	}
	return cmp;
}

void init_stack(stack *s)
{
	s->base = (car *)malloc(MAXSIZE * sizeof(car));
	memset(s->base, 0, sizeof(car));
	s->top = s->base;
	return;
}

void destory_stack(stack *s)
{
	free(s->base);
	s->top = NULL;
	return;
}

int stack_empty(const stack *s)
{
	return s->top == s->base;
}

void push(stack *s, const car n)
{
	if (s->top - s->base == MAXSIZE)
	{
		return;
	}
	*(s->top) = n;
	s->top++;
	return;
}

car pop(stack *s)
{
	return *(--(s->top));
}

int stack_size(const stack *s)
{
	return s->top - s->base;
}

void init_queue(queue *q)
{
	q->base = (car *)malloc(MAXSIZE * sizeof(car));
	memset(q->base, 0, sizeof(car));
	q->front = q->rear = 0;
	q->length = 0;
	return;
}

void destory_queue(queue *q)
{
	free(q->base);
	q->base = NULL;
	q->front = q->rear = q->length = 0;
	return;
}

int queue_full(const queue *q)
{
	return q->length == MAXSIZE;
}

void join_queue(queue *q, const car n)
{
	if (q->length == MAXSIZE)
	{
		return;
	}
	q->base[q->rear] = n;
	q->rear = (q->rear + 1) % MAXSIZE;
	q->length++;
	return;
}

car leave_queue(queue *q)
{
	car n;
	n = q->base[q->front];
	q->front = (q->front + 1) % MAXSIZE;
	q->length--;
	return n;
}

void init(void)
{
	init_stack(&park);
	init_queue(&wait);
	init_stack(&temp);
	printf("开放时间(时 分):");
	scanf("%d %d", &open_time.hour, &open_time.min);
	printf("结束时间(时 分):");
	scanf("%d %d", &close_time.hour, &close_time.min);
	t = open_time;
	return;
}

void show()
{
	int i, x, y, z;
	//状态缓存
	int table[MAXSIZE][3];
	memset(table, 0, MAXSIZE * 3 * sizeof(int));
	//按存储方式直接读取数据保存到状态缓存区
	for (i = 0; i < stack_size(&park); i++)
	{
		table[i][0] = park.base[i].num;
	}
	for (i = 0; i < wait.length; i++)
	{
		table[i][1] = wait.base[(i + wait.front) % MAXSIZE].num;
	}
	for (i = 0; i < stack_size(&temp); i++)
	{
		table[i][2] = temp.base[i].num;
	}
	//屏幕输出
	system("cls");
	printf("        停车场管理系统\n");
	printf("当前时间:");
	show_time(t);
	printf("序号 停车场地 等待队列 让行便道 序号\n");
	printf("    —————        —————\n");
	printf("    |                          |\n");
	for (i = 0; i < MAXSIZE; i++)
	{
		x = table[MAXSIZE - i - 1][0];
		y = table[i][1];
		z = table[MAXSIZE - i - 1][2];
		printf("  %02d|", MAXSIZE - i);
		x ? printf("%8d|", x) : printf("        |");
		y ? printf("%8d|", y) : printf("        |");
		z ? printf("%8d|", z) : printf("        |");
		printf("%02d  \n", MAXSIZE - i);
	}
	printf("    —————        —————\n");
	printf("收费标准:\n");
	printf("停车区3元/30分钟,不足30分钟按30分钟收费\n");
	printf("等待区2元/30分钟,不足30分钟按30分钟收费\n\n");
	//显示延迟
	Sleep(3000);
	return;
}

int input()
{
	int i;
	printf("请输入不多于20条指令\n");
	printf("指令格式:指令代码 车牌号码 执行时刻\n");
	printf("指令代码:A-车辆到达 D-车辆离开 E-输入结束 Q-退出程序\n");
	//读取不超过20条指令,大小写不敏感
	for (i = 0; i < 19; i++)
	{
		printf("指令%d:", i + 1);
		scanf(" %c %d %d %d", &p[i].ch, &p[i].num, &p[i].t.hour, &p[i].t.min);
		//小写转大写
		if (p[i].ch == 'e')
		{
			p[i].ch = 'E';
		}
		else if (p[i].ch == 'a')
		{
			p[i].ch = 'A';
		}
		else if (p[i].ch == 'd')
		{
			p[i].ch = 'D';
		}
		else if (p[i].ch == 'q')
		{
			p[i].ch = 'Q';
		}
		//特殊、错误指令处理
		if (p[i].ch == 'E')
		{
			show();
			break;
		}
		else if (p[i].ch == 'Q')
		{
			del();
			exit(0);
		}
		else if (p[i].ch != 'A' && p[i].ch != 'D')
		{
			printf("输入指令有误,请重新输入\n");
			i--;
			continue;
		}
		if (time_comp(p[i].t, t) < 0)
		{
			printf("该时刻已经过去!\n");
			i--;
			continue;
		}
	}
	//对指令按时间排序
	qsort(p, i + 1, sizeof(order), comp);
	return i + 1;
}

void deal(int i)
{
	//要处理的对象
	car x;
	//对象当前的状态,0-不在停车场中,1-在停车区,2-在等待区
	int pos;
	x.num = p[i].num;
	t = p[i].t;
	pos = search_car(i);
	//车辆到达
	if (p[i].ch == 'A')
	{
		//车辆已经在停车场中
		if (pos)
		{
			printf("该车已经在停车场中!\n");
			Sleep(1000);
			return;
		}
		//停车区有空车位
		if (stack_size(&park) != MAXSIZE)
		{
			x.arrive_wait = t;
			x.depart_wait = t;
			x.arrive_park = t;
			push(&park, x);
			show();
		}
		//停车区无空车位但等待区有空车位
		else if (wait.length != MAXSIZE)
		{
			x.arrive_wait = t;
			x.arrive_park = t;
			x.depart_park = t;
			join_queue(&wait, x);
			show();
		}
		//停车区与等待区均无空车位
		else
		{
			printf("车号%d的车主,对不起,停车区和等待区均无空位,请选择附近其它停车场停放车辆!\n", p[i].num);
			Sleep(1000);
			return;
		}
	}
	//车辆离开
	else if (p[i].ch == 'D')
	{
		//车辆不在停车场中
		if (pos == 0)
		{
			printf("车号为%d的车不在此停车场中!\n", p[i].num);
			Sleep(1000);
			return;
		}
		//车辆在停车区
		else if (pos == 1)
		{
			//前方车辆进入便道让行
			while (x = pop(&park), x.num != p[i].num)
			{
				push(&temp, x);
				show();
			}
			//车辆离开停车场并统计费用
			x.depart_park = t;
			bill(x);
			//便道让行车辆回到停车区
			while (!stack_empty(&temp))
			{
				x = pop(&temp);
				push(&park, x);
				show();
			}
			//停车区出现空位,若等待区有车辆则移入停车区
			if (wait.length)
			{
				x = leave_queue(&wait);
				x.depart_wait = t;
				push(&park, x);
				x.arrive_park = t;
				show();
			}
		}
		//车辆在等待区
		else if (pos == 2)
		{
			//前方车辆进入便道绕行
			while (x = leave_queue(&wait), x.num != p[i].num)
			{
				push(&temp, x);
				show();
			}
			//车辆离开停车场并统计费用
			x.depart_wait = t;
			bill(x);
			//便道车辆移至等待区队尾
			while (!stack_empty(&temp))
			{
				x = pop(&temp);
				join_queue(&wait, x);
				show();
			}
		}
	}
	return;
}

void del()
{
	destory_stack(&park);
	destory_queue(&wait);
	destory_stack(&temp);
	return;
}

int comp(const void *a, const void *b)
{
	//按时间升序排列
	return time_comp((*(order *)a).t, (*(order *)b).t);
}

int search_car(int i)
{
	int j, pos;
	//查找停车区
	for (j = 0, pos = 0; j < stack_size(&park); j++)
	{
		if (park.base[j].num == p[i].num)
		{
			pos = 1;
			break;
		}
	}
	//查找等待区
	for (j = 0; j < wait.length && pos == 0; j++)
	{
		if (wait.base[j].num == p[i].num)
		{
			pos = 2;
			break;
		}
	}
	return pos;
}

void bill(car x)
{
	int payment, a, b, c, d;
	time p = last_time(x.arrive_park, x.depart_park);
	time w = last_time(x.arrive_wait, x.depart_wait);
	//分块计算费用并累加
	a = p.hour * 6;
	b = p.min ? 0 : (p.min >= 30 ? 6 : 3);
	c = w.hour * 6;
	d = w.min ? 0 : (w.min >= 30 ? 6 : 3);
	x.fee = a + b + c + d;
	//屏幕输出
	system("cls");
	printf("车号:%d\n", x.num);
	printf("停车时间:");
	show_time(p);
	printf("等待时间:");
	show_time(w);
	printf("应付:%d元\n", x.fee);
	printf("实付:");
	scanf("%d", &payment);
	printf("找零:%d\n", payment - x.fee);
	printf("付费完成\n欢迎下次再来,祝您一路平安!\n");
	system("pause");
	return;
}