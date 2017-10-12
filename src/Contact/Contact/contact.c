#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
��ʾ�˵��������û�ѡ���ѡ���ʾ����Ŵ�1��ʼ�����ص�ѡ���Ӧ�����±��0��ʼ��
options: �˵�����
count: �˵���Ŀ��
*/
int menu(char options[][50], int count)
{
	int i, t;
	for (i = 0; i < count; i++)
	{
		printf("%d - %s\n", i + 1, options[i]);
	}
	printf("\n");
	while (1)
	{
		int k = scanf_s("%d", &t);
		//k == 0 ��ʾ��ȡʧ�ܣ����������ĸ
		if (k == 0)
		{
			char s[100];
			printf("��������\n");
			fgets(s, 100, stdin);
			continue;
		}
		//Խ��
		if (t < 1 || t > count)
		{
			printf("��������\n");
			continue;
		}
		//��������
		return t - 1;
	}
}

/*
���ַ����в���ָ���ַ�
s: Ҫ���ҵ��ַ���
ch: Ҫ���ҵ��ַ�
*/
int index_of(char *s, char ch)
{
	int i;
	for (i = 0; i < (int)strlen(s); i++)
	{
		if (ch == s[i])
		{
			return i;
		}
	}
	return -1;
}

/*
��ʾ��ϵ�˵Ľṹ��
*/
typedef struct contact {
	//�����ڶ�д�ļ�ʱ�жϸ�λ���Ƿ��������
	int id;

	//����
	char name[20];
	
	//��ϵ�绰
	char number[11];

	//���ͣ�0-�칫�࣬ 1-�����࣬ 2-�����ࣩ
	int type;

	//�����ʼ�
	char email[50];
} contact;

//������ϵ�����ݵ�����
contact contacts[15];

//��ϵ����������Ч���ݵ�����
int size = 0;

/*
��һ����ϵ�˶����е����ݿ�������һ��������
dest: Ŀ���ַ
src: Դ��ַ
*/
void copy(contact *dest, contact *src)
{
	dest->id = src->id;
	strcpy_s(dest->name, sizeof(dest->name), src->name);
	strcpy_s(dest->number, sizeof(dest->number), src->number);
	dest->type = src->type;
	strcpy_s(dest->email, sizeof(dest->email), src->email);
}

/*
��ȡ�����ļ��е�����
*/
void read()
{
	FILE *fp;
	fopen_s(&fp, "d://a.dat", "rb");
	if (fp == NULL)
	{
		return;
	}
	fread(contacts, sizeof(contact), 15, fp);
	fclose(fp);

	while (contacts[size].id != 0)
	{
		size++;
	}
}

/*
�ö����Ʒ�ʽ������д�뵽�ļ�
*/
void write()
{
	FILE *fp;
	char msg[50];
	errno_t n = fopen_s(&fp, "d://a.dat", "wb");
	if (n != 0)
	{
		strerror_s(msg, 50, n);
		printf("%s\n", msg);
		return;
	}
	fwrite(contacts, sizeof(contact), 15, fp);
	fflush(fp);
	fclose(fp);
}

/*
��ϵ�˽ṹ��ȽϺ�����������������
*/
int cmp(const void *a, const void *b)
{
	contact *c = (contact *)a;
	contact *d = (contact *)b;
	if (c->type != d->type)
	{
		return c->type - d->type;
	}
	else
	{
		return strcmp(c->name, d->name);
	}

}

//��ϵ��������ֵ��Ӧ���ַ���
char types[][50] = { "�칫��", "������", "������" };

/*
��ʾ��������
*/
void show()
{
	printf("%-5s%-15s%-15s%-10s%-30s\n", "���", "����", "�绰����", "���", "�����ʼ�");
	for (int i = 0; i < size; i++)
	{
		printf("%-5d%-15s%-15s%-10s%-30s\n", (i + 1), contacts[i].name, contacts[i].number, types[contacts[i].type], contacts[i].email);
	}
	printf("\n\n");
}

/*
�������������򡢸�����Ų�д���ļ�
*/
void save()
{
	qsort(contacts, size, sizeof(contact), cmp);
	for (int i = 0; i < 15; i++)
	{
		if (i < size)
		{
			contacts[i].id = i + 1;
		}
		else
		{
			contacts[i].id = 0;
		}
	}
	write();
}

/*
�����ϵ��
*/
void add()
{
	int t, i;
	contact c;

	//���洢�ռ�
	if (size == 15)
	{
		printf("�洢�ռ��������޷��������\n\n\n");
		return;
	}

	//���
	printf("��ѡ�����\n");
	t = menu(types, 3);
	c.type = t;

	//����
	printf("����������\n");
	if (!scanf_s("%s", c.name, 20))
	{
		printf("�������ܳ���20���ַ�\n\n\n");
		return;
	}
	for (i = 0; i < size; i++)
	{
		if (strcmp(contacts[i].name, c.name) == 0)
		{
			printf("�������Ѿ�����\n\n\n");
			return;
		}
	}

	//�绰����
	printf("������绰����\n");
	if (!scanf_s("%s", c.number, 11))
	{
		printf("�绰���벻�ܳ���11λ\n\n\n");
		return;
	}
	for (i = 0; i < (int)strlen(c.number); i++)
	{
		if (!isdigit(c.number[i]))
		{
			printf("�绰��������Ƿ��ַ�\n\n\n");
			return;
		}
	}
	for (i = 0; i < size; i++)
	{
		if (strcmp(contacts[i].number, c.number) == 0)
		{
			printf("�ú����Ѿ�����\n\n\n");
			return;
		}
	}

	//�����ʼ�
	printf("����������ʼ�\n");
	if (!scanf_s("%s", c.email, 50))
	{
		printf("�����ʼ����ܳ���50���ַ�\n\n\n");
		return;
	}
	if (index_of(c.email, '@') == -1)
	{
		printf("�����ʼ��������@����\n\n\n");
		return;
	}

	//���롢����
	copy(&contacts[size], &c);
	size++;
	save();
	printf("��ӳɹ�\n\n\n");
}

/*
ɾ����ϵ��
*/
void delete()
{
	int t;
	show();
	printf("������Ҫɾ������Ŀ���\n");
	scanf_s("%d", &t);
	t--;
	if (t < 0 || t >= size)
	{
		printf("����ı������\n\n\n");
		return;
	}

	copy(&contacts[t], &contacts[size - 1]);
	size--;
	save();
	printf("ɾ���ɹ�\n\n\n");
}

/*
�޸���ϵ����Ϣ
*/
void update()
{
	int t, k, i;
	show();
	printf("������Ҫ�޸ĵ���Ŀ���\n");
	scanf_s("%d", &k);
	k--;
	if (k < 0 || k >= size)
	{
		printf("����ı������\n\n\n");
		return;
	}

	contact c;
	//���
	printf("��ѡ���޸ĺ�����\n");
	t = menu(types, 3);
	c.type = t;

	//����
	printf("����������\n");
	if (!scanf_s("%s", c.name, 20))
	{
		printf("�������ܳ���20���ַ�\n\n\n");
		return;
	}
	for (i = 0; i < size; i++)
	{
		if (strcmp(contacts[i].name, c.name) == 0 && k != i)
		{
			if (t != i)
			{
				printf("�������Ѿ�����\n\n\n");
				return;
			}
		}
	}

	//�绰����
	printf("������绰����\n");
	if (!scanf_s("%s", c.number, 11))
	{
		printf("�绰���벻�ܳ���11λ\n\n\n");
		return;
	}
	for (i = 0; i < (int)strlen(c.number); i++)
	{
		if (!isdigit(c.number[i]))
		{
			printf("�绰��������Ƿ��ַ�\n\n\n");
			return;
		}
	}
	for (i = 0; i < size; i++)
	{
		if (strcmp(contacts[i].number, c.number) == 0 && k != i)
		{
			printf("�ú����Ѿ�����\n\n\n");
			return;
		}
	}

	//�����ʼ�
	printf("����������ʼ�\n");
	if (!scanf_s("%s", c.email, 50))
	{
		printf("�����ʼ����ܳ���50���ַ�\n\n\n");
		return;
	}
	if (index_of(c.email, '@') == -1)
	{
		printf("�����ʼ��������@����\n\n\n");
		return;
	}

	//�����޸�
	copy(&contacts[k], &c);
	save();
}

/*
������csv�ļ�
*/
void export_csv()
{
	char dir[150];
	char name[50];
	printf("�������ļ�����·��\n");
	if (!scanf_s("%s", dir, 100))
	{
		printf("�ļ�·������\n\n\n");
		return;
	}
	printf("�������ļ���\n");
	if (!scanf_s("%s", name, 50))
	{
		printf("�ļ�������\n\n\n");
		return;
	}
	strcat_s(dir, 150 * sizeof(char), "\\");
	strcat_s(dir, 150 * sizeof(char), name);
	strcat_s(dir, 150 * sizeof(char), ".csv");
	
	FILE *fp;
	char msg[50];
	errno_t n = fopen_s(&fp, dir, "w");
	//�ļ���ʧ�ܵĴ���
	if (n != 0)
	{
		strerror_s(msg, 50, n);
		printf("%s\n", msg);
		return;
	}

	int i;
	fprintf(fp, "���,����,�绰����,���,�����ʼ�\n");
	for (i = 0; i < size; i++)
	{
		fprintf(fp, "%d,%s,%s,%s,%s\n", i + 1, contacts[i].name, contacts[i].number, types[contacts[i].type], contacts[i].email);
	}
	printf("�ļ�[%s]�����ɹ�\n\n\n", dir);
}

/*
����
*/
void clear()
{
	system("cls");
}

/*
�˳�����
*/
void quit()
{
	exit(0);
}

//�����˵��е�ѡ���Ӧ�ĺ������浽����ָ�����飬֮����Ը���menu�������ص�ֵȡ�������еĺ������е���
void(*(f[7]))() = { show, add, delete, update, export_csv, clear, quit };

/*
������
*/
int main(void)
{
	int t;
	char options[7][50] = { "�鿴", "����", "ɾ��", "�޸�", "����Ϊcsv�ļ�", "����", "�˳�" };
	read();
	while (1)
	{
		printf("ͨѶ¼\n");
		t = menu(options, 7);
		f[t]();
	}
	return 0;
}
