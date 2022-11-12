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
	//初始化解析器
	aser = new Analyser();

	//1.文件不存在
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	//文件不存在情况
	if (!ifs.is_open()) {
		cout << "文件不存在" << endl;
		g_FileIsEmpty = true;
		g_TotalNum = 0;
		g_StudentArray = NULL;
		ifs.close();
		return;
	}

	//文件存在但没有记录
	char ch;
	ifs >> ch;

	if (ifs.eof())
	{
		cout << "文件为空！" << endl;
		g_FileIsEmpty = true;
		g_TotalNum = 0;
		g_StudentArray = NULL;
		ifs.close();
		return;
	}

	//文件存在并有记录
	int num = get_StudentNum();
	g_TotalNum = num;
	//cout << "学生人数：" << num << endl;

	//开辟空间
	g_StudentArray = new Student * [g_TotalNum];

	//文件存在并录入数组
	aser->InitGrades_txt(FILENAME,g_StudentArray);
}

void GradeManager::ShowMenuMain()
{
	cout << "*****************************************************" << endl;
	cout << "***************** 欢迎使用成绩管理系统 *****************" << endl;
	cout << "****************** 0.退出管理系统 *********************" << endl;
	cout << "****************** 1.录入成绩信息 *********************" << endl;
	cout << "****************** 2.修改成绩信息 *********************" << endl;
	cout << "****************** 3.查询学生成绩 *********************" << endl;
	cout << "*****************************************************" << endl;
	cout << endl;
}

void GradeManager::ShowMenuSecond_first()
{
	cout << "*****************************************************" << endl;
	cout << "****************** 1.按字段录入  *********************" << endl;
	cout << "****************** 2.按文件录入  *********************" << endl;
	cout << "*****************************************************" << endl;

	int choice = 0;
	cin >> choice;

	switch (choice)
	{
	case 1:
		AddGrade_filed();    //按字段添加成绩
		break;
	case 2:
		AssignFile();		//首先指定目录下文件
		break;
	default :
		system("cls");
		break;
	}
}

void GradeManager::ShowMenuSecond_second()
{
	cout << "*****************************************************" << endl;
	cout << "*********** 1.单科成绩最高分/最低分/平均分  *************" << endl;
	cout << "*********** 2.三科成绩最高分/最低分/平均分  *************" << endl;
	cout << "*********** 3.单科/三科成绩排名            *************" << endl;
	cout << "******************************************************" << endl;

	int choice = 0;
	cin >> choice;

	switch (choice)
	{
	case 1:
		ShowMenuThird_second();
		break;
	case 2:
		cout << "三科成绩情况："
			<< "\t最高分：" << MaxAllGrade()
			<< "\t最低分：" << MinAllGrade()
			<< "\t平均分：" << AvergeAllGrade()
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

//查找学生成绩
void GradeManager::ShowMenuThird_first()
{
	cout << "请输入学生姓名：" << endl;
	string name;
	cin >> name;
	ShowGrades();
}

//学生成绩单科情况
void GradeManager::ShowMenuThird_second()
{
	cout << "想知道哪门科目的成绩情况?" << endl;
	cout << "1.语文" << endl;
	cout << "2.英语" << endl;
	cout << "3.数学" << endl;

	int choice = 0;
	cin >> choice;

	switch (choice)
	{
	case 1:
		VarSubject("语文");
		break;
	case 2:
		VarSubject("英语");
		break;
	case 3:
		VarSubject("数学");
		break;
	default:
		system("cls");
		break;
	}
}

void GradeManager::ShowMenuThird_third()
{
	cout << "想知道哪门科目的排名情况？" << endl;
	cout << "1.单科排名" << endl;
	cout << "2.三科排名" << endl;

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

//单科排名细分菜单
void GradeManager::ShowMenuFourth_first()
{
	cout << "想知道哪个科目的排序成绩？"<<endl;
	cout << "1.语文" << endl;
	cout << "2.英语" << endl;
	cout << "3.数学" << endl;

	int choice = 0;
	cin >> choice;

	switch (choice) {
	case 1:
		SortGrades("语文");
		break;
	case 2:
		SortGrades("英语");
		break;
	case 3:
		SortGrades("数学");
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
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}

void GradeManager::AssignFile()
{
	cout << "请输入要操作的成绩表单名称:" << endl;
	string t_filename;
	cin >> t_filename;

	if (fileNmaeisAvaliable(t_filename)) { //判断文件是否有效

		AddGrade_fileName(t_filename);
	}
	else {
		cout << "输入有误" << endl;
	}

}

bool GradeManager::fileNmaeisAvaliable(const string &fileName)
{
	// Windows下文件名中不能包含\/:*?"<>|这些字符
	regex regExpress("[\\/:*?\"<>|]");
	bool pointValid = !std::regex_search(fileName, regExpress);

	string suffixx = aser->getFileSuffix(fileName);
	bool suffixValid = availableFileType->find(suffixx);

	return pointValid && suffixValid;
}

void GradeManager::AddGrade_filed()
{
	cout << "请输入录入学生成绩数量" << endl;

	int addNum = 0;
	cin >> addNum;

	if (addNum > 0) 
	{
		//计算空间大小
		int newSize = this->g_TotalNum + addNum;

		//开辟新空间
		Student** newSpace = new Student * [newSize];

		//将空间下的内容存放到新空间下
		if (this->g_StudentArray != NULL)
		{
			for (int i = 0; i < this->g_TotalNum; i++)
			{
				newSpace[i] = this->g_StudentArray[i];
			}
		}

		//输入新数据
		for (int i = 0; i < addNum; i++)
		{
			string t_name;
			int t_chinese;
			int t_english;
			int t_math;

			cout << "请输入第" << i + 1 << "个学生的姓名：" << endl;
			cin >> t_name;

			cout << "请输入第" << i + 1 << "个学生的语文成绩：" << endl;
			cin >> t_chinese;

			cout << "请输入第" << i + 1 << "个学生的英语成绩：" << endl;
			cin >> t_english;

			cout << "请输入第" << i + 1 << "个学生的数学成绩：" << endl;
			cin >> t_math;

			Student* st = new Student(t_name,t_chinese,t_english,t_math);

			//将学生成绩保存到新数组中
			newSpace[this->g_TotalNum + i] = st;
		}

		//释放原有空间
		delete[] g_StudentArray;

		//更改空间的指向
		g_StudentArray = newSpace;

		//更改学生人数
		g_TotalNum = newSize;

		//更改成绩表单不为空的标志
		g_FileIsEmpty = false;

		//保存文件
		Save();

		//提示信息
		cout << "成功添加" << addNum << "名学生成绩！" << endl;
	}
	else
	{
		cout << "输入有误" << endl;
	}

	//按任意键后清屏回到上级目录
	system("pause");
	system("cls");
}



void GradeManager::AddGrade_fileName(const string& fileName)
{
	string fileType = aser->getFileSuffix(fileName);
	//文件类型分支

	if (fileType == ".txt") {
		aser->InitGrades_txt(fileName,g_StudentArray);
	}

	if (fileType == ".csv") {
		
	}
}

void GradeManager::Save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out); //写文件

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
	ifs.open(FILENAME, ios::in); //打开文件

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
//	//关闭文件
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
//	//关闭文件
//	ifs.close();
//}

void GradeManager::ShowGrades()
{
	//判断文件是否为空
	if (g_FileIsEmpty) {
		cout << "文件不存在或记录为空" << endl;
	}
	else {
		for (int i = 0; i < g_TotalNum; i++) {
			g_StudentArray[i]->ShowInfo();
		}
	}
	//按任意键清屏
	system("pause");
	system("cls");
}

void GradeManager::FindGrade_Show(const string& name)
{
	if (g_FileIsEmpty) {
		cout << "文件不存在！" << endl;
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
		cout << "文件不存在！" << endl;
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
		cout << "文件不存在或者记录为空" << endl;
	}
	else {
		cout << "请输入修改同学的姓名：" << endl;
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


		cout << "1.修改姓名" << endl;
		cout << "2.修改语文成绩" << endl;
		cout << "3.修改英语成绩" << endl;
		cout << "4.修改数学成绩" << endl;

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

		cout << "修改" << g_StudentArray[index]->g_name <<"的成绩成功!"<< endl;

		Save();

	}
}

void GradeManager::SortGrades(string subject)
{
	scoreMap smap;
	if (subject == "语文") {
		for (int i = 0; i < g_TotalNum; i++) {
			smap.insert(scoreMap::value_type(g_StudentArray[i]->g_chinese, i));
		}

		cout << subject << "的排名情况为：" << endl;

		for (scoreMap::iterator it = smap.begin(); it != smap.end(); it++) {
			cout << g_StudentArray[it->second]->g_name << "  " << g_StudentArray[it->second]->g_chinese << endl;
		}
	}
	else if (subject == "英语") {
		for (int i = 0; i < g_TotalNum; i++) {
			smap.insert(scoreMap::value_type(g_StudentArray[i]->g_english, i));
		}

		cout << subject << "的排名情况为：" << endl;

		for (scoreMap::iterator it = smap.begin(); it != smap.end(); it++) {
			cout << g_StudentArray[it->second]->g_name << "  " << g_StudentArray[it->second]->g_english << endl;
		}
	}
	else if (subject == "数学") {
		for (int i = 0; i < g_TotalNum; i++) {
			smap.insert(scoreMap::value_type(g_StudentArray[i]->g_math, i));
		}

		cout << subject << "的排名情况为：" << endl;

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

	cout << "总成绩的排名情况为：" << endl;

	for (scoreMap::iterator it = sallmap.begin(); it != sallmap.end(); it++) {
		cout << g_StudentArray[it->second]->g_name << "  " << it->first << endl;
	}
	system("pause");
}

int GradeManager::MaxGrade(string& subject)
{
	int maxScore = INT_MIN;
	if (subject == "语文") {
		for (int i = 0; i < g_TotalNum; i++) {
			maxScore = max(maxScore, g_StudentArray[i]->g_chinese);
		}
	}
	else if (subject == "英语") {
		for (int i = 0; i < g_TotalNum; i++) {
			maxScore = max(maxScore, g_StudentArray[i]->g_english);
		}
	}
	else if (subject == "数学") {
		for (int i = 0; i < g_TotalNum; i++) {
			maxScore = max(maxScore, g_StudentArray[i]->g_math);
		}
	}
	return maxScore;
}

int GradeManager::MinGrade(string& subject)
{
	int minScore = INT_MAX;
	if (subject == "语文") {
		for (int i = 0; i < g_TotalNum; i++) {
			minScore = min(minScore, g_StudentArray[i]->g_chinese);
		}
	}
	else if (subject == "英语") {
		for (int i = 0; i < g_TotalNum; i++) {
			minScore = min(minScore, g_StudentArray[i]->g_english);
		}
	}
	else if (subject == "数学") {
		for (int i = 0; i < g_TotalNum; i++) {
			minScore = min(minScore, g_StudentArray[i]->g_math);
		}
	}
	return minScore;
}

int GradeManager::AvergeGrade(string& subject)
{
	int avergeScore = 0;
	if (subject == "语文") {
		for (int i = 0; i < g_TotalNum; i++) {
			avergeScore += g_StudentArray[i]->g_chinese;
		}
		avergeScore /= g_TotalNum;
	}
	else if (subject == "英语") {
		for (int i = 0; i < g_TotalNum; i++) {
			avergeScore += g_StudentArray[i]->g_english;
		}
		avergeScore /= g_TotalNum;
	}
	else if (subject == "数学") {
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
	cout << subject << "的学科成绩情况为："
		<< "\t最高分：" << MaxGrade(subject)
		<< "\t最低分：" << MinGrade(subject)
		<< "\t平均分：" << AvergeGrade(subject)
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


