#include <string>
#include <iostream>
#include <iterator>

template <typename K, typename V>
class Map {
    int count;

    public:
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

        Node* root;
        Map() {
            root = nullptr;
            count = 0;
        }

        ~Map() {
            clear();
        }

        void clear() {
            cleanUp(root);
        }
        
        void cleanUp(Node* &node) {
            if(node == nullptr) 
                return;

            cleanUp(node->left);
            cleanUp(node->right);
            delete node;
            node = nullptr;
        }

        void deleteNode(K key, Node* &node) {

        }

        void erase(K key) {
            root = deleteNode(key, root);
            count--;
        }

        V get(K key) {
            if(root == nullptr)
                return nullptr;

            return search(key, root);
        }

        Node* insert(K &key, V &value, Node* &node) {
            if(node == nullptr)
                return new Node(key, value);

            if(key < node->key) {
                Node* left = insert(key, value, node->left);
                node->left = left;
                left->parent = node;
            }
            else if(key > node->key) {
                Node* right = insert(key, value, node->right);
                node->right = right;
                right->parent = node;
            }

            return node;
        }
        
        bool isEmpty() const {
            return root == nullptr;
        }
        
        V search(K key, Node* &node) {
            if(node == nullptr)
                return nullptr;

            if(key < node->key)
                return search(key, node->left);
            else if(key > node->key) 
                return search(key, node->right);

            return node->value;
        }

        void set(K key, V value) {
            root = insert(key, value, root);
            count++;
        }

        int size() const {
            return count;
        }
};

#include <queue>

template <typename K, typename V>
class MapIterator {
    friend class Map<K, V>;

    typedef std::pair<K, V> KeyValuePair;
    typedef typename Map<K, V>::Node Node;

    private:
        const Map<K, V>& map;
        std::queue<Node*> stack;
        Node* current;

    public:
        MapIterator(const Map<K, V>& m): map(m)
        {
            // map = m;
            this->current = map.root;

            while(this->current != nullptr) {
                stack.push(this->current);
                this->current = this->current->left;
            }

            if(!stack.empty()) {
                this->current = stack.front();
                stack.pop();
            }
            else
                this->current = nullptr;
        }

        bool valid() const {
            return this->current != nullptr;
        }

        KeyValuePair getCurrent() const {
            return KeyValuePair(this->current->key, this->current->value);
        }

        void next() {
            this->current = stack.front();
            stack.pop();

            if(this->current->right != nullptr) {
                this->current = this->current->right;
                while(this->current != nullptr) {
                    this->stack.push(this->current);
                    this->current = this->current->left;
                }
            }
            
            if(stack.size()){
                this->current = stack.front();
                stack.pop();
            }
            else
                this->current = nullptr;
        }
};

#include <map>

int main() {

    Map<int, std::string> maplol;

    maplol.set(3, "Hello");
    maplol.set(15, "?");
    maplol.set(5, "World");
    maplol.set(8, "!");

    // map.delete(15);

    auto x = maplol.get(15);

    std::cout << x << std::endl;

    MapIterator<int, std::string> iter = MapIterator<int, std::string>(maplol);
    

    for (; iter.valid(); iter.next())
    {
        std::cout << iter.getCurrent().second << std::endl;
    }
    

    return 0;
}