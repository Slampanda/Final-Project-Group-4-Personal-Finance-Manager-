#pragma once
#include <stdexcept>

template <typename T>
class DynamicArray {
private:
    T** data;
    int capacity;
    int size;

    void resize(int newCapacity) {
        T** newData = new T*[newCapacity];
        
        // Copy existing pointers
        for (int i = 0; i < size; i++) {
            newData[i] = data[i];
        }
        
        // Initialize new pointers to nullptr
        for (int i = size; i < newCapacity; i++) {
            newData[i] = nullptr;
        }
        
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    // Constructor
    DynamicArray() : capacity(10), size(0) {
        data = new T*[capacity];
        for (int i = 0; i < capacity; i++) {
            data[i] = nullptr;
        }
    }
    
    // Copy constructor (quan trọng!)
    DynamicArray(const DynamicArray& other) : capacity(other.capacity), size(other.size) {
        data = new T*[capacity];
        for (int i = 0; i < capacity; i++) {
            if (i < size && other.data[i] != nullptr) {
                data[i] = new T(*(other.data[i]));
            } else {
                data[i] = nullptr;
            }
        }
    }
    
    // Assignment operator
    DynamicArray& operator=(const DynamicArray& other) {
        if (this != &other) {
            // Clean up current data
            for (int i = 0; i < size; i++) {
                delete data[i];
            }
            delete[] data;
            
            // Copy from other
            capacity = other.capacity;
            size = other.size;
            data = new T*[capacity];
            for (int i = 0; i < capacity; i++) {
                if (i < size && other.data[i] != nullptr) {
                    data[i] = new T(*(other.data[i]));
                } else {
                    data[i] = nullptr;
                }
            }
        }
        return *this;
    }
    
    // Destructor
    ~DynamicArray() {
        clear();
        delete[] data;
    }
    
    // Thêm phần tử
    void add(const T& item) {
        if (size >= capacity) {
            resize(capacity * 2);
        }
        data[size] = new T(item);
        size++;
    }
    
    // Lấy phần tử
    T& get(int index) {
        if (index < 0 || index >= size || data[index] == nullptr) {
            throw std::out_of_range("Index out of range");
        }
        return *(data[index]);
    }
    
    const T& get(int index) const {
        if (index < 0 || index >= size || data[index] == nullptr) {
            throw std::out_of_range("Index out of range");
        }
        return *(data[index]);
    }
    
    // Xóa phần tử
    void remove(int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        
        delete data[index];
        
        // Shift elements
        for (int i = index; i < size - 1; i++) {
            data[i] = data[i + 1];
        }
        
        data[size - 1] = nullptr;
        size--;
    }
    
    // Kích thước
    int getSize() const {
        return size;
    }
    
    // Xóa tất cả
    void clear() {
        for (int i = 0; i < size; i++) {
            delete data[i];
            data[i] = nullptr;
        }
        size = 0;
    }
    
    // Toán tử []
    T& operator[](int index) {
        return get(index);
    }
    
    const T& operator[](int index) const {
        return get(index);
    }
};
