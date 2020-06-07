#include <queue>
#include <string>
#include <iostream>
#include <map>

#include "SortedMap.h"
#include "SortedMapIterator.h"

template<typename K, typename V>
SortedMapIterator<K, V>::SortedMapIterator(const SortedMap<K, V>& m)
{
    // map = m;
    this->current = map.root;

    while (this->current != nullptr) {
        stack.push(this->current);
        this->current = this->current->left;
    }

    if (!stack.empty()) {
        this->current = stack.front();
        stack.pop();
    }
    else
        this->current = nullptr;
}

template<typename K, typename V>
bool SortedMapIterator<K, V>::valid() const
{
    return this->current != nullptr;
}

template<typename K, typename V>
KeyValuePair SortedMapIterator<K, V>::getCurrent() const
{
    return KeyValuePair(this->current->key, this->current->value); return KeyValuePair();
}

template<typename K, typename V>
void SortedMapIterator<K, V>::next()
{
    this->current = stack.front();
    stack.pop();

    if (this->current->right != nullptr) {
        this->current = this->current->right;
        while (this->current != nullptr) {
            this->stack.push(this->current);
            this->current = this->current->left;
        }
    }

    if (stack.size()) {
        this->current = stack.front();
        stack.pop();
    }
    else
        this->current = nullptr;
}
