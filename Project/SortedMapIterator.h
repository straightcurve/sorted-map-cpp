#pragma once

#include <queue>
#include <iterator>
#include "SortedMap.h"

template <typename K, typename V>
class SortedMapIterator
{
    friend class SortedMap<K, V>;

    typedef std::pair<K, V> KeyValuePair;
    typedef typename SortedMap<K, V>::Node Node;

    private:
        const SortedMap<K, V>& map;
        std::queue<Node*> stack;
        Node* current;

    public:
        SortedMapIterator(const SortedMap<K, V>& m) : map(m);
        bool valid() const;
        KeyValuePair getCurrent() const;
        void next();
 };