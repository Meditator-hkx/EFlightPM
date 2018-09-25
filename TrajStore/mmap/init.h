/*************************************************************************
	> File Name: init.h
	> Author: Kaixn 
	> Mail: Kaixinhuang@sjtu.edu.cn
	> Created Time: 2018年04月17日 星期二 18时18分27秒
 ************************************************************************/

#ifndef _INIT_H
#define _INIT_H

#include<sys/ipc.h>
#include<sys/shm.h>
#include<unistd.h>
#include<string.h>
#include<stdio.h>
#include<error.h>
#include<sys/mman.h>
#include<stdlib.h>
#include<fcntl.h>

#define INIT_SIZE 200*1024*1024L // 200MB, allowed to configure
#define INIT_KEY 12345 // for shm_get
#define CHUNK_SIZE 50*1024*1024L // 50MB
#define LOG_SIZE 20*1024*1024L // 20MB, allowed to configure
#define CHUNK_NUM ((INIT_SIZE-LOG_SIZE)/CHUNK_SIZE-1) // The first chunk is reserved for system metadata
#define ID_CACHE_SIZE (sizeof(struct_d_cache));
#define OBJ_META_SIZE (sizeof(struct_obj_meta));
#define GLOBAL_META_SIZE (sizeof(struct_global_meta))
#define MAP_TARGET "/dev/pmem0m"

typedef struct {
    int global_id;
    int total_size;
    int free_size;
    int active_id_list[100];
    // To be added...
}struct_global_meta;

typedef struct {
    int id;
    char *addr;
}struct_id_cache;

typedef struct {
    int id;
    int length;
}struct_obj_meta;


char *get_sys_base_addr();
char *get_user_base_addr();
void  p_init();
char *p_malloc(int ID, int size);
char *p_get(int ID);
int   p_free(int ID);
int   p_clear();
int   outer_hash(int ID);

#endif
