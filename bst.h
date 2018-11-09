#include <iostream>

template <typename T>
class BST{
	struct Node{
		T data_;
		Node* left_;
		Node* right_;
		Node(const T& data,Node* left=nullptr, Node* right=nullptr){
			data_=data;
			left_=left;
			right_=right;
		}
	};
	Node* root_;
	void insert(const T& data,Node*& subtreeroot){
		if(subtreeroot==nullptr){
			subtreeroot=new Node(data);
		}
		else{
			if(data < subtreeroot->data_){
				insert(data,subtreeroot->left_);
			}
			else{
				insert(data,subtreeroot->right_);
			}
		}

	}
	void printPreOrder(const Node* subtreeroot,int depth) const{
		if(subtreeroot){

			for(int i=0;i<depth;i++){
				std::cout<<"---" ;
			}
			std::cout << subtreeroot->data_ << std::endl;
			printPreOrder(subtreeroot->left_,depth+1);
			printPreOrder(subtreeroot->right_,depth+1);
		}
	}

public:
	BST(){
		root_=nullptr;
	}
	void insertRecursive(const T& data){
		insert(data, root_);
	}
	void insertIterative(const T& data){
		if(root_==nullptr){
			root_=new Node(data);
		}
		else{
			Node* curr=root_;
			while(curr!=nullptr){
				if(data < curr->data_){
					//go left
					if(curr->left_!=nullptr){
						curr=curr->left_;
					}
					else{
						curr->left_=new Node(data);
						curr=nullptr;
					}
				}
				else{
					if(curr->right_!= nullptr){
						curr=curr->right_;
					}
					else{
						curr->right_=new Node(data);
						curr=nullptr;
					}								
				}
			}
		}

	}
	void printPreOrder() const{
		printPreOrder(root_,0);
	}
};





