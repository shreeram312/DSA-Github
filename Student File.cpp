//Student File


#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct Student {
    int rollNumber;
    char name[50];
    char division;
    char address[100];
};

void addStudent() {
    ofstream file("student.txt", ios::app | ios::binary);
    if (!file) {
        cout << "Error opening file.\n";
        return;
    }
    
    Student student;
    
    cout << "Enter Roll Number: ";
    cin >> student.rollNumber;
    cin.ignore();
    
    cout << "Enter Name: ";
    cin.getline(student.name, 50);
    
    cout << "Enter Division: ";
    cin >> student.division;
    cin.ignore();
    
    cout << "Enter Address: ";
    cin.getline(student.address, 100);
    
    file.write(reinterpret_cast<char*>(&student), sizeof(Student));
    
    cout << "Student added successfully.\n";
    
    file.close();
}

void deleteStudent(int rollNumber) {
    ifstream file("student.txt", ios::in | ios::binary);
    if (!file) {
        cout << "Error opening file.\n";
        return;
    }
    
    ofstream tempFile("temp.txt", ios::out | ios::binary);
    if (!tempFile) {
        cout << "Error creating temporary file.\n";
        file.close();
        return;
    }
    
    Student student;
    bool found = false;
    
    while (file.read(reinterpret_cast<char*>(&student), sizeof(Student))) {
        if (student.rollNumber == rollNumber) {
            found = true;
            continue;
        }
        
        tempFile.write(reinterpret_cast<char*>(&student), sizeof(Student));
    }
    
    file.close();
    tempFile.close();
    
    remove("student.txt");
    rename("temp.txt", "student.txt");
    
    if (found) {
        cout << "Student deleted successfully.\n";
    } else {
        cout << "Student not found.\n";
    }
}

void displayStudent(int rollNumber) {
    ifstream file("student.txt", ios::in | ios::binary);
    if (!file) {
        cout << "Error opening file.\n";
        return;
    }
    
    Student student;
    bool found = false;
    
    while (file.read(reinterpret_cast<char*>(&student), sizeof(Student))) {
        if (student.rollNumber == rollNumber) {
            found = true;
            cout << "Roll Number: " << student.rollNumber << endl;
            cout << "Name: " << student.name << endl;
            cout << "Division: " << student.division << endl;
            cout << "Address: " << student.address << endl;
            break;
        }
    }
    
    file.close();
    
    if (!found) {
        cout << "Student not found.\n";
    }
}

void searchStudent() {
    int rollNumber;
    cout << "Enter Roll Number of the Student to search: ";
    cin >> rollNumber;
    displayStudent(rollNumber);
}

int main() {
    int choice;
    
    while (true) {
        cout << "\nStudent Information Menu:\n";
        cout << "1. Add Student\n";
        cout << "2. Delete Student\n";
        cout << "3. Display Student\n";
        cout << "4. Search Student\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                int rollNumber;
                cout << "Enter Roll Number of the Student to delete: ";
                cin >> rollNumber;
                deleteStudent(rollNumber);
                break;
            case 3:
                cout << "Enter Roll Number of the Student to display: ";
                cin >> rollNumber;
                displayStudent(rollNumber);
                break;
            case 4:
                searchStudent();
                break;
            case 5:
                exit(0);
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}

