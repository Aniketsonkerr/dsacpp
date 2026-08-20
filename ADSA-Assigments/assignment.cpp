#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

// 1. LINKED LIST
struct Node {
    int data;
    Node* next;
    Node(int val) {
        data = val;
        next = NULL;
    }
};

class LinkedList {
public:
    Node* head;
    
    LinkedList() {
        head = NULL;
    }

    void insert(int val) {
        Node* newNode = new Node(val);
        if (head == NULL) {
            head = newNode;
            return;
        }
        Node* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    bool search(int target) {
        Node* temp = head;
        while (temp != NULL) {
            if (temp->data == target) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    void remove(int target) {
        if (head == NULL) return;
        
        if (head->data == target) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }
        
        Node* temp = head;
        while (temp->next != NULL && temp->next->data != target) {
            temp = temp->next;
        }
        
        if (temp->next != NULL) {
            Node* toDelete = temp->next;
            temp->next = temp->next->next;
            delete toDelete;
        }
    }
};

// 2. STACK
class Stack {
    int* arr;
    int top;
    int capacity;
public:
    Stack(int cap) {
        capacity = cap;
        arr = new int[capacity];
        top = -1;
    }

    void push(int val) {
        if (top < capacity - 1) {
            top++;
            arr[top] = val;
        }
    }

    void pop() {
        if (top >= 0) {
            top--;
        }
    }
};

// 3. QUEUE
class Queue {
    int* arr;
    int front;
    int rear;
    int capacity;
public:
    Queue(int cap) {
        capacity = cap;
        arr = new int[capacity];
        front = 0;
        rear = -1;
    }

    void enqueue(int val) {
        if (rear < capacity - 1) {
            rear++;
            arr[rear] = val;
        }
    }

    void dequeue() {
        if (front <= rear) {
            front++;
        }
    }
};

// Function to test everything for a given input size N
void testDataStructures(int N) {
    cout << "\n--- Testing for Input Size N = " << N << " ---" << endl;

    // --- ARRAY (VECTOR) ---
    vector<int> arr;
    
    auto start = high_resolution_clock::now();
    for (int i = 0; i < N; i++) {
        arr.push_back(i);
    }
    auto stop = high_resolution_clock::now();
    double arrayInsert = duration_cast<microseconds>(stop - start).count() / 1000.0;

    start = high_resolution_clock::now();
    for (int i = 0; i < N; i++) {
        if (arr[i] == N - 1) break;
    }
    stop = high_resolution_clock::now();
    double arraySearch = duration_cast<microseconds>(stop - start).count() / 1000.0;

    start = high_resolution_clock::now();
    arr.erase(arr.begin() + N / 2);
    stop = high_resolution_clock::now();
    double arrayDelete = duration_cast<microseconds>(stop - start).count() / 1000.0;


    // --- LINKED LIST ---
    LinkedList list;

    start = high_resolution_clock::now();
    for (int i = 0; i < N; i++) {
        list.insert(i);
    }
    stop = high_resolution_clock::now();
    double listInsert = duration_cast<microseconds>(stop - start).count() / 1000.0;

    start = high_resolution_clock::now();
    list.search(N - 1);
    stop = high_resolution_clock::now();
    double listSearch = duration_cast<microseconds>(stop - start).count() / 1000.0;

    start = high_resolution_clock::now();
    list.remove(N / 2);
    stop = high_resolution_clock::now();
    double listDelete = duration_cast<microseconds>(stop - start).count() / 1000.0;


    // --- STACK ---
    Stack st(N);

    start = high_resolution_clock::now();
    for (int i = 0; i < N; i++) {
        st.push(i);
    }
    stop = high_resolution_clock::now();
    double stackPush = duration_cast<microseconds>(stop - start).count() / 1000.0;

    start = high_resolution_clock::now();
    for (int i = 0; i < N; i++) {
        st.pop();
    }
    stop = high_resolution_clock::now();
    double stackPop = duration_cast<microseconds>(stop - start).count() / 1000.0;


    // --- QUEUE ---
    Queue q(N);

    start = high_resolution_clock::now();
    for (int i = 0; i < N; i++) {
        q.enqueue(i);
    }
    stop = high_resolution_clock::now();
    double queueEnqueue = duration_cast<microseconds>(stop - start).count() / 1000.0;

    start = high_resolution_clock::now();
    for (int i = 0; i < N; i++) {
        q.dequeue();
    }
    stop = high_resolution_clock::now();
    double queueDequeue = duration_cast<microseconds>(stop - start).count() / 1000.0;

    // Printing output
    cout << "Array Insert: " << arrayInsert << " ms" << endl;
    cout << "Array Search: " << arraySearch << " ms" << endl;
    cout << "Array Delete: " << arrayDelete << " ms" << endl;
    
    cout << "Linked List Insert: " << listInsert << " ms" << endl;
    cout << "Linked List Search: " << listSearch << " ms" << endl;
    cout << "Linked List Delete: " << listDelete << " ms" << endl;
    
    cout << "Stack Push: " << stackPush << " ms" << endl;
    cout << "Stack Pop: " << stackPop << " ms" << endl;
    
    cout << "Queue Enqueue: " << queueEnqueue << " ms" << endl;
    cout << "Queue Dequeue: " << queueDequeue << " ms" << endl;
}

int main() {
    int sizes[] = {1000, 10000, 50000, 100000};

    for (int i = 0; i < 4; i++) {
        testDataStructures(sizes[i]);
    }

    return 0;
}