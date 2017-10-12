#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
显示菜单并返回用户选择的选项（显示的序号从1开始，返回的选项对应数组下标从0开始）
options: 菜单内容
count: 菜单条目数
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
		//k == 0 表示读取失败，如读到了字母
		if (k == 0)
		{
			char s[100];
			printf("输入有误\n");
			fgets(s, 100, stdin);
			continue;
		}
		//越界
		if (t < 1 || t > count)
		{
			printf("输入有误\n");
			continue;
		}
		//正常返回
		return t - 1;
	}
}

/*
在字符串中查找指定字符
s: 要查找的字符串
ch: 要查找的字符
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
表示联系人的结构体
*/
typedef struct contact {
	//用于在读写文件时判断该位置是否存在数据
	int id;

	//姓名
	char name[20];
	
	//联系电话
	char number[11];

	//类型（0-办公类， 1-个人类， 2-商务类）
	int type;

	//电子邮件
	char email[50];
} contact;

//保存联系人数据的数组
contact contacts[15];

//联系人数组中有效数据的数量
int size = 0;

/*
将一个联系人对象中的内容拷贝到另一个对象中
dest: 目标地址
src: 源地址
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
读取数据文件中的内容
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
用二进制方式将数据写入到文件
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
联系人结构体比较函数，用于数组排序
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

//联系人类型数值对应的字符串
char types[][50] = { "办公类", "个人类", "商务类" };

/*
显示现有数据
*/
void show()
{
	printf("%-5s%-15s%-15s%-10s%-30s\n", "序号", "姓名", "电话号码", "类别", "电子邮件");
	for (int i = 0; i < size; i++)
	{
		printf("%-5d%-15s%-15s%-10s%-30s\n", (i + 1), contacts[i].name, contacts[i].number, types[contacts[i].type], contacts[i].email);
	}
	printf("\n\n");
}

/*
对现有数据排序、更新序号并写入文件
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
添加联系人
*/
void add()
{
	int t, i;
	contact c;

	//检查存储空间
	if (size == 15)
	{
		printf("存储空间已满，无法继续添加\n\n\n");
		return;
	}

	//类别
	printf("请选择类别\n");
	t = menu(types, 3);
	c.type = t;

	//姓名
	printf("请输入姓名\n");
	if (!scanf_s("%s", c.name, 20))
	{
		printf("姓名不能超过20个字符\n\n\n");
		return;
	}
	for (i = 0; i < size; i++)
	{
		if (strcmp(contacts[i].name, c.name) == 0)
		{
			printf("该姓名已经存在\n\n\n");
			return;
		}
	}

	//电话号码
	printf("请输入电话号码\n");
	if (!scanf_s("%s", c.number, 11))
	{
		printf("电话号码不能超过11位\n\n\n");
		return;
	}
	for (i = 0; i < (int)strlen(c.number); i++)
	{
		if (!isdigit(c.number[i]))
		{
			printf("电话号码包含非法字符\n\n\n");
			return;
		}
	}
	for (i = 0; i < size; i++)
	{
		if (strcmp(contacts[i].number, c.number) == 0)
		{
			printf("该号码已经存在\n\n\n");
			return;
		}
	}

	//电子邮件
	printf("请输入电子邮件\n");
	if (!scanf_s("%s", c.email, 50))
	{
		printf("电子邮件不能超过50个字符\n\n\n");
		return;
	}
	if (index_of(c.email, '@') == -1)
	{
		printf("电子邮件必须包含@符号\n\n\n");
		return;
	}

	//插入、保存
	copy(&contacts[size], &c);
	size++;
	save();
	printf("添加成功\n\n\n");
}

/*
删除联系人
*/
void delete()
{
	int t;
	show();
	printf("请输入要删除的条目编号\n");
	scanf_s("%d", &t);
	t--;
	if (t < 0 || t >= size)
	{
		printf("输入的编号有误\n\n\n");
		return;
	}

	copy(&contacts[t], &contacts[size - 1]);
	size--;
	save();
	printf("删除成功\n\n\n");
}

/*
修改联系人信息
*/
void update()
{
	int t, k, i;
	show();
	printf("请输入要修改的条目编号\n");
	scanf_s("%d", &k);
	k--;
	if (k < 0 || k >= size)
	{
		printf("输入的编号有误\n\n\n");
		return;
	}

	contact c;
	//类别
	printf("请选择修改后的类别\n");
	t = menu(types, 3);
	c.type = t;

	//姓名
	printf("请输入姓名\n");
	if (!scanf_s("%s", c.name, 20))
	{
		printf("姓名不能超过20个字符\n\n\n");
		return;
	}
	for (i = 0; i < size; i++)
	{
		if (strcmp(contacts[i].name, c.name) == 0 && k != i)
		{
			if (t != i)
			{
				printf("该姓名已经存在\n\n\n");
				return;
			}
		}
	}

	//电话号码
	printf("请输入电话号码\n");
	if (!scanf_s("%s", c.number, 11))
	{
		printf("电话号码不能超过11位\n\n\n");
		return;
	}
	for (i = 0; i < (int)strlen(c.number); i++)
	{
		if (!isdigit(c.number[i]))
		{
			printf("电话号码包含非法字符\n\n\n");
			return;
		}
	}
	for (i = 0; i < size; i++)
	{
		if (strcmp(contacts[i].number, c.number) == 0 && k != i)
		{
			printf("该号码已经存在\n\n\n");
			return;
		}
	}

	//电子邮件
	printf("请输入电子邮件\n");
	if (!scanf_s("%s", c.email, 50))
	{
		printf("电子邮件不能超过50个字符\n\n\n");
		return;
	}
	if (index_of(c.email, '@') == -1)
	{
		printf("电子邮件必须包含@符号\n\n\n");
		return;
	}

	//保存修改
	copy(&contacts[k], &c);
	save();
}

/*
导出到csv文件
*/
void export_csv()
{
	char dir[150];
	char name[50];
	printf("请输入文件保存路径\n");
	if (!scanf_s("%s", dir, 100))
	{
		printf("文件路径过长\n\n\n");
		return;
	}
	printf("请输入文件名\n");
	if (!scanf_s("%s", name, 50))
	{
		printf("文件名过长\n\n\n");
		return;
	}
	strcat_s(dir, 150 * sizeof(char), "\\");
	strcat_s(dir, 150 * sizeof(char), name);
	strcat_s(dir, 150 * sizeof(char), ".csv");
	
	FILE *fp;
	char msg[50];
	errno_t n = fopen_s(&fp, dir, "w");
	//文件打开失败的处理
	if (n != 0)
	{
		strerror_s(msg, 50, n);
		printf("%s\n", msg);
		return;
	}

	int i;
	fprintf(fp, "序号,姓名,电话号码,类别,电子邮件\n");
	for (i = 0; i < size; i++)
	{
		fprintf(fp, "%d,%s,%s,%s,%s\n", i + 1, contacts[i].name, contacts[i].number, types[contacts[i].type], contacts[i].email);
	}
	printf("文件[%s]导出成功\n\n\n", dir);
}

/*
清屏
*/
void clear()
{
	system("cls");
}

/*
退出程序
*/
void quit()
{
	exit(0);
}

//将主菜单中的选项对应的函数保存到函数指针数组，之后可以根据menu函数返回的值取此数组中的函数进行调用
void(*(f[7]))() = { show, add, delete, update, export_csv, clear, quit };

/*
主函数
*/
int main(void)
{
	int t;
	char options[7][50] = { "查看", "增加", "删除", "修改", "导出为csv文件", "清屏", "退出" };
	read();
	while (1)
	{
		printf("通讯录\n");
		t = menu(options, 7);
		f[t]();
	}
	return 0;
}
