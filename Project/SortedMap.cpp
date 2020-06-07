#include <string>
#include <iostream>
#include <iterator>

#include "SortedMap.h"
#include "SortedMapIterator.h"

template<typename K, typename V>
SortedMap<K, V>::Node::Node()
{
	left = nullptr;
	right = nullptr;
	parent = nullptr;
}

template<typename K, typename V>
SortedMap<K, V>::Node::Node(K _key, V _value)
{
	left = nullptr;
	right = nullptr;
	parent = nullptr;
	key = _key;
	value = _value;
}


//Node* root
template<typename K, typename V>
SortedMap<K, V>::SortedMap()
{
	root = nullptr;
	count = 0;
}

template<typename K, typename V>
SortedMap<K, V>::~SortedMap()
{
	clear();
}

template<typename K, typename V>
void SortedMap<K, V>::clear()
{
	cleanUp(root);
}

template<typename K, typename V>
void SortedMap<K, V>::cleanUp(Node*& node)
{
	if (node == nullptr)
		return;

	cleanUp(node->left);
	cleanUp(node->right);
	delete node;
	node = nullptr;
}

template<typename K, typename V>
void SortedMap<K, V>::deleteNode(K key, Node*& node)
{

}

template<typename K, typename V>
void SortedMap<K, V>::erase(K key)
{
	root = deleteNode(key, root);
	count--;
}

template<typename K, typename V>
V SortedMap<K, V>::get(K key)
{
	if (root == nullptr)
		return nullptr;

	return search(key, root);
}

template<typename K, typename V>
Node* SortedMap<K, V>::insert(K& key, V& value, Node*& node)
{
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

template<typename K, typename V>
bool SortedMap<K, V>::isEmpty() const
{
	return root == nullptr;
}

template<typename K, typename V>
V SortedMap<K, V>::search(K key, Node*& node)
{
	if (node == nullptr)
		return nullptr;

	if (key < node->key)
		return search(key, node->left);
	else if (key > node->key)
		return search(key, node->right);

	return node->value;
}

template<typename K, typename V>
void SortedMap<K, V>::set(K key, V value)
{
	root = insert(key, value, root);
	count++;
}

template<typename K, typename V>
int SortedMap<K, V>::size() const
{
	return count;
}