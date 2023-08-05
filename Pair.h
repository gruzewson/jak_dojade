#pragma once

template<typename T1, typename T2>
class MyPair 
{
public:
    MyPair() : first(T1()), second(T2()) {}
    MyPair(const T1& t1, const T2& t2) : first(t1), second(t2) {}

    T1 first;
    T2 second;
};
