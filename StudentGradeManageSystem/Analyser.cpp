#include "Analyser.h"

string Analyser::getFileSuffix(const string& fileName)
{
	return fileName.substr(fileName.find_last_of('.') + 1);
}

void Analyser::InitGrades_txt(const string& path,Student ** tempStudent)
{
	ifstream ifs;
	ifs.open(path, ios::in);

	string name;
	int ch;
	int en;
	int ma;


	int index = 0;
	while (ifs >> name && ifs >> ch && ifs >> en && ifs >> ma) {
		Student* student = new Student(name, ch, en, ma);
		tempStudent[index] = student;
		index++;
	}

	//¹Ø±ÕÎÄ¼ş
	ifs.close();
}

void Analyser::OutGrades_txt(string txt, Student** tempStudent)
{
}

void Analyser::InitGrades_csv(const string& path, Student** tempStudent)
{
}

void Analyser::OutGrades_csv(string csv, Student** tempStudent)
{
}


