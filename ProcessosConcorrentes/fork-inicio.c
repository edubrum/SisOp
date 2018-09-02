// #include <thread.h>
#include <unistd.h>

// primeiro programa com fork
// gcc fork-inicio.c -o frk
// executar  ./frk
// interprete o resultado


main()
{

int pid, pid2, pid3;


    printf("Antes do Fork - meu identificador de processo eh : %d\n", getpid());

    pid = fork();  // processo filho ee copia identica do pai unica diferenca
	               // ee o valor de retorno: para o pai, pid ee id do filho, para filho ee 0

    printf("Depois do Fork - meu identificador de processo eh : %d\n", getpid());

    if (pid!=0) 
		  { printf("Eu sou o pai, meu pid eh: %d\n", getpid()) ; 
            printf("Aqui deve ir o codigo soo do pai \n"); 
		    pid2 = wait(0);
            printf("Esperei o filho morrer.  Pid do filho:  %d\n", pid2); 
		    }
    else  
		  { printf("Eu sou o filho, meu pid eh: %d\n", getpid()) ; 
            printf("Aqui deve ir o codigo soo do filho \n"); 
		    pid3 = wait(0);
            printf("Nao tenho filho, wait retorna -1 imediatamete:  %d\n", pid3); 
		}
	
	printf("os dois executam isso \n");
		
	
}


