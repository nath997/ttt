#include<iostream>
#include<fstream>
#include<conio.h>
#include<string.h>
#include<iomanip>
#include"console.h"

using namespace std;

#define FALSE 0
#define TRUE 1
#define AGAIN -1

const int MAX = 100;


struct Student
{
	int id;  // ma so sinh vien
	char lastName[100]; // ho 
	char firstName[10]; // ten
	char classID[10]; // ten lop
};

struct List
{
	int nStudent = 0;   
	Student Student[MAX];
};

int searchInfo(List List, int id) // tim sinh vien theo ma so neu co tra ve true
{
	for (int i = 0; i < List.nStudent; i++)
	{
		if (List.Student[i].id == id)
			return TRUE;  // co sinh sinh voi cung id 
	}
	return FALSE; // khong co sinh vien voi cung id 
}

int searchPOS(List List, int id) // tim kiem sinh vien voi cung id va xuat ra vi tri cua sinh vien do
{
	for (int i = 0; i < List.nStudent; i++)
	{
		if (List.Student[i].id == id)
			return i;
	}
}

int insertStudent(List &List, int pos, Student Temp) // chen mot hoc sinh vao vi tri pos 
{
	if (List.nStudent == MAX)
		return FALSE;
	if (pos > List.nStudent)
		return FALSE;
	for (int i = List.nStudent; i > pos; i--)
		List.Student[i] = List.Student[i - 1];
	List.Student[pos] = Temp;
	List.nStudent += 1;
	return TRUE;
}

int deletePOS(List &List, int pos) // xoa sinh vien theo vi tri
{
	if (pos >= List.nStudent || List.nStudent == 0)
		return FALSE;
	if (pos == List.nStudent - 1)
	{
		List.nStudent--;
		return TRUE;
	}
	for (int i = pos; i < List.nStudent - 1; i++)
		List.Student[i] = List.Student[i + 1];
	List.nStudent--;
	return TRUE;
}

int deleteStudent(List &List, int id) // xoa sinh vien co trung so id
{
	if (searchInfo(List, id) == FALSE)
		return FALSE;
	else
	{
		int pos;
		pos=searchPOS(List, id);
		deletePOS(List, pos);
		return TRUE;
	}
}

int deleteStudent(List &List, char *classID) // xoa nhung sinh vien co ma lop la ClassID
{
	int s = 0;
	for (int i = 0; i < List.nStudent; i++)
	{
		if (_stricmp(List.Student[i].classID, classID) == 0)
		{
			deletePOS(List, i);
			i--;
			s++;
		}
	}
	return s;
}

int sortList(List &List) // sap xep List theo thu tu ma so sinh vien tu nho den lon
{
	Student Temp;
	if (List.nStudent == 0)
		return FALSE;
	for (int i = 0; i < List.nStudent-1; i++)
	{
		for (int j = i+1; j < List.nStudent; j++)
		{
			if (List.Student[i].id > List.Student[j].id)
			{
				Temp = List.Student[i];
				List.Student[i] = List.Student[j];
				List.Student[j] = Temp;
			}
		}
	}
}

int importStudent(List List, Student &Temp)  // nhap du lieu cho mot hoc sinh
{
	cout << "Nhap ma so sinh vien vao:  ", cin >> Temp.id;
	if (searchInfo(List, Temp.id) == TRUE)
		return AGAIN;
	if (Temp.id < 0)
		return FALSE;
	fflush(stdin);
	cout << "Nhap ho cua sinh vien:      ", cin.getline(Temp.lastName, 100);
	cout << "Nhap ten cua sinh vien:     ", cin.getline(Temp.firstName, 10);
	cout << "Nhap ma lop cua sinh vien:  ", cin.getline(Temp.classID, 10);
	cout << endl << endl;
	return TRUE;
}

void importList(List &List) // Nhap du lieu cho List
{
	int err; // bien kiem tra loi va cung la nhap du lieu cho bien student
	Student Temp;
	while (List.nStudent < MAX)
	{
		err = importStudent(List, Temp);
		switch (err)
		{
			case TRUE:
			{
				List.Student[List.nStudent] = Temp;
				List.nStudent++;
			}
			case FALSE:
			{
				cout << "Ngung nhap lieu";
				break;
			}
			case AGAIN:
			{
				cout << "Da co sinh vien voi ma so: " << Temp.id << endl;
				continue;
			}
		}
	}
}

int insertStudent(List &List) // Chen mot hoc sinh vao mang da sap xep va van giu thu tu sap xep do , overloaded function
{
	sortList(List); // sap xep
	Student Temp;
	int err;  // kiem tra loi
	while (List.nStudent < MAX)
	{
		err = importStudent(List, Temp);
		switch (err)
		{
		case TRUE:
		{
			int i = 0;
			for (i; (i < List.nStudent) && (Temp.id >= List.Student[i].id); i++){} // khi vong lap ngung lai thi vi tri thu i la vi tri can chen 
			insertStudent(List, i, Temp);
		}
		case FALSE:
		{
			cout << "Ngung nhap lieu";
			break;
		}
		case AGAIN:
		{
			cout << "Da co sinh vien voi ma so: " << Temp.id << endl;
			continue;
		}
		}
	}
}


int main()
{


	
	_getch();
}



