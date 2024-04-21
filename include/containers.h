#pragma once

#ifndef CONTAINER_H
#define CONTAINER_H
#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <deque>
#include <algorithm>
#include "utility.h" // Include your existing utility header
#include "Collection.h"

namespace Utility {

    namespace Container {
        template <typename T>
        void println(const T& value) {
            std::cout << value << std::endl;
        }

        template <typename T>
        bool contains(const std::vector<T>& vec, const T& value) {
            return std::find(vec.begin(), vec.end(), value) != vec.end();
        }

        template <typename K, typename V>
        bool containsKey(const std::map<K, V>& mp, const K& key) {
            return mp.find(key) != mp.end();
        }

        template <typename K, typename V>
        bool containsKey(const std::unordered_map<K, V>& ump, const K& key) {
            return ump.find(key) != ump.end();
        }

        template <typename T>
        bool contains(const std::set<T>& s, const T& value) {
            return s.find(value) != s.end();
        }

        template <typename T>
        bool contains(const std::unordered_set<T>& us, const T& value) {
            return us.find(value) != us.end();
        }

        template <typename T>
        void add(std::vector<T>& vec, const T& value) {
            vec.push_back(value);
        }

        template <typename K, typename V>
        void put(std::map<K, V>& mp, const K& key, const V& value) {
            mp[key] = value;
        }

        template <typename K, typename V>
        void put(std::unordered_map<K, V>& ump, const K& key, const V& value) {
            ump[key] = value;
        }

        template <typename T>
        void add(std::set<T>& s, const T& value) {
            s.insert(value);
        }

        template <typename T>
        void add(std::unordered_set<T>& us, const T& value) {
            us.insert(value);
        }

        // Java-style LinkedList implementation with smart pointers
        template <typename T>
        class LinkedList {
        private:
            struct Node {
                T data;
                std::unique_ptr<Node> next;
                Node(const T& value) : data(value), next(nullptr) {}
            };
            std::unique_ptr<Node> head;
            Node* tail;
            size_t size;

        public:
            LinkedList() : head(nullptr), tail(nullptr), size(0) {}

            void add(const T& value) {
                if (!head) {
                    head = std::make_unique<Node>(value);
                    tail = head.get();
                }
                else {
                    tail->next = std::make_unique<Node>(value);
                    tail = tail->next.get();
                }
                size++;
            }

            size_t getSize() const {
                return size;
            }

            bool isEmpty() const {
                return size == 0;
            }

            void clear() {
                head.reset();
                tail = nullptr;
                size = 0;
            }

            // Other operations like get, remove, etc., can be added based on requirements
        };

        template <typename T>
        class Stack {
        private:
            std::deque<T> stack; // Use deque for efficient push/pop operations

        public:
            void push(const T& value) {
                stack.push_back(value);
            }

            void pop() {
                if (!isEmpty()) {
                    stack.pop_back();
                }
            }

            const T& top() const {
                return stack.back();
            }

            bool isEmpty() const {
                return stack.empty();
            }

            size_t getSize() const {
                return stack.size();
            }

            // Clear the stack
            void clear() {
                stack.clear();
            }

            // Check if a value exists in the stack
            bool contains(const T& value) const {
                return std::find(stack.begin(), stack.end(), value) != stack.end();
            }

            // Output stream operator overload (for printing)
            friend std::ostream& operator<<(std::ostream& os, const Stack<T>& s) {
                os << "Stack [";
                for (const auto& elem : s.stack) {
                    os << elem << " ";
                }
                os << "]";
                return os;
            }
        };

        // Java-style ListMultimap (a map that allows multiple values for the same key)
        template <typename K, typename V>
        class ListMultimap {
        private:
            std::unordered_map<K, std::list<V>> map;

        public:
            void put(const K& key, const V& value) {
                map[key].push_back(value);
            }

            const std::list<V>& get(const K& key) const {
                static const std::list<V> emptyList;
                auto it = map.find(key);
                if (it != map.end()) {
                    return it->second;
                }
                return emptyList;
            }

            bool containsKey(const K& key) const {
                return map.find(key) != map.end();
            }

            size_t getSize() const {
                return map.size();
            }

            bool isEmpty() const {
                return map.empty();
            }

            void clear() {
                map.clear();
            }
        };

        // Java-style EnumMap (a map with enum keys)
        template <typename Enum, typename V>
        class EnumMap {
        private:
            std::unordered_map<Enum, V, std::hash<std::underlying_type_t<Enum>>> map;

        public:
            void put(Enum key, const V& value) {
                map[key] = value;
            }

            const V& get(Enum key) const {
                static const V defaultValue;
                auto it = map.find(key);
                if (it != map.end()) {
                    return it->second;
                }
                return defaultValue;
            }

            bool containsKey(Enum key) const {
                return map.find(key) != map.end();
            }

            size_t getSize() const {
                return map.size();
            }

            bool isEmpty() const {
                return map.empty();
            }

            void clear() {
                map.clear();
            }
        };

        template<typename T>
        class List : public Collection<T> {
        protected:
            T* elements;     // Pointer to the dynamic array storing elements
            size_t capacity; // Current capacity of the dynamic array
            size_t size;     // Current number of elements in the list
            static const size_t INITIAL_CAPACITY = 10; // Initial capacity of the dynamic array

        public:
            // Constructor
            List() : capacity(INITIAL_CAPACITY), size(0) {
                elements = new T[capacity];
            }

            // Destructor
            ~List() {
                delete[] elements;
            }

            // Copy constructor
            List(const List& other) : capacity(other.capacity), size(other.size) {
                elements = new T[capacity];
                std::copy(other.elements, other.elements + size, elements);
            }

            // Assignment operator
            List& operator=(const List& other) {
                if (this != &other) {
                    delete[] elements;
                    capacity = other.capacity;
                    size = other.size;
                    elements = new T[capacity];
                    std::copy(other.elements, other.elements + size, elements);
                }
                return *this;
            }

            typename Collection<T>::iterator begin() override {
                return elements;
            }

            typename Collection<T>::iterator end() override {
                return elements + size;
            }

            typename Collection<T>::const_iterator begin() const override {
                return elements;
            }

            typename Collection<T>::const_iterator end() const override {
                return elements + size;
            }

            void forEach(std::function<void(const T&)> action) {
                for (size_t i = 0; i < size; ++i) {
                    action(elements[i]);
                }
            }

            // Add an element to the end of the list
            void add(const T& element) {
                if (size == capacity) {
                    // Resize the array if necessary
                    capacity *= 2;
                    T* newElements = new T[capacity];
                    std::copy(elements, elements + size, newElements);
                    delete[] elements;
                    elements = newElements;
                }
                elements[size++] = element;
            }

            // Remove the first occurrence of an element from the list
            void remove(const T& element) override {
                auto it = std::find(elements, elements + size, element);
                if (it != elements + size) {
                    std::copy(it + 1, elements + size, it); // Shift elements left to overwrite the removed element
                    size--;
                }
            }

            // Check if the list contains a specific element
            bool contains(const T& element) const override {
                return std::find(elements, elements + size, element) != elements + size;
            }

            // Get the current size of the list
            size_t getSize() const override {
                return size;
            }

            // Check if the list is empty
            bool isEmpty() const override {
                return size == 0;
            }

            // Clear all elements from the list
            void clear() override {
                size = 0;
            }

            // Operator overloading for element access using []
            T& operator[](size_t index) override {
                if (index < 0 || index >= size) {
                    throw std::out_of_range("Index out of range");
                }
                return elements[index];
            }

            // Const version of element access using []
            const T& operator[](size_t index) const override {
                if (index < 0 || index >= size) {
                    throw std::out_of_range("Index out of range");
                }
                return elements[index];
            }

            // Operator overloading for appending an element
            List<T>& operator+=(const T& element) override {
                add(element);
                return *this;
            }

        protected:
            // Resize the dynamic array (double the capacity)
            void resize() {
                capacity *= 2;
                T* newElements = new T[capacity];
                std::copy(elements, elements + size, newElements);
                delete[] elements;
                elements = newElements;
            }
        };

        template<typename T>
        class ArrayList : public List<T> {
        public:
            // Constructor
            ArrayList() : List<T>() {}

            // Destructor (inherits List's destructor)

            // Copy constructor (inherits List's copy constructor)

            // Assignment operator (inherits List's assignment operator)

            // Add an element to the end of the array list
            void add(const T& element) {
                // Check if capacity needs to be increased
                if (this->getSize() == this->capacity) {
                    this->resize(); // Access resize() from the base class
                }
                // Add element to the end of the array
                this->elements[this->size++] = element; // Access elements and size from the base class
            }

            // Insert an element at a specific index
            void insert(size_t index, const T& element) {
                // Check if index is valid
                if (index < 0 || index > this->size) {
                    throw std::out_of_range("Index out of range");
                }
                // Check if capacity needs to be increased
                if (this->getSize() == this->capacity) {
                    this->resize();
                }
                // Shift elements to make space for the new element
                for (size_t i = this->size; i > index; --i) {
                    this->elements[i] = this->elements[i - 1];
                }
                // Insert the new element at the specified index
                this->elements[index] = element;
                this->size++;
            }

            // Remove an element at a specific index
            void removeAt(size_t index) {
                // Check if index is valid
                if (index < 0 || index >= this->size) {
                    throw std::out_of_range("Index out of range");
                }
                // Shift elements to remove the element at the specified index
                for (size_t i = index; i < this->size - 1; ++i) {
                    this->elements[i] = this->elements[i + 1];
                }
                // Decrease the size of the array list
                this->size--;
            }

            // Get the index of the first occurrence of an element
            // Returns -1 if element is not found
            int indexOf(const T& element) const {
                for (size_t i = 0; i < this->size; ++i) {
                    if (this->elements[i] == element) {
                        return static_cast<int>(i);
                    }
                }
                return -1; // Element not found
            }

            // Check if the array list contains a specific element
            bool contains(const T& element) const {
                return indexOf(element) != -1;
            }
        };


    }
   
}

#endif // CONTAINER_H