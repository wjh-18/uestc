#include<iostream>
#include"CLFileOperator.h"
using namespace std;
int main() {
	CLFileOperator *Opt=new CLFileOperator("test2.txt");
	Opt->Write("0123456789");//第一次写
	Opt->Write("abcdefg");//第二次写
	char buf[30];
	Opt->Read(buf, 1,3);
	cout << buf << endl;
	Opt->Read(buf, 2,4);
	cout << buf << endl;
	Opt->Read(buf, 3,5);
	cout << buf << endl;
	return 0;
}
