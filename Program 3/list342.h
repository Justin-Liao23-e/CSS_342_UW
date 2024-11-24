#ifndef LIST342_H_
#define LIST342_H_

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// Node Struct
template <class T>
struct Node {
    T *data; //pointer to data
    Node *next; //pointer to next node
};

template <class T>
class List342 {
public:
    // Constructors & Destructor
    List342();
    List342(const List342& list); //copy constructor 
    ~List342();

    // Functions
    bool BuildList(string file_name);
    bool Insert(T* obj);
    bool Remove(T target,T& result);
    bool Peek(T target, T& result) const;
    int Size() const;
    void DeleteList();
    bool Merge(List342& list1);

    // Operator Overloads
    List342<T> operator+(const List342<T> &list) const;
    List342<T>& operator+=(const List342<T> &list);
    bool operator==(const List342<T> &list)const;
    bool operator!=(const List342<T> &list);
    List342<T>& operator=(const List342<T> &list);

    // Output Operator Overload
    template <class O> //different name since it's friend class (not member function)
    friend ostream& operator <<(ostream& stream, const List342<O> &list);

private:
    Node<T>* head_; //pointer to linkedlist head

};


template <class T>
List342<T>::List342() {
    head_ = nullptr;
}

template <class T>
List342<T>::List342(const List342& list) {
    head_ = nullptr;
    *this = list; //call assignment operator
}

template <class T>
List342<T>::~List342() {
    if (head_ != nullptr) {
        DeleteList();
    }
}

template <class T>
bool List342<T>::BuildList(string file_name) {
    ifstream in_file;
    in_file.open(file_name); 

    if (!in_file) { //if nothing is in the file
        cout << "This is an empty file!" << endl;
        return false;
    } 

    T temp; //stores any value type
    while (!in_file.eof()) { //loop until end of file
        in_file >> temp; //read value
        Insert(&temp); //write
    }

    in_file.close(); //prevent memory leak
    return true;
}

template <class T>
bool List342<T>::Insert(T* obj) {
    if(obj == nullptr) { //if object is empty
        return false;
    }

    Node<T>* curr = head_; //current node to head

    // Check Duplicates
    while (curr != nullptr) {
        if (*(curr->data) == *obj) { //if data is the same
            return false;
        }
        curr = curr->next;
    }

    Node<T>* insert_node = new Node<T>; 
    insert_node->data = new T(*obj); //deep copy of data (avoid shallow copy; dangling pointer)

    // Empty List or Insert at Head
    if (head_ == nullptr || *obj < *(head_->data)) {
        insert_node->next = head_;
        head_ = insert_node;
        return true;
    }

    // Insert in Sorted Order
    Node<T>* prev = nullptr;
    curr = head_;

    while (curr != nullptr && *(curr->data) < *obj) { //loop til the correct position
        prev = curr;
        curr = curr->next;
    }
    // Connect the Nodes
    insert_node->next = curr; 
    prev->next = insert_node;

    return true;
}

template <class T>
bool List342<T>::Remove(T target, T& result) {
    Node<T>* curr = head_; //current node to head
    Node<T>* prev = nullptr;
   
    while (curr != nullptr && *(curr->data) != target) { //loop til the correct position
        prev = curr;
        curr = curr->next;
    }

    if (curr == nullptr) { //if target not found
        return false;  
    }

    result = *(curr->data); //stores the removed value to result reference

    if (prev == nullptr) { //remove head node
        head_ = curr->next;
    } else { //remove node in the middle
        prev->next = curr->next;
    }

    // Memory Release
    delete curr->data;
    delete curr;
    return true;
}

template <class T>
bool List342<T>::Peek(T target, T& result) const {
    Node<T>* curr = head_;
    Node<T>* prev = nullptr;
    // Similar to Remove Function
    while (curr != nullptr && *(curr->data) != target) {
        prev = curr;
        curr = curr->next;
    }
    if (curr == nullptr) {
        return false;
    }
    result = *(curr->data); //return item
    return true;
}

template <class T>
int List342<T>::Size() const {
    int count = 0;
    Node<T>* curr = head_; 
    while (curr != nullptr) { //loop through each node
        count++;
        curr = curr->next;
    }
    return count;
}

template <class T>
void List342<T>::DeleteList() {
    while (head_ != nullptr) { //loop until head is empty
        Node<T>* temp = head_;
        head_ = head_->next; //move head to next node
        delete temp->data;
        delete temp;
    }
    head_ = nullptr;
}

template <class T>
bool List342<T>::Merge(List342& list1) {
    // Check if Same List
    if (this == &list1) {
        return false;
    }
    // Check if Merge Empty List
    if (list1.head_ == nullptr) {
        return false;
    }

    // Current List is Empty
    if (head_ == nullptr) {
        head_ = list1.head_;
        list1.head_ = nullptr;
        return true;
    }

    // Node for Each List & Previous Node 
    Node<T>* a = head_;
    Node<T>* b = list1.head_;
    Node<T>* prev = nullptr;

    // Merge Comparison
    while (a != nullptr && b != nullptr) { //loop through each node
        if (*(a->data) < *(b->data)) {
            prev = a;
            a = a->next;
        } else if (*(a->data) > *(b->data)) {
            Node<T>* b_next = b->next; //store list1's next node
            if (prev == nullptr) { //insert at head
                b->next = head_;
                head_ = b;
            } else { //insert in the middle
                prev->next = b;
                b->next = a;
            }
            prev = b;
            b = b_next;
        } else { //if data is the same
            Node<T>* temp = b;
            b = b->next;
            delete temp->data;
            delete temp;
            prev = a;
            a = a->next;
        }
    }
    // Check Remaining Nodes
    if (b != nullptr) {
        if (prev == nullptr) {
            head_ = b;
        } else {
            prev->next = b;
        }
    }
    list1.head_ = nullptr; //reset list1
    return true;
}

template <class T>
List342<T> List342<T>::operator+(const List342<T> &list) const {
    List342<T> temp = list; //copy list to not modify the orignial
    List342<T> result = *this;
    result.Merge(temp);
    return result;
}

template <class T>
List342<T> &List342<T>::operator+=(const List342<T> &list) {
    List342<T> temp = list;
    Merge(temp);
    return *this;
}

template <class T>
bool List342<T>::operator==(const List342<T> &list) const {
    Node<T>* a = this->head_; //node for current list
    Node<T>* b = list.head_; //node for compared list

    while (a != nullptr && b != nullptr) { //loop through each list's node
        if (*(a->data) != *(b->data)) { //if data is not the same
            return false;
        }
        a = a->next;
        b = b->next;
    }
    // Check Length of Each List
    if (a != nullptr || b != nullptr) {
        return false;  
    }

    return true;
}

template <class T>
bool List342<T>::operator!=(const List342<T> &list) {
    return !(*this == list); //opposite of ==
}

template <class T>
List342<T>& List342<T>::operator=(const List342<T>& list) {
    // Check if Same List
    if (this == &list) {
        return *this;
    }
    this->DeleteList(); //delete current list to avoid memory leak

    Node<T>* curr = list.head_; 
    Node<T>* last = nullptr;  

    while (curr != nullptr) {
        Node<T>* temp = new Node<T>;
        temp->data = new T(*(curr->data)); //deep copy
        temp->next = nullptr; 

        if (head_ == nullptr) { //if head is empty
            head_ = temp;
        } else {
            last->next = temp; //link new node to the end
        }
        last = temp; 
        curr = curr->next;
    }
    if (last != nullptr) {
        last->next = nullptr;
    }
    return *this;
}

template <class O>
ostream &operator <<(ostream& stream, const List342<O> &list) { 
    Node<O>* curr = list.head_;
    while(curr != nullptr) {
        stream << *(curr->data); //print data individually
        curr = curr ->next;
    }
    return stream;
}

#endif