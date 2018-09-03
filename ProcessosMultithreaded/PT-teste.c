//gcc -pthread PT-teste.c -o p
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
int n = 0, *d;
void *producting(void) {
	 int *a = malloc(10);
     for(int i=0;i<10;i++) 
         a[i]=n++;
     pthread_exit((void*)a); 
 }

void *consuming(){

}
int main(void){
     pthread_t thread1, thread2;
     int  iret1, iret2,*d,i;
     iret1 = pthread_create( &thread1, NULL, producting, NULL);
     iret2 = pthread_create( &thread2, NULL, consuming, NULL); 
     pthread_join( thread1, (void**)&d);
     pthread_join( thread2, (void**)&d); 
     printf(" n = %i \n", n);
	for( i=1;i<=10;i++)
		printf("d[%d] = %d\n ",i,d[i]);
     exit(EXIT_SUCCESS);
	free(d);
	return (0);
}

