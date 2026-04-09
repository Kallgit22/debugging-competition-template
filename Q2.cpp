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
    ~Cache() {} 
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
        head->next = node; 
        head->next->prev = node; 
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
        }
        if (map.size() == capacity) {
            map.erase(tail->prev->key);
            removeNode(tail->prev);
        }
        Node* newNode = new Node(key, value);
        insertAtHead(newNode);
        map[key] = newNode;
    }
};

int main() {
    Cache* lru = new LRUCache(2);
    lru->put(1, 10);
    lru->put(2, 20);
    cout << "Get 1: " << lru->get(1) << endl; 
    lru->put(3, 30); 
    cout << "Get 2: " << lru->get(2) << endl; 
    
    delete lru; 
    return 0;
}
