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

Student *creat(Student *p)//��������
{
	Student *p1 = NULL;
	p1 = (Student*)malloc(sizeof(Student));
	p->next = p1;
	p1->next = NULL;
	printf("������Ҫ��ӵ�ѧ������Ϣ\n");
	printf("ѧ�ţ�");
	scanf("%s", p1->num);
	printf("����: ");
	scanf("%s", p1->name);
	printf("��ѧ�ɼ���");
	scanf("%d", &p1->scorem);
	printf("Ӣ��ɼ���");
	scanf("%d", &p1->scoree);
	printf("C���Գɼ���");
	scanf("%d", &p1->scorec);
	p1->sum = 0;
	p1->sum = p1->scorem + p1->scorec + p1->scoree;
	printf("�ܷ֣�%d", p1->sum);
	return p1;
}
void save(Student *p)//��������ڴ汣�浽�ļ���
{
	FILE *fp;
	if ((fp = fopen("d:\\ѧ���ɼ�����ϵͳ.txt", "wb+")) == NULL)
	{
		printf("����ʧ��!\n");
	}
	do
	{
		p = p->next;
		fwrite(p, sizeof(Student), 1, fp);
	} while (p->next != NULL);
	fclose(fp);
	printf("����ɹ�!\n");
}
Student *read()//���ļ��е����ݶ���������
{
	FILE *fp;
	Student *head = NULL, *p = NULL,*q = NULL;
	if ((fp = fopen("d:\\ѧ���ɼ�����ϵͳ.txt", "rb+")) == NULL)
	{
		printf("��ȡʱ���ļ���ʧ��!\n");
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
Student *sortsum(Student  *head)//������ 
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

Student *input()//��Ӻ���
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
		printf("\n�Ƿ��������ѧ����Ϣ��( y / n )��\n");
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
			printf("���������������������룬");
		}
	} while (1);
	return p->next;
}
Student *output()//����������鿴ȫ��ѧ����Ϣ
{
	Student *p = read();
	printf("\n   *************************STUDENT***********************\n");
	printf("   -------------------------------------------------------\n");
	printf("   |   ѧ��   |  ����  |  ��ѧ  |  Ӣ��  | C���� |  �ܷ� |\n");
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
Student *search()//���Һ���
{
	int n;
	char a[9];
	Student *p = NULL, *head = NULL;
	printf("����ѡ��Ҫ���ҵķ�ʽ��1 ������  2 ��ѧ��\n");
	scanf("%d", &n);
	if (n != 1 && n != 2)
	{
		printf("��������");
		return NULL;
	}
	printf("��������Ҫ���ҵ�ѧ����%s��\n", n == 1 ? "����" : "ѧ��");
	scanf("%s", a);
	p = head = read();
	printf("\n   *************************STUDENT***********************\n");
	printf("   -------------------------------------------------------\n");
	printf("   |   ѧ��   |  ����  |  ��ѧ  |  Ӣ��  | C���� |  �ܷ� |\n");
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
Student *dele()//ɾ������
{
	int count = 0;
	Student *p = NULL, *q = NULL, *head = NULL;
	char a[9];
	output();
	printf("��������Ҫɾ����Ϣ���˵�������\n");
	scanf("%s", a);
	p = head = read();
	if (head == NULL)
	{
		printf("�Բ�����ʱû����Ϣ���޷�ɾ����\n");
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
	printf("ɾ��%d����¼", count);
	return head;
}
Student *change()//�޸ĺ���
{
	int a, count = 0;
	char x[9];
	Student *p = NULL, *head = NULL, *q = NULL;
	output();
	p = head = read();
	if (head == NULL)
	{
		printf("������!\n");
		return NULL;
	}
	printf("������Ҫ�޸ĵ��˵�������\n");
	scanf("%s", x);
	do
	{
		p = p->next;
		if (strcmp(p->name, x) == 0)
		{
			count++;
			printf("\n   *************************STUDENT***********************\n");
			printf("   -------------------------------------------------------\n");
			printf("   |   ѧ��   |  ����  |  ��ѧ  |  Ӣ��  | C���� |  �ܷ� |\n");
			printf("   -------------------------------------------------------\n");
			printf("   | %4s |  %-4s  |  %3d   |   %3d  |  %3d  |  %3d  |\n", p->num,
				p->name, p->scorem, p->scoree, p->scorec, p->sum);
			printf("   -------------------------------------------------------\n");
			printf("��ѡ���޸ĵ����ݣ�\n");
			printf("1.����\n");
			printf("2.ѧ��\n");
			printf("3.��ѧ�ɼ�\n");
			printf("4.Ӣ��ɼ�\n");
			printf("5.C�ɼ�\n");
			printf("6.ȡ��\n");
			do
			{
				scanf("%d", &a);
				if (a >= 1 && a <= 6)
				{
					break;
				}
				printf("������������������������룺\n");
			} while (1);
			switch (a)
			{
			case 1:
				printf("��������ĺ��������\n");
				scanf("%s", p->name);
				break;
			case 2:
				printf("��������ĺ��ѧ�ţ�\n");
				scanf("%s", p->num);
				break;
			case 3:
				printf("��������ĺ����ѧ�ɼ���\n");
				scanf("%d", &p->scorem);
				break;
			case 4:	printf("��������ĺ��Ӣ��ɼ���\n");
				scanf("%d", &p->scoree);
				break;
			case 5:
				printf("��������ĺ��C�ɼ���\n");
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
			printf("���ĺ���ܷ֣�%d\n", p->sum);
		}
	} while (p->next != NULL);
	save(head);
	if (count == 0)
	{
		printf("�Բ���û������ˡ�\n");
	}
	return head;
}
Student *outputsortsum()//�ܷ��������
{
	int i = 1;
	Student *head = NULL, *p = NULL;
	head = read();
	sortsum(head);
	p = head->next;
	printf("\n       *************************STUDENT****************************\n");
	printf("       ------------------------------------------------------------\n");
	printf("       | ���� |   ѧ��   |   ���� |  ��ѧ |  Ӣ�� | C���� |  �ܷ� |\n");
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
Student *statistic()//ͳ�ƺ���
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
	printf("�ܹ���%d��ѧ����Ϣ.\n\n", m);
	q = sortsum(head)->next;
	printf("������ߵ�ѧ������Ϣ:\n");
	printf("\n       ***********************STUDENT*************************\n");
	printf("       -------------------------------------------------------\n");
	printf("       |   ѧ��   |  ����  |  ��ѧ  |  Ӣ��  | C���� |  �ܷ� |\n");
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
		printf("���������룺");
		get_psw(input);
		if (m == 1 && strcmp(input, psw_admin) == 0)
		{
			printf("\n��ӭ�������Ա����ϵͳ !\n");
			break;
		}
		else if (m == 2 && strcmp(input, psw_stu) == 0)
		{
			printf("\n��ӭ����ѧ������ϵͳ !\n");
			break;
		}
		printf("\n��������Ǵ���ģ�\n");
	}
}
void menu(int n)
{
	system("cls");
	if (n == 0)
	{
		printf("******************************************************\n");
		printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
		printf("����������������������������\n\n");
		printf("                     ����������ѧ\n");
		printf("                  �������ϵͳ��ӭ��!\n\n");
		printf("                     ��ѡ���������\n\n");
		printf("                     1.����Ա\n");
		printf("                     2.ѧ��\n\n");
		printf("                     3.�˳�ϵͳ\n\n");
		printf("����������������������������\n");
		printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
		printf("******************************************************\n");
		printf("����ѡ��: ");
	}
	else if (n == 1)
	{
		printf("                            ����Ա�û�\n\n");
		printf("*******************************���˵�****************************\n");
		printf("*                                                               *\n");
		printf("*                         1 ���ѧ���ɼ�                        *\n");
		printf("*          *              2 ����ѧ���ɼ�             *          *\n");
		printf("*        *   *            3 ɾ��ָ��ѧ��           *   *        *\n");
		printf("*      *       *          4 �޸�ѧ����Ϣ         *       *      *\n");
		printf("*        *   *            5 �ܷ�������Ϣ           *   *        *\n");
		printf("*          *              6 �鿴ȫ����Ϣ             *          *\n");
		printf("*                         7 ͳ��ѧ������                        *\n");
		printf("*                         8 ֹͣ��������                        *\n");
		printf("*                                                               *\n");
		printf("*****************************************************************\n");
		printf("����ѡ��");
	}
	else if (n == 2)
	{
		printf("                            ѧ���û�\n\n");
		printf("*******************************���˵�****************************\n");
		printf("*                                                               *\n");
		printf("*          *              1 ����ѧ���ɼ�             *          *\n");
		printf("*        *   *            2 �ܷ�������Ϣ           *   *        *\n");
		printf("*      *       *          3 �鿴ȫ����Ϣ         *       *      *\n");
		printf("*        *   *            4 ͳ��ѧ������           *   *        *\n");
		printf("*          *              5 ֹͣ��������             *          *\n");
		printf("*                                                               *\n");
		printf("*****************************************************************\n");
		printf("����ѡ��");
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
		printf("����������������룡");
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
			printf("�������\n");
		}
		printf("\n\n��ѡ��������Ĳ�����\n");
		printf(" 1 . �������˵�      2 . �˳�����\n");
		scanf("%d", &b);
	}
	return 0;
}