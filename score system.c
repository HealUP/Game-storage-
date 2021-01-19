���룺
#include<stdio.h>
#include<stdlib.h>    //��exit()��
#include<string.h>
/*����ṹ��students*/
struct student
{
	int num;    //ѧ��
	char name[8];    //����
	int score;     //�ɼ�
};


/*�ɼ�����*/
void student_new()
{
	struct student stu, g;
	FILE* fp;
	fp = fopen("stud.dat", "ab+");
	fseek(fp, -16L, 2);//���ļ�������ǰ�ƶ�һ��student���ݽṹ���ȵ��ֽ� 
	fread(&g, sizeof(struct student), 1, fp);
	fseek(fp, 0L, 2);
	{
		printf("\n�����%dѧ���������ͳɼ�:\n", g.num + 1);
		stu.num = g.num + 1;
		printf("����:");
		scanf("%s", stu.name);
		printf("�ɼ�:");
		scanf("%d", &stu.score);
	}
	fwrite(&stu, sizeof(struct student), 1, fp);
	fclose(fp);
}


//*��ʾ���м�¼����*
void load()
{
	struct student stu;
	FILE* fp;
	fp = fopen("stud.dat", "rb");
	if (fp == NULL)
	{
		printf("�ļ���ʧ��!\n");
		exit(1);
	}
	printf("====================================================\n");
	printf("ѧ��         ����       �ɼ�\n");
	printf("====================================================\n");
	while (fread(&stu, sizeof(struct student), 1, fp))//����Ƿ��ȡ�ɹ���δ��ȡ�ɹ�˵���Ѷ�ȡ��� 
	{
		printf("\n%-10d %-8s %-4d\n", stu.num, stu.name, stu.score);
		printf("\n");
	}
	fclose(fp);
}


//*����ѧ�Ų�ѯѧ����Ϣ����*
void score_search()
{
	int i, a;
	FILE* fp;
	struct student stu, g;
	fp = fopen("stud.dat", "rb");
	if (fp == NULL)
	{
		printf("�ļ���ʧ��!\n");
		exit(1);
	}
	printf("������ѧ�ţ�");
	scanf("%d", &a);
	fseek(fp, -16L, 2); //���ļ�������ǰ�ƶ�һ��student���ݽṹ���ȵ��ֽ�
	fread(&g, sizeof(struct student), 1, fp);//¼�����һ��ѧ�������� 
	fseek(fp, 0L, 0);//��ָ���Ƶ���ǰ�� 
	for (i = 0; i < g.num; i++)
	{
		fread(&stu, sizeof(struct student), 1, fp);
		if (stu.num == a)
		{
			printf("====================================================\n");
			printf("ѧ��     ����     �ɼ�\n");
			printf("====================================================\n");
			printf("\n%-10d %-8s %4d\n", stu.num, stu.name, stu.score);
			printf("\n");
			break;
		}
	}
	if (i == g.num)printf("��ѧ����Ϣ������");
	fclose(fp);
}


//*�޸ĳɼ�����*
void modify()
{
	struct student stu, g;
	int i, a;
	FILE* fp;
	fp = fopen("stud.dat", "rb+");
	if (fp == NULL)
	{
		printf("�ļ���ʧ��!\n");
		exit(1);
	}
	fseek(fp, -16L, 2); //���ļ�������ǰ�ƶ�һ��student���ݽṹ���ȵ��ֽ�
	fread(&g, sizeof(struct student), 1, fp);//¼�����һ��ѧ�������� 
	printf("������Ҫ�޸ĳɼ���ѧ��ѧ�ţ�");
	scanf("%d", &a);
	fseek(fp, 0L, 0);//��ָ���Ƶ���ǰ 
	for (i = 0; i < g.num; i++)
	{
		fread(&stu, sizeof(struct student), 1, fp);
		if (stu.num == a)
		{
			printf("====================================================\n");
			printf("ѧ��         ����       �ɼ�\n");
			printf("====================================================\n");
			printf("\n%-10d %-8s %4d\n", stu.num, stu.name, stu.score);
			printf("\n");
			printf("�������������ȷ�ɼ���");
			scanf("%d", &stu.score);
			fseek(fp, -16L, 1);//ǰ��
			fwrite(&stu, sizeof(struct student), 1, fp);
			printf("\n%-10d %-8s %4d\n", stu.num, stu.name, stu.score);
			printf("\n");
			break;
		}
		if (i == g.num)
			printf("��ѧ����Ϣ������");
	}
	fclose(fp);
}



//*ͳ�Ƽ���������������*
void loadsum()
{
	struct student stu, g;
	int i, s1 = 0, s2 = 0;
	FILE* fp;
	fp = fopen("stud.dat", "rb");
	if (fp == NULL)
	{
		printf("�ļ���ʧ��!\n");
		exit(1);
	}
	fseek(fp, -16L, 2); //���ļ�������ǰ�ƶ�һ��student���ݽṹ���ȵ��ֽ�
	fread(&g, sizeof(struct student), 1, fp);//¼�����һ��ѧ�������� 
	fseek(fp, 0L, 0);//��ָ���Ƶ���ǰ
	for (i = 0; i < g.num; i++)
	{
		fread(&stu, sizeof(struct student), 1, fp);
		if (stu.score >= 60) s1 = s1 + 1;
		if (stu.score >= 85) s2 = s2 + 1;
	}
	fclose(fp);
	printf("��������:%4d\n��������:%4d\n", s1, s2);
	printf("\n");
}


//*���������ѧ���ɼ�����*
void loadpen1()
{
	struct student stu, g;
	int i, s1 = 0, s2 = 0;
	FILE* fp;
	fp = fopen("stud.dat", "rb");
	if (fp == NULL)
	{
		printf("�ļ���ʧ��!\n");
		exit(1);
	}
	fseek(fp, -16L, 2); //���ļ�������ǰ�ƶ�һ��student���ݽṹ���ȵ��ֽ�
	fread(&g, sizeof(struct student), 1, fp);//¼�����һ��ѧ�������� 
	fseek(fp, 0L, 0);//��ָ���Ƶ���ǰ
	for (i = 0; i < g.num; i++)
	{
		fread(&stu, sizeof(struct student), 1, fp);
		if (stu.score < 60)
			printf("\n%-10d %-8s %4d\n", stu.num, stu.name, stu.score);
	}
	fclose(fp);
}


//*�������ѧ���ɼ�����*
void loadpen2()
{
	struct student stu, g;
	int i, s1 = 0, s2 = 0;
	FILE* fp;
	fp = fopen("stud.dat", "rb");
	if (fp == NULL)
	{
		printf("�ļ���ʧ��!\n");
		exit(1);
	}
	fseek(fp, -16L, 2); //���ļ�������ǰ�ƶ�һ��student���ݽṹ���ȵ��ֽ�
	fread(&g, sizeof(struct student), 1, fp);//¼�����һ��ѧ�������� 
	fseek(fp, 0L, 0);//��ָ���Ƶ���ǰ
	for (i = 0; i < g.num; i++)
	{
		fread(&stu, sizeof(struct student), 1, fp);
		if (stu.score >= 85)
			printf("\n%-10d %-8s %4d\n", stu.num, stu.name, stu.score);
	}
	fclose(fp);
}


//*�˵�*		 
main()
{
	int i, select, flag = 1, p;
	FILE* fp;
	struct student a, stu[5] = { {1,"zhangsan",98},{2,"lisi",85},{3,"wangwu",76},{4,"chenliu",65},{5,"liuqi",54} };
	fp = fopen("stud.dat", "ab");//�����������ļ� 
	if (fp == NULL)
	{
		printf("�ļ�����ʧ��!\n");
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
		printf("\t\t ��ӭ����ѧ����Ϣ����ϵͳ\n");
		printf("\t\t**************************\n");
		printf("\t\t*1 ��������              *\n");
		printf("\t\t*2 ��ѯ�ɼ�              *\n");
		printf("\t\t*3 �޸ĳɼ�              *\n");
		printf("\t\t*4 �������ѧ����Ϣ      *\n");
		printf("\t\t*5 ͳ�Ƽ������������    *\n");
		printf("\t\t*6 ����������ѧ�������ͳɼ�*\n");
		printf("\t\t*7 �������ѧ�������ͳɼ�*\n");
		printf("\t\t*0 �˳�                  *\n");
		printf("\t\t**************************\n");
	}
	while (flag)
	{
		printf("������ѡ�");
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