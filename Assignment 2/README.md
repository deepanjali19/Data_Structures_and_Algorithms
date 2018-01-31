
**Overview**

In this assignment, you will be working with classes derived from an abstract base class named Table. The starter file for this assignment can be found in the file table.h available in course repository.

The file contains the following:
- The abstract base class Table
- SimpleTable which is derived from Table. 
    - This table implements the Table as a sorted array.
    - The code works to spec (ie, its a sorted array, you can compile and run it, it will pass all tests).
    - You will work with this table in Part A and B of your assignment
- LPTable which is derived from Table. 
    - This table is not implemented.
    - You will need to implement this class and it must be a hash table using linear probing as its collision resolution method.
   
**Table Class**

The Table class is a templated abstract base class. That is, it describes the functionalities of a Table but does not implement any part of it. It is up to classes derived from the Table to implement the Table itself. This section describes the interfaces (ie the operations) of a Table. The specifics of the implementation (ie is it a hash table or a sorted array? what collision resolution method is used etc.) is done in the derived classes.

The records for this table consists of key-value pairs. The key in a c++ string. The value can be any data type that supports the following:
  - assignment (=)
  - instantiation without arguments (you can declare variables of TYPE, the value of which is undefined)

In the description below the word record refer to a key-value pair. The way you store it (whether you make a template struct called Record with a data member for key and value, or you store them separately in parallel structures is entirely up to you.

Here are the operations on Table:
  
``Table();``

Initializes a Table to an empty table

``bool update(const string& key, const TYPE& value);``
This function is passed a key-value pair. If your table already has a record with a matching key, the record's value is replaced by the value passed to this function. If no record exists, a record with key-value pair is added to the table as long as it is possible to do so (some implementations restrict the amount of data it can hold). If the record was successfully added or updated, function returns true. Otherwise false is returned.

``bool find(const string& key,TYPE& value );``
This function is passed a key and a reference for passing back a found value. If your table contains a record with a matching key, the function returns true, and passes back the value from the record. If it does not find a record with a matching key, function returns false.

``bool remove(const string& key);``
This function is passed a key. If your table contains a record with a matching key, the record (both the key and the value) is removed from the table

``int numRecords() const``
This function returns the number of records in the table.

``bool isEmpty() const``
This function returns the number of records in the table.

Aside from the above functions, all tables must have proper destructors, copy constructors/assignment operators, move constructor/operator that allow for resources to be properly managed.
Part A (10 marks)
Study the implementation of the SimpleTable class without making any modifications. Using that implementation, determine the run time of the following functions/situation as they are currently implemented, where n is the amount of data currently in the table.:
update() - if item does not exists so you need to add it as a new record with grow()
update() - if item does not exists so you need to add it as a new record, without grow()
update() - if item does exists and you are just modifying what is there
find() - if item is there
find() - if item is not there
remove() - if item is there
remove() - if item is not there
copy constructor
assignment operator
destructor

