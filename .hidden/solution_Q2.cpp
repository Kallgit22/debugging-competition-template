#include <iostream>
#include <unordered_map>
using namespace std;

class Node {
public:
    int key, value;
    Node* prev;
    Node* next;
    Node(int k, int v) : key(k), value(v), prev(NULL), next(NULL) {}
};

class Cache {
protected:
    int capacity;
public:
    Cache(int cap) { capacity = cap; }
    virtual void put(int key, int value) = 0;
    virtual int get(int key) = 0;
    // FIX 1: Virtual destructor to ensure subclass memory is cleaned up
    virtual ~Cache() {} 
};

class LRUCache : public Cache {
    Node* head;
    Node* tail;
    unordered_map<int, Node*> map;

    void removeNode(Node* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    void insertAtHead(Node* node) {
        node->next = head->next;
        node->prev = head;
        // FIX 2: Order of operations corrected to maintain Doubly Linked List integrity
        head->next->prev = node; 
        head->next = node; 
    }

public:
    LRUCache(int cap) : Cache(cap) {
        head = new Node(-1, -1);
        tail = new Node(-1, -1);
        head->next = tail;
        tail->prev = head;
    }

    int get(int key) override {
        if (map.find(key) == map.end()) return -1;
        Node* resNode = map[key];
        removeNode(resNode);
        insertAtHead(resNode);
        return resNode->value;
    }

    void put(int key, int value) override {
        if (map.find(key) != map.end()) {
            Node* existingNode = map[key];
            map.erase(key);
            removeNode(existingNode);
            delete existingNode; // FIX 3: Prevent memory leak by deleting the old node
        }
        if (map.size() >= capacity) {
            Node* lruNode = tail->prev;
            map.erase(lruNode->key);
            removeNode(lruNode);
            delete lruNode; // FIX 3: Prevent memory leak by deleting evicted node
        }
        Node* newNode = new Node(key, value);
        insertAtHead(newNode);
        map[key] = newNode;
    }

    // FIX 4: Subclass destructor to clean up remaining nodes
    ~LRUCache() override {
        Node* curr = head;
        while (curr != NULL) {
            Node* nextNode = curr->next;
            delete curr;
            curr = nextNode;
        }
    }
};

int main() {
    Cache* lru = new LRUCache(2);
    lru->put(1, 10);
    lru->put(2, 20);
    cout << "Get 1: " << lru->get(1) << endl; // Prints 10
    lru->put(3, 30); // Evicts key 2
    cout << "Get 2: " << lru->get(2) << endl; // Prints -1
    
    delete lru; 
    return 0;
}
