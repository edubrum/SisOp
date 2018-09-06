// pthreads - exemplo (toda parte principal achada na internet)
// Utilizado por Fernando Dotti em Sistemas Operacionais
// Filename: peterson_spinlock.c
// Use below command to compile:
// gcc -pthread -D_REENTRANT peterson_spinlock.c -o peterson_spinlock   ??
//  cc -pthread peterson_spinlock.c -o petNaive
 
#include <stdio.h>
#include <pthread.h>


// -----------------------------------------------------------------------------------------------
// ------- variaveis e procedimentos do algoritmo de peterson para exclusao mutua por duas threads
// -----------------------------------------------------------------------------------------------  
  
int flag[2];                // variaveis do algoritmo de peterson
int turn;

void lock_init()
{	
    flag[0] = flag[1] = 0;  // inicia lock resetando o desejo de ambas threads de adquirirem o lock.
    turn = 0;               // daa a vez a uma delas
}
 
void lock(int self)         // executado antes da secao critica
{
    flag[self] = 1;         // flag[self] = 1 diz que quer o lock
    turn = 1-self;          // mas antes daa aa outra trhead a chance de adquirir o lock 
    while (flag[1-self]==1 &&   // espera ate que outra thread nao queira mais o lock
  turn==1-self) ;      // ou seja a vez desta thread pegar o lock	
}
 
void unlock(int self)       // executado depois da secao critica
{
    flag[self] = 0;         // voce nao quer obter o lock, isso permite aa outra thread obter
}
 
 
// -----------------------------------------------------------------------------------------------
// ------- exemplo de uso do algoritmo de peterson em duas threads
// -----------------------------------------------------------------------------------------------  
   
 
const int MAX = 1000000;
int global = 0;                // a variavel compartilhada!!   a ser protegida
 
void *accessToShared(void *s)         // uma funcao simples executada em duas threads criadas no main
{
    int i = 0;
    int self = (int *)s;
    printf("Thread entrou: %d\n", self);    // diz qual o identificador desta thread:   0 ou 1
 
	for (i=0; i<MAX; i++) {        // entra e sai MAX vezes na SC
		lock(self);                // CODIGO DE ENTRADA NA SC	
		global++;                     // SECAO CRITICA 		
		unlock(self);              // CODIGO DE SAIDA DA SECAO CRITICA		
	} 	
}
 

int main()
{
    // inicia as variaves de peterson
    pthread_t p1, p2;
    lock_init();
 
    // cria as duas threads
    pthread_create(&p1, NULL, accessToShared, (void*)0);
    pthread_create(&p2, NULL, accessToShared, (void*)1);
 
    // espera seus fins
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
 
    printf("Valor do contador: %d | Valor esperado: %d\n", global, MAX*2);
    return 0;
}
