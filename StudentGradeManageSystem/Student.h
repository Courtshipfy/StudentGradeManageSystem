#pragma once
#include <iostream>
using namespace std;

class Student
{
public:


	//��ʾ������Ϣ
	virtual void ShowInfo();

	//��ʼ����
	Student(string name, int chinese, int english, int math);

	//�ɼ����
	int scoreSum();

	//������Ϣ
	string g_name;
	int g_chinese;
	int g_english;
	int g_math;
};
