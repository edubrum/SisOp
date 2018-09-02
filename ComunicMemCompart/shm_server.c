/*
 * shm-server - programa servidor
 * demonstra a criacao e compartilhamento de area de memoria
 *
 * EXEMPLO de:  https://users.cs.cf.ac.uk/Dave.Marshall/C/node27.html
 *
 * Utilizado para exemplificacao por Fernando Dotti em Sistemas Operacionais
 *
 */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

#define SHMSZ     27

main()
{
    char c;
    int shmid;
    key_t key;
    char *shm, *s;

    /*
     * Vamos chamar nosso segmento de memoria compartilhada de 
     * "5678".
     */
    key = 5678;

    /*
     * cria o segmento.
     */
    if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    /*
     * associa este segmento ao nosso espaço de dados - 'registra no PCB'.
     */
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    /*
     * Coloca valores na memoria para outro processo ler.
     */
    s = shm;

    for (c = 'a'; c <= 'z'; c++)
        *s++ = c;
    *s = NULL;

    /*
     * Espera ate que outro processo mude o primeiro caracter da nossa 
	 * memoria compartilhada para '*', depois acaba este servidor.
	 */
    while (*shm != '*')
        sleep(1);

    exit(0);
}