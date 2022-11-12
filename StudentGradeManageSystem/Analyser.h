#pragma once
#include <iostream>
#include <fstream>
#include "Student.h"

using namespace std;

class Analyser
{
public :

	//��ȡ�ļ���׺��
	string getFileSuffix(const string& fileName);

	//��txt��ʼ��ѧ���ɼ���
	void InitGrades_txt(const string& path,Student ** tempStudent);

	//���txt��ʽ���ļ�
	void OutGrades_txt(string txt, Student** tempStudent);

	//��cvs��ʼ��ѧ���ɼ���
	void InitGrades_csv(const string& path, Student** tempStudent);

	//���txt��ʽ���ļ�
	void OutGrades_csv(string csv, Student** tempStudent);

};