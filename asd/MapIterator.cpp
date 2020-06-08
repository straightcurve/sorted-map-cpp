
#include "MapIterator.h"
#include "Map.h"

template <typename K, typename V>
MapIterator<K, V>::MapIterator(const Map<K, V>& m) : map(m)
{
    current = map.root;
    while (current != nullptr) {
        stack.push_back(current);
        current = current->left;
    }

    if (!stack.empty()) {
        current = stack.back();
        stack.pop_back();
    }
    else
        current = nullptr;
}

template <typename K, typename V>
bool MapIterator<K, V>::valid() const {
    return current != nullptr;
}

template <typename K, typename V>
typename MapIterator<K, V>::KeyValuePair MapIterator<K, V>::getCurrent() const {
    return KeyValuePair(current->key, current->value);
}

template <typename K, typename V>
void MapIterator<K, V>::next() {
    if (current->right != nullptr) {
        current = current->right;

        while (current != nullptr) {
            stack.push_back(current);
            current = current->left;
        }
    }

    if (!stack.empty()) {
        current = stack.back();
        stack.pop_back();
    }
    else
        current = nullptr;
}

#include "Invoice.cpp"
template class MapIterator<int, Invoice>;