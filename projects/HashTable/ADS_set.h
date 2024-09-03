#ifndef ADS_SET_H
#define ADS_SET_H

#include <functional>
#include <algorithm>
#include <iostream>
#include <stdexcept>

template <typename T>
class MyVector
{
public:
    class ConstIterator;
    class Iterator;
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type &;
    using const_reference = const value_type &;
    using pointer = value_type *;
    using const_pointer = const value_type *;
    using iterator = MyVector::Iterator;
    using const_iterator = MyVector::ConstIterator;

private:
    // Instanzvariablen
    std::size_t sz;
    std::size_t max_sz;
    pointer values;

public:
    void swap(MyVector &other) noexcept
    {
        using std::swap;
        swap(values, other.values);
        swap(max_sz, other.max_sz);
        swap(sz, other.sz);
    }

    void resize(std::size_t n)
    {
        if (max_sz < n)
        {
            std::size_t new_max{max_sz * 2 + 1};
            while (new_max < n)
                new_max *= 2;
            pointer new_values = new value_type[new_max];
            for (std::size_t i{0}; i < sz; ++i)
                new_values[i] = values[i];
            delete[] values;
            values = new_values;
            max_sz = new_max;
        }
    }

    // Methoden
    // MyVector() : sz{0}, max_sz{0}, values{} {}
    MyVector(std::size_t n = 5) : sz{0}, max_sz{n}, values{n ? new value_type[n] : new value_type[5]}
    {
    }

    MyVector(const MyVector &v) : MyVector(v.size())
    {
        for (; sz < v.sz; ++sz)
            values[sz] = v.values[sz];
    }

    MyVector(std::initializer_list<value_type> l) : MyVector(l.size())
    {
        for (const auto &value : l)
            values[sz++] = value;
    }

    ~MyVector()
    {
        delete[] values;
    }

    MyVector &operator=(const MyVector &a)
    {
        auto *p = new value_type[a.sz];
        for (std::size_t i = 0; i < a.sz; i++)
            p[i] = a.values[i];
        delete[] values;
        this->values = p;
        this->sz = a.sz;
        return *this;
    }

    std::size_t size() const
    {
        return sz;
    }

    bool empty() const
    {
        return (sz == 0);
    }

    void push_back(const_reference x)
    {
        resize(sz + 1);
        values[sz++] = x;
    }

    void clear()
    {
        sz = 0;
    }

    void shrink_to_fit()
    {
        max_sz = sz;
    }

    void reserve(std::size_t n)
    {
        if (max_sz < n)
            resize(n);
    }

    value_type &operator[](std::size_t index)
    {
        if (index > sz - 1)
        {
            throw std::runtime_error("out1 of range!");
        }
        return values[index];
    }

    const value_type &operator[](std::size_t index) const
    {
        if (index > sz - 1)
            throw std::runtime_error("out2 of range!");

        return values[index];
    }

    std::size_t capacity() const
    {
        return max_sz;
    }

    void pop_back()
    {
        if (sz < 1)
            throw std::runtime_error("MyVector is already empty!");

        sz--;
    }

    std::ostream &print(std::ostream &o) const
    {
        o << "[";
        bool first{true};
        for (std::size_t i{0}; i < sz; i++)
        {
            if (first)
                first = false;
            else
                o << ", ";
            o << values[i];
        }
        return o << "]";
    }

    void full_clear()
    {
        delete[] values;
    }

    std::size_t max_size() const
    {
        return max_sz;
    }

    iterator begin() { return Iterator(values, values + sz); }
    iterator end() { return Iterator(values + sz, values + sz); }
    const_iterator begin() const { return ConstIterator(values, values + sz); }
    const_iterator end() const { return ConstIterator(values + sz, values + sz); }

    iterator insert(const_iterator pos, const_reference val)
    {
        auto diff = pos - begin();
        if (diff < 0 || static_cast<size_type>(diff) > sz)
            throw std::runtime_error("Iterator out of bounds");
        size_type current{static_cast<size_type>(diff)};
        if (sz >= max_sz)
            reserve(max_sz * 2); // Achtung Sonderfall, wenn keine Mindestgroesze definiert ist
        for (auto i{sz}; i-- > current;)
            values[i + 1] = values[i];
        values[current] = val;
        sz++;
        return iterator(values + current, values + sz);
    }

    iterator erase(const_iterator pos)
    {
        auto diff = pos - begin();
        if (diff < 0 || static_cast<size_type>(diff) >= sz)
            throw std::runtime_error("Iterator out of bounds");
        size_type current{static_cast<size_type>(diff)};
        for (auto i{current}; i < sz - 1; ++i)
            values[i] = values[i + 1];
        --sz;
        return iterator(&values[current], &values[sz]);
    }

    class Iterator
    {
    public:
        using value_type = MyVector::value_type;
        using reference = MyVector::reference;
        using pointer = MyVector::pointer;
        using difference_type = MyVector::difference_type;
        using iterator_category = std::forward_iterator_tag;

    private:
        // Instanzvariablen
        pointer ptr;
        pointer end_ptr;

    public:
        // Methoden
        Iterator() : ptr{nullptr}, end_ptr{nullptr}
        {
        }

        Iterator(pointer ptr) : ptr{ptr}, end_ptr{nullptr}
        {
        }

        Iterator(pointer ptr, pointer end_ptr) : ptr{ptr}, end_ptr{end_ptr}
        {
        }

        reference operator*() const
        {
            pointer tmp2{nullptr};
            if (ptr == tmp2)
                throw std::runtime_error("Out of range!");
            if (end_ptr == tmp2)
                throw std::runtime_error("Out of range!");
            if (ptr == end_ptr)
                throw std::runtime_error("Out of range!");
            return *ptr;
        }

        pointer operator->() const
        {
            pointer tmp2{nullptr};
            if (ptr == tmp2)
                throw std::runtime_error("Out of range!");
            if (end_ptr == tmp2)
                throw std::runtime_error("Out of range!");
            if (ptr == end_ptr)
                throw std::runtime_error("Out of range!");
            return ptr;
        }

        bool operator==(const const_iterator &r_ptr) const { return static_cast<ConstIterator>(*this) == r_ptr; }
        bool operator!=(const const_iterator &r_ptr) const { return static_cast<ConstIterator>(*this) != r_ptr; }
        bool operator==(const iterator &r_ptr) const { return ptr == r_ptr.ptr; }
        bool operator!=(const iterator &r_ptr) const { return ptr != r_ptr.ptr; }

        iterator &operator++()
        {
            pointer temp{ptr};
            temp++;
            pointer tmp2{nullptr};
            if (ptr == tmp2)
                return *this;
            if (ptr == end_ptr)
                return *this;
            if (end_ptr == tmp2)
                return *this;
            ptr = temp;
            return *this;
        }

        iterator operator++(int)
        {
            Iterator temp;
            temp = *this;
            ++(*this);
            return temp;
        }

        operator const_iterator() const
        {
            ConstIterator temp{ptr};
            return temp;
        }

        pointer GetPtr()
        {
            return ptr;
        }
    };

    class ConstIterator
    {
    public:
        using value_type = MyVector::value_type;
        using reference = MyVector::const_reference;
        using pointer = MyVector::const_pointer;
        using difference_type = MyVector::difference_type;
        using iterator_category = std::forward_iterator_tag;

    private:
        // Instanzvariablen
        pointer ptr;
        pointer end_ptr;

    public:
        // Methoden
        ConstIterator() : ptr{nullptr}
        {
        }

        ConstIterator(pointer ptr) : ptr{ptr}
        {
        }

        ConstIterator(pointer ptr, pointer end_ptr) : ptr{ptr}, end_ptr{end_ptr}
        {
        }

        reference operator*() const
        {
            pointer tmp2{nullptr};
            if (ptr == tmp2)
                throw std::runtime_error("Out of range!");
            if (end_ptr == tmp2)
                throw std::runtime_error("Out of range!");
            if (ptr == end_ptr)
                throw std::runtime_error("Out of range!");
            return *ptr;
        }

        pointer operator->() const
        {
            pointer tmp2{nullptr};
            if (ptr == tmp2)
                throw std::runtime_error("Out of range!");
            if (end_ptr == tmp2)
                throw std::runtime_error("Out of range!");
            if (ptr == end_ptr)
                throw std::runtime_error("Out of range!");
            return ptr;
        }

        bool operator==(const const_iterator &r_ptr) const { return ptr == r_ptr.ptr; }
        bool operator!=(const const_iterator &r_ptr) const { return ptr != r_ptr.ptr; }

        const_iterator &operator++()
        {
            pointer temp{ptr};
            temp++;
            pointer tmp2{nullptr};
            if (ptr == tmp2)
                return *this;
            if (end_ptr == tmp2)
                return *this;
            if (ptr == end_ptr)
                return *this;
            ptr = temp;
            return *this;
        }

        pointer GetPtr() const
        {
            return ptr;
        }

        const_iterator operator++(int)
        {
            ConstIterator temp;
            temp = *this;
            ++(*this);
            return temp;
        }

        friend MyVector::difference_type operator-(const MyVector::ConstIterator &lop,
                                                   const MyVector::ConstIterator &rop)
        {
            return lop.ptr - rop.ptr;
        }
    };
};
template <typename T>
void swap(MyVector<T> &lhs, MyVector<T> &rhs) noexcept { lhs.swap(rhs); }

template <typename T>
inline std::ostream &operator<<(std::ostream &o, const MyVector<T> &v)
{
    return v.print(o);
}

template <typename Key, size_t N = 3>
class ADS_set
{
public:
    class Iterator;
    using value_type = Key;
    using key_type = Key;
    using reference = value_type &;
    using const_reference = const value_type &;
    using size_type = size_t;
    using difference_type = std::ptrdiff_t;
    using const_iterator = Iterator;
    using iterator = const_iterator;
    // using key_compare = std::less<key_type>;                         // B+-Tree
    using key_equal = std::equal_to<key_type>; // Hashing
    using hasher = std::hash<key_type>;        // Hashing
private:
    enum class Mode
    {
        free,
        used
    };

    class Element
    {
    public:
        key_type element;
        Mode mode{Mode::free};
    };

    class Block
    {

    public:
        size_type block_size;
        size_type count;
        key_type *values;
        Block *overflow;

        Block() : block_size(2), count(0), overflow(nullptr)
        {
            values = new key_type[block_size];
        }

        ~Block() { clear_block(); }

        bool full() { return count == block_size; }

        void block_print(std::ostream &o = std::cerr) const
        {
            for (size_type i{0}; i < count; i++)
            {
                o << "[" << values[i] << "]";
            }
            if (overflow != nullptr)
            {
                o << " --> ";
                overflow->block_print();
            }
        }

        bool push_back(const key_type &key)
        {
            if (count < block_size)
            {
                values[count++] = key;
            }
            else
            {
                if (overflow == nullptr)
                {
                    overflow = new Block();
                }
                overflow->push_back(key);
                return true;
            }
            return false;
        }

        void clear_block()
        {
            delete[] values;
            values = nullptr;

            if (overflow != nullptr)
            {
                overflow->clear_block();
                delete overflow;
                overflow = nullptr;
            }
            count = 0;
        }

        void collect(MyVector<key_type> &v)
        {
            for (size_type i = 0; i < count; i++)
            {
                v.push_back(values[i]);
            }
            if (overflow)
            {
                overflow->collect(v);
            }
        }

        bool find(const key_type &key)
        {
            for (size_type i = 0; i < count; i++)
            {
                if (key_equal{}(values[i], key))
                {
                    return true;
                }
            }
            if (overflow != nullptr)
            {
                return overflow->find(key);
            }
            return false;
        }

        std::pair<size_type, Block *> it_find(const key_type &key)
        {
            for (size_type i = 0; i < count; i++)
            {
                if (key_equal{}(values[i], key))
                {
                    return std::make_pair(i, this);
                }
            }
            if (overflow != nullptr)
            {
                return overflow->it_find(key);
            }
            return std::make_pair(0, nullptr);
        }
    };

    MyVector<Block *> table;
    size_type table_length;
    size_type nextToSplit;
    size_type capacity;
    int d;
    size_type total;

    // ADD
    void add(const key_type &key)
    {
        size_type idx{h(key)};

        bool check = table[idx]->push_back(key);

        if (check)
        {
            split();
        }
        if (nextToSplit == static_cast<size_type>(1 << d))
        {
            nextToSplit = 0;
            d++;
        }
        ++total;
    }

    // SPLIT
    void split()
    {
        MyVector<key_type> v;
        table[nextToSplit]->collect(v);

        table.push_back(new Block());
        table_length++;

        table[nextToSplit]->clear_block();
        delete table[nextToSplit];
        table[nextToSplit] = nullptr;
        table[nextToSplit] = new Block();

        nextToSplit++;

        for (const auto &key1 : v)
        {
            size_type idx2 = h(key1);
            table[idx2]->push_back(key1);
        }
    }

    // LOCATE
    bool locate(const key_type &key) const
    {
        size_type idx{h(key)};
        return table[idx]->find(key);
    }

    // HASH
    size_type h(const key_type &key) const
    {

        size_type idx = hasher{}(key) % (1 << d);
        if (idx < nextToSplit)
        {
            idx = hasher{}(key) % (1 << (d + 1));
        }
        return idx;
    }

public:
    ADS_set() : table(8), table_length(8), nextToSplit(0), capacity(2), d(3), total(0)
    {
        for (size_type i{0}; i < table_length; ++i)
        {
            table.push_back(new Block());
        }
    } // PH1
    ADS_set(std::initializer_list<key_type> ilist) : ADS_set{std::begin(ilist), std::end(ilist)}
    {
    } // PH1
    template <typename InputIt>
    ADS_set(InputIt first, InputIt last) : ADS_set() { insert(first, last); } // PH1

    ADS_set(const ADS_set &other) : ADS_set()
    {
        for (const auto &o : other)
        {
            add(o);
        }
    }

    ~ADS_set()
    {
        for (size_type i = 0; i < table_length; ++i)
        {
            if (table[i] != nullptr)
            {
                table[i]->clear_block();
                delete table[i];
                table[i] = nullptr;
            }
        }
    }

    ADS_set &operator=(const ADS_set &other)
    {
        ADS_set tmp(other);
        swap(tmp);
        return *this;
    }

    ADS_set &operator=(std::initializer_list<key_type> ilist)
    {

        ADS_set tmp{ilist};

        swap(tmp);
        return *this;
    }

    size_type size() const { return total; }  // PH1
    bool empty() const { return total == 0; } // PH1

    void insert(std::initializer_list<key_type> ilist) { insert(std::begin(ilist), std::end(ilist)); } // PH1

    template <typename InputIt>
    void insert(InputIt first, InputIt last)
    {
        if (first == last)
            return;

        for (auto it = first; it != last; ++it)
        {
            if (count(*it) == 0)
            {
                add(*it);
            }
        }
    }

    void clear()
    {
        for (auto &block : table)
        {
            if (block)
            {
                delete block;
                block = nullptr;
            }
        }

        table.clear();
        table_length = 8;
        d = 3;
        total = 0;
        nextToSplit = 0;
        table.resize(table_length);
        for (size_type i = 0; i < table_length; ++i)
        {
            table.push_back(new Block());
        }
    }

    size_type erase(const key_type &key)
    {
        size_type idx{h(key)};
        auto i = table[idx]->find(key);
        if (!i)
            return 0;
        // Block temp = new Block;
        MyVector<key_type> v;
        table[idx]->collect(v);
        table[idx]->clear_block();
        delete table[idx];
        // table[idx] = nullptr;
        table[idx] = new Block();
        for (const key_type &elem : v)
        {
            if (!key_equal{}(elem, key))
            {
                table[idx]->push_back(elem);
            }
        }
        total--;
        return 1;
    }

    size_type count(const key_type &key) const
    {
        if (empty())
            return 0;
        else if (locate(key) == true)
            return 1;
        return 0;
    } // PH1

    void swap(ADS_set &other) noexcept
    {
        using std::swap;
        swap(table, other.table);
        swap(table_length, other.table_length);
        swap(nextToSplit, other.nextToSplit);
        swap(capacity, other.capacity);
        swap(d, other.d);
        swap(total, other.total);
    }

    void dump([[maybe_unused]] std::ostream &o = std::cerr) const
    {
        for (size_type i{0}; i < table_length; i++)
        {
            if (i == nextToSplit)
            {
                o << "p->" << i << "-[";
            }
            else
                o << "   " << i << "-[";
            if (table[i] != nullptr && table[i]->count != 0)
                table[i]->block_print();
            o << "]";
            o << "\n";
        }
    }

    friend bool operator==(const ADS_set &lhs, const ADS_set &rhs)
    {
        if (lhs.total != rhs.total)
            return false;
        for (const auto &k : lhs)
            if (!rhs.count(k))
                return false;
        return true;
    }
    friend bool operator!=(const ADS_set &lhs, const ADS_set &rhs) { return !(lhs == rhs); }

    std::pair<iterator, bool> insert(const key_type &key)
    {

        size_type idx{h(key)};
        auto i = table[idx]->it_find(key);
        if (i.second != nullptr)
        {
            auto it = Iterator(i.first, idx, i.second, this);
            return std::make_pair(it, false);
        }
        add(key);
        size_type idx2{h(key)};
        auto i2 = table[idx2]->it_find(key);
        auto it = iterator(i2.first, idx2, i2.second, this);
        return std::make_pair(it, true);
    }

    iterator find(const key_type &key) const
    {

        size_type idx{h(key)};
        auto i = table[idx]->it_find(key);
        if (i.second == nullptr)
        {
            return Iterator(2, table_length, nullptr, this);
        }
        return Iterator(i.first, idx, i.second, this);
    }

    const_iterator begin() const
    {

        if (total == 0)
            return end();

        return const_iterator(0, 0, table[0], this);
    }
    const_iterator end() const
    {

        Block *endblock = table[table_length - 1];

        while (endblock->overflow)
        {
            endblock = endblock->overflow;
        }

        return const_iterator(2, table_length, nullptr, this);
    }
};

template <typename Key, size_t N>
class ADS_set<Key, N>::Iterator
{
private:
    size_type idx;
    size_type global_count;
    Block *curr;
    const ADS_set *ads;

    void skip()
    {
        // If the current block is not nullptr and the index is not at the end
        if ((idx == 0 && curr->count == 1) || (idx == 0 && curr->count == 2) || (idx == 1 && curr->count == 2))
        {
            return;
        }
        if (curr != nullptr)
        {

            // Move to the next index
            //++idx;
            // If the current block has an overflow, move to it and reset the index
            if (curr->overflow != nullptr)
            {
                curr = curr->overflow;
                idx = 0;
            }
            else
            {
                if (global_count != ads->table_length)
                {
                    // If the current block has no overflow and the index is at 2, move to the next non-empty block
                    ++global_count;
                    while (global_count < ads->table_length && ads->table[global_count]->count == 0)
                    {
                        ++global_count;
                    }
                    // If a non-empty block is found, update the current block and reset the index
                    if (global_count < ads->table_length)
                    {
                        curr = ads->table[global_count];
                        idx = 0;
                    }
                    else
                    {
                        // If all blocks are empty, set the current block to nullptr
                        curr = nullptr;
                    }
                }
            }
        }
    }

public:
    using value_type = Key;
    using difference_type = std::ptrdiff_t;
    using reference = const value_type &;
    using pointer = const value_type *;
    using iterator_category = std::forward_iterator_tag;

    explicit Iterator(size_type idx = 2, size_type global_count = 0, Block *curr = nullptr, const ADS_set *ads = nullptr) : idx(idx), global_count(global_count), curr(curr), ads(ads)
    {
        if (curr != nullptr && idx != 2)
        {
            skip();
        }
    }

    reference operator*() const
    {
        if (idx == 0 && curr != nullptr)
        {
            return curr->values[0];
        }
        else if (idx == 1 && curr != nullptr && curr->count == 2)
        {
            return curr->values[1];
        }
        throw std::runtime_error("Invalid dereference of iterator");
    }
    pointer operator->() const
    {
        if (idx == 0 && curr != nullptr)
        {
            return &curr->values[0];
        }
        else if (idx == 1 && curr != nullptr && curr->count == 2)
        {
            return &curr->values[1];
        }
        return nullptr;
    }

    Iterator &operator++()
    {
        if (curr != nullptr)
        {
            ++idx;
            skip();
        }
        return *this;
    }
    Iterator operator++(int)
    {
        auto copy = *this;
        ++(*this);
        return copy;
    }

    [[nodiscard]] bool is_end() const
    {

        return curr == nullptr && global_count == ads->table_length;
    }

    friend bool operator==(const Iterator &lhs, const Iterator &rhs)
    {
        if (lhs.is_end() && rhs.is_end())
        {
            return true;
        }
        return lhs.curr == rhs.curr && lhs.idx == rhs.idx;
    }
    friend bool operator!=(const Iterator &lhs, const Iterator &rhs)
    {
        return !(lhs == rhs);
    }
};

template <typename Key, size_t N>
void swap(ADS_set<Key, N> &lhs, ADS_set<Key, N> &rhs) noexcept { lhs.swap(rhs); }

#endif // ADS_SET_H