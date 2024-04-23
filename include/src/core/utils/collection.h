#pragma once


#ifndef COLLECTION_H
#define COLLECTION_H

/**
 * @brief The base class for generic collections.
 *
 * This class defines a common interface for generic collections.
 * Subclasses must implement the methods to manage and iterate over elements.
 *
 * @tparam T The type of elements stored in the collection.
 */
namespace Utility {

    template<typename T>
    class Collection {
    public:
        // Iterator types
        using iterator = T*;
        using const_iterator = const T*;

        /**
         * @brief Adds an element to the collection.
         *
         * @param element The element to add.
         */
        virtual void add(const T& element) = 0;

        /**
         * @brief Removes an element from the collection.
         *
         * @param element The element to remove.
         */
        virtual void remove(const T& element) = 0;

        /**
         * @brief Checks if the collection contains a specific element.
         *
         * @param element The element to check.
         * @return true if the element is found, false otherwise.
         */
        virtual bool contains(const T& element) const = 0;

        /**
         * @brief Returns the number of elements in the collection.
         *
         * @return The number of elements.
         */
        virtual size_t getSize() const = 0;

        /**
         * @brief Checks if the collection is empty.
         *
         * @return true if the collection is empty, false otherwise.
         */
        virtual bool isEmpty() const = 0;

        /**
         * @brief Removes all elements from the collection.
         */
        virtual void clear() = 0;

        /**
         * @brief Returns an iterator pointing to the first element.
         *
         * @return An iterator to the beginning of the collection.
         */
        virtual iterator begin() = 0;

        /**
         * @brief Returns an iterator pointing to the past-the-end element.
         *
         * @return An iterator to the end of the collection.
         */
        virtual iterator end() = 0;

        /**
         * @brief Returns a const iterator pointing to the first element.
         *
         * @return A const iterator to the beginning of the collection.
         */
        virtual const_iterator begin() const = 0;

        /**
         * @brief Returns a const iterator pointing to the past-the-end element.
         *
         * @return A const iterator to the end of the collection.
         */
        virtual const_iterator end() const = 0;

        virtual T& operator[](size_t index) = 0; // Pure virtual operator[] for access

        virtual const T& operator[](size_t index) const = 0; // Pure virtual const operator[] for access

        virtual Collection<T>& operator+=(const T& element) = 0; // Pure virtual operator+= for appending


        /**
         * @brief Virtual destructor for the Collection class.
         */
        virtual ~Collection() {}
    };
}

#endif // COLLECTION_H