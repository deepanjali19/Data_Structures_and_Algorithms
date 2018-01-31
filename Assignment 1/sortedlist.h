	// sortedlist.h

#include<utility>
#include<iostream>

	// class SortedList consist of front_ and back_ nodes as Sentinals
	// class holds various nodes and node functions in a list

template <typename T>
class SortedList {

	// Node structure consist of data and two pointers which points to next and previous nodes of each node

	struct Node {
		T data_;
		Node* next_;
		Node* prev_;

		Node(const T& data = T{}, Node* nx = nullptr, Node* pr = nullptr) {
			data_ = data;
			next_ = nx;
			prev_ = pr;
		}
	};

	// front and back Node pointers used as sentinels

	Node* front_;
	Node* back_;

	public:

	// the variable keeps track of list size

	int size_;

	// const_iterator class is used to traverse through sorted list without changing current values
	// class consists of functions such as prefix, postfix operators, deferencing operator, etc.

	class const_iterator {

		friend class SortedList;
	
		protected:

		Node* curr;

		const_iterator(Node* n) {
			curr = n;
		}
		
		public:

		const_iterator() {
			curr = nullptr;
		}
		
		const_iterator operator++() {
			curr = curr->next_;
			return *this;
		}
		
		const_iterator operator++(int) {
			const_iterator old = *this;
			curr = curr->next_;
			return old;
		}
		
		const_iterator operator--() {
			curr = curr->prev_;
			return *this;
		}
		
		const_iterator operator--(int) {
			const_iterator old = *this;
			curr = curr->prev_;
			return old;
		}
		
		bool operator==(const_iterator rhs) {
			return curr == rhs.curr;
		}
		
		bool operator!=(const_iterator rhs) {
			return curr != rhs.curr;
		}

		const T& operator*()const {
			return curr->data_;
		}
	};

	// iterator class is also used to traverse through sorted list which changes current values unlike const_iterator
        // class also consists of functions such as prefix, postfix operators, deferencing operator, etc.

	class iterator :public const_iterator {

		friend class SortedList;

		protected:

		iterator(Node* n) {
			this->curr = n;
		}

		public:

		iterator() {
			this->curr = nullptr;
		}

		iterator operator++() {
			this->curr = this->curr->next_;
			return *this;
		}

		iterator operator++(int) {
			iterator old = *this;
			this->curr = this->curr->next_;
			return old;
		}

		iterator operator--() {
			this->curr = this->curr->prev_;
			return *this;
		}
		iterator operator--(int) {
			iterator old = *this;
			this->curr = this->curr->prev_;
			return old;
		}

		T& operator*() {
			return this->curr->data_;
		}

		const T& operator*()const {
			return this->curr->data_;
		}
	};

	SortedList();

	~SortedList();

	SortedList(const SortedList& rhs);

	SortedList& operator=(const SortedList& rhs);

	SortedList(SortedList&& rhs);

	SortedList& operator=(SortedList&& rhs);

	// begin() and end() functions to point to begin and end of the sorted list using iterators
 
	iterator begin() {
		return iterator(front_->next_);
	}

	iterator end() {
		return iterator(back_);
	}

	const_iterator begin() const {
		return const_iterator(front_->next_);
	}

	const_iterator end() const {
		return const_iterator(back_);
	}

	iterator insert(const T& data);

	iterator search(const T& data);

	const_iterator search(const T& data) const;

	iterator erase(iterator it);

	iterator erase(iterator first, iterator last);

	bool empty() const;

	int size() const;
};

	// default constructor for SortedList which set the Sentinals for the list

template <typename T>
SortedList<T>::SortedList() {
	front_ = new Node();
	back_ = new Node();
	front_->next_ = back_;
	back_->prev_ = front_;
	size_=0;
}

	//Sortedlist destructor deletes the existing list, deletes and deallocates the memory and sets list size to zero

template <typename T>
SortedList<T>::~SortedList() {
	Node* curr = front_->next_;
	while (curr) {
		Node* rm = curr;
		curr = curr->next_;
		delete rm;
	}
	size_ = 0;
}

	// Copy constructor

template <typename T>
SortedList<T>::SortedList(const SortedList& rhs) {
	front_ = new Node();
	back_ = new Node();
	front_->next_ = back_;
	back_->prev_ = front_;
	size_ = 0;
	*this = rhs;
}

	// Copy assignment operator with deep copy for sorted list
	// delete the existing values in list, assign new nodes and deep copy values of argument to the list
	
template <typename T>
SortedList<T>& SortedList<T>::operator=(const SortedList& rhs) {
	if (this != &rhs) {
		while (!empty()) {
			erase(begin());
		}
		delete front_;
		size_ = 0;
		front_ = nullptr;
		front_ = new Node();
		back_ = new Node();
		front_->next_ = back_;
		back_->prev_ = front_;
	
		for (auto it = rhs.begin(); it != rhs.end();it++) {
			Node* curr = new Node(*it, back_,back_->prev_);
			back_->prev_->next_ = curr;
			back_->prev_ = curr;
			size_++;
		}
	}
	return *this;
}
	
	// Move constructor

template <typename T>
SortedList<T>::SortedList(SortedList&& rhs) {
	front_ = new Node();
	back_ = new Node();
	front_->next_ = back_;
	back_->prev_ = front_;
	size_ = 0;
	*this = std::move(rhs);
}

	// Move assignment operator
	// Moves the values of rhs to the list by deleting existing values

template <typename T>
SortedList<T>& SortedList<T>::operator=(SortedList&& rhs) {
	if (this != &rhs) {
		Node* temp;
		temp = front_;
		front_ = rhs.front_;
		rhs.front_ = temp;

		temp = back_;       
                back_ = rhs.back_;
                rhs.back_ = temp;
	}
	return *this;
}

	// insert function receives new data to add in the list in sorted manner
	// it finds the data smaller than data to add data after it
	// after finding position to be added, it pushes back the data 
	// the list is accessed and traversed using an iterator it
	
template <typename T>
typename SortedList<T>::iterator SortedList<T>::insert(const T& data) {

	Node* curr_ = new Node(data);
	iterator it = begin();

	while ((it != end()) && ((*it)<curr_->data_)) {
		it++;
	}
	
	Node* c = it.curr;
	curr_->next_ = c;
	curr_->prev_ = c->prev_;
	c->prev_->next_ = curr_;
	c->prev_ = curr_;
	size_++;

	return iterator(curr_);
}

	// search finds the data provided in argument in the sorted list
	// it uses an iterator it to go through the list and the returns the iterator pointing to data
	// if data is not found, it returns to end of list

template <typename T>
typename SortedList<T>::iterator SortedList<T>::search(const T& data) {

	auto it = begin();
	T d = data;

	while (it != end()) {
		if (d == *it) {
			return iterator(it.curr);
		}
		it++;
	}
	return end();
}

	// this search functions same as search above with only difference of returning a const_iterator

template <typename T>
typename SortedList<T>::const_iterator SortedList<T>::search(const T& data) const {
	const_iterator it = begin();

	while (it != end()) {
		if (data == *it) {
			return const_iterator(it.curr);
		}
		it++;
	}

	return end();
}
	// erase receives an iterator and deletes the node pointed by that iterator
	// after deleting the node it points the next and previous pointers of other two nodes surrounding deleted node
	// the functions returns an iterator pointing to node after deleted node

template <typename T>
typename SortedList<T>::iterator SortedList<T>::erase(iterator it) {

	Node* cc = it.curr;
	iterator r(cc->next_);
	
	cc->prev_->next_ = cc->next_;
	cc->next_->prev_ = cc->prev_;
	delete cc;
	cc = nullptr;
	size_--;

	return r;
}

	// this erase function receives two iterator and deletes nodes between these iterators
	// it deletes nodes from first iterator to one iterator before the last iterator provided
	// after deleting the nodes it returns an iterator pointing to the last iterator of deleted cluster

template <typename T>
typename SortedList<T>::iterator SortedList<T>::erase(iterator first, iterator last) {
	for (auto it = first; it != last;)
	{
		it = erase(it);
		size_--;
	}

	return last;
}

	// empty functons retruns true if list has no nodes,i.e., is empty otherwise returns false 

template <typename T>
bool SortedList<T>::empty() const {
	if (front_->next_ == back_)
		return true;
	else
		return false;
}

	// size function returns the size of the sorted list,i.e., number of nodes except Sentinals

template <typename T>
int SortedList<T>::size() const {

	return size_;
}
