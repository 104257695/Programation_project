#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
/*
int main() {
    std::vector<int> v1 = {1, 2, 3, 4};
    std::vector<int> v2 = v1;        // Copy
    std::vector<int> v3 = std::move(v1); // Move

    std::cout << "v1 size: " << v1.size() << std::endl;
    std::cout << "v2 size: " << v2.size() << std::endl;
    std::cout << "v3 size: " << v3.size() << std::endl;

    return 0;
}

Questions:

• What is the output of this program?
v1 size: 0
v2 size: 4
v3 size: 4

• Why does v1.size() return 0 after the move?
Because the elements of v1 are moved to v3 and then v1 is empty.

• What does std::move do?
Converts the object to an rvalue reference (T&&) 

• Why is v1 still in a valid but unspecified state?
Because it is to avoid the cost of restoring the object after moving its resources to improve efficiency.
*/

class Buffer {
    private:
        int* data;
        size_t size;
    
    public:
        Buffer(size_t s) : size(s), data(new int[s]) {
            std::cout << "Constructor called\n";
        }
    
        ~Buffer() {
            delete[] data;
            std::cout << "Destructor called\n";
        }
    
        // Copy constructor
        Buffer(const Buffer& other) : size(other.size), data(new int[other.size]) {
            std::copy(other.data, other.data + other.size, data);
            std::cout << "Copy constructor called\n";
        }
    
        // Copy assignment operator
        Buffer& operator=(const Buffer& other) {
            if (this != &other) {
                delete[] data;
                size = other.size;
                data = new int[size];
                std::copy(other.data, other.data + size, data);
                std::cout << "Copy assignment operator called\n";
            }
            return *this;
        }
    
        // Move constructor
        Buffer(Buffer&& other) noexcept : data(other.data), size(other.size) {
            other.data = nullptr;
            other.size = 0;
            std::cout << "Move constructor called\n";
        }
    
        // Move assignment operator
        Buffer& operator=(Buffer&& other) noexcept {
            if (this != &other) {
                delete[] data;
                data = other.data;
                size = other.size;
                other.data = nullptr;
                other.size = 0;
                std::cout << "Move assignment operator called\n";
            }
            return *this;
    }
};

int main() {
    Buffer b1(100);
    Buffer b2 = b1;           
    Buffer b3 = std::move(b1); 

    Buffer b4(50);
    b4 = b2;                  
    b4 = std::move(b2);       

    auto start = std::chrono::high_resolution_clock::now();
    // Operation
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Duration: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n";
    return 0;
}

/*  Questions:
• What constructors and assignments are called and when? 
First we call copy constructor, then move constructor, constructor, copy assignment, and finally move assignment.

• What happens to the source object after a move? 
The source object is left in a valid but empty state.

• What would happen if you didn’t define the move constructor/assignment?
C++ would use the copy constructor/assignment instead, which can be slower.


• What did you learn about move semantics?
Move semantics let you transfer ownership of resources efficiently instead of copying. It's useful for better 
performance, especially when dealing with large data.

• In what kinds of projects do you think this would matter?
Projects that handle large data like buffers, images, or audio.

• What are some risks of using std::move incorrectly?
If you use std::move and then use the object again, it may behave unexpectedly or be in an empty state.

*/