#include <iostream>
#include <fstream>
using namespace std;

struct Student {
    int rollNo;
    char name[50];
    float marks;
};

void addStudent() {
    Student s;
    ofstream file("students.dat", ios::binary | ios::app);

    cout << "Enter Roll No: ";
    cin >> s.rollNo;

    cout << "Enter Name: ";
    cin >> s.name;

    cout << "Enter Marks: ";
    cin >> s.marks;

    file.write((char*)&s, sizeof(s));
    file.close();

    cout << "\nStudent Added Successfully!\n";
}

void displayStudents() {
    Student s;
    ifstream file("students.dat", ios::binary);

    cout << "\n----- Student Records -----\n";

    while(file.read((char*)&s, sizeof(s))) {
        cout << "Roll No: " << s.rollNo << endl;
        cout << "Name: " << s.name << endl;
        cout << "Marks: " << s.marks << endl;
        cout << "--------------------------\n";
    }

    file.close();
}

void searchStudent() {
    int roll;
    Student s;
    bool found = false;

    cout << "Enter Roll Number to Search: ";
    cin >> roll;

    ifstream file("students.dat", ios::binary);

    while(file.read((char*)&s, sizeof(s))) {
        if(s.rollNo == roll) {
            cout << "\nStudent Found\n";
            cout << "Name: " << s.name << endl;
            cout << "Marks: " << s.marks << endl;
            found = true;
            break;
        }
    }

    if(!found)
        cout << "Student Not Found\n";

    file.close();
}

void updateStudent() {
    int roll;
    Student s;

    cout << "Enter Roll Number to Update: ";
    cin >> roll;

    fstream file("students.dat", ios::binary | ios::in | ios::out);

    while(file.read((char*)&s, sizeof(s))) {
        if(s.rollNo == roll) {
            cout << "Enter New Name: ";
            cin >> s.name;

            cout << "Enter New Marks: ";
            cin >> s.marks;

            file.seekp(file.tellg() - streampos(sizeof(s)));
            file.write((char*)&s, sizeof(s));

            cout << "Record Updated Successfully\n";
            file.close();
            return;
        }
    }

    cout << "Student Not Found\n";
    file.close();
}

int main() {
    int choice;

    do {
        cout << "\n===== STUDENT MANAGEMENT SYSTEM =====\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Exit\n";
        cout << "Enter Choice: ";

        cin >> choice;

        switch(choice) {
            case 1:
                addStudent();
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                updateStudent();
                break;

            case 5:
                cout << "Thank You!\n";
                break;

            default:
                cout << "Invalid Choice\n";
        }

    } while(choice != 5);

    return 0;
}