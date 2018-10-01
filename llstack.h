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
		const_iterator top=theStack_.begin();
		return *(top);
	}
	bool isEmpty() const{
		return (cbegin()==cend())
	}	
};