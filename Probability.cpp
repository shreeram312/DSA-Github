//Probability


#include <iostream>
using namespace std;

// Structure to represent a node in the binary search tree
struct Node {
    int key;
    Node* left;
    Node* right;

    Node(int val) {
        key = val;
        left = nullptr;
        right = nullptr;
    }
};

// Function to construct an optimal binary search tree
Node* constructOBST(int keys[], double probabilities[], int start, int end) {
    // Base case: Empty range
    if (start > end)
        return nullptr;

    double minCost = 9999999999.0;
    int minIndex = -1;

    for (int i = start; i <= end; i++) {
        double cost = 0;
        for (int j = start; j <= end; j++) {
            if (j < i)
                cost += probabilities[j];
            else if (j > i)
                cost += probabilities[j];
            else
                cost += probabilities[j] + probabilities[i];
        }

        if (cost < minCost) {
            minCost = cost;
            minIndex = i;
        }
    }

    Node* root = new Node(keys[minIndex]);

    root->left = constructOBST(keys, probabilities, start, minIndex - 1);
    root->right = constructOBST(keys, probabilities, minIndex + 1, end);

    return root;
}

// Function to perform in-order traversal of the binary search tree
void inOrderTraversal(Node* root) {
    if (root == nullptr)
        return;

    inOrderTraversal(root->left);
    cout << root->key << " ";
    inOrderTraversal(root->right);
}

int main() {
    int n;
    cout << "Enter the number of keys: ";
    cin >> n;

    int* keys = new int[n];
    double* probabilities = new double[n];

    cout << "Enter the keys: ";
    for (int i = 0; i < n; i++) {
        cin >> keys[i];
    }

    cout << "Enter the probabilities: ";
    for (int i = 0; i < n; i++) {
        cin >> probabilities[i];
    }

    Node* root = constructOBST(keys, probabilities, 0, n - 1);

    cout << "In-order traversal of the constructed binary search tree: ";
    inOrderTraversal(root);
    cout << endl;

    delete[] keys;
    delete[] probabilities;

    return 0;
}

