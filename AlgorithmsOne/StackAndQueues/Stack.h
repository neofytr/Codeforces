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

template <typename T> class LinkedListStack : public Stack<T> {
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