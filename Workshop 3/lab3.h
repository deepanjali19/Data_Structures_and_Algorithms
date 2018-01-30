#include <iostream>

template <typename T>
class SList{
	struct Node{
		T data_;
		Node* next_;
		Node(const T& data=T{},Node* next=nullptr){
			data_=data;
			next_=next;
		}
	};
	Node* front_;
	Node* back_;
public:
	SList(){
		front_=nullptr;
		back_=nullptr;
	}
	void push_front(const T& data);
	void push_back(const T& data);
	void pop_front();
	void pop_back();
	void print() const;
	~SList();
};

template <typename T>
void SList<T>::push_front(const T& data){
	Node* curr = new Node(data,front_);
	if(front_==NULL){
		back_=curr;
	}
	front_=curr;
}
template <typename T>
void SList<T>::push_back(const T& data){
	Node* curr = new Node(data);
	if(front_==NULL){   
                front_=curr;
		back_=curr;   
        }
	else{
        	back_->next_=curr;
		back_=curr;
	}
}
template <typename T>
void SList<T>::pop_front(){
	if(front_!=NULL){
		Node* curr = front_;
		if(front_!=back_){
			front_=front_->next_;
		}
		else{
			front_=NULL;
			back_=NULL;
		}
	delete curr;
	}
}
template <typename T>
void SList<T>::pop_back(){
	if(front_!=NULL){
		if(front_ !=back_){   
                	Node* curr = front_;
			while(curr->next_!=back_){
                		curr=curr->next_;
			}  
			curr->next_=NULL;
       			delete back_;
			back_=curr;
		}
        	else{
			delete back_;
                	front_=NULL;
                	back_=NULL;
        	}
	}
}
template <typename T>
void SList<T>::print() const{
	Node* curr=front_;
	while(curr){
		std::cout << curr->data_ << " ";
		curr=curr->next_;
	}
	std::cout << std::endl;
}
template <typename T>
SList<T>::~SList(){
	Node* curr=front_;
	while(curr){
		Node* rm=curr;
		curr=curr->next_;
		delete rm;
	}
}

template <typename T>
class Sentinel{
	struct Node{
		T data_;
		Node* next_;
		Node* prev_;
		Node(const T& data=T{},Node* next=nullptr, Node* prev=nullptr){
			data_=data;
			next_=next;
			prev_=prev;
		}
	};
	Node* front_;
	Node* back_;
public:
	Sentinel(){
		front_=new Node();
		back_=new Node();
		front_->next_=back_;
		back_->prev_=front_;
	}
	void push_front(const T& data);
	void push_back(const T& data);
	void pop_front();
	void pop_back();
	void print() const;
	void reversePrint() const;
	~Sentinel();
};


template <typename T>
void Sentinel<T>::push_front(const T& data){
	Node* curr = new Node(data,front_->next_,front_);
	front_->next_->prev_=curr;	
	front_->next_ = curr;
}
template <typename T>
void Sentinel<T>::push_back(const T& data){
	Node* curr = new Node(data,back_,back_->prev_);
	back_->prev_->next_=curr;
	back_->prev_=curr;
}
template <typename T>
void Sentinel<T>::pop_front(){
	if(front_->next_ != back_){	
		Node* curr=front_->next_;
		front_->next_=curr->next_;
		curr->next_->prev_=front_;
		delete curr;
	}
}
template <typename T>
void Sentinel<T>::pop_back(){
	if(back_->prev_ != front_){
		Node* curr=back_->prev_;
		back_->prev_=curr->prev_;
		curr->prev_->next_=back_;
		delete curr;
	}
}
template <typename T>
void Sentinel<T>::print() const{
	Node* curr=front_->next_;
	while(curr!=back_){
		std::cout << curr->data_ << " ";
		curr=curr->next_;
	}
	std::cout << std::endl;
}
template <typename T>
void Sentinel<T>::reversePrint() const{
	Node* curr=back_->prev_;
	while(curr!=front_){
		std::cout << curr->data_ << " ";
		curr=curr->prev_;
	}
	std::cout << std::endl;
}
template <typename T>
Sentinel<T>::~Sentinel(){
	Node* curr=front_;
	while(curr){
		Node* rm=curr;
		curr=curr->next_;
		delete rm;
	}
}
