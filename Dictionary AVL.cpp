//Dictionary AVL


#include <iostream>
#include <string>
using namespace std;

struct Node {
    string keyword;
    string meaning;
    Node* left;
    Node* right;
    int height;
};

int getHeight(Node* node) {
    if (node == nullptr)
        return 0;
    return node->height;
}

int getBalance(Node* node) {
    if (node == nullptr)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

Node* insert(Node* root, string keyword, string meaning) {
    if (root == nullptr) {
        Node* newNode = new Node;
        newNode->keyword = keyword;
        newNode->meaning = meaning;
        newNode->left = nullptr;
        newNode->right = nullptr;
        newNode->height = 1;
        return newNode;
    }

    if (keyword < root->keyword)
        root->left = insert(root->left, keyword, meaning);
    else if (keyword > root->keyword)
        root->right = insert(root->right, keyword, meaning);
    else {
        cout << "Keyword already exists in the dictionary.\n";
        return root;
    }

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    int balance = getBalance(root);

    if (balance > 1 && keyword < root->left->keyword)
        return rotateRight(root);

    if (balance < -1 && keyword > root->right->keyword)
        return rotateLeft(root);

    if (balance > 1 && keyword > root->left->keyword) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    if (balance < -1 && keyword < root->right->keyword) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

Node* minValueNode(Node* node) {
    Node* current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

Node* deleteNode(Node* root, string keyword) {
    if (root == nullptr) {
        cout << "Keyword not found in the dictionary.\n";
        return root;
    }

    if (keyword < root->keyword)
        root->left = deleteNode(root->left, keyword);
    else if (keyword > root->keyword)
        root->right = deleteNode(root->right, keyword);
    else {
        if (root->left == nullptr || root->right == nullptr) {
            Node* temp = root->left ? root->left : root->right;
            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } else
                *root = *temp;
            delete temp;
        } else {
            Node* temp = minValueNode(root->right);
            root->keyword = temp->keyword;
            root->meaning = temp->meaning;
            root->right = deleteNode(root->right, temp->keyword);
        }
    }

    if (root == nullptr)
        return root;

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rotateRight(root);

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return rotateLeft(root);

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

void displayAscending(Node* root) {
    if (root != nullptr) {
        displayAscending(root->left);
        cout << root->keyword << " - " << root->meaning << endl;
        displayAscending(root->right);
    }
}

void displayDescending(Node* root) {
    if (root != nullptr) {
        displayDescending(root->right);
        cout << root->keyword << " - " << root->meaning << endl;
        displayDescending(root->left);
    }
}

Node* search(Node* root, string keyword, int& comparisons) {
    if (root == nullptr || root->keyword == keyword) {
        comparisons++;
        return root;
    }

    comparisons++;
    if (keyword < root->keyword)
        return search(root->left, keyword, comparisons);
    return search(root->right, keyword, comparisons);
}

int main() {
    Node* root = nullptr;
    int choice, comparisons;
    string keyword, meaning;

    while (true) {
        cout << "\nDictionary Menu:\n";
        cout << "1. Add Keyword\n";
        cout << "2. Delete Keyword\n";
        cout << "3. Update Meaning\n";
        cout << "4. Display Dictionary in Ascending Order\n";
        cout << "5. Display Dictionary in Descending Order\n";
        cout << "6. Find Maximum Comparisons for a Keyword\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter keyword: ";
                cin >> keyword;
                cout << "Enter meaning: ";
                cin >> meaning;
                root = insert(root, keyword, meaning);
                break;
            case 2:
                cout << "Enter keyword to delete: ";
                cin >> keyword;
                root = deleteNode(root, keyword);
                break;
            case 3:
                cout << "Enter keyword to update: ";
                cin >> keyword;
                cout << "Enter new meaning: ";
                cin >> meaning;
                root = deleteNode(root, keyword);
                root = insert(root, keyword, meaning);
                break;
            case 4:
                cout << "Dictionary in Ascending Order:\n";
                displayAscending(root);
                break;
            case 5:
                cout << "Dictionary in Descending Order:\n";
                displayDescending(root);
                break;
            case 6:
                cout << "Enter keyword to find maximum comparisons: ";
                cin >> keyword;
                comparisons = 0;
                search(root, keyword, comparisons);
                cout << "Maximum comparisons required for keyword '" << keyword << "': " << comparisons << endl;
                break;
            case 7:
                exit(0);
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}

