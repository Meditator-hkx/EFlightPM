/*************************************************************************
	> File Name: trajtest.c
	> Author: 
	> Mail: 
	> Created Time: Sun 23 Sep 2018 07:48:33 PM PDT
 ************************************************************************/
#include<stdlib.h>
#include<stdio.h>
#include "traj.h"
#include<time.h>
#include<unistd.h>

#define TRAJNUM  (100)
#define QUERYNUM (30)
int main() {
    // Step 1: certify the trajectory number
    FILE *fp;
    TrajInfo *buffer = (TrajInfo *)malloc(sizeof(TrajInfo));
    int i,j,k;
    int read_traj_num;
    int traj_x, traj_y, traj_z;
    int query_end_flag = 0;

    fp = fopen("trajdata.bin", "wb+");
    
    TrajInfo *trajs = (TrajInfo *)malloc(sizeof(TrajInfo) * QUERYNUM);
    if (trajs == NULL) {
        printf("Error for trajectory space allocation.\n");
        return -1;
    }

    // Step 2: create random trajectories
    for (i = 0;i < TRAJNUM;i++) {
        rand_create_traj(&trajs[i]);
    }

    // Step 3: range query for specified number of trajectories
    for (i = 0;i < QUERYNUM;i++) {
        time_t t;
        srand(time(&t));
        j = rand() % TRAJNUM;
        
        // read the content of trajs[j]
        read_traj_num = trajs[j].point_num;
        if (i == 0) {
            fwrite(&trajs[j], sizeof(TrajInfo), 1, fp);
        }
        printf("write to buffer: %d.\n", read_traj_num);
        fflush(fp);
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
    // Step 4: recovery from system/program failure
    // 4.1 Save all data into backup file using fsync
    // load into memory if needed as recovery
    fread(buffer, sizeof(TrajInfo), 1, fp);
    printf("buffer content: %d\n", buffer->point_num);
    free(trajs);
    fclose(fp);
}
