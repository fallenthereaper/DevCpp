#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

// Define constants
constexpr auto PI = 3.14159;


// Declare utility functions
namespace Utility {
 


    enum Day { SUNDAY, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY };
    // Function to print elements of a vector
    template<typename T>
    void printVector(const std::vector<T>& vec) {
        for (const auto& elem : vec) {
            std::cout << elem << " ";
        }

 
        std::cout << std::endl;
    }

    // Check if a number is even
    bool isEven(int num) {
        return num % 2 == 0;
    }

    // Check if a number is odd
    bool isOdd(int num) {
        return !isEven(num);
    }

    // Function to calculate factorial using recursion
    int factorial(int n) {
        return (n == 0 || n == 1) ? 1 : n * factorial(n - 1);
    }

    // Calculate greatest common divisor (GCD) of two numbers
    int gcd(int a, int b) {
        return b == 0 ? a : gcd(b, a % b);
    }

    // Calculate least common multiple (LCM) of two numbers
    int lcm(int a, int b) {
        return (a * b) / gcd(a, b);
    }

    // Compute power of a number (base^exponent)
    double power(double base, int exponent) {
        return std::pow(base, exponent);
    }

    // Round a floating-point number to a specified number of decimal places
    double roundToDecimal(double num, int decimalPlaces) {
        double multiplier = std::pow(10.0, decimalPlaces);
        return std::round(num * multiplier) / multiplier;
    }

 
    // Shuffle elements of a vector
    template<typename T>
    void shuffleVector(std::vector<T>& vec) {
        std::shuffle(vec.begin(), vec.end(), std::mt19937{ std::random_device{}() });
    }

    // Check if a string contains only digits
    bool isStringNumeric(const std::string& str) {
        return !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit);
    }

    // Convert radians to degrees
    double radiansToDegrees(double radians) {
        return radians * (180.0 / PI);
    }

    // Calculate the hypotenuse of a right triangle given two sides
    double hypotenuse(double a, double b) {
        return std::sqrt(a * a + b * b);
    }

    // Find the minimum element in a vector
    template<typename T>
    T minElement(const std::vector<T>& vec) {
        return *std::min_element(vec.begin(), vec.end());
    }

    // Find the maximum element in a vector
    template<typename T>
    T maxElement(const std::vector<T>& vec) {
        return *std::max_element(vec.begin(), vec.end());
    }

    // Swap two variables using references
    template<typename T>
    void swap(T& a, T& b) {
        T temp = a;
        a = b;
        b = temp;
    }

    const string repeatString(const string& str, int count) {
        string result;
        for (int i = 0; i < count; ++i) {
            result += str;
        }
        return result;
    }

    // Sort a vector in descending order
    template<typename T>
    void sortDescending(std::vector<T>& vec) {
        std::sort(vec.rbegin(), vec.rend());
    }

    // Function to check if a number is prime
    bool isPrime(int num) {
        if (num <= 1) return false;
        if (num <= 3) return true;
        if (num % 2 == 0 || num % 3 == 0) return false;
        for (int i = 5; i * i <= num; i += 6) {
            if (num % i == 0 || num % (i + 2) == 0) return false;
        }
        return true;
    }

    // Function to compute the nth Fibonacci number
    int fibonacci(int n) {
        if (n <= 1) return n;
        int prev = 0, curr = 1;
        for (int i = 2; i <= n; ++i) {
            int next = prev + curr;
            prev = curr;
            curr = next;
        }
        return curr;
    }


    // Function to calculate area of a circle
    double circleArea(double radius) {
        return PI * std::pow(radius, 2);
    }

    // Function to convert any type to string
    template<typename T>
    std::string toString(const T& value) {
        std::ostringstream oss;
        oss << value;
        return oss.str();
    }

    // Function to convert string to any type
    template<typename T>
    T fromString(const std::string& str) {
        T value;
        std::istringstream iss(str);
        iss >> value;
        return value;
    }

    // Function to reverse a string
    std::string reverseString(const std::string& str) {
        return std::string(str.rbegin(), str.rend());
    }

    // Function to trim whitespace from both ends of a string
    std::string trimString(const std::string& str) {
        size_t start = str.find_first_not_of(" \t\n\r");
        size_t end = str.find_last_not_of(" \t\n\r");
        return (start == std::string::npos) ? "" : str.substr(start, end - start + 1);
    }

    // Function to check if a string starts with a specific prefix
    bool startsWith(const std::string& str, const std::string& prefix) {
        return str.size() >= prefix.size() && str.compare(0, prefix.size(), prefix) == 0;
    }

    // Function to check if a string ends with a specific suffix
    bool endsWith(const std::string& str, const std::string& suffix) {
        return str.size() >= suffix.size() && str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
    }

    // Function to convert degrees to radians
    double degreesToRadians(double degrees) {
        return degrees * (PI / 180.0);
    }

    // Function to generate a random number in a specified range
    int getRandomInRange(int min, int max) {
    
        return min + (rand() % (max - min + 1));
    }

    namespace Mth {
        struct Vec3 {
            float x;
            float y;
            float z;

            // Constructors
            Vec3() : x(0.0f), y(0.0f), z(0.0f) {}
            Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

            // Accessors
            float getX() const { return x; }
            float getY() const { return y; }
            float getZ() const { return z; }

            // Mutators
            void setX(float x) { this->x = x; }
            void setY(float y) { this->y = y; }
            void setZ(float z) { this->z = z; }

            // Vector length (magnitude)
            float length() const {
                return std::sqrt(x * x + y * y + z * z);
            }

            // Normalize vector (make unit vector)
            Vec3 normalize() const {
                float len = length();
                if (len != 0.0f)
                    return Vec3(x / len, y / len, z / len);
                else
                    return Vec3();
            }

            // Dot product of two vectors
            float dot(const Vec3& other) const {
                return x * other.x + y * other.y + z * other.z;
            }

            // Cross product of two vectors
            Vec3 cross(const Vec3& other) const {
                return Vec3(y * other.z - z * other.y,
                    z * other.x - x * other.z,
                    x * other.y - y * other.x);
            }

            // Operator overloads
            Vec3 operator+(const Vec3& other) const {
                return Vec3(x + other.x, y + other.y, z + other.z);
            }

            Vec3 operator-(const Vec3& other) const {
                return Vec3(x - other.x, y - other.y, z - other.z);
            }

            Vec3 operator*(float scalar) const {
                return Vec3(x * scalar, y * scalar, z * scalar);
            }

            friend Vec3 operator*(float scalar, const Vec3& vec) {
                return vec * scalar;
            }

            Vec3& operator+=(const Vec3& other) {
                x += other.x;
                y += other.y;
                z += other.z;
                return *this;
            }

            Vec3& operator-=(const Vec3& other) {
                x -= other.x;
                y -= other.y;
                z -= other.z;
                return *this;
            }

            Vec3& operator*=(float scalar) {
                x *= scalar;
                y *= scalar;
                z *= scalar;
                return *this;
            }

            // Output stream operator
            friend std::ostream& operator<<(std::ostream& os, const Vec3& vec) {
                os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
                return os;
            }
        };

        struct Vec2 {
            float x;
            float y;

            // Constructors
            Vec2() : x(0.0f), y(0.0f) {}
            Vec2(float x, float y) : x(x), y(y) {}

            // Accessors
            float getX() const { return x; }
            float getY() const { return y; }

            // Mutators
            void setX(float x) { this->x = x; }
            void setY(float y) { this->y = y; }

            // Vector length (magnitude)
            float length() const {
                return std::sqrt(x * x + y * y);
            }

            // Normalize vector (make unit vector)
            Vec2 normalize() const {
                float len = length();
                if (len != 0.0f)
                    return Vec2(x / len, y / len);
                else
                    return Vec2();
            }

            // Dot product of two vectors
            float dot(const Vec2& other) const {
                return x * other.x + y * other.y;
            }

            // Operator overloads
            Vec2 operator+(const Vec2& other) const {
                return Vec2(x + other.x, y + other.y);
            }

            Vec2 operator-(const Vec2& other) const {
                return Vec2(x - other.x, y - other.y);
            }

            Vec2 operator*(float scalar) const {
                return Vec2(x * scalar, y * scalar);
            }

            friend Vec2 operator*(float scalar, const Vec2& vec) {
                return vec * scalar;
            }

            Vec2& operator+=(const Vec2& other) {
                x += other.x;
                y += other.y;
                return *this;
            }

            Vec2& operator-=(const Vec2& other) {
                x -= other.x;
                y -= other.y;
                return *this;
            }

            Vec2& operator*=(float scalar) {
                x *= scalar;
                y *= scalar;
                return *this;
            }

            // Output stream operator
            friend std::ostream& operator<<(std::ostream& os, const Vec2& vec) {
                os << "(" << vec.x << ", " << vec.y << ")";
                return os;
            }
        };
    }
}

#endif // UTILITY_H