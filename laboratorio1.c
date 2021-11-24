#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NTHREADS 2 //definindo uma constante que vai ser o numero de threads
#define TAM 10000

//cria a estrutura de dados para armazenar os argumentos da thread
typedef struct {
   int *elementos, inicio;
} t_Args;

void * tarefa (void * arg){
    t_Args *valor = (t_Args *) arg;

    for(int i=0; i<TAM/2; i++){
        valor->elementos[i + valor->inicio] = (i + valor->inicio) * (i + valor->inicio);
    }

    pthread_exit(NULL); //retorno vazio
}

int main(void){
    pthread_t tid[NTHREADS]; //identificador da thread no sistema

    int elementos[TAM], temp;

    t_Args *arg;//receberá os argumentos para a thread

    for(int i=0; i<TAM; i++){
        elementos[i] = i;
    }

    for(int i = 0; i < NTHREADS; i++){
        arg = malloc(sizeof(t_Args));
        if (arg == NULL) {
            printf("--ERRO: malloc()\n"); exit(-1);
        }
        arg->elementos = elementos; 
        arg->inicio = i * TAM/2; 

        if (pthread_create(&tid[i], NULL, tarefa, (void *)arg)){ 
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
            printf("Elemento na posição %d está errado.\n", i);
        }
    }

    printf("Fim.\n");
    return 0;
}
