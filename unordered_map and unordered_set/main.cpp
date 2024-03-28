#include <iostream>
#include <functional>
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
    Vector(int initial_size, const T& initial_value) : size(initial_size), capacity(initial_size), arr(new T[capacity]) {
        for (int i = 0; i < size; ++i) {
            arr[i] = initial_value;
        }
    }
    Vector(int size, int capacity, T *arr) : size(size), capacity(capacity), arr(arr) {}

    void push_front(T data) {
        if (size == capacity) {
            T* temp = new T[capacity * 2];
            for (int i = 0; i < size; ++i)
                temp[i + 1] = arr[i];
            delete[] arr;
            capacity *= 2;
            arr = temp;
        }
        arr[0] = data;
        ++size;
    }

    int getSize() const {
        return size;
    }
    void push_back(T data) {
        if (size == capacity) {
            T* temp = new T[capacity * 2];
            for (int i = 0; i < size; ++i)
                temp[i] = arr[i];
            delete[] arr;
            capacity *= 2;
            arr = temp;
        }
        arr[size++] = data;
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
    int length() const {
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
        delete[] arr;
    }

    void set(int index , const T& value){
        if(index >=0 && index < size){
            arr[index]  = value;
        }else{
            throw out_of_range ("Index out of range");
        }
    }

    void resize(int new_size , T data){
        if(new_size<size)
            size = new_size;
        else if (new_size > size){
            T* temp = new T[new_size];
            for(int i = 0 ; i < size;i++)
                temp[i] = arr[i];
            for(int i = 0 ; i < new_size;i++)
                temp[i] = data;
            delete[] arr;
            arr = temp;
            size = new_size;
            capacity = new_size;
        }
    }


    T* begin() const {
        return arr;
    }

    T* end() const {
        return arr + size;
    }
};

template<typename K, typename V> class unorderedMap {
private:
    class Node {
    public:
        K key;
        V value;
        int hash;
        Node* next;
        Node(K key, V value, int hash, Node* next = nullptr) : key(key), value(value), hash(hash), next(next) {}
    };

    int size; /// Текущий элеменеты который хранящихся в хэш-карте.
    int init_size; ///  Начальный размер
    Vector<Node*> table; ///table является экземпляром класса Vector
    hash<K>  hasher; /// Хэшер для ключей

public:
    unorderedMap() : size(0), init_size(16), table(init_size, nullptr) {}

/// Hashing the key
    size_t getIndex(K key){/////Беззнаковый целочисленный тип
        return hasher(key)%init_size;
    }

    void put(K key ,V value){
        int index = getIndex(key);
        Node* cur = table[index];

        if(cur==nullptr){
            table.set(index,new Node(key,value,hasher(key),nullptr));
            size++;
            return;
        }

        while(cur!=nullptr){
            if(cur->key ==key){
                cur ->value= value;
            }
            cur = cur->next;
        }
        cur = table[index];

        while(cur->next != nullptr){
            cur = cur->next;
        }
        cur->next = new Node(key,value,hasher(key),nullptr);
        size++;
    }

    V get(K key){
        int index = getIndex(key);
        Node* cur = table[index];

        while(cur!=nullptr){
            if(cur->key == key){
                return cur->value;
            }
            cur = cur->next;
        }
    }


    void remove(K key){
        int index = getIndex(key);
        Node* cur = table[index];
        Node* prev = nullptr;

        while(cur!=nullptr){
            if(cur->key==key){
                if(prev!=nullptr){
                    prev->next = cur->next;
                }else{
                    table.set(index,cur->next);
                }
                delete cur;
                size--;
            }
            prev = cur;
            cur = cur->next;
        }
    }

    // Оператор вывода
    friend ostream& operator<<(ostream& os,  unorderedMap& umap) {
       os <<"[";
       for(auto it = umap.table.begin();it!=umap.table.end();it++){
           Node* cur = *it;
           while(cur!=nullptr){
               os<<"{"<<cur->key<<":"<<cur->value<<"}";
               if(cur->next!=nullptr){
                   os<<",";
               }
               cur = cur->next;
           }
       }
       os<<"]";
       return os;
    }
};






template<typename K> class unorderedSet {
private:
    unorderedMap<K, bool> table;
public:
    unorderedSet() {}
    void add(K key){
        table.put(key,true);
    }

    bool contains(K key){
        try{
            table.get(key);
         }catch(out_of_range& e){
            return false;
        }
    }

   void remove(K key){
        try{
            table.remove(key);
        }catch(out_of_range& e){

        }
    }

    friend ostream &operator<<(ostream& os, unorderedSet& set){
        os<<"table:"<<set.table;
        return os;
    }

};




int main(){
    unorderedMap <string , int> map;
    map.put("Erkebulan",80);
    map.put("Isa",95);
    map.put("Ardak" , 75);
    map.put("Erkebulan" ,98);
    map.put("Damir" , 100);
    map.put("Nurbolat" , 100);
    cout<<map.get("Erkebulan")<<" ";
    cout<<map.get("Isa")<<endl;

    map.remove("Erkebulan");

    try {
        cout << map.get("Erkebulan") << endl;
    } catch (const out_of_range& e) {
        cout << "Key 'Erkebulan' not found" << endl;
    }

    cout << map << endl;


    unorderedSet<string> set;
    set.add("Erkebulan");
    set.add("Damir");
    set.add("Islam");

    cout << "Contains Erkebulan: " << set.contains("Erkebulan") << endl;
    cout << "Contains John: " << set.contains("John") << endl;

    set.remove("Damir");

    cout << set << endl;




    return 0;
}