/*************************************************************/
/*    V 1.1:                                                 */
/*      - added prototypes for numRecords() and isEmpty()    */
/*      - coded isEmpty() and numRecords() in SimpleTable    */
/*      - created empty functions for isEmpty() and          */
/*        numRecords() in LPTable                            */
/*************************************************************/
/*							     */
/*    PART B                                                 */
/*    Changes made to the following functions:               */
/*							     */
/*	int search(const string& key);			     */
/*	void sort();			     		     */
/*	void grow();					     */
/*	SimpleTable(..&other);		                     */
/*	virtual bool update(const.., const..);		     */
/*	virtual bool remove(const..);			     */
/*	virtual const SimpleTable& operator=(..&other);	     */
/*	virtual ~SimpleTable();				     */
/*                                                           */   
/*************************************************************/


#include <string>
#include <utility>
#include <functional>

using namespace std;

template <class TYPE>
class Table {
public:
	Table() {}
	virtual bool update(const string& key, const TYPE& value) = 0;
	virtual bool remove(const string& key) = 0;
	virtual bool find(const string& key, TYPE& value) = 0;
	virtual int numRecords() const = 0;
	virtual bool isEmpty() const = 0;
	virtual ~Table() {}
};

template <class TYPE>
class SimpleTable :public Table<TYPE> {

	struct Record {
		TYPE data_;
		string key_;
		Record(const string& key, const TYPE& data) {
			key_ = key;
			data_ = data;
		}

	};

	Record** records_;   //the table
	int max_;           //capacity of the array
	int size_;          //current number of records held
	int search(const string& key);
	void grow();
public:
	SimpleTable(int maxExpected);
	SimpleTable(const SimpleTable& other);
	SimpleTable(SimpleTable&& other);
	virtual bool update(const string& key, const TYPE& value);
	virtual bool remove(const string& key);
	virtual bool find(const string& key, TYPE& value);
	virtual const SimpleTable& operator=(const SimpleTable& other);
	virtual const SimpleTable& operator=(SimpleTable&& other);
	virtual ~SimpleTable();
	virtual bool isEmpty() const { return size_ == 0; }
	virtual int numRecords() const { return size_; }
};


//returns index of where key is found.
template <class TYPE>
int SimpleTable<TYPE>::search(const string& key) {
	int rc = -1;
	int low = 0;
  	int high = numRecords() - 1;
	int mid;

//binary search 
	while(low <= high && rc == -1){
    		mid = (low + high) / 2;
    		if(records_[mid]->key_ > key)
      			high = mid - 1;
    		else if(records_[mid]->key_ < key)
      			low = mid + 1;
    		else
      			rc = mid;
	}
	return rc;
}

//grow the array by one element
template <class TYPE>
void SimpleTable<TYPE>::grow() {
	Record** newArray = new Record*[max_ * 2];
	max_ = max_ * 2;
	for (int i = 0; i < numRecords(); i++) {
 		newArray[i] = records_[i];
	}
	delete[] records_;
	records_ = newArray;
}

template <class TYPE>
SimpleTable<TYPE>::SimpleTable(int maxExpected) : Table<TYPE>() {
	records_ = new Record*[maxExpected];
	max_ = maxExpected;
	size_ = 0;
}

template <class TYPE>
SimpleTable<TYPE>::SimpleTable(const SimpleTable<TYPE>& other) {
	max_ = other.max_;
	size_ = other.size_;
	records_ = new Record*[other.max_];
	for (int i = 0; i < other.size_; i++) {
		records_[i]=new Record(*other.records_[i]);
	}

}
template <class TYPE>
SimpleTable<TYPE>::SimpleTable(SimpleTable<TYPE>&& other) {
	size_ = other.size_;
	max_ = other.max_;
	records_ = other.records_;
	other.records_ = nullptr;
	other.size_ = 0;
	other.max_ = 0;
}

template <class TYPE>
bool SimpleTable<TYPE>::update(const string& key, const TYPE& value) {
	int idx = search(key);
	if (idx == -1) {
		if (size_ == max_) {
			grow();
		}
		
//finding the correct index to add new record so that all records remain sorted

		int i=numRecords();
		while(i>0 && key < records_[i-1]->key_){
			records_[i]=records_[i-1];
			i--;	
		}
		records_[i]=new Record(key,value);
		size_++;
	}
	else {
		records_[idx]->data_ = value;
	}
	return true;
}

template <class TYPE>
bool SimpleTable<TYPE>::remove(const string& key) {
	int idx = search(key);
	bool keyRemoved=false;
	if (idx != -1 && !keyRemoved ) {
		delete records_[idx];
		for (int i = idx; i<numRecords() - 1; i++) {
			records_[i] = records_[i + 1];
		}
		size_--;
		keyRemoved = true;
	}
	return keyRemoved;
}

template <class TYPE>
bool SimpleTable<TYPE>::find(const string& key, TYPE& value) {
	int idx = search(key);
	if (idx == -1)
		return false;
	else {
		value = records_[idx]->data_;
		return true;
	}
}

template <class TYPE>
const SimpleTable<TYPE>& SimpleTable<TYPE>::operator=(const SimpleTable<TYPE>& other) {
 if (this != &other) {
                if (records_) {
                        for (int i = 0; i<numRecords(); i++) {
                                remove(records_[0]->key_);
                        }
                        delete[] records_;
                }
                records_ = new Record*[other.max_];
                max_ = other.max_;
                size_ = 0;
                for (int i = 0; i<other.size_; i++) {
                        update(other.records_[i]->key_, other.records_[i]->data_);
                }

        }
        return *this;
}
template <class TYPE>
const SimpleTable<TYPE>& SimpleTable<TYPE>::operator=(SimpleTable<TYPE>&& other) {
	swap(records_, other.records_);
	swap(size_, other.size_);
	swap(max_, other.max_);
	return *this;
}
template <class TYPE>
SimpleTable<TYPE>::~SimpleTable() {
	if (records_) 
		delete[] records_;
}

template <class TYPE>
class LPTable :public Table<TYPE> {

	string* key_array;
	TYPE* value_array;

	int curr_size;
	int total_capacity;
	int max_expected;
	
	bool isBetween(int, int, int);

public:
//to generate hash keys
	hash<string> hashFunction;

	LPTable(int maxExpected, double percentOpen);
	LPTable(const LPTable& other);
	LPTable(LPTable&& other);
	virtual bool update(const string& key, const TYPE& value);
	virtual bool remove(const string& key);
	virtual bool find(const string& key, TYPE& value);
	virtual const LPTable& operator=(const LPTable& other);
	virtual const LPTable& operator=(LPTable&& other);
	virtual ~LPTable();
	virtual bool isEmpty() const {
		return curr_size == 0;
	}
	virtual int numRecords() const {
		return curr_size;
	}
};

template <class TYPE>
LPTable<TYPE>::LPTable(int maxExpected, double percentOpen) : Table<TYPE>() {

	max_expected = maxExpected;
	total_capacity = maxExpected + (maxExpected*percentOpen);
	curr_size = 0;
	key_array = new string[total_capacity];
	for (int i = 0; i < total_capacity; i++){
		key_array[i] = "";
	}
	value_array = new TYPE[total_capacity];
}

template <class TYPE>
LPTable<TYPE>::LPTable(const LPTable<TYPE>& other) {

	curr_size = other.curr_size;
	total_capacity = other.total_capacity;
	max_expected = other.max_expected;
	key_array = new string[total_capacity];
	value_array = new TYPE[total_capacity];
	*this = other;
}

template <class TYPE>
LPTable<TYPE>::LPTable(LPTable<TYPE>&& other) {

	key_array = new string[total_capacity];
	value_array = new TYPE[total_capacity];
	*this = move(other);
}

template <class TYPE>
bool LPTable<TYPE>::update(const string& key, const TYPE& value) {
	bool isUpdated = false;
	size_t hash = hashFunction(key);
	size_t idx = hash % total_capacity;
	size_t i = idx;
//updating here if key exist
	while (key_array[i] != "") {
		if (key_array[i] == key) {
			value_array[i] = value;
			isUpdated = true;
		}
		if (i == (total_capacity - 1))
			i = 0;
		else
			i++;
	}
//adding here if key does not exist
	if (!isUpdated) {
		i = idx;
		while (key_array[i] != "") {
			if (i == (total_capacity - 1))
				i = 0;
			else
				i++;
		}
		if (curr_size < max_expected) {
			key_array[i] = key;
			value_array[i] = value;
			curr_size++;
			isUpdated = true;
		}
	}
	return isUpdated;
}

template <class TYPE>
bool LPTable<TYPE>::remove(const string& key) {
	bool isRemoved=false;
	int empty_idx;
	int curr, temp;
	size_t hash = hashFunction(key);
	size_t idx = hash % total_capacity;

//removing key
	while (key_array[idx] != "" && !isRemoved) {
		if (key_array[idx] == key) {
			empty_idx = idx;
			key_array[idx] = "";
			isRemoved = true;
			curr_size--;
			break;
		}
		if (idx == (total_capacity - 1))
			idx = 0;
		else
			idx++;
	}

//updating table after removing key
	if (isRemoved) {
		if(empty_idx == (total_capacity-1))
			curr =0;
		else
			curr = empty_idx+1; 
		while (key_array[curr] != "") {
			size_t hash_ = hashFunction(key_array[curr]);
			size_t hash_curr = hash_ % total_capacity;

//function to check if hash value of current index is between empty or not
//swapping empty spot with closest next value according to hash keys

			if (isBetween(empty_idx, hash_curr, curr)) {
				key_array[empty_idx] = key_array[curr];
				value_array[empty_idx] = value_array[curr];
				key_array[curr] = "";
				temp=curr;
				empty_idx= temp;
				curr=empty_idx;
			}
			if(curr ==(total_capacity-1))
					curr=0;
				else
					curr++;
		}
	}
	return isRemoved;
}

/* This function takes in index for empty spot in array,index for current spot and
   hash value of current spot.This function checks if the empty spot is between 
   value of hash key and current spot.
   If it is in between, function returns true else false. */

template <class TYPE>
bool LPTable<TYPE>::isBetween(int emptyIdx_, int hashIdx_, int currIdx_) {
	if(emptyIdx_ >=hashIdx_ && emptyIdx_ < currIdx_)
		return true;
	else if((emptyIdx_ >=hashIdx_) && (emptyIdx_ > currIdx_) && (currIdx_ < hashIdx_))
                return true;
	else
		return false;
}

template <class TYPE>
bool LPTable<TYPE>::find(const string& key, TYPE& value) {
	bool found = false;
	size_t hash = hashFunction(key);
	size_t idx = hash % total_capacity;

//going through the array until record is found or it hits an empty spot

	while (key_array[idx] != "" && !found) {
		if (key_array[idx] == key) {
			value = value_array[idx];
			found = true;
		}
		if (idx == (total_capacity - 1))
			idx = 0;
		else
			idx++;
	}
	return found;
}

template <class TYPE>
const LPTable<TYPE>& LPTable<TYPE>::operator=(const LPTable<TYPE>& other) {
	if (this != &other) {
		delete[] key_array;
		delete[]value_array;
		curr_size = other.curr_size;
		total_capacity = other.total_capacity;
		max_expected = other.max_expected;
		key_array = new string[total_capacity];
		value_array = new TYPE[total_capacity];

		for (int i = 0; i < total_capacity; i++)
			key_array[i] = other.key_array[i];
		for (int i = 0; i < total_capacity; i++)
			value_array[i] = other.value_array[i];
	}
	return *this;
}

template <class TYPE>
const LPTable<TYPE>& LPTable<TYPE>::operator=(LPTable<TYPE>&& other) {
	if (this != &other) {
		delete[] key_array;
		delete[]value_array;
		curr_size = other.curr_size;
		total_capacity = other.total_capacity;
		max_expected = other.max_expected;
		key_array = new string[total_capacity];
		value_array = new TYPE[total_capacity];

		for (int i = 0; i < total_capacity; i++)
			key_array[i] = other.key_array[i];
		for (int i = 0; i < total_capacity; i++)
			value_array[i] = other.value_array[i];
	
		other.curr_size = 0;
		other.total_capacity = 0;
		other.max_expected = 0;	
		delete[] other.key_array;
		delete[] other.value_array;
	}
	return *this;
}

template <class TYPE>
LPTable<TYPE>::~LPTable() {
	delete[] key_array;
	delete[]value_array;
	curr_size = 0;
	total_capacity = 0;
	max_expected = 0;
}
