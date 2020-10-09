#include <stdio.h>

struct FLAT {             //公寓楼
    int ID;               //该楼的编号
    int unit_add[12];    
};

struct USER {
    int ID;
    int trail[28];
    int *other_user;
    int infected;
};

struct CLUSTER {
    int x;
    int y; 
};            //簇节点，x，y分别代表在地图里的横纵坐标

struct MAP {              //地图
    int MAX_WIDTH;        //最大宽度
    int MAX_HEIGHT;       //最大高度
    struct FLAT* FLAT_add;
    struct CLUSTER* CLUSTER_add;
};

extern int pingfang(int x);
extern int coincidence_detection(int x, int y, struct CLUSTER *cluster, int clust_num, struct FLAT *flat, int flat_num, int index);
extern void init_MAP();
extern void USER_move(struct FLAT *flat, struct USER *user, int user_num, int flat_num, int *broadcast, int time_stamp);
extern void UPDATE(struct CLUSTER *cluster, struct USER *user, struct FLAT *flat, int *CLOUD_user, int user_num, int clust_num, int *broadcast, int time_stamp);