#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

//estrutura da caixa
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

//Algoritmo de ordenação por propriedade da caixa
void insertionSort(Caixa *V,int n)
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

//Função que verifica se duas caixas são empilháveis
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

//Função que retorna maior de dois valores


//Função que retorna menor de dois valores



int main(int argc, char *argv[])
{


    int **empilhar; //memoriza a última caixa empilhada
    int **m;//memoriza o melhor valor para uma dada altura máxima
    int **mAdjacencia; //matriz de adjacência para consulta de caixas empilháeis
    int hPilha;//altura máxima
    int numCaixas;//Número de caixas diferentes
    int valorTotal;//Armazena melhor valor de utilidade para uma dada altura máxima
    int solucOtima;//Solução ótima do problema completo
    Caixa *caixas;//Vetor que armazena caixas após leitura do arquivo
    Caixa *caixasRot;//Vetor que armazena caixas e suas respectivas rotações
    FILE *arq;
    char Linha[15];
    char *entrada;
    char *saida;

    char *result;
    int i,j,k;

    //entrada = argv[0];
    //saida = argv[1];
    //arq = fopen(entrada, "rt");
    clock_t end,start;

    start = clock();
    arq = fopen(argv[1], "rt");
    if (arq == NULL)
    {
        printf("Problemas na abertura do arquivo\n");
        return 0;
    }

    i = 1;
    j = 1;
    k = 0;
    while (!feof(arq))
    {
        result = fgets(Linha, 15, arq);
        if (result)


            if(i == 1)
            {
                numCaixas = atoi(result);
                printf("Numero de caixas %d: \n",numCaixas);
                caixas = (Caixa *)malloc(numCaixas * sizeof(Caixa));

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

            }

        if(i>numCaixas+2 && i <= numCaixas*3 + (numCaixas + 2))
        {
            if((i-(numCaixas+3))%3 == 0)
            {
                caixas[k].largura = atoi(result);

            }
            if((i-(numCaixas+3))%3==1)
            {
                caixas[k].altura = atoi(result);

            }
            if((i-(numCaixas+3))%3==2)
            {
                caixas[k].profundidade = atoi(result);
                caixas[k].areaBase = caixas[k].largura * caixas[k].profundidade;
                strcpy(caixas[k].rotacao,"R1");
                caixas[k].idCaixa = k+1;
                k++;
            }
        }
        i++;
    }//fim leitura do arquivo


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
            caixasRot[i].areaBase = caixasRot[i].profundidade * caixasRot[i].largura;
            k++;
        }
    }//Fim preenchimento caixas rotacionadas

    //Número de caixas duplicados
    numCaixas *=2;

    //Ordena caixas pela área da base
    insertionSort(caixasRot,numCaixas);

    //Conferência das caixas rotacionadas
//    for(i = 0; i<numCaixas; i++)
//    {
//        printf("CaixasRot[%d].idCaixa = %d\n",i,caixasRot[i].idCaixa);
//        printf("CaixasRot[%d].rotacao = %s\n",i,caixasRot[i].rotacao);
//        printf("CaixasRot[%d].valorUtilidade = %d\n",i,caixasRot[i].valorUtilidade);
//        printf("CaixasRot[%d].altura = %d\n",i,caixasRot[i].altura);
//        printf("CaixasRot[%d].largura = %d\n",i,caixasRot[i].largura);
//        printf("CaixasRot[%d].profundidade = %d\n",i,caixasRot[i].profundidade);
//        printf("CaixasRot[%d].areaBase = %d\n",i,caixasRot[i].areaBase);
//
//}

    //adicionar 1 no número de caixas e altura máxima da pilha de caixas, para anular o índice zero

    numCaixas +=1;
    hPilha +=1;

    //alocação de memória da matriz de adjacências
    mAdjacencia = (int **)malloc(numCaixas * sizeof (int *));
    for (j = 0; j < numCaixas; j++)
    {
        mAdjacencia[j] = (int *)malloc(numCaixas*sizeof(int));
    }

    //Preenchimento matriz de adjacências
    for(i = 0; i<numCaixas-1; i++)
    {

        for(j = 0; j <numCaixas-1; j++)
        {
            if(empilhavel(caixasRot[i],caixasRot[j])==1)
            {
                mAdjacencia[i][j] = 1;
            }
            else
            {
                mAdjacencia[i][j] = 0;
            }
        }
    }

//Alocação de memória da matriz de memoização, e memória de última caixa adicionada

    m = (int**)malloc(numCaixas * sizeof (int *));
    for (j = 0; j < numCaixas; j++)
    {
        m[j] = (int*)malloc(hPilha * sizeof(int));
    }

    empilhar = (int**)malloc(numCaixas * sizeof (int*));
    for (j = 0; j < numCaixas; j++)
    {
        empilhar[j] = (int*)malloc(hPilha * sizeof(int));
    }

    //Preenchendo matrizes de memoização e memorização da útima caixa empilhada.
    for(i = 0; i < numCaixas; i++)
    {
        for(j = 0; j < hPilha; j++)
        {
            if(i==0 || j==0)
            {
                m[i][j] = 0;
                empilhar[i][j] = 0;
            }
            if(i>=1)
            {
                if(i==1) //ok
                {
                    m[i][j] = (j/caixasRot[i-1].altura)*caixasRot[i-1].valorUtilidade;
                    if(j < caixasRot[i-1].altura){
                        empilhar[i][j] = 0;
                    }else{
                        empilhar[i][j] = i;
                    }
                }
                else
                {
                    if(j < caixasRot[i-1].altura)
                    {
                        m[i][j] = m[i-1][j];
                        empilhar[i][j] = empilhar[i-1][j];
                    }

                    if(j == caixasRot[i-1].altura)
                    {
                        if(caixasRot[i-1].valorUtilidade > m[i-1][j])
                        {
                            m[i][j] = caixasRot[i-1].valorUtilidade;
                            empilhar[i][j] = i;
                        }
                        else
                        {
                            m[i][j] = m[i-1][j];
                            empilhar[i][j] = empilhar[i-1][j];

                        }
                    }
                    if(j > caixasRot[i-1].altura)
                    {
                        if(m[i][j-caixasRot[i-1].altura] + caixasRot[i-1].valorUtilidade <= m[i-1][j])
                        {
                            m[i][j] = m[i-1][j];
                            empilhar[i][j] = empilhar[i-1][j];
                        }

                         if(m[i][j-caixasRot[i-1].altura] + caixasRot[i-1].valorUtilidade > m[i-1][j])
                        {
                            if(mAdjacencia[i-1][(empilhar[i][j-caixasRot[i-1].altura])-1] == 1)
                            {
                                m[i][j] = m[i][j-caixasRot[i-1].altura] + caixasRot[i-1].valorUtilidade;
                                empilhar[i][j] = i;
                            }
                            else
                            {
                                for(k = 1; k<i-1; k++)
                                {
                                    if(mAdjacencia[i-1][(empilhar[k][j-caixasRot[i-1].altura])-1] == 1)
                                    {
                                        m[i][j] = m[k][j-caixasRot[i-1].altura] + caixasRot[i-1].valorUtilidade;
                                        empilhar[i][j] = i;
                                    }

                                }
                            }
                        }
                        if(m[i][j]<m[i][j-1]){
                            m[i][j] = m[i][j-1];
                                empilhar[i][j] = empilhar[i][j-1];
                        }
                    }
                }
            }

            //printf("%d,%d:%d ",i,j,m[i][j]);
        }
//  printf("\n");
    }



    printf("Soluc. Otima (%d,%d)\n",numCaixas/2,m[numCaixas-1][hPilha-1]);
    solucOtima = m[numCaixas-1][hPilha-1];
    int *solucao = (int*) malloc (hPilha*sizeof(int));
    for(i=0;i<hPilha;i++){
        solucao[i] = -1;
    }
    int n = numCaixas-1;
    int h = hPilha-1;

    int maxC;
    j=0;
    while(n>0 && h>0){
        int cx = n;
        for(int i=n; i>=1; i--){
            if(m[i][h]==m[i-1][h])
                cx = i-1;
            else
                break;
        }
        if(cx>0)
            solucao[j]=cx-1;
        j++;
        maxC =j;
        h=h-caixasRot[cx-1].altura;
        n=cx;
    }

    printf("Num caixas empilhadas: %d\n",maxC);
    for(i =0; i<=hPilha-2;i++){
        if(solucao[i]!=-1){
           // printf("%d %s\n",caixasRot[solucao[i]].idCaixa,caixasRot[solucao[i]].rotacao);
        }
    }
//FILE *sol = fopen(saida, "w");
    FILE *sol = fopen(argv[2], "w");
    if(!sol)
    {
        fprintf(stderr,"Erro: nao foi possivel abrir o arquivo de sols.\n");
        exit(EXIT_FAILURE);
    }

    fprintf(sol, "%d",solucOtima);
    fprintf(sol, "\n");
    fprintf(sol, "%d",maxC);
    fprintf(sol, "\n");
    for(i = hPilha-2; i>=0;i--){
        if (solucao[i]!=-1){
        fprintf(sol, "%d ", caixasRot[solucao[i]].idCaixa );
        fprintf(sol, "%s ", caixasRot[solucao[i]].rotacao );
        fprintf(sol, "\n");
        }

    }
    fclose(sol);




    free(m[0]);
    free(m);
    free(empilhar[0]);
    free(empilhar);
    free(caixas);
    free(caixasRot);

end = clock();
printf("Tempo gasto: %3.0f ms\n\n",1000*(double)(end-start)/(double)(CLOCKS_PER_SEC));

    return 0;
}
