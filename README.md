# PAA
Disciplina Projeto e Análise de Algorítimos - Pós-Graduação UFOP 2018.1

Trabalho prático I - Programação Dinâmica

Considere que você tenha n tipos de caixas, cada tipo com valor Vi, e três dimensões: Largura, Altura e Profundidade. Considere o problema de construir uma pilha de altura máxima h, incluindo o maior valor possível de caixas, sendo que para cada tipo de caixa temos um número virtualmente ilimitado de caixas daquele tipo. Considere ainda, que as caixas podem ser rotacionadas de duas maneiras, e que  o empilhamento deve ser estável, ou seja, cada caixa deve ter sua largura menor ou igual à caixa de baixo e profundidade menor ou igual à caixa de baixo. As rotações R1 e R2 consistem em R1=(base = largura x profundidade, x altura) e 
R2=(base = profundidade x altura, x Largura).

Os dados de entrada devem ser lidos de um arquivo de texto no seguinte formato:

n (número de tipos caixas)
h (altura máxima da pilha de caixas)
V1 ( Valor de utilidade ao empilhar a caixa V1)
.
.
.
Vn (Valor de utilidade ao empilhar a caixa Vn)
L1 (largura da caixa 1)
A1 (altura da caixa 1)
P1 (profundidade da caixa 1)
.
.
.
Ln (largura da caixa n)
An (altura da caixa n)
Pn (profundidade da caixa n)

A saída deve ser escrita na forma de um arquivo de texto na forma:

m (número de tipos de caixas utilizadas)
caixa1 r1 (caixa 1, rotação da caixa 1)
...
caixam rm (caixa m, rotação da caiax m)
