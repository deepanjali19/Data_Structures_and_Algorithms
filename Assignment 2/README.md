
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
