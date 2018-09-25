template <class T>
class Queue{
	T* theQueue_;
	int capacity_;
	int used_;
	void grow(){
	}
public:
	Queue(){
	}
	void enqueue(const T& data){
	}
	void dequeue(){
	}
	T front() const{

	}
	bool isEmpty() const{
	}
	~Queue(){
		delete [] theQueue_;
	}	
};