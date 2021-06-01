// Copyright [2021] <Anthony Bernardo Kamers>
#ifndef STRUCTURES_ARRAY_LIST_H
#define STRUCTURES_ARRAY_LIST_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ Exceptions


namespace structures {

template<typename T>
class ArrayList {
 public:
    ArrayList();
    explicit ArrayList(std::size_t max_size);
    ~ArrayList();

    void clear();
    void push_back(const T &data);
    void push_front(const T &data);
    void insert(const T &data, std::size_t index);
    void insert_sorted(const T &data);
    T pop(std::size_t index);
    T pop_back();
    T pop_front();
    void remove(const T &data);
    bool full() const;
    bool empty() const;
    bool contains(const T &data) const;
    std::size_t find(const T &data) const;
    std::size_t size() const;
    std::size_t max_size() const;
    T& at(std::size_t index);
    T& operator[](std::size_t index);
    const T& at(std::size_t index) const;
    const T& operator[](std::size_t index) const;

    bool bigger_than(const T &data1, const T &data2) const;
    bool less_than(const T &data1, const T &data2) const;
    bool equal(const T &data1, const T &data2) const;

    void print_lista();

 private:
    T *contents;
    std::size_t size_;
    std::size_t max_size_;

    static const auto DEFAULT_MAX = 10u;
};

}  // namespace structures

#endif

template <typename T>
void structures::ArrayList<T>::print_lista() {
    for (int i = 0; i < static_cast<int>(max_size()); i++) {
        std::cout << contents[i] << " - ";
    }

    std::cout << "\n";
}

template<typename T>
bool structures::ArrayList<T>::bigger_than(const T &data1,
    const T &data2) const {
    return data1 > data2 ? true : false;
}

template<typename T>
bool structures::ArrayList<T>::less_than(const T &data1, const T &data2) const {
    return data1 < data2 ? true : false;
}

template<typename T>
bool structures::ArrayList<T>::equal(const T &data1, const T &data2) const {
    return data1 == data2 ? true : false;
}

template<typename T>
structures::ArrayList<T>::ArrayList() {
    size_ = 0;
    max_size_ = DEFAULT_MAX;
    contents = new T[DEFAULT_MAX];
}

template<typename T>
structures::ArrayList<T>::ArrayList(std::size_t max_size) {
    size_ = 0;
    max_size_ = max_size;
    contents = new T[max_size];
}

template<typename T>
structures::ArrayList<T>::~ArrayList() {
    delete[] contents;
}

template<typename T>
void structures::ArrayList<T>::clear() {
    size_ = 0;
}

// adiciona no final
template<typename T>
void structures::ArrayList<T>::push_back(const T &data) {
    if (full()) {
        throw std::out_of_range("lista cheia");
    } else {
        contents[size_] = data;
        size_++;
    }
}

// adiciona no início
template<typename T>
void structures::ArrayList<T>::push_front(const T &data) {
    if (full()) {
        throw std::out_of_range("lista cheia");
    } else {
        int position = size_;
        while (position > 0) {
            contents[position] = contents[position - 1];
            position--;
        }
        contents[0] = data;
        size_++;
    }
}

template<typename T>
void structures::ArrayList<T>::insert(const T &data, std::size_t index) {
    if (full()) {
        throw std::out_of_range("lista cheia");
    } else if (index > size_ + 1 || index < 0u) {
        throw std::out_of_range("erro de posicao");
    } else {
        std::size_t position = size_;
        while (position > index) {
            contents[position] = contents[position - 1];
            position--;
        }
        contents[index] = data;
        size_++;
    }
}

template<typename T>
void structures::ArrayList<T>::insert_sorted(const T &data) {
    if (full()) {
        throw std::out_of_range("lista cheia");
    } else {
        if (size_ == 0) {
            insert(data, 0);
        } else {
            std::size_t position = 0u;
            while (position <= size_ - 1 && bigger_than(data,
                contents[position])) {
                position++;
            }
            insert(data, position);
        }
    }
}

template<typename T>
T structures::ArrayList<T>::pop(std::size_t index) {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    } else if (index > size_ - 1) {
        throw std::out_of_range("erro de posicao");
    } else {
        size_--;
        int value = contents[index];
        std::size_t position = index;
        while (position <= size_) {
            contents[position] = contents[position + 1];
            position++;
        }

        return value;
    }
}

template<typename T>
T structures::ArrayList<T>::pop_back() {  // retira do final
    if (empty()) {
        throw std::out_of_range("lista vazia");
    } else {
        size_--;
        int value = contents[size_];

        return value;
    }
}

template<typename T>
T structures::ArrayList<T>::pop_front() {  // retira do início
    if (empty()) {
        throw std::out_of_range("lista vazia");
    } else {
        size_--;
        int value = contents[0];
        std::size_t position = 0u;
        while (position <= size_) {
            contents[position] = contents[position + 1];
            position++;
        }

        return value;
    }
}

template<typename T>
void structures::ArrayList<T>::remove(const T &data) {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    } else {
        std::size_t position_element = find(data);
        pop(position_element);
    }
}

template<typename T>
bool structures::ArrayList<T>::contains(const T &data) const {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    } else {
        for (std::size_t position = 0; position < size_; position++) {
            if (contents[position] == data) {
                return true;
            }
        }

        return false;
    }
}

template<typename T>
std::size_t structures::ArrayList<T>::find(const T &data) const {
    std::size_t position = 0u;
    while (position <= size_ - 1 && !(equal(data, contents[position]))) {
        position++;
    }

    if (position > size_) {
        throw std::out_of_range("erro de posicao");
    } else {
        return position;
    }
}

template<typename T>
T& structures::ArrayList<T>::at(std::size_t index) {
    if (index < 0u || index > size_) {
        throw std::out_of_range("erro de posicao");
    } else {
        return contents[index];
    }
}

template<typename T>
const T& structures::ArrayList<T>::at(std::size_t index) const {
    if (index < 0u || index > size_) {
        throw std::out_of_range("erro de posicao");
    } else {
        return contents[index];
    }
}

template<typename T>
T& structures::ArrayList<T>::operator[](std::size_t index) {
    return contents[index];
}

template<typename T>
const T& structures::ArrayList<T>::operator[](std::size_t index) const {
    return contents[index];
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
bool structures::ArrayList<T>::full() const {
    return (size_ == max_size());
}

template<typename T>
bool structures::ArrayList<T>::empty() const {
    return (size_ == 0);
}