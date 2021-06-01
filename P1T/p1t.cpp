// Copyright [2021] Antonio Silverio Montagner

#ifndef STRUCTURES_ARRAY_LIST_H
#define STRUCTURES_ARRAY_LIST_H
#include <iostream>
#include <cstdint>

namespace structures {

template<typename T>
class ArrayList {
 public:
	ArrayList();
	explicit ArrayList(std::size_t max_size);
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

	// --
	void shell(int d);
	// --

 private:
	T* contents;
	std::size_t size_;
	std::size_t max_size_;

	static const auto DEFAULT_MAX = 10u;
};

}  // namespace structures
#endif

template<typename T>
structures::ArrayList<T>::ArrayList() {
	size_ = 0;
	max_size_ = DEFAULT_MAX;
	contents = new T[max_size_];
}

template<typename T>
structures::ArrayList<T>::ArrayList(std::size_t max_size) {
	size_ = 0;
	max_size_ = max_size;
	contents = new T[max_size_];
}

template<typename T>
structures::ArrayList<T>::~ArrayList() {
	delete [] contents;
}

template<typename T>
void structures::ArrayList<T>::clear() {
	size_ = 0;
}

template<typename T>
bool structures::ArrayList<T>::full() const {
	return size_ == max_size_;
}

template<typename T>
bool structures::ArrayList<T>::empty() const {
	return size_ == 0;
}

template<typename T>
bool structures::ArrayList<T>::contains(const T& data) const {
	for (std::size_t i = 0; i < size_; i++) {
		if (data == contents[i]) {
			return true;
		}
	}
	return false;
}

template<typename T>
std::size_t structures::ArrayList<T>::find(const T& data) const {
	std::size_t i = 0;
	while (i < size_) {
		if (contents[i] == data) {
			break;
		}
		i++;
	}
	return i;
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
void structures::ArrayList<T>::push_back(const T& data) {
	if (full()) {
		throw std::out_of_range("no space");
	} else {
		contents[size_] = data;
		size_++;
	}
}


template<typename T>
void structures::ArrayList<T>::push_front(const T& data) {
	if (full()) {
		throw std::out_of_range("no space");
	} else {
		for (std::size_t i = size_; i > 0; i--) {
			contents[i] = contents[i - 1];
		}
		contents[0] = data;
		size_++;
	}
}

template<typename T>
void structures::ArrayList<T>::insert(const T& data, std::size_t index) {
	if (full()) {
		throw std::out_of_range("no space");
	} else if (index < 0 || index > size_) {
		throw std::out_of_range("invalid index");
	} else {
		for (std::size_t i = size_; i > index; i--) {
			contents[i] = contents[i - 1];
		}
		contents[index] = data;
		size_++;
	}
}

template<typename T>
void structures::ArrayList<T>::insert_sorted(const T& data) {
	if (full()) {
		throw std::out_of_range("no space");
	} else if (empty() || data > contents[size_ - 1]) {
		push_back(data);
	} else {
		std::size_t current;
		current = 0;
		while (data > contents[current]) {
			current++;
		}
		insert(data, current);
	}
}

template<typename T>
T structures::ArrayList<T>::pop(std::size_t index) {
	if (index < 0 || index > size_ - 1) {
		throw std::out_of_range("invalid index");
	} else if (empty()) {
		throw std::out_of_range("empty");
	} else {
		T value = contents[index];
		size_--;
		for (std::size_t i = index; i < size_; i++) {
			contents[i] = contents[i + 1];
		}
		return value;
	}
}

template<typename T>
T structures::ArrayList<T>::pop_back() {
	return pop(size_ - 1);
}

template<typename T>
T structures::ArrayList<T>::pop_front() {
	return pop(0);
}

template<typename T>
void structures::ArrayList<T>::remove(const T& data) {
	if (empty()) {
		throw std::out_of_range("empty");
	} else {
		pop(find(data));
	}
}

template<typename T>
T& structures::ArrayList<T>::at(std::size_t index) {
	if (empty()) {
		throw std::out_of_range("empty");
	} else if (index < 0 || index > size_) {
		throw std::out_of_range("invalid index");
	} else {
		return contents[index];
	}
}

template<typename T>
T& structures::ArrayList<T>::operator[](std::size_t index) {
	return contents[index];
}

template<typename T>
const T& structures::ArrayList<T>::at(std::size_t index) const {
	if (empty()) {
		throw std::out_of_range("empty");
	} else if (index < 0 || index > size_) {
		throw std::out_of_range("invalid index");
	} else {
		return contents[index];
	}
}

template<typename T>
const T& structures::ArrayList<T>::operator[](std::size_t index) const {
	return contents[index];
}

/*
template<typename T>
void structures::ArrayList<T>::shell(int d){

// loop para um numero menor que a metade da lista para eveitar pegar index já utilizado
	for (std::size_t i = 0; i < (size_ / 2); i++){
		std::cout << "for 1" << std::endl;
// variavel utilizada para percorrer a lista do final para a metade
// 		std::size_t t = size() - i;  // recebe o index equivalente a posição oposta 
		// t --;                       // arrumar o tamanho da lista para incluir posição 0
		std::size_t t;
// duplicar os "d" elementos
		for(int j = 0; j < d; j++){ // loop para pegar os "d" elementos
			t = size() - i;  // recebe o index equivalente a posição oposta 

			
			
			std::cout << "for 2 a" << std::endl;
			std::cout << d << "i"<< i << "t" << t << std::endl;
			
			
			int index = i + d;      // index para inserir a copia apos "d" elementos
			int indexT = t - d;     // index oposto trabalhando do final para a metade

			const T& dataT = at(t);   // pegar o elemento t para fazer a copia

			insert(dataT, indexT);          // passar o elemento t na posicao de copia



			std::cout << dataT << std::endl;
			std::cout << indexT << std::endl;
			for (std::size_t i = 0; i<size();i++){
				std::cout << at(i);
			}



			const T& data = at(i);    // pegar o elemento i para fazer a copia
			std::cout <<"\n"<< data << std::endl;

			
			insert(data, index);             // passar o elemento i na posucao de copia

			
			
			
			
			std::cout <<"\n"<< data << std::endl;
			std::cout << index << std::endl;

			for (std::size_t i = 0; i<size();i++){
				std::cout << at(i);
			}
			std::cout << "for 2 aaaa" << std::endl;





			// t--;                    // diminuir 1 de t até rodar o loop "d" vezes
			i++;                    // adicionar 1 a i até rodar o loop "d" vezes
		}        
		i+= (d*2);
	}

}
*/

template<typename T>
void structures::ArrayList<T>::shell(int d) {
	// pegar o elemento na posicao "size_ - d" e acrescentar na lista
	for ( int i = 0; i < d; i++){	 // loop para pegar os "d" elementos
		push_front(at(d));			// inserir o elemento no inicio ate completar os "d" elementos
		push_back(at(size_-d));		// inserir o elemento no final ate completar os "d" elementos
	}
}


int main(){
	structures::ArrayList<int> list{};

	list.insert_sorted(1);
	list.push_back(2);
	list.push_back(0);
	list.push_back(7);

	list.push_back(3);
	list.push_back(8);
	list.push_back(9);
	
	
	list.shell(3);
	for (std::size_t i = 0; i<list.size();i++){
		std::cout << list.at(i) << std::endl;
	}

	return 0;
}





