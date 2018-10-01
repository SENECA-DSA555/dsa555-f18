#include "dlist.h"
template<typename T>
class Queue{
	DList<T> theQueue_;

public:
	Queue(){
	}
	void enqueue(const T& data){
		theQueue_.push_back(data);
	}
	void dequeue(){
		theQueue_.pop_front();
	}
	T front() const{
		T rc;
		if(!isEmpty()){
			rc=*(theQueue_.cbegin());
		}
		return rc;
	}
	bool isEmpty() const{
		return theQueue_.cbegin() == theQueue_.cend();
	}	
};