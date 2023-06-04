#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

struct node {
	char data;
	node* left, * right;
};

void add(node** p, char*& a)
{
	if (*a == '\0')
		return;

	while (1) {
		if (*p == nullptr) {
			node* nn = new node;
			nn->data = *a;
			nn->left = nullptr;
			nn->right = nullptr;
			*p = nn;
		}
		else {
			if (*a >= 'a' && *a <= 'z')
				return;

			add(&(*p)->left, ++a);
			add(&(*p)->right, ++a);
			return;
		}
	}
}

void inr(node* p)
{
	if (p == nullptr)
		return;
	else {
		inr(p->left);
		cout << p->data << " ";
		inr(p->right);
	}
}

void postr(node* p)
{
	if (p == nullptr)
		return;
	else {
		postr(p->left);
		postr(p->right);
		cout << p->data << " ";
	}
}

int main()
{
	node* s = nullptr;
	char a[] = "+--a*bc/def";
	char* ptr = a;
	add(&s, ptr);
	cout << "The Infix expression is:\n ";
	inr(s);
	cout << "\n";
	cout << "The Postfix expression is:\n ";
	postr(s);
	return 0;
}

