Trabalho do segundo grau da matéria Software Básico.

O trabalho consiste em desenvolver um compilador de uma linguagem básica chamada LinB.

-A Linguagem Básica:
Funções na linguagem LinB contém atribuições, operações aritméticas, instruções de desvio e de retorno.

Uma atribuição tem a forma:
 varp '<=' expr 
onde varp é uma variável local ou um parâmetro e expr é uma operação aritmética.

Uma operação aritmética tem a forma:
 varpc op varpc 
onde varpc é uma variável local, um parâmetro ou uma constante inteira e op é um dos operadores: + - *.

A instrução de desvio tem a forma:
 'if' varp num 
onde varp é uma variável local ou um parâmetro e num é o número da linha no código fonte para a qual o controle deve ser desviado caso o valor de varp seja diferente de zero.

Finalmente, a instrução de retorno tem a forma:
 'ret' 
Neste caso, a função deverá retornar, e seu valor de retorno é o valor da variável local v1.


Na linguagem LinB, as variáveis locais são da forma vi, sendo o índice i utilizado para identificar a variável (ex. v1, v2, etc...). A linguagem permite o uso de no máximo 4 variáveis locais. 
Da mesma forma, os parâmetros são denotados por pi, e podem ser usados no máximo 2 parâmetros (p1 e p2).
Constantes são escritas na forma $i, onde i é um valor inteiro, com um sinal opcional. Por exemplo, $10 representa o valor 10 e $-10 representa o valor -10.


-Alguns Exemplos:
Veja a seguir alguns exemplos de funções LinB.
Note que os comentários não fazem parte da linguagem! Eles estão incluidos nos exemplos abaixo apenas para facilitar seu entendimento.

O exemplo abaixo implementa uma função f(x) = x + 1:
v1 <= p1 + $1          // 1: i = x + 1
ret                   // 2: retorna i

O próximo exemplo implementa uma função f(x,y) = (x+y) * (x-y):
v1 <= p1 + p2          // 1: i = x + y
p1 <= p1 - p2          // 2: x = x - y
v1 <= v1 * p1          // 3: i = i * x
ret                   // 4: retorna i

O próximo exemplo é uma função fatorial fat(n):
v1 <= $0 + $1          // 1: f = 1
if p1 4               // 2: if (n != 0) desvia para linha 4
ret                   // 3: retorna f
v1 <= v1 * p1          // 4: f = f * n
p1 <= p1 - $1          // 5: n = n - 1
if p1 4               // 6: if (n != 0) desvia para linha 4
ret                   // 7: retorna f

Finalmente, uma função squad(x) que calcula a soma dos quadrados de 1 a x:
v1 <= $0 + $0          // 1: sum = 0
v2 <= $1 + $0          // 2: i = 1
p1 <= p1 + $1          // 3: x = x + 1
v3 <= p1 - v2          // 4: aux = x - i  (será zero se x == i)
if v3 7               // 5: if (aux != 0) desvia para linha 7
ret                   // 6: retorna sum
v3 <= v2 * v2          // 7: aux = i * i
v1 <= v1 + v3          // 8: sum = sum + aux
v2 <= v2 + $1          // 9: i = i + 1
if v2 4               // 10: if (i != 0) desvia para linha 4 (sempre desviará)
