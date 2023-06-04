// Patient


#include <iostream>
using namespace std;

struct Patient {
    string name;
    int priority;
};

class PriorityQueue {
    private:
        static const int MAX_SIZE = 100;
        Patient arr[MAX_SIZE];
        int size;
        
    public:
        PriorityQueue() {
            size = 0;
        }
        
        bool isEmpty() {
            return size == 0;
        }
        
        bool isFull() {
            return size == MAX_SIZE;
        }
        
        void enqueue(string name, int priority) {
            if (isFull()) {
                cout << "Queue is full. Cannot enqueue more patients.\n";
                return;
            }
            
            int index = size;
            
            while (index > 0 && arr[index-1].priority < priority) {
                arr[index] = arr[index-1];
                index--;
            }
            
            Patient patient;
            patient.name = name;
            patient.priority = priority;
            arr[index] = patient;
            size++;
            
            cout << "Patient " << name << " with priority " << priority << " is added to the queue.\n";
        }
        
        void dequeue() {
            if (isEmpty()) {
                cout << "Queue is empty. No patients to dequeue.\n";
                return;
            }
            
            Patient patient = arr[size-1];
            size--;
            
            cout << "Patient " << patient.name << " with priority " << patient.priority << " is dequeued.\n";
        }
        
        void display() {
            if (isEmpty()) {
                cout << "Queue is empty. No patients to display.\n";
                return;
            }
            
            cout << "Patients in the priority queue:\n";
            for (int i = 0; i < size; i++) {
                cout << "Patient " << arr[i].name << " with priority " << arr[i].priority << endl;
            }
        }
};

int main() {
    PriorityQueue priorityQueue;
    int choice, priority;
    string name;
    
    while (true) {
        cout << "\nHospital Priority Queue Menu:\n";
        cout << "1. Enqueue Patient\n";
        cout << "2. Dequeue Patient\n";
        cout << "3. Display Patients\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter patient name: ";
                cin >> name;
                cout << "Enter patient priority (1 for Serious, 2 for Non-serious, 3 for General Checkup): ";
                cin >> priority;
                priorityQueue.enqueue(name, priority);
                break;
            case 2:
                priorityQueue.dequeue();
                break;
            case 3:
                priorityQueue.display();
                break;
            case 4:
                exit(0);
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}

