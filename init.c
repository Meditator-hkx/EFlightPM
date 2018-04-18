/*************************************************************************
	> File Name: init.c
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

#include "init.h"

static char *shmaddr = NULL;

/* Get base address of initiated memory region
 * if NULL, then it is not initiated at all
 */ 
char *get_sys_base_addr() {
    int shmid = shmget(INIT_KEY, INIT_SIZE, IPC_CREAT | 0666);
    // printf("shmid: %d\n", shmid);
    shmaddr = (char *)shmat(shmid, NULL, 0);
    // printf("shmaddr: %p\n", shmaddr);
    return shmaddr;
}

/* Get base address of user data space
 * notice the first chunk (1KB) is reserved for metadata
 * PROBLEM: error occurs when I used the commented codes as follows. 
 */ 
char *get_user_base_addr() {
    // char *user_base_addr;
    // if (shmaddr == NULL) 
    //    user_base_addr = shmaddr + CHUNK_SIZE;
    // else 
    //    user_base_addr = get_sys_base_addr() + CHUNK_SIZE;
    char *user_base_addr = get_sys_base_addr() + CHUNK_SIZE;
    return user_base_addr;
}

void p_init() {
    shmaddr = get_sys_base_addr();
    struct_global_meta *global_meta = (struct_global_meta *)shmaddr;
    // init the metadata 
    global_meta->global_id = INIT_KEY;
    global_meta->total_size = INIT_SIZE;
    global_meta->free_size = INIT_SIZE - LOG_SIZE - CHUNK_SIZE;
    // how to initiate the active id list? write a tool function!
}

/*  malloc(volatile) --> p_malloc(non-volatile)
 *  double hashing mechanism: 
 *    1. outer hashing: ID --> chunk number
 *    2. inner hashing: ID --> start address
 *  maybe a hot-data cache can be maintained here 
 *  [ID, addr_off]
 *  [ID, addr_off]
 *       ...
 *  [ID, addr_off]
 */
char *p_malloc(int id, int size) {
    int flag = 0;
    int offset = OBJ_META_SIZE;
    char *ret_addr = NULL;
    char *user_base_addr = get_user_base_addr();
    int hash_chunk_num = outer_hash(id);
    char *chunk_addr = user_base_addr + hash_chunk_num * CHUNK_SIZE;
    struct_obj_meta *obj_meta = (struct_obj_meta *)(chunk_addr + offset);

    // init the global_meta if it is the first allocation
    struct_global_meta *global_meta = (struct_global_meta *)shmaddr;
    if (global_meta->global_id != INIT_KEY) 
        p_init();
    
    // do-while may be better here
    while (offset + size < CHUNK_SIZE) {
        // pass by the allocated part
        if (obj_meta->id != 0) {
            offset = offset + OBJ_META_SIZE + obj_meta->length;
            obj_meta = (struct_obj_meta *)(chunk_addr+offset);
        } else {
        // find first available part to user
            // write metadata for allocation
            obj_meta->id = id;
            obj_meta->length = size;
            ret_addr = chunk_addr + offset + OBJ_META_SIZE;
        // TODO: later the id-addr pair should be written to id-cache

            // write to the global_meta
            global_meta->free_size = global_meta->free_size - obj_meta->length - OBJ_META_SIZE; 
            break;
        }
    }
    if (ret_addr == NULL) {
        printf("Fail to allocate memory for object with ID %d.\n", id);
    }
    return ret_addr; 
}

char *p_get(int id) {
    /*
     * (1) find the base address
     * (2) hash the ID/name_str to specified object_start_addr
     */
    char *ret_addr = NULL;
    int hash_chunk_num = outer_hash(id);
    int offset = OBJ_META_SIZE;
    char *user_base_addr = get_user_base_addr();
    char *chunk_addr = user_base_addr + hash_chunk_num * CHUNK_SIZE;
    struct_obj_meta *obj_meta = (struct_obj_meta *)(chunk_addr + offset);

    while (offset < CHUNK_SIZE && obj_meta->id != id) {
        offset = offset + OBJ_META_SIZE + obj_meta->length;
        obj_meta = (struct_obj_meta *)(chunk_addr + offset);
    }
    if (obj_meta->id == id) {
        ret_addr = (char *)obj_meta + OBJ_META_SIZE;
    } else {
        printf("Object with ID %d is not found.\n", id);
    }
    return ret_addr;
}

int p_free(int id) {
    int ret = -1;
    int hash_chunk_num = outer_hash(id);
    int offset = OBJ_META_SIZE;
    char *user_base_addr = get_user_base_addr();
    char *chunk_addr = user_base_addr + hash_chunk_num * CHUNK_SIZE;
    struct_obj_meta *obj_meta = (struct_obj_meta *)(chunk_addr + offset);
    char *free_addr;
    struct_global_meta *global_meta = (struct_global_meta *)shmaddr;
    // bypass the unmatched item
    while (offset < CHUNK_SIZE && obj_meta->id != id) {
        offset = offset + OBJ_META_SIZE + obj_meta->length;
        obj_meta = (struct_obj_meta *)(chunk_addr + offset);
    }
    // if item found, clear the data in it
    if (obj_meta->id == id) {
        obj_meta->id = 0; // 0 represents free
        // obj_meta->length keeps unchanged
        free_addr = chunk_addr + offset + OBJ_META_SIZE; 
        memset(free_addr, 0, obj_meta->length);
        // write to the global_meta
        global_meta->free_size = global_meta->free_size + obj_meta->length + OBJ_META_SIZE; 
        ret = 0;
    }
    if (ret) {
        perror("Fail to free persistent region");
    }
    return ret;
}

int p_clear() {
    int ret = -1;
    char *sys_base_addr = get_sys_base_addr();
    memset(sys_base_addr, 0, INIT_SIZE);
    ret = shmdt(shmaddr);
    if (ret == -1) {
        perror("Fail to reset!\n");
    }
    return ret;
}

int outer_hash(int id) {
    int ret = id % CHUNK_NUM;
    return ret;
}
