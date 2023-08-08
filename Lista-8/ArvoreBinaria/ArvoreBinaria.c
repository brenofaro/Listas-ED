#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "ArvBin.h"


char compare(ITEM x, ITEM y)
{
    return x > y ? 1 : (x < y ? -1 : 0);
}


bool igual(ITEM x, ITEM y)
{
    return compare(x,y) == 0;
}


void inicializar(ARVORE_BINARIA *arvore)
{
    arvore = NULL;
}


bool vazia(ARVORE_BINARIA *arvore)
{
    return arvore == NULL;
}


void criarNo(ITEM item, ARVORE_BINARIA **arvore)
{
    if (!vazia(*arvore))
    {
       printf("ERRO: O no deve estar vazio para ser criado.");
       exit(EXIT_FAILURE);
    }

    *arvore = (ARVORE_BINARIA*) malloc(sizeof(ARVORE_BINARIA));
    (*arvore)->item = item;
    (*arvore)->pai = NULL;
    (*arvore)->esq = NULL;
    (*arvore)->dir = NULL;
}


bool existeNo(DIRECAO direcao, ARVORE_BINARIA *arvore)
{
   if (vazia(arvore))
      return false;

   if (direcao == NoRaiz)
      return true;
   
   if (direcao == NoPai)
      return !vazia(arvore->pai);

   if (direcao == NoEsquerdo)
      return !vazia(arvore->esq);

   if (direcao == NoDireito)
      return !vazia(arvore->dir);

   return false;
}


// Deslocar o apontador Arvore para o No indicado por Direcao
void deslocar(DIRECAO direcao, ARVORE_BINARIA **arvore)
{
   if (direcao == NoRaiz)
      while (existeNo(NoPai, *arvore))
         *arvore = (*arvore)->pai;

   if (direcao == NoPai)
      *arvore = (*arvore)->pai;

   if (direcao == NoEsquerdo)
      *arvore = (*arvore)->esq;

   if (direcao == NoDireito)
      *arvore = (*arvore)->dir;
}


bool obterItem(ITEM *item, ARVORE_BINARIA *arvore)
{
   if (vazia(arvore))
      return false;
  
   *item = arvore->item;
   return true;
}


bool alterarItem(ITEM item, ARVORE_BINARIA *arvore)
{
   if (vazia(arvore))
      return false;
  
   arvore->item = item;
   return true;
}


bool adicionarFilho(ITEM item, DIRECAO direcao, ARVORE_BINARIA *arvore)
{
   if (vazia(arvore) || (direcao == NoPai) || (direcao == NoRaiz) || existeNo(direcao, arvore))
     return false;  // Criacao ilegal de um filho

   if (direcao == NoEsquerdo)
   {
       criarNo(item, &(arvore->esq));
       arvore->esq->pai = arvore;
   }
   else
   {
       criarNo(item, &(arvore->dir));
       arvore->dir->pai = arvore;
   }
   return true;
}


void disposeArvore(ARVORE_BINARIA *arvore)
{
   if (!vazia(arvore))
   {
      disposeArvore(arvore->esq);
      disposeArvore(arvore->dir);
      free(arvore);
   }
}


void deltree(ARVORE_BINARIA **arvore)
{
   ARVORE_BINARIA *pTemp = *arvore;

   /* 
     Testa se Arvore tem pai. Caso tenha, arvore se desloca para ele e pTemp
     continua apontando para o inicio da arvore a ser deletada, depois a
     arvore e apagada e o apontador do pai e atualizado com NULL. Caso Arvore
     nao tenha pai, a arvore e eliminada usando pTemp e arvore recebe NULL */
   if (existeNo(NoPai, *arvore))
   {
      deslocar(NoPai, arvore);
      disposeArvore(pTemp);
      if ((*arvore)->esq == pTemp)
         (*arvore)->esq = NULL;
      else
         (*arvore)->dir = NULL;
   }
   else
   {
      disposeArvore(pTemp);
      arvore = NULL;
   }
}


void preOrdem(ARVORE_BINARIA *arvore, void (*visite)(ARVORE_BINARIA*) )
{
   if (!vazia(arvore))
   {         
      visite(arvore);
      preOrdem(arvore->esq, visite);
      preOrdem(arvore->dir, visite);
   }
}


void inOrdem(ARVORE_BINARIA *arvore, void (*visite)(ARVORE_BINARIA*) )
{
   if (!vazia(arvore))
   {         
      inOrdem(arvore->esq, visite);
      visite(arvore);
      inOrdem(arvore->dir, visite);
   }
}


void posOrdem(ARVORE_BINARIA *arvore, void (*visite)(ARVORE_BINARIA*) )
{
   if (!vazia(arvore))
   {         
      posOrdem(arvore->esq, visite);
      posOrdem(arvore->dir, visite);
      visite(arvore);
   }
}