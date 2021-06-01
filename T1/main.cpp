#ifndef STRUCTURES_LINKED_STACK_H
#define STRUCTURES_LINKED_STACK_H

#include <algorithm>
#include <stack>
#include <string>
#include <utility> // pair
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <tuple>

#include <cstdint>
#include <stdexcept>

namespace region_counter {

    /**
     * Valores possíveis de um pixel na matriz binária  
    */
    enum COLOR {
        /// Pixel preto = 0
        BLACK,
        /// Pixel branco = 1
        WHITE,
    };

    /**
	 * @brief Transforma uma região conexa inteira da matriz em 0's, começando pelo elemento indicado pelas posições (i, j)
     * @param vector<vector<bool>> matriz booleana base
     * @param int i coordenada i do pixel 
     * @param int j coordenada j do pixel 
    */
    void clear_region(std::vector<std::vector<bool>>& matrix, int i, int j);
    
    /**
	 * @brief Conta a quantidade de regiões de valor 1 conexas em uma matriz booleana
     * @param vector<vector<bool>> matriz booleana a ser utilizada para a contagem
    */
    int connectivity_counter(std::vector<std::vector<bool>> matrix);

    /** 
	 * @brief Cria uma matriz booleana a partir de uma string de '0' e '1'.
     * @param string str_matrix matriz codificada em string
     * @param int width largura da matriz
     * @param int height altura da matriz
    */
    std::vector<std::vector<bool>> create_matrix(const std::string& str_matrix, int width, int height);
}

int main() {
    char xml_file_name[100];
    std::ifstream xml_file;

    std::cin >> xml_file_name;

    xml_file.open(xml_file_name);
    
    if (not xml_file.is_open()) {
        std::cout << "error\n";
        return -1;
    }
    
    std::stringstream stream;
	stream << xml_file.rdbuf();
	std::string contents = stream.str();

    xml_file.close();

    // Se o arquivo não é um XML válido, retorna -1 junto com uma mensagem de erro
    if (not xml::validate(contents)) {
        std::cout << "error\n";
        return -1;
    }

    size_t i = {0};

    while (i < contents.length())
    {
        // Busca a tag completa da próxima imagem dentro do arquivo
        std::string open_tag = "<img>";
        std::string close_tag = "</img>";
        std::string image = xml::get_tag(contents, open_tag, close_tag, i);

        i += image.length() + close_tag.length();
        
        // Sai do laço caso tenha chegado ao final das imagens
        if (i > contents.length()) break;
	
        // Utiliza a função get_value pra buscar o conteúdo de cada atributo da imagem
        std::string data = xml::get_value(image, "<data>", "</data>");
        const std::string name = xml::get_value(image, "<name>", "</name>");
        const int width = std::stoi(xml::get_value(image, "<width>", "</width>"));
        const int height = std::stoi(xml::get_value(image, "<height>", "</height>"));

        // Caso seja uma imagem inválida (com alguma das dimensões menores ou iguais a 0)
        // retorna -1 como sinal de erro.
        if (height <= 0|| width <= 0) return -1;

        // Remove \n da string data
        data.erase(std::remove(data.begin(), data.end(), '\n'), data.end());

        std::vector<std::vector<bool>> matrix = region_counter::create_matrix(data, width, height);

        int regions = region_counter::connectivity_counter(matrix);
		std::cout << name << ' ' << regions << std::endl;
    }
}


namespace region_counter {

// Implementa a lógica de Flood Fill, pintando de preto todos os pixels brancos
// que são conexos ao pixel inicial passado pelas coordenadas (i, j). A lógica de
// flood é implementada com o auxílio de uma estrutura do tipo Pilha, implementada
// durante as aulas da disciplina.

void clear_region(std::vector<std::vector<bool>>& matrix, int i, int j) {
    structures::LinkedStack<std::tuple<int, int>> stack;

    int width = matrix[0].size();
    int height = matrix.size();

    stack.push(std::make_tuple(i, j));

    while (!stack.empty()) {
        std::tuple<int, int> last = stack.pop();
        
        i = std::get<0>(last);
        j = std::get<1>(last);

        matrix[i][j] = 0;

        // Verifica se o elemento a esquerda existe e se é branco.
        if (j > 0 && matrix[i][j - 1])
            stack.push(std::make_tuple(i, j - 1));     

        // Verifica se o elemento a direita existe e se é branco.
        if (j < (width - 1) && matrix[i][j + 1])
            stack.push(std::make_tuple(i, j + 1));

        // Verifica se o elemento acima existe e se é branco.
        if (i > 0 && matrix[i - 1][j])
            stack.push(std::make_tuple(i - 1, j));
        
        // Verifica se o elemento abaixo existe e se é branco.
        if (i < (height - 1) && matrix[i + 1][j])
            stack.push(std::make_tuple(i + 1, j));
    }

} 

// Conta a quantidade de regiões conexas de valor 1 existentes em uma matriz booleana, para isso
// usa uma lógica de flood fill, onde ao encontrar um elemento com valor 1 incrementa um contador/
// e logo após preenche com 0 esse elemento e toda os pixels conexos a ele. Essa lógica de preenchimento
// é executada pela função clear_region

int connectivity_counter(std::vector<std::vector<bool>> matrix) {
    int connectivity_count = 0;
    
    for (int i = 0; i < (int) matrix.size(); i++) {
        for (int j = 0; j < (int) matrix[0].size(); j++) {
            if (matrix[i][j] == COLOR::WHITE) {
                connectivity_count++;
                clear_region(matrix, i, j);
            }
        }
    }
    
    return connectivity_count;
}

/// Cria uma matriz de tamanho width * height, do tipo std::vector<std::vector<bool>> a partir de uma
/// string binária. A string deve conter apenas os caracteres 0 e 1. 
std::vector<std::vector<bool>> create_matrix(const std::string& str_matrix, int width, int height) {
    std::vector<std::vector<bool>> matrix;

    for (int i = 0u; i < height; i++) {
        std::vector<bool> line;

        for (int j = 0; j < width; j++)
            line.push_back(str_matrix[i * width + j] == '1');

        matrix.push_back(line);
    }
    
    return matrix;
}

}


namespace structures {

//! LinkedStack implementation
template<typename T>
class LinkedStack {
 public:
    LinkedStack();
    ~LinkedStack();
    //! Limpa pilha
    void clear();
    //! Limpa pilha
    void push(const T& data);
    //! Limpa pilha
    T pop();
    //! Limpa pilha
    T& top() const;
    //! Limpa pilha
    bool empty() const;
    //! Limpa pilha
    std::size_t size() const;

 private:
    class Node {  // Elemento
     public:
        explicit Node(const T& data):
            data_{data}
        {}

        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}

        T& data() {  // getter: dado
            return data_;
        }

        const T& data() const {  // getter const: dado
            return data_;
        }

        Node* next() {  // getter: próximo
            return next_;
        }

        const Node* next() const {  // getter const: próximo
            return next_;
        }

        void next(Node* node) {  // setter: próximo
            next_ = node;
        }

     private:
        T data_;
        Node* next_{nullptr};
    };

    Node* top_{nullptr};
    std::size_t size_{0u};
};

template<typename T>
LinkedStack<T>::LinkedStack() {}

template<typename T>
LinkedStack<T>::~LinkedStack() {
    top_ = nullptr;
    size_ = 0;
}

template<typename T>
void LinkedStack<T>::clear() {
    top_ = nullptr;
    size_ = 0;
}

template<typename T>
void LinkedStack<T>::push(const T& data) {
    Node* new_node = new Node(data, top_);

    top_ = new_node;

    size_++;
}

template<typename T>
T LinkedStack<T>::pop() {
    if (empty()) {
        throw std::out_of_range("Stack is empty");
    }

    Node* removed_node = top_;
    T data = removed_node->data();

    top_ = top_->next();

    size_--;

    delete removed_node;

    return data;
}

template<typename T>
T& LinkedStack<T>::top() const {
    if (empty()) {
        throw std::out_of_range("Stack is empty");
    }

    return top_->data();
}

template<typename T>
bool LinkedStack<T>::empty() const {
    return size_ == 0;
}

template<typename T>
std::size_t LinkedStack<T>::size() const {
    return size_;
}

}  // namespace structures

#endif


namespace xml {
    /**
        @brief Valida o arquivo XML baseando-se num algoritmo que empilha e desempilha tags de abertura fechamento.
    */ 
    bool validate(const std::string& contents);

    /**
        @brief Retorna o conteúdo completo de uma tag específica (incluindo os delimitadores da tag)
        @param string source texto de onde se quer buscar as tags
        @param string open_tag tag de abertura do que se quer buscar
        @param string close_tag tag de fechamento do que se quer buscar
        @param size_t start_index indice da string source de onde será começado a busca
    */
    std::string get_tag(
        const std::string& source, 
        const std::string& open_tag,
        const std::string& close_tag, 
        size_t& start_index
    );

    /**
        @brief Retorna o valor interno de uma tag específica
        @param string source texto de onde se quer buscar as tags
        @param string open_tag tag de abertura do que se quer buscar
        @param string close_tag tag de fechamento do que se quer buscar
    */
    std::string get_value(
        const std::string& source,
        const std::string& open_tag,
        const std::string& close_tag
    );
} // namespace xml


namespace xml {
    bool validate(const std::string& contents) {
        structures::LinkedStack<std::string> tags;

        size_t i = 0u;

        while (i < contents.length())
        {
            // Calcula o íncio e final da próxima tag do arquivo
            size_t start_position = contents.find('<', i);
            size_t end_position = contents.find('>', start_position);

            // Caso o find do início falhe, chegamos ao final do arquivo
            if (start_position == std::string::npos) break;

            // Caso a posição do final falhe, temos um erro no arquivo
            if (end_position == std::string::npos) return false;
            
            // Utiliza substring para buscar a tag completa
            std::string tag = contents.substr(start_position, end_position + 1 - start_position);
            
            // Incrementa a posição de busca inicial para a posição seguinte ao final da tag atual
            i = end_position + 1;

            // Caso seja uma tag de abertura, insere na pilha com uma / no início
            // que será utilizada depois para comparação
            if (tag[1] != '/') {
                tags.push(tag.insert(1, "/"));
            } else {
                // Se tiver uma tag de fechamento com a pilha vazia
                // significa que não havia uma tag de abertura, arquivo inválido
                if (tags.empty()) return false;
                // Se a tag de fechamento for igual ao topo da pilha, desempilha o topo
                else if(tags.top() == tag) tags.pop();
                // Do contrário, erro no arquivo
                else return false;  
            }
        }
        
        return tags.empty();
    }

    std::string get_tag(
        const std::string& source, 
        const std::string& open_tag, 
		const std::string& close_tag, 
        size_t& start_index
    )
    {		
        size_t start_position = source.find(open_tag, start_index);
        size_t end_position = source.find(close_tag, start_position);
                
        start_position += open_tag.length();

        std::string tag_contents = source.substr(start_position, end_position - start_position);
        
        return tag_contents;
    }

    std::string get_value(
        const std::string& source, 
        const std::string& open_tag, 
        const std::string& close_tag
    )
    {
        std::size_t pos{0};

        return get_tag(source, open_tag, close_tag, pos);
    }
} // namespace xml