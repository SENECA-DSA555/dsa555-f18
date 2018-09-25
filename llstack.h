#include "dlist.h"
template <class T>
class Stack{
	DList<T> theStack_;

public:
	Stack(){}
	void push(const T& data){
		theStack_.push_front(data);
	}
	void pop(){
		theStack_.pop_front();
	}
	T top() const{
		const_iterator top=theStack_.cbegin();
		return *top;
	}
	bool isEmpty(){
		return (begin()==end())
	}	
};