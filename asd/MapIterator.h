#pragma once

#include "Map.h"
#include "Stack.h"
#include <utility>

template <typename K, typename V>
class MapIterator {
    friend class Map<K, V>;

    typedef std::pair<K, V> KeyValuePair;
    typedef typename Map<K, V>::Node Node;

    const Map<K, V>& map;
    Stack<Node*> stack;
    Node* current;

public:
    MapIterator(const Map<K, V>& m);
    bool valid() const;
    KeyValuePair getCurrent() const;
    void next();
};