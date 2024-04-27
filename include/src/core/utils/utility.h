#pragma once

#ifndef UTILITY_H
#define UTILITY_H
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <functional>
#include <optional>
#include "functional.h"
#include <stack>
#include < conio.h >
#include "src/core/game_engine.h"
// Define constants
constexpr auto PI = 3.14159;


// Declare utility functions
namespace Utility {

    void bootGameEngine();


    using namespace Functional;

    // forEach: Performs the given action for each element of the container.
    template<typename T>
    void forEach(const std::vector<T>& container, consumer<T> action);

    // Define a function template to iterate over a generic container and apply a consumer
    template<typename T, typename Collection>
    void forEach(const Collection& collection, std::function<void(const T&)> action);


    // map: Applies the given function to each element of the container and stores the results in another container.
    template<typename T, typename R>
    std::vector<R> map(const std::vector<T>& container, func<T, R> function);

    // filter: Returns a new container containing only the elements that satisfy the given predicate.
    template<typename T>
    std::vector<T> filter(const std::vector<T>& container, predicate<T> predicate);

    // forEach: Performs the given action for each pair of elements from two containers.
    template<typename T, typename U>
    void forEach(const std::vector<T>& container1, const std::vector<U>& container2, biConsumer<T, U> action);

    // Function to throw an exception with a message
    void throwError(const std::string& message);

    // zipWith: Applies the given function to each pair of elements from two containers and stores the results in another container.
    template<typename T, typename U, typename R>
    std::vector<R> zipWith(const std::vector<T>& container1, const std::vector<U>& container2, biFunction<T, U, R> function);

    // filter: Returns a new container containing only the pairs of elements that satisfy the given predicate.
    template<typename T, typename U>
    std::vector<std::pair<T, U>> filter(const std::vector<T>& container1, const std::vector<U>& container2, biPredicate<T, U> predicate);

    enum Day { SUNDAY, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY };
    // Function to print elements of a vector
    template<typename T>
    void printVector(const std::vector<T>& vec);

    const void endl(const int n = 1);

    // Check if a number is even
    bool isEven(int num);

  static const bool validParenthesis(const std::string& input);
  static const bool validParentheses(const std::string& input);
    // Check if a number is odd
    bool isOdd(int num);

    // Function to calculate factorial using recursion
    int factorial(int n);

    // Calculate greatest common divisor (GCD) of two numbers
    int gcd(int a, int b);

    // Calculate least common multiple (LCM) of two numbers
    int lcm(int a, int b);

    // Compute power of a number (base^exponent)
    double power(double base, int exponent);

    // Round a floating-point number to a specified number of decimal places
    double roundToDecimal(double num, int decimalPlaces);


    // Shuffle elements of a vector
    template<typename T>
    void shuffleVector(std::vector<T>& vec);

    // Check if a string contains only digits
    bool isStringNumeric(const std::string& str);

    // Convert radians to degrees
    double radiansToDegrees(double radians);

    // Calculate the hypotenuse of a right triangle given two sides
    double hypotenuse(double a, double b);

    // Find the minimum element in a vector
    template<typename T>
    T minElement(const std::vector<T>& vec);

    // Find the maximum element in a vector
    template<typename T>
    T maxElement(const std::vector<T>& vec);

    // Swap two variables using references
    template<typename T>
    void swap(T& a, T& b);

    const std::string repeatString(const std::string& str, int count);

    // Sort a vector in descending order
    template<typename T>
    void sortDescending(std::vector<T>& vec);

    // Function to check if a number is prime
    bool isPrime(int num);

    // Function to compute the nth Fibonacci number
    int fibonacci(int n);


    // Function to calculate area of a circle
    double circleArea(double radius);

    // Function to convert any type to string
    template<typename T>
    std::string toString(const T& value);

    // Function to convert string to any type
    template<typename T>
    T fromString(const std::string& str);

    // Function to reverse a string
    std::string reverseString(const std::string& str);

    // Function to trim whitespace from both ends of a string
    std::string trimString(const std::string& str);

    // Function to check if a string starts with a specific prefix
    bool startsWith(const std::string& str, const std::string& prefix);

    // Function to check if a string ends with a specific suffix
    bool endsWith(const std::string& str, const std::string& suffix);

    // Function to convert degrees to radians
    double degreesToRadians(double degrees);

    // Function to generate a random number in a specified range
    int getRandomInRange(int min, int max);

    std::pair<std::string, std::vector<std::string>> parseCommand(const std::string& input);

    namespace Mth {

        struct Operator {
            std::string symbol;
            int precedence;
            std::function<double(double, double)> operation;

            // Constructor for MathOperator
            Operator(const std::string& sym, int prec, const std::function<double(double, double)>& op);

            // Function to calculate the result of the operator applied to two doubles
            double calculate(double a, double b) const;
        };

        struct Condition {
            std::string symbol;
            std::function<bool(double, double)> meet;

            Condition(const std::string& sym, const std::function<bool(double, double)>& condition);

            // Function to evaluate the condition with two doubles
            bool evaluate(double val1, double val2) const;
        };

        struct Vec3 {
            float x;
            float y;
            float z;

            // Constructors
            Vec3();
            Vec3(float x, float y, float z);

            // Accessors
            float getX() const;
            float getY() const;
            float getZ() const;

            // Mutators
            void setX(float x);
            void setY(float y);
            void setZ(float z);

            // Vector length (magnitude)
            float length() const;

            // Normalize vector (make unit vector)
            Vec3 normalize() const;

            // Dot product of two vectors
            float dot(const Vec3& other) const;

            // Cross product of two vectors
            Vec3 cross(const Vec3& other) const;

            // Operator overloads
            Vec3 operator+(const Vec3& other) const;
            Vec3 operator-(const Vec3& other) const;
            Vec3 operator*(float scalar) const;
            friend Vec3 operator*(float scalar, const Vec3& vec);
            Vec3& operator+=(const Vec3& other);
            Vec3& operator-=(const Vec3& other);
            Vec3& operator*=(float scalar);

            // Output stream operator
            friend std::ostream& operator<<(std::ostream& os, const Vec3& vec);
        };

        struct Vec2 {
        public:
            float x;
            float y;

            // Constructors
            Vec2();

            Vec2(float x, float y);

            // Accessors
            float getX() const;
            float getY() const;

            // Mutators
            void setX(float x);
            void setY(float y);

            // Vector length (magnitude)
            float length() const;

            // Normalize vector (make unit vector)
            Vec2 normalize() const;

            // Dot product of two vectors
            float dot(const Vec2& other) const;

            // Operator overloads
            Vec2 operator+(const Vec2& other) const;

            Vec2 operator-(const Vec2& other) const;

            Vec2 operator*(float scalar) const;

            friend Vec2 operator*(float scalar, const Vec2& vec);

            Vec2& operator+=(const Vec2& other);

            Vec2& operator-=(const Vec2& other);

            Vec2& operator*=(float scalar);

            // Output stream operator
            friend std::ostream& operator<<(std::ostream& os, const Vec2& vec);
        };  

     // Define a structure to represent MathOperator
       
    }

   
}

#endif // UTILITY_H