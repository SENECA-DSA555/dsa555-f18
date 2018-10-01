template <class T>
class Stack{
	T* theStack_;
	int capacity_;
	int used_;
	void grow(){
		T* tmp=new T[capacity_+capacity_];
		for(int i=0;i<used_;i++){
			tmp[i]=theStack_[i];
		}
		capacity_=capacity_+capacity_;
		delete []theStack_;
		theStack_=tmp;
	}
public:
	Stack(int cap=13){
		capacity_=cap;
		theStack_=new T[capacity_];
		used_=0;
	}
	void push(const T& data){
		if(used_==capacity_){
			grow();
		}
		theStack_[used_++]=data;
	}
	void pop(){
		if(used_!=0){
			used_--;
		}
	}
	T top() const{
		T rc;
		if(used_!=0){
			rc=theStack_[used_-1];
		}
		return rc;
	}
	bool isEmpty() const{
		return used_==0;
	}
	~Stack(){
		delete [] theStack_;
	}	
};