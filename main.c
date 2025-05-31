#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No {
    int dado;
    struct No *prox;
} No;


// 1. Inserção no Início
void inserir_inicio(No **lista, int val) {
    No *novo = malloc(sizeof(No));
    novo->dado = val;
    novo->prox = *lista;
    *lista = novo;
}

// 1. Inserção no Fim
void inserir_fim(No **lista, int val) {
    No *novo = malloc(sizeof(No));
    novo->dado = val;
    novo->prox = NULL;
    if (*lista == NULL) {
        *lista = novo;
    } else {
        No *p = *lista;
        while (p->prox) p = p->prox;
        p->prox = novo;
    }
}


void imprimir_lista(No *lista) {
    No *p = lista;
    while (p) {
        printf("%d ", p->dado);
        p = p->prox;
    }
    printf("\n");
}


// 2. Contar nós
int contar_nos(No *lista) {
    int cont = 0;
    No *p = lista;
    while (p) {
        cont++;
        p = p->prox;
    }
    return cont;
}


// 3. Buscar elemento
int buscar_elemento(No *lista, int val) {
    No *p = lista;
    while (p) {
        if (p->dado == val) return 1;
        p = p->prox;
    }
    return 0;
}


// 4. Inserir em posição 
void inserir_posicao(No **lista, int val, int pos) {
    if (pos == 0) {
        inserir_inicio(lista, val);
        return;
    }
    No *p = *lista;
    int i = 0;
    while (p && i < pos-1) {
        p = p->prox;
        i++;
    }
    if (!p) return; 
    No *novo = malloc(sizeof(No));
    novo->dado = val;
    novo->prox = p->prox;
    p->prox = novo;
}


// 5. Remover primeira ocorrência por valor
void remover_valor(No **lista, int val) {
    No *p = *lista;
    No *ant = NULL;
    while (p) {
        if (p->dado == val) {
            if (!ant) *lista = p->prox;
            else ant->prox = p->prox;
            free(p);
            return;
        }
        ant = p;
        p = p->prox;
    }
}


// 6. Inverter lista iterativamente
void inverter_lista(No **lista) {
    No *prev = NULL;
    No *curr = *lista;
    No *prox = NULL;
    while (curr) {
        prox = curr->prox;
        curr->prox = prev;
        prev = curr;
        curr = prox;
    }
    *lista = prev;
}


// 7. Encontrar nó do meio 
No* encontrar_meio(No *lista) {
    if (!lista) return NULL;
    No *slow = lista;
    No *fast = lista;
    while (fast && fast->prox) {
        slow = slow->prox;
        fast = fast->prox->prox;
    }
    return slow;
}


typedef struct {
    int dados[100];
    int topo;
} Pilha;

void pilha_inicializar(Pilha *p) {
    p->topo = -1;
}

int pilha_esta_vazia(Pilha *p) {
    return p->topo == -1;
}

int pilha_push(Pilha *p, int val) {
    if (p->topo == 99) return 0;
    p->dados[++p->topo] = val;
    return 1;
}

int pilha_pop(Pilha *p) {
    if (pilha_esta_vazia(p)) return -1;
    return p->dados[p->topo--];
}


// 8. Imprimir reverso com pilha
void imprimir_reversa_com_pilha(No *lista) {
    Pilha p;
    pilha_inicializar(&p);
    No *curr = lista;
    while (curr) {
        pilha_push(&p, curr->dado);
        curr = curr->prox;
    }
    while (!pilha_esta_vazia(&p)) {
        printf("%d ", pilha_pop(&p));
    }
    printf("\n");
}


// 9. Pilha com array fixo
typedef struct {
    int dados[100];
    int topo;
} PilhaArray;

void pilha_array_inicializar(PilhaArray *p) {
    p->topo = -1;
}

int pilha_array_push(PilhaArray *p, int val) {
    if (p->topo == 99) return 0;
    p->dados[++p->topo] = val;
    return 1;
}

int pilha_array_pop(PilhaArray *p) {
    if (p->topo == -1) return -1;
    return p->dados[p->topo--];
}

int pilha_array_topo(PilhaArray *p) {
    if (p->topo == -1) return -1;
    return p->dados[p->topo];
}

int pilha_array_esta_vazia(PilhaArray *p) {
    return p->topo == -1;
}


// 10. Pilha com lista encadeada
typedef struct NoPilha {
    int dado;
    struct NoPilha *prox;
} NoPilha;

typedef struct {
    NoPilha *topo;
} PilhaLista;

void pilha_lista_inicializar(PilhaLista *p) {
    p->topo = NULL;
}

int pilha_lista_push(PilhaLista *p, int val) {
    NoPilha *novo = malloc(sizeof(NoPilha));
    if (!novo) return 0;
    novo->dado = val;
    novo->prox = p->topo;
    p->topo = novo;
    return 1;
}

int pilha_lista_pop(PilhaLista *p) {
    if (!p->topo) return -1;
    NoPilha *remover = p->topo;
    int val = remover->dado;
    p->topo = remover->prox;
    free(remover);
    return val;
}

int pilha_lista_topo(PilhaLista *p) {
    if (!p->topo) return -1;
    return p->topo->dado;
}

int pilha_lista_esta_vazia(PilhaLista *p) {
    return p->topo == NULL;
}


// 11. Verificação de parênteses balanceados

int verificar_balanceamento(char *str) {
    PilhaArray p;
    pilha_array_inicializar(&p);
    for (int i = 0; str[i]; i++) {
        char c = str[i];
        if (c == '(' || c == '[' || c == '{') {
            pilha_array_push(&p, c);
        } else if (c == ')' || c == ']' || c == '}') {
            if (pilha_array_esta_vazia(&p)) return 0;
            char topo = pilha_array_pop(&p);
            if ((c == ')' && topo != '(') ||
                (c == ']' && topo != '[') ||
                (c == '}' && topo != '{')) {
                return 0;
            }
        }
    }
    return pilha_array_esta_vazia(&p);
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct No {
    int dado;
    struct No *prox;
} No;



void inserir_fim(No **lista, int val) {
    No *novo = malloc(sizeof(No));
    novo->dado = val;
    novo->prox = NULL;
    if (*lista == NULL) {
        *lista = novo;
    } else {
        No *p = *lista;
        while (p->prox) p = p->prox;
        p->prox = novo;
    }
}
void imprimir_lista(No *lista) {
    No *p = lista;
    while (p) {
        printf("%d ", p->dado);
        p = p->prox;
    }
    printf("\n");
}


// 12. Inversão de string com pilha
typedef struct {
    char dados[100];
    int topo;
} PilhaChar;

void pilha_char_inicializar(PilhaChar *p) {
    p->topo = -1;
}
int pilha_char_esta_vazia(PilhaChar *p) {
    return p->topo == -1;
}
int pilha_char_push(PilhaChar *p, char val) {
    if (p->topo == 99) return 0;
    p->dados[++p->topo] = val;
    return 1;
}
char pilha_char_pop(PilhaChar *p) {
    if (pilha_char_esta_vazia(p)) return '\0';
    return p->dados[p->topo--];
}

void inverter_string(char *str) {
    PilhaChar p;
    pilha_char_inicializar(&p);
    for (int i = 0; str[i]; i++) {
        pilha_char_push(&p, str[i]);
    }
    int i = 0;
    while (!pilha_char_esta_vazia(&p)) {
        str[i++] = pilha_char_pop(&p);
    }
    str[i] = '\0';
}


// 13. Verificação de palíndromo usando pilha
int verificar_palindromo(char *str) {
    int len = strlen(str);
    PilhaChar p;
    pilha_char_inicializar(&p);

    for (int i = 0; i < len / 2; i++) {
        pilha_char_push(&p, str[i]);
    }

    int start = (len % 2 == 0) ? len/2 : len/2 +1;

    for (int i = start; i < len; i++) {
        if (pilha_char_pop(&p) != str[i]) return 0;
    }
    return 1;
}


// 14. Ordenação de pilha usando outra pilha
typedef struct {
    int dados[100];
    int topo;
} PilhaInt;

void pilha_int_inicializar(PilhaInt *p) {
    p->topo = -1;
}
int pilha_int_esta_vazia(PilhaInt *p) {
    return p->topo == -1;
}
int pilha_int_push(PilhaInt *p, int val) {
    if (p->topo == 99) return 0;
    p->dados[++p->topo] = val;
    return 1;
}
int pilha_int_pop(PilhaInt *p) {
    if (pilha_int_esta_vazia(p)) return -1;
    return p->dados[p->topo--];
}
int pilha_int_topo(PilhaInt *p) {
    if (pilha_int_esta_vazia(p)) return -1;
    return p->dados[p->topo];
}


void ordenar_pilha(PilhaInt *p) {
    PilhaInt aux;
    pilha_int_inicializar(&aux);

    while (!pilha_int_esta_vazia(p)) {
        int tmp = pilha_int_pop(p);
        while (!pilha_int_esta_vazia(&aux) && pilha_int_topo(&aux) > tmp) {
            pilha_int_push(p, pilha_int_pop(&aux));
        }
        pilha_int_push(&aux, tmp);
    }

   
    while (!pilha_int_esta_vazia(&aux)) {
        pilha_int_push(p, pilha_int_pop(&aux));
    }
}


// 15. Fila com array circular
typedef struct {
    int dados[100];
    int inicio, fim, tamanho;
} FilaCirc;

void fila_circ_inicializar(FilaCirc *f) {
    f->inicio = 0;
    f->fim = -1;
    f->tamanho = 0;
}

int fila_circ_esta_vazia(FilaCirc *f) {
    return f->tamanho == 0;
}
int fila_circ_esta_cheia(FilaCirc *f) {
    return f->tamanho == 100;
}

int fila_circ_enfileirar(FilaCirc *f, int val) {
    if (fila_circ_esta_cheia(f)) return 0;
    f->fim = (f->fim + 1) % 100;
    f->dados[f->fim] = val;
    f->tamanho++;
    return 1;
}

int fila_circ_desenfileirar(FilaCirc *f) {
    if (fila_circ_esta_vazia(f)) return -1;
    int val = f->dados[f->inicio];
    f->inicio = (f->inicio + 1) % 100;
    f->tamanho--;
    return val;
}

int fila_circ_frente(FilaCirc *f) {
    if (fila_circ_esta_vazia(f)) return -1;
    return f->dados[f->inicio];
}


// 16. Fila com lista encadeada
typedef struct NoFila {
    int dado;
    struct NoFila *prox;
} NoFila;

typedef struct {
    NoFila *inicio, *fim;
} FilaLista;

void fila_lista_inicializar(FilaLista *f) {
    f->inicio = f->fim = NULL;
}

int fila_lista_esta_vazia(FilaLista *f) {
    return f->inicio == NULL;
}

int fila_lista_enfileirar(FilaLista *f, int val) {
    NoFila *novo = malloc(sizeof(NoFila));
    if (!novo) return 0;
    novo->dado = val;
    novo->prox = NULL;
    if (fila_lista_esta_vazia(f)) {
        f->inicio = f->fim = novo;
    } else {
        f->fim->prox = novo;
        f->fim = novo;
    }
    return 1;
}

int fila_lista_desenfileirar(FilaLista *f) {
    if (fila_lista_esta_vazia(f)) return -1;
    NoFila *rem = f->inicio;
    int val = rem->dado;
    f->inicio = rem->prox;
    if (!f->inicio) f->fim = NULL;
    free(rem);
    return val;
}

int fila_lista_frente(FilaLista *f) {
    if (fila_lista_esta_vazia(f)) return -1;
    return f->inicio->dado;
}


// 17. Geração de N números binários usando fila

void gerar_binarios(int N) {
    if (N <= 0) return;

    FilaLista fila;
    fila_lista_inicializar(&fila);
    fila_lista_enfileirar(&fila, 1);

    for (int i = 0; i < N; i++) {
        NoFila *front = fila.inicio;
        int num = front->dado;

        
        break;
    }
}



typedef struct NoString {
    char str[100];
    struct NoString *prox;
} NoString;

typedef struct {
    NoString *inicio, *fim;
} FilaStr;

void fila_str_inicializar(FilaStr *f) {
    f->inicio = f->fim = NULL;
}

int fila_str_esta_vazia(FilaStr *f) {
    return f->inicio == NULL;
}

int fila_str_enfileirar(FilaStr *f, const char *s) {
    NoString *novo = malloc(sizeof(NoString));
    if (!novo) return 0;
    strcpy(novo->str, s);
    novo->prox = NULL;
    if (fila_str_esta_vazia(f)) {
        f->inicio = f->fim = novo;
    } else {
        f->fim->prox = novo;
        f->fim = novo;
    }
    return 1;
}

char* fila_str_desenfileirar(FilaStr *f) {
    if (fila_str_esta_vazia(f)) return NULL;
    NoString *rem = f->inicio;
    char *res = malloc(strlen(rem->str) + 1);
    strcpy(res, rem->str);
    f->inicio = rem->prox;
    if (!f->inicio) f->fim = NULL;
    free(rem);
    return res;
}

void gerar_binarios(int N) {
    FilaStr fila;
    fila_str_inicializar(&fila);
    fila_str_enfileirar(&fila, "1");

    for (int i = 0; i < N; i++) {
        char *s = fila_str_desenfileirar(&fila);
        printf("%s\n", s);

        char s0[110], s1[110];
        sprintf(s0, "%s0", s);
        sprintf(s1, "%s1", s);

        fila_str_enfileirar(&fila, s0);
        fila_str_enfileirar(&fila, s1);

        free(s);
    }
}


// 18. Inverter os primeiros K elementos da fila usando pilha

void inverter_primeiros_k(FilaLista *f, int K) {
    if (fila_lista_esta_vazia(f) || K <= 0) return;
    PilhaInt p;
    pilha_int_inicializar(&p);

    int count = 0;
    
    for (int i = 0; i < K; i++) {
        if (fila_lista_esta_vazia(f)) break;
        int val = fila_lista_desenfileirar(f);
        pilha_int_push(&p, val);
        count++;
    }
    
    while (!pilha_int_esta_vazia(&p)) {
        fila_lista_enfileirar(f, pilha_int_pop(&p));
    }
    
    int tamanho_restante = 0;
    NoFila *curr = f->inicio;
    while (curr) {
        tamanho_restante++;
        curr = curr->prox;
    }
    for (int i = 0; i < tamanho_restante - count; i++) {
        int val = fila_lista_desenfileirar(f);
        fila_lista_enfileirar(f, val);
    }
}


// 19. Detectar ciclo em lista (Floyd)
int detectar_ciclo(No *lista) {
    No *slow = lista;
    No *fast = lista;
    while (fast && fast->prox) {
        slow = slow->prox;
        fast = fast->prox->prox;
        if (slow == fast) return 1;
    }
    return 0;
}


// 20. União de listas ordenadas
No* unir_listas_ordenadas(No *l1, No *l2) {
    No dummy;
    No *tail = &dummy;
    dummy.prox = NULL;

    while (l1 && l2) {
        if (l1->dado <= l2->dado) {
            tail->prox = l1;
            l1 = l1->prox;
        } else {
            tail->prox = l2;
            l2 = l2->prox;
        }
        tail = tail->prox;
    }
    tail->prox = (l1) ? l1 : l2;
    return dummy.prox;
}



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No {
    int dado;
    struct No *prox;
} No;


void inserir_fim(No **lista, int val) {
    No *novo = malloc(sizeof(No));
    novo->dado = val;
    novo->prox = NULL;
    if (*lista == NULL) {
        *lista = novo;
    } else {
        No *p = *lista;
        while (p->prox) p = p->prox;
        p->prox = novo;
    }
}

void imprimir_lista(No *lista) {
    No *p = lista;
    while (p) {
        printf("%d ", p->dado);
        p = p->prox;
    }
    printf("\n");
}


// 21. Remover todas as ocorrências
void remover_todas_ocorrencias(No **lista, int val) {
    while (*lista && (*lista)->dado == val) {
        No *rem = *lista;
        *lista = (*lista)->prox;
        free(rem);
    }
    No *p = *lista;
    while (p && p->prox) {
        if (p->prox->dado == val) {
            No *rem = p->prox;
            p->prox = rem->prox;
            free(rem);
        } else {
            p = p->prox;
        }
    }
}


// 22. Encontrar interseção de listas (se existir)
No* encontrar_intersecao(No *l1, No *l2) {
    
    int len1 = 0, len2 = 0;
    No *p1 = l1, *p2 = l2;
    while (p1) { len1++; p1 = p1->prox; }
    while (p2) { len2++; p2 = p2->prox; }

    p1 = l1;
    p2 = l2;

    if (len1 > len2) {
        for (int i = 0; i < len1 - len2; i++) p1 = p1->prox;
    } else {
        for (int i = 0; i < len2 - len1; i++) p2 = p2->prox;
    }

    while (p1 && p2) {
        if (p1 == p2) return p1;
        p1 = p1->prox;
        p2 = p2->prox;
    }
    return NULL;
}


// 23. Rotacionar lista em K posições
void rotacionar_lista(No **lista, int K) {
    if (!*lista || K == 0) return;


    int len = 0;
    No *p = *lista;
    while (p) {
        len++;
        p = p->prox;
    }
    K %= len;
    if (K == 0) return;

   
    int passos = len - K - 1;
    p = *lista;
    for (int i = 0; i < passos; i++) {
        p = p->prox;
    }

    No *novo_inicio = p->prox;
    p->prox = NULL;

   
    No *fim = novo_inicio;
    while (fim->prox) fim = fim->prox;
    fim->prox = *lista;

    *lista = novo_inicio;
}


// 24. Pilha com mínimo em O(1)
typedef struct {
    int dados[100];
    int minimos[100];
    int topo;
} PilhaMin;

void pilha_min_inicializar(PilhaMin *p) {
    p->topo = -1;
}
int pilha_min_esta_vazia(PilhaMin *p) {
    return p->topo == -1;
}
int pilha_min_push(PilhaMin *p, int val) {
    if (p->topo == 99) return 0;
    p->topo++;
    p->dados[p->topo] = val;
    if (p->topo == 0) {
        p->minimos[p->topo] = val;
    } else {
        p->minimos[p->topo] = (val < p->minimos[p->topo - 1]) ? val : p->minimos[p->topo - 1];
    }
    return 1;
}
int pilha_min_pop(PilhaMin *p) {
    if (pilha_min_esta_vazia(p)) return -1;
    return p->dados[p->topo--];
}
int pilha_min_topo(PilhaMin *p) {
    if (pilha_min_esta_vazia(p)) return -1;
    return p->dados[p->topo];
}
int pilha_min_minimo(PilhaMin *p) {
    if (pilha_min_esta_vazia(p)) return -1;
    return p->minimos[p->topo];
}


// 25. Duas pilhas em um único array
typedef struct {
    int dados[100];
    int topo1;
    int topo2;
} DuasPilhas;

void duas_pilhas_inicializar(DuasPilhas *dp) {
    dp->topo1 = -1;
    dp->topo2 = 100;
}

int duas_pilhas_push1(DuasPilhas *dp, int val) {
    if (dp->topo1 + 1 == dp->topo2) return 0; 
    dp->dados[++dp->topo1] = val;
    return 1;
}

int duas_pilhas_push2(DuasPilhas *dp, int val) {
    if (dp->topo2 - 1 == dp->topo1) return 0; 
    dp->dados[--dp->topo2] = val;
    return 1;
}

int duas_pilhas_pop1(DuasPilhas *dp) {
    if (dp->topo1 == -1) return -1; 
    return dp->dados[dp->topo1--];
}

int duas_pilhas_pop2(DuasPilhas *dp) {
    if (dp->topo2 == 100) return -1; 
    return dp->dados[dp->topo2++];
}


// 26. Avaliação de expressão pós-fixa
int avaliar_posfixa(const char *expr) {
    PilhaInt p;
    pilha_int_inicializar(&p);

    int i = 0;
    while (expr[i]) {
        if (isspace(expr[i])) {
            i++;
            continue;
        }
        if (isdigit(expr[i])) {
            int num = 0;
            while (isdigit(expr[i])) {
                num = num * 10 + (expr[i] - '0');
                i++;
            }
            pilha_int_push(&p, num);
        } else {
            int b = pilha_int_pop(&p);
            int a = pilha_int_pop(&p);
            int res = 0;
            switch (expr[i]) {
                case '+': res = a + b; break;
                case '-': res = a - b; break;
                case '*': res = a * b; break;
                case '/': res = a / b; break;
                default: return 0;  
            }
            pilha_int_push(&p, res);
            i++;
        }
    }
    return pilha_int_pop(&p);
}


// 27. Fila usando duas pilhas
typedef struct {
    PilhaInt pilha_enq;
    PilhaInt pilha_deq;
} FilaDupla;

void fila_dupla_inicializar(FilaDupla *f) {
    pilha_int_inicializar(&f->pilha_enq);
    pilha_int_inicializar(&f->pilha_deq);
}

int fila_dupla_esta_vazia(FilaDupla *f) {
    return pilha_int_esta_vazia(&f->pilha_enq) && pilha_int_esta_vazia(&f->pilha_deq);
}

void fila_dupla_enfileirar(FilaDupla *f, int val) {
    pilha_int_push(&f->pilha_enq, val);
}

int fila_dupla_desenfileirar(FilaDupla *f) {
    if (pilha_int_esta_vazia(&f->pilha_deq)) {
        while (!pilha_int_esta_vazia(&f->pilha_enq)) {
            pilha_int_push(&f->pilha_deq, pilha_int_pop(&f->pilha_enq));
        }
    }
    return pilha_int_pop(&f->pilha_deq);
}


// 28. Inverter em grupos de K nós
No* inverter_grupos(No *head, int K) {
    if (!head || K <= 1) return head;

    No *current = head;
    No *prevTail = NULL;
    No *newHead = NULL;

    while (current) {
        No *groupHead = current;
        No *prev = NULL;
        int count = 0;

        while (current && count < K) {
            No *next = current->prox;
            current->prox = prev;
            prev = current;
            current = next;
            count++;
        }
        if (!newHead) newHead = prev;
        if (prevTail) prevTail->prox = prev;
        prevTail = groupHead;
    }
    return newHead;
}


// 29. Palíndromo com espaço O(1)
int eh_palindromo(No *head) {
    if (!head || !head->prox) return 1;

    
    No *slow = head, *fast = head;
    while (fast && fast->prox) {
        slow = slow->prox;
        fast = fast->prox->prox;
    }


    No *prev = NULL;
    No *curr = slow;
    while (curr) {
        No *next = curr->prox;
        curr->prox = prev;
        prev = curr;
        curr = next;
    }

    
    No *p1 = head;
    No *p2 = prev;
    int res = 1;
    while (p2) {
        if (p1->dado != p2->dado) {
            res = 0;
            break;
        }
        p1 = p1->prox;
        p2 = p2->prox;
    }

   
    curr = prev;
    prev = NULL;
    while (curr) {
        No *next = curr->prox;
        curr->prox = prev;
        prev = curr;
        curr = next;
    }

    return res;
}


// 30. Trapping Rain Water
int trapping_rain_water(int *height, int n) {
    int stack[1000];
    int top = -1;
    int res = 0;
    for (int i = 0; i < n; i++) {
        while (top != -1 && height[i] > height[stack[top]]) {
            int top_idx = stack[top--];
            if (top == -1) break;
            int dist = i - stack[top] - 1;
            int bounded_height = (height[i] < height[stack[top]] ? height[i] : height[stack[top]]) - height[top_idx];
            res += dist * bounded_height;
        }
        stack[++top] = i;
    }
    return res;
}


typedef struct {
    int dados[100];
    int topo;
} PilhaInt;

void pilha_int_inicializar(PilhaInt *p) { p->topo = -1; }
int pilha_int_esta_vazia(PilhaInt *p) { return p->topo == -1; }
int pilha_int_push(PilhaInt *p, int val) {
    if (p->topo == 99) return 0;
    p->dados[++p->topo] = val;
    return 1;
}
int pilha_int_pop(PilhaInt *p) {
    if (pilha_int_esta_vazia(p)) return -1;
    return p->dados[p->topo--];
}




// Testes (main)

int main() {
    // Ex: 1
    printf("Teste Ex 1 - Inserção:\n");
    No *lista = NULL;
    inserir_fim(&lista, 10);
    inserir_fim(&lista, 20);
    inserir_inicio(&lista, 5);
    imprimir_lista(lista); 

    // Ex: 2
    printf("Teste Ex 2 - Contar nós: %d\n", contar_nos(lista)); 
    // Ex: 3
    printf("Teste Ex 3 - Buscar 10: %d\n", buscar_elemento(lista, 10)); 
    printf("Teste Ex 3 - Buscar 15: %d\n", buscar_elemento(lista, 15)); 

    // Ex: 4
    inserir_posicao(&lista, 15, 2); 
    imprimir_lista(lista); 

    // Ex: 5
    remover_valor(&lista, 10);
    imprimir_lista(lista); 

    // Ex: 6
    inverter_lista(&lista);
    imprimir_lista(lista); 

    // Ex: 7
    No *meio = encontrar_meio(lista);
    if (meio) printf("Meio da lista: %d\n", meio->dado); 

    // Ex: 8
    printf("Impressão reversa com pilha: ");
    imprimir_reversa_com_pilha(lista); 

    // Ex: 9
    printf("Teste Ex 9 - Pilha com array fixo:\n");
    PilhaArray p;
    pilha_array_inicializar(&p);
    pilha_array_push(&p, 1);
    pilha_array_push(&p, 2);
    pilha_array_push(&p, 3);
    printf("Topo da pilha: %d\n", pilha_array_topo(&p)); 
    printf("Pop: %d\n", pilha_array_pop(&p)); 
    printf("Pop: %d\n", pilha_array_pop(&p)); 

    // Ex: 10
    printf("Teste Ex 10 - Pilha com lista encadeada:\n");
    PilhaLista pl;
    pilha_lista_inicializar(&pl);
    pilha_lista_push(&pl, 100);
    pilha_lista_push(&pl, 200);
    printf("Topo: %d\n", pilha_lista_topo(&pl)); 
    printf("Pop: %d\n", pilha_lista_pop(&pl));   
    printf("Pop: %d\n", pilha_lista_pop(&pl));   
    printf("Pop em pilha vazia: %d\n", pilha_lista_pop(&pl)); 

    // Ex: 11
    printf("Teste Ex 11 - Balanceamento:\n");
    char s1[] = "({[]})";
    char s2[] = "({[})";
    printf("%s: %d\n", s1, verificar_balanceamento(s1)); 
    printf("%s: %d\n", s2, verificar_balanceamento(s2)); 

    // Ex: 12
    printf("Exercicio 12: inverter string\n");
    char s1[] = "hello";
    inverter_string(s1);
    printf("%s\n", s1); 

    // Ex: 13
    printf("Exercicio 13: verificar palindromo\n");
    printf("%d\n", verificar_palindromo("radar")); 
    printf("%d\n", verificar_palindromo("hello")); 

    // Ex: 14
    printf("Exercicio 14: ordenar pilha\n");
    PilhaInt p;
    pilha_int_inicializar(&p);
    pilha_int_push(&p, 3);
    pilha_int_push(&p, 1);
    pilha_int_push(&p, 4);
    pilha_int_push(&p, 2);
    ordenar_pilha(&p);
    while (!pilha_int_esta_vazia(&p)) {
        printf("%d ", pilha_int_pop(&p));
    }
    printf("\n"); 

    // Ex: 15
    printf("Exercicio 15: fila circular\n");
    FilaCirc f;
    fila_circ_inicializar(&f);
    fila_circ_enfileirar(&f, 10);
    fila_circ_enfileirar(&f, 20);
    fila_circ_enfileirar(&f, 30);
    printf("%d\n", fila_circ_frente(&f)); 
    printf("%d\n", fila_circ_desenfileirar(&f)); 
    printf("%d\n", fila_circ_frente(&f)); 

    // Ex: 16
    printf("Exercicio 16: fila com lista encadeada\n");
    FilaLista fl;
    fila_lista_inicializar(&fl);
    fila_lista_enfileirar(&fl, 5);
    fila_lista_enfileirar(&fl, 15);
    printf("%d\n", fila_lista_frente(&fl)); 
    printf("%d\n", fila_lista_desenfileirar(&fl)); 
    printf("%d\n", fila_lista_frente(&fl)); 

    // Ex: 17
    printf("Exercicio 17: gerar N números binários\n");
    gerar_binarios(5);
   
    // Ex: 18
    printf("Exercicio 18: inverter primeiros K elementos da fila\n");
    fila_lista_inicializar(&fl);
    for (int i = 1; i <= 5; i++) fila_lista_enfileirar(&fl, i); 
    inverter_primeiros_k(&fl, 3);
    NoFila *p = fl.inicio;
    while (p) {
        printf("%d ", p->dado);
        p = p->prox;
    }
    printf("\n"); 

    // Ex: 19
    printf("Exercicio 19: detectar ciclo\n");
    No *head = NULL;
    inserir_fim(&head, 1);
    inserir_fim(&head, 2);
    inserir_fim(&head, 3);
   
    head->prox->prox->prox = head->prox; 
    printf("%d\n", detectar_ciclo(head)); 

    
    head->prox->prox->prox = NULL;

   
    printf("Exercicio 20: unir listas ordenadas\n");
    No *l1 = NULL;
    No *l2 = NULL;
    inserir_fim(&l1, 1);
    inserir_fim(&l1, 3);
    inserir_fim(&l1, 5);

    inserir_fim(&l2, 2);
    inserir_fim(&l2, 4);
    inserir_fim(&l2, 6);

    No *unida = unir_listas_ordenadas(l1, l2);
    imprimir_lista(unida); 

     // Ex: 21
    printf("Exercicio 21: remover todas as ocorrencias\n");
    No *l = NULL;
    inserir_fim(&l, 1);
    inserir_fim(&l, 2);
    inserir_fim(&l, 2);
    inserir_fim(&l, 3);
    inserir_fim(&l, 2);
    remover_todas_ocorrencias(&l, 2);
    imprimir_lista(l); 

     // Ex: 22
    printf("Exercicio 22: encontrar intersecao\n");
    No *a1 = malloc(sizeof(No));
    No *a2 = malloc(sizeof(No));
    No *a3 = malloc(sizeof(No));
    a1->dado = 1; a1->prox = a2;
    a2->dado = 2; a2->prox = a3;
    a3->dado = 3; a3->prox = NULL;
    No *b1 = malloc(sizeof(No));
    b1->dado = 4; b1->prox = a2; 
    No *inter = encontrar_intersecao(a1, b1);
    printf("%d\n", inter ? inter->dado : -1); 

     // Ex: 23
    printf("Exercicio 23: rotacionar lista\n");
    No *r = NULL;
    for (int i = 1; i <= 5; i++) inserir_fim(&r, i);
    rotacionar_lista(&r, 2);
    imprimir_lista(r); 

     // Ex: 24
    printf("Exercicio 24: pilha com minimo\n");
    PilhaMin pm;
    pilha_min_inicializar(&pm);
    pilha_min_push(&pm, 5);
    pilha_min_push(&pm, 2);
    pilha_min_push(&pm, 3);
    printf("%d\n", pilha_min_minimo(&pm)); 
    pilha_min_pop(&pm);
    printf("%d\n", pilha_min_minimo(&pm)); 
    pilha_min_pop(&pm);
    printf("%d\n", pilha_min_minimo(&pm)); 

     // Ex: 25
    printf("Exercicio 25: duas pilhas em um array\n");
    DuasPilhas dp;
    duas_pilhas_inicializar(&dp);
    duas_pilhas_push1(&dp, 10);
    duas_pilhas_push2(&dp, 20);
    printf("%d %d\n", duas_pilhas_pop1(&dp), duas_pilhas_pop2(&dp)); 

     // Ex: 26
    printf("Exercicio 26: avaliar posfixa\n");
    printf("%d\n", avaliar_posfixa("3 4 + 2 *")); 

     // Ex: 27
    printf("Exercicio 27: fila usando duas pilhas\n");
    FilaDupla fd;
    fila_dupla_inicializar(&fd);
    fila_dupla_enfileirar(&fd, 1);
    fila_dupla_enfileirar(&fd, 2);
    printf("%d\n", fila_dupla_desenfileirar(&fd)); 
    printf("%d\n", fila_dupla_desenfileirar(&fd)); 
     
    // Ex: 28
    printf("Exercicio 28: inverter em grupos de K\n");
    No *g = NULL;
    for (int i = 1; i <= 5; i++) inserir_fim(&g, i);
    g = inverter_grupos(g, 2);
    imprimir_lista(g); 

     // Ex: 29
    printf("Exercicio 29: palindromo com O(1) espaco\n");
    No *p = NULL;
    inserir_fim(&p, 1);
    inserir_fim(&p, 2);
    inserir_fim(&p, 3);
    inserir_fim(&p, 2);
    inserir_fim(&p, 1);
    printf("%d\n", eh_palindromo(p)); 

     // Ex: 30
    printf("Exercicio 30: trapping rain water\n");
    int alturas[] = {0,1,0,2,1,0,1,3,2,1,2,1};
    printf("%d\n", trapping_rain_water(alturas, 12)); 

    return 0;
}

