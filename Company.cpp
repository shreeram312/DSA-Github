//Company


#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct Employee {
    int empId;
    char name[50];
    char designation[50];
    float salary;
};

struct IndexRecord {
    int empId;
    int offset;
};

void addEmployee() {
    ofstream dataFile("employee.dat", ios::binary | ios::app);
    ofstream indexFile("index.dat", ios::binary | ios::app);

    if (!dataFile || !indexFile) {
        cout << "Error opening file.\n";
        return;
    }

    Employee employee;
    IndexRecord indexRecord;

    cout << "Enter Employee ID: ";
    cin >> employee.empId;
    cout << "Enter Name: ";
    cin.ignore();
    cin.getline(employee.name, 50);
    cout << "Enter Designation: ";
    cin.getline(employee.designation, 50);
    cout << "Enter Salary: ";
    cin >> employee.salary;

    indexRecord.empId = employee.empId;
    indexRecord.offset = dataFile.tellp();

    dataFile.write(reinterpret_cast<char*>(&employee), sizeof(Employee));
    indexFile.write(reinterpret_cast<char*>(&indexRecord), sizeof(IndexRecord));

    cout << "Employee added successfully.\n";

    dataFile.close();
    indexFile.close();
}

void displayEmployee(int empId) {
    ifstream dataFile("employee.dat", ios::binary);
    ifstream indexFile("index.dat", ios::binary);

    if (!dataFile || !indexFile) {
        cout << "Error opening file.\n";
        return;
    }

    Employee employee;
    IndexRecord indexRecord;
    bool found = false;

    while (indexFile.read(reinterpret_cast<char*>(&indexRecord), sizeof(IndexRecord))) {
        if (indexRecord.empId == empId) {
            dataFile.seekg(indexRecord.offset);
            dataFile.read(reinterpret_cast<char*>(&employee), sizeof(Employee));

            cout << "Employee ID: " << employee.empId << endl;
            cout << "Name: " << employee.name << endl;
            cout << "Designation: " << employee.designation << endl;
            cout << "Salary: " << employee.salary << endl;

            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Employee not found.\n";
    }

    dataFile.close();
    indexFile.close();
}

void deleteEmployee(int empId) {
    fstream dataFile("employee.dat", ios::binary | ios::in | ios::out);
    fstream indexFile("index.dat", ios::binary | ios::in | ios::out);

    if (!dataFile || !indexFile) {
        cout << "Error opening file.\n";
        return;
    }

    Employee employee;
    IndexRecord indexRecord;
    bool found = false;

    while (indexFile.read(reinterpret_cast<char*>(&indexRecord), sizeof(IndexRecord))) {
        if (indexRecord.empId == empId) {
            dataFile.seekg(indexRecord.offset);
            dataFile.read(reinterpret_cast<char*>(&employee), sizeof(Employee));

            cout << "Employee ID: " << employee.empId << endl;
            cout << "Name: " << employee.name << endl;
            cout << "Designation: " << employee.designation << endl;
            cout << "Salary: " << employee.salary << endl;

            found = true;
            break;
        }
    }

    if (found) {
        char confirm;
        cout << "Are you sure you want to delete this employee? (Y/N): ";
        cin >> confirm;

        if (confirm == 'Y' || confirm == 'y') {
            int deleteOffset = indexFile.tellg() - static_cast<streampos>(sizeof(IndexRecord));
            indexFile.seekp(deleteOffset);
            indexFile.write(reinterpret_cast<char*>(&indexRecord), sizeof(IndexRecord));
            cout << "Employee deleted successfully.\n";
        }
    }
    else {
        cout << "Employee not found.\n";
    }

    dataFile.close();
    indexFile.close();
}

int main() {
    int choice;
    int empId;

    do {
        cout << "========== Employee Management System ==========\n";
        cout << "1. Add Employee\n";
        cout << "2. Display Employee\n";
        cout << "3. Delete Employee\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "======= Add Employee ========\n";
                addEmployee();
                break;
            case 2:
                cout << "======= Display Employee ========\n";
                cout << "Enter Employee ID: ";
                cin >> empId;
                displayEmployee(empId);
                break;
            case 3:
                cout << "======= Delete Employee ========\n";
                cout << "Enter Employee ID: ";
                cin >> empId;
                deleteEmployee(empId);
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }

        cout << endl;
    } while (choice != 4);

    return 0;
}




