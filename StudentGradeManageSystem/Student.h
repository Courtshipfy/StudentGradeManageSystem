#pragma once
#include <iostream>
using namespace std;

class Student
{
public:


	//显示个人信息
	virtual void ShowInfo();

	//初始构造
	Student(string name, int chinese, int english, int math);

	//成绩求和
	int scoreSum();

	//个人信息
	string g_name;
	int g_chinese;
	int g_english;
	int g_math;
};
