#include <stdexcept>
#include <string>
using namespace std;

template <typename T> class Stack {
  public:
    virtual ~Stack() = default; // add the default destructor
    virtual void push(T &data) = 0;
    virtual T pop() = 0;
    virtual bool isEmpty() const = 0;
    virtual int size() const = 0;
    ;
};

// Proposition -> Every operation takes constant time in the worst case
template <typename T> class LinkedListStack final : public Stack<T> {
  private:
    struct Node {
        T data;
        Node *next;
        explicit Node(const T &data) { this->data = data, next = nullptr; } // this is a copy assignment, the struct will hold its own copy of data
    };
    Node *head;
    int sz;

  public:
    LinkedListStack() {
        sz = 0;
        head = nullptr;
    }
    ~LinkedListStack() override {
        while (!isEmpty())
            pop();
    }
    void push(T &data) override {
        Node *node = new Node(data);
        node->next = head, head = node, sz++;
    }
    T pop() override {
        if (isEmpty())
            throw runtime_error("illegal operation -> popping from an empty stack!");
        const T data = head->data;
        const auto newHead = head->next;
        delete head, head = newHead;
        return data;
    }
    bool isEmpty() const override { return !sz; }
    int size() const override { return sz; }
};

// Array implementation of a stack
template <typename T> class ArrayStack final : public Stack<T> {
  private:
    T *st;
    int top, cap;

  public:
    explicit ArrayStack(const int capacity) {
        st = new T[capacity];
        top = 0, cap = capacity;
    }
    ~ArrayStack() override { delete st; }

    int size() const override { return top; }
    bool isEmpty() const override { return !top; }
    void push(const T &data) override {
        if (top >= cap)
            throw runtime_error("invalid operation -> stack overflow");
        st[top++] = data;
    }
    T pop() override {
        if (isEmpty())
            throw runtime_error("invalid operation -> cannot pop from an empty stack!");
        return st[--top];
    }
};

/*
 * Stack Considerations
 * 1. Underflow -> throw exception if popping from an empty stack
 * 2. Overflow -> use resizing arrays for array implementation to dynamically increase the stack capacity at runtime
 * 3. Null items -> we allow null items to be inserted
 * 4. Loitering -> holding a reference to an object when it's no longer needed
 */

// Requiring the client to provide capacity does not implement the API!
// How to grow and shrink array?
// First try ->
// 1. push() -> increase size of array by 1
// 2. pop() -> decrease size of array by 1

// This is too expensive!
// 1. Need to copy all items to a new array when resizing
// 2. Inserting first N items takes time ~ (1 + (1 + 1) + (2 + 1) + (3 + 1) + ... + (N - 1 + 1)) ~ N^2 / 2
// we ignore the cost to create arrays but consider the cost to copy elements
// initially, the array is of size 1; pushing the first element takes only 1 operation;
// pushing the next element creates an array of size (1 + 1) = 2; this involves copying all the old elements
// into a new array of size 2 and then inserting the new element, a total cost of 2 operations
// and so on...

// How to grow array?
// If the array is full, create a new array of twice the size, and copy items
// Initially, make the array be of size 1
// Inserting the first N items takes time ~ (N + 2^0 + 2^1 + 2^2 + ... 2^(logN)) ~ (N + (2 ^ (logN + 1) - 1)) ~ 3N
// So the amortized wost case time for each insertion is constant
// we ignore the cost to create the arrays but consider the cost to copy elements
// since we are inserting N elements, we have cost N for these insertions
// also, every time the array size reaches a power of 2, we double its size and copy elements
// so, for each 2^r < N, we copy 2^r elements, incurring a cost of 2^r everytime

// How to shrink array?
// Efficient Solution ->
// 1. push() -> double size of array when its full
// 2. pop() -> halve size of array when array is one-quarter full
// Invariant -> array is always between 25% and 100% full
// Invariant -> every time you resize, you've already paid for it in an amortized sense by pushing or popping

// Amortized Analysis
// Average running time per operation over a worst-case sequence of operations
// Proposition -> starting from an empty stack, any sequence of M push and pop operations takes time proportional to M

// operation        best          worst         amortized
// construct        1               1               1
// push             1               N               1
// pop              1               N               1
// size             1               1               1

// Resizing array v/s linked list
// Tradeoffs ->
// Can implement a stack with either resizing array or linked list; client can use interchangeably
// Which one is better?

// Linked-list implementation
// 1. Every operation takes constant time in the worst case
// 2. Uses extra time and space to deal with the links

// Resizing array implementation
// 1. Every operation takes constant amortized time
// 2. Less wasted space

template <typename T> class ResizingArrayStack final : public Stack<T> {
  private:
    T *st;
    int cap;
    int top;

    void resize(const int newCap) {
        cap = newCap;
        T *newSt = new T[cap];
        for (int r = 0; r < top; r++)
            newSt[r] = st[r];
        delete st;
        st = newSt;
    }

  public:
    ResizingArrayStack() {
        st = new T[1];
        cap = 1;
        top = 0;
    }
    ~ResizingArrayStack() override { delete st; }
    void push(const T &data) override {
        if (top >= cap)
            resize(cap << 1);
        st[top++] = data;
    }
    T pop() override {
        if (isEmpty())
            throw runtime_error("invalid operation -> stack underflow!");
        if (top == cap / 4)
            resize(cap / 2);
        return st[--top];
    }
    bool isEmpty() const override { return !top; }
};