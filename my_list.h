#ifndef my_list_H
#define my_list_H
#include <memory.h>
#include <iostream>

template <typename T, typename A = std::allocator<T>>
class MyList {
public:
    struct Node {
        T data;
        Node * next;
    };

    MyList(A allocator = A());
    ~MyList();

    bool is_empty() {
        return head == nullptr;
    }

    void insert(const T& data);

    void remove_first();
    void remove_last();
    void remove(const T& _data);
    void print();
    Node* find(const T& _data);
    Node* operator[] (const int index);

    class Iterator{
    public:
        Iterator(MyList* list): parent(list), ptr(list->head){}

        void operator ++ ()
        {
            if (ptr != nullptr)
                ptr = ptr->next;
        }

        typename MyList::Node& operator * ()
        {
            return *ptr;
        }

        typename MyList::Node* operator -> ()
        {
            return ptr;
        }

        bool IsEnd() const
        {
            return ptr == nullptr;
        }

    private:
        MyList* parent;
        typename MyList::Node* ptr;
    };

    friend class Iterator;
private:
    Node * head;
    Node * tail;

    void Destroy(Node* node);

    using AllocatorTraits = std::allocator_traits<A>;
    using RebindAllocNode = typename AllocatorTraits::template rebind_alloc<Node>;

    A allocData;
    RebindAllocNode allocNode;
};

template <typename T, typename A>
MyList<T, A>::MyList(A allocator)
    : head(nullptr), tail(nullptr), allocData(allocator)
{
}

template <typename T, typename A>
MyList<T, A>::~MyList()
{
    auto ptr = head;
    while (ptr != nullptr)
    {
        auto next = ptr->next;
        Destroy(ptr);
        ptr = next;
    }
}

template <typename T, typename A>
void MyList<T,A>::insert(const T& data){
    Node* node = allocNode.allocate(1);
    allocData.construct(node, Node{data, nullptr});
    if (is_empty()) {
        head = node;
        tail = node;
        return;
    }
    tail->next = node;
    tail = node;
}

template <typename T, typename A>
void MyList<T, A>::Destroy(Node* node)
{
    allocData.destroy(node);
    allocNode.deallocate(node, 1);
}

template <typename T, typename A>
void MyList<T,A>:: remove_first() {
    if (is_empty()) return;
    Node* node = head;
    head = node->next;
    Destroy(node);
}

template <typename T, typename A>
void MyList<T,A>::remove_last() {
    if (is_empty()) return;
    if (head == tail) {
        remove_first();
        return;
    }
    Node* node = head;
    while (node->next != tail) node = node->next;
    node->next = nullptr;
    Destroy(tail);
    tail = node;
}

template <typename T, typename A>
void MyList<T,A>::remove(const T& _data) {
       if (is_empty()) return;
       if (head->data == _data) {
           remove_first();
           return;
       }
       else if (tail->data == _data) {
           remove_last();
           return;
       }
       Node* slow = head;
       Node* fast = head->next;
       while (fast && fast->data != _data) {
           fast = fast->next;
           slow = slow->next;
       }
       if (!fast) {
           std::cout << "Error: element does not exist!" << std::endl;
           return;
       }
       slow->next = fast->next;
       Destroy(fast);
}

template <typename T, typename A>
void MyList<T, A>::print() {
    if (is_empty()) return;
    Node* node = head;
    while (node) {
        std::cout << node->data << " ";
        node = node->next;
    }
    std::cout << std::endl;
}

template <typename T, typename A>
typename MyList<T, A>::Node* MyList<T, A>::find(const T& _data) {
        Node* node = head;
        while (node && node->data != _data) node = node->next;
        return (node && node->data == _data) ? node : nullptr;
    }

template <typename T, typename A>
typename MyList<T,A>::Node* MyList<T,A>::operator[] (const int index) {
    if (is_empty()) return nullptr;
    Node* node = head;
    for (int i = 0; i < index; i++) {
        node = node->next;
        if (!node) return nullptr;
    }
    return node;
}
#endif // my_list_H