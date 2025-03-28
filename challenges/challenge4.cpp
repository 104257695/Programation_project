#include <iostream>
#include <string> 
#include <concepts>
#include <type_traits>
// --------------------Task 1.1: Write a Simple Template Function----------------
template <typename T>
T maxValue(const T& a, const T& b) {
    return (a > b) ? a : b;
}
//-------------------------------------------------
template <typename T>
T maxValue1(const T& a, const T& b, const T& c) {
    return maxValue(a, maxValue(b, c));
}

template <typename T>
concept Numeric = std::integral<T> || std::floating_point<T>;

template <Numeric T>
T add(const T& a, const T& b) {
    return a + b;
}


template <typename T>
void printAll(const T& t) {
    std::cout << t << std::endl;
}

template <typename T, typename... Args>
void printAll(const T& t, const Args... args) {
    std::cout << t << " ";
    printAll(args...);
}


template <typename T>
T sum(const T& t) {
    return t;
}

template <typename T, typename... Args>
T sum(const T& t, const Args... args) {
    return t + sum(args...);
}


template <int N>
struct Factorial {
    static constexpr int value = N * Factorial<N - 1>::value;
};

// Caso base
template <>
struct Factorial<0> {
    static constexpr int value = 1;
};


template <int N>
struct Fibonacci {
    static constexpr int value = Fibonacci<N - 1>::value + Fibonacci<N - 2>::value;
};

template <>
struct Fibonacci<0> {
    static constexpr int value = 0;
};

template <>
struct Fibonacci<1> {
    static constexpr int value = 1;
};

int main() {
    std::cout << ("---Task 1.1-----") << std::endl;
    std::cout << maxValue(5, 30) << std::endl;              
    std::cout << maxValue(40.8, 2.11) << std::endl;               
    std::cout << maxValue(std::string("computer"), std::string("orange")) << std::endl; 

    std::cout << ("---Task 1.2-----") << std::endl; 
    std::cout << maxValue1(1,5, 3) << std::endl;        
    std::cout << maxValue1(2.1, 3.7, 1.9) << std::endl;    

    std::cout << ("---Task 2.1-----") << std::endl;
    std::cout << add(3, 4) << std::endl;       
    std::cout << add(2.5, 3.1) << std::endl;   
    
    std::cout << ("---Task 3.1-----") << std::endl;
    printAll(30, 22.80, "Jefferson", 'G');

    std::cout << ("---Task 3.2-----") << std::endl;
    std::cout << sum(6, 4, 1, 6, 3) << std::endl;            
    std::cout << sum(1.1, 0.73, 2.5) << std::endl;             
     
    std::cout << ("---Task 4.1-----") << std::endl;
    constexpr int result1 = Factorial<6>::value; 
    std::cout<< result1 << std::endl;  
 
    std::cout << ("---Task 4.2-----") << std::endl;
    constexpr int result = Fibonacci<10>::value;
    std::cout << result << std::endl; 

    return 0;
}

