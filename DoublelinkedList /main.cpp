#include<iostream>
using namespace std;
template<typename T> class DoubleLinkedList {
    class Node {
    public:
        T value;
        Node *next;
        Node *prev;

        Node(T value, Node *next, Node *prev) : value(value), next(next), prev(prev) {}
    };
    int size;
    Node *head;
    Node *tail;
public:
    DoubleLinkedList() {
        size = 0;
        head = tail = nullptr;
    }
    int length(){
        return size;
    }
    T operator [] (int index) {
        Node* current = nullptr;
        int count = size -1;
        if (index > size/2){
            current = tail;
            while (count != index){
                current = current -> prev;
                count--;
            }
        }
        else {
            current = head;
            for (int i = 0; i < index; i++) {
                current = current->next;
            }
        }
        return current -> value;

    }
    void push_back(T data){
        if(head==nullptr){
            head=new Node(data, nullptr, nullptr);
            tail=head;
        }else{
            Node* temp=new Node(data, nullptr,tail);
            tail->next=temp;
            tail=temp;
        }
     size++;
    }
    void push_front(T data){
        if(head==nullptr){
            head=new Node(data, nullptr, nullptr);
            tail=head;
        }else{
            Node* temp=new Node(data, head,tail);
            head->prev=temp;
            head=temp;
        }
        size++;
    }
    void pop_back(){
        if(size==1){
            delete head;
            head=tail=nullptr;
        }else{
            tail=tail->prev;
            delete tail->next;
            tail->next=nullptr;
        }
        size--;
    }
    void pop_front(){
        if(size==1){
            delete head;
            head=tail=nullptr;
        }else{
            head=head->next;
            delete head->prev;
            head->prev=nullptr;
        }
        size--;
    }

        void add(T data, int index) {
        int count = size -1;
        Node* current = nullptr;

        if (index == size-1){
            push_back(data);
        }
        if (size/2 < index){
            current = head;
            for (int i = 0; i < index; ++i){
                current++;
                current = current -> next;
            }
        }
        if (size/2 > index) {
            current = tail;
            while(count != index){
                count--;
                current = current->prev;
            }
        }
        Node* newNode=new Node(data,current->next,current);
        if (current -> next != nullptr) {
            current->next->prev = newNode;
        }else {
            tail = newNode;
        }
        current->next = newNode;
        size++;
    }
    void remove(int index) {
        int count = size-1;
        Node* current = nullptr;

        if (index == size-1){
            pop_back();

        }
        if (index > size/2) {
            current = tail;
            while (count != index) {
                count--;
                current = current->prev;
            }
        }
        else {
            current = head;
            for (int i = 0; i < index; ++i) {
                current = current->next;
            }
        }
        if(current -> prev != nullptr){current->prev->next = current->next;}
        else{head = current -> next;}
        if (current -> next != nullptr){ current->next->prev = current->prev; }
        else{tail = current -> next;}
        delete current;
        size--;
    }

    bool operator==(DoubleLinkedList<T> another)
const{
        Node* cur=head;
        Node* cur1=another.head;
        while(cur!= nullptr&&cur1!= nullptr){
            if(cur->value!=cur1->value)
                return false;
        cur=cur->next;
        cur1=cur->next;
        }
    return true;
    }

    bool operator!=(DoubleLinkedList<T>& another)
    const{
        return !(*this == another);
    }
    ~DoubleLinkedList() {
        while(size != 0)
            pop_back();
    }

    void set(T data, int index) {
        int count = size -1;
        Node* current = nullptr;
        Node* newData = new Node(data, nullptr, nullptr);

        if (size/2 < index){
            current = head;
            while(current -> next != nullptr){
                count++;
                current = current -> next;
                if(count == index){
                    current->next = newData->next;
                    current->prev = newData->prev;
                    current->prev->next = newData;
                    current->next->prev = newData;
                    delete current;
                }
            }
        }
        if (size/2 > index) {
            current = tail;
            while(current -> prev != nullptr){
                count--;
                current = current -> prev;
                if (count == index){
                    current->next = newData->next;
                    current->prev = newData->prev;
                    current->prev->next = newData;
                    current->next->prev = newData;
                    delete current;
                }
            }
        }

    }


};
int main(){
    DoubleLinkedList<int>list;
    for(int i=0;i<10;i++)
        list.push_back(i+1);
  list.push_back(102);
//    list.push_front(103);
//    list.pop_front();
//    list.pop_back();
//list.set(101,1);
    list.add(102,2);
    for(int i=0;i<list.length();i++)
     cout<<list[i]<<" ";

    return 0;
}