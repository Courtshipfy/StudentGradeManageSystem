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


	//��¼������
	int g_TotalNum;

	//�ɼ�����ַ
	string fileName;

	//ѧ������ָ��
	Student** g_StudentArray;

	//�ļ��Ƿ�Ϊ��
	bool g_FileIsEmpty;

	
	//Ĭ�Ϲ���
	GradeManager();

	//��ʾ�˵�
	void ShowMenuMain();

	//�����˵�
	void ShowMenuSecond_first();
	void ShowMenuSecond_second();

	//�����˵�
	void ShowMenuThird_first();
	void ShowMenuThird_second();
	void ShowMenuThird_third();

	//�ļ��˵�
	void ShowMenuFourth_first();
	void ShowMenuFourth_second();


	//�˳�ϵͳ
	void ExitSystem();

	//ָ��Ҫ�������ļ�
	void AssignFile();

	//ȷ�������ļ������Ƿ���Ч
	bool fileNmaeisAvaliable(const string &fileName);

	//���ֶ�¼��ѧ���ɼ�
	void AddGrade_filed();

	//����ѧ���ɼ�
	void FindGrade_Show(const string& name);

	//����ѧ������
	int FindGrade_Index(const string& name);

	//���ļ�¼��ѧ���ɼ�
	void AddGrade_fileName(const string& fileName);

	//����ɼ�
	void Save();

	//ͳ������
	int get_StudentNum();

	//��ʾ�ɼ�
	void ShowGrades();

	//�޸ĳɼ�
	void ModGrade();

	//��������ɼ�
	void SortGrades(string subject);

	//��������ɼ�
	void AllSortGrades();

	//������߷�
	int MaxGrade(string& subject);

	//������ͷ�
	int MinGrade(string& subject);

	//����ƽ����
	int AvergeGrade(string& subject);

	//���Ƽ�����߷�
	int MaxAllGrade();

	//������ͷ�
	int MinAllGrade();

	//����ƽ����
	int AvergeAllGrade();

	//����ͳ�����
	void VarSubject(string subject);

	

	~GradeManager();
};


