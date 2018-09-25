template <class T>
class Stack{
	T* theStack_;
	int capacity_;
	int used_;
	void grow(){
	}
public:
	Stack(){
	}
	void push(const T& data){
	}
	void pop(){
	}
	T top() const{
	}
	bool isEmpty() const{
	}
	~Stack(){
		delete [] theStack_;
	}	
};