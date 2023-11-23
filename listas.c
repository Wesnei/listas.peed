#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura do nó
typedef struct No {
    int dado;
    struct No* anterior;
    struct No* proximo;
} No;

// Função para criar um novo nó
No* criarNo(int dado) {
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->dado = dado;
    novoNo->anterior = NULL;
    novoNo->proximo = NULL;
    return novoNo;
}

// Função para inserir no início da lista duplamente encadeada
void inserirNoInicio(No** cabeca, int dado) {
    No* novoNo = criarNo(dado);
    if (*cabeca == NULL) {
        *cabeca = novoNo;
    } else {
        novoNo->proximo = *cabeca;
        (*cabeca)->anterior = novoNo;
        *cabeca = novoNo;
    }
}

// Função para inserir no fim da lista duplamente encadeada
void inserirNoFim(No** cabeca, int dado) {
    No* novoNo = criarNo(dado);
    if (*cabeca == NULL) {
        *cabeca = novoNo;
    } else {
        No* temp = *cabeca;
        while (temp->proximo != NULL) {
            temp = temp->proximo;
        }
        temp->proximo = novoNo;
        novoNo->anterior = temp;
    }
}

// Função para inserir em uma posição específica na lista duplamente encadeada
void inserirNaPosicao(No** cabeca, int dado, int posicao) {
    No* novoNo = criarNo(dado);
    if (posicao == 1) {
        novoNo->proximo = *cabeca;
        (*cabeca)->anterior = novoNo;
        *cabeca = novoNo;
        return;
    }
    No* temp = *cabeca;
    for (int i = 1; i < posicao - 1 && temp != NULL; ++i) {
        temp = temp->proximo;
    }
    if (temp == NULL) {
        printf("Posição inválida.\n");
    } else {
        novoNo->proximo = temp->proximo;
        novoNo->anterior = temp;
        if (temp->proximo != NULL) {
            temp->proximo->anterior = novoNo;
        }
        temp->proximo = novoNo;
    }
}

// Função para exibir todos os nós da lista duplamente encadeada
void exibirLista(No* cabeca) {
    No* temp = cabeca;
    while (temp != NULL) {
        printf("%d ", temp->dado);
        temp = temp->proximo;
    }
    printf("\n");
}

// Função para excluir do início da lista duplamente encadeada
void excluirDoInicio(No** cabeca) {
    if (*cabeca == NULL) {
        printf("Lista vazia. Não é possível excluir.\n");
    } else {
        No* temp = *cabeca;
        *cabeca = temp->proximo;
        if (*cabeca != NULL) {
            (*cabeca)->anterior = NULL;
        }
        free(temp);
    }
}

// Função para excluir do fim da lista duplamente encadeada
void excluirDoFim(No** cabeca) {
    if (*cabeca == NULL) {
        printf("Lista vazia. Não é possível excluir.\n");
    } else {
        No* temp = *cabeca;
        while (temp->proximo != NULL) {
            temp = temp->proximo;
        }
        if (temp->anterior != NULL) {
            temp->anterior->proximo = NULL;
        } else {
            *cabeca = NULL;
        }
        free(temp);
    }
}

// Função para excluir de uma posição específica na lista duplamente encadeada
void excluirDaPosicao(No** cabeca, int posicao) {
    if (*cabeca == NULL) {
        printf("Lista vazia. Não é possível excluir.\n");
    } else {
        No* temp = *cabeca;
        for (int i = 1; i < posicao && temp != NULL; ++i) {
            temp = temp->proximo;
        }
        if (temp == NULL) {
            printf("Posição inválida.\n");
        } else {
            if (temp->anterior != NULL) {
                temp->anterior->proximo = temp->proximo;
            } else {
                *cabeca = temp->proximo;
            }
            if (temp->proximo != NULL) {
                temp->proximo->anterior = temp->anterior;
            }
            free(temp);
        }
    }
}

// Função para pesquisar um nó na lista duplamente encadeada
No* buscarNo(No* cabeca, int dado) {
    No* temp = cabeca;
    while (temp != NULL && temp->dado != dado) {
        temp = temp->proximo;
    }
    return temp;
}

// Função principal
int main() {
    No* cabeca = NULL;

    inserirNoInicio(&cabeca, 1);
    inserirNoFim(&cabeca, 2);
    inserirNoFim(&cabeca, 3);
    inserirNaPosicao(&cabeca, 4, 2);

    printf("Lista duplamente encadeada: ");
    exibirLista(cabeca);

    No* resultadoBusca = buscarNo(cabeca, 2);
    if (resultadoBusca != NULL) {
        printf("Nó encontrado: %d\n", resultadoBusca->dado);
    } else {
        printf("Nó não encontrado.\n");
    }

    excluirDoInicio(&cabeca);
    excluirDoFim(&cabeca);
    excluirDaPosicao(&cabeca, 2);

    printf("Lista duplamente encadeada após exclusões: ");
    exibirLista(cabeca);

    return 0;
}
