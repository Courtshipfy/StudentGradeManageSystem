#include "Student.h"


void Student::ShowInfo()
{
	cout << "ѧ������" << this->g_name
		<< "\t����" << this->g_chinese
		<< "\tӢ��" << this->g_english
		<< "\t��ѧ" << this->g_math << endl;

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
