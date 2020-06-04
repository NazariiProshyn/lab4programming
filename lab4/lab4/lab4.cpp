﻿
#include <iostream>
#include<string>
#include <unordered_map>
using namespace std;
class Data
{
public:

	///void setfunction(string set);
	//string getfunction();
	//void setnameoffile(string setname);
	//string nameoffile();
protected:
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

	}
	else if (function == "--decompress") {
		inputfile = argv[2];

	}
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