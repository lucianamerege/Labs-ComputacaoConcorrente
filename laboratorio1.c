#include <stdio.h>
#include <pthread.h>

#define NTHREADS 2 //definindo uma constante que vai ser o numero de threads
#define TAM 10000
int posicao = 0;

void * tarefa (void * arg){
    int *valor = (int *) arg;

    posicao = posicao+1;

    for(int i=0; i<TAM/2; i++){
        if(posicao == 1){ //isso checa se é a primeira ou a segunda metade do vetor
            valor[i] = valor[i] * valor[i];
        }else if(posicao == 2){
            valor[i+(TAM/2)] = valor[i+(TAM/2)] * valor[i+(TAM/2)];
        }
    }

    pthread_exit(NULL); //retorno vazio
}

int main(void){
    pthread_t tid[NTHREADS]; //identificador da thread no sistema

    int elementos[TAM], temp;

    for(int i=0; i<TAM; i++){
        elementos[i] = i;
    }

    for(int i = 0; i < NTHREADS; i++){
        if (pthread_create(&tid[i], NULL, tarefa, (void *)elementos)){ 
            printf("Erro.");
        }
    }

    for(int i = 0; i < NTHREADS; i++){
        if (pthread_join(tid[i], NULL)){ 
            printf("Erro.");
        }
    } //esperar todas as threads terminarem antes de continuar a main

    for(int i=0; i<TAM; i++){ //estou checando se cada valor é igual ao valor inicial^2. Como os valores são iguais a sua posição no array, só criei essa variavel temporaria para guardar a posição do array ao quadrado e comparar com o valor naquela posição.
        temp = i*i;
        if(elementos[i]!=temp){
            printf("Elemento na posição %d está errado.", i);
        }
    }

    printf("\nFim.\n");
    return 0;
}