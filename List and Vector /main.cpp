#include <iostream>
using namespace std;
template<typename T> class Vector{
    int size;
    int capacity;
    T*arr;
public:
    Vector(){
        size=0;
        capacity=10;
        arr=new T[capacity];
    }
    void push_front(T data){
        if(size==capacity){
            T* temp=new T[capacity*2];
            for(int i=0;i<size;i++)
                temp[i+1]=arr[i];
            delete arr;
            capacity*=2;
            arr=temp;
        }
        arr[0]=data;
        size++;
    }

    void push_back(T data){
        if(size==capacity){
            T* temp=new T[capacity*2];
            for(int i=0;i<size;i++)
                temp[i]=arr[i];
            delete arr;
            capacity*=2;
            arr=temp;
        }
        arr[size++]=data;
    }

    void pop_back(){
        size--;
    }

    void pop_front(){
        if(size>0){
            for(int i=0;i<size-1;i++)
                arr[i]=arr[i+1];
            size--;
        }
    }
    friend ostream &operator<<(ostream &os, const Vector &vector) {
        os << "[";
        for(int i = 0; i < vector.size; i++)
            os << vector.arr[i] << " ";
        os << "]";
        return os;
    }

    T& operator[](int index){
        return arr[index];
    }
    int length(){
        return size;
    }
    bool operator==(const Vector& other) const {
        if (size != other.size) {
            return false;
        }

        for (int i = 0; i < size; i++) {
            if (arr[i] != other.arr[i]) {
                return false;
            }
        }

        return true;
    }

    bool operator!=(const Vector& other) const {
        return !(*this == other);
    }

    ~Vector() {
        delete [] arr;
    }
};

template<typename T>class List{
    class Node{

    public:
        T value;
        Node* next;
        Node(T value = T(),Node *next =nullptr){
            this->value=value;
            this->next=next;
        }
    };
    int size;
    Node* head;
public:
    List(){
        size=0;
        head=nullptr;
    }
    int Size(){
        return size;
    }
    void push_back(T data){
        if(size==0){
            head=new Node(data);
        }else{
            Node* current=head;
            while(current->next!=nullptr){
                current=current->next;
            }
            current->next=new Node(data);
        }
        size++;
    }

    void pop_back(T data){
        if(size==0){
            head=new Node(data);

        }else{
            Node* current=head;
            while(current->next!=nullptr){
                current=current->next;
            }
            delete current->next;
            current->next=new Node(data);
        }
        size--;
    }
    void push_front(T data){
        Node* newhead=new Node(data,head);
        head=newhead;
        size++;
    }
    void pop_front(){
        Node* oldHead=head;
        head=head->next;
        delete oldHead;
        size--;
    }
    T operator[](int index){
        int counter=0;
        Node* current =head;
        while(counter!=index){
            current=current->next;
            counter++;
        }
        return current->value;

    }
    friend ostream &operator<<(ostream &os, List &list) {
        for (int i = 0; i < list.size; ++i) {
            os << list[i] << " ";
        }
        return os;
    }
    bool operator==(const List& other)
    const{
        if(size!=other.size){
            return false;
        }
        Node* current1=head;
        Node* current2=other.head;
        while(current1!=nullptr&&current2!=nullptr) {
            if (current1->value != current2->value) {
                return false;
            }
            current1 = current1->next;
            current2 = current2->next;
        }
        return true;
    }
    bool operator!=(const List& other)
    const{
        return!(*this==other);
    }
    ~List(){
        while(size!=0)
            pop_front();
    }
};

int main(){
    Vector<int> v;
    //    v.push_front(0);
    //    v.pop_front();
    for(int i = 1; i < 10; i++)
        v.push_back(i);
    //    v.pop_back();
    //    v.pop_front();
    for(int i = 0; i < v.length(); i++)
        cout << v[i] << " ";
    cout<<"________________________________"<<endl;

    List<int> l;// []
    //    l.pop_front();
    //    l.pop_back(5);
    for(int i = 1; i < 10; i++)
        l.push_back(i);
    l.push_front(0);
    cout << l << endl;


    cout<<"________________________________"<<endl;


    return 0;
}