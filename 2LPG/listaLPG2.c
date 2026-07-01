#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Funções auxiliares
float* arrSort(float* array, int arr_size){ // The array and size parameters must be diffent
    for(int i=0; i<arr_size; i++){
        int min = i;
        for(int s=i+1; s<arr_size; s++){
            if(array[min]>array[s]){
                min = s;
                }
            }
        float temp = array[i];
        array[i] = array[min];
        array[min] = temp;
        }
    return array;
}

/* 1) Faça um programa que lê os três lados de um triângulo e determina o seu tipo, conforme
códigos a seguir. Os códigos devem ser retornados por uma função de tipo int, que recebe
os lados do triângulo como parâmetro. Protótipo da função:
int tipo_triangulo(float, x, float y, float z);
O retorno da função deve ser conforme os códigos a seguir:
0. Os lados não formam um triângulo (ou seja, a soma de dois deles é menor ou igual
ao outro lado);
1. Triângulo equilátero;
2. Triângulo isóceles;
3. Triângulo escaleno.
*/
int tipo_triangulo(float x, float y, float z){
    // printf("%d %d %d\n", x+y<=z, y+z<=x, x+z<=y);
    if((x+y<=z)||(y+z<=x)||(x+z<=y)){
        return 0;
    }
    else{
        if((x==y)&&(y==z)){
            return 1;
        }
        else if((x==y)||(y==z)||(x==z)){
            return 2;
        }
        else{
            return 3;
        }
    }
}
void triangleType(){
    int ans;
    float lados[3]; 
    for(int c=0; c<3; c++){
        scanf("%f", &lados[c]);
    }
    ans = tipo_triangulo(lados[0], lados[1], lados[2]);
    switch(ans){
        case 0: 
            printf("Nao forma triangulo.\n");
            break;
        case 1:
            printf("Triangulo equilatero.\n");
            break;
        case 2: 
            printf("Triangulo isosceles.\n");
            break;
        case 3:
            printf("Triangulo escaleno.\n");
            break;
    }
}

/* 2) Faça uma função que recebe três valores inteiros e retorna o maior valor. É preciso
considerar que podem haver dois (ou mesmo os três) parâmetros iguais como sendo o
maior valor. Por exemplo, os parâmetros poderiam ser 5, 8 e 8. Neste caso, a função deve
retornar 8.
*/

int maior_valor(int n1, int n2, int n3){
    if(n1>=n2&&n1>=n3){
        return n1;
    }
    else if(n2>=n1&&n2>=n3){
        return n2;
    }
    else if(n3>=n1&&n3>=n2){
        return n3;
    }
}
void biggestNum(){
    int num, nums[3];
    for(int c=0; c<3; c++){
        scanf("%d", &nums[c]);
    }
    num = maior_valor(nums[0], nums[1], nums[2]);
    printf("%d\n", num);
}

/* 3) Escreva um programa que informa se um caractere digitado pelo usuário representa um
dígito de 0 a 9. A verificação deve ser feita por uma função booleana (int) que recebe um
char como parâmetro. Caso o caractere seja um dígito, converta-o para um valor inteiro e
o armazene em uma variável int. Em seguida, mostre o valor inteiro na tela.
*/
int verif_inteiro(char carac){
    if((carac>='0')&&(carac<='9')){
        return 1;
    }
    else{
        return 0;
    }
}
void printInt(){
    char carac;
    scanf(" %c", &carac);
    int isInt = verif_inteiro(carac);
    if(isInt){
        int num = (int)carac;
        printf("%d\n", num);
    }
}
/* 4) Faça uma função que recebe 2 parâmetros, x e y, e calcule a soma dos números impares
entre eles (sem contar com eles mesmos). Repare que a função deve levar em conta de
que x pode ser maior do que y. Por exemplo, para x = 6 e y = -5, temos a seguinte soma
(em ordem crescente): -3 + (-1) + 1 + 3 + 5 = 5.
Outro exemplo: para x = 3 e y = 10 temos 5 + 7 + 9 = 21.
*/
int soma_impares(int x, int y){
    int fst, last, sum=0; 
    if(x<=y){
        fst = x;
        last = y;
    }
    else{
        fst = y;
        last = x;
    }
    for(int c=fst+1; c<last; c++){
        if(c%2!=0){
            sum += c;
        }
    }
    return sum;
}
void sumOdds(){
    int nums[2];
    for(int c=0; c<2; c++){
        scanf("%d", &nums[c]);
    }
    printf("%d\n", soma_impares(nums[0], nums[1]));
}

/* 5) Faça um programa que, dados k e n, mostre na tela os n primeiros números primos acima
de k. A verificação do número (se é ou não é primo) deve ser feita através de uma função.
*/
int eh_primo(int num){
    for(int c=2; c<=sqrt(num); c++){
        if(num%c==0){
            return 0;
        }
    }
    return 1;
}
void fstPrimes(){
    int k, terms, count, soma=0;
    scanf("%d", &k);
    scanf("%d", &terms);
    count = k+1;
    while(terms>0){
        count += 1;
        if(eh_primo(count)){
            printf("primo: %d\n", count);
            soma += count;
            terms -= 1;
        }
    }
    //printf("%d\n", soma);
}

/* 6) Faça um programa que mostre na tela os n primeiros termos da sequência de Fibonacci.
Por exemplo, dado n = 8, temos: 1, 1, 2, 3, 5, 8, 13 e 21. A determinação do n-ésimo termo
da sequência deve ser feita por uma função iterativa que tem o seguinte protótipo:
    int fibo(int n);
*/
int fibo(int size){
    int sum, nums[size]; nums[0]=1;
    for(int c=1; c<size; c++){
        sum += nums[c-1];
        nums[c] = sum;
    }
    return sum;
}

void fstFibon(){
    int qnt;
    scanf("%d", &qnt);
    printf("%d\n", fibo(qnt));
    //for(int c=1; c<=qnt; c++){

    //}
}

/* 7) Escreva uma função que calcula o somatório dos n termos que são múltiplos de k a partir
de x. Os parâmetros são determinados pelo usuário e a função é chamada pelo programa
principal, que em seguida mostra o resultado na tela. Exemplo:
para n = 3, k = 4 e x = 18, temos, 20 + 24 + 28 = 72. Protótipo da função:
    int soma_especial(int n, int k, int x);
*/
int soma_especial(int n, int k, int x){
    int sum, fst, count;
    while(n){
        if(fst<x){
            count++;
            fst *= k*count;
            sum = fst;
        }
        else{
            count++;
            sum += k*count;
            n--;
        }

    }
}
void specialSum(){
    int terms, num, fst;
    scanf("%d", &terms);
    scanf("%d", &num);
    scanf("%d", &fst);
    printf("%d\n", soma_especial(terms, num, fst));
}
/* 8) Faça um programa que leia um inteiro n e determine a soma S da seguinte forma:
1 + 2 + 3 + 4 + ... + n.
Escreva duas versões de funções: iterativa e recursiva.
*/

/* 9) Faça um programa que leia um inteiro n e utilize uma função (faça as versões iterativa e
recursiva) para determinar a soma S da série harmônica definida a seguir:

    S = 1 + 1/2 + 1/3 + 1/4 + ... + 1/n
*/

/* 10) Faça um programa que leia um inteiro n e utilize uma função (faça as versões iterativa e
recursiva) para calcular o somatório que determina o valor da constante e:

    S = 1/0! + 1/1! + 1/2! + 1/3! + 1/4! + ... + 1/n!
*/

void main(){
    printf("Escolha uma questao da lista: \
    \n1) Tipo de triangulo \
    \n2) Maior de Tres Valores \
    \n3) Verificacao 0 a 9 \
    \n4) Soma de Impares \
    \n5) N Primeiros Numeros Primos \
    \n6) N Primeiros Termos de Fibonacci \
    \n7) Soma Especial \
    \n8) Soma Simples \
    \n9) Serie Harmonica \
    \n10) Somatorio Numero de Euler \
    \n\n > ");
    int ans; scanf("%d", &ans);
    switch(ans){
        case 1: triangleType(); break;
        case 2: biggestNum(); break;
        case 3: printInt(); break;
        case 4: sumOdds(); break;
        case 5: fstPrimes(); break;
        case 6: fstFibon(); break;
        case 7: specialSum(); break;
        default: printf("Digite um índice correto! (entre 1 e 10)\n");
    }
}