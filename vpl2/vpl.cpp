#ifndef STRUCTURES_ARRAY_LIST_H
#define STRUCTURES_ARRAY_LIST_H

#include <cstdint>


namespace structures {

template<typename T>
class ArrayList {
public:
    ArrayList();
    ArrayList(std::size_t max_size);
    ~ArrayList();

    void clear();
    void push_back(const T& data);
    void push_front(const T& data);
    void insert(const T& data, std::size_t index);
    void insert_sorted(const T& data);
    T pop(std::size_t index);
    T pop_back();
    T pop_front();
    void remove(const T& data);
    bool full() const;
    bool empty() const;
    bool contains(const T& data) const;
    std::size_t find(const T& data) const;
    std::size_t size() const;
    std::size_t max_size() const;
    T& at(std::size_t index);
    T& operator[](std::size_t index);
    const T& at(std::size_t index) const;
    const T& operator[](std::size_t index) const;

private:
    T* contents;
    std::size_t size_;
    std::size_t max_size_;
    int end_;
    int begin_;

    const static auto DEFAULT_MAX = 10u;
};

}

#endif

//-------------------------------------------------

template<typename T>
structures::ArrayList<T>::ArrayList() {
    contents = new T[DEFAULT_MAX];
    begin_ = size_ = 0;
    end_ = -1;
}

template<typename T>
structures::ArrayList<T>::ArrayList(std::size_t max_size){
    max_size_ = max_size;
    contents = new T[max_size];
    begin_ = size_ = 0;
    end_ = -1;

}

template<typename T>
structures::ArrayList<T>::~ArrayList() {
    delete[] contents;
}

template<typename T>
structures::ArrayList<T>::void clear() {
    begin_ = size_ = 0;
    end_ = -1;
}

template<typename T>
structures::ArrayList<T>::push_back(const T& data) {
    if (full()) {
        throw std::out_of_range("fila esta cheia");
    } else {
        end_ = ((end_ + 1) % max_size_);
        contents[end_] = data;
        size_++;
    }

}

template<typename T>
structures::ArrayList<T>::insert(const T& data, std::size_t index) {
    if (full()) {
        throw std::out_of_range("fila esta cheia");
    } else {
        end_ = ((end_ + 1) % max_size_);
        index = end_;
        while(index > 0){
            contents[index] = contents[index -1];
            index--;
        }
        contents[end_] = data;
        size_++;
    }

}

template<typename T>
structures::ArrayList<T>::insert_sorted(const T& data) {

}

template<typename T>
structures::ArrayList<T>::pop(std::size_t index) {
    if (empty()){
        throw std::out_of_range("fila esta cheia");
    }else{
        end_--;
        index = contents[index]
        index
    }

}

template<typename T>
structures::ArrayList<T>::pop_back() {
    if(empty()){
        throw std::out_of_range("fila esta vazia");
    }else{
        end_ --;
        
    }

}

template<typename T>
structures::ArrayList<T>::pop_front() {

}

template<typename T>
structures::ArrayList<T>::remove(const T& data) {

}

template<typename T>
structures::ArrayList<T>::full() const {
    if (end_ = max_size_-1){
        return 1;
    }
    else{
        return 0;
    }
    //return (size_ == max_size_);
}

template<typename T>
structures::ArrayList<T>::empty() const {
    if (end_ = -1){
        return 1;
    }
    else{
        return 0;
    }
    //return 0;
}

template<typename T>
structures::ArrayList<T>::contains(const T& data) const {
return 0;
}

template<typename T>
std::size_t structures::ArrayList<T>::find(const T& data) const {
    return 0;
}

template<typename T>
std::size_t structures::ArrayList<T>::size() const {
    return size_;

}

template<typename T>
std::size_t structures::ArrayList<T>::max_size() const {
    return max_size_;

}

template<typename T>
T& structures::ArrayList<T>::at(std::size_t index) {

}

template<typename T>
T& structures::ArrayList<T>::operator[](std::size_t index) {

}
