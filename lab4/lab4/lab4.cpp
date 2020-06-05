
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>

using namespace std;



class DATA {
protected:
	int size = 255;
	vector<int> output;
	int code = 256;
	string method;
	string inputfile;
	string outputfile;
	void Create_Dictionary();
	unordered_map<string, int> Dictionary;
	void InfDecom();
	void InfCom();

};

class ARCHIVATOR :public DATA {
	string information;
	
	void InputInformation();
	void OutputInformation();
	void outputDict();
	void InArchive();
	void OutArchive();
	void CreateArchive();
public:
	ARCHIVATOR(int argc, char* argv[]);
};




int main(int argc, char* argv[])
{
	ARCHIVATOR archivator(argc,argv);
   
}


void DATA::InfCom() {
	cout << "Compresing " << inputfile << " in " << outputfile << endl;
	cout << "Done" << endl;
}
void DATA::InfDecom() {
	cout << "Getting out file " << outputfile<< endl;
	cout << "Done" << endl;
}

ARCHIVATOR::ARCHIVATOR(int argc, char* argv[])
{
	method=argv[1];
	if (method == "--compress") {//
		inputfile=argv[3];//
		outputfile=argv[2];//
		Create_Dictionary();//
		InputInformation();//
		InfCom();//
		InArchive();//
	}
	else if (method == "--decompress") {//
		inputfile=argv[2];//
		Create_Dictionary();//
		OutputInformation();//
		InfDecom();//
		OutArchive();
	}
}
void ARCHIVATOR::InputInformation() {
	ifstream fin(inputfile);
	int i = 0;
	while (!fin.eof()) {
		string val;
		fin >> val;
		if (i == 0) {
			information += val;
			i++;
		}
		else
			information += " " + val;
	}
	fin.close();
}

void ARCHIVATOR::OutputInformation() {
	fstream fin(inputfile);
	int i = 0;
	
	char* val = new char[code];
	while (!fin.eof()) {
		if (i == 0) {
			fin >> val;
			i++;
			outputfile=val;
		}
		int temp;
		fin >> temp;
		output.push_back(temp);
	}
	fin.close();
}

void DATA::Create_Dictionary() {
	string val;
	for (int i = 0; i < code; i++) {
		 val = "";
		val += char(i);
		Dictionary[val] = i;
		val.clear();
	}
}
void ARCHIVATOR::outputDict() {
	for (int i = 0; i <= size; i++) {
		string ch = "";
		ch += char(i);
		cout << Dictionary[ch] << " , ";
	}
	cout << endl;
}
void ARCHIVATOR::CreateArchive() {
	ofstream fout(outputfile);
	for (int i = 0; i < output.size() + 1; i++)
	{
		if (i == 0) {fout << inputfile << " ";continue;}
		fout << output[i - 1] << " ";
	}
	fout.close();
}
void ARCHIVATOR::InArchive() {
	string char1 = "", char2 = "";
	char1 += information[0];
	for (int i = 0; i < information.length(); i++) {
		if (i != information.length() - 1)
			char2 += information[i + 1];
		if (Dictionary.find(char1 + char2) != Dictionary.end()) {char1 = char1 + char2;}
		else {
			output.push_back(Dictionary[char1]);
			Dictionary[char1 + char2] = code;
			code++;
			char1 = char2;
		}
		char2 = "";
	}
	output.push_back(Dictionary[char1]);
	CreateArchive();
}
void ARCHIVATOR::OutArchive() {
	unordered_map<int, string> val;
	string num ;
	for (int i = 0; i <code; i++) {
		
		num += char(i);
		val[i] = num;
		num.clear();
	}
	int old = output[0], n;
	string c = "";
	string sc = val[old];
	string str;
	c += sc[0];
	str += sc;
	int count = 256;
	for (int i = 0; i < output.size() - 1; i++) {
		n = output[i + 1];
		if (val.find(n) == val.end()) {	sc = val[old];	sc = sc + c;}	
		else {
			sc = val[n];
		}
		str += sc;
		c = "";
		c += sc[0];
		val[count] = val[old] + c;
		count++;
		old = n;
	}
	string name = outputfile;
	ofstream out(name);
	for (int i = 0; i < str.size(); i++) {
		out << str[i];
	}
	out.close();
}