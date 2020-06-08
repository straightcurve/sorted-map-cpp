#pragma once

#include "Stack.h"
template <typename K, typename V>
class MapIterator;

template <typename K, typename V>
class Map {
    friend class MapIterator<K, V>;

    class Node {
    public:
        Node* left;
        Node* right;
        Node* parent;
        K key;
        V value;

        Node() {
            left = nullptr;
            right = nullptr;
            parent = nullptr;
        }

        Node(K _key, V _value) {
            left = nullptr;
            right = nullptr;
            parent = nullptr;
            key = _key;
            value = _value;
        }
    };

    friend class Stack<Node>;
    Node* root;
    int count;

    void clear();
    void cleanUp(Node*& node);
    Node* insert(K& key, V& value, Node*& node);
    Node* lookup(K key, Node*& node);
    void removeRoot();

public:
    Map();
    ~Map();

    void add(K key, V value);
    bool isEmpty() const;
    MapIterator<K, V> iterator();
    void remove(K key);
    V search(K key);
    int size() const;
};