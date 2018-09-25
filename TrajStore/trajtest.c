/*************************************************************************
	> File Name: trajtest.c
	> Author: 
	> Mail: 
	> Created Time: Sun 23 Sep 2018 07:48:33 PM PDT
 ************************************************************************/
#include<stdlib.h>
#include<stdio.h>
#include "traj.h"
#include "mmap/init.h"
#include<time.h>
#include<unistd.h>

#define TRAJNUM  (1000)
#define QUERYNUM (300)
int main(int argc, char **argv) {
    // Step 1: certify the trajectory number
    FILE *fp;
    TrajInfo *trajs;
    // TrajInfo *buffer = (TrajInfo *)malloc(sizeof(TrajInfo));
    int i,j,k;
    int read_traj_num;
    int traj_x, traj_y, traj_z;
    int query_end_flag = 0;
    clock_t start, end;
    double duration;
    
    if (argc == 2 && argv[1][0] == 'P') {
        p_clear();
        trajs = (TrajInfo *)p_malloc(1, sizeof(TrajInfo) * QUERYNUM);
        if (trajs == NULL) {
            printf("PM: Error for trajectory space allocation.\n");
            return -1;
        }
    } else {
        fp = fopen("trajdata.bin", "wb+");
        if (fp == NULL) {
            printf("open trajdata.bin failed!\n");
        }
        trajs = (TrajInfo *)malloc(sizeof(TrajInfo) * QUERYNUM);
        if (trajs == NULL) {
            printf("DRAM: Error for trajectory space allocation.\n");
            return -1;
        }
    }

    if (argc == 2 && argv[1][0] == 'D') {
        start = clock();
        printf("DRAM: loading data...\n");
    }
    // Step 2: create random trajectories
    for (i = 0;i < TRAJNUM;i++) {
        rand_create_traj(&trajs[i]);
    }
    if (argc == 2 && argv[1][0] == 'P') {
        start = clock();
        printf("PM: loading data...\n");
    }

    // Step 3: range query for specified number of trajectories
    for (i = 0;i < QUERYNUM;i++) {
        time_t t;
        srand((unsigned int)time(NULL));
        j = rand() % TRAJNUM;
        
        // read the content of trajs[j]
        read_traj_num = trajs[j].point_num;
        if (argc == 2 && argv[1][0] == 'D') {
            fwrite(&trajs[j], sizeof(TrajInfo), 1, fp);
            // printf("write trajectory data to buffer: %d.\n", read_traj_num);
            fflush(fp);
        }
        k = 0;
        while (query_end_flag == 0) {
            traj_x = trajs[j].point_set[k].xx;
            traj_y = trajs[j].point_set[k].yy;
            traj_z = trajs[j].point_set[k].zz;
            if (trajs[j].point_set[k].end == 1) {
                query_end_flag = 0;
                break;
            }
            k++;
        }
    }
    end = clock();
    duration = (double)(end - start) / (CLOCKS_PER_SEC);
    if (argc == 2 && argv[1][0] == 'P')
        printf("PM: total query time: %f secs.\n", duration);
    else 
        printf("DRAM: total query time: %f secs.\n", duration);
    

    // Step 4: recovery from system/program failure
    // 4.1 Save all data into backup file using fsync
    // load into memory if needed as recovery
    // fread(buffer, sizeof(TrajInfo), 1, fp);
    // printf("buffer content: %d\n", buffer->point_num);
    if (argc == 2 && argv[1][0] == 'P') {
        p_clear();
    } else {
        printf("free trajs.\n");
        free(trajs);
        fclose(fp);
    }
}
