#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

/* ����ģ�� */

//ʱ��ģ��
typedef struct
{
	int hour;
	int min;
} time;
//����ģ��
typedef struct
{
	int num;
	time arrive_park;
	time depart_park;
	time arrive_wait;
	time depart_wait;
	int fee;
} car;
//ջģ��
typedef struct
{
	car *base;
	car *top;
} stack;
//����ģ��
typedef struct
{
	car *base;
	int front;
	int rear;
	int length;
} queue;
//����ģ��
typedef struct
{
	char ch;
	int num;
	time t;
} order;

/* ȫ�ֲ��� */

//ͣ����ÿ������Ŀռ�
const int MAXSIZE = 20;
//ִ�������ʱ���
time t;
//����ʱ��͹ر�ʱ��
time open_time, close_time;
//ͣ������
stack park;
//�Ⱥ�����
queue wait;
//���
stack temp;
//������������б�
order p[20];
//������
int money;
//ͣ����ʱ��
time park_time;
//�ȴ���ʱ��
time wait_time;
//��������
int arrive_amout;
//ͣ������
int park_amount;

/* �������� */

//��ʾʱ��
void show_time(time t);
//��ʱ���
time last_time(time begin, time end);
//ʱ���Ⱥ�Ƚ�
int time_comp(time t1, time t2);

//��ʼ��ջ�ռ�
void init_stack(stack *s);
//����ջ�ռ�
void destory_stack(stack *s);
//�ж�ջ�Ƿ�Ϊ��
int stack_empty(const stack *s);
//��Ԫ��ѹ��ջ��
void push(stack *s, const car n);
//����ջ��Ԫ�ز�������ֵ
car pop(stack *s);
//ջ�����е�Ԫ����Ŀ
int stack_size(const stack *s);
//����ջ����
void copy_stack(stack *dest, const stack *src);

//��ʼ�����пռ�
void init_queue(queue *q);
//���ٶ��пռ�
void destory_queue(queue *q);
//�ж϶����Ƿ�����
int queue_full(const queue *q);
//��Ԫ�ز����β
void join_queue(queue *q, const car n);
//ȡ������Ԫ�ز�������ֵ
car leave_queue(queue *q);
//���ƶ��ж���
void copy_queue(queue *dest, const queue *src);

//���ó�ʼ״̬������ռ�
void init();
//������ʾ
void show();
//��ȡָ������
int input();
//ָ���
void deal(int i);
//�ͷſռ�
void del();

//��������
int comp(const void *a, const void *b);
//���ҳ���
int search_car(int i);
//���ü���
void bill(car x);

/* ������ */

int main()
{
	int i, n;
	init();
	while((t.hour < close_time.hour) || (t.hour == close_time.hour && t.min < close_time.min))
	{
		show();
		n = input();
		for(i = 0; i < n; i++)
		{
			deal(i);
		}
	}
	del();
	return 0;
}

/* ����ʵ�� */

void show_time(time t)
{
	printf("%2dʱ%2d��\n", t.hour, t.min);
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
	if(t1.hour - t2.hour > 0 || (t1.hour == t2.hour && t1.min > t2.min))
	{
		cmp = 1;
	}
	else if(t1.hour == t2.hour && t1.min == t2.min)
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
	s->base = malloc(MAXSIZE * sizeof(car));
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
	if(s->top - s->base == MAXSIZE)
	{
		return;
	}
	* (s->top) = n;
	s->top++;
	return;
}

car pop(stack *s)
{
	return * (-- (s->top));
}

int stack_size(const stack *s)
{
	return s->top - s->base;
}

void copy_stack(stack *dest, const stack *src)
{
	destory_stack(dest);
	init_stack(dest);
	memcpy(dest->base, src->base, MAXSIZE * sizeof(car));
	dest->top = dest->base + (src->top - src->base);
	return;
}

void init_queue(queue *q)
{
	q->base = malloc(MAXSIZE * sizeof(car));
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
	if(q->length == MAXSIZE)
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

void copy_queue(queue *dest, const queue *src)
{
	destory_queue(dest);
	init_queue(dest);
	memcpy(dest->base, src->base, MAXSIZE * sizeof(car));
	dest->front = src->front;
	dest->rear = src->rear;
	dest->length = src->length;
	return;
}

void init()
{
	init_stack(&park);
	init_queue(&wait);
	init_stack(&temp);
	printf("����ʱ��(ʱ ��):");
	scanf("%d %d", &open_time.hour, &open_time.min);
	printf("����ʱ��(ʱ ��):");
	scanf("%d %d", &close_time.hour, &close_time.min);
	t = open_time;
	return;
}

void show()
{
	int i, x, y, z;

	//״̬����
	int table[MAXSIZE][3];
	memset(table, 0, MAXSIZE * 3 * sizeof(int));

	//���洢��ʽֱ�Ӷ�ȡ���ݱ��浽״̬������
	for(i = 0; i < stack_size(&park); i++)
	{
		table[i][0] = park.base[i].num;
	}
	for(i = 0; i < wait.length; i++)
	{
		table[i][1] = wait.base[(i + wait.front) % MAXSIZE].num;
	}
	for(i = 0; i < stack_size(&temp); i++)
	{
		table[i][2] = temp.base[i].num;
	}

	//��Ļ���
	system("cls");
	printf("        ͣ��������ϵͳ\n");
	printf("��ǰʱ��:");
	show_time(t);
	printf("��� ͣ������ �ȴ����� ���б�� ���\n");
	printf("    ����������        ����������\n");
	printf("    |                          |\n");
	for(i = 0; i < MAXSIZE; i++)
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
	printf("    ����������        ����������\n");
	printf("�շѱ�׼:\n");
	printf("ͣ����3Ԫ/30����,����30���Ӱ�30�����շ�\n");
	printf("�ȴ���2Ԫ/30����,����30���Ӱ�30�����շ�\n\n");

	//��ʾ�ӳ�
	Sleep(3000);

	return;
}

int input()
{
	int i;

	printf("�����벻����20��ָ��\n");
	printf("ָ���ʽ:ָ����� ���ƺ��� ִ��ʱ��\n");
	printf("ָ�����:A-�������� D-�����뿪 E-������� Q-�˳�����\n");

	//��ȡ������20��ָ��,��Сд������
	for(i = 0; i < 19; i++)
	{
		printf("ָ��%d:", i + 1);
		scanf(" %c %d %d %d", &p[i].ch, &p[i].num, &p[i].t.hour, &p[i].t.min);

		//Сдת��д
		if(p[i].ch == 'e')
		{
			p[i].ch = 'E';
		}
		else if(p[i].ch == 'a')
		{
			p[i].ch = 'A';
		}
		else if(p[i].ch == 'd')
		{
			p[i].ch = 'D';
		}
		else if(p[i].ch == 'q')
		{
			p[i].ch = 'Q';
		}

		//���⡢����ָ���
		if(p[i].ch == 'E')
		{
			show();
			break;
		}
		else if(p[i].ch == 'Q')
		{
			exit(0);
		}
		else if(p[i].ch != 'A' && p[i].ch != 'D')
		{
			printf("����ָ������,����������\n");
			i--;
			continue;
		}
		if(time_comp(p[i].t, t) < 0)
		{
			printf("��ʱ���Ѿ���ȥ!\n");
			i--;
			continue;
		}
	}

	//��ָ�ʱ������
	qsort(p, i + 1, sizeof(order), comp);

	return i + 1;
}

void deal(int i)
{
	//Ҫ����Ķ���
	car x;
	//����ǰ��״̬,0-����ͣ������,1-��ͣ����,2-�ڵȴ���
	int pos;

	x.num = p[i].num;
	t = p[i].t;
	pos = search_car(i);

	//��������
	if(p[i].ch == 'A')
	{
		//�����Ѿ���ͣ������
		if(pos)
		{
			printf("�ó��Ѿ���ͣ������!\n");
			Sleep(1000);
			return;
		}

		//ͣ�����пճ�λ
		if(stack_size(&park) != MAXSIZE)
		{
			x.arrive_wait = t;
			x.depart_wait = t;
			x.arrive_park = t;
			push(&park, x);
			show();
		}

		//ͣ�����޿ճ�λ���ȴ����пճ�λ
		else if(wait.length != MAXSIZE)
		{
			x.arrive_wait = t;
			x.arrive_park = t;
			x.depart_park = t;
			join_queue(&wait, x);
			show();
		}

		//ͣ������ȴ������޿ճ�λ
		else
		{
			printf("����%d�ĳ���,�Բ���,ͣ�����͵ȴ������޿�λ,��ѡ�񸽽�����ͣ����ͣ�ų���!\n", p[i].num);
			Sleep(1000);
			return;
		}
	}
	//�����뿪
	else if(p[i].ch == 'D')
	{
		//��������ͣ������
		if(pos == 0)
		{
			printf("����Ϊ%d�ĳ����ڴ�ͣ������!\n", p[i].num);
			Sleep(1000);
			return;
		}

		//������ͣ����
		else if(pos == 1)
		{
			//ǰ����������������
			while(x = pop(&park), x.num != p[i].num)
			{
				push(&temp, x);
				show();
			}

			//�����뿪ͣ������ͳ�Ʒ���
			x.depart_park = t;
			bill(x);

			//������г����ص�ͣ����
			while(!stack_empty(&temp))
			{
				x = pop(&temp);
				push(&park, x);
				show();
			}

			//ͣ�������ֿ�λ,���ȴ����г���������ͣ����
			if(wait.length)
			{
				x = leave_queue(&wait);
				x.depart_wait = t;
				push(&park, x);
				x.arrive_park = t;
				show();
			}
		}

		//�����ڵȴ���
		else if(pos == 2)
		{
			//ǰ����������������
			while(x = leave_queue(&wait), x.num != p[i].num)
			{
				push(&temp, x);
				show();
			}

			//�����뿪ͣ������ͳ�Ʒ���
			x.depart_wait = t;
			bill(x);

			//������������ȴ�����β
			while(!stack_empty(&temp))
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
	//��ʱ����������
	return time_comp((*(order *)a).t, (*(order *)b).t);
}

int search_car(int i)
{
	int j, pos;

	//����ͣ����
	for(j = 0, pos = 0; j < stack_size(&park); j++)
	{
		if(park.base[j].num == p[i].num)
		{
			pos = 1;
			break;
		}
	}

	//���ҵȴ���
	for(j = 0; j < wait.length && pos == 0; j++)
	{
		if(wait.base[j].num == p[i].num)
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

	//�ֿ������ò��ۼ�
	a = p.hour * 6;
	b = p.min ? 0 : (p.min >= 30 ? 6 : 3);
	c = w.hour * 6;
	d = w.min ? 0 : (w.min >= 30 ? 6 : 3);
	x.fee = a + b + c + d;

	//��Ļ���
	system("cls");
	printf("����:%d\n", x.num);
	printf("ͣ��ʱ��:");
	show_time(p);
	printf("�ȴ�ʱ��:");
	show_time(w);
	printf("Ӧ��:%dԪ\n", x.fee);
	printf("ʵ��:");
	scanf("%d", &payment);
	printf("����:%d\n", payment - x.fee);
	printf("�������\n��ӭ�´�����,ף��һ·ƽ��!\n");
	system("pause");

	return;
}
