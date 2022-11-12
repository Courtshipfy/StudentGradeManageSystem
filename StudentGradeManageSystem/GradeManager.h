#pragma once
#include <iostream>
#include "Student.h"
#include "Analyser.h"
using namespace std;

class GradeManager 
{
public:

	Analyser *aser;

	string availableFileType[2] = {{"txt"},{"csv"}};
	/*enum availableFileType
	{
		txt,
		csv,
	};*/


	//记录总人数
	int g_TotalNum;

	//成绩表单地址
	string fileName;

	//学生数组指针
	Student** g_StudentArray;

	//文件是否为空
	bool g_FileIsEmpty;

	
	//默认构造
	GradeManager();

	//显示菜单
	void ShowMenuMain();

	//二级菜单
	void ShowMenuSecond_first();
	void ShowMenuSecond_second();

	//三级菜单
	void ShowMenuThird_first();
	void ShowMenuThird_second();
	void ShowMenuThird_third();

	//四级菜单
	void ShowMenuFourth_first();
	void ShowMenuFourth_second();


	//退出系统
	void ExitSystem();

	//指定要操作的文件
	void AssignFile();

	//确定输入文件名称是否有效
	bool fileNmaeisAvaliable(const string &fileName);

	//按字段录入学生成绩
	void AddGrade_filed();

	//查找学生成绩
	void FindGrade_Show(const string& name);

	//查找学生索引
	int FindGrade_Index(const string& name);

	//按文件录入学生成绩
	void AddGrade_fileName(const string& fileName);

	//保存成绩
	void Save();

	//统计人数
	int get_StudentNum();

	//显示成绩
	void ShowGrades();

	//修改成绩
	void ModGrade();

	//单科排序成绩
	void SortGrades(string subject);

	//三科排序成绩
	void AllSortGrades();

	//计算最高分
	int MaxGrade(string& subject);

	//计算最低分
	int MinGrade(string& subject);

	//计算平均分
	int AvergeGrade(string& subject);

	//三科计算最高分
	int MaxAllGrade();

	//三科最低分
	int MinAllGrade();

	//三科平均分
	int AvergeAllGrade();

	//单科统计输出
	void VarSubject(string subject);

	

	~GradeManager();
};


