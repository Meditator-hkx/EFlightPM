/*************************************************************************
	> File Name: test.c
	> Author: Kaixn 
	> Mail: Kaixinhuang@sjtu.edu.cn
	> Created Time: 2018年04月17日 星期二 18时25分45秒
 ************************************************************************/

#include<stdio.h>
#include "init.h"

typedef struct {
    int stu_id;
    char *name;
} struct_stu;

int main(int argc, char **argv) {
    int ret;
    int id = 100;
    if (argc == 2 && argv[1][0] == 'm') {
        // init to guarantee purity of this run
        p_clear();
        // allocate memory space for struct_stu
        id = 100;
        struct_stu *stu = (struct_stu *)p_malloc(id,sizeof(struct_stu));
        stu->stu_id = 10001;
        stu->name = "kaixin";
    } else if (argc == 2 && argv[1][0] == 'g') {
        // get the persistent object
        struct_stu *stu_get = (struct_stu *)p_get(id);
        printf("student   id: %d\n", stu_get->stu_id);
        printf("student name: %s\n", stu_get->name);
    } else if (argc == 2 && argv[1][0] == 'f') {
        // free the allocated memory region
        ret = p_free(id);
        if (ret == 0) {
            printf("Success in freeing specified memory.\n");
        } 
    } else if (argc == 2 && argv[1][0] == 'c') {
        // reset the whole initiated space
        ret = p_clear();
        if (ret == 0) {
            printf("Success in reseting the whole user heap.\n");
        }  
    } else {
        printf("Test begins / ends!\n");
        printf("---------------------------------------------------------------\n\n");
    }
    return 0;
}

