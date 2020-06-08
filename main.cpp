#include <string>
#include <iostream>
#include <iterator>
#include <vector>

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

        #pragma region Public methods
        void add(K key, V value) {
            root = insert(key, value, root);
            count++;
        }

        bool isEmpty() const {
            return root == nullptr;
        }

        void remove(K key) {
            Node* node = root;
            Node* parent = nullptr;
            bool isLeftNode = false;

            if(node->key == key)
                return removeRoot();

            while(node->key != key) {
                if(key < node->key) {
                    parent = node;
                    node = node->left;
                    isLeftNode = true;
                } else {
                    parent = node;
                    node = node->right;
                    isLeftNode = false;
                }
            }
            
            //  1. leaf
            if(node->left == nullptr && node->right == nullptr) {
                if(isLeftNode)
                    parent->left = nullptr;
                else
                    parent->right = nullptr;
            }

            //  2. 2 children
            else if(node->left != nullptr && node->right != nullptr) {
                auto leftmost = node->right;
                while(leftmost->left != nullptr)
                    leftmost = leftmost->left;

                remove(leftmost->key);

                leftmost->left = node->left;
                leftmost->right = node->right;

                if(isLeftNode)
                    parent->left = leftmost;
                else
                    parent->right = leftmost;
            }

            //  3. 1 child
            else {
                if(node->left != nullptr) {
                    if(isLeftNode)
                        parent->left = node->left;
                    else
                        parent->right = node->left;
                } else {
                    if(isLeftNode)
                        parent->left = node->right;
                    else
                        parent->right = node->right;
                }
            }

            count--;
        }

        V search(K key) {
            if(root == nullptr)
                return nullptr;

            return lookup(key, root)->value;
        }

        int size() const {
            return count;
        }
        #pragma endregion

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

        Node* lookup(K key, Node* &node) {
            if(node == nullptr)
                return nullptr;

            if(key < node->key)
                return lookup(key, node->left);
            else if(key > node->key) 
                return lookup(key, node->right);

            return node;
        }

        void removeRoot() {
            //  1. leaf
            if(root->left == nullptr && root->right == nullptr) {
                root = nullptr;
            }

            //  2. 2 children
            else if(root->left != nullptr && root->right != nullptr) {
                auto leftmost = root->right;
                while(leftmost->left != nullptr)
                    leftmost = leftmost->left;

                remove(leftmost->key);

                leftmost->left = root->left;
                leftmost->right = root->right;

                root = leftmost;
            }

            //  3. 1 child
            else {
                if(root->left != nullptr)
                    root = root->left;
                else
                    root = root->right;
            }
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
};

template <typename K, typename V>
class MapIterator {
    friend class Map<K, V>;

    typedef std::pair<K, V> KeyValuePair;
    typedef typename Map<K, V>::Node Node;

    private:
        const Map<K, V>& map;
        std::vector<Node*> stack;
        Node* current;

    public:
        MapIterator(const Map<K, V>& m): map(m)
        {
            current = map.root;
            while(current != nullptr) {
                stack.push_back(current);
                current = current->left;
            }

            if(!stack.empty()) {
                current = stack.back();
                stack.pop_back();
            } else
                current = nullptr;
        }

        bool valid() const {
            return current != nullptr;
        }

        KeyValuePair getCurrent() const {
            return KeyValuePair(current->key, current->value);
        }

        void next() {
            if(current->right != nullptr) {
                current = current->right;

                while(current != nullptr) {
                    stack.push_back(current);
                    current = current->left;
                }
            }

            if(!stack.empty()) {
                current = stack.back();
                stack.pop_back();
            } else
                current = nullptr;
        }
};

struct Invoice {
    int id;

    std::string name;
    int cost;
};

std::string getHeader(int suffix) {
    std::string result = "#\tName";

    for (size_t i = 0; i < suffix; i++)
        result += " ";

    result += "Cost";

    return result;
}

int main() {
    // #    Name                    Cost    Other stuff..
    // 23  Factura pentru circ      120     ashduah
    // 23  Factura pentru circ      120     ashduah
    // 23  Factura pentru circ      120     ashduah
    // 23  Factura pentru circ      120     ashduah

    Map<int, Invoice> map;
    for (size_t i = 0; i < 10; i++)
    {
        auto invoice = Invoice();
        invoice.id = i + 100;
        invoice.name = "Factura " + std::to_string(invoice.id);
        invoice.cost = 20 + i;
        map.add(invoice.id, invoice);
    }
    
    MapIterator<int, Invoice> iter = MapIterator<int, Invoice>(map);
    
    std::string output;
    int maxLength = 0;

    for (; iter.valid(); iter.next())
    {
        auto p = iter.getCurrent();
        output += std::to_string(p.second.id);
        output += "\t";
        output += p.second.name;
        output += "\t";
        output += std::to_string(p.second.cost);
        output += "\n";

        if(p.second.name.length() > maxLength)
            maxLength = p.second.name.length();
    }

    std::cout << getHeader(maxLength + 1) << std::endl;
    std::cout << output << std::endl;

    return 0;
}