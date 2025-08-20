module;
export module List;
import Container;
import <cstddef>;

struct Node {
    Node(Node *nxt, const double d) : next(nxt), data(d) {}
    Node *next;
    double data;
};

export class List final : public Container {
  public:
    List(); // defined outside
    [[nodiscard]] size_t size() const override { return sz; }

    double &operator[](size_t index) override;             // defined outside
    const double &operator[](size_t index) const override; // defined outside

    ~List() override;
    // This derived destructor will implicitly call the base class destructor at the end.
    // So, the base class destructor needs to be defined to atleast something (default, for example)

  private:
    Node *head;
    size_t sz{};
};

inline List::List() {
    head = new Node(nullptr, -1); // dummy head node
    sz = 0;
}

inline double &List::operator[](const size_t index) {
    Node *node = head;
    for (size_t i = 0; i <= index; i++)
        node = node->next;
    return node->data;
}

inline const double &List::operator[](const size_t index) const {
    const Node *node = head;
    for (size_t i = 0; i <= index; i++)
        node = node->next;
    return node->data;
}

inline List::~List() {
    const Node *start = head;
    while (start) {
        const Node *tmp = start->next;
        delete start;
        start = tmp;
    }
    sz = 0;
    head = nullptr;
}
