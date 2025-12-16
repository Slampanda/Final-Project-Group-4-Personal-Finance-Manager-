#pragma once
#include <stdexcept>
template <typename T> // dùng dynamicArray cho nhiều dữ liệu transaction, wallet, income, expense
class DynamicArray{
private:
    T* data;
    int capacity;
    int size;

    void resize(int newCapacity){
        T* newData = new T[newCapacity];
        for (int i = 0; i<size; i++){
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }
    
public:
    // Constructor
    DynamicArray() : capacity(10), size(0){
        data = new T[capacity];
    }
    
    // Destructor
    ~DynamicArray(){
        delete[] data;
    }
    
    // Copy constructor
    DynamicArray(const DynamicArray& other)
        : capacity(other.capacity), size(other.size){
        data = new T[capacity];
        for (int i = 0; i<size; i++){
            data[i] = other.data[i];
        }
    }
    
    // Assignment operator
    DynamicArray& operator=(const DynamicArray& other){
        if (this != &other){
            delete[] data;
            capacity = other.capacity;
            size = other.size;
            data = new T[capacity];
            for (int i = 0; i < size; i++){
                data[i] = other.data[i];
            }
        }
        return *this;
    }
    
    // Thêm phần tử
    void add(const T& item){
        if (size >= capacity){
            resize(capacity * 2);
        }
        data[size] = item;
        size = size + 1;
    }
    
    // Lấy phần tử
    T& get(int index){
        return data[index];
    }
    
    const T& get(int index) const{
        return data[index];
    }
    
    // Xóa phần tử
    void remove(int index){
        for (int i = index; i <size-1; i++){
            data[i] = data[i+1];
        }
        size = size - 1;
    }
    
    // Kích thước
    int getSize() const{
        return size;
    }
    
    // Capacity
    int getCapacity() const{
        return capacity;
    }
    
    // Xóa tất cả
    void clear(){
        size = 0;
    }
    
    // Tìm phần tử
    int find(const T& item) const{
        for (int i = 0; i < size; i++){
            if (data[i] == item){
                return i;
            }
        }
        return -1;
    }

    T& operator[](int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Your choice is not available in system");
        }
        return data[index];
    }
    const T& operator[](int index) const{
        if (index < 0 || index >= size) {
            throw std::out_of_range("Your choice is not available in system");
        }
        return data[index];
    }
};
