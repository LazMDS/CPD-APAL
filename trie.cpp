#include <iostream>
using namespace std;
 
// Define o tamanho do caractere
#define CHAR_SIZE 128
 
// Uma classe para armazenar um nó Trie
class Trie
{
public:
    bool ehFolha;
    Trie* character[CHAR_SIZE];
 
    // Construtor
    Trie()
    {
        this->ehFolha = false;
 
        for (int i = 0; i < CHAR_SIZE; i++) {
            this->character[i] = nullptr;
        }
    }
 
    void insert(string);
    bool deletion(Trie*&, string);
    bool search(string);
    bool haveChildren(Trie const*);
};
 
// Função iterativa para inserir uma chave em um Trie
void Trie::insert(string chave)
{
    // inicia do nó raiz
    Trie* atual = this;
    for (int i = 0; i < chave.length(); i++)
    {
        // cria um novo nó se o caminho não existir
        if (atual->character[chave[i]] == nullptr) {
            atual->character[chave[i]] = new Trie();
        }
 
        // vai para o próximo nó
        atual = atual->character[chave[i]];
    }
 
    // marca o nodo atual como uma folha
    atual->ehFolha = true;
}
 
// Função iterativa para pesquisar uma chave em um Trie. Ele retorna verdadeiro
// se a chave for encontrada no Trie; caso contrário, retorna falso
bool Trie::search(string chave)
{
    // retorna false se Trie estiver vazio
    if (this == nullptr) {
        return false;
    }
 
    Trie* atual = this;
    for (int i = 0; i < chave.length(); i++)
    {
        // vai para o próximo nó
        atual = atual->character[chave[i]];
 
        // se a string for inválida (alcançou o final de um caminho no Trie)
        if (atual == nullptr) {
            return false;
        }
    }
 
    // retorna true se o nó atual for uma folha e o
    // fim da string é atingido
    return atual->ehFolha;
}
 
// Retorna true se um determinado nó tiver algum filho
bool Trie::haveChildren(Trie const* atual)
{
    for (int i = 0; i < CHAR_SIZE; i++)
    {
        if (atual->character[i]) {
            return true;    // filho encontrado
        }
    }
 
    return false;
}
 
// Função recursivo para deletar uma chave no Trie
bool Trie::deletion(Trie*& atual, string chave)
{
    // retorna se Trie estiver vazio
    if (atual == nullptr) {
        return false;
    }
 
    // se o final da chave não for alcançado
    if (chave.length())
    {
        //recorre para o nó correspondente ao próximo caractere na chave
        // e se retornar verdadeiro, exclui o nó atual (se não for folha)
 
        if (atual != nullptr &&
            atual->character[chave[0]] != nullptr &&
            deletion(atual->character[chave[0]], chave.substr(1)) &&
            atual->ehFolha == false)
        {
            if (!haveChildren(atual))
            {
                delete atual;
                atual = nullptr;
                return true;
            }
            else {
                return false;
            }
        }
    }
 
    // se o fim da chave for atingido
    if (chave.length() == 0 && atual->ehFolha)
    {
        // se o nodo atual for um nodo folha e não tiver filhos
        if (!haveChildren(atual))
        {
            //deleta o nó atual
            delete atual;
            atual = nullptr;
 
            // exclui os nós pais não-folha
            return true;
        }
 
        // se o nodo atual for um nodo folha e tiver filhos
        else {
            // marca o nó atual como um nó não folha (DON'T DELETE IT)
            atual->ehFolha = false;
 
            // não exclui seus nós pais
            return false;
        }
    }
 
    return false;
}
 
// Implementação C++ da estrutura de dados Trie
int main()
{
    Trie* head = new Trie();
 
    head->insert("hello");
    cout << head->search("hello") << " ";      // imprime 1
 
    head->insert("helloworld");
    cout << head->search("helloworld") << " "; // imprime 1
 
    cout << head->search("helll") << " ";      // imprime 0 (Não encontrado)
 
    head->insert("hell");
    cout << head->search("hell") << " ";       // imprime 1
 
    head->insert("h");
    cout << head->search("h");                 // imprime 1
 
    cout << endl;
 
    head->deletion(head, "hello");
    cout << head->search("hello") << " ";      // imprime 0
 
    cout << head->search("helloworld") << " "; // imprime 1
    cout << head->search("hell");              // imprime 1
 
    cout << endl;
 
    head->deletion(head, "h");
    cout << head->search("h") << " ";          // imprime 0
    cout << head->search("hell") << " ";       // imprime 1
    cout << head->search("helloworld");        // imprime 1
 
    cout << endl;
 
    head->deletion(head, "helloworld");
    cout << head->search("helloworld") << " "; // imprime 0
    cout << head->search("hell") << " ";       // imprime 1
 
    head->deletion(head, "hell");
    cout << head->search("hell");              // imprime 0
 
    cout << endl;
 
    if (head == nullptr) {
        cout << "Trie empty!!\n";              // Trie está vazio agora
    }
 
    cout << head->search("hell");              // imprime 0
 
    return 0;
}