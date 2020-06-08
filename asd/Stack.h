#pragma once

template<typename TItem>
struct Stack {
    static const int DEFAULT_SIZE = 30;
    
    TItem data[DEFAULT_SIZE];
    int head = -1;

    TItem back();
    bool empty();
    void pop_back();
    void push_back(TItem value);
};