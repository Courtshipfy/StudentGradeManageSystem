#pragma once
#include <iostream>
#include <fstream>
#include "Student.h"

using namespace std;

class Analyser
{
public :

	//获取文件后缀名
	string getFileSuffix(const string& fileName);

	//用txt初始化学生成绩单
	void InitGrades_txt(const string& path,Student ** tempStudent);

	//输出txt格式的文件
	void OutGrades_txt(string txt, Student** tempStudent);

	//用cvs初始化学生成绩单
	void InitGrades_csv(const string& path, Student** tempStudent);

	//输出txt格式的文件
	void OutGrades_csv(string csv, Student** tempStudent);

};