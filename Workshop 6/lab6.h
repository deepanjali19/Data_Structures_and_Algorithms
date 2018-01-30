#include "arrayqueue.h"
#include<iostream>

using namespace std;

template <typename T>
class BST {
	struct Node {
		T data_;
		Node* left_;
		Node* right_;
		Node(const T& data, Node* left = nullptr, Node* right = nullptr) {
			data_ = data;
			left_ = left;
			right_ = right;
		}
	};
	Node* root_;

	//this function inserts data into the tree with root
	//subRoot

	void insert(const T& data, Node*& subRoot) {
		if (subRoot == nullptr) {
			subRoot = new Node(data);
		}
		else {
			if (data < subRoot->data_) {
				insert(data, subRoot->left_);
			}
			else {
				insert(data, subRoot->right_);
			}
		}
	}

	//this function will receive a pointer to a node
	//and detach and remove the smallest node in this subtree

	Node* detachInorderSuccessor(Node*& subRoot) {
		if(subRoot->left_ == nullptr){
			Node* temp = subRoot;
			subRoot = subRoot->right_;
			return temp;
		}
		else{
			return detachInorderSuccessor(subRoot->left_);
		}
	}

	void remove(const T& data, Node*& subRoot) {
		if (subRoot != nullptr) {
			if (data == subRoot->data_) {
				Node* rm = subRoot;   
	//make a temp to subRoot so I 					  
	//don't lose it by accident								  
	//subroot is a leaf node
				if (subRoot->left_ == nullptr && subRoot->right_ == nullptr) {
					//null out pointer from parent
					subRoot = nullptr;
				}
				else if (subRoot->left_ != nullptr && subRoot->right_ == nullptr) {
					//one child on left
					subRoot = subRoot->left_;
				}
				else if (subRoot->right_ != nullptr && subRoot->left_ == nullptr) {
					//one child on right
					subRoot = subRoot->right_;
				}
				else {
					Node* inorderSuccesor = detachInorderSuccessor(subRoot->right_);
					
					inorderSuccesor->left_ = subRoot->left_;
					
					inorderSuccesor->right_ = subRoot->right_;
					subRoot = inorderSuccesor;
				}


				delete rm;
			}
			else if (data < subRoot->data_) {
				remove(data, subRoot->left_);
			}
			else {
				remove(data, subRoot->right_);
			}
		}

	}

	void printPreOrder(const Node* subRoot) const {
		if (subRoot != nullptr) {
			cout << subRoot->data_ << " ";
			
		printPreOrder(subRoot->left_);
			
		printPreOrder(subRoot->right_);
		}
	}

	void printInOrder(const Node* subRoot) const {
		if (subRoot != nullptr) {
			printInOrder(subRoot->left_);
			cout << subRoot->data_ << " ";
			
		printInOrder(subRoot->right_);
		}
	}

	void destroy(Node* subRoot) {
		if (subRoot != nullptr) {
			destroy(subRoot->left_);
			destroy(subRoot->right_);
			delete subRoot;
		}
	}

	// function to copy all nodes of the tree

	Node* copyTree(Node*& curr, Node* copy){

		if(copy != nullptr){
			curr = new Node(copy->data_);
			copyTree(curr->right_,copy->right_);
			copyTree(curr->left_,copy->left_);
			return curr;
		}
		else{
			return nullptr;
		}
	}

public:
	BST() {
		root_ = nullptr;
	}
	void insert(const T& data) {
		insert(data, root_);
	}
	void iterativeInsert(const T& data) {
		if (root_ == nullptr) {
			root_ = new Node(data);
		}
		else {
			Node* curr = root_;
			bool inserted = false;
			while (!inserted) {
				if (data < curr->data_) {
					if (curr->left_ == nullptr) {
						curr->left_ = new Node(data);
						inserted = true;
					}
					else {
						curr = curr->left_;
					}
				}
				else {
					if (curr->right_ == nullptr) {
						curr->right_ = new Node(data);
						inserted = true;
					}
					else {
						curr = curr->right_;
					}
				}
			}
		}
	}

	void remove(const T& data) {
		remove(data, root_);
	}

	//preOrder is depth first

	void printPreOrder() const {
		printPreOrder(root_);
	}

	//inOrder is depth first

	void printInOrder() const {
		printInOrder(root_);
	}

	//postOrder is depth first

	void printPostOrder() const {

	}


	//breadthFirst

	void printBreadthFirst() const {
		Queue<Node*> q;
		q.enqueue(root_);
		while (!q.empty()) {
			Node* curr = q.front();
			q.dequeue();
			if (curr != nullptr) {
				cout << curr->data << " " << endl;
				q.enqueue(curr->left_);
				q.enqueue(curr->right_);
			}
		}
	}

	//depth

	int depth(const T& data) {

		Node * curr = root_;
		int finalDepth = -1;
		int tempValue = 0;

		while (curr !=nullptr) {

			if (data == curr->data_) {
				finalDepth = tempValue;
				return finalDepth;
			}
			else if (data < curr->data_) {
				curr = curr->left_;
			}
			else if (data > curr->data_) {
				curr = curr->right_;
			}
					
			tempValue++;	
		}
		return finalDepth;
	}


	BST(const BST& rhs){
		root_ = copyTree(root_,rhs.root_);
	}
	
	~BST() {
		destroy(root_);
	}
};
