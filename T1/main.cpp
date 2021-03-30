#include <iostream>
#include <string>
#include <fstream>
#include <stack>
#include <list>
#include <map>
#include <queue>
 //! gets filename from input stream
std::string get_file_name() {
    std::string xmlfilename;
    std::cin >> xmlfilename;  // entrada
    return xmlfilename;
};
  //! gets the name from every image and pushes it onto the list, closes the file
int get_atribute_name(std::fstream& file, std::list<std::string>& name_list_);
  //! gets the height from every image and pushes it onto the list, closes the file
int get_atribute_height(std::fstream& file, std::list<std::string>& height_list_);
  //! gets the width from every image and pushes it onto the list, closes the file
int get_atribute_width(std::fstream& file, std::list<std::string>& width_list_);
  //! gets the data from every image and pushes it onto the list, closes the file
int get_atribute_data(std::fstream& file, std::list<std::string>& data_list_, std::list<std::string> height_list_);
  //! labelling algorithm, returns the ammount of single elements in the data
int labelling(std::string name, std::string height, std::string width, std::string data);
  //! verifies the xml file
bool verify_xml(std::fstream& file);

//! inicio da funcao main
int main() {
    // pega o nome do arquivo
    auto file_name = get_file_name();
    // abre o arquivo
    std::fstream file(file_name);
    // verificao xml
    if (verify_xml(file) == true) {
        std::cout << "error";
        return 0;
    }
    // strings que receberam os nomes das imagens, altura, comprimento, dados
    std::list<std::string> name_list;
    std::list<std::string> height_list;
    std::list<std::string> width_list;
    std::list<std::string> data_list;
    
    file.open(file_name);
    get_atribute_name(file, name_list);// pega o nome das imagens
    file.open(file_name);

    get_atribute_height(file, height_list);// pega a altura das imagens

    file.open(file_name);

    get_atribute_width(file, width_list);// pega o comprimento das imagens

    file.open(file_name);

    get_atribute_data(file, data_list, height_list);// pega a matriz de zeros 

// segunda parte, funcao que faz labeling
    auto size = name_list.size();
    for (int i = 0; i != size; i++) {
        std::cout << name_list.front() << " " << labelling(name_list.front(),
        height_list.front(), width_list.front(), data_list.front()) << std::endl;
        name_list.pop_front();height_list.pop_front();width_list.pop_front();data_list.pop_front();
    }

    return 0;
}
//! funcao labeling, pega a matriz de referencia, cria uma copia dela e conta o numero de imagens encontradas (labels)
int labelling(std::string name, std::string height, std::string width, std::string data) {
    auto _height = stoi(height);
    auto _width = stoi(width);
    char copy[_height][_width];
    char reference[_height][_width];

     for (int i = 0; i != _height; i++)
         for (int j = 0; j != _width; j++) {
            copy[i][j] = '0'; // de baixo pra cima 
         }  

    int j = 0;
    for (int i = 0; i != data.size(); i++) {
        
        if (i%_width == 0 && i != 0) {
            j++;
        }
        //ESQUERDA PRA DIREITA
        reference[j][i%_width] = data.at(i); 
    }
    int num = 0;
    char label = '1';
    std::queue<std::pair<int, int>> kiwi;// cria uma lista de pares
    for (int i = 0; i != _height; i++) {
        for (int k = 0; k != _width; k++) {
            if (reference[i][k] == '1' && copy[i][k] == '0') {/** se na posição i e k na matriz de referencia for igual
                                                             a 1 e na copia for igual a zero, entao armazena o par de coordenadas*/
                kiwi.push(std::make_pair(i, k));// enfileira o par
                while(!kiwi.empty()){// se a fila nao estiver vazia
                    auto temp = kiwi.front();// armazena as posicoes linha e coluna em temp
                    kiwi.pop();// tira da primeira posição da fila
                    if (temp.first-1 >= 0)// se a linha -1 for maior ou igual a 0, entao
                        if(reference[temp.first-1][temp.second] == '1' && copy[temp.first-1][temp.second] == '0') {
                            kiwi.push(std::make_pair(temp.first-1, temp.second));// enfileira se na matriz copia for igual a zero
                            copy[temp.first-1][temp.second] = label;
                        }
                    if (temp.first+1 < _height)// se a linha +1 for maior ou igual a 0, entao
                        if(reference[temp.first+1][temp.second] == '1' && copy[temp.first+1][temp.second] == '0') {
                            kiwi.push(std::make_pair(temp.first+1, temp.second));// enfileira se na matriz copia for igual a zero
                            copy[temp.first+1][temp.second] = label;
                        }
                    if (temp.second-1 >= 0)// se a coluna -1 for maior ou igual a 0, entao
                        if (reference[temp.first][temp.second-1] == '1' && copy[temp.first][temp.second-1] == '0') {
                            kiwi.push(std::make_pair(temp.first, temp.second-1));// enfileira se na matriz copia for igual a zero
                            copy[temp.first][temp.second-1] = label;
                        }
                    if (temp.second+1 < _width)// se a coluna +1 for maior ou igual a 0, entao
                        if (reference[temp.first][temp.second+1] == '1' && copy[temp.first][temp.second+1] == '0') {
                            kiwi.push(std::make_pair(temp.first, temp.second+1));// enfileira se na matriz copia for igual a zero
                            copy[temp.first][temp.second+1] = label;
                        }
                        copy[temp.first][temp.second] = label;
                     // pondo label na copia de zeros
                }
                num++;
            }
        }
    }

    
    return num;// retorna o valor do label
}
bool verify_xml(std::fstream& file) {// verifica os tres erros propostos no xml
    std::stack<std::string> stack;
        
    bool read = false;
    bool error = false;
    int m = 0;
    std::string temp_data = "";
    if (file.is_open()) {
        std::string line = "";
        while(std::getline(file, line)) {
            // for para percorrer a string da linha obtida com getline
            for (std::string::size_type i = 0; i < line.size(); ++i) {
                if (line[i] == '<') {
                    auto desempilha = false;
                    if(line[i+1] == '/') {
                        i++;
                        desempilha = true;
                    }
                    std::string info ="";
                    for(std::string::size_type j = i+1; j < line.size(); ++j) {
                        if (line[j] == '>' && desempilha) {  ///< se encontrou o fechamento e desempilhar for vdd
                            if (!stack.empty()) {
                                if (stack.top().compare(info) == 0) {  //< checa se o alvo a desempilhar é o topo
                                    stack.pop();  //< se for o topo desempilha
                                    break;
                                } else {  //< se não, lança erro
                                    error = true;
                                    break;
                                }
                            } else {
                                break;
                                error = true;
                            }
                        } else if (line[j] == '>' && !desempilha) {  //< se encontrou fechamento e desempilhar for falso
                                stack.push(info);  //< empilha o tag
                                break;
                            }
                        info = info + (line[j]);
                    }
                }
            }
        }
    } else {
            printf("didnt open!\n");// nao conseguiu abrir o xml
        }
    if (!stack.empty()) {// caso abriu uma tag mas nao fechou
        error = true;
    }
    file.close();// fecha o arquivo
    return error;
}
//! pega o name de cada imagem
int get_atribute_name(std::fstream& file, std::list<std::string>& name_list_) {
    if (file.is_open()){
        std::string line;
        while(std::getline(file, line)){
            std::string name;
            while (line.find("<name>") != line.npos) {
                auto position = line.find("<name>");
                for (std::string::size_type i = position+6; i < line.size(); ++i) {
                    if (line[i] == '<') {
                        line[position+1] = '@';
                        break;
                    } else {
                        name = name + line[i];
                    }
                }
            }
            if (name != "") {
                name_list_.push_back(name);
            }
        }
    }
    file.close();
    return name_list_.size();// retorna os nomes das imagens binarias
}
// pega a altura de cada imagem
int get_atribute_height(std::fstream& file, std::list<std::string>& height_list_) {
    
    if (file.is_open()){
        std::string line;
        while(std::getline(file, line)){
            std::string height;
            while (line.find("<height>") != line.npos) {
                auto position = line.find("<height>");
                for (std::string::size_type i = position+8; i < line.size(); ++i) {
                    if (line[i] == '<') {
                        line[position+1] = '@';
                        break;
                    } else {
                        height = height + line[i];
                    }
                }
            }
            if (height != "") {
                height_list_.push_back(height);
            }
        }
    }
    file.close();
    return height_list_.size();// retorna as alturas das imagens binarias
}
// pega o comprimento de cada imagem
int get_atribute_width(std::fstream& file, std::list<std::string>& width_list_) {
    
    if (file.is_open()){
        std::string line;
        while(std::getline(file, line)){
            std::string width;
            while (line.find("<width>") != line.npos) {
                auto position = line.find("<width>");
                for (std::string::size_type i = position+7; i < line.size(); ++i) {
                    if (line[i] == '<') {
                        line[position+1] = '@';
                        break;
                    } else {
                        width = width + line[i];
                    }
                }
            }
            if (width != "") {
                width_list_.push_back(width);
            }
        }
    }
    file.close();
    return width_list_.size();// retorna os comprimentos das imagens binarias
}
// pega o nome de cada imagem
int get_atribute_data(std::fstream& file, std::list<std::string>& data_list_, std::list<std::string> height_list_) {
    std::list<std::string> aux;
    if (file.is_open()){
        std::string line;
        while(std::getline(file, line)){
            if (line.find('<') == line.npos && line != "") {
                    aux.push_back(line);
            }
        }
    }
    auto size = height_list_.size();
    for (auto i = 0; i != size; i++) {
        std::string empilha;
        for (int j = 0; j != stoi(height_list_.front()); j++) {
                empilha = empilha + aux.front();

            aux.pop_front();
        }
        data_list_.push_back(empilha);
        height_list_.pop_front();
    }

    file.close();
    return data_list_.size();/// retorna os nomes das imagens binarias
}