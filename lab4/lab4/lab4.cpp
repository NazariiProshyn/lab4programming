
#include <iostream>
#include<string>
#include <unordered_map>
#include<fstream>
using namespace std;
class Data
{
public:

	///void setfunction(string set);
	//string getfunction();
	//void setnameoffile(string setname);
	//string nameoffile();
protected:
	vector <int> archive_out;
	int size = 255, code = 256;
	void CreateDictionary();
	unordered_map<string, int> Dictionary;
	string function;
	string inputfile;
	string outputfile;
};

class archivator :public Data
{
public:
	archivator(int argc, char* argv[]);

private:
	string information;
	void inputinformation();
	void outputinformation();
	void NotUsefullFunction();
	void NotUsefullFunction2();
	void archive_file();
	void Create_Archive();
};



int main(int argc, char* argv[])
{
	archivator archive(argc, argv);
}

archivator::archivator(int argc, char* argv[])
{
	function = argv[1];
	if (function == "--compress") {
		inputfile = argv[3];
		outputfile = argv[2];
		CreateDictionary();
		inputinformation();
		NotUsefullFunction();
	}
	else if (function == "--decompress") {
		inputfile = argv[2];
		CreateDictionary();
		outputinformation();
	}
}

void archivator::inputinformation()
{
	ifstream fin(inputfile);
	int i = 0; string inp;
	while (!fin.eof()) {
		fin >> inp;
		if (i == 0) { information += inp; i++; }
		else { information += " " + inp; }
		inp.clear();
	}
	fin.close();
}

void archivator::outputinformation()
{
	ifstream fin(inputfile);
	int i = 0; string inp;
	while (!fin.eof())
	{
		fin >> inp;
		if (i == 0) { information += inp; i++; }
		else { information += " " + inp; }
		inp.clear();
	}
	fin.close();
}

void archivator::NotUsefullFunction()
{
	cout << "Compresing... " << inputfile << " in " << outputfile << endl;
	cout << "Done" << endl;
}

void archivator::NotUsefullFunction2()
{
	cout << "Getting out file " << outputfile << " ..." << endl;
	cout << "Done" << endl;
}

void archivator::archive_file()
{
	string char1 = "", char2 = "";
	char1 += information[0];
	for (int i = 0; i < information.length(); i++) {
		if (i != information.length() - 1)
			char2 += information[i + 1];
		if (Dictionary.find(char1 + char2) != Dictionary.end()) {
			char1 = char1 + char2;
		}
		else {
			archive_out.push_back(Dictionary[char2]);
			Dictionary[char1 + char2] = code;
			code++;
			char1 = char2;
		}
		char2 = "";
	}
	archive_out.push_back(Dictionary[char1]);
	Create_Archive();
}

void archivator::Create_Archive()
{
	ofstream fout(outputfile);
	for (int i = 0; i < archive_out.size() + 1; i++)
	{
		if (i == 0) {
			fout << inputfile << " ";
			continue;
		}
		fout << archive_out[i - 1] << " ";
	}
	fout.close();
}


void Data::CreateDictionary()
{
	string val;
	for (int i = 0; i < code; i++) {
		val = '0' + i;
		Dictionary[val] = i;
		val.clear();
	}
}
