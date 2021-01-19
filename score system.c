代码：
#include<stdio.h>
#include<stdlib.h>    //供exit()用
#include<string.h>
/*定义结构体students*/
struct student
{
	int num;    //学号
	char name[8];    //姓名
	int score;     //成绩
};


/*成绩输入*/
void student_new()
{
	struct student stu, g;
	FILE* fp;
	fp = fopen("stud.dat", "ab+");
	fseek(fp, -16L, 2);//从文件后面向前移动一个student数据结构长度的字节 
	fread(&g, sizeof(struct student), 1, fp);
	fseek(fp, 0L, 2);
	{
		printf("\n输入第%d学生的姓名和成绩:\n", g.num + 1);
		stu.num = g.num + 1;
		printf("姓名:");
		scanf("%s", stu.name);
		printf("成绩:");
		scanf("%d", &stu.score);
	}
	fwrite(&stu, sizeof(struct student), 1, fp);
	fclose(fp);
}


//*显示所有记录函数*
void load()
{
	struct student stu;
	FILE* fp;
	fp = fopen("stud.dat", "rb");
	if (fp == NULL)
	{
		printf("文件打开失败!\n");
		exit(1);
	}
	printf("====================================================\n");
	printf("学号         姓名       成绩\n");
	printf("====================================================\n");
	while (fread(&stu, sizeof(struct student), 1, fp))//检测是否读取成功，未读取成功说明已读取完毕 
	{
		printf("\n%-10d %-8s %-4d\n", stu.num, stu.name, stu.score);
		printf("\n");
	}
	fclose(fp);
}


//*根据学号查询学生信息函数*
void score_search()
{
	int i, a;
	FILE* fp;
	struct student stu, g;
	fp = fopen("stud.dat", "rb");
	if (fp == NULL)
	{
		printf("文件打开失败!\n");
		exit(1);
	}
	printf("请输入学号：");
	scanf("%d", &a);
	fseek(fp, -16L, 2); //从文件后面向前移动一个student数据结构长度的字节
	fread(&g, sizeof(struct student), 1, fp);//录入最后一名学生的数据 
	fseek(fp, 0L, 0);//将指针移到最前面 
	for (i = 0; i < g.num; i++)
	{
		fread(&stu, sizeof(struct student), 1, fp);
		if (stu.num == a)
		{
			printf("====================================================\n");
			printf("学号     姓名     成绩\n");
			printf("====================================================\n");
			printf("\n%-10d %-8s %4d\n", stu.num, stu.name, stu.score);
			printf("\n");
			break;
		}
	}
	if (i == g.num)printf("该学生信息不存在");
	fclose(fp);
}


//*修改成绩函数*
void modify()
{
	struct student stu, g;
	int i, a;
	FILE* fp;
	fp = fopen("stud.dat", "rb+");
	if (fp == NULL)
	{
		printf("文件打开失败!\n");
		exit(1);
	}
	fseek(fp, -16L, 2); //从文件后面向前移动一个student数据结构长度的字节
	fread(&g, sizeof(struct student), 1, fp);//录入最后一名学生的数据 
	printf("请输入要修改成绩的学生学号：");
	scanf("%d", &a);
	fseek(fp, 0L, 0);//将指针移到最前 
	for (i = 0; i < g.num; i++)
	{
		fread(&stu, sizeof(struct student), 1, fp);
		if (stu.num == a)
		{
			printf("====================================================\n");
			printf("学号         姓名       成绩\n");
			printf("====================================================\n");
			printf("\n%-10d %-8s %4d\n", stu.num, stu.name, stu.score);
			printf("\n");
			printf("请输入该生的正确成绩：");
			scanf("%d", &stu.score);
			fseek(fp, -16L, 1);//前移
			fwrite(&stu, sizeof(struct student), 1, fp);
			printf("\n%-10d %-8s %4d\n", stu.num, stu.name, stu.score);
			printf("\n");
			break;
		}
		if (i == g.num)
			printf("该学生信息不存在");
	}
	fclose(fp);
}



//*统计及格及优秀人数函数*
void loadsum()
{
	struct student stu, g;
	int i, s1 = 0, s2 = 0;
	FILE* fp;
	fp = fopen("stud.dat", "rb");
	if (fp == NULL)
	{
		printf("文件打开失败!\n");
		exit(1);
	}
	fseek(fp, -16L, 2); //从文件后面向前移动一个student数据结构长度的字节
	fread(&g, sizeof(struct student), 1, fp);//录入最后一名学生的数据 
	fseek(fp, 0L, 0);//将指针移到最前
	for (i = 0; i < g.num; i++)
	{
		fread(&stu, sizeof(struct student), 1, fp);
		if (stu.score >= 60) s1 = s1 + 1;
		if (stu.score >= 85) s2 = s2 + 1;
	}
	fclose(fp);
	printf("及格人数:%4d\n优秀人数:%4d\n", s1, s2);
	printf("\n");
}


//*输出不及格学生成绩函数*
void loadpen1()
{
	struct student stu, g;
	int i, s1 = 0, s2 = 0;
	FILE* fp;
	fp = fopen("stud.dat", "rb");
	if (fp == NULL)
	{
		printf("文件打开失败!\n");
		exit(1);
	}
	fseek(fp, -16L, 2); //从文件后面向前移动一个student数据结构长度的字节
	fread(&g, sizeof(struct student), 1, fp);//录入最后一名学生的数据 
	fseek(fp, 0L, 0);//将指针移到最前
	for (i = 0; i < g.num; i++)
	{
		fread(&stu, sizeof(struct student), 1, fp);
		if (stu.score < 60)
			printf("\n%-10d %-8s %4d\n", stu.num, stu.name, stu.score);
	}
	fclose(fp);
}


//*输出优秀学生成绩函数*
void loadpen2()
{
	struct student stu, g;
	int i, s1 = 0, s2 = 0;
	FILE* fp;
	fp = fopen("stud.dat", "rb");
	if (fp == NULL)
	{
		printf("文件打开失败!\n");
		exit(1);
	}
	fseek(fp, -16L, 2); //从文件后面向前移动一个student数据结构长度的字节
	fread(&g, sizeof(struct student), 1, fp);//录入最后一名学生的数据 
	fseek(fp, 0L, 0);//将指针移到最前
	for (i = 0; i < g.num; i++)
	{
		fread(&stu, sizeof(struct student), 1, fp);
		if (stu.score >= 85)
			printf("\n%-10d %-8s %4d\n", stu.num, stu.name, stu.score);
	}
	fclose(fp);
}


//*菜单*		 
main()
{
	int i, select, flag = 1, p;
	FILE* fp;
	struct student a, stu[5] = { {1,"zhangsan",98},{2,"lisi",85},{3,"wangwu",76},{4,"chenliu",65},{5,"liuqi",54} };
	fp = fopen("stud.dat", "ab");//创建二进制文件 
	if (fp == NULL)
	{
		printf("文件创建失败!\n");
		exit(1);
	}
	fseek(fp, 0L, 2);
	p = ftell(fp);
	if (p == -0L)
		for (i = 0; i < 5; i++)
		{
			fwrite(&stu[i], sizeof(struct student), 1, fp);
		}
	fclose(fp);
	{
		printf("\t\t 欢迎进入学生信息管理系统\n");
		printf("\t\t**************************\n");
		printf("\t\t*1 输入数据              *\n");
		printf("\t\t*2 查询成绩              *\n");
		printf("\t\t*3 修改成绩              *\n");
		printf("\t\t*4 输出所有学生信息      *\n");
		printf("\t\t*5 统计及格和优秀人数    *\n");
		printf("\t\t*6 输出不及格的学生姓名和成绩*\n");
		printf("\t\t*7 输出优秀学生姓名和成绩*\n");
		printf("\t\t*0 退出                  *\n");
		printf("\t\t**************************\n");
	}
	while (flag)
	{
		printf("请输入选项：");
		scanf("%d", &select);
		switch (select)
		{
		case 1:student_new(); break;
		case 2:score_search(); break;
		case 3:modify(); break;
		case 4:load(); break;
		case 5:loadsum(); break;
		case 6:loadpen1(); break;
		case 7:loadpen2(); break;
		case 0:flag = 0; break;
		default:break;
		}
	}
}