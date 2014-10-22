#include "iostream"
#include <stack>
#include <queue>

using namespace std;

class Node {

	public:
		int value;
		Node *left;
		Node *right;

		Node(int value) {
			this->value = value;
			this->left = NULL;
			this->right = NULL;
		}

};

class Tree {
		
	Node *root;

	public:
		Tree() {
			root = NULL;
		}

		void insert(int value) {
		
			if(root == NULL) {
				root = new Node(value);
				return;
			}

			Node *p = root;

			while(true) {
				if(value <= p->value) {
					if(p->left != NULL)
						p = p->left;
					else {
						p->left = new Node(value);
						break;
					}
				}
				else {
					if(p->right != NULL)
						p = p->right;
					else {
						p->right = new Node(value);
						break;
					}
				}
			}
		}

		void deleteNode(int value) {
		
			Node *p = root;
			Node *parent = NULL;
			if(p == NULL)
				return;

			while (p != NULL && p->value != value) {
				parent = p;
				if(value < p->value)
					p = p->left;
				else
					p = p->right;
			}

			if(p == NULL)
				return;

			if(p->left == NULL && p->right == NULL) {
				if(parent == NULL)
					root = NULL;
				else if(parent->left == p)
					parent->left = NULL;
				else
					parent->right = NULL;

				delete(p);
				return;
			}

			if(p->left != NULL && p->right == NULL) {
				if(parent == NULL)
					root = p->left;
				else if(parent->left == p)
					parent->left = p->left;
				else
					parent->right = p->left;

				delete(p);
				return;
			}

			if(p->left == NULL && p->right != NULL) {
				if(parent == NULL)
					root = p->right;
				else if(parent->left == p)
					parent->left = p->right;
				else
					parent->right = p->right;

				delete(p);
				return;
			}

			else {
				Node *rp = p->right;
				Node *parent_rp = rp;

				while(rp->left != NULL) {
					parent_rp = rp;
					rp = rp->left;
				}

				if(rp == parent_rp) {
					if(parent == NULL)
						root = rp;
					else if(parent->left == p)
						parent->left = rp;
					else
						parent->right = rp;
					
					rp->left = p->left;
					delete(p);
					return;
				}

				parent_rp->left = rp->right;
				rp->left = p->left;
				rp->right = p->right;

				if(parent == NULL)
					root = rp;
				else if(parent->left == p)
					parent->left = rp;
				else 
					parent->right = rp;

				delete(p);
				return;
			}
		}

		Node* getRoot() {
			return root;
		}

		void inorderRecursive(Node *p) {
			
			if(p == NULL)
				return;

			inorderRecursive(p->left);
			cout<<p->value<<" ";
			inorderRecursive(p->right);
		}

		void postorderRecursive(Node *p) {
			
			if(p == NULL)
				return;

			postorderRecursive(p->left);
			postorderRecursive(p->right);
			cout<<p->value<<" ";	
		}

		void preorderRecursive(Node *p) {
			
			if(p == NULL)
				return;

			cout<<p->value<<" ";
			preorderRecursive(p->left);
			preorderRecursive(p->right);
		}

		void inorderIterative() {
		
			Node *p = root;
			if(p == NULL)
				return;

			stack<Node*> myStack;

			while(p != NULL) {
				
				while (p != NULL) {
					myStack.push(p);
					p = p->left;
				}

				if(!myStack.empty()) {
					cout<<myStack.top()->value<<" ";
					p = myStack.top();
					myStack.pop();
				}
				
				while(!myStack.empty() && p->right == NULL) {
					cout<<myStack.top()->value<<" ";
					p = myStack.top();
					myStack.pop();
				}

				p = p->right;
			}
		}

		void preorderIterative() {
			
			Node *p = root;
			if(p == NULL)
				return;

			stack<Node*> myStack;

			while(p != NULL) {
				
				while (p != NULL) {
					cout<<p->value<<" ";
					myStack.push(p);
					p = p->left;
				}

				if(!myStack.empty()) {
					p = myStack.top();
					myStack.pop();
				}
				
				while(!myStack.empty() && p->right == NULL) {
					p = myStack.top();
					myStack.pop();
				}

				p = p->right;
			}
		}

		void postorderIterative() {
			
			Node *p = root;
			if(p == NULL)
				return;

			stack<Node*> myStack;
			Node *lastVisited = NULL;

			while(p != NULL || !myStack.empty()) {
				
				if(p != NULL) {
					myStack.push(p);
					p = p->left;
				}
				else {
					Node *top = myStack.top();

					if(top->right != NULL && lastVisited != top->right) {
						p = top->right;
					}

					else {
						cout<<myStack.top()->value<<" ";
						lastVisited = myStack.top();
						myStack.pop();
					}
				}
			}
		}

		void printBreadthFirst() {

			Node *p = root;
			if(p == NULL)
				return;

			queue<Node*> myQueue;
			myQueue.push(p);

			while(!myQueue.empty()) {
				Node *temp = myQueue.front();
				cout<<temp->value<<" ";
				myQueue.pop();

				if(temp->left != NULL)
					myQueue.push(temp->left);

				if(temp->right != NULL)
					myQueue.push(temp->right);
			}
		}

		int getHeightDFS(Node *p) {
			
			if(p == NULL)
				return 0;

			if(p->left == NULL && p->right == NULL)
				return 1;

			return max(getHeightDFS(p->left),getHeightDFS(p->right)) + 1;
		}

		int getHeightBFS() {
			
			Node *p = root;
			if(p == NULL)
				return 0;

			int height = 0;
			queue<Node*> myQueue;
			Node *dummy = NULL;
			myQueue.push(p);
			myQueue.push(dummy);

			while(!myQueue.empty()) {
				Node *temp = myQueue.front();
				myQueue.pop();

				if(temp == NULL) {
					height++;

					if(myQueue.empty())
						break;
					else
						myQueue.push(temp);
				}

				if(temp != NULL && temp->left != NULL)
					myQueue.push(temp->left);

				if(temp != NULL && temp->right != NULL)
					myQueue.push(temp->right);
			}

			return height;
		}
};

int main(int argc, char **argv) {

	Tree *tree = new Tree();
	
	tree->insert(25);
	tree->insert(15);
	tree->insert(20);
	tree->insert(24);
	tree->insert(23);
	tree->insert(10);
	tree->insert(5);
	tree->insert(30);
	tree->insert(17);
	tree->insert(18);
	
	/*tree->inorderRecursive(tree->getRoot());
	cout<<endl;
	tree->inorderIterative();
	cout<<endl<<endl;

	tree->preorderRecursive(tree->getRoot());
	cout<<endl;
	tree->preorderIterative();
	cout<<endl<<endl;
	
	tree->postorderRecursive(tree->getRoot());
	cout<<endl;
	tree->postorderIterative();
	cout<<endl<<endl;*/

	//tree->printBreadthFirst(tree->getRoot());
	
	//cout<<tree->getHeightDFS(tree->getRoot());
	//cout<<tree->getHeightBFS();

	tree->deleteNode(25);
	tree->inorderRecursive(tree->getRoot());
	return 0;
}