#include "GradeManager.h"
#include "Analyser.h"
#include <fstream>
#include "Student.h"
#include <regex>
#include <map>
#define FILENAME "empFile.txt"

typedef multimap<int, int> scoreMap;

GradeManager::GradeManager()
{
	//��ʼ��������
	aser = new Analyser();

	//1.�ļ�������
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	//�ļ����������
	if (!ifs.is_open()) {
		cout << "�ļ�������" << endl;
		g_FileIsEmpty = true;
		g_TotalNum = 0;
		g_StudentArray = NULL;
		ifs.close();
		return;
	}

	//�ļ����ڵ�û�м�¼
	char ch;
	ifs >> ch;

	if (ifs.eof())
	{
		cout << "�ļ�Ϊ�գ�" << endl;
		g_FileIsEmpty = true;
		g_TotalNum = 0;
		g_StudentArray = NULL;
		ifs.close();
		return;
	}

	//�ļ����ڲ��м�¼
	int num = get_StudentNum();
	g_TotalNum = num;
	//cout << "ѧ��������" << num << endl;

	//���ٿռ�
	g_StudentArray = new Student * [g_TotalNum];

	//�ļ����ڲ�¼������
	aser->InitGrades_txt(FILENAME,g_StudentArray);
}

void GradeManager::ShowMenuMain()
{
	cout << "*****************************************************" << endl;
	cout << "***************** ��ӭʹ�óɼ�����ϵͳ *****************" << endl;
	cout << "****************** 0.�˳�����ϵͳ *********************" << endl;
	cout << "****************** 1.¼��ɼ���Ϣ *********************" << endl;
	cout << "****************** 2.�޸ĳɼ���Ϣ *********************" << endl;
	cout << "****************** 3.��ѯѧ���ɼ� *********************" << endl;
	cout << "*****************************************************" << endl;
	cout << endl;
}

void GradeManager::ShowMenuSecond_first()
{
	cout << "*****************************************************" << endl;
	cout << "****************** 1.���ֶ�¼��  *********************" << endl;
	cout << "****************** 2.���ļ�¼��  *********************" << endl;
	cout << "*****************************************************" << endl;

	int choice = 0;
	cin >> choice;

	switch (choice)
	{
	case 1:
		AddGrade_filed();    //���ֶ���ӳɼ�
		break;
	case 2:
		AssignFile();		//����ָ��Ŀ¼���ļ�
		break;
	default :
		system("cls");
		break;
	}
}

void GradeManager::ShowMenuSecond_second()
{
	cout << "*****************************************************" << endl;
	cout << "*********** 1.���Ƴɼ���߷�/��ͷ�/ƽ����  *************" << endl;
	cout << "*********** 2.���Ƴɼ���߷�/��ͷ�/ƽ����  *************" << endl;
	cout << "*********** 3.����/���Ƴɼ�����            *************" << endl;
	cout << "******************************************************" << endl;

	int choice = 0;
	cin >> choice;

	switch (choice)
	{
	case 1:
		ShowMenuThird_second();
		break;
	case 2:
		cout << "���Ƴɼ������"
			<< "\t��߷֣�" << MaxAllGrade()
			<< "\t��ͷ֣�" << MinAllGrade()
			<< "\tƽ���֣�" << AvergeAllGrade()
			<< endl;
		system("pause");
		break;
	case 3:
		ShowMenuThird_third();
		break;
	default:
		system("cls");
		break;
	}
}

//����ѧ���ɼ�
void GradeManager::ShowMenuThird_first()
{
	cout << "������ѧ��������" << endl;
	string name;
	cin >> name;
	ShowGrades();
}

//ѧ���ɼ��������
void GradeManager::ShowMenuThird_second()
{
	cout << "��֪�����ſ�Ŀ�ĳɼ����?" << endl;
	cout << "1.����" << endl;
	cout << "2.Ӣ��" << endl;
	cout << "3.��ѧ" << endl;

	int choice = 0;
	cin >> choice;

	switch (choice)
	{
	case 1:
		VarSubject("����");
		break;
	case 2:
		VarSubject("Ӣ��");
		break;
	case 3:
		VarSubject("��ѧ");
		break;
	default:
		system("cls");
		break;
	}
}

void GradeManager::ShowMenuThird_third()
{
	cout << "��֪�����ſ�Ŀ�����������" << endl;
	cout << "1.��������" << endl;
	cout << "2.��������" << endl;

	int choice = 0;
	cin >> choice;
	switch (choice)
	{
	case 1:
		ShowMenuFourth_first();
		break;
	case 2:
		AllSortGrades();
		break;
	default:
		system("cls");
		break;
	}
}

//��������ϸ�ֲ˵�
void GradeManager::ShowMenuFourth_first()
{
	cout << "��֪���ĸ���Ŀ������ɼ���"<<endl;
	cout << "1.����" << endl;
	cout << "2.Ӣ��" << endl;
	cout << "3.��ѧ" << endl;

	int choice = 0;
	cin >> choice;

	switch (choice) {
	case 1:
		SortGrades("����");
		break;
	case 2:
		SortGrades("Ӣ��");
		break;
	case 3:
		SortGrades("��ѧ");
		break;
	default:
		system("cls");
		break;
	}
}

void GradeManager::ShowMenuFourth_second()
{
}

void GradeManager::ExitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}

void GradeManager::AssignFile()
{
	cout << "������Ҫ�����ĳɼ�������:" << endl;
	string t_filename;
	cin >> t_filename;

	if (fileNmaeisAvaliable(t_filename)) { //�ж��ļ��Ƿ���Ч

		AddGrade_fileName(t_filename);
	}
	else {
		cout << "��������" << endl;
	}

}

bool GradeManager::fileNmaeisAvaliable(const string &fileName)
{
	// Windows���ļ����в��ܰ���\/:*?"<>|��Щ�ַ�
	regex regExpress("[\\/:*?\"<>|]");
	bool pointValid = !std::regex_search(fileName, regExpress);

	string suffixx = aser->getFileSuffix(fileName);
	bool suffixValid = availableFileType->find(suffixx);

	return pointValid && suffixValid;
}

void GradeManager::AddGrade_filed()
{
	cout << "������¼��ѧ���ɼ�����" << endl;

	int addNum = 0;
	cin >> addNum;

	if (addNum > 0) 
	{
		//����ռ��С
		int newSize = this->g_TotalNum + addNum;

		//�����¿ռ�
		Student** newSpace = new Student * [newSize];

		//���ռ��µ����ݴ�ŵ��¿ռ���
		if (this->g_StudentArray != NULL)
		{
			for (int i = 0; i < this->g_TotalNum; i++)
			{
				newSpace[i] = this->g_StudentArray[i];
			}
		}

		//����������
		for (int i = 0; i < addNum; i++)
		{
			string t_name;
			int t_chinese;
			int t_english;
			int t_math;

			cout << "�������" << i + 1 << "��ѧ����������" << endl;
			cin >> t_name;

			cout << "�������" << i + 1 << "��ѧ�������ĳɼ���" << endl;
			cin >> t_chinese;

			cout << "�������" << i + 1 << "��ѧ����Ӣ��ɼ���" << endl;
			cin >> t_english;

			cout << "�������" << i + 1 << "��ѧ������ѧ�ɼ���" << endl;
			cin >> t_math;

			Student* st = new Student(t_name,t_chinese,t_english,t_math);

			//��ѧ���ɼ����浽��������
			newSpace[this->g_TotalNum + i] = st;
		}

		//�ͷ�ԭ�пռ�
		delete[] g_StudentArray;

		//���Ŀռ��ָ��
		g_StudentArray = newSpace;

		//����ѧ������
		g_TotalNum = newSize;

		//���ĳɼ�����Ϊ�յı�־
		g_FileIsEmpty = false;

		//�����ļ�
		Save();

		//��ʾ��Ϣ
		cout << "�ɹ����" << addNum << "��ѧ���ɼ���" << endl;
	}
	else
	{
		cout << "��������" << endl;
	}

	//��������������ص��ϼ�Ŀ¼
	system("pause");
	system("cls");
}



void GradeManager::AddGrade_fileName(const string& fileName)
{
	string fileType = aser->getFileSuffix(fileName);
	//�ļ����ͷ�֧

	if (fileType == ".txt") {
		aser->InitGrades_txt(fileName,g_StudentArray);
	}

	if (fileType == ".csv") {
		
	}
}

void GradeManager::Save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out); //д�ļ�

	for (int i = 0; i < g_TotalNum; i++) {
		ofs << g_StudentArray[i]->g_name << " "
			<< g_StudentArray[i]->g_chinese << " "
			<< g_StudentArray[i]->g_english << " "
			<< g_StudentArray[i]->g_math << endl;
	}

	ofs.close();
	
}

int GradeManager::get_StudentNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in); //���ļ�

	string name;
	int ch;
	int en;
	int ma;

	int num = 0;

	while (ifs >> name && ifs >> ch && ifs >> en && ifs >> ma) {
		num++;
	}
	ifs.close();
	return num;
}

//void GradeManager::InitGrades()
//{
//	ifstream ifs;
//	ifs.open(FILENAME, ios::in);
//
//	string name;
//	int ch;
//	int en;
//	int ma;
//
//
//	int index = 0;
//	while (ifs >> name && ifs >> ch && ifs >> en && ifs >> ma) {
//		Student* student = new Student(name,ch,en,ma);
//		g_StudentArray[index] = student;
//		index++;
//	}
//
//	//�ر��ļ�
//	ifs.close();
//}

//void GradeManager::InitGrades_txt(const string& path)
//{
//	ifstream ifs;
//	ifs.open(path, ios::in);
//
//	string name;
//	int ch;
//	int en;
//	int ma;
//
//
//	int index = 0;
//	while (ifs >> name && ifs >> ch && ifs >> en && ifs >> ma) {
//		Student* student = new Student(name, ch, en, ma);
//		g_StudentArray[index] = student;
//		index++;
//	}
//
//	//�ر��ļ�
//	ifs.close();
//}

void GradeManager::ShowGrades()
{
	//�ж��ļ��Ƿ�Ϊ��
	if (g_FileIsEmpty) {
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else {
		for (int i = 0; i < g_TotalNum; i++) {
			g_StudentArray[i]->ShowInfo();
		}
	}
	//�����������
	system("pause");
	system("cls");
}

void GradeManager::FindGrade_Show(const string& name)
{
	if (g_FileIsEmpty) {
		cout << "�ļ������ڣ�" << endl;
	}
	else {
		for (int i = 0; i < g_TotalNum; i++) {
			if (g_StudentArray[i]->g_name == name) {
				g_StudentArray[i]->ShowInfo();
			}
		}
	}
}

int GradeManager::FindGrade_Index(const string& name)
{
	if (g_FileIsEmpty) {
		cout << "�ļ������ڣ�" << endl;
	}
	else {
		for (int i = 0; i < g_TotalNum; i++) {
			if (g_StudentArray[i]->g_name == name) {
				return i;
				break;
			}
		}
	}
	return 0;
}

void GradeManager::ModGrade()
{
	if (g_FileIsEmpty) {
		cout << "�ļ������ڻ��߼�¼Ϊ��" << endl;
	}
	else {
		cout << "�������޸�ͬѧ��������" << endl;
		string name;
		cin >> name;
		
		int index = FindGrade_Index(name);

		Student* newStudent = NULL;

		string old_mame = g_StudentArray[index]->g_name;
		int old_chinese = g_StudentArray[index]->g_chinese;
		int old_english = g_StudentArray[index]->g_english;
		int old_math = g_StudentArray[index]->g_math;

		string new_mame;
		int new_chinese;
		int new_english;
		int new_math;


		cout << "1.�޸�����" << endl;
		cout << "2.�޸����ĳɼ�" << endl;
		cout << "3.�޸�Ӣ��ɼ�" << endl;
		cout << "4.�޸���ѧ�ɼ�" << endl;

		int choice;
		cin >> choice;

		switch (choice)
		{
		case 1:
			cin >> new_mame;
			newStudent = new Student(new_mame, old_chinese, old_english, old_math);
			break;
		case 2:
			cin >> new_chinese;
			newStudent = new Student(old_mame, new_chinese, old_english, old_math);
			break;
		case 3:
			cin >> new_english;
			newStudent = new Student(old_mame, old_chinese, new_english, old_math);
			break;
		case 4:
			cin >> new_math;
			newStudent = new Student(old_mame, old_chinese, old_english, new_math);
			break;
		}

		g_StudentArray[index] = newStudent;

		cout << "�޸�" << g_StudentArray[index]->g_name <<"�ĳɼ��ɹ�!"<< endl;

		Save();

	}
}

void GradeManager::SortGrades(string subject)
{
	scoreMap smap;
	if (subject == "����") {
		for (int i = 0; i < g_TotalNum; i++) {
			smap.insert(scoreMap::value_type(g_StudentArray[i]->g_chinese, i));
		}

		cout << subject << "���������Ϊ��" << endl;

		for (scoreMap::iterator it = smap.begin(); it != smap.end(); it++) {
			cout << g_StudentArray[it->second]->g_name << "  " << g_StudentArray[it->second]->g_chinese << endl;
		}
	}
	else if (subject == "Ӣ��") {
		for (int i = 0; i < g_TotalNum; i++) {
			smap.insert(scoreMap::value_type(g_StudentArray[i]->g_english, i));
		}

		cout << subject << "���������Ϊ��" << endl;

		for (scoreMap::iterator it = smap.begin(); it != smap.end(); it++) {
			cout << g_StudentArray[it->second]->g_name << "  " << g_StudentArray[it->second]->g_english << endl;
		}
	}
	else if (subject == "��ѧ") {
		for (int i = 0; i < g_TotalNum; i++) {
			smap.insert(scoreMap::value_type(g_StudentArray[i]->g_math, i));
		}

		cout << subject << "���������Ϊ��" << endl;

		for (scoreMap::iterator it = smap.begin(); it != smap.end(); it++) {
			cout << g_StudentArray[it->second]->g_name << "  " << g_StudentArray[it->second]->g_math << endl;
		}
	}

	system("pause");
}

void GradeManager::AllSortGrades()
{
	scoreMap sallmap;

	for (int i = 0; i < g_TotalNum; i++) {
		sallmap.insert(scoreMap::value_type(g_StudentArray[i]->scoreSum(), i));
	}

	cout << "�ܳɼ����������Ϊ��" << endl;

	for (scoreMap::iterator it = sallmap.begin(); it != sallmap.end(); it++) {
		cout << g_StudentArray[it->second]->g_name << "  " << it->first << endl;
	}
	system("pause");
}

int GradeManager::MaxGrade(string& subject)
{
	int maxScore = INT_MIN;
	if (subject == "����") {
		for (int i = 0; i < g_TotalNum; i++) {
			maxScore = max(maxScore, g_StudentArray[i]->g_chinese);
		}
	}
	else if (subject == "Ӣ��") {
		for (int i = 0; i < g_TotalNum; i++) {
			maxScore = max(maxScore, g_StudentArray[i]->g_english);
		}
	}
	else if (subject == "��ѧ") {
		for (int i = 0; i < g_TotalNum; i++) {
			maxScore = max(maxScore, g_StudentArray[i]->g_math);
		}
	}
	return maxScore;
}

int GradeManager::MinGrade(string& subject)
{
	int minScore = INT_MAX;
	if (subject == "����") {
		for (int i = 0; i < g_TotalNum; i++) {
			minScore = min(minScore, g_StudentArray[i]->g_chinese);
		}
	}
	else if (subject == "Ӣ��") {
		for (int i = 0; i < g_TotalNum; i++) {
			minScore = min(minScore, g_StudentArray[i]->g_english);
		}
	}
	else if (subject == "��ѧ") {
		for (int i = 0; i < g_TotalNum; i++) {
			minScore = min(minScore, g_StudentArray[i]->g_math);
		}
	}
	return minScore;
}

int GradeManager::AvergeGrade(string& subject)
{
	int avergeScore = 0;
	if (subject == "����") {
		for (int i = 0; i < g_TotalNum; i++) {
			avergeScore += g_StudentArray[i]->g_chinese;
		}
		avergeScore /= g_TotalNum;
	}
	else if (subject == "Ӣ��") {
		for (int i = 0; i < g_TotalNum; i++) {
			avergeScore += g_StudentArray[i]->g_english;
		}
		avergeScore /= g_TotalNum;
	}
	else if (subject == "��ѧ") {
		for (int i = 0; i < g_TotalNum; i++) {
			avergeScore += g_StudentArray[i]->g_math;
		}
		avergeScore /= g_TotalNum;
	}
	return avergeScore;
}

int GradeManager::MaxAllGrade()
{
	int maxAllGrade = INT_MIN;
	for (int i = 0; i < g_TotalNum; i++) {
		maxAllGrade = max(maxAllGrade, g_StudentArray[i]->g_chinese + g_StudentArray[i]->g_english + g_StudentArray[i]->g_math);
	}
	return maxAllGrade;

}

int GradeManager::MinAllGrade()
{
	int minAllGrade = INT_MAX;
	for (int i = 0; i < g_TotalNum; i++) {
		minAllGrade = min(minAllGrade, g_StudentArray[i]->g_chinese + g_StudentArray[i]->g_english + g_StudentArray[i]->g_math);
	}
	return minAllGrade;
}

int GradeManager::AvergeAllGrade()
{
	int avergeAllScore = 0;
	for (int i = 0; i < g_TotalNum; i++){
		avergeAllScore += g_StudentArray[i]->g_chinese + g_StudentArray[i]->g_english + g_StudentArray[i]->g_math;
	}
	avergeAllScore /= g_TotalNum;
	return avergeAllScore;
}

void GradeManager::VarSubject(string subject)
{
	cout << subject << "��ѧ�Ƴɼ����Ϊ��"
		<< "\t��߷֣�" << MaxGrade(subject)
		<< "\t��ͷ֣�" << MinGrade(subject)
		<< "\tƽ���֣�" << AvergeGrade(subject)
		<<endl;
	system("pause");
}


GradeManager::~GradeManager()
{
	if (g_StudentArray != NULL) {
		delete[] g_StudentArray;
		g_StudentArray = NULL;
	}
}


