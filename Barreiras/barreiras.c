// SINCRONIZACAO COM BARREIRAS
// Fernando Dotti
// Sistemas Operacionais e Modelos de Computação Concorrente
// Este programa mostra como barreiras podem ser construidas com semaforos
//
// cc -lpthread barreiras.c -o bar
// 


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>


// ----------------------------------------------------------------------------------
// ---------- DEFINICOES GENERICAS PARA BARREIRAS  ----------------------------------
// ----------------------------------------------------------------------------------


typedef struct {
    int n;                /* processos que chegaram na barreira */
    sem_t * mutex;          /* exclusao mutua na estrutura da barreira */
	sem_t * block;
} Barrier;


void initBarrier(Barrier * b, int max){	
	b->n = max;
    // sem_init(&(b->mutex), 0, 1);                 // em unix ou linux
    // sem_init(&(b->block), 0, 0);					// em unix ou linux
    b->mutex = sem_open("/b.mutex1",O_CREAT,0,1);    // isto é no macos
    b->block = sem_open("/b.block1",O_CREAT,0,0);    // isto é no macos
}

void destroyBarrier(Barrier * b){	                // destroi semaforos no macos
	    sem_unlink("/b.mutex1");                    
	    sem_unlink("/b.block1");                     
	    sem_close(b->mutex);                        
	    sem_close(b->block);
}


void chega(Barrier * b){
	sem_wait(b->mutex);
	b->n--;
	sem_post(b->mutex);
	
	if (b->n==0) { sem_post(b->block); }
	
	sem_wait(b->block);
	sem_post(b->block); 
}

// ----------------------------------------------------------------------------------
// --------- EXEMPLO DE USO DE BARREIRA ---------------------------------------------
// ----------------------------------------------------------------------------------

#define NP         3              /* numero de threads */
Barrier bGlobal;

void *usaBarreira() {              /* as threads executam isso */ 
	sleep(1);
	printf("antes da barreira \n");
	chega(&bGlobal);
	printf("trecho critico depois da barreira \n");	
}


int main() {
	pthread_t tidp1, tidp2,tidp3;

    initBarrier(&bGlobal, NP+1);    // threads mais main
		
    pthread_create(&tidp1, NULL, usaBarreira, NULL);
    pthread_create(&tidp2, NULL, usaBarreira, NULL);
    pthread_create(&tidp3, NULL, usaBarreira, NULL);

	chega(&bGlobal);                


    pthread_join(tidp1,NULL);
    pthread_join(tidp2,NULL);
    pthread_join(tidp3,NULL);

	printf("liberou \n");	

    destroyBarrier(&bGlobal);
	return (0);
}
