/*
 * Simplified version of the std::vector
 * This is your h file. Do not edit it!
 */

#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <iostream>
#include <exception>
using std::exception;
using std::cout;
using std::endl;
using std::cin;


// Purpose: Swaps two elements of a vector
// Parameters: a, b: the list elements themselves to be swapped
// e.g., swap(list_obj[2], list_obj[1]);
template <typename T>
void swap(T &a, T &b);


// We're giving you this one for free.
// You will need to throw it in some below functions.
class OutOfBoundsException: public exception
{
    public:
        virtual const char * what() const throw()
        {
            return "Array out of bounds!";
        }
};


template <typename T>
class MyVector
{
    private:
        T *m_data;
        int reserved_size;
        int data_size;

    public:
        // Should default to a dynamically sized array 1 large
        // Just a simple default constructor.
        MyVector();

        ~MyVector();

        MyVector<T> & operator=(const MyVector<T> &source);

        MyVector(const MyVector<T> &source);

        // Returns the element of the array by reference, so it can be read or written.
        T & operator[](int i);

        // Purpose: Returns the element stored at the index by reference
        // Parameters: index - The location of the element to be returned.
        // This one should through an OutOfBoundsException exception when out-of-bounds
        T & at(int index);

        // Purpose: Returns the element stored at the front of the vector
        T & front();

        // Purpose: Returns the element stored at the back of the vector
        T & back();

        // Purpose: Returns the maximum number of elements that can be stored in the current Vector
        int capacity();

        // Purpose: Ensures that there is enough room for a specific number of elements
        // Parameters: new_cap - The amount of space to be reserved in the array.
        // Postconditions: Increases max_size to new_cap if new_cap > max_size
        // Other functions should check that their operations are not going beyond the size limit,
        // and call this one if so
        // By default, you should double the size of the current array when it fills up.
        void reserve(int new_cap);

        // If your array hits the point at which it is less than 1/4 full, it should call this function.
        // It should shrink such that the array is 2x as big as the data.
        void shrink_to_fit();

        // Fills the array with count of T value (e.g., 5 a would be [a, a, a, a, a])
        // This replaces the current array.
        void assign(int count, const T &value);

        // Purpose: Clears the MyVector
        // Postconditions: current size set to 0, storage size to default.
        //                 elements are deallocated and data is set to NULL
        void clear();

        // Purpose: puts the value x at the end of an MyVector
        // Parameters: x is value to be added to MyVector
        // Postconditions: current size is incremented by 1
        //     If max size is reached, the storage array is grown.
        void push_back(const T &x);

        // Removes the last element of the list
        void pop_back();

        // Purpose: puts the value x at the position i in the  MyVector
        // Parameters: x is value to be added to MyVector
        //             i is the position to insert x at
        // Postconditions: current size is incremented by 1
        //     If max size is reached, the storage array is grown().
        void insert(int i, const T &x);

        // Purpose: Removes the element at index i in the array
        // Parameters: i, the index of the element to remove
        // Postconditions: if the size of the list is greater than 0
        //     size is decremented by one.
        //     if the size of the list less than 1/4 the max size,
        //     the storage array is shrunk.
        void remove(int i);

        // Returns the size of the actual data stored in the array list
        // Remember, with indexing at 0, this is 1 more than the last elements position index
        int size();

        int begin()
        {
            return 0;
        }

        int end()
        {
            return size();
        }
};


// This relies on you having implemented the .at() and .size() member functions first.
template <typename T>
std::ostream & operator<<(std::ostream &out, MyVector<T> &my_list)
{
    out << "[ ";

    for(int i = 0; i < my_list.size(); i++)
    {
        out << my_list.at(i) << ", ";
    }
    out << "]";

    return out;
}


#include "MyVector.hpp"

#endif
