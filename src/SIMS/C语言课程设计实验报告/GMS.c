#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <conio.h>

typedef struct student
{
	char num[9];
	char name[9];
	int scorem;
	int scoree;
	int scorec;
	int sum;
	struct student *next;
} Student;

Student *creat(Student *p)//创建链表
{
	Student *p1 = NULL;
	p1 = (Student*)malloc(sizeof(Student));
	p->next = p1;
	p1->next = NULL;
	printf("请输入要添加的学生的信息\n");
	printf("学号：");
	scanf("%s", p1->num);
	printf("姓名: ");
	scanf("%s", p1->name);
	printf("数学成绩：");
	scanf("%d", &p1->scorem);
	printf("英语成绩：");
	scanf("%d", &p1->scoree);
	printf("C语言成绩：");
	scanf("%d", &p1->scorec);
	p1->sum = 0;
	p1->sum = p1->scorem + p1->scorec + p1->scoree;
	printf("总分：%d", p1->sum);
	return p1;
}
void save(Student *p)//将链表从内存保存到文件中
{
	FILE *fp;
	if ((fp = fopen("d:\\学生成绩管理系统.txt", "wb+")) == NULL)
	{
		printf("创建失败!\n");
	}
	do
	{
		p = p->next;
		fwrite(p, sizeof(Student), 1, fp);
	} while (p->next != NULL);
	fclose(fp);
	printf("保存成功!\n");
}
Student *read()//把文件中的数据读到链表中
{
	FILE *fp;
	Student *head = NULL, *p = NULL,*q = NULL;
	if ((fp = fopen("d:\\学生成绩管理系统.txt", "rb+")) == NULL)
	{
		printf("读取时，文件打开失败!\n");
		return NULL;
	}
	p = head = (Student *)malloc(sizeof(Student));
	while(!feof(fp))
	{
		q = (Student *)malloc(sizeof(Student));
		if (fread(q, sizeof(Student), 1, fp) == 1)
		{
			p->next = q;
			q->next = NULL;
			p = p->next;
		}
		else
		{
			free(q);
			break;
		}
	}
	fclose(fp);
	return head;
}
Student *sortsum(Student  *head)//排序函数 
{
	Student *p, *q, *max, *a, *b;
	for (p = head->next;p->next != NULL;p = p->next)
	{
		max = p;
		for (q = p->next;q != NULL;q = q->next)
		{
			if (q->sum > max->sum)
			{
				max = q;
			}
		}
		if (max != p)
		{
			a = p->next;
			b = max->next;
			Student t = *max;
			*max = *p;
			*p = t;
			p->next = a;
			max->next = b;
		}
	}
	return head;
}
void get_psw(char *psw)
{
	int i;
	char ch;
	for (i = 0;(ch = getch()) != '\r';)
	{
		if (ch == '\b')
		{
			if (i > 0)
			{
				putchar('\b');
				putchar(' ');
				putchar('\b');
				i--;
			}
		}
		else
		{
			psw[i++] = ch;
			putchar('*');
		}
	}
	psw[i] = 0;
}

Student *input()//添加函数
{
	char ch;
	Student *p = NULL, *head = read();
	p = head;
	while (p->next != NULL)
	{
		p = p->next;
	}
	do
	{
		p->next = creat(p);
		printf("\n是否继续输入学生信息？( y / n )：\n");
		scanf(" %c", &ch);
		if (ch == 'y' || ch == 'Y')
		{
			p = p->next;
			continue;
		}
		else if (ch == 'n' || ch == 'N')
		{
			save(head);
			break;
		}
		else
		{
			printf("您的输入有误，请重新输入，");
		}
	} while (1);
	return p->next;
}
Student *output()//输出函数，查看全部学生信息
{
	Student *p = read();
	printf("\n   *************************STUDENT***********************\n");
	printf("   -------------------------------------------------------\n");
	printf("   |   学号   |  姓名  |  数学  |  英语  | C语言 |  总分 |\n");
	printf("   -------------------------------------------------------\n");
	do
	{
		if (p == NULL)
		{
			break;
		}
		p = p->next;
		p->sum = p->scorem + p->scoree + p->scorec;
		printf("   | %4s |  %-4s  |  %3d   |   %3d  |  %3d  |  %3d  |\n", p->num,
			p->name, p->scorem, p->scoree, p->scorec, p->sum);
		printf("   -------------------------------------------------------\n");
	} while (p->next != NULL);
	return p;
}
Student *search()//查找函数
{
	int n;
	char a[9];
	Student *p = NULL, *head = NULL;
	printf("请您选择要查找的方式：1 按姓名  2 按学号\n");
	scanf("%d", &n);
	if (n != 1 && n != 2)
	{
		printf("输入有误！");
		return NULL;
	}
	printf("请输入您要查找的学生的%s：\n", n == 1 ? "姓名" : "学号");
	scanf("%s", a);
	p = head = read();
	printf("\n   *************************STUDENT***********************\n");
	printf("   -------------------------------------------------------\n");
	printf("   |   学号   |  姓名  |  数学  |  英语  | C语言 |  总分 |\n");
	printf("   -------------------------------------------------------\n");
	while (p->next != NULL)
	{
		if (p == NULL)
		{
			break;
		}
		p = p->next;
		if (strcmp(n == 1 ? p->name : p->num, a) == 0)
		{
			printf("   | %4s |  %-4s  |  %3d   |   %3d  |  %3d  |  %3d  |\n", p->num,
				p->name, p->scorem, p->scoree, p->scorec, p->sum);
			printf("   -------------------------------------------------------\n");
		}
	} 
	return head;
}
Student *dele()//删除函数
{
	int count = 0;
	Student *p = NULL, *q = NULL, *head = NULL;
	char a[9];
	output();
	printf("请输入需要删除信息的人的姓名：\n");
	scanf("%s", a);
	p = head = read();
	if (head == NULL)
	{
		printf("对不起，暂时没有信息，无法删除。\n");
	}
	while (p->next != NULL)
	{
		if (strcmp(a, p->next->name) == 0)
		{
			q = p->next;
			p->next = q->next;
			free(q);
			count++;
		}
		else
		{
			p = p->next;
		}
	}
	save(head);
	printf("删除%d条记录", count);
	return head;
}
Student *change()//修改函数
{
	int a, count = 0;
	char x[9];
	Student *p = NULL, *head = NULL, *q = NULL;
	output();
	p = head = read();
	if (head == NULL)
	{
		printf("无数据!\n");
		return NULL;
	}
	printf("请输入要修改的人的姓名：\n");
	scanf("%s", x);
	do
	{
		p = p->next;
		if (strcmp(p->name, x) == 0)
		{
			count++;
			printf("\n   *************************STUDENT***********************\n");
			printf("   -------------------------------------------------------\n");
			printf("   |   学号   |  姓名  |  数学  |  英语  | C语言 |  总分 |\n");
			printf("   -------------------------------------------------------\n");
			printf("   | %4s |  %-4s  |  %3d   |   %3d  |  %3d  |  %3d  |\n", p->num,
				p->name, p->scorem, p->scoree, p->scorec, p->sum);
			printf("   -------------------------------------------------------\n");
			printf("请选择修改的内容：\n");
			printf("1.姓名\n");
			printf("2.学号\n");
			printf("3.数学成绩\n");
			printf("4.英语成绩\n");
			printf("5.C成绩\n");
			printf("6.取消\n");
			do
			{
				scanf("%d", &a);
				if (a >= 1 && a <= 6)
				{
					break;
				}
				printf("您输入的数字有误，请重新输入：\n");
			} while (1);
			switch (a)
			{
			case 1:
				printf("请输入更改后的姓名：\n");
				scanf("%s", p->name);
				break;
			case 2:
				printf("请输入更改后的学号：\n");
				scanf("%s", p->num);
				break;
			case 3:
				printf("请输入更改后的数学成绩：\n");
				scanf("%d", &p->scorem);
				break;
			case 4:	printf("请输入更改后的英语成绩：\n");
				scanf("%d", &p->scoree);
				break;
			case 5:
				printf("请输入更改后的C成绩：\n");
				scanf("%d", &p->scorec);
				break;
			case 6:
				a = 0;
				break;
			}
			if (a == 0)
			{
				continue;
			}
			p->sum = p->scorem + p->scoree + p->scorec;
			printf("更改后的总分：%d\n", p->sum);
		}
	} while (p->next != NULL);
	save(head);
	if (count == 0)
	{
		printf("对不起，没有这个人。\n");
	}
	return head;
}
Student *outputsortsum()//总分排序输出
{
	int i = 1;
	Student *head = NULL, *p = NULL;
	head = read();
	sortsum(head);
	p = head->next;
	printf("\n       *************************STUDENT****************************\n");
	printf("       ------------------------------------------------------------\n");
	printf("       | 名次 |   学号   |   姓名 |  数学 |  英语 | C语言 |  总分 |\n");
	printf("       ------------------------------------------------------------\n");
	while (p != NULL)
	{
		printf("       | %3d  | %4s |  %-4s  |  %3d  |  %3d  |  %3d  |  %3d  |\n", i++, p->num,
			p->name, p->scorem, p->scoree, p->scorec, p->sum);
		printf("       ------------------------------------------------------------\n");
		p = p->next;
	}
	return head;
}
Student *statistic()//统计函数
{
	int m = 0;
	Student *head = NULL;
	Student *p, *q;
	p = head = read();
	while (p->next != NULL)
	{
		m++;
		p = p->next;
	} 
	printf("总共有%d个学生信息.\n\n", m);
	q = sortsum(head)->next;
	printf("分数最高的学生的信息:\n");
	printf("\n       ***********************STUDENT*************************\n");
	printf("       -------------------------------------------------------\n");
	printf("       |   学号   |  姓名  |  数学  |  英语  | C语言 |  总分 |\n");
	printf("       -------------------------------------------------------\n");
	printf("       | %4s |  %-4s  |  %3d   |  %3d   |  %3d  |   %3d |\n", q->num,
		q->name, q->scorem, q->scoree, q->scorec, q->sum);
	printf("       -------------------------------------------------------\n");
	return head;
}

void login(int m)
{
	while (1)
	{
		char input[20];
		char psw_admin[20] = { "abcde" };
		char psw_stu[20] = { "12345" };
		printf("请输入密码：");
		get_psw(input);
		if (m == 1 && strcmp(input, psw_admin) == 0)
		{
			printf("\n欢迎进入管理员管理系统 !\n");
			break;
		}
		else if (m == 2 && strcmp(input, psw_stu) == 0)
		{
			printf("\n欢迎进入学生管理系统 !\n");
			break;
		}
		printf("\n这个密码是错误的！\n");
	}
}
void menu(int n)
{
	system("cls");
	if (n == 0)
	{
		printf("******************************************************\n");
		printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
		printf("★★★★★★★★★★★★★★★★★★★★★★★★★★★\n\n");
		printf("                     沈阳建筑大学\n");
		printf("                  教务管理系统欢迎您!\n\n");
		printf("                     请选择您的身份\n\n");
		printf("                     1.管理员\n");
		printf("                     2.学生\n\n");
		printf("                     3.退出系统\n\n");
		printf("★★★★★★★★★★★★★★★★★★★★★★★★★★★\n");
		printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
		printf("******************************************************\n");
		printf("请您选择: ");
	}
	else if (n == 1)
	{
		printf("                            管理员用户\n\n");
		printf("*******************************主菜单****************************\n");
		printf("*                                                               *\n");
		printf("*                         1 添加学生成绩                        *\n");
		printf("*          *              2 查找学生成绩             *          *\n");
		printf("*        *   *            3 删除指定学生           *   *        *\n");
		printf("*      *       *          4 修改学生信息         *       *      *\n");
		printf("*        *   *            5 总分排序信息           *   *        *\n");
		printf("*          *              6 查看全部信息             *          *\n");
		printf("*                         7 统计学生人数                        *\n");
		printf("*                         8 停止程序运行                        *\n");
		printf("*                                                               *\n");
		printf("*****************************************************************\n");
		printf("请您选择：");
	}
	else if (n == 2)
	{
		printf("                            学生用户\n\n");
		printf("*******************************主菜单****************************\n");
		printf("*                                                               *\n");
		printf("*          *              1 查找学生成绩             *          *\n");
		printf("*        *   *            2 总分排序信息           *   *        *\n");
		printf("*      *       *          3 查看全部信息         *       *      *\n");
		printf("*        *   *            4 统计学生人数           *   *        *\n");
		printf("*          *              5 停止程序运行             *          *\n");
		printf("*                                                               *\n");
		printf("*****************************************************************\n");
		printf("请您选择：");
	}
	
}

int main(void)
{
	int a, m;
	int b = 1;
	menu(0);
	do
	{
		scanf("%d", &m);
		if (m == 1 || m == 2)
		{
			break;
		}
		else if (m == 3)
		{
			return 0;
		}
		printf("命令错误，请重新输入！");
	} while (1);
	login(m);

	Student* (*op_admin[7])(void) = {input,search,dele,change,outputsortsum,output,statistic};
	Student* (*op_stu[4])(void) = { search,outputsortsum,output,statistic };
	while (b == 1)
	{
		menu(m);
		scanf("%d", &a);
		if (m == 1 && (a >= 1 && a <= 7))
		{
			op_admin[a - 1]();
		}
		else if (m == 2 && (a >= 1 && a <= 4))
		{
			op_stu[a - 1]();
		}
		else if (m == 1 && a == 8 || m == 2 && a == 5)
		{
			return 0;
		}
		else
		{
			printf("输入错误！\n");
		}
		printf("\n\n请选择接下来的操作：\n");
		printf(" 1 . 返回主菜单      2 . 退出程序\n");
		scanf("%d", &b);
	}
	return 0;
}