#include <iostream>

template<typename T>
class Vector 
{
private:
    T* data_ = nullptr;
    int capacity_ = 0;
    int size_ = 0;

public:
    Vector();
    ~Vector();

    int size() const;
    void popback();
    void insert(T value, int index);
    void add(T value);
    void clear();

    T& operator[](int index);
    const T& operator[](int index) const;
};

template<typename T>
Vector<T>::Vector() : data_(nullptr), capacity_(0), size_(0) {}

template<typename T>
Vector<T>::~Vector()
{
    delete[] data_;
}

template<typename T>
int Vector<T>::size() const
{
    return size_;
}

template<typename T>
void Vector<T>::popback()
{
    if (size_ > 0)
    {
        size_--;
    }
}

template<typename T>
void Vector<T>::insert(T value, int index)
{
    if (size_ == capacity_)
    {
        capacity_ = (capacity_ == 0 ? 1 : capacity_ * 2);
        T* new_data = new T[capacity_];
        for (int i = 0; i < index; i++)
        {
            new_data[i] = data_[i];
        }
        new_data[index] = value;
        for (int i = index; i < size_; i++)
        {
            new_data[i + 1] = data_[i];
        }
        delete[] data_;
        data_ = new_data;
    }
    else {
        for (int i = size_; i > index; i--)
        {
            data_[i] = data_[i - 1];
        }
        data_[index] = value;
    }

    size_++;
}

template<typename T>
void Vector<T>::add(T value)
{
    insert(value, size_);
}

template<typename T>
void Vector<T>::clear()
{
    delete[] data_;
    data_ = nullptr;
    capacity_ = 0;
    size_ = 0;
}

template<typename T>
T& Vector<T>::operator[](int index)
{
    return data_[index];
}

template<typename T>
const T& Vector<T>::operator[](int index) const
{
    return data_[index];
}
