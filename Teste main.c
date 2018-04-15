#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

typedef struct{
int largura;
int altura;
int profundidade;
int areaBase;
int valorUtilidade;
char rotacao[3];
}Caixa;

void insertionSortBase(Caixa *V,int n){
    int i, j;
    Caixa aux;
    for(i=1; i<n;i++){
        aux = V[i];
        for(j=i; j>0 && (aux.areaBase<V[j-1].areaBase);j--)
            V[j] = V[j - 1];
        V[j] = aux;

    }
}
int main(void){

int hPilha;
int numCaixas;
Caixa *caixas;
Caixa *caixasRot;

 FILE *arq;
  char Linha[100];
  char *result;
    int i,j,k;



  // Abre um arquivo TEXTO para LEITURA
  arq = fopen("stk10.data", "rt");

  if (arq == NULL)  // Se houve erro na abertura
  {
     printf("Problemas na abertura do arquivo\n");
     return;
  }

  i = 1;
  j = 1;
  k = 0;
  while (!feof(arq))
  {
	// Lê uma linha (inclusive com o '\n')
      result = fgets(Linha, 100, arq);  // o 'fgets' lê até 99 caracteres ou até o '\n'
      if (result)  // Se foi possível ler
	  //printf("Linha %d : %s",i,Linha);

      if(i == 1){
        numCaixas = atoi(result);
        printf("Numero de caixas %d: \n",numCaixas);
        caixas = (Caixa *)malloc(numCaixas * sizeof(Caixa));
        //caixas2 = (Caixa *)malloc(numCaixas * sizeof(Caixa));
        }

      if(i == 2){
        hPilha = atoi(result);
        printf("Altura da pilha %d: \n",hPilha);
        }else

        if((i>2) && (i<=numCaixas+2)){
            caixas[i-3].valorUtilidade = atoi(result);
            printf("Caixas[%d].valorUtilidade = %d\n",i-3,atoi(result));
        }

      if(i>numCaixas+2 && i <= numCaixas*3 + (numCaixas + 2)){
        if((i-(numCaixas+3))%3 == 0){
            caixas[k].largura = atoi(result);
            printf("Caixa[%d].largura = %d\n", k, caixas[k].largura );

        }
        if((i-(numCaixas+3))%3==1){
            caixas[k].altura = atoi(result);
            printf("Caixa[%d].altura = %d\n", k, caixas[k].altura );

        }
        if((i-(numCaixas+3))%3==2){
            caixas[k].profundidade = atoi(result);
            caixas[k].areaBase = caixas[k].largura * caixas[k].profundidade;
            strcpy(caixas[k].rotacao,"R1");
            printf("Caixa[%d].profunfidade = %d\n", k, caixas[k].profundidade );
        k++;
        }


      }
      i++;

  }//fim while

  printf("Vetor de caixas na rotacao normal \n");
  for (i = 0;i<numCaixas;i++){

  }
  //Preenchimento do vetor com as caixas com as duas rotações
  caixasRot = (Caixa *)malloc(2*numCaixas * sizeof(Caixa));
  k = 0;
  for (i=0;i<2*numCaixas;i++){
    if(i<numCaixas){
        caixasRot[i] = caixas[i];
        printf("CaixasRot[%d].rotacao = %s\n",i,caixasRot[i].rotacao);
        printf("CaixasRot[%d].valorUtilidade = %d\n",i,caixasRot[i].valorUtilidade);
        printf("CaixasRot[%d].largura = %d\n",i,caixasRot[i].largura);
        printf("CaixasRot[%d].altura = %d\n",i,caixasRot[i].altura);
        printf("CaixasRot[%d].profundidade = %d\n",i,caixasRot[i].profundidade);
        printf("CaixasRot[%d].areaBase = %d\n",i,caixasRot[i].areaBase);
    }else{
        strcpy(caixasRot[i].rotacao,"R2");;
        printf("CaixasRot[%d].rotacao = %s\n",i,caixasRot[i].rotacao);
        caixasRot[i].valorUtilidade = caixas[k].valorUtilidade;
        printf("CaixasRot[%d].valorUtilidade = %d\n",i,caixasRot[i].valorUtilidade);
        caixasRot[i].altura = caixas[k].largura;
        printf("CaixasRot[%d].altura = %d\n",i,caixasRot[i].altura);
        caixasRot[i].largura = caixas[k].altura;
        printf("CaixasRot[%d].largura = %d\n",i,caixasRot[i].largura);
        caixasRot[i].profundidade = caixas[k].profundidade;
        printf("CaixasRot[%d].profundidade = %d\n",i,caixasRot[i].profundidade);
        caixasRot[i].areaBase = caixas[k].altura * caixas[k].profundidade;
        printf("CaixasRot[%d].areaBase = %d\n",i,caixasRot[i].areaBase);
        k++;
    }
}


  fclose(arq);

  free(caixas);
  free(caixasRot);
  return 0;
}
