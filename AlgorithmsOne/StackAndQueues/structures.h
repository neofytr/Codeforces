#include <stdexcept>
using namespace std;

template <typename type> class Stack {
  private:
    struct Node {
        Node *next;
        type data;
        explicit Node(const type &data) {
            next = nullptr;
            this->data = data;
        }
    };
    Node *top;
    int sz;

  public:
    Stack() { top = nullptr, sz = 0; }
    ~Stack() {
        while (!isEmpty())
            pop();
    }
    bool isEmpty() const { return !sz; }
    int size() const { return sz; }

    void push(const type &data) {
        auto node = new Node(data);
        node->next = top, top = node, sz++;
    }

    type pop() {
        if (isEmpty())
            throw runtime_error("stack underflow!");
        auto tmp = top;
        auto data = top->data;
        top = top->next, delete tmp, sz--;
        return data;
    }

    class Iterator {
      private:
        Node *curr;

      public:
        explicit Iterator(Node *node) { curr = node; }
        type &operator*() { return curr->data; }
        Iterator &operator++() {
            curr = curr->next;
            return *this;
        }
        bool operator==(const Iterator &other) const { return curr == other.curr; }
    };

    Iterator begin() { return Iterator(top); }
    Iterator end() { return Iterator(nullptr); }
};

template <typename type> class Queue {
  private:
    struct Node {
        Node *next;
        type data;
        explicit Node(const type &data) {
            this->data = data;
            next = nullptr;
        }
    };
    Node *front, *back;
    int sz;

  public:
    Queue() { front = back = nullptr, sz = 0; }
    ~Queue() {
        while (!isEmpty())
            pop();
    }
    bool isEmpty() const { return !sz; }
    int size() const { return sz; }
    void push(const type &data) {
        auto node = new Node(data);
        if (isEmpty())
            front = back = node;
        else
            back->next = node, back = node;
        sz++;
    }
    type pop() {
        if (isEmpty())
            throw runtime_error("cannot pop from an empty queue!");
        const auto tmp = front;
        const auto data = tmp->data;
        front = front->next, delete tmp, sz--;
        if (isEmpty())
            back = front = nullptr;
        return data;
    }

    class Iterator {
      private:
        Node *curr;

      public:
        explicit Iterator(Node *node) { curr = node; }
        type &operator*() { return curr->data; }
        Iterator &operator++() {
            curr = curr->next;
            return *this;
        }
        bool operator==(const Iterator &other) const { return curr == other.curr; }
    };

    Iterator begin() { return Iterator(front); }
    Iterator end() { return Iterator(nullptr); }
};