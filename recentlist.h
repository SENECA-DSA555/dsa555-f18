
template <typename T>

class RecentList{
	struct Node{

		Node(const T& data=T{},Node* nx=nullptr,Node* pr=nullptr){
			
		}
	};

public:
	class const_iterator{
	public:
		const_iterator(){}
		const_iterator operator++(){}
		const_iterator operator++(int){}
		const_iterator operator--(){}
		const_iterator operator--(int){}
		bool operator==(const_iterator rhs){}
		bool operator!=(const_iterator rhs){}
		const T& operator*()const{}
	};
	class iterator:public const_iterator{
	public:
		iterator();
		iterator operator++(){}
		iterator operator++(int){}
		iterator operator--(){}
		iterator operator--(int){}
		T& operator*(){}
		const T& operator*()const{}
	};
	RecentList();
	~RecentList();
	RecentList(const RecentList& rhs);
	RecentList& operator=(const RecentList& rhs);
	RecentList(RecentList&& rhs);
	RecentList& operator=(RecentList&& rhs);
	iterator begin();
	iterator end();
	const_iterator cbegin() const;
	const_iterator cend() const;
	void insert(const T& data);
	iterator search(const T& data);
	iterator erase(iterator it);
	iterator erase(iterator first, iterator last);
	bool empty() const;
	int size() const;
};

template <typename T>
RecentList<T>::RecentList(){

}
template <typename T>
RecentList<T>::~RecentList(){

}
template <typename T>
RecentList<T>::RecentList(const RecentList& rhs){

}
template <typename T>
RecentList<T>& RecentList<T>::operator=(const RecentList& rhs){

}
template <typename T>
RecentList<T>::RecentList(RecentList&& rhs){

}

template <typename T>
RecentList<T>& RecentList<T>::operator=(RecentList&& rhs){

}


template <typename T>
void RecentList<T>::insert(const T& data){

}

template <typename T>
typename RecentList<T>::iterator RecentList<T>::search(const T& data){

}

template <typename T>
typename RecentList<T>::const_iterator RecentList<T>::search(const T& data) const{

}

template <typename T>
typename RecentList<T>::iterator RecentList<T>::erase(iterator it){

}

template <typename T>
typename RecentList<T>::iterator RecentList<T>::erase(iterator first, iterator last){

}
template <typename T>
bool RecentList<T>::empty() const{

}
template <typename T>
int RecentList<T>::size() const{

}
