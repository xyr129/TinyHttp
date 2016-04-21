#pragma once
#include"HaffmanTree.h"
#include"FileCompress.h"
#include<windows.h>

void TestHT()
{
	int array[] = { 2, 5, 4, 6, 9, 3, 0, 8, 1, 7 };
	HaffmanTree<int> hf(array, 10, -1);
	hf.Print();
}

void TestFileCompress()
{
	FileCompress file;
	int start1 = GetTickCount();
	file.Compress("bigFile.txt");
	int end1 = GetTickCount();
	cout<<end1-start1<<endl;
	
	/*FileCompress file1;
	//int start2 = GetTickCount();
	file1.UnCompress("fileHuf.txt", "config.txt");
	//int end2 = GetTickCount();
	//cout << end2-start2 << endl;*/
}

int main()
{
	//TestHT();
	TestFileCompress();
	system("pause");
	return 0;
	
}