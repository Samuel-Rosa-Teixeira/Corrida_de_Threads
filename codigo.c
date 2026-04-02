#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX 100

int num_threads;
int count = 0;

pthread_mutex_t lock;
pthread_cond_t cond;

int champ = -1;  //O campeão

void wall()
{
    pthread_mutex_lock(&lock);  //Entra na região crítica
    count++;
    if(count == num_threads)
        pthread_cond_broadcast(&cond); //acorda todo mundo pra largada

    else
    {
        //Se os threads não chegarem, todo mundo dorme
        while (count < num_threads)
        {
            pthread_cond_wait(&cond, &lock);
        }
    }

    pthread_mutex_unlock(&lock); //Saí da região crítica
}

void* run_cond(void* arg)
{
    int id = *(int*)arg; //As ids das threads
    wall();
    for(int i = 0; i < MAX; i++)
        printf("Thread %d: %d\n", id, i);

    //Que comecem os jogos \o/
    pthread_mutex_lock(&lock);

    if (champ == -1)
    {
        champ = id;
        printf("\n Thread %d venceu!\n", id);
    }

    pthread_mutex_unlock(&lock);
    count;
    return NULL;
}

int main(int argc, char* argv[]) {

    //Verifica se passaram as threads
    if (argc < 2)
    {
        printf("Uso: %s <num_threads>\n", argv[0]);
        return 1;
    }

    num_threads = atoi(argv[1]);
    pthread_t threads[num_threads];
    int ids[num_threads];

    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond, NULL);

    for (int i = 0; i < num_threads; i++)
    {
        ids[i] = i + 1;
        pthread_create(&threads[i], NULL, run_cond, &ids[i]);
    }

    //A Corrida
    for (int i = 0; i < num_threads; i++)
        pthread_join(threads[i], NULL);

    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);

    return 0;
}
