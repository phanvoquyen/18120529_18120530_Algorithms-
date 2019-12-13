#include"HuffmanTree.h"
#include"FileCompress.h"
#include"compressFolder.h"
#include<string>
#include<iostream>
int main()
{
	string filename;

	cout << "You want to:" << endl;
	cout << "1. Compress" << endl;
	cout << "2. UnCompress" << endl;
	cout << "3: compress the foler" << endl;
	cout << "4: decompress the folder" << endl;
	cout << "0. Thoat" << endl;
	cout << "Your choose: ";
	int i = 0;
	cin >> i;
	cout << "Enter full your filename or folder: ";
	cin >> filename;
	switch (i)
	{
	case 1:
		TestCompress(filename, filename);
		break;
	case 2:
		TestUnCompress(filename, filename);
		break;
	case 3: {
		DuyetDeNen(filename, filename);
	}
			break;
	case 4: {
		DuyetDeGiaiNen(filename, filename);
	}
	default:
		break;
	}
	system("pause");
	return 0;
}