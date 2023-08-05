#pragma once
#include <iostream>

class String {
private:
    char* string;
    int size;
public:
    String();

    // Parameterized constructor
    String(const char* s);

    // Copy constructor
    String(const String& other);

    // Move constructor
    String(String&& other);

    ~String();

    friend std::ostream& operator<<(std::ostream& os, const String& str);
    
    String& operator=(const String& other);
    void operator+=(const char rhs);
    String operator+(const String& other) const;
    bool operator==(const String& other) const;
    bool operator!=(const String& other) const;

    int toInt(const String& other);
};
