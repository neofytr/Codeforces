#include <iostream>
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

// Stack applications
// 1. Parsing in a compiler
// 2. Java virtual machine
// 3. Undo in a word processor
// 4. Back button in a Web Browser
// 5. PostScript language for printers
// 6. Implementing function calls in a compiler, ... and so on

// Function Calls
// How a compiler implements a function?
// Function Call : push local environment and return address
// Return : pop return address and local environment

// Recursive function -> function that calls itself
// Note -> can always use an explicit stack to remove recursion

int main() {
    Stack<char> ops;
    Stack<int> vals;

    cout << "Enter expression: ";
    string line;
    getline(cin, line);
    istringstream iss(line);
    string token;

    while (iss >> token) {
        if (token == "(") {
        } else if (token == "+" || token == "*") {
            ops.push(token[0]);
        } else if (token == ")") {
            const char op = ops.pop();
            const int v2 = vals.pop();
            const int v1 = vals.pop();
            int result = 0;
            if (op == '+') {
                result = v1 + v2;
            } else if (op == '*') {
                result = v1 * v2;
            }
            vals.push(result);
        } else {
            vals.push(stoi(token));
        }
    }

    if (!vals.isEmpty()) {
        cout << "Result: " << vals.pop() << endl;
    } else {
        cout << "No expression evaluated." << endl;
    }

    return 0;
}
