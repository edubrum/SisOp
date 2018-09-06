 /* 1a) Você tem uma matriz de dimensões [x,y] carregada de valores.
          Lance, para cada linha l: 0..x, uma thread que computa o somatório dos valores de indice 0 a y-1 
          e armazena o resultado na posição y da linha.
          As threads todas devem acabar o somatório e entao a main soma todas as posicoes y das x linhas
          gerando assim o somatório total.
          A sincronizacao entre as threads e a main acontece com barreiras.*/
#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
struct Barrier{
	int n;                /* processos que chegaram na barreira */
	sem_t * mutex;          /* exclusao mutua na estrutura da barreira */
	sem_t * block;
};
void initBarrier(Barrier * b, int max){	
	b->n = max;
	sem_init(&(b->mutex), 0, 1);     // em unix ou linux
	sem_init(&(b->block), 0, 0);	// em unix ou linux
	//b->mutex = sem_open("/b.mutex1",O_CREAT,0,1);    // isto é no macos
	//b->block = sem_open("/b.block1",O_CREAT,0,0);    // isto é no macos
}
//void destroyBarrier(Barrier * b){// destroi semaforos no macos
//	sem_unlink("/b.mutex1");                    
//	sem_unlink("/b.block1");                     
//	sem_close(b->mutex);                        
//	sem_close(b->block);
//}
//void chega(Barrier * b){
//	sem_wait(b->mutex);
//	b->n--;
//	sem_post(b->mutex);
//	if (b->n==0) { sem_post(b->block); }
//	sem_wait(b->block);
//	sem_post(b->block); 
//}
struct arguments{
	int somatorio[4];
	int a_matrix[4][5];
	int l,c;
};
void *somando(void *parametros){
	struct arguments *arg = parametros;
	for (int j=0;j<5;j++)
		arg->somatorio[arg->l]=arg->somatorio[arg->l] + arg->a_matrix[arg->l][j];
	pthread_exit(NULL);
}

struct Barrier bGlobal;
int main(void){
	pthread_t td[4]; 
	int matrix[4][5],i,j,result=0;
	struct arguments arg;
	//initBarrier(&bGlobal, 4+1);    // 4 threads mais main
	for(i=0;i<4;i++){
		for(j=0;j<5;j++){
			arg.a_matrix[i][j]=matrix[i][j] = rand() % 20;
			printf("%d\t\t",matrix[i][j]);
		}
		printf("\n");
	}
	for(i=0;i<4;i++){
		arg.l=i;
		arg.somatorio[i]=0;
		pthread_create(&td[i],0,somando,(void *)&arg);
	}
	//chega(&bGlobal);
	for(i=0;i<4;i++)
		if(pthread_join(td[i],NULL))
			result = arg.somatorio[i] + result;
	printf("O resultado é: %d\n",result);
	// destroyBarrier(&bGlobal);
	return (0);
}
