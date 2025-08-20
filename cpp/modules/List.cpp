module;
export module List;

import Container;
import <cstddef>;

struct Node {
    Node(struct Node *nxt, const double d) {
        this->next = nxt;
        this->data = d;
    }
    struct Node *next;
    double data;
};

// a linked list implementation
export class List final : public Container {
  public:
    List() {
        head = new Node(nullptr, -1);
        this->sz = 0;
    }
    [[nodiscard]] size_t size() const override { return this->sz; }
    double &operator[](const size_t index) override {
        Node *node = head;
        for (size_t i = 0; i <= index; i++)
            node = node->next;
        return node->data;
    }
    const double &operator[](const size_t index) const override {
        const Node *node = head;
        for (size_t i = 0; i <= index; i++)
            node = node->next;
        return node->data;
    }
    ~List() override {
        const Node *start = head;
        while (start) {
            const Node *tmp = start->next;
            delete start;
            start = tmp;
        }
        sz = 0;
        head = nullptr;
    }

  private:
    struct Node *head;
    size_t sz{};
};