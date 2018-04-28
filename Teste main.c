#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <math.h>

typedef struct{
int largura;
int altura;
int profundidade;
int areaBase;
int valorUtilidade;
int idCaixa;
char rotacao[3];
}Caixa;

void quicksort(Caixa *A, int esq, int dir) { // esq 0, n-1
    Caixa y;
    int i = esq;
    int j = dir;
    int pivo = A[(esq + dir) / 2].areaBase;

    while(i <= j) {
        while(A[i].areaBase > pivo && i < dir)
            i++;
        while(A[j].areaBase < pivo && j > esq)
            j--;
        if(i <= j) {
            y = A[i];
            A[i] = A[j];
            A[j] = y;
            i++;
            j--;
        }
    }
    if(j > esq)
        quicksort(A, esq, j);
    if(i < dir)
        quicksort(A, i, dir);
}
int compara(const void *a, const void *b){
    Caixa *caixas = (Caixa *)a;
    Caixa *caixasRot = (Caixa *)b;
    return (caixasRot->areaBase - caixas->areaBase);
}

void insertionSortBase(Caixa *V,int n){
    int i, j= 0;
    Caixa aux;
    for(i=1; i<n;i++){
        aux = V[i];
        for(j=i; j>0 && (aux.valorUtilidade<V[j-1].valorUtilidade);j--){
            V[j] = V[j - 1];
            }
        V[j] = aux;
    }
}
//Verifica se caixa de cima é empilhável na caixa de baixo
int empilhavel(Caixa acima, Caixa abaixo){
    if (acima.profundidade <= abaixo.profundidade &&
        acima.largura <= abaixo.largura ){
        return 1;
        }
}
int maior(int a, int b){
    if(a > b)
        return a;
    else
        return b;
}
int menor(int a, int b){
    if(a < b)
        return a;
    else
        return b;
}
int menorAltura(Caixa *vet,int n){
int menor = vet[0].altura;
int i;
for (i = 1;i<n;i++){
    if(vet[i].altura < menor){
        menor = vet[i].altura;
    }
}
return menor;
}
int main(void){


int ***pilhaCaixa;
int **pilhaCaixa2d;
int **mAdjacencia;
int hPilha;
int *vetUtilidade;
int numCaixas;
int valorTotal;
int empilhadas;
int alturaRestante;
int hPilhaTmp;
int basePilha;
int uTemp;
int uMax;
int solucOtima;
Caixa *solucao;
Caixa caixaBase;
Caixa *caixas;
Caixa *caixasRot;
Caixa **caixaria;

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
            caixas[k].idCaixa = k;
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
        printf("CaixasRot[%d].idCaixa = %d\n",i,caixasRot[i].idCaixa);
        printf("CaixasRot[%d].rotacao = %s\n",i,caixasRot[i].rotacao);
        printf("CaixasRot[%d].valorUtilidade = %d\n",i,caixasRot[i].valorUtilidade);
        printf("CaixasRot[%d].largura = %d\n",i,caixasRot[i].largura);
        printf("CaixasRot[%d].altura = %d\n",i,caixasRot[i].altura);
        printf("CaixasRot[%d].profundidade = %d\n",i,caixasRot[i].profundidade);
        printf("CaixasRot[%d].areaBase = %d\n",i,caixasRot[i].areaBase);
    }else{
        caixasRot[i].idCaixa = caixas[k].idCaixa;
        printf("CaixasRot[%d].idCaixa = %d\n",i,caixasRot[i].idCaixa);
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
//ordenação da entrada pela área da base
numCaixas *=2;
//quicksort(caixasRot,0, numCaixas-1);

qsort(caixasRot,numCaixas,sizeof(caixasRot),compara);
//insertionSortBase(caixasRot,numCaixas);

for(i = 0;i<numCaixas;i++){
        printf("CaixasRot[%d].idCaixa = %d\n",i,caixasRot[i].idCaixa);
        printf("CaixasRot[%d].rotacao = %s\n",i,caixasRot[i].rotacao);
        printf("CaixasRot[%d].valorUtilidade = %d\n",i,caixasRot[i].valorUtilidade);
        printf("CaixasRot[%d].largura = %d\n",i,caixasRot[i].largura);
        printf("CaixasRot[%d].altura = %d\n",i,caixasRot[i].altura);
        printf("CaixasRot[%d].profundidade = %d\n",i,caixasRot[i].profundidade);
        printf("CaixasRot[%d].areaBase = %d\n",i,caixasRot[i].areaBase);

}
printf("depois do for ordenado \n");

printf("Empilhavel: %d\n",empilhavel(caixasRot[0],caixasRot[0]));

/*
caixaria = (Caixa**)malloc(numCaixas * sizeof(Caixa*));
for (i=0;i<numCaixas;i++){
    caixaria[i] = (Caixa*)malloc(numCaixas * sizeof(Caixa*));
}
*/


//for(i = 0;i < numCaixas; i++){
//    for(j = 0; j<numCaixas; j++){
//        if(empilhavel(caixasRot[i], caixasRot[j])==1){
//            mAdjacencia[i][j] = 1;
//        }
//        //printf("c[%d][%d] = %d",i,j,mAdjacencia[i][j]);
//    }
//    printf("\n");
//}

numCaixas +=1;
hPilha +=1;

mAdjacencia = (int *)malloc(numCaixas * sizeof (int));
for (j = 0; j < numCaixas; j++){
    mAdjacencia[j] = (int *)malloc(hPilha*sizeof(int));
}
for(i = 1; i<numCaixas; i++){
        printf("\n");
    for(j = 1;j <numCaixas; j++){
        if(empilhavel(caixasRot[i-1],caixasRot[j-1])==1){
            mAdjacencia[i-1][j-1] = 1;
        }else{
            mAdjacencia[i-1][j-1] = 0;
        }
        printf("(%d,%d):%d",i-1,j-1,mAdjacencia[i-1][j-1]);
    }
}




//pilhaCaixa = (int ***)malloc(numCaixas*sizeof(int**));
//        for (i = 0; i< numCaixas; i++) {
//         pilhaCaixa[i] = (int **) malloc(numCaixas*sizeof(int *));
//          for (j = 0; j < numCaixas; j++) {
//              pilhaCaixa[i][j] = (int *)malloc(hPilha*sizeof(int));
//          }
//        }



pilhaCaixa2d = (int *)malloc(numCaixas * sizeof (int));
for (j = 0; j < numCaixas; j++){
    pilhaCaixa2d[j] = (int *)malloc(hPilha * sizeof(int));
}

for(i = 0;i<numCaixas;i++){
   //printf("\n");
    for(j = 0;j<hPilha;j++){
    //Se a caixa for 0, ou a altura testada for 0, então preenche linha e/ou coluna com 0;
        if(i == 0 || j==0){
            pilhaCaixa2d[i][j] = 0;
        }else if(i==1){
                if(caixasRot[i-1].altura > j){
                    pilhaCaixa2d[i][j] = 0;
                }else if(caixasRot[i-1].altura == j){
                    pilhaCaixa2d[i][j] = caixasRot[i-1].valorUtilidade;

            }else if(caixasRot[i-1].altura < j){
                pilhaCaixa2d[i][j] = (int)floor(j/caixasRot[i-1].altura)*caixasRot[i-1].valorUtilidade;
            }
        }else if( i>0 && j == caixasRot[i-1].altura){ //Se altura da caixa for igual à altura testada
                pilhaCaixa2d[i][j] = caixasRot[i-1].valorUtilidade;

                    if(pilhaCaixa2d[i-1][j] > pilhaCaixa2d[i][j]){
                        pilhaCaixa2d[i][j] = pilhaCaixa2d[i-1][j];
                    }else if(pilhaCaixa2d[i][j-1] > pilhaCaixa2d[i][j]){
                            pilhaCaixa2d[i][j] = pilhaCaixa2d[i][j-1];
                    }
        }  else if(i > 0 && j < caixasRot[i-1].altura){
                pilhaCaixa2d[i][j] = 0;
                if(pilhaCaixa2d[i-1][j] > pilhaCaixa2d[i][j]){
                        pilhaCaixa2d[i][j] = pilhaCaixa2d[i-1][j];
                }else if(pilhaCaixa2d[i][j-1] > pilhaCaixa2d[i][j]){
                            pilhaCaixa2d[i][j] = pilhaCaixa2d[i][j-1];
                }
        }else if(i > 0 && j > caixasRot[i-1].altura){
            pilhaCaixa2d[i][j] = (int)floor(j/caixasRot[i-1].altura)*caixasRot[i-1].valorUtilidade;
            //  pilhaCaixa2d[i][j] = caixasRot[i-1].valorUtilidade;
                for(k= 1;k<i;k++){
                if(empilhavel(caixasRot[i-1], caixasRot[k-1]) == 1 &&
                   caixasRot[k-1].altura + caixasRot[i-1].altura <= j &&
                   caixasRot[k-1].valorUtilidade + caixasRot[i-1].valorUtilidade<= floor(j/caixasRot[i-1].altura)*caixasRot[i-1].valorUtilidade){
                    pilhaCaixa2d[i][j] = caixasRot[i-1].valorUtilidade + caixasRot[k-1].valorUtilidade;
                }
            }
//            if(pilhaCaixa2d[i-1][j] > pilhaCaixa2d[i][j]){
//                pilhaCaixa2d[i][j] = pilhaCaixa2d[i-1][j];
//                }else if(pilhaCaixa2d[i][j-1] > pilhaCaixa2d[i][j]){
//                    pilhaCaixa2d[i][j] = pilhaCaixa2d[i][j-1];
//                }



//            for(k = 1;k<numCaixas;k++){
//                if(mAdjacencia[i-1][k-1]==1 && floor(j/(caixasRot[i-1].altura + caixasRot[k-1].altura) >= 1 &&
//                 pilhaCaixa2d[i][j]< floor(j/caixasRot[k-1].altura)*caixasRot[i-1].valorUtilidade )){
//                 pilhaCaixa2d[i][j]=floor(j/caixasRot[k-1].altura)*caixasRot[k-1].valorUtilidade;
//                }
//            }
//            for (k = 1;k<numCaixas; k++){
//                //printf("entrou no for interno");
//                    if(empilhavel(caixasRot[k-1],caixasRot[i-1]) == 1 &&
//                    pilhaCaixa2d[i][j]< (caixasRot[k-1].valorUtilidade+caixasRot[i-1].valorUtilidade)){
//                    pilhaCaixa2d[i][j] = caixasRot[k-1].valorUtilidade+caixasRot[i-1].valorUtilidade;
//                }
//            }

        }

        //printf(" %d ",pilhaCaixa2d[i][j]);
    }

}

k = 0;
for(int i = 1;i<numCaixas;i++){
    for(j = 1;j<hPilha;j++){
        if(maior(pilhaCaixa2d[i][j],k) == pilhaCaixa2d[i][j]){
            k = pilhaCaixa2d[i][j];
    }
}
}
printf("(Caixas, Sol. Otima) = (%d,%d)",(numCaixas - 1)/2, k);
//Matriz de adjacência mostrando caixas que são empilháveis
//for(i = 0;i < numCaixas; i++){
//
//    for(j = 0;j<=i; j++){
//        if(empilhavel(caixasRot[i],caixasRot[j]) == 1){
//            mAdjacencia[i][j] = 1;
//            printf("V[%d][%d]= %d\n",i,j,mAdjacencia[i][j]);
//        }else{
//            mAdjacencia[i][j] = 0;
//            printf("V[%d][%d]= %d\n",i,j,mAdjacencia[i][j]);
//        }
//    }
//}



//for(i = 0;i<numCaixas;i++){
//    for(j=1;j<hPilha;j++){
//
//        if(caixasRot[i].altura < j){
//            pilhaCaixa2d[i][j] = 0;
//        }
//        if(j % caixasRot[i].altura == 0 && (int)floor(j/caixasRot[i].altura)==1){
//            pilhaCaixa2d[i][j] = caixasRot[i].valorUtilidade;
//            //printf("%d ",pilhaCaixa2d[i][j]);
//        }
//        if(j % caixasRot[i].altura < menorAltura(caixasRot,numCaixas) && (int)floor(j/caixasRot[i].altura)==1){
//            pilhaCaixa2d[i][j] = caixasRot[i].valorUtilidade;
//           // printf("%d ",pilhaCaixa2d[i][j]);
//
//        }
//        if(j % caixasRot[i].altura > menorAltura(caixasRot,numCaixas)){
//        valorTotal = j % caixasRot[i].altura;
//
//        pilhaCaixa2d[i][j] = (int)floor(j/caixasRot[i].altura) * caixasRot[i].valorUtilidade;
//        printf("%d ",pilhaCaixa2d[i][j]);
//
//    }
//
//}
//}

//Solução unidimensional

//
//for (i = 0; i<numCaixas;i++){
//    for(j = 0;j<hPilha; j++){
//        if(i == 0){
//            if(caixasRot[i].altura>j){
//            pilhaCaixa2d = 0;
//            }else{
//            pilhaCaixa2d = (int)floor(j/caixasRot[i].altura)*caixasRot[i].valorUtilidade;
//        }
//
//        }else{
//            if(caixasRot[i].altura > j ||
//               pilhaCaixa2d[i-1][j-1] == 0 ||
//               pilhaCaixa2d[i][j] == 0 ||
//               pilhaCaixa2d[i][j-1]){
//
//            }
//        }
//
//
//    }
//
//}

//
//for(i = 0; i<=numCaixas;i++){
//    for (j = 0; j <= hPilha; j++){
//    //mAdjacencia[i][j] = 0;
//}
//}

free(vetUtilidade);
free(pilhaCaixa);
free(pilhaCaixa2d);
free(mAdjacencia);
fclose(arq);
free(caixas);
free(caixasRot);

return 0;
}
