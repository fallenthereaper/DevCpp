

#include "src/core/utils/utility.h";

// Declare utility functions

    using namespace Utility::Functional;

    // forEach: Performs the given action for each element of the container.
    template<typename T>
    void Utility::forEach(const std::vector<T>& container, consumer<T> action) {
        for (const auto& element : container) {
            action(element);
        }
    }



    void Utility::bootGameEngine(const std::string& windowTitle, int screenHeight, int screenWidth) {
     
        std::thread gameLoop([=]() {
            Blaze2D::GameEngine* instance = Blaze2D::GameEngine::getInstance();
            if (instance->init(windowTitle, screenWidth, screenHeight)) {
                while (instance->isRunning()) {
                    instance->handleEvents();
                    instance->tick();
                    instance->render();
                }

                instance->clean();
            }
            });
        gameLoop.join();
    
    }

    static bool const Utility::validParentheses(const std::string& input) {
        std::stack<char> stack;
        std::unordered_map<char, char> pair;

        pair.emplace('(', ')');
        pair.emplace('{', '}');
        pair.emplace('[', ']');

        for (char c : input) {
            if (pair.find(c) != pair.end()) { //Contains key
                stack.push(c);
            }
            else if (pair.find(stack.top()) != pair.end() && pair[stack.top()] == c) { //if a stack top value is present and it's value is equal to the current char
                stack.pop();
            }
            else {
                // Ignore non-parentheses characters
            }
        }

        return stack.empty();
    }

   static bool const Utility::validParenthesis(const std::string& input) {
        int openedCount = 0;

        for (std::size_t i = 0; i < input.length(); i++) {
            char c = input.at(i);

            if (c == '(') {
                openedCount++;
            }
            else if (c == ')') {
                if (openedCount > 0) {
                    openedCount--;
                }
                else {
                    // If there's no matching opening parenthesis for this closing one, return false
                    return false;
                }
            }
        }

        // After looping through all characters,
        // the count should be zero for balanced parenthesis
        return openedCount == 0;
    }

    // Define a function template to iterate over a generic container and apply a consumer
    template<typename T, typename Collection>
    void Utility::forEach(const Collection& collection, std::function<void(const T&)> action) {

        // Use auto for the iterator type to allow type deduction
        for (auto it = collection.begin(); it != collection.end(); ++it) {
            action(*it); // Apply the action on each element of the collection
        }
    }

    // map: Applies the given function to each element of the container and stores the results in another container.
    template<typename T, typename R>
    std::vector<R> Utility::map(const std::vector<T>& container, func<T, R> function) {
        std::vector<R> result;
        result.reserve(container.size());
        for (const auto& element : container) {
            result.push_back(function(element));
        }
        return result;
    }

    // filter: Returns a new container containing only the elements that satisfy the given predicate.
    template<typename T>
    std::vector<T> Utility::filter(const std::vector<T>& container, predicate<T> predicate) {
        std::vector<T> result;
        std::copy_if(container.begin(), container.end(), std::back_inserter(result), predicate);
        return result;
    }

    // forEach: Performs the given action for each pair of elements from two containers.
    template<typename T, typename U>
    void Utility::forEach(const std::vector<T>& container1, const std::vector<U>& container2, biConsumer<T, U> action) {
        size_t minSize = std::min(container1.size(), container2.size());
        for (size_t i = 0; i < minSize; ++i) {
            action(container1[i], container2[i]);
        }
    }

    // Function to throw an exception with a message
    void Utility::throwError(const std::string& message) {
        throw std::runtime_error(message);
    }

    // zipWith: Applies the given function to each pair of elements from two containers and stores the results in another container.
    template<typename T, typename U, typename R>
    std::vector<R> Utility::zipWith(const std::vector<T>& container1, const std::vector<U>& container2, biFunction<T, U, R> function) {
        size_t minSize = std::min(container1.size(), container2.size());
        std::vector<R> result;
        result.reserve(minSize);
        for (size_t i = 0; i < minSize; ++i) {
            result.push_back(function(container1[i], container2[i]));
        }
        return result;
    }

    // filter: Returns a new container containing only the pairs of elements that satisfy the given predicate.
    template<typename T, typename U>
    std::vector<std::pair<T, U>> Utility::filter(const std::vector<T>& container1, const std::vector<U>& container2, biPredicate<T, U> predicate) {
        size_t minSize = std::min(container1.size(), container2.size());
        std::vector<std::pair<T, U>> result;
        for (size_t i = 0; i < minSize; ++i) {
            if (predicate(container1[i], container2[i])) {
                result.emplace_back(container1[i], container2[i]);
            }
        }
        return result;
    }

    // Function to print elements of a vector
    template<typename T>
    void Utility::printVector(const std::vector<T>& vec) {
        for (const auto& elem : vec) {
            std::cout << elem << " ";
        }


        std::cout << std::endl;
    }

    const void Utility::endl(const int n) {
        int temp = 0;
        while (temp < n) {
            std::cout << std::endl;
            temp++;
        }
    }

    // Check if a number is even
    bool Utility::isEven(int num) {
        return num % 2 == 0;
    }

    // Check if a number is odd
    bool Utility::isOdd(int num) {
        return !isEven(num);
    }

    // Function to calculate factorial using recursion
    int Utility::factorial(int n) {
        return (n == 0 || n == 1) ? 1 : n * factorial(n - 1);
    }

    // Calculate greatest common divisor (GCD) of two numbers
    int Utility::gcd(int a, int b) {
        return b == 0 ? a : gcd(b, a % b);
    }

    // Calculate least common multiple (LCM) of two numbers
    int Utility::lcm(int a, int b) {
        return (a * b) / gcd(a, b);
    }

    // Compute power of a number (base^exponent)
    double Utility::power(double base, int exponent) {
        return std::pow(base, exponent);
    }

    // Round a floating-point number to a specified number of decimal places
    double Utility::roundToDecimal(double num, int decimalPlaces) {
        double multiplier = std::pow(10.0, decimalPlaces);
        return std::round(num * multiplier) / multiplier;
    }


    // Shuffle elements of a vector
    template<typename T>
    void Utility::shuffleVector(std::vector<T>& vec) {
        std::shuffle(vec.begin(), vec.end(), std::mt19937{ std::random_device{}() });
    }

    // Check if a string contains only digits
    bool Utility::isStringNumeric(const std::string& str) {
        return !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit);
    }

    // Convert radians to degrees
    double Utility::radiansToDegrees(double radians) {
        return radians * (180.0 / PI);
    }

    // Calculate the hypotenuse of a right triangle given two sides
    double Utility::hypotenuse(double a, double b) {
        return std::sqrt(a * a + b * b);
    }

    // Find the minimum element in a vector
    template<typename T>
    T Utility::minElement(const std::vector<T>& vec) {
        return *std::min_element(vec.begin(), vec.end());
    }

    // Find the maximum element in a vector
    template<typename T>
    T Utility::maxElement(const std::vector<T>& vec) {
        return *std::max_element(vec.begin(), vec.end());
    }

    // Swap two variables using references
    template<typename T>
    void Utility::swap(T& a, T& b) {
        T temp = a;
        a = b;
        b = temp;
    }

    const std::string Utility::repeatString(const std::string& str, int count) {
        std::string result;
        for (int i = 0; i < count; ++i) {
            result += str;
        }
        return result;
    }

    // Sort a vector in descending order
    template<typename T>
    void Utility::sortDescending(std::vector<T>& vec) {
        std::sort(vec.rbegin(), vec.rend());
    }

    // Function to check if a number is prime
    bool Utility::isPrime(int num) {
        if (num <= 1) return false;
        if (num <= 3) return true;
        if (num % 2 == 0 || num % 3 == 0) return false;
        for (int i = 5; i * i <= num; i += 6) {
            if (num % i == 0 || num % (i + 2) == 0) return false;
        }
        return true;
    }

    // Function to compute the nth Fibonacci number
    int Utility::fibonacci(int n) {
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
    double Utility::circleArea(double radius) {
        return PI * std::pow(radius, 2);
    }

    // Function to convert any type to string
    template<typename T>
    std::string Utility::toString(const T& value) {
        std::ostringstream oss;
        oss << value;
        return oss.str();
    }

    // Function to convert string to any type
    template<typename T>
    T Utility::fromString(const std::string& str) {
        T value;
        std::istringstream iss(str);
        iss >> value;
        return value;
    }

    // Function to reverse a string
    std::string Utility::reverseString(const std::string& str) {
        return std::string(str.rbegin(), str.rend());
    }

    // Function to trim whitespace from both ends of a string
    std::string Utility::trimString(const std::string& str) {
        size_t start = str.find_first_not_of(" \t\n\r");
        size_t end = str.find_last_not_of(" \t\n\r");
        return (start == std::string::npos) ? "" : str.substr(start, end - start + 1);
    }

    // Function to check if a string starts with a specific prefix
    bool Utility::startsWith(const std::string& str, const std::string& prefix) {
        return str.size() >= prefix.size() && str.compare(0, prefix.size(), prefix) == 0;
    }

    // Function to check if a string ends with a specific suffix
    bool Utility::endsWith(const std::string& str, const std::string& suffix) {
        return str.size() >= suffix.size() && str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
    }

    // Function to convert degrees to radians
    double Utility::degreesToRadians(double degrees) {
        return degrees * (PI / 180.0);
    }

    // Function to generate a random number in a specified range
    int Utility::getRandomInRange(int min, int max) {

        return min + (rand() % (max - min + 1));
    }



    //Thanks ChatGPT for this algorithm
    std::pair<std::string, std::vector<std::string>> Utility::parseCommand(const std::string& input) {
        std::pair<std::string, std::vector<std::string>> result;

        std::istringstream iss(input);

        // Extract the command word (first token before any commas)
        std::string token;
        if (std::getline(iss, token, ';')) {
            result.first = token; // This is the command word
        }
        else {
            return result; // Return empty result if no command word found
        }

        // Extract the remaining tokens as parameters
        std::string remaining;
        if (std::getline(iss, remaining)) {
            std::istringstream paramStream(remaining);
            std::string parameter;
            while (std::getline(paramStream, parameter, ',')) {
                if (!parameter.empty()) {
                    result.second.push_back(parameter); // Add parameter to vector
                }
            }
        }

        return result;
    }

    using Vec2 = Utility::Mth::Vec2;
    using Vec3 = Utility::Mth::Vec3;
    using Operator = Utility::Mth::Operator;
    using Condition = Utility::Mth::Condition;

    Vec2::Vec2() : x(0.0f), y(0.0f) {}

    Vec2::Vec2(float x, float y) : x(x), y(y) {}

    // Accessors
    float Vec2::getX() const { return x; }

    float Vec2::getY() const { return y; }

    // Mutators
    void Vec2::setX(float x) { this->x = x; }

    void Vec2::setY(float y) { this->y = y; }

    // Vector length (magnitude)
    float Vec2::length() const {
        return std::sqrt(x * x + y * y);
    }

    // Normalize vector (make unit vector)
    Vec2 Vec2::normalize() const {
        float len = length();
        if (len != 0.0f) {
            return Vec2(x / len, y / len);
        }
        return *this; // If length is zero, return the vector itself
    }

    // Dot product of two vectors
    float Vec2::dot(const Vec2& other) const {
        return x * other.x + y * other.y;
    }

    // Operator overloads
    Vec2 Vec2::operator+(const Vec2& other) const {
        return Vec2(x + other.x, y + other.y);
    }

    Vec2 Vec2::operator-(const Vec2& other) const {
        return Vec2(x - other.x, y - other.y);
    }

    Vec2 Vec2::operator*(float scalar) const {
        return Vec2(x * scalar, y * scalar);
    }

    Vec2 operator*(float scalar, const Vec2& vec) {
        return vec * scalar;
    }

    Vec2& Vec2::operator+=(const Vec2& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vec2& Vec2::operator-=(const Vec2& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    Vec2& Vec2::operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    // Output stream operator
    std::ostream& operator<<(std::ostream& os, const Vec2& vec) {
        os << "(" << vec.x << ", " << vec.y << ")";
        return os;
    }

    // Constructor for MathOperator
    Operator::Operator(const std::string& sym, int prec, const std::function<double(double, double)>& op)
        : symbol(sym), precedence(prec), operation(op) {}

    // Function to calculate the result of the operator applied to two doubles
    double Operator::calculate(double a, double b) const {
        return operation(a, b);
    }

    // Constructor for MathCondition
    Condition::Condition(const std::string& sym, const std::function<bool(double, double)>& condition)
        : symbol(sym), meet(condition) {}

    // Function to evaluate the condition with two doubles
    bool Condition::evaluate(double val1, double val2) const {
        return meet(val1, val2);
    }

    // Constructors
    Vec3::Vec3() : x(0.0f), y(0.0f), z(0.0f) {}

    Vec3::Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

    // Accessors
    float Vec3::getX() const {
        return x;
    }

    float Vec3::getY() const {
        return y;
    }

    float Vec3::getZ() const {
        return z;
    }

    // Mutators
    void Vec3::setX(float x) {
        this->x = x;
    }

    void Vec3::setY(float y) {
        this->y = y;
    }

    void Vec3::setZ(float z) {
        this->z = z;
    }

    // Vector length (magnitude)
    float Vec3::length() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    // Normalize vector (make unit vector)
    Vec3 Vec3::normalize() const {
        float len = length();
        if (len != 0.0f) {
            return Vec3(x / len, y / len, z / len);
        }
        return Vec3();
    }

    // Dot product of two vectors
    float Vec3::dot(const Vec3& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    // Cross product of two vectors
    Vec3 Vec3::cross(const Vec3& other) const {
        return Vec3(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        );
    }

    // Operator overloads
    Vec3 Vec3::operator+(const Vec3& other) const {
        return Vec3(x + other.x, y + other.y, z + other.z);
    }

    Vec3 Vec3::operator-(const Vec3& other) const {
        return Vec3(x - other.x, y - other.y, z - other.z);
    }

    Vec3 Vec3::operator*(float scalar) const {
        return Vec3(x * scalar, y * scalar, z * scalar);
    }

    Vec3 operator*(float scalar, const Vec3& vec) {
        return vec * scalar;
    }

    Vec3& Vec3::operator+=(const Vec3& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    Vec3& Vec3::operator-=(const Vec3& other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    Vec3& Vec3::operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }

    // Output stream operator
    std::ostream& operator<<(std::ostream& os, const Vec3& vec) {
        os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
        return os;
    }

