#include "Student.h"


void Student::ShowInfo()
{
	cout << "学生姓名" << this->g_name
		<< "\t语文" << this->g_chinese
		<< "\t英语" << this->g_english
		<< "\t数学" << this->g_math << endl;

}

Student::Student(string name, int chinese, int english, int math)
{
	this->g_name = name;
	this->g_chinese = chinese;
	this->g_english = english;
	this->g_math = math;
}

int Student::scoreSum()
{
	return g_chinese + g_english + g_math;
}
