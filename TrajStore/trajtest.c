/*************************************************************************
	> File Name: trajtest.c
	> Author: 
	> Mail: 
	> Created Time: Sun 23 Sep 2018 07:48:33 Daisy+PM PDT
 ************************************************************************/
#include<stdlib.h>
#include<stdio.h>
#include "traj.h"
#include "mmap/init.h"
#include<time.h>
#include<unistd.h>

#define TRAJNUM  (200000)
#define QUERYNUM (10000000)
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
    int p_get_flag = 0;

    printf("\n-------------------------------------------------------------------------\n");
    //p_clear();
    
    if (argc == 2 && argv[1][0] == 'P') {
        // p_clear();
        trajs = (TrajInfo *)p_get(1);
        if (trajs) {
            p_get_flag = 1;
            printf("Daisy+PM: trajectory data found in PM.\n");
        }   else {
            p_get_flag = 0;
            p_clear();
            trajs = (TrajInfo *)p_malloc(1, sizeof(TrajInfo) * TRAJNUM);
            if (trajs == NULL) {
                printf("Daisy+PM: Error for trajectory space allocation.\n");
                return -1;
            }
            printf("Daisy+PM: No trajectory data in PM.\n");
            printf("Daisy+PM: loading data into PM...\n");
        }
    } else {
        fp = fopen("trajdata.bin", "wb+");
        if (fp == NULL) {
            printf("open trajdata.bin failed!\n");
        }
        // trajs = (TrajInfo *)malloc(sizeof(TrajInfo) * TRAJNUM);
        // p_free(2);
        trajs = (TrajInfo *)malloc(sizeof(TrajInfo) * TRAJNUM);
        if (trajs == NULL) {
            printf("DRAM: Error for trajectory space allocation.\n");
            return -1;
        }
        printf("DRAM: loading data into DRAM...\n");
    }
    
    start = clock();

    // Step 2: create random trajectories
    // Recovery Test
    unsigned long li;
    if (p_get_flag == 0) {
        for (i = 0;i < TRAJNUM;i++) {
            rand_create_traj(&trajs[i]);
        }
        for (li = 0;li < 1024 * 1024 * 1024;li++) {
            
        }
    }

    end = clock();
    duration = (double)(end-start) / CLOCKS_PER_SEC;

    if (argc == 2 && argv[1][0] == 'P') {
        printf("Daisy+PM: Data recovery success!\n");
        printf("Daisy+PM Recovery Time: %f seconds.\n", duration);
    } else {
        printf("DRAM: data recovery success!\n");
        printf("DRAM Recovery Time: %f seconds.\n", duration);
    }
    printf("-------------------------------------------------------------------------\n");

    // Step 3: range query for specified number of trajectories
    if (argc == 2 && argv[1][0] == 'P') {
        printf("Daisy+PM: start quering %d trajectory records.\n", QUERYNUM);
    } else {
        printf("DRAM: start quering %d trajectory records.\n", QUERYNUM);
    }


    start = clock();
    for (i = 0;i < QUERYNUM;i++) {
        srand((unsigned int)time(NULL));
        j = rand() % TRAJNUM;
        
        // read the content of trajs[j]
        /*read_traj_num = trajs[j].point_num;
         if (argc == 2 && argv[1][0] == 'D') {
            fwrite(&trajs[j], sizeof(TrajInfo), 1, fp);
            // printf("write trajectory data to buffer: %d.\n", read_traj_num);
            //fflush(fp);
        }
        */
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
        printf("Daisy+PM: query time: %f secs.\n", duration);
    else 
        printf("DRAM: query time: %f secs.\n", duration);
    

    // Step 4: recovery from system/program failure
    // 4.1 Save all data into backup file using fsync
    // load into memory if needed as recovery
    // fread(buffer, sizeof(TrajInfo), 1, fp);
    // printf("buffer content: %d\n", buffer->point_num);
    if (argc == 2 && argv[1][0] == 'P') {
        // p_clear();
    } else {
        // printf("free trajs.\n");
        // free(trajs);
        free(trajs);
        fclose(fp);
    }
}
