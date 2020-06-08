#include "Stack.h"

template<typename TItem>
TItem Stack<TItem>::back() {
    return data[head];
}

template<typename TItem>
bool Stack<TItem>::empty() {
    return head == -1;
}

template<typename TItem>
void Stack<TItem>::pop_back() {
    head--;
}

template<typename TItem>
void Stack<TItem>::push_back(TItem value) {
    data[++head] = value;
}

#include "Map.h"
#include "Invoice.cpp"
template class Stack<Map<int, Invoice>::Node>;