/*************************************************************************
	> File Name: test.c
	> Author: Kaixn 
	> Mail: Kaixinhuang@sjtu.edu.cn
	> Created Time: 2018年04月17日 星期二 18时25分45秒
 ************************************************************************/
 /**
  * This program is used for data persistence test: we first malloc a memory region for an object with specified ID 
  * and then recover the object after next boot of system/program
  * Two object structures are tested in our program
  * Better compare it to the previous work called PMDK (pmemobj pmalloc)
  *
  **
  * How to Test:
  * ./ptest   (Declare the beginning or ending of this test)
  * ./ptest m (Malloc memory for two specified objects: struct_stu(ID=100) and integer(ID=200))
  * ./ptest g (Recover the persisted data object by corresponding IDs)
  * ./ptest f (Free the allocated memory space by IDs)
  * ./ptest c (Reset the whole heap space for other use)
  */

#include <stdio.h>
#include "init.h"

typedef struct {
    int age;
    char *name;
} struct_stu;

static struct_global_meta *global_meta;

int main(int argc, char **argv) {
    int ret;
    int id = 100;
    int iid = 200;

    // global meta info
    global_meta = (struct_global_meta *)get_sys_base_addr();

    if (argc == 2 && argv[1][0] == 'm') {
        printf("\n1. p_malloc test. If successful, return allocated memory address for each data element, else return failed info.\n");
        // init to guarantee purity of this run
        p_clear();
        // allocate memory space for struct_stu
        id = 100;
        struct_stu *obj_stu = (struct_stu *)p_malloc(id,sizeof(struct_stu));
        if (obj_stu == NULL) {
            printf("Allocation failed.\n");
            return;
	}
	obj_stu->age = 18;
        obj_stu->name = "kaixin";
        iid = 200;
        int *obj_int = (int *)p_malloc(iid, sizeof(int));
        *obj_int = 1234;

        // print sum info
        printf("------------------------------Info Sum-------------------------------------------\n");
        printf("heap total size : %-10d;  free size: %-10d\n", global_meta->total_size, global_meta->free_size);
        printf("obj_stu address : %-10p; obj_stu id: %-10d\n", obj_stu, *((int *)obj_stu-2));
        printf("obj_int address : %-10p; obj_int id: %-10d\n", obj_int, *((int *)obj_int-2)); 
        printf("obj_stu metadata: | id    = %-10d | length = %-10d\n", *((int *)obj_stu-2), *((int *)obj_stu-1));
        printf("obj_int metadata: | id    = %-10d | length = %-10d\n", *((int *)obj_int-2), *((int *)obj_int-1));
        printf("obj_stu         : | name  = %-10s | age    = %-10d\n", obj_stu->name, obj_stu->age);
        printf("obj_int         : | value = %-10d\n", *obj_int);
        printf("---------------------------------------------------------------------------------\n\n");
    } else if (argc == 2 && argv[1][0] == 'g') {
        printf("\n2. p_get test. If successful, return persisted object corresponding to each id, else return failed info.\n");
        // get the persistent object
        struct_stu *obj_stu = (struct_stu *)p_get(id);
        int *obj_int = (int *)p_get(iid);

        // print sum info
        printf("------------------------------Info Sum-------------------------------------------\n");
        printf("heap total size : %-10d;  free size: %-10d\n", global_meta->total_size, global_meta->free_size);
        printf("obj_stu address : %-10p; obj_stu id: %-10d\n", obj_stu, *((int *)obj_stu-2));
        printf("obj_int address : %-10p; obj_int id: %-10d\n", obj_int, *((int *)obj_int-2)); 
        printf("obj_stu metadata: | id    = %-10d | length = %-10d\n", *((int *)obj_stu-2), *((int *)obj_stu-1));
        printf("obj_int metadata: | id    = %-10d | length = %-10d\n", *((int *)obj_int-2), *((int *)obj_int-1));
        printf("obj_stu         : | name  = %-10s | age    = %-10d\n", obj_stu->name, obj_stu->age);
        printf("obj_int         : | value = %-10d\n", *obj_int);
        printf("---------------------------------------------------------------------------------\n\n");
        // printf("student   id: %d\n", stu_get->age);
        // printf("student name: %s\n", stu_get->name);
    } else if (argc == 2 && argv[1][0] == 'f') {
        printf("\n3. p_free test. If successful, free the memory of corresponding id, else return failed info.\n");
        // free the allocated memory region
        ret = p_free(id); // id = 100
        if (ret == 0) {
            printf("Success in freeing specified memory.\n");
        } 
        // print sum info
        printf("------------------------------Info Sum-------------------------------------------\n");
        printf("heap total size : %-10d;  free size: %-10d\n", global_meta->total_size, global_meta->free_size);
        printf("---------------------------------------------------------------------------------\n\n");
    } else if (argc == 2 && argv[1][0] == 'c') {
        printf("\n4. p_clear test. If successful, return success info, else return failed info.\n");
        // reset the whole initiated space
        ret = p_clear();
        if (ret == 0) {
            printf("Success in reseting the whole user heap.\n");
        }  
    } else {
        // print sum info
        printf("Test begins / ends!\n");
        printf("------------------------------Info Sum-------------------------------------------\n");
        p_init();
        printf("heap total size : %d MB; free size: %d MB\n", global_meta->total_size / (1024*1024), global_meta->free_size / (1024*1024));
        printf("---------------------------------------------------------------------------------\n\n");
    }
    return 0;
}

