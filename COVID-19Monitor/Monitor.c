#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "DataStructure.h"

int main (int argc, char *argv[]) {
    
    if (argc > 1) {
        if (!strcmp(argv[1], "init")) {
            init_MAP();
        }
    }

    srand((unsigned)time(0));

    int map_width, map_height;
    int clust_num_x, clust_num_y;
    int clust_num;
    int flat_num;
    int user_num;

    //从文件中载入地图信息
    FILE *fp = fopen("map.config", "r+");
    fscanf(fp, "%d%d", &map_width, &map_height);
    fscanf(fp, "%d%d", &clust_num_x, &clust_num_y);
    fscanf(fp, "%d", &flat_num);
    fscanf(fp, "%d", &user_num);
    clust_num = clust_num_x * clust_num_y;

    struct CLUSTER *cluster = (struct CLUSTER*) malloc(clust_num * sizeof(struct CLUSTER));
    struct FLAT *flat = (struct FLAT*) malloc(flat_num * sizeof(struct FLAT));
    struct USER *user = (struct USER*) malloc(user_num * sizeof(struct USER));

    for (int i = 0; i < clust_num_x; i++) {
        for (int j = 0; j < clust_num_y; j++) {
            cluster[i * clust_num_y + j].x = i * 1000 + 500;
            cluster[i * clust_num_y + j].y = j * 1000 + 500;
        }
    }

    for (int i = 0; i < flat_num; i++) {
        flat[i].ID = i + 1;
        for (int j = 0; j < 6; j++) {
            fscanf(fp, "%d%d", &(flat[i].unit_add[j*2]), &(flat[i].unit_add[j*2+1]));
        }
    }

    for (int i = 0; i < user_num; i++) {
        user[i].ID = i;
        int test = rand() % 6;
        if(test == 3)
            user[i].infected = 1;
        else
            user[i].infected = 1;

        user[i].other_user = (int*) malloc(user_num * 4 * sizeof(int));   //time_stamp, infected, ID, unit
        for (int j = 0; j < user_num; j++) {
            user[i].other_user[4 * j] = -1;
        }
    }

    int *broadcast = (int*) malloc(user_num * 3 * sizeof(int));
    int *CLOUD_user = (int*) malloc(user_num * 56 * sizeof(int));
    int time_stamp = 0;

    char controller = '0';
    int userID;
    int detec_x, detec_y;
    int infected_num = 0;
    
    while(controller != 'q') {
        time_stamp++;
        USER_move(flat, user, user_num, flat_num, broadcast, time_stamp);
        
        UPDATE(cluster, user, flat, CLOUD_user, user_num, clust_num, broadcast, time_stamp);
        
        printf("当前天数：%d，按‘1’选择追踪用户轨迹，按‘2’统计某一地点感染人数，按c键继续模拟，按q退出\n", time_stamp);
        controller = getchar();
        getchar();
        infected_num = 0;
        while(controller != 'c' && controller != 'q') {
            switch(controller) {
                case '1':
                    printf("请选择用户编号：0~%d\n", user_num);
                    scanf("%d", &userID);
                    getchar();
                    printf("选择了%d号用户\n", userID);
                    for (int i = 0; i < 14; i++) {
                        printf("第%d天，(%d,%d)\n", CLOUD_user[userID*56+i*4], CLOUD_user[userID*56+i*4+2]+1, CLOUD_user[userID*56+i*4+3]+1);
                    }
                    printf("按‘1’选择追踪用户轨迹，按‘2’统计某一地点感染人数，按c键继续模拟，按q退出\n");
                    controller = getchar();
                    getchar();
                    break;
                case '2':
                    printf("请选择想要查询的地点，横纵坐标范围0~%d，0~%d\n", map_width, map_height);
                    scanf("%d%d", &detec_x, &detec_y);\
                    getchar();
                    //直接寻找查询点1km范围内的公寓楼，找公寓楼里的人数
                    for (int i = 0; i < flat_num; i++) {
                        for (int j = 0; j < 6; j++) {
                            if ((pingfang(detec_x - flat[i].unit_add[j*2]) + pingfang(detec_y - flat[i].unit_add[j*2+1])) <= 10000) {
                                for (int m = 0; m < user_num; m++) {
                                    if ((CLOUD_user[m*56+2]==flat[i].unit_add[j*2]) && (CLOUD_user[m*56+3]==flat[i].unit_add[j*2+1])) {
                                        if (CLOUD_user[m*56+1]) {
                                            infected_num++;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    printf("坐标(%d，%d)周围1km的感染人数为：%d\n", detec_x, detec_y, infected_num);
                    printf("按‘1’选择追踪用户轨迹，按‘2’统计某一地点感染人数，按c键继续模拟，按q退出\n");
                    controller = getchar();
                    getchar();
                    break;
                default:
                    break;
            }
        }
    }

    free(cluster);
    free(flat);
    free(user);
    free(broadcast);
    free(CLOUD_user);
    fclose(fp);

    return 0;
}
