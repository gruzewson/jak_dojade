#include "String.h"

String::String() : string(nullptr), size(0) {}

String::String(const char* s) 
{
    int len = 0;
    while (s[len] != '\0') 
    {
        len++;
    }
    size = len;
    string = new char[size + 1];
    for (int i = 0; i < size; i++) 
    {
        string[i] = s[i];
    }
    string[size] = '\0';
}

// Copy constructor
String::String(const String& other) : size(other.size) 
{
    string = new char[size + 1];
    for (int i = 0; i < size; i++) 
    {
        string[i] = other.string[i];
    }
    string[size] = '\0';
}

// Move constructor
String::String(String&& other) : string(other.string), size(other.size) 
{
    other.string = nullptr;
    other.size = 0;
}

String::~String() 
{
    delete[] string;
}

std::ostream& operator<<(std::ostream& os, const String& str)
{
    os << str.string;
    return os;
}

String& String::operator=(const String& other) 
{
    if (this != &other)
    {
        delete[] string;
        size = other.size;
        string = new char[size + 1];
        for (int i = 0; i < size; i++) 
        {
            string[i] = other.string[i];
        }
        string[size] = '\0';
    }
    return *this;
}

void String::operator+=(const char rhs) 
{
    int newSize = size + 1;
    char* temp = new char[newSize + 1] {};
    for (int i = 0; i < size; i++)
    {
        temp[i] = this->string[i];
    }
    temp[size] = rhs;
    temp[newSize] = '\0';
    size = newSize;
    delete string;
    string = temp;
}

String String::operator+(const String& other) const 
{
    int newSize = size + other.size;
    char* temp = new char[newSize + 1] {};
    for (int i = 0; i < size; i++) {
        temp[i] = string[i];
    }
    for (int i = size; i < newSize; i++) 
    {
        temp[i] = other.string[i - size];
    }
    temp[newSize] = '\0';
    String result(temp);
    delete[] temp;
    return result;
}

bool String::operator==(const String& other) const 
{
    if (size != other.size) 
    {
        return false;
    }
    for (int i = 0; i < size; i++) 
    {
        if (string[i] != other.string[i]) 
        {
            return false;
        }
    }
    return true;
}

bool String::operator!=(const String& other) const 
{
    return !(*this == other);
}

int String::toInt(const String& other)
{
    int newInt = 0;
    for (int i = 0; i < size; i++)
    {
        if (string[i] >= '0' && string[i] <= '9')
        {
            newInt = newInt * 10 + (string[i] - '0');
        }
    }
    return newInt;
}