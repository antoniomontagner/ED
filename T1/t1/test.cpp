/** INE508 
 *	@author Antonio S M
 *	@version 19.20.37.42
 *  @brief Projeto I - processamento de XML com imagens binárias
*/

/**
 *	@brief includes a serem usados no trabalho
*/
#include <iostream>
#include <string>
#include <fstream>
#include <stack>
#include <list>
#include <queue>

/**
 *  @brief retornar o nome do arquivo xml a ser utilizado
*/
std::string nome_arq() {
	std::string arqXML;
	std::cin >> arqXML;
	return arqXML;
};

/**
 *    @brief instancias que serão utilizadas e a serem completadas
*/

/**
 *    @brief pegar os nomes que estão no arquivo e colocar na lista
*/
int get_nome(std::fstream& file, std::list<std::string>& list_nome);

/**
 *    @brief pegar a altura e colocar na lista
*/
int get_altura(std::fstream& file, std::list<std::string>& list_altura);

/**
 *    @brief pegar o comprimento e colocar na lista
*/
int get_comprimento(std::fstream& file, std::list<std::string>& list_comprimento);

/**
 *    @brief pegar os dados e colocar na lista
*/
int get_data(std::fstream& file, std::list<std::string>& list_dado, std::list<std::string> list_altura);

/**
 *    @brief retorna a quantidade de elementos da matriz
*/
int matrix_Q(std::string name, std::string altura, std::string comprimento, std::string data);

/**
 *    @brief verificar o se existe o arq xml, caso não, retorna 0 junto com uma mensagem de erro
*/
bool verificar(std::fstream& file);


/**
 * @brief MAIN
*/
int main() {
	auto file_name = nome_arq();
	std::fstream file(file_name);
	if (verificar(file) == true) {  // retorna 0 junto com uma mensagem de erro caso nao seja válido
		std::cout << "error";
		return 0;
	}
	
	std::list<std::string> nome_lista;   // recebe o nome da imagem
	std::list<std::string> altura_lista; // recebe a altura
	std::list<std::string> comprimento_lista;  // recebe o comprimento
	std::list<std::string> dados_lista;   // recebe os dados


	/**
	 *    @brief obter dados dos arquivos
	 *    @brief pegar os dados nome, altura, comprimento e a matriz
	*/
	file.open(file_name);   // abrir a imagem 
	get_nome(file, nome_lista); // pegar o nome da imagem do arquivo
	file.open(file_name);
	get_altura(file, altura_lista);
	file.open(file_name);
	get_comprimento(file, comprimento_lista);
	file.open(file_name);
	get_data(file, dados_lista, altura_lista);

	auto size = nome_lista.size();
	for (int i = 0; i != size; i++) {

		std::cout << nome_lista.front() << " " << matrix_Q(nome_lista.front(),   // retorno da quantidade de elementos específico
		altura_lista.front(), comprimento_lista.front(), dados_lista.front()) << std::endl;
		nome_lista.pop_front();altura_lista.pop_front();comprimento_lista.pop_front();dados_lista.pop_front();
	}

	return 0;
}


/**
 *    @brief verificar se o arquivo XML passado "file" é valido, 
 *    @brief pegar os dados do arquivo passado em um escopo diferente do primeiro elemento de "list_altura", 
 *    @brief retorna-los em uma lista "list_dado" 
*/
int get_data(std::fstream& file, std::list<std::string>& list_dado, std::list<std::string> list_altura) {
	std::list<std::string> aux;
	if (file.is_open()){

		std::string line;
		while(std::getline(file, line)){

			if (line.find('<') == line.npos && line != "") {
					aux.push_back(line);
			}
		}
	}
	auto size = list_altura.size();
	for (auto i = 0; i != size; i++) {

		std::string empilha;
		for (int j = 0; j != stoi(list_altura.front()); j++) {
				empilha = empilha + aux.front();

			aux.pop_front();
		}
		list_dado.push_back(empilha);
		list_altura.pop_front();
	}

	file.close();   // fechar o arq
	return list_dado.size();
}


/**
 * @brief retorna a quantidade de elementos da matriz 
 * @brief em um escopo de altura X comprimento e utilizando a lista de dados do XML passado
*/
int matrix_Q(std::string name, std::string altura, std::string comprimento, std::string data) {
	// pega a matriz e cria uma copia
	auto comp_ = stoi(comprimento); // comprimento
	auto alt_ = stoi(altura);  // altura
	char copy[alt_][comp_];
	char reference[alt_][comp_];

	for (int i = 0; i != alt_; i++)
		for (int j = 0; j != comp_; j++) {
			copy[i][j] = '0';       // copy
		}

	int j = 0;
	for (int i = 0; i != data.size(); i++) {
		if (i%comp_ == 0 && i != 0) {
			j++;
		}
		reference[j][i%comp_] = data.at(i); 
	}

	int n = 0;
	char label = '1';
	std::queue<std::pair<int, int>> kiwi;   // cria uma lista
	for (int i = 0; i != alt_; i++) {

		for (int k = 0; k != comp_; k++) {

			if (reference[i][k] == '1' && copy[i][k] == '0') {

				kiwi.push(std::make_pair(i, k));    // armazena a coordenada 
				while(!kiwi.empty()){

					auto temp = kiwi.front();   // armazena em temp
					kiwi.pop(); // da pop 
					if (temp.second-1 >= 0)
						if (reference[temp.first][temp.second-1] == '1' && copy[temp.first][temp.second-1] == '0') {
							kiwi.push(std::make_pair(temp.first, temp.second-1));
							copy[temp.first][temp.second-1] = label;    // enfileira se for igual a zero
						}
					if (temp.first+1 < alt_)
						if(reference[temp.first+1][temp.second] == '1' && copy[temp.first+1][temp.second] == '0') {
							kiwi.push(std::make_pair(temp.first+1, temp.second));   // enfileira se for igual a zero
							copy[temp.first+1][temp.second] = label;
						}
					if (temp.first-1 >= 0)
						if(reference[temp.first-1][temp.second] == '1' && copy[temp.first-1][temp.second] == '0') {
							kiwi.push(std::make_pair(temp.first-1, temp.second));   // enfileira
							copy[temp.first-1][temp.second] = label;
						}
					if (temp.second+1 < comp_)
						if (reference[temp.first][temp.second+1] == '1' && copy[temp.first][temp.second+1] == '0') {
							kiwi.push(std::make_pair(temp.first, temp.second+1));   // enfileira
							copy[temp.first][temp.second+1] = label;
						}
						copy[temp.first][temp.second] = label;
				}
				n++;
			}
		}
	}
	return n;
}


/**
 *    @brief pegar os nomes que estão no arquivo XML e colocar em uma lista
*/
int get_nome(std::fstream& file, std::list<std::string>& list_nome) {
	// pega nome da imagem
	if (file.is_open()){

		std::string line;
		while(std::getline(file, line)){

			std::string name;
			while (line.find("<name>") != line.npos) {

				auto pos = line.find("<name>");    // procura o nome
				for (std::string::size_type i = pos+6; i < line.size(); ++i) {

					if (line[i] == '<') {
						line[pos+1] = '@'; // adiciona no fim
						break;
					} else {
						name = name + line[i];
					}
				}
			}

			if (name != "") {
				list_nome.push_back(name); // adiciona o nome na lista
			}
		}
	}
	file.close();    // fechar o arq
	return list_nome.size();
}


/**
 *    @brief verificar o se existe o arq xml, caso não, retorna erro junto com uma mensagem de erro
*/
bool verificar(std::fstream& file) {
	// verifica os erros 
	std::stack<std::string> stack;
	bool read = false;
	bool error = false;
	int m = 0;
	std::string temp_ = "";
	if (file.is_open()) {

		std::string line = "";
		while(std::getline(file, line)) {   // percorrer a string

			for (std::string::size_type i = 0; i < line.size(); ++i) {

				if (line[i] == '<') {
					auto desempilha = false;
					if(line[i+1] == '/') {
						i++;
						desempilha = true;
					}

					std::string top ="";
					for(std::string::size_type j = i+1; j < line.size(); ++j) {

						if (line[j] == '>' && desempilha) { 

							if (!stack.empty()) {

								if (stack.top().compare(top) == 0) {   // checar se é topo
									stack.pop();
									break;
								} else {
									error = true;   // caso nao, passa erro
									break;
								}
							} else {
								break;
								error = true;
							}
						} else if (line[j] == '>' && !desempilha) {
								stack.push(top);
								break;
							}
						top = top + (line[j]);
					}
				}
			}
		}
	} else {
			printf("Não foi possivel abrir o xml.\n");
		}
	if (!stack.empty()) {
		error = true;
	}
	file.close();   // fechar o arq
	return error;
}


/**
 *    @brief abre o arquivo e conta suas linhas para pegar a altura e colocar na lista
*/
int get_altura(std::fstream& file, std::list<std::string>& list_altura) {
	// pegar altura
	if (file.is_open()){

		std::string line;
		while(std::getline(file, line)){

			std::string comp;   // comprimento
			while (line.find("<height>") != line.npos) {    // procurar tag de altura

				auto pos = line.find("<height>");      // pegar altura
				for (std::string::size_type i = pos+8; i < line.size(); ++i) {

					if (line[i] == '<') {
						line[pos+1] = '@'; // adinionar no fim
						break;
					} else {
						comp = comp + line[i];
					}
				}
			}
			if (comp != "") {
				list_altura.push_back(comp);
			}
		}
	}
	file.close();   // fechar o arq
	return list_altura.size();
}


/**
 *    @brief abre o arquivo e conta suas linhas para pegar o comprimento e colocar na lista
*/
int get_comprimento(std::fstream& file, std::list<std::string>& list_comprimento) {
	// pegar comprimento
	if (file.is_open()){

		std::string line;
		while(std::getline(file, line)){

			std::string alt;    // altura
			while (line.find("<width>") != line.npos) {     // procurar tag de comprimento

				auto pos = line.find("<width>");       // pegar comprimento
				for (std::string::size_type i = pos+7; i < line.size(); ++i) {

					if (line[i] == '<') {
						line[pos+1] = '@'; // adinionar no fim
						break;
					} else {
						alt = alt + line[i];
					}
				}
			}
			if (alt != "") {
				list_comprimento.push_back(alt);
			}
		}
	}
	file.close();   // fechar o arq
	return list_comprimento.size();
}
