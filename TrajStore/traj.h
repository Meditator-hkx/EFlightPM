/*************************************************************************
	> File Name: traj.h
	> Author: 
	> Mail: 
	> Created Time: Sat 22 Sep 2018 08:21:43 PM PDT
 ************************************************************************/

#ifndef _TRAJ_H
#define _TRAJ_H

typedef struct {
    int city_code;
    float xx;
    float yy;
    float zz;
    int end;
} PointInfo;

typedef struct {
    int point_num;
    PointInfo point_set[10];
} TrajInfo;

void rand_create_point(PointInfo *point);
void rand_create_traj(TrajInfo *traj);


#endif
