#ifndef ARVORE_COSTURADA_ARVORE_COSTURADA_SIMPLES_H
#define ARVORE_COSTURADA_ARVORE_COSTURADA_SIMPLES_H

struct ArvCosSimp;                                          // Tipo de dado utilizado na árvore.

ArvCosSimp* criarArvoreVazia();                             // Função que inicializa a árvore.
bool arvoreVazia(ArvCosSimp*);                              // Função que retorna se a árvore está vazia.
void inserirElemento(ArvCosSimp**, int);                    // Inserção de elementos na árvore.
ArvCosSimp* noMaisADireita(ArvCosSimp*);                    // Função auxiliar que retorna o nó mais a direita da árvore.
ArvCosSimp* noMaisAEsquerda(ArvCosSimp*);                   // Função auxiliar que retorna o nó mais a esquerda.
void imprimirEmOrdem(ArvCosSimp*);                          // Função de exibição da árvore na forma de leitura "em ordem".
bool pertence(ArvCosSimp*, int);                            // Funçaõ auxiliar que retorna se um elemento pertence a arvore.
ArvCosSimp* buscarEmOrdem(ArvCosSimp**, int);               // Função que busca um nó através da informação que contem nele e retorna o retorna.
ArvCosSimp* buscarPai(ArvCosSimp**, int);                   // Função que retorna o elemento pai de um nó.
void exclusaoCaso1(ArvCosSimp*, ArvCosSimp*, ArvCosSimp*);  // Caso de exclusão onde o nó é folhas.
void exclusaoCaso2(ArvCosSimp*, ArvCosSimp*, ArvCosSimp*);  // Caso de exclusão onde o nó possui apenas um filho.
void exclusaoCaso3(ArvCosSimp*, ArvCosSimp*);               // Caso de exclusão onde o nó possui ambos os filhos.
void excluirElemento(ArvCosSimp**, int);                    // Função para excluir elemento através de chave de busca.
void liberarArvore(ArvCosSimp*);                            // Função para destruir (liberar a memória) da árvore.
void menu();                                               // Função de exibição de Menu
void selecao();                                            // Função de seleção de Menu;
void teste();                                              // Função para realização de testes.


#endif //ARVORE_COSTURADA_ARVORE_COSTURADA_SIMPLES_H