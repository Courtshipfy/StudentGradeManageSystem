#include <iostream>
#include "GradeManager.h"
#include "Student.h"
using namespace std;

int main()
{
	//ʵ�����������
	GradeManager gm;

	int choice = 0;

	while (true)
	{
		gm.ShowMenuMain();

		cout << "������ѡ��" << endl;
		cin >> choice;

		switch (choice) 
		{
		case 0:	//�˳�ϵͳ
			gm.ExitSystem();
			break;
		case 1:
			gm.ShowMenuSecond_first();
			break;
		case 2:
			gm.ModGrade();
			break;
		case 3:
			gm.ShowMenuSecond_second();
			break;
		default:
			system("cls");
			break;
		}
	}

	//system("chcp 65001");
	system("pause");
	return 0;
}