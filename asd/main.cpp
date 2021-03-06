#include <string>
#include <iostream>
#include <assert.h>

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

    Node* root;
    int count;

    void clear() {
        cleanUp(root);
    }

    void cleanUp(Node*& node) {
        if (node == nullptr)
            return;

        cleanUp(node->left);
        cleanUp(node->right);
        delete node;
        node = nullptr;
    }

    Node* lookup(K key, Node*& node) {
        if (node == nullptr)
            return nullptr;

        if (key < node->key)
            return lookup(key, node->left);
        else if (key > node->key)
            return lookup(key, node->right);

        return node;
    }

    void removeRoot() {
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

    Node* insert(K& key, V& value, Node*& node) {
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

public:
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

    MapIterator<K, V> iterator() {
        return MapIterator<K, V>(*this);
    }

    void remove(K key) {
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

    V search(K key) {
        auto found = lookup(key, root);
        if(found == nullptr)
            return V();

        return found->value;
    }

    int size() const {
        return count;
    }
#pragma endregion
};

template<typename TItem>
struct Stack {
    static const int DEFAULT_SIZE = 30;

    TItem data[DEFAULT_SIZE];
    int head = -1;

    TItem back() {
        return data[head];
    }

    bool empty() {
        return head == -1;
    }

    void pop_back() {
        head--;
    }

    void push_back(TItem value) {
        data[++head] = value;
    }
};

template <typename K, typename V>
class MapIterator {
    friend class Map<K, V>;

    typedef std::pair<K, V> KeyValuePair;
    typedef typename Map<K, V>::Node Node;

private:
    const Map<K, V>& map;
    Stack<Node*> stack;
    Node* current;

public:
    MapIterator(const Map<K, V>& m) : map(m)
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

    bool valid() const {
        return current != nullptr;
    }

    KeyValuePair getCurrent() const {
        return KeyValuePair(current->key, current->value);
    }

    void next() {
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
};

struct Invoice {
    int id = -1;

    std::string name;
    int cost = 0;

    Invoice() {

    }

    Invoice(int _id, std::string _name, int _cost) {
        id = _id;
        name = _name;
        cost = _cost;
    }

    bool operator==(const Invoice& other) const
    {
        return (
            id == other.id &&
            name == other.name &&
            cost == other.cost
        );
    }
};

std::string getHeader(size_t suffix);
void callTests();

int main() {
    char op;
    Map<int, Invoice> map;
    while (true)
    {
        system("@cls||clear");
        std::cout 
            << "Please select an option: " << '\n' 
            << "[A] - Add an invoice" << '\n' 
            << "[R] - Remove an invoice" << '\n' 
            << "[S] - Search for an invoice" << '\n' 
            << "[L] - Load invoices" << '\n' 
            << "[D] - Display all invoices" << '\n' 
            << "[E] - Exit" << '\n'
            << "Operation: ";
        std::cin >> op;
        
        switch (op) {
        case 'a': {
            auto inv = new Invoice();
            std::cout << "ID: ";  std::cin >> inv->id;
            std::cout << "Name: ";  std::cin >> inv->name;
            std::cout << "Cost: "; std::cin >> inv->cost;
            map.add(inv->id, *inv);
            std::cout << "Successfully added the invoice." << std::endl;
            std::cin >> op;
            continue;
        }
        case 'd': {
            std::string output;
            size_t maxLength = 0;

            for (auto iter = map.iterator(); iter.valid(); iter.next())
            {
                auto p = iter.getCurrent();
                output += std::to_string(p.second.id);
                output += "\t";
                output += p.second.name;
                output += "\t";
                output += std::to_string(p.second.cost);
                output += "\n";

                if (p.second.name.length() > maxLength)
                    maxLength = p.second.name.length();
            }

            std::cout << getHeader(maxLength + 1) << std::endl;
            std::cout << output << std::endl;
            std::cin >> op;
            continue;
        }
        case 'r': {
            int k;
            std::cout << "ID: "; std::cin >> k;
            map.remove(k);
            std::cout << "Removed the specified invoice." << std::endl;
            std::cin >> op;
            continue;
        }
        case 's': {
            int k;
            std::cout << "ID: "; std::cin >> k;
            auto inv = map.search(k);
            if(inv.id == -1)
                std::cout << "Couldn't find the specified invoice." << std::endl;
            else {
                std::cout << getHeader(inv.name.length() + 1) << std::endl;
                std::cout << inv.id << "\t" << inv.name << "\t" << inv.cost << std::endl;
            }
            std::cin >> op;
            continue;
        }
        case 'l': {
            for (size_t i = 0; i < 5; i++)
            {
                auto invoice = Invoice();
                invoice.id = i + 100;
                invoice.name = "Factura " + std::to_string(invoice.id);
                invoice.cost = 20 + i;
                map.add(invoice.id, invoice);
            }
            break;
        }
        case 'e':
            exit(0);
        default:
            std::cout << "Unknown option." << '\n';
            break;
        }

        continue;
    }

    return 0;
}

std::string getHeader(size_t suffix) {
    std::string result = "#\tName";

    for (size_t i = 0; i < suffix; i++)
        result += " ";

    result += "Cost";

    return result;
}

void testAdd();
void testRemove();
void testSearch();
void testIsEmpty();
void testSize();
void testValid();

void callTests()
{
    testAdd();
    testRemove();
    testSearch();
    testIsEmpty();
    testSize();
    testValid();
}

void testAdd()
{
    Map<int, Invoice> sm;
    auto invoice1 = Invoice(1, "Factura1", 21);
    auto invoice2 = Invoice(2, "Factura2", 22);
    auto invoice3 = Invoice(3, "Factura3", 23);
    auto iterator = sm.iterator();
    sm.add(1, invoice1);
    assert(iterator.getCurrent() == std::make_pair(1, invoice1));

    sm.add(2, invoice2);
    iterator.next();
    assert(iterator.getCurrent() == std::make_pair(2, invoice2));
    
    sm.add(3, invoice3);
    iterator.next();
    assert(iterator.getCurrent() == std::make_pair(3, invoice3));
}

void testRemove()
{
    Map<int, Invoice> sm;
    auto invoice1 = Invoice(1, "Factura1", 21);
    auto invoice2 = Invoice(2, "Factura2", 22);
    auto invoice3 = Invoice(3, "Factura3", 23);
    auto iterator = sm.iterator();
    sm.add(1, invoice1);
    sm.add(2, invoice2);

    iterator.next();
    assert(iterator.getCurrent() == std::make_pair(2, invoice2));

    sm.remove(2);
    assert(iterator.getCurrent() == std::make_pair(1, invoice1));
}

void testSearch()
{
    Map<int, Invoice> sm;
    auto invoice1 = Invoice(1, "Factura1", 21);
    auto invoice2 = Invoice(2, "Factura2", 22);
    auto invoice3 = Invoice(3, "Factura3", 23);

    sm.add(1, invoice1);
    sm.add(2, invoice2);
    assert(sm.search(1) == invoice1);
    assert(sm.search(2) == invoice2);
}

void testIsEmpty()
{
    Map<int, Invoice> sm;
    assert(sm.isEmpty());
    auto invoice1 = Invoice(1, "Factura1", 21);
    auto invoice2 = Invoice(2, "Factura2", 22);
    assert(!sm.isEmpty());
    sm.remove(1);
    sm.remove(2);
    assert(sm.isEmpty());
}

void testSize()
{
    Map<int, Invoice> sm;
    auto invoice1 = Invoice(1, "Factura1", 21);
    auto invoice2 = Invoice(2, "Factura2", 22);
    auto invoice3 = Invoice(3, "Factura3", 23);
    assert(sm.size() == 0);
    sm.add(1, invoice1);
    sm.add(2, invoice2);
    assert(sm.size() == 2);
    sm.remove(1);
    sm.remove(2);
    assert(sm.size() == 0);
}

void testValid()
{
    Map<int, Invoice> sm;
    auto invoice1 = Invoice(1, "Factura1", 21);
    auto invoice2 = Invoice(2, "Factura2", 22);
    auto invoice3 = Invoice(3, "Factura3", 23);
    auto iterator = sm.iterator();
    assert(!iterator.valid());

    // sm.add(1, invoice1);
    // iterator = sm.iterator();
    // assert(iterator.valid());

    // sm.remove(1);
    // iterator = sm.iterator();
    // assert(iterator.valid());
}