#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX 100

int num_threads;
int contador = 0;

pthread_mutex_t lock;
pthread_cond_t cond;

int camp = -1;  //O campeão

void barreira()
{
    pthread_mutex_lock(&lock);  //Entra na região crítica
    contador++;
    if(contador == num_threads) //Prepara o tiro
    {
        pthread_cond_broadcast(&cond); //Atira e acorda todo mundo pra largada
    }
    else
    {
        //Se os threads não chegarem, todo mundo dorme
        while (contador < num_threads)
        {
            pthread_cond_wait(&cond, &lock);
        }
    }
    pthread_mutex_unlock(&lock); //Saí da região crítica
}


int main()
{
    return 0;
}