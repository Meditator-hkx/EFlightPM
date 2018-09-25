/*************************************************************************
	> File Name: traj.c
	> Author: 
	> Mail: 
	> Created Time: Sat 22 Sep 2018 09:01:58 PM PDT
 ************************************************************************/

#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include "traj.h"

time_t t;

void rand_create_point(PointInfo *point) {
    // time_t t;
    srand((unsigned int)time(NULL));
    point->city_code = rand() % 50;
    point->xx = rand() % 360;
    point->yy = rand() % 360;
    point->zz = rand() % 360;
    point->end = 0;
}

void rand_create_traj(TrajInfo *traj) {
    // time_t t;
    int last = 0, i;
    srand((unsigned int)time(NULL));
    traj->point_num = rand() % 11;
    for (i = 0;i < traj->point_num;i++) {
        // rand_create_point(&traj->point_set[i]);
        traj->point_set[i].city_code = rand() % 50;
        traj->point_set[i].xx = rand() % 360;
        traj->point_set[i].yy = rand() % 360;
        traj->point_set[i].zz = rand() % 360;
        traj->point_set[i].end = 0;
    } 
    last = i - 1;
    traj->point_set[last].end = 1;
}

