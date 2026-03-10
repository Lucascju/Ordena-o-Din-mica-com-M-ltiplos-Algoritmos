#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long comparacoes = 0;
long long trocas = 0;


void trocar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
    trocas++;
}

void exibir_vetor(int *v, int n) {
    printf("Estrutura atual:");
    for (int i = 0; i < n; i++) {
        printf(" %d", v[i]);
    }
    printf("\n");
}

void resetar_contadores() {
    comparacoes = 0;
    trocas = 0;
}


void bubble_sort(int *v, int n) {
    resetar_contadores();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparacoes++;
            if (v[j] > v[j + 1]) {
                trocar(&v[j], &v[j + 1]);
            }
        }
    }
}

void selection_sort(int *v, int n) {
    resetar_contadores();
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            comparacoes++;
            if (v[j] < v[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            trocar(&v[i], &v[min_idx]);
        }
    }
}

void insertion_sort(int *v, int n) {
    resetar_contadores();
    for (int i = 1; i < n; i++) {
        int chave = v[i];
        int j = i - 1;
        while (j >= 0) {
            comparacoes++;
            if (v[j] > chave) {
                v[j + 1] = v[j];
                trocas++;
                j--;
            } else {
                break;
            }
        }
        v[j + 1] = chave;
    }
}


int particionar(int *v, int baixo, int alto) {
    int pivot = v[alto];
    int i = baixo - 1;

    for (int j = baixo; j < alto; j++) {
        comparacoes++;
        if (v[j] <= pivot) {
            i++;
            trocar(&v[i], &v[j]);
        }
    }
    trocar(&v[i + 1], &v[alto]);
    return i + 1;
}

void quick_sort_rec(int *v, int baixo, int alto) {
    if (baixo < alto) {
        int pi = particionar(v, baixo, alto);
        quick_sort_rec(v, baixo, pi - 1);
        quick_sort_rec(v, pi + 1, alto);
    }
}

void quick_sort(int *v, int n) {
    resetar_contadores();
    quick_sort_rec(v, 0, n - 1);
}


void merge(int *v, int esq, int meio, int dir) {
    int n1 = meio - esq + 1;
    int n2 = dir - meio;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++) L[i] = v[esq + i];
    for (int j = 0; j < n2; j++) R[j] = v[meio + 1 + j];

    int i = 0, j = 0, k = esq;

    while (i < n1 && j < n2) {
        comparacoes++;
        if (L[i] <= R[j]) {
            v[k++] = L[i++];
        } else {
            v[k++] = R[j++];
            trocas++;
        }
    }

    while (i < n1) v[k++] = L[i++];
    while (j < n2) v[k++] = R[j++];

    free(L);
    free(R);
}

void merge_sort_rec(int *v, int esq, int dir) {
    if (esq < dir) {
        int meio = esq + (dir - esq) / 2;
        merge_sort_rec(v, esq, meio);
        merge_sort_rec(v, meio + 1, dir);
        merge(v, esq, meio, dir);
    }
}

void merge_sort(int *v, int n) {
    resetar_contadores();
    merge_sort_rec(v, 0, n - 1);
}

const char *nome_algoritmo(int opcao) {
    switch (opcao) {
        case 1: return "Bubble Sort";
        case 2: return "Selection Sort";
        case 3: return "Insertion Sort";
        case 4: return "Quick Sort";
        case 5: return "Merge Sort";
        default: return "Desconhecido";
    }
}

void executar_algoritmo(int opcao, int *v, int n) {
    switch (opcao) {
        case 1: bubble_sort(v, n); break;
        case 2: selection_sort(v, n); break;
        case 3: insertion_sort(v, n); break;
        case 4: quick_sort(v, n); break;
        case 5: merge_sort(v, n); break;
    }
}

int main() {
    int opcao;

    printf("Escolha o algoritmo:\n");
    printf("1 - Bubble Sort\n");
    printf("2 - Selection Sort\n");
    printf("3 - Insertion Sort\n");
    printf("4 - Quick Sort\n");
    printf("5 - Merge Sort\n");
    printf("\nOpcao: ");
    scanf("%d", &opcao);

    if (opcao < 1 || opcao > 5) {
        printf("Opcao invalida!\n");
        return 1;
    }

    printf("\nAlgoritmo selecionado: %s\n\n", nome_algoritmo(opcao));

    int qtd;
    printf("Quantos valores deseja inserir? ");
    scanf("%d", &qtd);

    if (qtd <= 0) {
        printf("Quantidade invalida!\n");
        return 1;
    }

    int *vetor = (int *)malloc(qtd * sizeof(int));
    if (!vetor) {
        printf("Erro ao alocar memoria!\n");
        return 1;
    }

    int n = 0;

    for (int i = 0; i < qtd; i++) {
        int valor;
        printf("\nDigite o valor: ");
        scanf("%d", &valor);

        vetor[n++] = valor;

        executar_algoritmo(opcao, vetor, n);
        exibir_vetor(vetor, n);
        printf("Comparacoes: %lld | Trocas: %lld\n", comparacoes, trocas);
    }

    printf("\n=== Resultado Final ===\n");
    printf("Algoritmo: %s\n", nome_algoritmo(opcao));
    exibir_vetor(vetor, n);
    printf("Total de comparacoes: %lld\n", comparacoes);
    printf("Total de trocas: %lld\n", trocas);

    free(vetor);
    return 0;
}
