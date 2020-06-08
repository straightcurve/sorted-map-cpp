#include "MapIterator.h"

#pragma region Constructors
template <typename K, typename V>
Map<K, V>::Map() {
    root = nullptr;
    count = 0;
}

template <typename K, typename V>
Map<K, V>::~Map() {
    clear();
}
#pragma endregion

#pragma region Public methods
template <typename K, typename V>
void Map<K, V>::add(K key, V value) {
    root = insert(key, value, root);
    count++;
}

template <typename K, typename V>
bool Map<K, V>::isEmpty() const {
    return root == nullptr;
}

template <typename K, typename V>
MapIterator<K, V> Map<K, V>::iterator() {
    return MapIterator<K, V>(*this);
}

template <typename K, typename V>
void Map<K, V>::remove(K key) {
    Node* node = root;
    Node* parent = nullptr;
    bool isLeftNode = false;

    if (node->key == key)
        return removeRoot();

    while (node->key != key) {
        if (key < node->key) {
            parent = node;
            node = node->left;
            isLeftNode = true;
        }
        else {
            parent = node;
            node = node->right;
            isLeftNode = false;
        }
    }

    //  1. leaf
    if (node->left == nullptr && node->right == nullptr) {
        if (isLeftNode)
            parent->left = nullptr;
        else
            parent->right = nullptr;
    }

    //  2. 2 children
    else if (node->left != nullptr && node->right != nullptr) {
        auto leftmost = node->right;
        while (leftmost->left != nullptr)
            leftmost = leftmost->left;

        remove(leftmost->key);

        leftmost->left = node->left;
        leftmost->right = node->right;

        if (isLeftNode)
            parent->left = leftmost;
        else
            parent->right = leftmost;
    }

    //  3. 1 child
    else {
        if (node->left != nullptr) {
            if (isLeftNode)
                parent->left = node->left;
            else
                parent->right = node->left;
        }
        else {
            if (isLeftNode)
                parent->left = node->right;
            else
                parent->right = node->right;
        }
    }

    count--;
}

template <typename K, typename V>
V Map<K, V>::search(K key) {
    // if (root == nullptr)
    //     return Node();

    return lookup(key, root)->value;
}

template <typename K, typename V>
int Map<K, V>::size() const {
    return count;
}
#pragma endregion

#pragma region Private methods
template <typename K, typename V>
void Map<K, V>::clear() {
    cleanUp(root);
}

template <typename K, typename V>
void Map<K, V>::cleanUp(Node*& node) {
    if (node == nullptr)
        return;

    cleanUp(node->left);
    cleanUp(node->right);
    delete node;
    node = nullptr;
}

template <typename K, typename V>
typename Map<K, V>::Node* Map<K, V>::insert(K& key, V& value, Node*& node) {
    if (node == nullptr)
        return new Node(key, value);

    if (key < node->key) {
        Node* left = insert(key, value, node->left);
        node->left = left;
        left->parent = node;
    }
    else if (key > node->key) {
        Node* right = insert(key, value, node->right);
        node->right = right;
        right->parent = node;
    }

    return node;
}

template <typename K, typename V>
typename Map<K, V>::Node* Map<K, V>::lookup(K key, Node*& node) {
    if (node == nullptr)
        return nullptr;

    if (key < node->key)
        return lookup(key, node->left);
    else if (key > node->key)
        return lookup(key, node->right);

    return node;
}

template <typename K, typename V>
void Map<K, V>::removeRoot() {
    //  1. leaf
    if (root->left == nullptr && root->right == nullptr) {
        root = nullptr;
    }

    //  2. 2 children
    else if (root->left != nullptr && root->right != nullptr) {
        auto leftmost = root->right;
        while (leftmost->left != nullptr)
            leftmost = leftmost->left;

        remove(leftmost->key);

        leftmost->left = root->left;
        leftmost->right = root->right;

        root = leftmost;
    }

    //  3. 1 child
    else {
        if (root->left != nullptr)
            root = root->left;
        else
            root = root->right;
    }
}
#pragma endregion

#include "Invoice.cpp"
template class Map<int, Invoice>;