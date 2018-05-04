#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <math.h>

typedef struct
{
    int largura;
    int altura;
    int profundidade;
    int areaBase;
    int valorUtilidade;
    int idCaixa;
    char rotacao[3];
} Caixa;

void quicksort(Caixa *A, int esq, int dir)   // esq 0, n-1
{
    Caixa y;
    int i = esq;
    int j = dir;
    int pivo = A[(esq + dir) / 2].areaBase;

    while(i <= j)
    {
        while(A[i].areaBase > pivo && i < dir)
            i++;
        while(A[j].areaBase < pivo && j > esq)
            j--;
        if(i <= j)
        {
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
int compara(const void *a, const void *b)
{
    Caixa *caixas = (Caixa *)a;
    Caixa *caixasRot = (Caixa *)b;
    return (caixasRot->areaBase - caixas->areaBase);
}

void insertionSortP(Caixa *V,int n)
{
    int i, j= 0;
    Caixa aux;
    for(i=1; i<n; i++)
    {
        aux = V[i];
        for(j=i; j>0 && (aux.areaBase>V[j-1].areaBase); j--)
        {
            V[j] = V[j - 1];
        }
        V[j] = aux;
    }
}
//Verifica se caixa de cima é empilhável na caixa de baixo
int empilhavel(Caixa acima, Caixa abaixo)
{
    if (acima.profundidade <= abaixo.profundidade &&
            acima.largura <= abaixo.largura )
    {
        return 1;
    }
    else
        return 0;
}
int maior(int a, int b)
{
    if(a > b)
        return a;
    else
        return b;
}
int menor(int a, int b)
{
    if(a < b)
        return a;
    else
        return b;
}
int menorAltura(Caixa *vet,int n)
{
    int menor = vet[0].altura;
    int i;
    for (i = 1; i<n; i++)
    {
        if(vet[i].altura < menor)
        {
            menor = vet[i].altura;
        }
    }
    return menor;
}
/*
int topDown(int hMax,int nCx,int *memo,Caixas *vet)
{
    int i,temp,hTemp = 0;
    if(memo[hMax]!=-1)
    {
        return memo[hMax];
    }
    else
    {
        memo[hMax] =0;
        for(i = 0; i<nCx; i++)
        {
            for(j = 0; j<hMax; j++)
            {
                if(i==0 || j==0)
                {
                    memo[i] == 0;
                }
                hTemp = j - vet[i].altura;
                if(hTemp>=0)
                {
                    temp = topDown(hTemp, nCx, memo,Caixas *vet)+vet[i].valorUtilidade;
                }
                if(temp > memo[hMax])
                {
                    memo[hMax] = temp;
                    return memo[hMax];
                }
            }
        }
    }

}
*/
int main(void)
{

    int *memo;
    int **basePilha;
    int **pilhaCaixa2d;
    int **mAdjacencia;
    int hPilha;
    int clinha,mlinha;


    int a;
    int numCaixas;
    int valorTotal;
    int hRest;
    int maisUtil;
    int hPilhaTmp;
    int solucOtima;

    Caixa caixaBase;
    Caixa *solucao;
    Caixa *caixas;
    Caixa *caixasRot;


    FILE *arq;
    char Linha[100];
    char *result;
    int i,j,k;



    // Abre um arquivo TEXTO para LEITURA
    arq = fopen("stk03h.data", "rt");

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

            if(i == 1)
            {
                numCaixas = atoi(result);
                printf("Numero de caixas %d: \n",numCaixas);
                caixas = (Caixa *)malloc(numCaixas * sizeof(Caixa));
                //caixas2 = (Caixa *)malloc(numCaixas * sizeof(Caixa));
            }

        if(i == 2)
        {
            hPilha = atoi(result);
            printf("Altura da pilha %d: \n",hPilha);
        }
        else

            if((i>2) && (i<=numCaixas+2))
            {
                caixas[i-3].valorUtilidade = atoi(result);
                printf("Caixas[%d].valorUtilidade = %d\n",i-3,atoi(result));
            }

        if(i>numCaixas+2 && i <= numCaixas*3 + (numCaixas + 2))
        {
            if((i-(numCaixas+3))%3 == 0)
            {
                caixas[k].largura = atoi(result);
                printf("Caixa[%d].largura = %d\n", k, caixas[k].largura );

            }
            if((i-(numCaixas+3))%3==1)
            {
                caixas[k].altura = atoi(result);
                printf("Caixa[%d].altura = %d\n", k, caixas[k].altura );

            }
            if((i-(numCaixas+3))%3==2)
            {
                caixas[k].profundidade = atoi(result);
                caixas[k].areaBase = caixas[k].largura * caixas[k].profundidade;
                strcpy(caixas[k].rotacao,"R1");
                caixas[k].idCaixa = k+1;
                printf("Caixa[%d].profunfidade = %d\n", k, caixas[k].profundidade );
                k++;
            }
        }
        i++;
    }//fim while

    //Preenchimento do vetor com as caixas com as duas rotações
    caixasRot = (Caixa *)malloc(2*numCaixas * sizeof(Caixa));

    k = 0;
    for (i=0; i<2*numCaixas; i++)
    {
        if(i<numCaixas)
        {
            caixasRot[i] = caixas[i];
        }
        else
        {
            caixasRot[i].idCaixa = caixas[k].idCaixa;
            strcpy(caixasRot[i].rotacao,"R2");
            caixasRot[i].valorUtilidade = caixas[k].valorUtilidade;
            caixasRot[i].altura = caixas[k].largura;
            caixasRot[i].largura = caixas[k].altura;
            caixasRot[i].profundidade = caixas[k].profundidade;
            caixasRot[i].areaBase = caixasRot[i].largura * caixasRot[i].profundidade;
            k++;
        }
    }

//ordenação da entrada pela área da base
    printf("%d %d",caixasRot[1].largura,caixasRot[2].largura);
    printf("Empilhavel: %d\n",empilhavel(caixasRot[1],caixasRot[2]));
    numCaixas *=2;
 //uicksort(caixasRot,0, numCaixas-1);

//ort(caixasRot,numCaixas,sizeof(caixasRot),compara);
insertionSortP(caixasRot,numCaixas);

    for(i = 0; i<numCaixas; i++)
    {
        printf("CaixasRot[%d].idCaixa = %d\n",i,caixasRot[i].idCaixa);
        printf("CaixasRot[%d].rotacao = %s\n",i,caixasRot[i].rotacao);
        printf("CaixasRot[%d].valorUtilidade = %d\n",i,caixasRot[i].valorUtilidade);
        printf("CaixasRot[%d].largura = %d\n",i,caixasRot[i].largura);
        printf("CaixasRot[%d].altura = %d\n",i,caixasRot[i].altura);
        printf("CaixasRot[%d].profundidade = %d\n",i,caixasRot[i].profundidade);
        printf("CaixasRot[%d].areaBase = %d\n",i,caixasRot[i].areaBase);

    }



    numCaixas +=1;
    hPilha +=1;


//mAdjacencia = (int *)malloc(numCaixas * sizeof (int));
//for (j = 0; j < numCaixas; j++){
//    mAdjacencia[j] = (int *)malloc(hPilha*sizeof(int));
//}
//for(i = 1; i<numCaixas; i++){
//        printf("\n");
//    for(j = 1;j <numCaixas; j++){
//        if(empilhavel(caixasRot[i-1],caixasRot[j-1])==1){
//            mAdjacencia[i-1][j-1] = 1;
//        }else{
//            mAdjacencia[i-1][j-1] = 0;
//        }
//        //printf("(%d,%d):%d",i-1,j-1,mAdjacencia[i-1][j-1]);
//    }
//}


    pilhaCaixa2d = (int*)malloc(numCaixas * sizeof (int));
    for (j = 0; j < numCaixas; j++)
    {
        pilhaCaixa2d[j] = (int*)malloc(hPilha * sizeof(int));
    }

    basePilha = (int*)malloc(numCaixas * sizeof (int));
    for (j = 0; j < numCaixas; j++)
    {
        basePilha[j] = (int*)malloc(hPilha * sizeof(int));
    }


    for(i = 0; i<numCaixas; i++)
    {
        //printf("Caixa %d: R = %s ",caixasRot[i].idCaixa,caixasRot[i].rotacao);
        for(j = 0; j<hPilha; j++)
        {
            //Se a caixa for 0, ou a altura testada for 0, então preenche linha e/ou coluna com 0;
            if(i == 0 || j==0)
            {

                pilhaCaixa2d[i][j] = 0;
                basePilha[i][j] = -1;
            }

            if(i == 1)
            {
                pilhaCaixa2d[i][j] = (int)floor(j/caixasRot[i-1].altura)*caixasRot[i-1].valorUtilidade;
                basePilha[i][j] = i-1;

            }

            if(i >1 && j == caixasRot[i-1].altura)
            {
                if (caixasRot[i-1].valorUtilidade >= pilhaCaixa2d[i-1][j])
                {
                    pilhaCaixa2d[i][j] = caixasRot[i-1].valorUtilidade;
                    basePilha[i][j] = i-1;
                }
                else
                {
                    pilhaCaixa2d[i][j] = pilhaCaixa2d[i-1][j];
                    basePilha[i][j] = basePilha[i-1][j];
                }

            }

            if(i > 1  && j>0 && caixasRot[i-1].altura > j )
            {
                pilhaCaixa2d[i][j] = pilhaCaixa2d[i-1][j];
                basePilha[i][j] = basePilha[i-1][j];
            }

            if(i > 1 && caixasRot[i-1].altura < j)
            {

                if(empilhavel(caixasRot[basePilha[i][j- caixasRot[i-1].altura]],caixasRot[i-1]) == 1 ||
                   empilhavel(caixasRot[i-1],caixasRot[basePilha[i][j- caixasRot[i-1].altura]]) == 1 &&
                pilhaCaixa2d[i][j- caixasRot[i-1].altura] + caixasRot[i-1].valorUtilidade > pilhaCaixa2d[i-1][j])
                {
                    if(caixasRot[i-1].valorUtilidade + pilhaCaixa2d[i][j-caixasRot[i-1].altura] > pilhaCaixa2d[i-1][j]){
                        pilhaCaixa2d[i][j] = caixasRot[i-1].valorUtilidade + pilhaCaixa2d[i][j-caixasRot[i-1].altura];
                        basePilha[i][j] = basePilha[i-1][j-caixasRot[i-1].altura];
                    }else{
                        pilhaCaixa2d[i][j] = pilhaCaixa2d[i-1][j];
                        basePilha[i][j] = basePilha[i-1][j];
                    }



                }
                else
                {
                    for(k =1; k<i-1; k++)
                    {
                        if(empilhavel(caixasRot[basePilha[k][j- caixasRot[i-1].altura]],caixasRot[i-1]) == 1 ||
                           empilhavel(caixasRot[i-1],caixasRot[basePilha[k][j- caixasRot[i-1].altura]]) == 1)
                        {
                            pilhaCaixa2d[i][j] = caixasRot[i-1].valorUtilidade + pilhaCaixa2d[k][j-caixasRot[i-1].altura];
                            basePilha[i][j] = basePilha[k][j-caixasRot[i-1].altura];
                        }
                    }

                    if(pilhaCaixa2d[i][j]<(int)floor(j/caixasRot[i-1].altura)*caixasRot[i-1].valorUtilidade)
                    {
                        pilhaCaixa2d[i][j] = (int)floor(j/caixasRot[i-1].altura)*caixasRot[i-1].valorUtilidade;
                        basePilha[i][j] = i-1;
                    }

                }
            }


            printf("%d,%d:%d ",i,j,pilhaCaixa2d[i][j]);
        }
        printf("\n");
    }

    k = 0;
    for(int i = 0; i<numCaixas; i++)
    {
        for(j = 0; j<hPilha; j++)
        {
            if(maior(pilhaCaixa2d[i][j],k) == pilhaCaixa2d[i][j])
            {
                k = pilhaCaixa2d[i][j];

            }
        }
    }
    printf("(Caixas, Sol. Otima) = (%d,%d)",(numCaixas - 1)/2, k);

    memo = (int *)malloc(hPilha * sizeof(int));
    for (i = 0; i<hPilha; i++)
        memo[i] = 0;



//    valorTotal = topDown(hPilha,numCaixas,memo,caixasRot);



    free(memo);
    free(basePilha);
    free(pilhaCaixa2d);
    free(mAdjacencia);
    fclose(arq);
    free(caixas);
    free(caixasRot);

return 0;
}
