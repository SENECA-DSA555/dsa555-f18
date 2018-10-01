template <class T>
class Queue{
	T* theQueue_;
	int capacity_;
	int used_;
	int front_;  //index of front of queue
	int back_;   //index of thing after the back of queue
	void grow(){
		T* tmp=new T[capacity_+capacity_];
		int j=front_;
		for(int i=0;i<used_;i++){
			tmp[i]=theQueue_[j++];
			if(j==capacity_){
				j=0;
			}
		}
		front_=0;
		back_=used_;
		capacity_=capacity_+capacity_;
		delete []theQueue_;
		theQueue_=tmp;

	}
public:
	Queue(int cap=13){
		capacity_=cap;
		theQueue_=new T[capacity_];
		used_=0;
		front_=0;
		back_=0;
	}
	void enqueue(const T& data){
		if(used_==capacity_){
			grow();
		}
/*		theQueue_[back_++]=data;
		if(back_==capacity_){
			back_=0;
		}*/
		theQueue_[back_]=data;
		back_=(back_+1)%capacity_;
		used_++;
	}
	void dequeue(){
		if(used_!=0){
			front_++;
			if(front_==capacity_){
				front_=0;
			}
			used_--;
		}
	}
	T front() const{

	}
	bool isEmpty() const{
	}
	~Queue(){
		delete [] theQueue_;
	}	
};