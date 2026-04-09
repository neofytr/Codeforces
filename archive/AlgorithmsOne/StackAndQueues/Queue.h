#include <stdexcept>
using namespace std;

// Queue
// front -> [x1, x2, x3, ..., xn} <- back
// enqueue -> insertion at back
// dequeue -> removal from front

template <typename T> class Queue {
  public:
    virtual ~Queue() = default;
    virtual void enqueue(const T &data) = 0;
    virtual T dequeue() = 0;
    virtual bool isEmpty() const = 0;
    virtual int size() const = 0;
};

/*
Minimal requirements for an iterator to work with range-based for loops:
1. begin() and end() methods in the container; These must return iterators.

Iterator class must implement:
1. operator*() → for dereferencing
2. operator++() → for incrementing
3. operator!=() (or operator==()) → for comparison

operator*() can return T&, const T&, or even T depending on what behavior you want (mutable, const, or by copy).
operator++() should return either Iterator& (pre-increment) or Iterator (post-increment), but pre-increment is enough for range-based loops.
operator!=() is required by the loop. If you define operator==(), you should also define operator!=(), or vice versa.
*/

template <typename T> class LinkedListQueue final : public Queue<T> {
  private:
    struct Node {
        Node *next;
        T data;
        explicit Node(const T &data) {
            this->data = data;
            next = nullptr;
        }
    };
    Node *front, *back;
    int sz;

  public:
    LinkedListQueue() { sz = 0, front = back = nullptr; }
    ~LinkedListQueue() override {
        while (!isEmpty())
            dequeue();
    }
    void enqueue(const T &data) override {
        auto node = new Node(data);
        if (isEmpty())
            front = back = node;
        else
            back->next = node, back = node;
        sz++;
    }
    T dequeue() override {
        if (isEmpty())
            throw runtime_error("cannot dequeue from an empty queue!");
        const auto tmp = front;
        const auto data = tmp->data;
        front = front->next, sz--;
        if (isEmpty())
            back = front = nullptr;
        delete tmp;
        return data;
    }
    bool isEmpty() const override { return !sz; }
    int size() const override { return sz; }

    class Iterator {
      private:
        Node *curr;

      public:
        explicit Iterator(Node *node) { curr = node; }
        // de-reference operator
        // the operator*() must return a reference, otherwise we won't be able to iterate over references at all
        // whether the loop variable is a copy or reference depends entirely on how its declared (T vs T&)
        T &operator*() { return curr->data; }
        // pre-increment
        Iterator &operator++() {
            curr = curr->next;
            return *this;
        }
        // unequal
        bool operator!=(const Iterator &other) const { return curr != other.curr; }
    };

    Iterator begin() { return Iterator(front); }
    static Iterator end() { return Iterator(nullptr); }
};
