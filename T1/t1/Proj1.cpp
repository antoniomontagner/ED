//! ###	Copyright [2021] <Antonio S M>
/*! @version 19.20.37.42 */
///  ### Projeto I - processamento de XML com imagens binárias
#define owner = < antoniomontagner309@gmail.com >


#include <iostream>
#include <string>
#include <fstream>
#include <stack>
#include <list>
#include <queue>

/**		### retornar nome do arquivo
 *  @brief retornar o nome do arquivo xml a ser utilizado
*/
std::string nome_arq() {
	std::string arqXML;
	std::cin >> arqXML;
	return arqXML;
};

/**
 *    \brief instancias que serão utilizadas e a serem completadas
*/

/**
 *    ## pegar os nomes que estão no arquivo e colocar na lista
*/
int get_nome(std::fstream& file, std::list<std::string>& list_nome);

/**
 *    ## pegar a altura e colocar na lista
*/
int get_altura(std::fstream& file, std::list<std::string>& list_altura);


/**
 *   ## pegar o comprimento e colocar na lista
*/
int get_comprimento(std::fstream& file, std::list<std::string>& list_comprimento);

/**
 *    ## pegar os dados e colocar na lista
*/
int get_data(std::fstream& file, std::list<std::string>& list_dado, std::list<std::string> list_altura);

/**
 *    ## retorna a quantidade de elementos da matriz
*/
int matrix_Q(std::string name, std::string altura, std::string comprimento, std::string data);

/**
 *    ## verificar se existe o arq xml, caso não, retorna 0 junto com uma mensagem de erro
*/
bool verificar(std::fstream& file);


/**
 * # MAIN
*/
int main() {
	auto file_name = nome_arq();
	std::fstream file(file_name);
	if (verificar(file) == true) {  /*! "verificar(file)" retorna 0 junto com uma mensagem de erro caso o arquivo nao seja válido */
		std::cout << "error";
		return 0;
	}
	/*!
	 * \param nome_lista
	 * \param altura_lista
	 * \param comprimento_lista
	 * \param dados_lista
	 * recebe o nome da imagem, altura, comprimento, dados
	*/
	std::list<std::string> nome_lista;
	std::list<std::string> altura_lista;
	std::list<std::string> comprimento_lista;
	std::list<std::string> dados_lista;


	/*! ## obter dados dos arquivos
	 *    @brief pegar os dados nome, altura, comprimento e a matriz
	*/
	file.open(file_name);   /*! abrir a imagem */ 
	get_nome(file, nome_lista); /*! pegar o nome da imagem do arquivo */
	file.open(file_name);
	get_altura(file, altura_lista);	/*! pegar altura da imagem do arquivo*/
	file.open(file_name);
	get_comprimento(file, comprimento_lista); /*! pegar comprimento da imagem do arquivo*/
	file.open(file_name);
	get_data(file, dados_lista, altura_lista); /*! pegar dados da imagem do arquivo*/

	auto size = nome_lista.size();
	for (int i = 0; i != size; i++) {

		std::cout << nome_lista.front() << " " << matrix_Q(nome_lista.front(),   /*! retorno da quantidade de elementos específico */
		altura_lista.front(), comprimento_lista.front(), dados_lista.front()) << std::endl;
		nome_lista.pop_front();altura_lista.pop_front();comprimento_lista.pop_front();dados_lista.pop_front();
	}

	return 0;
}


/*!		### get_data
 *    @brief verificar se o arquivo XML passado "file" é valido, 
 *    @brief pegar os dados do arquivo passado em um escopo diferente do primeiro elemento de "list_altura", 
 *    @brief retorna-los em uma lista "list_dado" 
 * \param file, list_dado, list_altura
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
	return list_dado.size(); /*! \return list_dado.size() */
}

/*!
 * \brief retorna a quantidade de elementos da matriz 
 *  em um escopo de altura X comprimento e utilizando a lista de dados do XML passado
* \param name, altura, comprimento, data
*/
int matrix_Q(std::string name, std::string altura, std::string comprimento, std::string data) {
	//< pega a matriz e cria uma copia
	/*! \param comp_ */
	/*! \param alt_ */
	auto comp_ = stoi(comprimento);
	auto alt_ = stoi(altura);
	char copy[alt_][comp_];
	char reference[alt_][comp_];

	for (int i = 0; i != alt_; i++)
		for (int j = 0; j != comp_; j++) {
			copy[i][j] = '0';
		}

	int j = 0;
	for (int i = 0; i != data.size(); i++) {
		if (i%comp_ == 0 && i != 0) {
			j++;
		}
		reference[j][i%comp_] = data.at(i); 
	}

	int n_elementos = 0;
	char label = '1';
	std::queue<std::pair<int, int>> list_q;   /*! cria uma lista para armazenar  os elementos da matriz*/
	for (int i = 0; i != alt_; i++) {

		for (int k = 0; k != comp_; k++) {

			if (reference[i][k] == '1' && copy[i][k] == '0') {

				list_q.push(std::make_pair(i, k));    /*! armazena o elemento da coordenada "push(std::make_pair(i, k))" */
				while(!list_q.empty()){

					auto temp = list_q.front();   /*! armazenar a lista em uma temporaria para retorno e limpar a lista principal */
					list_q.pop();
					if (temp.second-1 >= 0)	/*! verificar se o comprimento da lista temporaria e maior ou igual a 0 */
						if (reference[temp.first][temp.second-1] == '1' && copy[temp.first][temp.second-1] == '0') {
							list_q.push(std::make_pair(temp.first, temp.second-1));
							copy[temp.first][temp.second-1] = label;
						}
					if (temp.first+1 < alt_) /*! verificar se a altura da lista temporaria e menor que a altura passada */
						if(reference[temp.first+1][temp.second] == '1' && copy[temp.first+1][temp.second] == '0') {
							list_q.push(std::make_pair(temp.first+1, temp.second));
							copy[temp.first+1][temp.second] = label;
						}
					if (temp.first-1 >= 0) /*! verificar se a altura da lista temporaria e maior ou igual a 0 */
						if(reference[temp.first-1][temp.second] == '1' && copy[temp.first-1][temp.second] == '0') {
							list_q.push(std::make_pair(temp.first-1, temp.second));
							copy[temp.first-1][temp.second] = label;
						}
					if (temp.second+1 < comp_) /*! verificar se o comprimento da lista temporaria e menor que o comprimento passado */
						if (reference[temp.first][temp.second+1] == '1' && copy[temp.first][temp.second+1] == '0') {
							list_q.push(std::make_pair(temp.first, temp.second+1));   /*! enfileira */
							copy[temp.first][temp.second+1] = label;
						}
						copy[temp.first][temp.second] = label;
				}
				n_elementos++;
			}
		}
	}
	return n_elementos;	/*! \return n_elementos */
}


/*!
 *    @brief pegar os nomes que estão no arquivo XML e colocar em uma lista
 * 		\param file
 * 		\param list_nome
*/
int get_nome(std::fstream& file, std::list<std::string>& list_nome) {
	/*! pega nome da imagem */
	if (file.is_open()){

		std::string line;
		while(std::getline(file, line)){

			std::string name;
			while (line.find("<name>") != line.npos) {

				auto pos = line.find("<name>");    /*! "line.find()" procura o inicio do nome usando a tag <name>*/
				for (std::string::size_type i = pos+6; i < line.size(); ++i) {

					if (line[i] == '<') {
						line[pos+1] = '@'; /*! "line[pos+1]" adinionar no fim um marcador "@" */
						break;
					} else {
						name = name + line[i];
					}
				}
			}

			if (name != "") {
				list_nome.push_back(name); /*! "list_nome.push_back(name)" adiciona o nome na lista de nomes */
			}
		}
	}
	file.close();    /*! fechar o arquivo apor fazer a verificação e obter o nome */
	return list_nome.size();	/*! \return list_nome.size() */
}


/*!
 *    \brief verificar o se existe o arq xml, caso não, retorna erro junto com uma mensagem de erro.
 * 		\param file
*/
bool verificar(std::fstream& file) {
	/*! primeiro vamos verificar os erros  
	* \param stack
	* \param read
	* \param error
	*/
	std::stack<std::string> stack;
	bool read = false;
	bool error = false;
	int m = 0;
	std::string temp_ = "";
	if (file.is_open()) {

		std::string line = "";
		while(std::getline(file, line)) {   /*! usar getline para percorrer a string */

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

								if (stack.top().compare(top) == 0) {   /*! checar se é topo da lista para continuar ou nao */
									stack.pop();
									break;
								} else {
									error = true;   /*! caso nao seja topo da lista, passa erro e retorna */
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
	file.close();   /*! fechar o arquivo apor fazer a verificação */
	return error;	/*! \return error */
}


/*!
 *    \brief get_altura abre o arquivo e conta suas linhas para pegar a altura e colocar na lista de retorno.
 * 		\param file
 * 		\param list_altura
*/
int get_altura(std::fstream& file, std::list<std::string>& list_altura) {
	/*! verificar se esta aberto o arquivo e pegar altura */
	if (file.is_open()){

		std::string line;
		while(std::getline(file, line)){

			std::string comp;   /*! \param comprimento */
			while (line.find("<height>") != line.npos) {    /*! enquanto a posicao da tag "height" estiver diferente da posição atual  */

				auto pos = line.find("<height>");      /*! "line.find() " pegar altura */
				for (std::string::size_type i = pos+8; i < line.size(); ++i) {

					if (line[i] == '<') {
						line[pos+1] = '@'; /*! "line[pos+1]" adinionar no fim um marcador "@" */
						break;
					} else {
						comp = comp + line[i];	/*! atualizar comprimento + linha atual */
					}
				}
			}
			if (comp != "") {
				list_altura.push_back(comp);
			}
		}
	}
	file.close();   /*! fechar o arquivo apos criar a lista com os dados para retorno */
	return list_altura.size(); /*! \return  list_altura.size() */
}


/*!
 *    @brief abre o arquivo e conta suas linhas para pegar o comprimento e colocar na lista
 *		\param file
 * 		\param list_comprimento
*/
int get_comprimento(std::fstream& file, std::list<std::string>& list_comprimento) {
	/*! pegar comprimento */
	if (file.is_open()){

		std::string line;
		while(std::getline(file, line)){

			std::string alt;    /*! altura */
			while (line.find("<width>") != line.npos) {     /*! "line.find()" procurar tag de comprimento */

				auto pos = line.find("<width>");       /*! \param pos */
														/*! pegar comprimento */
				for (std::string::size_type i = pos+7; i < line.size(); ++i) {

					if (line[i] == '<') {
						line[pos+1] = '@'; /*! "line[pos+1]" adinionar no fim um marcador "@" */
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
	file.close();   /*! fechar o arquivo apos criar a lista com os dados para retorno */
	return list_comprimento.size();	/*! \return  list_comprimento.size() */
}
