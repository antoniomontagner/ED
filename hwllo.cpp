// outside libs for funccion
#include <iostream> // read write data print
#include <vector>
#include <string.h> // clica e ve funcoes
#include <fstream>
#include <cstdlib> // ramdom,convert
#include <limits>  // max min values
#include <ctime>
#include <cmath>
#include <stdlib.h> // alocar memoria


//#include "rascunho.cpp"
/* se colococar <limits> vai procurar primeiro nas bibliotecas internas
        se for " limits.h" vai procurar na pasta
        */

// comentario

/* 
auto T = o T vai ser um tipo automatico

multiplo coment

g++ -std=c++11 arquivo.cpp
./a.out

+, - , * , / , % , ++ , --
== , != , > , < , >= , <= 
*= , /= 
&& , || , and , or
  
\0      ---- caracter nulo para finalizar coisas



sizeof( )
// cin<< so pode uma palavra
// gets ( n)  pode mais de uma palavra


*/
/*
%d  int
%f  float
%c  char
%s  string
%u  unsigned int
%lu unsigned long int
%g  double  

*/


using namespace std;
int main()
//   int main(int argc, char argv[]) // argc= argumento de comando, algo colocado junto na linha de comando
// strings passadas pro programa quando executado

{
    //msg int 9;
    // #define const = 10

    //    cin >> numero; // entrada de dado
    //      printf(" ");
    //    char a = 'a'; // ascii table
    //                  //    cout << (int)a << endl; // corresponde ao numero 97 em ascii
    //
    //    //   cout << "hello" << endl;
    //      #define contante = para constante em C
    //    const double PI = 3.1415;
    //
    //    bool VouF = 1 > 0; //vai retorna 1 ou verdade
    //    //cout << VouF << endl;
    //    int myAge = 55;
    //
    //    myAge *= 2;
    //    //cout << myAge << "jaca" << endl;
    //
    //    float nFloat = 1.34251213;
    //
    //    int tamanho = sizeof(VouF);
    //    //cout << "tamanho em bites: " << tamanho << endl;
    //
    //    //cout << "saida: " << nFloat << endl; //add coisa a saida
    //
    //    //cout << "1+1: " << (float)4 / 5 << endl;
    //
    //    //cout << myAge << endl;
    //
    //    ///////////////////////////////////////////////////
    //    int dinheiro = 10;
    //    if (dinheiro >= 10)
    //    {
    //        //cout << "dinheiro 10" << endl;
    //
    //        if (dinheiro <= 20 or dinheiro >= 12)
    //        {
    //            //cout << "jaca" << endl;
    //        }
    //        else
    //        {
    //            //pass deixa sem nada
    //        }
    //    }
    //
    //    else
    //    {
    //        //cout << "nao maior que 10" << endl;
    //    }
    //
    //    /////////////////////////////////////////////////////////
    //    int jaca = 10;
    //    cout << "Numero" << endl;
    //    //cin >> jaca;
    //    switch (---)
    //    {
    //    case 9:
    //    //    cout << "switch case 9" << endl;
    //    //break;        se tirar o break ele passa direto para o proximo
    //    case 10:
    //        //  cout << "switch case 10" << endl;
    //        break;
    //    default:
    //        //cout << " default" << endl;
    //        break;
    //    }
    //
    //    /////////////////////////////////////////////////////////
    //    int n;
    //    while (n <= 10)
    //    {
    //        n++;
    //        //cout << n << endl;
    //        if (n == 5)
    //        {
    //            break;
    //        }
    //    }
    //
    //    /////////////////////////////////////////////////////////
    //    int i, j;
    //    for (i = 0; i < 12; i++) // ( parte1 parte2 parte3)
    //    {
    //        //cout<<i<<endl;
    //    }
    //
    //    for (i = 0, j = 1; i < 4, j < 6; i++, j++)
    //    {
    //        //cout<<i <<endl;
    //    }
    //
    //    /////////////////////////////////////////////////////////
    //    // aula 19 strig        \0 é nulo
    //
    //    char nome[] = {'m', 'a', 'a', 'a', '\0'};
    //    char nome2[] = "ma";
    //    int k = 0;
    //    while (nome2[k] != '\0')  // (true)
    //    {
    //        cout << nome2[k++] << endl;
    //    }
    //
    //    // do - while
    //    do
    //    {
    //        /* code */
    //        cout << "print ao menos uma vez" << endl;
    //    } while (k <= 1);
    //
    //    int tam;
    //    for (tam = 0; nome[tam]; tam++)
    //        ;
    //    for (int i = tam - 1; i >= 0; i--)
    //    {
    //        cout << nome[i] << endl;
    //    }
    //
    //    ///////////////////////////////////////////////
    //    // strings aula 20
    //
    //    tam = strlen(nome);
    //    for (int i = tam - 1; i >= 0; i--)
    //    {
    //        cout << nome[i] << endl;
    //    }
    //    // isalpha(nome[0]) retorna (true/false) se for alfabeto o elemento
    // isdigit (nome[0]) retorna se é digito
    // isupper (nome[0]) maiusculo
    // islower (nome[0])
    // isspace (nome[0]) se é caracter expasso
    // strlen( n)
    // tolower(n) minusculo
    // toupper(n)
    // strcat ( n1, n2)  concatenar
    // strcomp(n1,n2)       comparar

    /////////////////////////////////////////
    // 21  ponteiro

    // int n = 4; // esta alocado em uma memoria
    // int *pn, *pJaca;   // ponteiro
    // pn = &n;   // pega o endereco(mem) de n
    //  *pn = 424; // vai mudar o valor da memoria de "n"
    // vai retorna a posicao de memoria
    // 0x7ffc7f092f64
    // mas como esta usando 'int' que tem tamanho 4bites
    // a proxima alocavao de memoria soma 4
    // ( *pn +=1 ) = 0x7ffc7f092f68 e a proxima sera 0x7ffc7f092f6c

    //////////////// em funcoes

    //void somar ( float *var, float valor);
    //
    //int main (){
    //
    //    somar ( &num , 15)
    //}
    //
    //
    //void soma ( float *var, float valor){
    //    *var += valor; // vai alterar o valor que for passado pela memoria
    //}

    //////////////////////////////////////////////////////////
    // alocar memoria

    /* 
    int* parray = new int [10]; // vai alocar memoria
    int** pparray = &a; // um ponteiro de ponteiro
    // * (paaray ) == paaray[0] 
    // *(parray + 1) == parray[1]
    delete a; // vai deletar a memoria alocada
    // delete[] (*n)
    string *nome;
    nome = (string *) malloc (sizeof (string) +1);


    for (i=1; i<10; i++) if (vetor[i]< *min) *min = veor[i];                            // for if
    for (i=1; i<10; i++) printf("jaca");


    int *parray[3] = {1,2,3}; // um argumento pra cada memoria

 */

    //    ////////////////////////////////////////////////////////////////
    //    //
    //
    //    const int jaca = 3;
    //
    //    int *p1;
    //    p1 = &jaca;
    //    p1 = 4// altera a posicao
    //    *p1 = 4// altera o valor que ta nessa posicao
    //
    //
    //
    //////////////////////////////////////////////////////////
    // aula 27    classes    struct/class

    //char* array = new char[100]; // pilha de memoria nao é alocada na compilacao, constante é

    //char pessoas [4] [100]; // é uma matriz, primeiro é o numero de pessoas e o segundo o comprimento
    /*
    class Pessoa
    { // struct ou class para criar uma classe
        char nome[100];
        int idade;
    } t_pessoa; // nome resumido da classe, nao precisa usar "struct pessoa p"

    struct Jaca
    {
        // protected:  apenas dentro da classe
        // construtor
    public:
        string nome;
        int idade;
        Jaca(string nome, int idade)
        {
            this->nome = nome;
            this->idade = idade;
        }

    private: // acesso so por metodos declarados
        int c;
        int gay(int c)
        {                // metodo dentro da classe
            this->c = c; // para usar o valor passado
            cout << c << endl;
            return this->c; // acesso argumentos da classe
        }

    public: // funcao set para usar privado
        int UseGay(int c)
        {
            this->c = c;
            int a;
            a = gay(c);
            return a;
        }

        virtual void move() = 0; // funcao virtual tem que ser implementada pela heranca

        int getInt()
        { // get
            return this->c;
        }

        void setINT(int n)
        { // set private c para n
            this->c = n;
        }

        /* data */
    /*
    };
    // jaca j;
    // set
    // j.gay(3);
    Jaca jaca1("jaca", 2); // criar jaca
    jaca1.getInt();        // get

    class Ga : public Jaca
    { // HERANCA
    public:
        int getInt()
        {
            cout << "jaca" << endl;
            return this->c;
        }

        virtual void move(){
            cout<<'cui'<<endl; // classe implementada
        }


    }*/

    // t_pessoa p[2];  // gera 3 pessoas de uma vez
    // strcpy(p[0].nome, "jaca");
    //    p.nome = "jaca";
    // p[0].idade = 3;
    //cout << p[0].idade << p[0].nome<< endl;

    // ponteiro
    //    t_pessoa pes;
    //    t_pessoa* ppes;
    //    ppes = &pes;
    //    ppes -> idade = 33;  // acessar local é diferente
    //
    // strcpy (str1, str2);  // copia a str2 na 1
    //////////////////////////////////////////////////////////////////////
    // Class

//
//    class Jaca
//    {
//    private:
//        /* data */
//
//
//
//    public:
//        Jaca(/* args */);
//        ~Jaca();
//
//
//        strcpy()
//    };
//    
//    Jaca::jaca1(/* args */)
//    {
//    }
//    
//    Jaca::~Jaca()
//    {
//    }
//    //////////////////////////////////////////////////////////
//    int vetor[10];
//    for (int i=0; i<10; i++) vetor[i]=i;
//    
//    int *y = vetor;
//    for (int i = 0; i < 10; i++) printf("y: %d, %d, %d, %d, %d\n", y[i]), printf("jaca");
//    for (int i = 0, j = 10; i < 10, j>0; i++, j--) printf("%d, %d \n",i,j);
//
////
////////////////////////////////////////////////////////////////////
//#include <iostream>
//#include <stdio.h>
//using namespace std;
//
//int main (){
//    int vetor[10];
//    for (int i=0; i<10; i++) vetor[i]=i;
//    
//    int *y = vetor;
//    for (int i = 0; i < 10; i++) printf("y: %d, %d, %d, %d, %d\n", y[i]);
//    //for (int i = 0, j = 10; i < 10, j>0; i++, j--) printf("%d, %d \n",i,j);
//    int vet[5] = {1,2,3,4,5};
//    int* pvet;
//    pvet = vet;
//    pvet[0] = 22;
//    cout << pvet[0]<<vet[0]<<endl;
//    pvet = vet+3;
//    cout << pvet<< endl;
//
//    int a;
//    scanf("%d",&a);
//    cout << a;
//    int* pp = &a;
//    printf ("%d",*pp);
//    asm ("movl %ebx, %eax");
//    printf("%b",asm);
//
//    //arr = (int*)malloc(ln * sizeof(int));
////    while (bool a = true){
////        int *arr = (int*)malloc( sizeof(int));
////        asm ("add $a1, $a2, $a3");
////    }
//
//
//    return 0;
//}
//
///////////////////////////////////////////////////////////
// TEMPLATE
// 
// template< typename T> T soma(T n1, T n2){
//     return n1 + n2
//     // como se T fosse um generico e pode ser passado qualquer numer sem definir o tipo de resultado de saida da soma
//     // pode ser int, float e etc....
// }
// 
// 
// ////////////////--------------------------------------------
// TRY catch
//try { a%2}
//catch   (a=1){
//    cout<<"erro";
//}
//
////////////////--------------------------------------------
// alocacao de memoria
int  vet  = new int[4]; // aloca uma memoria de certo tamanho
delete [] vet;      // deleto o conjunto do vet []


    return 0;
}

//
//
/////////////////////////////////////////////////////////
// FUNCAO
// se colocar "bool par(int num;" no inicio do codigo
// nao da erro pois diz que tem uma funcao no codigo
// tipo do retorno da funcao "bool"

bool par(int num)
{
    if (num % 2 == 0)
        return true;
    else
    {
        return false;
    }
}

void msg()
{
    cout << "funcao que nao tem retorno" << endl;
}

void msg(int n)
{
    cout << "multiplas funcoes diferenciadas por argumentos" << endl;
}
//  msg();  para chamar a funcao

/////////////////////////////////////////////////////////
// incluir modulos

// #include "rascunho.cpp"

/////////////////////////////////////////////////////////
// statica

static int num_jaca = 1;
/* vai permanecer o numero ate o fim da execucao
pode usar como contador para ver quantas vezes passou
pela funcao
*/

/////////////////////////////////////////////////////////
int jaca()
{
    int vetor[100];
    for (int i = 0; i <= 100; i++)
    {
        vetor[i] = i;
        cout << vetor[i] << endl;
    }
    return 0;
}
//int vetor[] = {1, 2, 3, 4, '\0'}; // ja cria 4 vetores direto com os valor na ordem

// while( vetor) == while (vetor != \0)

// vetor [0].... vetor[12]
/*

do {
    int asas = 0
} while (vetor)
{
    return 1;
}

*/