/* Contador de palavras
 *
 * Este programa recebera uma serie de caracteres representando palavras em sua
 * entrada. Ao receber um caractere fim de linha ('\n'), deve imprimir na tela o
 * numero de palavras separadas que recebeu e, apos, encerrar.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <unistd.h>

int verificaPrimo(int numero){
    if (numero == 1 || numero == 0){
        return 0;
    }
    for (int i = 2; i < numero; i++){
        if (!(numero%i)){
            return 0;
        }
    }
    return 1;
}

int main() {
    int n;
    int count = 0;
    int* vetorNum = malloc(100*sizeof(int));

    int protection = PROT_READ | PROT_WRITE;
    int visibility = MAP_SHARED | MAP_ANON;

    /* Criar area de memoria compartilhada */
    int* vetorZ = (int *)mmap(NULL, sizeof(int) * 100, protection, visibility, 0, 0);

    while (scanf("%d", &n) != EOF){
        vetorNum[count] = n;
        vetorZ[count] = 0;
        count++;
    }

    pid_t p1, p2, p3, p4;
    p1 = fork();
    if (p1 == 0){
        for (int i = 0; i < count; i++){
            if (vetorZ[i] == 0){
                vetorZ[i] = 1;
                if (verificaPrimo(vetorNum[i])){
                    vetorZ[i] = 2; //quer dizer que é primo
                }
            }
        }
        exit(0);
    }
    p2 = fork();
    if (p2 == 0){
        for (int i = 0; i < count; i++)
        {
            if (vetorZ[i] == 0)
            {
                vetorZ[i] = 1;
                if (verificaPrimo(vetorNum[i]))
                {
                    vetorZ[i] = 2; //quer dizer que é primo
                }
            }
        }
        exit(0);
    }
    p3 = fork();
    if (p3 == 0){
        for (int i = 0; i < count; i++)
        {
            if (vetorZ[i] == 0)
            {
                vetorZ[i] = 1;
                if (verificaPrimo(vetorNum[i]))
                {
                    vetorZ[i] = 2; //quer dizer que é primo
                }
            }
        }
        exit(0);
    }
    p4 = fork();
    if (p4 == 0){
        for (int i = 0; i < count; i++)
        {
            if (vetorZ[i] == 0)
            {
                vetorZ[i] = 1;
                if (verificaPrimo(vetorNum[i]))
                {
                    vetorZ[i] = 2; //quer dizer que é primo
                }
            }
        }
        exit(0);
    }
    waitpid(p1, NULL, 0);
    waitpid(p2, NULL, 0);
    waitpid(p3, NULL, 0);
    waitpid(p4, NULL, 0);

    int primos = 0;

    for (int i = 0; i < count; i++){
        if (vetorZ[i] == 2){
            primos++;
        }
    }

    printf("%d\n", primos);
    return 0;
}
