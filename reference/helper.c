/*************************************************************************
	> File Name: ioremaptest.c
	> Author: Kaixn 
	> Mail: Kaixinhuang@sjtu.edu.cn
	> Created Time: 2018年04月17日 星期二 16时19分29秒
 ************************************************************************/

/* Notes:
 * A user-mode memory managment system is aimed at persistent memory
 * (App Direct Mode on AEP)
 * The procedure includes several key points:
 * 1. Allocate a fixed (&persistent) address from system memory address;
 * % mmap? ioremap? shget %
 * 2. Develop easy-to-use interfaces for persistent memory allocation and recycling;
 * % p_malloc? p_free? transaction? %
 * 3. Manage allocated memory region in an efficient method
 * % linear? tree-structure? buddy allocator? %
 * 4. To be added...
 */

#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<error.h>
#include<unistd.h>
#include<string.h>

#define INIT_SIZE (1024*1024*1024)
#define CHUNK_SIZE (200*1024*1024)
#define CHUNK_NUM (INIT_SIZE / CHUNK_SIZE)
#define KEY 12345

int main(int argc, char **argv) {
    int shmid;
    char *shmaddr;
    int flag = 0;
    int pid;

    // test mod function
    printf("INIT_SIZE %lu, CHUNK_SIZE %d, CHUNK_NUM %d\n", INIT_SIZE, CHUNK_SIZE, CHUNK_NUM);
    // write to shmaddr
    if (argc == 2 && argv[1][0] == 'w') {
        shmid = shmget(KEY, INIT_SIZE, IPC_CREAT | 0666);
        // printf("shmid: %d\n", shmid);
        shmaddr = (char *)shmat(shmid, NULL, 0);
        // printf("shmaddr: %p\n", shmaddr);
        int *a_test = (int *)shmaddr;
        *a_test = 100;
        printf("write value %d to shmaddr\n", *(int *)shmaddr);
        if (shmdt(shmaddr) == -1) {
            perror("disconnet error!\n");
        }
    }

    // read from shmaddr
    else if (argc == 2 && argv[1][0] == 'r') {
        shmid = shmget(KEY, INIT_SIZE, IPC_CREAT | 0666);
        // printf("shmid: %d\n", shmid);
        shmaddr = (char *)shmat(shmid, NULL, 0);
        // printf("shmaddr: %p\n", shmaddr);
        printf("get value %d from shmaddr\n", *(int *)shmaddr);
        if (shmdt(shmaddr) == -1) {
            perror("disconnet error!\n");
        }
    }

    else {
        printf("Error, please input the parameter.\n");
    }
   
    return 0;
}
