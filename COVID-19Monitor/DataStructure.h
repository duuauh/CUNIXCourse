#include <stdio.h>

struct FLAT {             //公寓楼
    int ID;               //该楼的编号
    int unit_add[12];     //单元的坐标，两两一组，一共六组
};

struct USER {
    int ID;               //用户编号
    int trail[28];        //用户最近十四天轨迹
    int *other_user;      //其他用户今天的轨迹
    int infected;         //用户是否被感染
};

struct CLUSTER {
    int x;
    int y; 
};            //簇节点，x，y分别代表在地图里的横纵坐标

struct MAP {              //地图
    int MAX_WIDTH;        //最大宽度
    int MAX_HEIGHT;       //最大高度
    struct FLAT* FLAT_add;       //公寓数组首地址
    struct CLUSTER* CLUSTER_add; //节簇点数组首地址
};

//计算整数平方
extern int pingfang(int x);

//随机选取公寓地址的时候检查是否与其他建筑位置冲突
extern int coincidence_detection(int x, int y, struct CLUSTER *cluster, int clust_num, struct FLAT *flat, int flat_num, int index);

//随机一个新地图，包括地图大小、节簇点和公寓位置
extern void init_MAP();

//用户随机移动到一个新的地点
extern void USER_move(struct FLAT *flat, struct USER *user, int user_num, int flat_num, int *broadcast, int time_stamp);

//用户和其他用户、节簇点通信，把信息跟新到云端
extern void UPDATE(struct CLUSTER *cluster, struct USER *user, struct FLAT *flat, int *CLOUD_user, int user_num, int clust_num, int *broadcast, int time_stamp);