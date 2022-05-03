#include <sys/time.h>

#include<stdio.h>
#include<stdlib.h>
#include"ArvInt.h"
#define bool int

struct tNode
{
    int data;
    struct tNode* esq;
    struct tNode* dir;
};

struct sNode
{
    struct tNode *t;
    struct sNode *prox;
};

void push(struct sNode** top_ref, struct tNode *t);
struct tNode *pop(struct sNode** top_ref);
bool isEmpty(struct sNode *top);

int insere_ArvBin(struct tNode* raiz, int valor){
    if(raiz == NULL)
        return 0;
    struct tNode* novo;
    novo = (struct tNode*) malloc(sizeof(struct tNode));
    if(novo == NULL)
        return 0;
    novo->data = valor;
    novo->dir = NULL;
    novo->esq = NULL;

    if(raiz == NULL)
        raiz = novo;
    else{
        struct tNode *atual = raiz;
        struct tNode *ant = NULL;
        while(atual != NULL){
            ant = atual;
            if(valor == atual->data){
                free(novo);
                return 0;
            }

            if(valor > atual->data)
                atual = atual->dir;
            else
                atual = atual->esq;
        }
        if(valor > ant->data)
            ant->dir = novo;
        else
            ant->esq = novo;
    }
    return 1;
}

void inOrder(struct tNode *root){
    struct tNode *current = root;
    struct sNode *s = NULL;
    bool done = 0;

    while (!done)
    {

        if(current != NULL)
        {
            push(&s, current);
            current = current->esq;
        }
        else
        {
            if (!isEmpty(s))
            {
                current = pop(&s);
                current = current->dir;
            }
            else
                done = 1;
        }
    }
}

int verificaFolha(struct tNode *no){
    if(no->esq == NULL && no->dir ==NULL){
        return 1;
    }
    return 0;
}
void liberaNO(struct tNode *no){
    if(verificaFolha(no) == 1)
        free(no);
}

int quantNos(struct tNode *root){
    struct tNode *current = root;
    struct sNode *s = NULL;
    bool done = 0;
    int quant = 0;

    while (!done)
    {

        if(current != NULL)
        {
            quant++;
            push(&s, current);
            current = current->esq;
        }
        else
        {

            if (!isEmpty(s))
            {
                current = pop(&s);
                liberaNO(current);
                current = current->dir;
            }
            else
                done = 1;
        }
    }
    return quant;
}


/* UTILITY FUNCTIONS */
/* Function to push an item to sNode*/
void push(struct sNode** top_ref, struct tNode *t)
{
/* allocate tNode */
    struct sNode* new_tNode =
            (struct sNode*) malloc(sizeof(struct sNode));

    if(new_tNode == NULL)
    {
        printf("Stack Overflow \n");
        getchar();
        exit(0);
    }

/* put in the data */
    new_tNode->t = t;

/* link the old list off the new tNode */
    new_tNode->prox = (*top_ref);

/* move the head to point to the new tNode */
    (*top_ref) = new_tNode;
}

/* The function returns true if stack is empty, otherwise false */
bool isEmpty(struct sNode *top)
{
    return (top == NULL)? 1 : 0;
}

/* Function to pop an item from stack*/
struct tNode *pop(struct sNode** top_ref)
{
    struct tNode *res;
    struct sNode *top;

/*If sNode is empty then error */
    if(isEmpty(*top_ref))
    {
        printf("Stack Underflow \n");
        getchar();
        exit(0);
    }
    else
    {
        top = *top_ref;
        res = top->t;
        *top_ref = top->prox;
        free(top);
        return res;
    }
}

/* Helper function that allocates a new tNode with the
given data and NULL esq and dir pointers. */
struct tNode* newtNode(int data)
{
    struct tNode* tNode = (struct tNode*)
            malloc(sizeof(struct tNode));
    tNode->data = data;
    tNode->esq = NULL;
    tNode->dir = NULL;

    return(tNode);
}
float timedifference_msec(struct timeval t0, struct timeval t1)
{
    return (t1.tv_sec - t0.tv_sec) * 1000.0f + (t1.tv_usec - t0.tv_usec) / 1000.0f;
}

int main()
{
    struct timeval t0;
    struct timeval t1;
    float elapsed;

    int flag = 10000;

    gettimeofday(&t0, 0);

    struct tNode *root = newtNode(1);
    for(int i = 0 ; i< 100000;i++) {
        insere_ArvBin(root, i);
    }
    //inOrder(root);

    gettimeofday(&t1, 0);
    elapsed = timedifference_msec(t0, t1);
    printf("\n%d", quantNos(root));

    printf("\nCode executed in %f milliseconds.\n", elapsed);
    return 0;
}
