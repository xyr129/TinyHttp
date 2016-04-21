#pragma once
#define _CRT_SECURE_NO_EARNING

#include<iostream>
using namespace std;

typedef long LongType;

struct FileInfo
{
	unsigned char _ch;  //�ַ�
	LongType _count;    //�ַ����ִ���
	string _code;       //�ַ�haffman����

	FileInfo()
		:_count(0)
	{}

	bool operator<(const FileInfo& f1)
	{
		return _count < f1._count;
	}
	bool operator != (const FileInfo& f1)const
	{
		return (_ch != f1._ch)&&(_count!=f1._count);
	}
	FileInfo operator+(const FileInfo& f1)
	{
		FileInfo tmp ;
		tmp._count = _count + f1._count;
		return tmp;
	}
};

FileInfo invalid;
class FileCompress
{
	typedef HaffmanTreeNode<FileInfo> HTNode;
public:
	FileCompress()
	{
		for (size_t i = 0; i < 256; ++i)
		{
			_file[i]._ch = i;
		}
	}
public:
	bool Compress(const char* filename)
	{
		assert(filename);
		//1�����ļ���ͳ�Ƹ��ַ����ִ���
		FILE* Input = fopen(filename, "rb");
		assert(Input);
		char ch = fgetc(Input);
		while (ch != EOF)
		{
			_file[(unsigned char)ch]._count++;
			ch = fgetc(Input);
		}
		fclose(Input);

		//2�����ɶ�Ӧ��Haffman����
		HaffmanTree<FileInfo> t(_file, 256, invalid);
		_CreateHaffmanCode(t._root);

		//3��ѹ��
		string compress = "fileHuf.txt";
		//compress += "Huf";
		FILE* Output = fopen(compress.c_str(), "wb");
		assert(Output);
		Input = fopen(filename, "rb");
		assert(Input);
		int index = 0;
		int count = 0;
		unsigned char inch = 0;
		ch = fgetc(Input);
		long long chCount = 0;
		while (ch != EOF)
		{
			chCount++;
			string& code = _file[(unsigned char)ch]._code;
			//��haffman����ת���ַ�λ
			for (size_t i = 0; i < code.size(); ++i)
			{
				inch <<= 1;
				if (code[i] == '1')
				{
					inch |= 1;
				}
				if (++index == 8)
				{
					fputc(inch, Output);
					inch = 0;
					index = 0;
				}
			}
			ch = fgetc(Input);
		}
		//ʣ�಻��һ���ֽ�
		int rest = 8 - index;
		if (index != 0)
		{
			inch <<= rest;
			fputc(inch, Output);
		}

		//4��д�����ļ�
		string config = "config.txt";
		FILE* configFile = fopen(config.c_str(), "w");

		//д����Ч�ַ���
		char str[128];
		_itoa((chCount >> 32), str, 10);
		fputs(str, configFile);//д�����ֽ�
		fputc('\n', configFile);
		_itoa(chCount & 0xffffffff, str, 10);
		fputs(str, configFile);//д�����ֽ�
		fputc('\n', configFile);


		for (size_t i = 0; i < 256; ++i)
		{
			string chInfo;
			string str;
			if (_file[i]._count>0)
			{
				chInfo += _file[i]._ch;
				chInfo += ',';
				chInfo += _itoa(_file[i]._count, (char*)str.c_str(), 10);
				chInfo += '\n';
			}
			fputs(chInfo.c_str(), configFile);
		}

		fclose(Input);
		fclose(Output);
		return true;
	}

	bool UnCompress(const char* compressFile, const char* configFile)
	{
		assert(compressFile && configFile);
		FILE* config = fopen(configFile, "rb");
		assert(config);
		FILE* comFile = fopen(compressFile, "rb");
		assert(comFile);

		//�������ַ���
		long long chCount = 0;
		string line;
		_Readline(config, line);
		chCount = atoi(line.c_str());
		chCount <<= 32;
		line.clear();
		_Readline(config, line);
		chCount += atoi(line.c_str());
		line.clear();
		
		//1�����������ļ��ؽ�haffman��
		while (_Readline(config,line))
		{
			//��������
			if (line.size()>1)
			{
				unsigned char ch = line[0];
				_file[ch]._count = atoi(line.substr(2).c_str());
				line.clear();
			}
			else
			{
				line = '\n';
			}
			
		}

		HaffmanTree<FileInfo> t(_file, 256, invalid);


		//��ѹ��
		string filename = "com.txt";
		FILE* Output = fopen(filename.c_str(), "w");

		HaffmanTreeNode<FileInfo>* cur = t._root;
		char ch = fgetc(comFile);
		char bit = 7;
		while (!feof(comFile))
		{
			if ((ch &(1 << bit)) == 0)
			{
				cur = cur->_left;
			}
			else
			{
				cur = cur->_right;
			}
			if (cur->_left == NULL && cur->_right == NULL)
			{
				fputc(cur->_weight._ch, Output);
				cur = t._root;
				if (--chCount == 0)
				{
					break;
				}
			}
			bit--;
			
			if (bit == -1)
			{
				bit = 7;
				ch = fgetc(comFile);
			}

		}
		fclose(config);
		fclose(comFile);
		return true;
	}

protected:
	void _CreateHaffmanCode(HTNode* root)
	{
		if (NULL == root)
		{
			return;
		}
		_CreateHaffmanCode(root->_left);
		_CreateHaffmanCode(root->_right);
		if (root->_left == NULL && root->_right == NULL)
		{
			HTNode* cur = root;
			HTNode* parent = root->_parent;
			string& code = _file[cur->_weight._ch]._code;
			while (parent)
			{
				if (cur == parent->_left)
				{
					code += '0';
				}
				if (cur == parent->_right)
				{
					code += '1';
				}
				cur = parent;
				parent = cur->_parent;
			}
			reverse(code.begin(), code.end());
		}
	}
	bool _Readline(FILE* fOut, string& str)
	{
		char ch = fgetc(fOut);
		if (ch == EOF)
		{
			return false;
		}
		while (ch != EOF && ch != '\n')
		{
			str += ch;
			ch = fgetc(fOut);
		}
		return true;
	}

protected:
	FileInfo _file[256];
};


