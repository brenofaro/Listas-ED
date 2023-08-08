#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "ArvBin.h"

/////////////////////////////////////////////////////
// Visita um NO da arvore, imprimindo o valor da chave
// entre parenteses
void visite(ARVORE_BINARIA *arvore) {
    printf("(%d)", arvore->item);
}

/////////////////////////////////////////////////////

int main()
{
   ARVORE_BINARIA *arv = NULL;
   inicializar(arv);

   ITEM item;
   item = 1;
   criarNo(item, &arv); // cria o no Raiz
   
   item = 2;
   adicionarFilho(item, NoEsquerdo, arv);
   item = 5;
   adicionarFilho(item, NoDireito, arv);
   /*
                 1
              2     5
   */

   printf("inOrdem: ");
   inOrdem(arv, visite);
   printf("\n");
   printf("inOrdem: ");
   inOrdem(arv, visite);
   printf("\n");
   printf("posOrdem: ");
   posOrdem(arv, visite);
   printf("\n");
   printf("preOrdem: ");
   preOrdem(arv, visite);
   printf("\n");

   item = 3;
   adicionarFilho(item, NoEsquerdo, arv->esq);
   item = 4;
   adicionarFilho(item, NoDireito, arv->esq);

   item = 6;
   adicionarFilho(item, NoEsquerdo, arv->dir);
   item = 7;
   adicionarFilho(item, NoDireito, arv->dir->esq);
  
/*
                                1
                             2     5
                            3 4   6
                                   7
*/

   printf("preOrdem: ");
   preOrdem(arv, visite); // Imprime: (1)(2)(3)(4)(5)(6)(7)
   printf("\n");

   deslocar(NoDireito, &arv);  // Vai para o No 5
   printf("Esperando 5, obtido %d\n", arv->item);   
   printf("Existe no esquerdo = %s\n", existeNo(NoEsquerdo, arv) ? "sim" : "nao");  // Deve ser TRUE
   printf("Existe no direito  = %s\n", existeNo(NoDireito, arv) ? "sim" : "nao");   // Deve ser FALSE

   deslocar(NoEsquerdo, &arv);  // Vai para 6
   deslocar(NoDireito, &arv);   // Vai para 7
   printf("Esperando 7, obtido %d\n", arv->item);

   deslocar(NoPai, &arv);  // Vai para 6
   printf("Esperando 6, obtido %d\n", arv->item);

   deslocar(NoRaiz, &arv); // Vai para 1
   printf("Esperando 1, obtido %d\n", arv->item);

   
   // Partindo da raiz, desce para o filho direito e executa um deltree
   deslocar(NoDireito, &arv);
   deltree(&arv);

/*
                              1
                             2
                            3 4
*/

   printf("preOrdem: ");
   preOrdem(arv, visite); // Imprime: (1)(2)(3)(4)
   printf("\n");

   disposeArvore(arv);
   return 0;
}
