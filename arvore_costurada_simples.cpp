#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "arvore_costurada_simples.h"

using namespace std;

struct ArvCosSimp { // ArvCosSimp == Árvore com costura simples.
    int info;
    struct ArvCosSimp* esq;
    struct ArvCosSimp* dir;
    bool costura; // Sinalizador de costura
};

// Função que inicializa a árvore
ArvCosSimp* criarArvoreVazia(){
     return NULL;
}

// Função que retorna se a árvore está vazia
bool arvoreVazia(ArvCosSimp* raiz){
    return (raiz == NULL);
}

//inserção de elementos na árvore
void inserirElemento(ArvCosSimp** raiz, int novaInfo){

    // Alocação de memória para novo elemento e atribuição de informações
    ArvCosSimp* novoElemento = (ArvCosSimp*)malloc(sizeof(ArvCosSimp));
    novoElemento->info = novaInfo;
    novoElemento->esq = NULL;
    novoElemento->dir = NULL;
    novoElemento->costura = false;

    //Inserção em árvore vazia: quando há apenas um elemento, não é necessário fazer a costura
    if(arvoreVazia(*raiz)){
        (*raiz) = novoElemento;
        novoElemento->dir = NULL;
    }
    // Inserção em árvore não vazia
    else{

        // Criação de auxiliares para percorrer a árvore.
        ArvCosSimp* anterior = NULL;   // Guarda o nó q já foi verificado (pai)
        ArvCosSimp* atual = *raiz;     // Guarda o nó q esta sendo verificado.

        // Loop de busca para identificar o local de inserção do novo nó.
        while (atual){
            anterior = atual;

            // Caso a informação nó a ser inserido já estiver na árvore
            if(atual->info == novaInfo){
                cout << "\nElemento já existe na árvore\n";
                return;
            }
            // Se nova informação for menor, segue a esquerda
            else if (novaInfo < atual->info){
                atual = atual->esq;
            }
            else{

                if(atual->costura){
                    atual = NULL;        // Para o Loop quando acha uma costura a direita do nó atual.
                }else{
                    atual = atual->dir;  // Segue para a direita pois o novo elemento é maior do que o verificado.
                }
            }

        }

        // Caso novo nó seja adicionado a esquerda do nó encontrado anteriormente
        if(novaInfo < anterior->info){
            anterior->esq = novoElemento;          // Adiciona o novo elemento a esquerda.
            novoElemento->dir = anterior;          // Faz a costura com o seu sucessor em ordem.
            novoElemento->costura = true;       // Modifica o estado do nó para "Costurado"
        }

        else {   // Caso o novo nó seja adicionado a direita do nó encontrado anteriormente.

            // Se o nó anterior já estiver costurado com outro nó
            if(anterior->costura){
                anterior->costura = false;      // Muda status do nó anterior para "sem costura"
                novoElemento->costura = true;   // Muda status do novo nó  para "costurado"
                novoElemento->dir = anterior->dir; // Costura meu novo nó com o com o nó que o anterior estava costurado.
                anterior->dir = novoElemento;      // Adiciona novo nó a direita do nó anterior
            }

            else { // Caso o nó anterior não possuir costuras

                novoElemento->costura = false;  // Muda status do novo elemento para "não costurado
                novoElemento->dir = NULL;          // Não costura novo nó
                anterior->dir = novoElemento;      // Adiciona novo nó a direita do anterior
            }
        }
    }
}

// Função auxiliar que retorna o nó mais a direita da árvore
ArvCosSimp* noMaisADireita(ArvCosSimp* raiz){
    if(raiz->dir == NULL){
        return raiz;
    }else {
        return noMaisADireita(raiz->dir);
    }
}

// Função auxiliar que retorna o nó mais a esquerda
ArvCosSimp* noMaisAEsquerda(ArvCosSimp* raiz){
    //Auxiliar que percorre a árvore
    ArvCosSimp* aux = raiz;
    // Caso a árvore for vazia
     if(aux == NULL){
         return NULL;
     }
     // Árvore não vazia
     else{
         // Passa auxiliar para esquerda até que não tenha mais nós a esquerda
         while (aux->esq != NULL){
             aux = aux->esq;
         }
     }
     return aux;

}

// Função de exibição da árvore na forma de leitura "em ordem"
void imprimirEmOrdem(ArvCosSimp* raiz){

    ArvCosSimp* aux = noMaisAEsquerda(raiz);   // começa pelo nó mais a esquerda da árvore
    while (aux != NULL){
        cout << aux->info << "\n";             // Exibe a informação do nó

        if(aux->costura){                      // Prossegue pela costura para seu sucessor em ordem
            aux = aux->dir;
        }else{
            aux = noMaisAEsquerda(aux->dir);   // Caso não houver costura, verifica se há filhos a esquerda para manter a ordem.
        }
    }
    cout << endl;
}

// Funçaõ auxiliar que retorna se um elemento pertence a arvore.
bool pertence(ArvCosSimp* raiz, int infoChave){
    ArvCosSimp* aux = raiz;
    while (aux) {
        if ( aux->info == infoChave) {       // Retorna true quando acha o elemento
            return true;
        }

        if (infoChave < aux->info) {         // Busca a esquerda se a chave for menor
            aux = aux->esq;
        }
        else if (!aux->costura){
            // Busca a direita se a chave de busca foe maior
            aux = aux->dir;
        }else{
            return false;
        }
    }
}

// Função que busca um nó através da informação que contem nele e retorna o retorna
ArvCosSimp* buscarEmOrdem(ArvCosSimp** raiz, int infoChave){
    // Auxiliar para buscar o nó  a ser removido.
    ArvCosSimp *aux = *raiz;

    // Loop para encontrar o nó a ser removido
    while (aux->info != infoChave) {

        // Busca na sub arvore a direita pois a chave de busca é maior que a verificada
        if (aux->info < infoChave) {
            if (aux->dir) {
                aux = aux->dir;
            }
        }

        // Busca na sub arvore a esquerda pois a chave é menor do que a verificada
        else if (aux->info > infoChave) {
            if (aux->esq) {
                aux = aux->esq;
            }
        }
        // Para o loop quando encontra o nó a ser removido
        else {
            break;
        }
    }

    return aux;
}

// Função que retorna o elemento pai de um nó.
ArvCosSimp* buscarPai(ArvCosSimp** raiz, int infoChave){
    ArvCosSimp *aux = *raiz;           // Auxiliar para buscar o nó  a ser removido.
    ArvCosSimp *pai = NULL;            // Guarda o pai do nó a ser removido.

    // Loop para encontrar o nó a ser removido
    while (aux->info != infoChave) {

        // Busca na sub arvore a direita pois a chave de busca é maior que a verificada
        if (aux->info < infoChave) {
            if (aux->dir) {
                pai = aux;
                aux = aux->dir;
            }
        }

        // Busca na sub arvore a esquerda pois a chave é menor do que a verificada
        else if (aux->info > infoChave) {
            if (aux->esq) {
                pai = aux;
                aux = aux->esq;
            }
        }
        // Para o loop quando encontra o nó a ser removido
        else {
            break;
        }
    }

    return pai;
}

// Caso de exclusão para o nó é folhas
void exclusaoCaso1(ArvCosSimp* raiz, ArvCosSimp* pai, ArvCosSimp* noEscoolhido){
    // Caso o nó a ser removido for a raiz da árvore.
    if (pai == NULL) {
        raiz = NULL;
    }

        // Caso o nó esteja a esquerda do pai, não importa se há costura pois a costura sempre leva ao pai
    else if(pai->esq == noEscoolhido){
        pai->esq = noEscoolhido->esq;
    }

        // Se o nó estiver a direita do pai, precisa-se verificar se há costura para manter a ordem de travessia
    else{
        pai->dir = noEscoolhido->dir;

        // Se o nó excluido tiver costura, o pai deve ser receber essa costura
        if(noEscoolhido->costura){
            pai->costura = true;
        }
    }

    free(noEscoolhido);
}

// Caso de exclusão onde o nó possui apenas um filho.
void exclusaoCaso2(ArvCosSimp* raiz, ArvCosSimp* pai, ArvCosSimp* noEscolhido){

    ArvCosSimp* filho;

    // Se o nó escolhido tiver apenas fiilho a esquerda
    if(noEscolhido->esq){
        filho = noEscolhido->esq;
    }
        // Se o nó escolhido tiver apenas filho direito
    else{
        filho = noEscolhido->dir;
    }

    // Caso nó for raiz
    if(pai == NULL){
        raiz = filho;
    }

    // Se o no estiver a direita do pai.
    if(pai->dir == noEscolhido){
        pai->dir = filho;
    }
    // Se o no estiver a direita do pai.
    else{
        pai->esq = filho;
        filho->dir = pai;
    }

    free(noEscolhido);
}

// Caso de exclusão onde o nó possui ambos os filhos
void exclusaoCaso3(ArvCosSimp* raiz, ArvCosSimp* noEscolhido){
    ArvCosSimp* paiDoSucessor = noEscolhido;
    ArvCosSimp* sucessor = noEscolhido->dir;

    // Loop para encontrar o nó mais esquerda do sucessor
    while (sucessor->esq){
        paiDoSucessor = sucessor;
        sucessor = sucessor->esq;
    }
    // Troca de informação com o nó escolhido.
    noEscolhido->info = sucessor->info;

    // Como a informacão já foi trocada, deve-se excluir o nó mais a esquerda da sub arvore a direita do nó escolhido.
    if(sucessor->esq == NULL && (sucessor->dir == NULL || sucessor->costura)){
        exclusaoCaso1(raiz, paiDoSucessor, sucessor);
    }else{
        exclusaoCaso2(raiz, paiDoSucessor, sucessor);
    }
}


// Função para excluir elemento através de chave de busca.
void excluirElemento(ArvCosSimp** raiz, int infoChave) {
    // Só realiza a exclusão se o elemento pertencer a árvore.
    if (pertence(*raiz, infoChave)) {
        ArvCosSimp* pai = buscarPai(raiz, infoChave);
        ArvCosSimp* noEscolhido = buscarEmOrdem(raiz, infoChave);

        // Caso o nó a ser excluido for um nó folha
        if ((noEscolhido->esq == NULL && noEscolhido->costura) || (noEscolhido->esq == NULL && noEscolhido->dir == NULL)) {
            exclusaoCaso1(*raiz, pai, noEscolhido);
        }

        // Nó a ser excluido possuir apenas um filho a direita.
        else if (noEscolhido->esq == NULL && noEscolhido->dir != NULL && !noEscolhido->costura) {
            //tratamento para a exclusão do elemento.
            exclusaoCaso2(*raiz, pai, noEscolhido);
        }

        // No a ser excluido possui apenas um filho a esquerda
        else if ((noEscolhido->esq != NULL && (noEscolhido->costura || noEscolhido->dir == NULL)) || (noEscolhido->esq != NULL && noEscolhido->dir == NULL)) {
            // Tratamento para exclusão do elemento
            exclusaoCaso2(*raiz, pai, noEscolhido);

        }

        // No a ser excluido possui os dois filhos
        else {
            exclusaoCaso3(*raiz, noEscolhido);
        }
    }

    // Caso o elemento n pertença a árvore.
    else {
        cout << "Elemento não pertence a arvore\n";
    }
}


// Função para destruir (liberar a memória) da árvore.
void liberarArvore(ArvCosSimp* raiz){
    if(!arvoreVazia(raiz)){
        liberarArvore(raiz->esq);
        if(raiz->costura){
            liberarArvore(raiz->dir);
            free(raiz);
        }
    }
    raiz = NULL;
}

void menu(){

    cout<<"======================================\n";
    cout<<"<> Árvore binária com costura simples <>\n";
    cout<<"======================================\n";
    cout<<"1. Inserir elmento\n";
    cout<<"2. Excluir elemento\n";
    cout<<"3. Imprimir em ordem\n";
    cout<<"4. Destruir árvore\n";
    cout<<"5. Sair\n";

}

void selecao(){
    int val, ch;
    char sim='s';
    ArvCosSimp *arvore = criarArvoreVazia();
    while(sim=='s'){
        cout<<"\nO que deseja fazer?:";cin>>ch;
        switch(ch){
            case 1:
                cout<<"Valor a adicionar:";cin>>val;
                inserirElemento(&arvore, val);
                break;

            case 2:
                cout<<"Valor a excluir:";cin>>val;
                excluirElemento(&arvore,val);
                break;

            case 3:
                cout<<"Árvore em ordem:\n";
                imprimirEmOrdem(arvore);
                break;

            case 4:
                cout << "Árvore destruída.\n";
                liberarArvore(arvore);
                break;

            case 5:
                exit(0);

            default: cout<<"Invalid choice";

        }
        cout<<"Continuar?\ns/n:";cin>>sim;
    }

    liberarArvore(arvore);
}

// Função de teste das funções, caso não queira utilizar menu.
void teste(){
    ArvCosSimp* arvore = criarArvoreVazia();

    inserirElemento(&arvore, 5);
    inserirElemento(&arvore, 10);
    inserirElemento(&arvore, 12);
    inserirElemento(&arvore, 9);
    inserirElemento(&arvore, 3);
    inserirElemento(&arvore, 4);
    inserirElemento(&arvore, 0);
    inserirElemento(&arvore, 1);
    inserirElemento(&arvore, 6);
    inserirElemento(&arvore, 2);
    inserirElemento(&arvore, 11);

    /*inserirElemento(&arvore, 6);
    inserirElemento(&arvore, 3);
    inserirElemento(&arvore, 8);
    inserirElemento(&arvore, 1);
    inserirElemento(&arvore, 5);
    inserirElemento(&arvore, 7);
    inserirElemento(&arvore, 11);
    inserirElemento(&arvore, 9);
    inserirElemento(&arvore, 13);

    inserirElemento(&arvore, 20);
    inserirElemento(&arvore, 10);
    inserirElemento(&arvore, 30);
    inserirElemento(&arvore, 5);
    inserirElemento(&arvore, 16);
    inserirElemento(&arvore, 14);
    inserirElemento(&arvore, 17);
    inserirElemento(&arvore, 13);*/

    cout << "imprimindo em ordem.";
    imprimirEmOrdem(arvore);

    cout << "\nexcluindo 12\n" << endl;

    excluirElemento(&arvore, 12);

    cout << "imprimindo em ordem.";

    imprimirEmOrdem(arvore);


    liberarArvore(arvore);

}