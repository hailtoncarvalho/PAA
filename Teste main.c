#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <math.h>

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
int maior(int a, int b)
{
    if(a > b)
        return a;
    else
        return b;
}

//Função que retorna menor de dois valores
int menor(int a, int b)
{
    if(a < b)
        return a;
    else
        return b;
}


//MAIN
int main()
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
    char *result;
    int i,j,k;

    // Abre um arquivo TEXTO para LEITURA
    arq = fopen("s50.data", "rt");

    if (arq == NULL)  // Se houve erro na abertura
    {
        printf("Problemas na abertura do arquivo\n");
        return 0;
    }

    i = 1;
    j = 1;
    k = 0;
    while (!feof(arq))
    {
        // Lê uma linha (inclusive com o '\n')
        result = fgets(Linha, 15, arq);  // o 'fgets' lê até 99 caracteres ou até o '\n'
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
    for(i = 0; i<numCaixas; i++)
    {
        printf("CaixasRot[%d].idCaixa = %d\n",i,caixasRot[i].idCaixa);
        printf("CaixasRot[%d].rotacao = %s\n",i,caixasRot[i].rotacao);
        printf("CaixasRot[%d].valorUtilidade = %d\n",i,caixasRot[i].valorUtilidade);
        printf("CaixasRot[%d].altura = %d\n",i,caixasRot[i].altura);
        printf("CaixasRot[%d].largura = %d\n",i,caixasRot[i].largura);
        printf("CaixasRot[%d].profundidade = %d\n",i,caixasRot[i].profundidade);
        printf("CaixasRot[%d].areaBase = %d\n",i,caixasRot[i].areaBase);

}

    //adicionar 1 no número de caixas e altura máxima da pilha de caixas, para anular o índice zero

    numCaixas +=1;
    hPilha +=1;

    //alocação de memória da matriz de adjacências
    mAdjacencia = (int *)malloc(numCaixas * sizeof (int));
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
            //printf("(%d,%d):%d",i,j,mAdjacencia[i][j]);
        }
        //printf("\n");
    }

//Alocação de memória da matriz de memoização, e memória de última caixa adicionada

    m = (int*)malloc(numCaixas * sizeof (int));
    for (j = 0; j < numCaixas; j++)
    {
        m[j] = (int*)malloc(hPilha * sizeof(int));
    }

    empilhar = (int*)malloc(numCaixas * sizeof (int));
    for (j = 0; j < numCaixas; j++)
    {
        empilhar[j] = (int*)malloc(hPilha * sizeof(int));
    }


    m = (int*)malloc(numCaixas * sizeof (int));
    for (j = 0; j < numCaixas; j++)
    {
        m[j] = (int*)malloc(hPilha * sizeof(int));
    }

    empilhar = (int*)malloc(numCaixas * sizeof (int));
    for (j = 0; j < numCaixas; j++)
    {
        empilhar[j] = (int*)malloc(hPilha * sizeof(int));
    }

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
                    m[i][j] = floor(j/caixasRot[i-1].altura)*caixasRot[i-1].valorUtilidade;
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
                    }//ok
                    if(j > caixasRot[i-1].altura)
                    {
                        if(m[i][j-caixasRot[i-1].altura] + caixasRot[i-1].valorUtilidade <= m[i-1][j]) // < testar
                        {
                            m[i][j] = m[i-1][j];
                            empilhar[i][j] = empilhar[i-1][j];
                        }

                         if(m[i][j-caixasRot[i-1].altura] + caixasRot[i-1].valorUtilidade > m[i-1][j])
                        {
                            if(mAdjacencia[i-1][(empilhar[i][j-caixasRot[i-1].altura])-1] == 1)
                            {
                                //ISSO NÃO FAZ NENHUM SENTIDO
                                m[i][j] = m[i][j-caixasRot[i-1].altura] + caixasRot[i-1].valorUtilidade; // = 3, J =6
                                empilhar[i][j] = i;
                               // printf("-> ",j-caixasRot[i-1].altura); //Verificar o que está acontecendo aqui
                            }
                            else
                            {
                                for(k = 1; k<i-1; k++)
                                {
                                    if(mAdjacencia[i-1][empilhar[k][j-caixasRot[i-1].altura]] == 1)
                                    {
                                        m[i][j] = m[k][j-caixasRot[i-1].altura] + caixasRot[i-1].valorUtilidade;
                                        empilhar[i][j] = i;
                                    }

                                }
                            }
                        }

                    }
                }
            }
            printf("%d,%d:%d ",i,j,m[i][j]);
        }
        printf("\n");
    }

    solucOtima = m[0][0];
    for(i=0;i<numCaixas;i++){
        for(j=0;j<hPilha;j++){
            if(m[i][j]>solucOtima){
                solucOtima = m[i][j];
            }
        }
    }

    printf("Soluc. Otima (%d,%d)",numCaixas/2,solucOtima);
    return 0;

    free(m[0]);
    free(m);
    free(empilhar[0]);
    free(empilhar);
    free(caixas);
    free(caixasRot);

}
