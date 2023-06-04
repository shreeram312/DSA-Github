//Binary tree


#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
};

Node* createNode(int data) {
    Node* newNode = new Node();
    if (!newNode) {
        cout << "Memory error\n";
        return NULL;
    }
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node* insertNode(Node* root, int data) {
    if (root == NULL) {
        root = createNode(data);
        return root;
    }
    if (data < root->data)
        root->left = insertNode(root->left, data);
    else if (data > root->data)
        root->right = insertNode(root->right, data);
    return root;
}

Node* insertMultipleNodes() {
    Node* root = NULL;
    int n, data;
    cout << "Enter the number of nodes: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "Enter data for node " << i + 1 << ": ";
        cin >> data;
        root = insertNode(root, data);
    }
    return root;
}

int countLongestPath(Node* root) {
    if (root == NULL)
        return 0;
    int leftPath = countLongestPath(root->left);
    int rightPath = countLongestPath(root->right);
    return max(leftPath, rightPath) + 1;
}

int findMinValue(Node* root) {
    if (root == NULL) {
        cout << "Tree is empty\n";
        return -1;
    }
    Node* current = root;
    while (current->left != NULL)
        current = current->left;
    return current->data;
}

void swapChildren(Node* root) {
    if (root == NULL)
        return;
    swapChildren(root->left);
    swapChildren(root->right);
    swap(root->left, root->right);
}

bool searchNode(Node* root, int value) {
    if (root == NULL)
        return false;
    if (root->data == value)
        return true;
    if (value < root->data)
        return searchNode(root->left, value);
    else
        return searchNode(root->right, value);
}

void deleteTree(Node* root) {
    if (root == NULL)
        return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

void displayMenu() {
    cout << "\n************ MENU ************\n";
    cout << "1. Insert a new node\n";
    cout << "2. Find the number of nodes in the longest path from root\n";
    cout << "3. Find the minimum data value in the tree\n";
    cout << "4. Change the tree by swapping left and right pointers at every node\n";
    cout << "5. Search a value in the tree\n";
    cout << "6. Exit\n";
}

int main() {
    Node* root = NULL;

    // Insert nodes into the BST
    root = insertMultipleNodes();

    int choice;
    while (true) {
        displayMenu();
        cout << "Enter your choice (1-6): ";
        cin >> choice;

        switch (choice) {
            case 1: {
                // Insert new node
                int newData;
                cout << "Enter data for the new node: ";
                cin >> newData;
                root = insertNode(root, newData);
                break;
            }
            case 2: {
                // Find number of nodes in the longest path from root
                int longestPath = countLongestPath(root);
                cout << "Number of nodes in the longest path from root: " << longestPath << endl;
                break;
            }
            case 3: {
                // Minimum data value found in the tree
                int minValue = findMinValue(root);
                cout << "Minimum data value in the tree: " << minValue << endl;
                break;
            }
            case 4: {
                // Change the tree by swapping left and right pointers at every node
                swapChildren(root);
                cout << "Tree with left and right pointers swapped at every node.\n";
                break;
            }
            case 5: {
                // Search a value
                int searchValue;
                cout << "Enter a value to search in the tree: ";
                cin >> searchValue;
                if (searchNode(root, searchValue))
                    cout << "Value found in the tree.\n";
                else
                    cout << "Value not found in the tree.\n";
                break;
            }
            case 6: {
                // Delete the entire tree to free memory
                deleteTree(root);
                root = NULL;
                cout << "Exiting...\n";
                return 0;
            }
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}

