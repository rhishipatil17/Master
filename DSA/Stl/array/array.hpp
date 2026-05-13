#ifndef ARRAY_H
#define ARRAY_H

#include <cstddef>
#include <stdexcept>
#include <utility>

// Note 1:
// const functions for 'const rp::array<>' declarations
// If rp::array is declared as const, compiler will use the corresponding function

// Note 2:
// Partial template specialization for N = 0 as declaring elements[0] is not allowed

// Note 3:
// The size and type of the two arrays do not need to be checked as the compiler does it for us
// rp::array<int, 4> and rp::array<int, 6> are two different data types for the compilers, not just arrays with different sizes
// array::swap(array& other) actually means array::swap(array<T, N>& other)
// If the correct data type is not passed to "other", the compiler will give an error

// Note 4:
// It is necessary to make the function as noexcept
// 1. to boost performance as the compiler does not generate error catching code for this
// 2. if the function fails to copy successfully and the function throws any exception, std::terminal will be called to crash the application
//    instead of continuing with corrupted arrays

// Note 5:
// "using std::swap" is written instead of directly calling std::swap(a, b)
// If the user of rp::array<CustomClass, 2> has created a specialized swap function for the CustomClass, that function should be called
// By pulling std::swap into the local scope we tell the compiler to look for a custom 'swap' function for the specified data type.
// If it is not present, then use std::swap

// Note 6:
// If swap(rp::array<>, rp::array<>) is done, the custom swap function for rp::array should be called instead of std::swap (Argument-Dependent Lookup)
// 'Hidden Friend' is needed to achieve this

namespace rp
{
    template <typename T, std::size_t N>
    struct array
    {
        // raw array in stack memory
        T elements[N];

    // --- Capacity ---

        constexpr std::size_t size() { return N; }
        constexpr std::size_t max_size() { return N; }
        constexpr bool empty() { return N == 0; }

    // --- Element Access ---

        // no limit checking for size of array before indexing (faster)
        T& operator[](std::size_t index)
        {
            return elements[index];
        }
        const T& operator[](std::size_t index) const
        {
            return elements[index];
        }

        // limit is checked for size of array before indexing
        T& at(std::size_t index)
        {
            if( index > N )
            {
                throw std::out_of_range("rp::array index out of bounds");
            }
            return elements[index];
        }
        const T& at(std::size_t index) const
        {
            if( index > N )
            {
                throw std::out_of_range("rp::array index out of bounds");
            }
            return elements[index];
        }

        T& front() { return elements[0]; }
        const T& front() const { return elemnts[0]; }

        T& back() { return elements[N-1]; }
        const T& back() const { return elements[N-1]; }

        // return a pointer to the underlying raw array
        T* data() { return elements; }
        cons T* data() const { return elements; }

    // --- Iterators ---

        // since rp::array stores objects contegeously, a custom iterator struct is not needed
        using iterator = T*;
        using const_iterator = const T*;

        iterator begin() { return elements; }
        iterator end() { return elements + N; }

        const_iterator begin() const { return elements; }
        const_iterator end() const { return elements + N; }

        const_iterator cbegin() const { return elements; }
        const_iterator cend() const { return elements + N; }

    // --- Operations ---

        // fill the value in all positions of the container
        void fill(const T& value)
        {
            for(std::size_t i = 0; i < N; i++)
            {
                elements[i] = value;
            }
        }

        // Note 3, 4
        void swap(array& other) noexcept
        {
            for(std::size_t i = 0; i < N; i++)
            {
                // Note 5
                using std::swap;
                swap(elements[i], other.elements[i]);
            }
        }

        // Note 6
        friend void swap(array& lhs, array& rhs) noexcept
        {
            lhs.swap(rhs);
        }
    };

    // Note 2
    template<typename T>
    struct array<T, 0>
    {
        // no raw array declaration here

    // --- Capacity ---

        constexpr std::size_t size() { return 0; }
        constexpr std::size_t max_size() { return 0; }
        constexpr bool empty() { return true; }

    // --- Element Access ---

        // undefined behavior if called
        T& operator[](std::size_t /*index*/) { return *data(); }
        const T& operator[](std::size_t /*index*/) const { return *data(); }

        T& at(std::size_t /*index*/)
        {
            throw std::out_of_range("rp::array index out of bounds (array is empty)");
        }
        const T& at(std::size_t /*index*/) const
        {
            throw std::out_of_range("rp::array index out of bounds (array is empty)");
        }

        // undefined behavior if called
        T& front() { return *data(); }
        const T& front() const { return *data(); }

        // undefined behavior if called
        T& back() { return *data(); }
        const T& back() const { return *data(); }

        // undefined behavior if called
        T* data() { return nullptr; }
        const T* data() const { return nullptr; }

    // --- Iterators ---

        using iterator = T*;
        using const_iterator = const T*;

        iterator begin() { return nullptr; }
        iterator end() { return nullptr; }

        const_iterator begin() const { return nullptr; }
        const_iterator end() const { return nullptr; }

        const_iterator cbegin() const { return nullptr; }
        const_iterator cend() const { return nullptr; }

    // --- Operations ---

        void fill(const T& /*value*/)
        {
            // Do nothing as the array is empty
        }

        void swap(array& /*other*/) noexcept
        {
            // Do nothing as the arrays are empty
        }

        friend void swap(array& /*lhs*/, array& /*rhs*/) noexcept
        {
            // Do nothing as the arrays are empty
        }
    };
}

#endif
