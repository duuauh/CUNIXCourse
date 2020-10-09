#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "DataStructure.h"

int pingfang (int x) {
    return x * x;
}

int coincidence_detection (int x, int y, struct CLUSTER *cluster, int clust_num, struct FLAT *flat, int flat_num, int index) {
    for (int i = 0; i < clust_num; i++) {
        for (int j = 0; j < 6; j++) {
            if ((x + j == cluster[i].x) && (y == cluster[i].y))
                return 1;
            if ((x == cluster[i].x) && (y + j == cluster[i].y))
                return 1;
        }
    }

    for (int i = 0; i < index; i++) {
        for (int j = 0; j < 6; j++) {
            for (int k = 0; k < 6; k++) {
                if ((x + j == flat[i].unit_add[k*2]) && (y == flat[i].unit_add[k*2+1]))
                    return 1;
                if ((x == flat[i].unit_add[k*2]) && (y + j == flat[i].unit_add[k*2+1]))
                    return 1;
            }
        }
    }

    return 0;
}

void init_MAP() {

    //随机生成地图大小的相关数据
    srand((unsigned)time(0));

    int map_width = 0;
    int map_height = 0;
    do {
        map_width = (rand() % 5) * 1000;
    } while (!map_width);

    do {
        map_height = (rand() % 5) * 1000;
    } while (!map_height);

    int clust_num_x = map_width / 1000;
    int clust_num_y = map_height / 1000;
    int clust_num = clust_num_x * clust_num_y;
    int flat_num = clust_num * 10;
    int user_num = 1000;
    
    //初始化节簇点位置
    struct CLUSTER *cluster = (struct CLUSTER*) malloc(clust_num * sizeof(struct CLUSTER));
    for (int i = 0; i < clust_num_x; i++) {
        for (int j = 0; j < clust_num_y; j++) {
            cluster[i * clust_num_y + j].x = i * 1000 + 500;
            cluster[i * clust_num_y + j].y = j * 1000 + 500;
        }
    }

    //初始化公寓的位置
    struct FLAT *flat = (struct FLAT *)malloc(flat_num * sizeof(struct FLAT));
    int direction = 0;
    int flat_x_tmp = 0;
    int flat_y_tmp = 0;
    for (int i = 0; i < flat_num; i++) {
        direction = rand() % 2;
        flat_x_tmp = rand() % map_width;
        flat_y_tmp = rand() % map_height;
        while(coincidence_detection(flat_x_tmp, flat_y_tmp, cluster, clust_num, flat, flat_num, i)) {
            flat_x_tmp = rand() % clust_num_x;
            flat_y_tmp = rand() % clust_num_y;
        }
        //printf("%d\n", i);
        if (direction) {
            for (int j = 0; j < 6; j++) {
                flat[i].unit_add[j*2] = flat_x_tmp;
                flat[i].unit_add[j*2 + 1] = flat_y_tmp + j;
            }
        } else {
            for (int j = 0; j < 6; j++) {
                flat[i].unit_add[j*2] = flat_x_tmp + j;
                flat[i].unit_add[j*2 + 1] = flat_y_tmp;
            }
        }
    }

    //将地图数据写入到文件“map.config”中
    FILE *fp = fopen("map.config", "w+");
    fprintf(fp, "%d %d\n%d %d\n%d\n%d\n", map_width, map_height, clust_num_x, clust_num_y, flat_num, user_num);
    for (int i = 0; i < flat_num; i++) {
        for (int j = 0; j < 6; j++){
            fprintf(fp, "%d %d ", flat[i].unit_add[j*2], flat[i].unit_add[j*2+1]);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);

    free(cluster);
    free(flat);
}

void USER_move(struct FLAT *flat, struct USER *user, int user_num, int flat_num, int *broadcast, int time_stamp) {
    srand((unsigned)time(0));

    for (int i = 0; i < user_num; i++) {
        //将近14天的轨迹推后一天
        for (int j = 0; j < 13; j++) {
            user[i].trail[27-j*2] = user[i].trail[27-(j+1)*2];
            user[i].trail[27-j*2-1] = user[i].trail[27-(j+1)*2-1];
        }
        user[i].trail[0] = rand() % flat_num;       //得到今天的公寓楼编号 
        user[i].trail[1] = rand() % 6;              //得到今天的单元号
        broadcast[i*3] = flat[user[i].trail[0]].unit_add[user[i].trail[1]*2];
        broadcast[i*3+1] = flat[user[i].trail[0]].unit_add[user[i].trail[1]*2+1];
        broadcast[i*3+2] = user[i].infected;        //将自己今天的信息广播出去，好让其他用户知道哪些用户离自己2km
        user[i].other_user[i*4] = time_stamp;
        user[i].other_user[i*4+1] = user[i].infected;
        user[i].other_user[i*4+2] = user[i].trail[0];
        user[i].other_user[i*4+3] = user[i].trail[1];    //更新自己的用户信息
    }
}

void UPDATE(struct CLUSTER *cluster, struct USER *user, struct FLAT *flat, int *CLOUD_user, int user_num, int clust_num, int *broadcast, int time_stamp) {
    
    for (int i = 0; i < user_num; i++) {
        for (int j = i+1; j < user_num; j++) {
            if ((((broadcast[i*3] - broadcast[j*3])^2) + ((broadcast[i*3+1] - broadcast[j*3+1])^2)) <= 40000) {     //寻找距离自己2km以内的用户
                if ((broadcast[i*3] == broadcast[j*3]) && (broadcast[i*3+1] == broadcast[j*3+1])) {
                    if (broadcast[i*3+2] || broadcast[j*3+2]) {
                        user[i].infected = 1;
                        user[j].infected = 1;
                    }//已经被感染的用户会刚染同单元的健康用户
                }
                for (int k = 0; k < user_num; k++){  //两个2km之内的用户交换数据
                    if (user[i].other_user[k*4] > user[j].other_user[k*4]) {    //以时间戳为依据更新数据
                        user[j].other_user[k*4] = user[i].other_user[k*4];
                        user[j].other_user[k*4+1] = user[i].other_user[k*4+1];
                        user[j].other_user[k*4+2] = user[i].other_user[k*4+2];
                        user[j].other_user[k*4+3] = user[i].other_user[k*4+3];
                    }
                    if (user[i].other_user[k*4] < user[j].other_user[k*4]) {
                        user[i].other_user[k*4] = user[j].other_user[k*4];
                        user[i].other_user[k*4+1] = user[j].other_user[k*4+1];
                        user[i].other_user[k*4+2] = user[j].other_user[k*4+2];
                        user[i].other_user[k*4+3] = user[j].other_user[k*4+3];
                    }
                }
            }
        }
    }

    //用户和节簇点通信，把数据上传到云端
    for (int i = 0; i < user_num; i++) {
        for (int j = 0; j < clust_num; j++) {
            if ((broadcast[i*3] - cluster[j].x) ^ 2 + (broadcast[i*3+1] - cluster[j].y) ^ 2 <= 40000) {
                for (int k = 0; k < user_num; k++) {
                    if (user[i].other_user[k*4] > CLOUD_user[k*56]){
                        for (int m = 0; m < 13; m++) {
                            CLOUD_user[k*56+55-m*4] = CLOUD_user[k*56+55-(m+1)*4];
                            CLOUD_user[k*56+55-m*4-1] = CLOUD_user[k*56+55-(m+1)*4-1];
                            CLOUD_user[k*56+55-m*4-2] = CLOUD_user[k*56+55-(m+1)*4-2];
                            CLOUD_user[k*56+55-m*4-3] = CLOUD_user[k*56+55-(m+1)*4-3];
                        }
                        CLOUD_user[k*56] = user[i].other_user[k*4];
                        CLOUD_user[k*56+1] = user[i].other_user[k*4+1];
                        CLOUD_user[k*56+2] = flat[user[i].other_user[k*4+2]].unit_add[user[i].other_user[k*4+3]*2];
                        CLOUD_user[k*56+3] = flat[user[i].other_user[k*4+2]].unit_add[user[i].other_user[k*4+3]*2+1];
                    }
                }
            }
        }
    }
}