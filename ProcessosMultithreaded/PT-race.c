/* pthreads - exemplo
 * Utilizado por Fernando Dotti em Sistemas Operacionais
 * Compile:
 * C compiler: ass (or cc -pthread PT-race.c -o ptr)  
 * or
 * C++ compiler: g++ -pthread PT-race.c -o ptr   (or g++ -lpthread  PT-race.c -o ptr))
*/

// 1) execute e entenda o significado de cada linha do programa
// 2) tente executar várias vezes e avaliar se a saída é a mesma, e se é a esperada
// 3) explique a razao destes resultados
// 4) descomente a operacao de join depois da criacao da primeira thread e comente uma linha de join ao final


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int global = 0 ;         // shared

void *accessToShared() 
 {
     int i;
     for(i=1;i<10001;i++) 
         global++;
 }


int main(void)
{
     pthread_t thread1, thread2;
     int  iret1, iret2;

     /* cria duas threads independentes.   ambas executam o mesmo codigo de funcao */
     iret1 = pthread_create( &thread1, NULL, accessToShared, NULL);
     if(iret1)
     {
         fprintf(stderr,"Error - pthread_create() return code: %d\n",iret1);
         exit(EXIT_FAILURE);
     }
	 
	 pthread_join( thread1, NULL);
    iret2 = pthread_create( &thread2, NULL, accessToShared, NULL);
     if(iret2)
     {
         fprintf(stderr,"Error - pthread_create() return code: %d\n",iret2);
         exit(EXIT_FAILURE);
     }

     /* Espera as threads completarem antes de continuar.
	    De outra forma corre-se o risco de executar exit antes 
	    de terminar as threads. */ 
   //  pthread_join( thread1, NULL);
     pthread_join( thread2, NULL); 
     printf("%i global\n", global);
     exit(EXIT_SUCCESS);
	return (0);
}

