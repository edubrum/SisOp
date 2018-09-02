// PUCRS - Escola Politécnica - Sistemas Operacionais
// Prof. Dotti
//
// gcc forkRec.c -o fr
// execute com ./fr
//
// Baixe, compile, execute e explique detalhadamente a origem de cada linha de saída deste programa: 
// que processo fez cada printf e porque ?
//
	
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/wait.h>

void recFork(int n) {
	if (n>0) {
		n--;
		fork();   
		
		printf("PID %d - meu n: %d \n",getpid(),n);
		// antes da chamada recursiva, quantos processos foram criados ?
		
		recFork(n);
		
		printf("PID %d - PPID %d \n",getpid(),getppid());	
		// retorno da chamada recursiva: quantas vezes esta linha deveria ser escrita ?	
	}
	sleep(1);   
	// este sleep é só para que os pais ainda existam no getppid  
	// nao garante, mas funciona na maioria das vezes pois espera 1 segundo
}


void main()
{    
    recFork(2);	
}




// Exemplo de saida:
// macintosh-2:ProcessosPesadosConcorrentes fldotti$ ./fr
// PID 26765 - meu n: 1 
// PID 26765 - meu n: 0 
// PID 26766 - meu n: 1 
// PID 26767 - meu n: 0 
// PID 26766 - meu n: 0 
// PID 26768 - meu n: 0 
// PID 26768 - PPID 26766 
// PID 26766 - PPID 26765 
// PID 26767 - PPID 26765 
// PID 26765 - PPID 26754 
// PID 26767 - PPID 26765 
// PID 26768 - PPID 26766 
// PID 26766 - PPID 26765 
// PID 26765 - PPID 26754 


