#include	<iostream>
#include	<cstdlib>
#include	<cstdio>
#include    <fstream>
#include    <string>
#include	<iomanip>
#include	"List.h"
#include    "LibStudent.h"
#include    "LibBook.h"			

//#define true (rand() % 100 < 98)					    //WARNING! PURE EVIL CODE: Enable this to confuse the hell out of the programmer

#define _CRT_SECURE_NO_WARNINGS							//Ignore some minor safety errors, or ... at least it should
const int SIZE = 256;									//Constant String Size throughout the projec
List* type1 = new List;									//To store type 1 warned list
List* type2 = new List;									//To store type 2 warned list

using namespace std;									//Disable this to avoid namespace contamination

bool ReadFile(string, List*);							
bool DeleteRecord(List *, char *);						
bool Display(List*, int, int);							
bool SearchStudent(List*, char* id, LibStudent&);		
bool InsertBook(string, List *);						
bool computeAndDisplayStatistics(List *);				
bool printStuWithSameBook(List *, char *);				
bool displayWarnedStudent(List *, List *, List *);		
int menu();												

char* Convert_WS(char*);								//Convert Underscore to White Space
void Convert_Date(char*, Node*, int, bool);				//Covert Date to invidual days, months and year
int JulianDay(int, int, int);							//Convert Gorgorian Date to Julian Day

int main() {
	cout << "@All rights reserved for 1802834 - UCCD1024\n";

	int choice = 0;										//Selection integer
	List* stu_list = new List;							//Primary list for storing student details
	LibBook book;										
	LibStudent stu;										
	char id[10], callNum[20];
	
	while (choice != 9) {
		choice = menu();
		if (choice == 1) {	//Read F(x)
			cout << "\n\nREAD FILE SELECTED\n\n\n";
			if (ReadFile("student.txt", stu_list));
			else cout << "\n\nWARNING: UNEXPECTED ERROR HAD OCCURED!\n\n";
		}
		if (choice == 2) { //Delete F(x)
			string d;
			int z = 0;
			cout << "\n\nDELETE RECORD SELECTED\n\n";
			if (stu_list->size() == 0) {
				cout << "\nStudent linked list is empty! Read a file first.\n\n";
				continue;
			}
			cout << "\nPlease Enter ID: ";
			cin >> id;
			cout << "\n\nDo you wish to delete the record?\n\n1. YES\n2. NO\nEnter your choice: ";
			cin >> d;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			for (int i = 0; i < size(d); i++) z += (int)d[i];		//Converting string to their ASCII number
			if (z == 49) {
				if (DeleteRecord(stu_list, id)) cout << "\n\nRecord ID \"" << id << "\" has successfully been deleted.\n\n";
				else cout << "\n\nRecord ID \"" << id << "\" cannot be found in the list.\n\n";
			}
			else if (z == 50) cout << "\n\nDelete record has been cancelled, returning to main menu.\n\n";
			else cout << "\n\nInvalid Input! Please try again.\n\n";
		}
		if (choice == 3) {	//Search F(x)
			cout << "\n\nSEARCH RECORD SELECTED\n\n";
			if (stu_list->size() == 0) {
				cout << "\nStudent linked list is empty! Read a file first.\n\n";
				continue;
			}
			cout << "\nPlease Enter ID: ";
			cin >> id;
			if(SearchStudent(stu_list,id,stu)) cout << "\n\nRecord ID \"" << id << "\" has successfully been found.\n\n";
			else cout << "\n\nRecord ID \"" << id << "\" cannot be found in the list.\n\n";
		}
		if (choice == 4) {	//Insert Book F(x)
			cout << "\n\nINSERT BOOK SELECTED\n";
			if (InsertBook("book.txt", stu_list));
			else cout << "\n\nStudent linked list is empty! Read a file first.\n\n";
		}
		if (choice == 5) { //Display F(x)
			int source, detail;
			cout << "\n\nDISPLAY SELECTED\n";
			if (stu_list->size() == 0) {
				cout << "\n\nStudent linked list is empty! Read a file first.\n\n";
				continue;
			}
			cout << "\n\nOutput Selection\n\n1. Display to file\n2. Display to screen"; //Type 2 only
			cout << "\nPlease Enter Display Option: ";
			cin >> source;
			cout << "\n\nDisplay Details\n\n1. Display Student Info Only\n2. Display Student Info and Book Info"; //Type 1 only
			cout << "\nPlease Enter Details Option: ";
			cin >> detail;
			if(Display(stu_list, source, detail)) cout << "\n\nRecord displayed successfully.\n\n";
			else cout << "\n\nWARNING: UNEXPECTED ERROR HAD OCCURED!\n\n";
		}
		if (choice == 6) { //Display Stats
			cout << "\n\nDISPLAY STATISTIC SELECTED\n";
			if (computeAndDisplayStatistics(stu_list)) cout << "\n\nStatistic displayed successfully.\n\n";
			else cout << "\n\nStudent linked list is empty! Read a file first.\n\n";
		}
		if (choice == 7) { //Compare Same Book
			cout << "\n\nSTUDENT WITH SAME BOOK SELECTED\n\n";
			if (stu_list->size() == 0) {
				cout << "\nStudent linked list is empty! Read a file first.\n\n";
				continue;
			}
			cout << "\nPlease Enter Book Call Number: ";
			cin >> callNum;
			cout << endl;
			if (printStuWithSameBook(stu_list, callNum)) cout << "\nStatistic displayed successfully.\n\n";
			else cout << "\nNo student have the book with Call Number: \"" << callNum << "\" borrowed.\n\n";
		}
		if (choice == 8) { //Insert and Display Warned Student
			cout << "\n\nDISPLAY WARNED LIST SELECTED\n";
			if (stu_list->size() == 0) {
				cout << "\n\nStudent linked list is empty! Read a file first.\n\n";
				continue;
			}
			if (displayWarnedStudent(stu_list, type1, type2)) cout << "\nWarned List displayed successfully.\n\n";
			else cout << "\n\nBoth Warned List is empty!\n\n";
		}
		if (choice == 0)cout << "\n\nInvalid Input! Please try again.\n\n";
	}
	cout << "\n\nPROGRAM TERMINATED\n";
	cout << "\n\n";
	system("pause");
	return 0;
}

int menu()
{
	string x;
	int y = 0;
	cout << "\nMenu\n\n";
	cout << "1. Read File\n";
	cout << "2. Delete Record\n";
	cout << "3. Search Student\n";
	cout << "4. Insert Book\n";
	cout << "5. Display Output\n";
	cout << "6. Compute and Display Statistics\n";
	cout << "7. Student with Same Book\n";
	cout << "8. Display Warned Student\n";
	cout << "9. Exit\n";
	cout << "Enter your choice: ";
	cin >> x;		
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	for (int i = 0; i < size(x); i++) y += (int)x[i];		//Converting string to their ASCII number
	switch (y) {
	case 49: return 1;
		break;
	case 50: return 2;
		break;
	case 51: return 3;
		break;
	case 52: return 4;
		break;
	case 53: return 5;
		break;
	case 54: return 6;
		break;
	case 55: return 7;
		break;
	case 56: return 8;
		break;
	case 57: return 9;
		break;
	default: return 0;
	}
}

bool ReadFile(string filename, List* list) {
	ifstream in;
	char temp[256];							
	Node* stu_list_node;
	int count = 0;							//Counter for books successfully been read				
	int Dupe = 0;							//Used to check for number of Duped record

	LibStudent stu_lib_info;				//Temporary Student Struct to store details

	in.open(filename);
	if (in.is_open()) {
		while (!in.eof()) {
			bool duping = false;			//Used to check for is the readed record a dupe of not
			for (int i = 0; i < 3; i++) {
				in >> temp;
			}
			in >> stu_lib_info.id;
			for (int i = 0; i < 2; i++) {
				in >> temp;
			}
			in.getline(stu_lib_info.name,256);
			for (int i = 0; i < 2; i++) {
				in >> temp;
			}
			in >> stu_lib_info.course;
			for (int i = 0; i < 3; i++) {
				in >> temp;
			}
			in >> stu_lib_info.phone_no;
			for (int i = 1; i <= list->size(); i++) {
				stu_list_node = list->find(i);
				if (strcmp(stu_list_node->item.id, stu_lib_info.id) == 0) {
					Dupe++;
					cout << "Alert! Student:" << stu_lib_info.name << " - with ID \"" << stu_lib_info.id << "\" has been repeated, student details is not read.\n\n\n";
					duping = true;
				}
				if (duping == true) break;	//If the record is a dupe, then skip to the next student info to read
			}
			if (duping == false) {
				list->insert(stu_lib_info);
				count++;
			}
		}
		cout << count << " Record(s) has successfully been read.\n\n";
		if (Dupe > 0)cout << "\nWarning! " << Dupe << " Duplicated Record(s) are found.\n\n";
	}
	else {
		cout << "Error! Cannot open " << filename << " file.\n";
		return false;
	}
	in.close();
	return true;
}

bool DeleteRecord(List* list, char* id) {
	Node* stu_list_node;
	type temp_info;
	//Removes student details from actual list, type 1 and type 2
	for (int i = 1; i <= list->size(); i++) {
		list->get(i, temp_info);
		if (strcmp(temp_info.id,  id)==0) {
			list->remove(i);
			for (int i = 1; i <= type1->size(); i++) {
				stu_list_node = type1->find(i);
				if (strcmp(stu_list_node->item.id, id) == 0) {
					type1->remove(i);
				}
			}
			for (int i = 1; i <= type2->size(); i++) {
				stu_list_node = type2->find(i);
				if (strcmp(stu_list_node->item.id, id) == 0) {
					type2->remove(i);
				}
			}
			return true;
		}
	}
	return false;
}

bool SearchStudent(List* list, char* id, LibStudent& stu) {
	for (int i = 1; i <= list->size(); i++) {
		list->get(i, stu);
		if (strcmp(stu.id, id) == 0) {		//Matching ID
			cout << "\n\n***************************************************************";
			stu.print(cout);
			cout << "\n***************************************************************\n";
			return true;
		}
	}
	return false;
}

bool Display(List* list, int source, int detail) {
	type temp_info;
	ofstream out;
	if (detail == 1) {			//Student Info Only
		if (source == 1) {			//Print to File
			out.open("student_info.txt");
			for (int i = 1; i <= list->size(); i++) {
				list->get(i, temp_info);
				out << "\nSTUDENT " << i;
				temp_info.print(out);
				out << "\n***************************************************************\n";
			}
			out.close();
			cout << "\n\nOutput File: \"student_info.txt\" has been created/updated.\n";
			return true;
		}
		else if (source == 2) {		//Print to Screen
			cout << "\n***************************************************************\n";
			for (int i = 1; i <= list->size(); i++) {
				list->get(i, temp_info);
				cout << "\nSTUDENT " << i;
				temp_info.print(cout);
				cout << "\n***************************************************************\n";
			}
			return true;
		}
	}
	else if (detail == 2) {		//Student Info + Book
		if (source == 1) {			//Print to File
			out.open("student_booklist.txt");
			for (int i = 1; i <= list->size(); i++) {
				list->get(i, temp_info);
				out << "\nSTUDENT " << i;
				temp_info.print(out);
				if (temp_info.totalbook != 0) {
					out << "\nBOOK LIST:\n";
					for (int x = 0; x < temp_info.totalbook; x++) {
						out << "\nBook " << x + 1 << endl;
						temp_info.book[x].print(out);
					}
				}else out << "\nThis student didn't borrow any book.\n";
				out << "\n***************************************************************\n";
			}
			out.close();
			cout << "\n\nOutput File: \"student_booklist.txt\" has been created/updated.\n";
			return true;
		}
		else if (source == 2) {		//Print to Screen
			cout << "\n***************************************************************\n";
			for (int i = 1; i <= list->size(); i++) {
				list->get(i, temp_info);
				cout << "\nSTUDENT " << i;
				temp_info.print(cout);
				if (temp_info.totalbook != 0) {
					cout << "\nBOOK LIST:\n";
					for (int x = 0; x < temp_info.totalbook; x++) {
						cout << "\nBook " << x + 1 << endl;
						temp_info.book[x].print(cout);
					}
				}
				else cout << "\nThis student didn't borrow any book.\n";
				cout << "\n***************************************************************\n";
			}
			return true;
		}
	}
	return false;
}

bool InsertBook(string filename, List* list) {
	ifstream in;
	char temp[SIZE], temp2[SIZE], temp3[SIZE];	//First temp for storing details, other 2 stores temporary Date information
	char* pch = new char[20];					//Token Pointer for Author Separator
	char* next_pch = NULL;						//Another Pointer for the Author Separator
	Node* stu_list_node;						//Using Node for Shallow Copying
	char temptitle[SIZE], tempid[SIZE];			//Temporary Storage for Not Found case
	
	List* temp_list = new List;
	Node* temp_node;							//Temporary Node to store shallow copied details
	LibStudent stu_book;						//Temporary Book Struct to store details
		
	int Dupe = 0;								//Counter for duped books
	int bookcount = 0;							//Counter for books for insertion

	int CDate = JulianDay(29, 3, 2020);			//Assumed Current Date : 29/3/2020
	int DDate;									//Due Date in Julian Day
	
	int NotFound = 0;							//To check for number of student not in the list
	
	in.open(filename);
	if (in.is_open()) {
		while (!in.eof()) {		
			bool duping = false;
			in >> temp;							//Comparing ID
			strcpy_s(tempid, sizeof(tempid), temp);
			if (list->size() == 0) return false;
			bool NF = true;						//Bool flag tag for invalid ID found
			for (int i = 1; i <= list->size(); i++) {
				if (in.eof()) break;
				stu_list_node = list->find(i);
				int totalbook = stu_list_node->item.totalbook;
				if (strcmp(stu_list_node->item.id, temp) == 0) {
					temp_list->insert(1, stu_book);
					temp_node = temp_list->find(1);
					in >> temp;
					int x = 0;															//Author Counter
					pch = strtok_s(temp, "/", &next_pch);								//Separating Authors into tokens
					while (pch != NULL) {												//Separating the Authors until next ptr = NULL
						/*stu_book.book[totalbook].author[x] = (char *)malloc(SIZE)*/	//Malloc or New to initialize a new author memory
						temp_node->item.book[totalbook].author[x] = new char[SIZE];
						strcpy_s(temp_node->item.book[totalbook].author[x], SIZE, Convert_WS(pch));
						pch = strtok_s(NULL, "/", &next_pch);
						x++;
					}
					in >> temp;															//Inserting Title
					strcpy_s(stu_book.book[totalbook].title, sizeof(stu_book.book[totalbook].title), Convert_WS(temp));
					in >> temp;															//Publisher
					strcpy_s(stu_book.book[totalbook].publisher, sizeof(stu_book.book[totalbook].publisher), Convert_WS(temp));
					in >> stu_book.book[totalbook].ISBN;								//ISBN
					in >> stu_book.book[totalbook].yearPublished;						//Year Published
					in >> stu_book.book[totalbook].callNum;								//Call Number
					in >> temp;
					strcpy_s(temp2, sizeof(temp2), temp);
					Convert_Date(temp, temp_node, totalbook, 0);						//Borrow Date
					in >> temp;
					strcpy_s(temp3, sizeof(temp3), temp);
					Convert_Date(temp, temp_node, totalbook, 1);						//Due Date
					
					DDate = JulianDay(temp_node->item.book[totalbook].due.day, temp_node->item.book[totalbook].due.month, temp_node->item.book[totalbook].due.year);
					if (CDate - DDate < 0) stu_book.book[totalbook].fine = 0;			//If true, then book is not in Due
					else {
						stu_book.book[totalbook].fine = (CDate - DDate) * 0.5;			//Else, every day's fine is RM0.50 from Due
					}
					NF = false;	//Since comparision is true, then invalid ID is false
					if (stu_list_node->item.totalbook != 0) { //Don't need to compare when no books  are available
						//Comparing books callNum and borrow date, since a student cant have the 2 books with the same callNum at the exact same borrowing date
						for (int i = 0; i < stu_list_node->item.totalbook; i++) {
							if (strcmp(stu_list_node->item.book[i].callNum, stu_book.book[totalbook].callNum) == 0) {
								int temp_borrow1 = JulianDay(stu_list_node->item.book[i].borrow.day, stu_list_node->item.book[i].borrow.month, stu_list_node->item.book[i].borrow.year);
								int temp_borrow2 = JulianDay(temp_node->item.book[totalbook].borrow.day, temp_node->item.book[totalbook].borrow.month, temp_node->item.book[totalbook].borrow.year);
								if (temp_borrow1 == temp_borrow2) {
									Dupe++;
									cout << "\n\nAlert! Book: " << stu_book.book[totalbook].title << "- with Call Number \"" << stu_book.book[totalbook].callNum << "\" has been repeated, book details is not inserted.\n";
									duping = true;
								}
							}

						}
					}
					if (duping == false) {	//If the book is not a dupe, then temporary holder will be inserted into the actual list
						for (int i = 0; i < x; i++) {
							stu_list_node->item.book[totalbook].author[i] = new char[SIZE];
							strcpy_s(stu_list_node->item.book[totalbook].author[i], SIZE, temp_node->item.book[totalbook].author[i]);
						}
						strcpy_s(stu_list_node->item.book[totalbook].title, sizeof(stu_list_node->item.book[totalbook].title), stu_book.book[totalbook].title);
						strcpy_s(stu_list_node->item.book[totalbook].publisher, sizeof(stu_list_node->item.book[totalbook].publisher), stu_book.book[totalbook].publisher);
						strcpy_s(stu_list_node->item.book[totalbook].ISBN, sizeof(stu_list_node->item.book[totalbook].ISBN), stu_book.book[totalbook].ISBN);
						stu_list_node->item.book[totalbook].yearPublished = stu_book.book[totalbook].yearPublished;
						strcpy_s(stu_list_node->item.book[totalbook].callNum, sizeof(stu_list_node->item.book[totalbook].callNum), stu_book.book[totalbook].callNum);
						Convert_Date(temp2, stu_list_node, totalbook, 0);
						Convert_Date(temp3, stu_list_node, totalbook, 1);
						stu_list_node->item.book[totalbook].fine = stu_book.book[totalbook].fine;
						bookcount++;
						stu_list_node->item.totalbook++;
					}
					stu_list_node->item.calculateTotalFine();
					temp_list->remove(1);
					break;
				}
			}if (NF == true) {	//If not ID matches, then read in all remaining data into temp buffer and skips to next ID
				NotFound++;
				for (int i = 0; i < 2; i++) in >> temp;
				strcpy_s(temptitle, sizeof(temptitle), Convert_WS(temp));
				cout << "\n\nAlert! Book: " << temptitle << "- with matching Student ID: \"" << tempid << "\" cannot be found, book is not inserted.\n";
				for (int i = 0; i < 6; i++) in >> temp;
			}
		}
		cout << "\n\n" << bookcount << " Book(s) inserted successfully to student list.\n\n";
		if (NotFound > 0) cout << "\nWarning! " << NotFound << " Books are not inserted as matching Student ID is not found.\n\n";
		if(Dupe > 0) cout << "\nWarning! " << Dupe << " Duplicated Record(s) are found. \n\n";
	}else
	{
		cout << "Error! Cannot open " << filename << " file.\n";
		return true;
	}
	in.close();
	return true;
}

bool computeAndDisplayStatistics(List* list) {
	Node* stu_list_node;
	string course[5] = { "CS","IA","IB","CN","CT" };					//Initializing 5 Courses
	int StuNo[5] = { 0 }, BookBorrowed[5] = { 0 }, BookDue[5] = { 0 };	//Initializing all stats
	double TotalDueFine[5] = { 0 };										//Initializing fines
	int tuple = 0;														//To identify the course tuple
	char temp[SIZE];

	if (list->size() == 0) return false;
	for (int i = 1; i <= list->size(); i++) {
		stu_list_node = list->find(i);
		strcpy_s(temp, SIZE, stu_list_node->item.course);	//Comparing node's course with exsisting tuple
		if (strcmp(temp, "CS") == 0) tuple = 0;				//For each course, that node is assigned a tuple for stats
		else if (strcmp(temp, "IA") == 0) tuple = 1;
		else if (strcmp(temp, "IB") == 0) tuple = 2;
		else if (strcmp(temp, "CN") == 0) tuple = 3;
		else if (strcmp(temp, "CT") == 0) tuple = 4;
		StuNo[tuple]++;
		BookBorrowed[tuple] += stu_list_node->item.totalbook;
		TotalDueFine[tuple] += stu_list_node->item.total_fine;
		for (int i = 1; i <= stu_list_node->item.totalbook; i++) {
			if (stu_list_node->item.book[i - 1].fine > 0) {	//If no fine, then no due book
				BookDue[tuple]++;
			}
			else continue;
		}
	}
	cout << "\n\n========================================================================================================";
	cout << "\n\nCourse\tNumber of Students\tTotal Books Borrowed\tTotal Overdue Books\tTotal Overdue Fine(RM)\n";
	cout << "\n========================================================================================================\n\n";
	for (tuple = 0; tuple < 5; tuple++) {
		cout << course[tuple] << "\t" << StuNo[tuple] << "\t\t\t";
		cout << BookBorrowed[tuple] << "\t\t\t" << BookDue[tuple] << "\t\t\t";
		cout << setprecision(2) << fixed << TotalDueFine[tuple] << endl;
	}
	cout << "\n========================================================================================================\n";
	return true;
}

bool printStuWithSameBook(List* list, char* callNum) {
	Node* stu_list_node;
	LibBook stu_list_book;
	int SameNo = 0;									//To test if there's any book that is the same
	strcpy_s(stu_list_book.callNum, 20, callNum);	//Initializing a new struct LibBook to use the compare f(x)

	for (int i = 1; i <= list->size(); i++) {		//First Loop finds how many student have the same book
		stu_list_node = list->find(i);
		for (int totalbook = 0; totalbook < stu_list_node->item.totalbook; totalbook++) {
			if ((stu_list_book.compareCallNum(stu_list_node->item.book[totalbook]) == 1))  SameNo++;
		}
	}
	if (SameNo == 0) return false;
	cout << "\nThere are " << SameNo << " students that borrow the book with call number \"" << callNum << "\" as shown below :\n\n";
	for (int i = 1; i <= list->size(); i++) {		//Second Loop prints out the details
		stu_list_node = list->find(i);
		for (int totalbook = 0; totalbook < stu_list_node->item.totalbook; totalbook++) {	//Testing every book in each student
			if ((stu_list_book.compareCallNum(stu_list_node->item.book[totalbook]) == 1)) {	//If true, it will print out the details
				cout << "Id: " << stu_list_node->item.id << endl;
				cout << "Name:" << stu_list_node->item.name << endl;
				cout << "Course: " << stu_list_node->item.course << endl;
				cout << "Phone No: " << stu_list_node->item.phone_no << endl;
				cout << "Borrow Date: ";
				stu_list_node->item.book[totalbook].borrow.print(cout);
				cout << endl;
				cout << "Due Date: ";
				stu_list_node->item.book[totalbook].due.print(cout);
				cout << endl << endl;
			}
		}
	}
	return true;
}

bool displayWarnedStudent(List* list, List* type1, List* type2) {
	LibStudent stu_list_info;
	Node* stu_list_node;
	Node* stu_dupe;
	int totalbook;							//Totalbook to test each book for every student
	int CDate = JulianDay(29, 3, 2020);		//Assumed current date is 29/3/2020

	for (int i = 1; i <= list->size(); i++) {
		list->get(i, stu_list_info);
		bool dupet1 = 0;
		bool dupet2 = 0;
		int type1due = 0;					//To record books with due duration more than or equal to 10 days
		int type2due = 0;					//To record any book that is due 
		for (totalbook = 0; totalbook < stu_list_info.totalbook; totalbook++) {
			int DDate = JulianDay(stu_list_info.book[totalbook].due.day, stu_list_info.book[totalbook].due.month, stu_list_info.book[totalbook].due.year);
			if (CDate - DDate >= 10) type1due++;
			if (CDate - DDate > 0) type2due++;
			else continue;
		}
		for (int i = 1; i <= type1->size(); i++) {
			stu_dupe = type1->find(i);
			if (strcmp(stu_dupe->item.id, stu_list_info.id) == 0) dupet1 = 1;
		}
		for (int i = 1; i <= type2->size(); i++) {
			stu_dupe = type2->find(i);
			if (strcmp(stu_dupe->item.id, stu_list_info.id) == 0) dupet2 = 1;
		}
		if (dupet1 != 1) {				//If true, then student is inserted to TYPE 1
			if (type1due > 2) type1->insert(stu_list_info);
		}
		if (dupet2 != 1) {				//If true, then student is inserted to TYPE 2
			if (stu_list_info.totalbook == type2due && stu_list_info.total_fine > 50) type2->insert(stu_list_info);
		}
	}
	if (type1->size() == 0 && type2->size() == 0)return false;	//If both list is empty, returing false			
	cout << "\n\n***************************************************************\n\n";
	cout << "\nType 1 Warned List:\n**Student has more than 2 books that are overdue for >= 10 days. ";		//Print out TYPE 1 Warned List
	if (type1->size() != 0) {
		for (int i = 1; i <= type1->size(); i++) {
			stu_list_node = type1->find(i);
			stu_list_node->item.print(cout);
			cout << "\nBOOK LIST:\n";
			for (int x = 0; x < stu_list_node->item.totalbook; x++) {
				cout << "\nBook " << x + 1 << endl;
				stu_list_node->item.book[x].print(cout);
			}
			if (i != type1->size())cout << "\n===============================================================";
		}
	}
	else cout << "\n\nType 1 Warned List is empty!";
	cout << "\n\n***************************************************************\n\n";
	cout << "\nType 2 Warned List:\n**Total fine for a student is more than RM50.00 and every book in the student¡¯s book list are overdue. ";	//Print out TYPE 2 Warned List
	if (type2->size() != 0) {
		for (int i = 1; i <= type2->size(); i++) {
			stu_list_node = type2->find(i);
			stu_list_node->item.print(cout);
			cout << "\nBOOK LIST:\n";
			for (int x = 0; x < stu_list_node->item.totalbook; x++) {
				cout << "\nBook " << x + 1 << endl;
				stu_list_node->item.book[x].print(cout);
			}
			if (i != type2->size())cout << "\n===============================================================";
		}
	}
	else cout << "\n\nType 2 Warned List is empty!";
	cout << "\n\n***************************************************************\n";
	cout << endl;
	return true;
}

//Convert Underscore to White Space
char* Convert_WS(char* temp) { 
	char* pch = new char[SIZE];
	char* next_pch = NULL;
	char buffer[SIZE];

	pch = strtok_s(temp, "_", &next_pch);		//Separates underscore into whitespace
	bool once = 1;								//To insure first strcpy runs only once
	while (pch != NULL) {
		if (once == 1) strcpy_s(buffer, sizeof(buffer), pch);
		else if (once == 0) strcat_s(buffer, sizeof(buffer), pch);
		strcat_s(buffer, sizeof(buffer), " ");
		pch = strtok_s(NULL, "_", &next_pch);
		once = 0;
	}
	return buffer;								//Converted char string is returned back
}

//Covert Date to invidual days, months and year
void Convert_Date(char* temp, Node* node, int i, bool bd) {
	char* pch = new char[SIZE];
	char* next_pch = NULL;

	if (bd == 0) {									//Borrow Date
		int x = 1;
		pch = strtok_s(temp, "/", &next_pch);		//Separates Date into tokens						
		while (pch != NULL) {
			if (x == 1)node->item.book[i].borrow.day = stoi(pch);
			else if (x == 2)node->item.book[i].borrow.month = stoi(pch);
			else if (x == 3)node->item.book[i].borrow.year = stoi(pch);
			pch = strtok_s(NULL, "/", &next_pch);
			x++;
		}
	}
	else if (bd == 1) {								//Due Date
		int x = 1;
		pch = strtok_s(temp, "/", &next_pch);		//Separates Date into tokens						
		while (pch != NULL) {
			if (x == 1)node->item.book[i].due.day = stoi(pch);
			else if (x == 2)node->item.book[i].due.month = stoi(pch);
			else if (x == 3)node->item.book[i].due.year = stoi(pch);
			pch = strtok_s(NULL, "/", &next_pch);
			x++;
		}
	}
}

//Convert Gorgorian Date to Julian Day
int JulianDay(int D, int M, int Y) {
	int JDN = (1461 * (Y + 4800 + (M - 14) / 12)) / 4 + (367 * (M - 2 - 12 * ((M - 14) / 12))) / 12 - (3 * ((Y + 4900 + (M - 14) / 12) / 100)) / 4 + D - 32075;
	return JDN;
}
