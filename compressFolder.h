#pragma once
#include<conio.h>
#include<direct.h>
#include"FileCompress.h"
#include<Windows.h>
void DuyetDeNen(string name, string foldernamecompress) {//name là tên thư mục muốn nén, foldernameco,press là tên thư mục sau khi nén
	string TenFile = name;//một biến lưu tên thư mục
	foldernamecompress = foldernamecompress + "huff";//tên thư mục sau nén sẽ có thêm đuôi huff để phân biệt với folder ban đầu
	_mkdir(foldernamecompress.c_str());//tạo thư mục mới để lưu những file nén
	TenFile.append("\\*.*");
	WIN32_FIND_DATA data;
	HANDLE find;
	if ((find = FindFirstFile(TenFile.c_str(), &data)) != INVALID_HANDLE_VALUE) {//nếu tím thấy file  đầu tiền trong thư mục
		do {
			if (!(data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {//de chi hien thi tap tin khong hien thi thu muc
				if (strstr(data.cFileName, ".txt") != NULL) {
					string a = name + "\\" + data.cFileName;//tên của thư tập tin cần nén
					TestCompress(a, foldernamecompress + "\\" + data.cFileName);//chuyền vào tên tập tin cần nén và tên tập tin sau khi nén
				}
			}
			else {
				if (strcmp(data.cFileName, ".") && strcmp(data.cFileName, "..")) {//kiểm tra nếu tìm thấy là một folder thì kiểm tra nó
					//có bằng "." và ".." nếu không thì thực hiện các lệnh dưới
					string a = name + "\\" + data.cFileName;//tên thư mục con 
					//gọi lại hàm duyệt chuyền vào tên thư mục con,
					//và tên của thư mục sau nén
					DuyetDeNen(string(a), foldernamecompress + "\\" + data.cFileName);

				};
			}
			//kiểm tra còn tìm thấy thêm file hay folder hay không
		} while (FindNextFile(find, &data) != 0);
		//đóng folder
		FindClose(find);
	}
}
void DuyetDeGiaiNen(string name, string foldernamedecompresss) {//chuyên vào tên file cần được giải nén và file lưu sau khi giải nén
	string TenFile = name;//lưu tên thư mục cha
	string a = foldernamedecompresss;//lưu tên thư mục lưu những thứ sau giải nén
	char*b = NULL;
	foldernamedecompresss = foldernamedecompresss.substr(0, foldernamedecompresss.find("huff"));
	//khi thư mục giải nén được tạo ra để không bị chùng lặp tên với thư mục ban đầu thì tên của thư mục sẽ thêm số 1 đằng sau;
	foldernamedecompresss = foldernamedecompresss + "1";
	_mkdir(foldernamedecompresss.c_str());//tạo thư mục mới để lưu những file nén
	TenFile.append("\\*.*");
	WIN32_FIND_DATA data;
	HANDLE find;
	//tìm kiếm file đầu tiên trong folder hoặc file 
	if ((find = FindFirstFile(TenFile.c_str(), &data)) != INVALID_HANDLE_VALUE) {
		do {
			if (!(data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {//nếu tìm thấy là một file thì thực hiện các dòng trong if
				//so sánh của tên file tìm thấy nếu trùng vời thì huffman, có nghĩ file là file nén
				if (strstr(data.cFileName, ".huffman") != NULL) {
					//tên file sẽ bào gồm đường dẫn đến file
					string a = name + "\\" + data.cFileName;
					//chuyền file cần nén, và thư mục chứa file sau nén
					TestUnCompress(a, foldernamedecompresss + "\\" + data.cFileName);
				}
			}
			else {
				//nếu tìm thấy là một folder thì kiểm tra tên folder tìm được khác "." và ".." hay không
				if (strcmp(data.cFileName, ".") && strcmp(data.cFileName, "..")) {
					//lưu tên folder cần phải nén
					string a = name + "\\" + data.cFileName;
					//tiếp tục duyệt folder vừa tìm thấy, chuyền vào dường dẫn folder cần duyệt và tên folder sau khi 
					//duyệt xong sẽ lưu dữ liệu vào đó
					DuyetDeGiaiNen(string(a), foldernamedecompresss + "\\" + data.cFileName);
				};
			}
			// tìm kiếm coi còn file hay folder nào khác trong thư mục đang duyệt
		} while (FindNextFile(find, &data) != 0);
		//đóng thư mục
		FindClose(find);
	}

}
