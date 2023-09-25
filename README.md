# CIntervalMin template class

## Description 
In this C++ application, a template for the CIntervalMin class is being created. This template is used to store values similar to std::vector, and additionally, it can quickly (in O(n * log n) time) find the minimum in a specified interval of stored values.

## Features
To make the CIntervalMin class as versatile as possible, the template is parameterized by two generic parameters:

The first parameter is the data type of the stored elements, T_. This can be, for example, an integer, a decimal number, std::string, or another type. It is assumed that the type T_ allows copying (move/copy constructible, move/copy assignable), comparison using the < operator, output to a stream using the << operator, and deletion. The type may have other interfaces.

The second optional generic parameter of the template is the comparator data type. It can be either a functor, a function, or a lambda function. If the parameter is not specified, the default comparator std::less is used for the element data type.

The user-defined class has the following interface:

1. Constructor with an optional comparator parameter. Creates an empty instance of the class.
2. Constructor with a pair of iterators (and an optional comparator parameter). Creates an instance of the class filled with data from the range of values defined by the iterators.
3. Method push_back(val) adds the value val to the end of the list of stored values.
4. Method pop_back() removes the last saved value.
5. Method size() returns the number of saved elements.

The const_iterator data type declares an iterator for accessing the elements stored in an instance of CIntervalMin. The iterator will have properties of a random-access iterator, similar to the iterator for std::vector. The iterator will only be used to read elements.

6. Method begin() returns a const_iterator referring to the first saved element.
7. Method end() returns a const_iterator referring to the one past the last saved element.
8. Method min(st, en) finds the smallest element in the range of values defined by the iterator pair from the parameters. This smallest element is returned as the return value. When searching for the minimum, the method compares according to the specified comparator (if provided) or using the < operator (if no comparator was specified). If there are multiple identical "smallest" values in the specified range, the method returns the first one (closer to the st iterator position). If it is not possible to determine the minimum for the specified iterators, the method throws a std::invalid_argument exception.

## Installation
1. Clone the repository to your local machine: 
-  git clone https://github.com/RobertGabdullin/CIntervalMin
2. Complile:
-  g++ -o app Source.cpp

## Usage
1. Run the application:
-  ./app

## Contact
r.gabdullin@innopolis.university
