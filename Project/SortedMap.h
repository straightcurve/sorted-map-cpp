#pragma once

#include <string>
#include <iostream>
#include <iterator>

template <typename K, typename V>
class SortedMap
{
    int count;

    public:
        class Node {
        public:
            Node* left;
            Node* right;
            Node* parent;
            K key;
            V value;

            Node();
            Node(K _key, V _value);
        };

        SortedMap();
        ~SortedMap();

        void clear();
        void cleanUp(Node*& node);
        void deleteNode(K key, Node*& node);
        void erase(K key);
        V get(K key);
        Node* insert(K& key, V& value, Node*& node);
        bool isEmpty() const;
        V search(K key, Node*& node);
        void set(K key, V value);
        int size() const;
};