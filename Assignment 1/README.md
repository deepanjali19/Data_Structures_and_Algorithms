**Assignment Details:**

**Part 1: Implement a sorted linked list**

Implement a template for a sorted doubly linked list called SortedList along with iterators to access the list.

Nodes in this list will have a pointer not only to the next node but also a pointer to the previous node. The values of the data within the list must also remain sorted. Thus, the smallest item must be at the front of the list, the second smallest is in the second node and so on.

The data type of the data stored in this list (T) supports the following operator

•	==

•	!=

•	<

•	=

The SortedList class has the following member functions. Each function must meet the big-O runtime specified. Unless otherwise stated n refers to number of nodes within the linked list.:

``SortedList();``

•	constructor, creates empty SortedList

•	O(1)

``iterator begin();``

•	returns iterator to Node containing the first piece of data in the linked list

•	O(1)

``iterator end();``

•	returns iterator to the Node after the node containing the last piece of data of the linked list

•	O(1)

``const_iterator begin() const;``

•	returns const_iterator to to Node containing the first piece of data in the linked list

•	O(1)

``const_iterator end() const;``

•	returns const_iterator to the Node after the node containing the last piece of data of the linked list

•	O(1)

``iterator insert(const T& data);``

•	adds data to the linked list

•	returns iterator to newly added node

•	O(n)

``iterator erase(iterator it);``

•	removes the node referred to by it

•	returns iterator to node after the node removed

•	O(1)

``iterator erase(iterator first, iterator last);``

•	removes the nodes between the nodes referred to by iterator first to last. This includes the node referred to by first but NOT the node referred to by last.

•	returns iterator to last

•	O(n) where n is the number of nodes between first and last

``iterator search(const T& data);
const_iterator search(const T& data) const;``

•	returns iterator to the node containing data. If data is not found, returns end()

•	O(n)

``bool empty() const;``

•	function returns true if the list is empty, false otherwise

•	O(1)

``int size() const;``

•	function returns number of pieces of data stored in the list

•	O(1)

``~SortedList();
SortedList(const SortedList&);
SortedList& operator=(const SortedList&);
SortedList(SortedList&&);
SortedList& operator=(SortedList&&);``

•	Your sorted linked list must also implement destructor, copy constructor, assignment operator, move constructor, move operator.

•	runtime for destructor, copy constructor and assignment operator must not exceed O(n)

•	runtime for move constructor/operator must not exceed O(1)

**Iterator**
The idea of an iterator is to provide a means to traverse your class. In the STL, different classes like vectors or list all have iterators that help you iterate through your list. For the sorted list, you will also write an iterator class.

You will need two iterators. a const_iterator and an iterator which is derived from const_iterator. For both operators, the following public members/operators are needed. You are welcome to add any other private or protected members as you see fit:

``iterator();
const_iterator();``

constructors, returns iterators to nullptrs O(1)

``iterator operator++();
const_iterator operator++() const;
iterator operator++(int);
const_iterator operator++(int);``

•	prefix and postfix ++ operator

•	makes iterator point to the next node in the list.

•	return as appropriate for each operator

•	O(1)

``iterator operator--();
const_iterator operator--() const;
iterator operator--(int);
const_iterator operator--(int);``

•	prefix and postfix operator --

•	increments iterator so that it points to previous node in list

•	return as appropriate for each operator

•	O(1)

``operator==``

returns true if two iterators point at the same node, false otherwise

``operator !=``

•	returns true if two iterators point at different nodes, false otherwise

•	O(1)

``const T& operator*()const; (in both iterator and const_iterator)
T& operator*(); (only in iterator)``

•	dereferencing operator, returns the data in the node pointed to by iterator

•	O(1)

##Part 2: Recursion: GCD, Polynomial division and remainder (10 marks)

Part of this requires a working sorted list (part 1). You will need to complete part 1 before you can complete this All functions must be written recursively for this part of the assignment to be considered complete. You are allowed to use the required functions as wrappers to recursive functions but the code that actually finds to the solution MUST be recursive

``int GCD(int a, int b);``

•	function returns the greatest common denominator of a and b (the biggest number that will evenly divide both a and b)

•	In otherwords GCD is the biggest number where a%gcd == 0 and b%gcd == 0

Complete the Polynomial class by writing the / and % operators.

``Polynomial operator/(const Polynomial& p1, const Polynomial& p2);
Polynomial operator%(const Polynomial& p1, const Polynomial& p2);``

The polynomial class is a sorted linked list of Terms. Each term consists of a coefficent and exponent. The coefficient is a fraction. the exponent is an unsigned integer. Terms are ordered by the exponent. The higher the exponent, the closer to the front of the list it is. Thus, the node with the biggest exponent will be placed at the front of the linked list.

**Part 3: Analysis**

Perform an analysis of the Polynomial::solve(const Fraction& x) function. The n in this case is the value of the biggest exponent (which also determines the maximum length of the list as the number of nodes <= n+1)

The solve function is not as efficient as it can be. There is a more efficient way to write this function. rewrite solve so that it's run time O(n).
