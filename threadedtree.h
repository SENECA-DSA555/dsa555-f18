#include <iostream>
using namespace std;

template <class T>
class ThreadedTree{
	struct Node{
		Node(const T& data=T{},Node* left=nullptr, Node* right=nullptr){
		}
	};
	Node* root_;	
	void print(const Node* rt, int lvl)const{
		//This function won't be tested, but you may find it useful to implement this so 
		//that you can see what the tree looks like.  lvl will allow you to use dashes to 
		//better show shape of tree
	}

public:
	class const_iterator{
	protected:

	public:
		const_iterator(){
		}
		const_iterator operator++(int){
		}
		const_iterator operator--(int){
		}
		const_iterator operator++(){
		}
		const_iterator operator--(){
		}
		const T& operator*() const{
		}
		bool operator==(const const_iterator& rhs) const{

		}
		bool operator!=(const const_iterator& rhs) const{

		}
		friend class ThreadedTree;
	};
	class iterator:public const_iterator{
	public:
		iterator():const_iterator(){
		}
		const T& operator*() const{
		}
		T& operator*(){
		}		
		iterator operator++(int){
		}
		iterator operator--(int){
		}
		iterator operator++(){
		}
		iterator operator--(){
		}

		friend class ThreadedTree;
	};

	ThreadedTree(){
	}
	void insert(const T& data){
	}
	iterator find(const T& data){
	}
	const_iterator find(const T& data) const{

	}
	iterator begin(){
	}
	iterator end(){
	}
	const_iterator cbegin()const{
	}
	const_iterator cend() const{
	}
	void print() const{
		//this function won't be tested, but you may wish to implement this 
		//to help you debug
	}
	~ThreadedTree(){

	}
};
