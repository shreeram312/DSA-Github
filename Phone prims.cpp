//prim


#include <iostream>
using namespace std;

class Tree {
    int branches[20][20], numVertices, numConnections, visited[20];

public:
    void input();
    void display();
    void minimum();
};

void Tree::input() {
    cout << "Enter the number of branches: ";
    cin >> numVertices;

    for (int i = 0; i < numVertices; i++) {
        visited[i] = 0;
        for (int j = 0; j < numVertices; j++) {
            branches[i][j] = 999;
        }
    }

    cout << "\nEnter the number of connections: ";
    cin >> numConnections;

    for (int i = 0; i < numConnections; i++) {
        int l, u, w;
        cout << "Enter the end branches of connection " << i + 1 << ": ";
        cin >> l >> u;
        cout << "Enter the phone company charges for this connection: ";
        cin >> w;
        branches[l - 1][u - 1] = branches[u - 1][l - 1] = w;
    }
}

void Tree::display() {
    cout << "\nAdjacency matrix:\n";
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            cout << branches[i][j] << "\t";
        }
        cout << endl;
    }
}

void Tree::minimum() {
    int p = 0, q = 0, total = 0, minCost;

    visited[0] = 1;
    for (int count = 0; count < (numVertices - 1); count++) {
        minCost = 999;

        for (int i = 0; i < numVertices; i++) {
            if (visited[i] == 1) {
                for (int j = 0; j < numVertices; j++) {
                    if (visited[j] != 1) {
                        if (minCost > branches[i][j]) {
                            minCost = branches[i][j];
                            p = i;
                            q = j;
                        }
                    }
                }
            }
        }

        visited[p] = 1;
        visited[q] = 1;
        total += minCost;

        cout << "Minimum cost connection: " << (p + 1) << " -> " << (q + 1) << " with charge: " << minCost << endl;
    }

    cout << "The minimum total cost of connections of all branches is: " << total << endl;
}

int main() {
    int choice;
    Tree t;

    do {
        cout << "\n==========PRIM'S ALGORITHM==========\n";
        cout << "1. Input\n";
        cout << "2. Display\n";
        cout << "3. Minimum\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "*******INPUT YOUR VALUES*******\n";
                t.input();
                break;
            case 2:
                cout << "*******DISPLAY THE CONTENTS********\n";
                t.display();
                break;
            case 3:
                cout << "*********MINIMUM************\n";
                t.minimum();
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}

