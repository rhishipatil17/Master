#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstddef>
#include <stdexcept>
#include <utility>
#include <initializer_list>

namespace rp
{
    template<typename T>
    class vector
    {
        public:
            vector() noexcept : m_data(nullptr), m_size(0), m_capacity(0) {}
            vector(const vector& other) : m_size(other.m_size), m_capacity(other.m_capacity)
            {
                m_data = new T[m_capacity];
                for(std::size_t i = 0; i < m_size; i++)
                {
                    m_data[i] = other.m_data[i];
                }
            }
            vector(vector&& other) noexcept : m_data(other.m_data), m_size(other.m_size), m_capacity(other.m_capacity)
            {
                other.m_data = nullptr;
                other.m_size = 0;
                other.m_capacity = 0;
            }
            vector(std::initializer_list<T> init_list)
            {
                m_size = init_list.size();
                m_capacity = m_size;
                m_data = new T[m_capacity];

                std::size_t i = 0;
                for( const  auto& item : init_list )
                {
                    m_data[i] = item;
                    i++;
                }
            }
            vector(std::size_t count, const T& value = T())
            {
                m_size = count;
                m_capacity = m_size;
                m_data = new T[m_capacity];

                for(std::size_t i = 0; i < m_size; i++)
                {
                    m_data[i] = value;
                }
            }
            ~vector()
            {
                delete[] m_data;
                m_data = nullptr;
                m_size = 0;
                m_capacity = 0;
            }
            vector& operator=(const vector& other)
            {
                if( this == &other)
                {
                    return *this;
                }

                delete[] m_data;
                m_size = other.m_size;
                m_capacity = other.m_capacity;

                m_data = new T[m_capacity];
                for(std::size_t i = 0; i < m_size; i++)
                {
                    m_data[i] = other.m_data[i];
                }

                return *this;
            }
            vector& operator=(vector&& other) noexcept
            {
                if( this == &other )
                {
                    return *this;
                }

                delete[] m_data;
                m_data = other.m_data;
                m_size = other.m_size;
                m_capacity = other.m_capacity;

                other.m_data = nullptr;
                other.m_size = 0;
                other.m_capacity = 0;

                return *this;
            }

        // --- Capacity ---

            constexpr bool empty() const noexcept { return m_size == 0; }
            constexpr std::size_t size() const noexcept { return m_size; }
            constexpr std::size_t max_size() const noexcept { return m_capacity; }
            constexpr std::size_t capacity() const noexcept { return m_capacity; }
            void reserve(std::size_t new_cap)
            {
                realloc(new_cap);
            }
            void shrink_to_fit()
            {
                if( m_capacity == m_size )
                {
                    return;
                }
                if( m_size == 0 )
                {
                    delete[] m_data;
                    m_data = nullptr;
                    m_capacity = 0;
                    return;
                }

                T* temp = new T[m_size];
                for(std::size_t i = 0; i < m_size; i++)
                {
                    temp[i] = std::move(m_data[i]);
                }
                delete[] m_data;
                
                m_data = temp;
                m_capacity = m_size;
            }
        
        // --- Element Access ---

            T& operator[](std::size_t index) { return m_data[index]; }
            const T& operator[](std::size_t index) const { return m_data[index]; }

            T& at(std::size_t index)
            {
                if( index >= m_size )
                {
                    throw std::out_of_range("rp::vector index out of bounds");
                }
                return m_data[index];
            }
            const T& at(std::size_t index) const
            {
                if( index >= m_size )
                {
                    throw std::out_of_range("rp::vector index out of bounds");
                }
                return m_data[index];
            }

            T& front() { return m_data[0]; }
            const T& front() const { return m_data[0]; }

            T& back() { return m_data[m_size-1]; }
            const T& back() const { return m_data[m_size-1]; }

            T* data() noexcept { return m_data; }
            const T* data() const noexcept { return m_data; }

        // --- Iterators ---

            using iterator = T*;
            using const_iterator = const T*;

            constexpr iterator begin() noexcept { return m_data; }
            constexpr iterator end() noexcept { return m_data + size; }

            constexpr const_iterator begin() const noexcept { return m_data; }
            constexpr const_iterator end() const noexcept { return m_data + size; }

            constexpr const_iterator cbegin() const noexcept { return m_data; }
            constexpr const_iterator cend() const noexcept { return m_data + size; }

        // --- Modifiers ---

            void clear()
            {
                for(std::size_t i = 0; i < m_size; i++)
                {
                    m_data[i].~T();
                }
                m_size = 0;
            }
            void push_back(const T& value)
            {
                check_and_increase_capacity();

                m_data[m_size] = value;
                m_size++;
            }
            void push_back(T&& value)
            {
                check_and_increase_capacity();

                m_data[m_size] = std::move(value);
                m_size++;
            }
            void pop_back()
            {
                if(m_size)
                {
                    m_data[m_size-1].~T();
                    m_size--;
                }
            }
            iterator insert(const_iterator pos, const T& value)
            {
                std::size_t idx = pos - begin();

                check_and_increase_capacity();

                for(std::size_t i = m_size; i > idx; i--)
                {
                    m_data[i] = std::move(m_data[i-1]);
                }
                m_data[idx] = value;
                size++;
                return begin() + idx;
            }
            iterator insert(const_iterator pos, T&& value)
            {
                std::size_t idx = pos - begin();

                check_and_increase_capacity();

                for(std::size_t i = m_size; i > idx; i--)
                {
                    m_data[i] = std::move(m_data[i-1]);
                }
                m_data[idx] = std::move(value);
                size++;

                return begin() + idx;;
            }
            iterator erase(const_iterator pos)
            {
                std::size_t idx = pos - begin();
                for(std::size_t i = idx; i < m_size-1; i++)
                {
                    m_data[i] = std::move(m_data[i+1]);
                }
                m_size--;

                return begin() + idx;
            }
            void resize(std::size_t count, const T& value = T())
            {
                if( count < m_size )
                {
                    m_size = count;
                }
                else if( count > m_size )
                {
                    if( count > m_capacity )
                    {
                        realloc( count * 2 );
                    }
                    for( std::size_t i = m_size; i < count; i++ )
                    {
                        m_data[i] = value;
                    }
                    m_size = count;
                }
            }

        private:
            T* m_data;
            std::size_t m_size;
            std::size_t m_capacity;

            void check_and_increase_capacity()
            {
                if( m_size == m_capacity )
                {
                    std::size_t new_cap = (m_capacity == 0) ? 1 : (m_capacity * 2);
                    realloc(new_cap);
                }
            }
            void realloc(std::size_t new_cap)
            {
                if( new_cap <= m_capacity )
                {
                    return;
                }

                T* temp = new T[new_cap];
                for(std::size_t i = 0; i < m_size; i++)
                {
                    temp[i] = std::move(m_data[i]);
                }

                delete[] m_data;
                m_data = temp;
                m_capacity = new_cap;
            }
    };
}

#endif
