import random
import numpy as np

def main():

#初始化小球，balls第一维度表示编号，第二维度表示重量，1表示正常质量
    balls = np.ones([12,2], dtype=int)
    for i in range(12):
        balls[i,0] = i
    deviant = random.randint(0,11)
    deviant_weight = 0 if random.randint(0,1)==1 else 2
    balls[deviant,1] = deviant_weight
    
#可以看到只有三层if判断，对应称三次
    if np.sum(balls[0:4,1]) == np.sum(balls[4:8,1]):
        if np.sum(balls[0:3,1]) == np.sum(balls[8:11,1]):
            if balls[0,1] > balls[11,1]:
                print("Ball 11 is ligher")
            else:
                print("Ball 11 is heavier")
        elif np.sum(balls[0:3,1]) > np.sum(balls[8:11,1]):
            if np.sum(balls[0:2,1]) == np.sum(balls[8:10,1]):
                print("Ball 10 is ligher")
            elif balls[8,1] > balls[9,1]:
                print("Ball 9 is ligher")
            else:
                print("Ball 8 is ligher")
        elif np.sum(balls[0:3,1]) < np.sum(balls[8:11,1]):
            if np.sum(balls[0:2,1]) == np.sum(balls[8:10,1]):
                print("Ball 10 is heavier")
            elif balls[8,1] > balls[9,1]:
                print("Ball 8 is heavier")
            else:
                print("Ball 9 is heavier")
    elif np.sum(balls[0:4,1]) > np.sum(balls[4:8,1]):
        if np.sum(balls[0:3,1]) + np.sum(balls[4:6,1]) == np.sum(balls[8:12,1]) + balls[3,1]:
            if balls[6,1] > balls[7,1]:
                print("Ball 7 is lighter")
            else:
                print("Ball 6 is lighter")
        elif np.sum(balls[0:3,1]) + np.sum(balls[5:7,1]) > np.sum(balls[8:12,1]) + balls[3,1]:
            if balls[0,1] > balls[1,1]:
                print("Ball 0 is heavier")
            elif balls[0,1] < balls[1,1]:
                print("Ball 1 is heavier")
            else:
                print("Ball 2 is heavier") 
        else:
            if balls[4,1] > balls[5,1]:
                print("Ball 5 is lighter")
            elif balls[4,1] < balls[5,1]:
                print("Ball 4 is lighter")
            else:
                print("Ball 3 is heavier")
    else:
        if np.sum(balls[4:7,1]) + np.sum(balls[0:2,1]) == np.sum(balls[8:12,1]) + balls[7,1]:
            if balls[2,1] > balls[3,1]:
                print("Ball 3 is lighter")
            else:
                print("Ball 2 is lighter")
        elif np.sum(balls[4:7,1]) + np.sum(balls[0:2,1]) > np.sum(balls[8:12,1]) + balls[7,1]:
            if balls[4,1] > balls[5,1]:
                print("Ball 4 is heavier")
            elif balls[4,1] < balls[5,1]:
                print("Ball 5 is heavier")
            else:
                print("Ball 6 is heavier")
        else:
            if balls[0,1] > balls[1,1]:
                print("Ball 1 is lighter")
            elif balls[4,1] < balls[5,1]:
                print("Ball 0 is lighter")
            else:
                print("Ball 7 is heavier")

#打印出真实情况，对比结果
    print(balls)

if __name__ == "__main__":
    main()
