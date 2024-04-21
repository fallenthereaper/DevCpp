#pragma once

#ifndef FUNCTIONAL_H
#define FUNCTIONAL_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <functional>
#include <optional>


namespace Utility {
	namespace Functional {
        // Supplier: Represents a function that produces a value without taking any input arguments.
        template<typename T>
        using supplier = std::function<T()>;

        // Consumer: Represents an operation that accepts a single input argument and returns no result.
        template<typename T>
        using consumer = std::function<void(const T&)>;

        // Function: Represents a function that accepts one argument and produces a result.
        template<typename T>
        using predicate = std::function<bool(T)>;

        // Predicate: Represents a predicate (boolean-valued function) of one argument.
        template<typename T, typename R>
        using func = std::function<R(T)>;

        // BiConsumer: Represents an operation that accepts two input arguments and returns no result.
        template<typename T, typename U>
        using biConsumer = std::function<void(const T&, const U&)>;

        // BiFunction: Represents a function that accepts two arguments and produces a result.
        template<typename T, typename U, typename R>
        using biFunction = std::function<R(const T&, const U&)>;

        // BiPredicate: Represents a predicate (boolean-valued function) of two arguments.
        template<typename T, typename U>
        using biPredicate = std::function<bool(const T&, const U&)>;

        template<typename T>
        using comparator = std::function<bool(const T&, const T&)>;

        template<typename T>
        class Supplier {
        public:
            // Constructor taking a lambda as argument to initialize the supplier
            Supplier(supplier<T> lambda) : m_lambda(lambda) {}

            // Overloaded operator() to invoke the lambda and return the result
            T operator()() const {
                return m_lambda();
            }

            // Method to to invoke the lambda and return the result
            T get() const {
                return m_lambda();
            }

        private:
            supplier<T> m_lambda;  // The lambda function held by the supplier
        };

        // Predicate: Represents a predicate(boolean - valued function) of one argument.
        template<typename T>
        class Predicate {
        public:
            // Constructor taking a lambda as argument to initialize the predicate
            Predicate(predicate<T> lambda) : m_lambda(lambda) {}

            // Overloaded operator() to invoke the predicate and return the result
            bool operator()(const T& arg) const {
                return m_lambda(arg);
            }

            // Method to test the predicate with an argument
            bool test(const T& arg) const {
                return m_lambda(arg);
            }

        private:
            std::function<bool(const T&)> m_lambda;  // The lambda function held by the predicate
        };

        // BiPredicate: Represents a predicate (boolean-valued function) of two arguments.
        template<typename T, typename U>
        class BiPredicate {
        public:
            // Constructor taking a lambda as argument to initialize the predicate
            BiPredicate(biPredicate<T, U> lambda) : m_lambda(lambda) {}

            // Overloaded operator() to invoke the predicate and return the result
            bool operator()(const T& arg1, const U& arg2) const {
                return m_lambda(arg1, arg2);
            }

            // Method to test the predicate with two arguments
            bool test(const T& arg1, const U& arg2) const {
                return m_lambda(arg1, arg2);
            }

        private:
            std::function<bool(const T&, const U&)> m_lambda;  // The lambda function held by the predicate
        };

        // Function: Represents a function that accepts one argument and produces a result.
        template<typename T, typename R>
        class Function {
        public:
            // Constructor taking a lambda as argument to initialize the function
            Function(func<T, R> lambda) : m_lambda(lambda) {}

            // Overloaded operator() to invoke the function and return the result
            R operator()(const T& arg) const {
                return m_lambda(arg);
            }

            // Method to apply the function to an argument
            R apply(const T& arg) const {
                return m_lambda(arg);
            }

        private:
            std::function<R(const T&)> m_lambda;  // The lambda function held by the function
        };

        // BiFunction: Represents a function that accepts two arguments and produces a result.
        template<typename T, typename U, typename R>
        class BiFunction {
        public:
            // Constructor taking a lambda as argument to initialize the function
            BiFunction(std::function<R(const T&, const U&)> lambda) : m_lambda(lambda) {}

            // Overloaded operator() to invoke the function and return the result
            R operator()(const T& arg1, const U& arg2) const {
                return m_lambda(arg1, arg2);
            }

            R apply(const T& arg1, const U& arg2) const {
                return m_lambda(arg1, arg2);
            }

        private:
            std::function<R(const T&, const U&)> m_lambda;  // The lambda function held by the function
        };

        template<typename T1, typename T2, typename T3, typename R>
        class TriFunction {
        public:
            TriFunction(std::function<R(const T1&, const T2&, const T3&)> lambda) : m_lambda(lambda) {}

            R operator()(const T1& arg1, const T2& arg2, const T3& arg3) const {
                return m_lambda(arg1, arg2, arg3);
            }

            R apply(const T1& arg1, const T2& arg2, const T3& arg3) const {
                return m_lambda(arg1, arg2, arg3);
            }

        private:
            std::function<R(const T1&, const T2&, const T3&)> m_lambda;
        };

        // Consumer: Represents an operation that accepts a single input argument and returns no result.
        template<typename T>
        class Consumer {
        public:
            // Constructor taking a lambda as argument to initialize the consumer
            Consumer(std::function<void(const T&)> lambda) : m_lambda(lambda) {}

            // Overloaded operator() to invoke the consumer
            void operator()(const T& arg) const {
                m_lambda(arg);
            }

            // Method to accept and consume an argument
            void accept(const T& arg) const {
                m_lambda(arg);
            }

        private:
            std::function<void(const T&)> m_lambda;  // The lambda function held by the consumer
        };

        // BiConsumer: Represents an operation that accepts two input arguments and returns no result.
        template<typename T, typename U>
        class BiConsumer {
        public:
            // Constructor taking a lambda as argument to initialize the bi-consumer
            BiConsumer(std::function<void(const T&, const U&)> lambda) : m_lambda(lambda) {}

            // Overloaded operator() to invoke the bi-consumer
            void operator()(const T& arg1, const U& arg2) const {
                m_lambda(arg1, arg2);
            }

            // Method to accept and consume two arguments
            void accept(const T& arg1, const U& arg2) const {
                m_lambda(arg1, arg2);
            }

        private:
            std::function<void(const T&, const U&)> m_lambda;  // The lambda function held by the bi-consumer
        };

        // Initializer: Represents an interface for initializing an object of type T.
        template<class T>
        class Initializer : public Consumer<T> {
        public:
            // Constructor taking a lambda as argument to initialize the initializer
            Initializer(std::function<void(T&)> lambda) : m_lambda(lambda) {}

            // Override accept method to invoke the init method
            void accept(T& input) const {
                init(input);
            }

            /**
             * Initializes the given object of type T.
             * Implementations of this method specify how the object should be set up or configured.
             *
             * @param input The object to be initialized.
             */
            void init(T& input) const {
                m_lambda(input);
            }

        private:
            std::function<void(T&)> m_lambda;  // The lambda function held by the initializer
        };

        // ValueProcessor: Represents a functional interface for processing values from type I to type R.
        template<typename I, typename R>
        class ValueProcessor : public Function<I, R> {
        public:
            // Constructor taking a lambda as argument to initialize the value processor
            ValueProcessor(std::function<R(const I&)> lambda) : m_lambda(lambda) {}

            // Override apply method to invoke the compute method
            R apply(const I& input) const {
                return compute(input);
            }

            /**
             * Maps a value based on the provided input.
             *
             * @param input The input used for value processing.
             * @return The processed value of type R.
             */
            R compute(const I& input) const {
                return m_lambda(input);
            }

            /**
             * Returns a composed ValueProcessor that first applies this function to its input,
             * and then applies the 'after' function to the result.
             *
             * @param after The function to apply after this function.
             * @return A composed function that first applies this function and then applies the 'after' function.
             */
            template<typename V>
            ValueProcessor<I, V> andThen(const ValueProcessor<R, V>& after) const {
                return ValueProcessor<I, V>[&](const I& i) {
                    return after.compute(this->compute(i));
                    };
            }

            /**
             * Returns a composed ValueProcessor that first applies the 'before' function to its input,
             * and then applies this function to the result.
             *
             * @param before The function to apply before this function is applied.
             * @return A composed function that first applies the 'before' function and then applies this function.
             */
            template<typename V>
            ValueProcessor<V, R> compose(const ValueProcessor<V, I>& before) const {
                return ValueProcessor<V, R>([&](const V& v) {
                    return compute(before.compute(v));
                    });
            }

            /**
             * Returns a ValueProcessor that always returns its input argument.
             *
             * @return A ValueProcessor that always returns its input argument.
             */
            static ValueProcessor<I, I> identity() {
                return ValueProcessor<I, I>([](const I& t) {
                    return t;
                    });
            }

        private:
            std::function<R(const I&)> m_lambda;  // The lambda function held by the value processor
        };

        // Factory: Represents a functional interface for creating objects of type R from type T.
        template<typename T, typename R>
        class Factory : public Function<T, R> {
        public:
            // Constructor taking a lambda as argument to initialize the factory
            Factory(std::function<R(const T&)> lambda) : m_lambda(lambda) {}

            // Override apply method to invoke the create method
            R apply(const T& t) const {
                return create(t);
            }

            /**
             * Creates an object of type R based on the provided input of type T.
             *
             * @param input The input used for object creation.
             * @return An object of type R.
             */
            R create(const T& input) const {
                return m_lambda(input);
            }

        private:
            std::function<R(const T&)> m_lambda;  // The lambda function held by the factory
        };

        template<typename T>
        class Optional {
        private:
            bool hasValue;
            T value;

        public:
            // Default constructor creates an empty Optional
            Optional() : hasValue(false) {}

            // Constructor to create an Optional with a value
            explicit Optional(const T& val) : hasValue(true), value(val) {}

            // Check if the Optional has a value
            bool isPresent() const {
                return hasValue;
            }

            // Get the value if present, otherwise throw an exception
            const T& get() const {
                if (!hasValue) {
                    throw std::logic_error("No value present in Optional");
                }
                return value;
            }

            // Get the value if present, or a default value if absent
            T getOrElse(const T& defaultValue) const {
                return hasValue ? value : defaultValue;
            }

            // Get the value if present, or throw a specific exception if absent
            template<typename E>
            T orElseThrow(const E& ex) const {
                if (!hasValue) {
                    throw ex;
                }
                return value;
            }
        };

        template<typename T>
        class ValueHolder {
        private:
            T defaultValue;
            T value;

        public:
            // Constructor to initialize the ValueHolder with an initial value
            ValueHolder(const T& initialValue) : defaultValue(initialValue), value(initialValue) {}

            // Retrieve the currently held value
            const T& get() const {
                return value;
            }

            // Set a new value for the ValueHolder
            void set(const T& newValue) {
                value = newValue;
            }

            // Get the immutable default value held by this ValueHolder
            const T& getDefaultValue() const {
                return defaultValue;
            }
        };

        template<typename T>
        class Comparator {
        public:
            Comparator(comparator<T> cmp) : m_cmp(cmp) {}

            bool operator()(const T& a, const T& b) const {
                return m_cmp(a, b);
            }

            bool compare(const T& a, const T& b) const {
                return m_cmp(a, b);
            }

        private:
            comparator<T> m_cmp;
        };

        template<typename T>
        class Lazy {
        private:
            supplier<T> m_supplier;
            std::optional<T> m_value;

        public:
            Lazy(supplier<T> supplier) : m_supplier(supplier) {}

            T get() {
                if (!m_value.has_value()) {
                    m_value = m_supplier();
                }
                return m_value.value();
            }
        };

        template<typename T> //todo Make this work with Collection
        class Stream {
        public:
            Stream(const std::vector<T>& data) : m_data(data) {}

            template<typename R>
            Stream<R> map(func<T, R> mapper) const {
                std::vector<R> result;
                std::transform(m_data.begin(), m_data.end(), std::back_inserter(result), mapper);
                return Stream<R>(result);
            }

            Stream<T> filter(predicate<T> pred) const {
                std::vector<T> result;
                std::copy_if(m_data.begin(), m_data.end(), std::back_inserter(result), pred);
                return Stream<T>(result);
            }

            template<typename R>
            R reduce(R initialValue, func<R, T> reducer) const {
                return std::accumulate(m_data.begin(), m_data.end(), initialValue, reducer);
            }

            std::vector<T> collect() const {
                return m_data;
            }

        private:
            std::vector<T> m_data;
        };

        template<typename T>
        using UnaryOperator = Function<T, T>;

        template<typename T>
        using BinaryOperator = BiFunction<T, T, T>;
	}
}

#endif // FUNCTIONAL_H