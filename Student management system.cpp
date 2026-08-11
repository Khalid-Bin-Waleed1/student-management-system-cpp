/*

TASK NO : 1

**STUDENT MANAGEMENT SYSTEM**

Project memebers details:
+------------------------+-------------+---------+
| Name                   | ID          | Section |
+------------------------+-------------+---------+
| Saad Bin Usman         | F2025376144 | A-10    |
| Ali Usman              | F2025376150 | A-10    |
| Khalid Bin Waleed      | F2025376122 | A-10    |
| Hamza Malik            | F2025376145 | A-10    |
+------------------------+-------------+---------+
*/

// we have also used some extra functions in this student management system because when we enter we enter maximum students the code evry time asks
// to enter maximum number of students which many times cause data program faliure logicaly and some time over writes data on the files so we create 
// a new function to resize capacity named in the code but in user interface named as increase capacity and locked the maximum number students permanaently
// in a new file and make a function for reset the new capacity and also add a new function named as delete student so it looks a proper student management 
// system we also add some key security layers to inhance the working of the code such as call save to file functions at every student is added so if user
// accidently forget to save data it may not have any data loss and call load function in main so at evey execution of program it automatically load the files
// and fetch data from the file and user do not need to enter any data again and again these are the some quality changes and additions we make to inhance 
// the working of the code. 

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct Student {

int id;
string name;
int noofsub;
float * marks;
float avg;
char grade;

};
void loadfile(Student [] , int & , int);
void add_student(Student [] , int & );
void calculate_avg_grade(Student &);
void search_student(Student [] , int);
void display_student(Student [] , int);
void savetofile(Student [] , int);
void resize_capacity(Student * & , int & , int &);
void delete_student(Student [], int &);
void reset_capacity(Student* & , int & , int &);
void printMenu();

int main(){
	
	cout << "******************************************" << endl;
     cout <<"*  WELCOME TO THE STUDENT RECORDS PORTAL *" << endl;
    cout << "******************************************" << endl;
	
    int maxStudents = 0 , count = 0, choice;
    ifstream configIn("config.txt");
    if (configIn >> maxStudents) {
        cout << "Loaded saved capacity: " << maxStudents << endl;
    } else {
        cout << "Enter max number of students: ";
        cin >> maxStudents;
        ofstream configOut("config.txt");
        configOut << maxStudents;
        configOut.close();
    }
    configIn.close();
    Student* students = new Student[maxStudents];
    
    loadfile(students , count , maxStudents);

    do {
        printMenu();
        cin >> choice;
        switch(choice) {
            case 1: loadfile(students , count , maxStudents); break;
            case 2: if (count < maxStudents){
            	         add_student(students , count);
            	         savetofile (students , count);
			           } 
			         else{
				           cout << "Capacity Full" << endl;
			          }
			          break;
			    
            case 3: display_student(students , count); break;
            case 4: search_student(students , count); break;
            case 5: savetofile(students , count); break;
            case 6: resize_capacity(students , count , maxStudents); break;
            case 7: delete_student(students , count); break;
            case 8: reset_capacity(students , count , maxStudents); break;
        }
    } while (choice != 9);

    for (int i = 0; i < count; i++) delete[] students[i].marks;
    delete[] students;
    return 0;
}

void calculate_avg_grade(Student &s){

float sum = 0;
for (int i = 0; i < s.noofsub; i++){
    sum = sum + s.marks[i];
}
s.avg = sum / s.noofsub;

if (s.avg >= 90){

    s.grade = 'A';
}
else if (s.avg >= 80){

    s.grade = 'B';
}
else if (s.avg >= 70){

    s.grade = 'C';
}
else if (s.avg >= 60){

    s.grade = 'D';
}
else if (s.avg >= 50){

    s.grade = 'E';
}
else{
    s.grade = 'F';
}
}
void add_student(Student students[] , int & count){
    cout << "Enter ID : " << endl;
    cin >> students[count].id;
    cout << "Enter Name : " << endl;
    cin >> students[count].name;
    cout << "Enter no of Subjects : " << endl;
    cin >> students[count].noofsub;

    students[count].marks = new float[students[count].noofsub];

    for (int i = 0; i < students[count].noofsub; i++){
        cout << "Enter Marks of subject"<< " " << (i+1) << " : " << endl;
        cin >> students[count].marks[i];
    }
    calculate_avg_grade(students[count]);
    count++;
}
void display_student(Student students[] , int count){
	    cout << "ID" << "\t" << "Name" << "\t" << "Average" << "\t" << "grade" << endl;
    for (int i = 0; i < count; i++) { 
        cout << students[i].id << "\t" << students[i].name << "\t" << students[i].avg << "\t" << students[i].grade << endl;
    }

}
void search_student(Student students[] , int count){
    int id;
    cout << "Enter ID to search: " << endl;
    cin >> id;
    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            cout << "Found: " << students[i].name << " Grade: " << students[i].grade << endl;
            return;
        }
    }
    cout << "Student not found." << endl;
}
void savetofile(Student students[], int count) {
    ofstream outFile("students.txt");
    
    if (!outFile){
    	cout << "Error: Could not open file for writing!" << endl;
        return;
	}
    outFile << "ID" << "\t" << "Name" << "\t" << "No of Subjects" << endl;
    for (int i = 0; i < count; i++) {
        outFile << students[i].id << "\t" << students[i].name << "\t" << students[i].noofsub << endl;
        for (int j = 0; j < students[i].noofsub; j++){
        	outFile << "Subject : " << (j+1) << "=";
        	outFile << students[i].marks[j] << "\t";        	
		}
        outFile << endl;
    }
    outFile.close();
    cout << "Data saved successfully to students.txt" << endl;
}

void loadfile(Student students[], int &count , int maxStudents ) {
    for (int i = 0; i < count; i++ ){
    	delete[] students[i].marks;
	}
	count = 0;
	
	
	
	ifstream inFile("students.txt");
    if (!inFile) {
        cout << "File could not be opened!" << endl;
        return;
    }
    while (count < maxStudents && inFile >> students[count].id >> students[count].name >> students[count].noofsub) {
        students[count].marks = new float[students[count].noofsub];
        for (int i = 0; i < students[count].noofsub; i++) {
            inFile >> students[count].marks[i];
        }
        calculate_avg_grade(students[count]);
        count++;
    }
    
    if (count >= maxStudents && !inFile.eof()) {
        cout << "Warning: Reached max capacity, not all records were loaded." << endl;
    }
    
    inFile.close();
    cout << "Data loaded successfully! Total students loaded: " << count << endl;
}
void resize_capacity(Student* &students, int &count, int &maxStudents) {
    int newMax;
    cout << "Enter new maximum number of students: ";
    cin >> newMax;

    if (newMax < count) {
        cout << "Error: New capacity is smaller than current number of students!" << endl;
        return;
    }

    Student* newStudents = new Student[newMax];

    for (int i = 0; i < count; i++) {
        newStudents[i] = students[i];
    }

    delete[] students;

    students = newStudents;
    maxStudents = newMax;
    cout << "Capacity updated successfully!" << endl;
}
void delete_student(Student students[], int &count) {
    int id, index = -1;
    cout << "Enter ID to delete: ";
    cin >> id;

    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Student ID not found!" << endl;
        return;
    }
    
    delete[] students[index].marks;

    for (int i = index; i < count - 1; i++) {
        students[i] = students[i + 1];
    }
    count--;
    
    savetofile(students, count);
    cout << "Student deleted successfully." << endl;
}
void reset_capacity(Student* &students, int &count, int &maxStudents) {
    
    for (int i = 0; i < count; i++) delete[] students[i].marks;
    delete[] students;

    remove("config.txt");
    
    cout << "Enter new max number of students: ";
    cin >> maxStudents;
    ofstream configOut("config.txt");
    configOut << maxStudents;
    configOut.close();

    students = new Student[maxStudents];
    count = 0;
    cout << "System reset." << endl;
}
void printMenu() {
    cout << "\n==========================================" << endl;
    cout << "   STUDENT MANAGEMENT SYSTEM" << endl;
    cout << "==========================================" << endl;
    cout << " 1. Load Data        | 6. Increase Capacity" << endl;
    cout << " 2. Add Student      | 7. Delete Student" << endl;
    cout << " 3. Display All      | 8. Reset System" << endl;
    cout << " 4. Search Student   | 9. Exit" << endl;
    cout << " 5. Save Data" << endl;
    cout << "==========================================" << endl;
    cout << " Select an option [1-9]: ";
}