
'''
State定义为现在三个杯子的状态，a、b、c分别表示8ml、5ml、3ml的杯子
hash和eq函数是为了让State变量能作为dict的key
'''
class State:
    def __init__(self, volume):
        self.a = volume[0]
        self.b = volume[1]
        self.c = volume[2]
    def __hash__(self):
        return self.a*100+self.b*10+self.c
    def __eq__(self, other):
        if isinstance(other, self.__class__):
            return [self.a, self.b, self.c]==[other.a, other.b, other.c]
        else:
            return False

'''
pour函数接收两个参数：杯子的State和倒水的方法
三个杯子相互倒水一共有6六种方法
最后返回倒水之后杯子的状态
'''
def pour(state, method):
    tmp = State([state.a, state.b, state.c])
    if method == 0:
        tmp.b = tmp.a + tmp.b
        tmp.a = 0
        if tmp.b > 5:
            tmp.a = tmp.b - 5
            tmp.b = 5
    if method == 1:
        tmp.c = tmp.a + tmp.c
        tmp.a = 0
        if tmp.c > 3:
            tmp.a = tmp.c - 3
            tmp.c = 3
    if method == 2:
        tmp.a = tmp.a + tmp.b
        tmp.b = 0
        if tmp.a > 8:
            tmp.b = tmp.a - 8
            tmp.a = 8
    if method == 3:
        tmp.c = tmp.b + tmp.c
        tmp.b = 0
        if tmp.c > 3:
            tmp.b = tmp.c - 3
            tmp.c = 3
    if method == 4:
        tmp.a = tmp.a + tmp.c
        tmp.c = 0
        if tmp.a > 8:
            tmp.c = tmp.a - 8
            tmp.a = 8
    if method == 5:
        tmp.b = tmp.b + tmp.c
        tmp.c = 0
        if tmp.b > 5:
            tmp.c = tmp.b - 5
            tmp.b = 5
    return tmp

'''
Action变量定义为杯子上一时刻的状态和倒水的动作
'''
class Action:
    def __init__(self, State, char):
        self.start = State
        self.action = char

'''
输入状态，检查是否达到要求
'''
def success(state):
    if (state.a == 4 & state.b == 4):
        return True
    else:
        return False

def main():
    history = {}
    method = ["ab", "ac", "ba", "bc", "ca", "cb"]
    #初始状态
    start = State([8,0,0])

    #搜索队列
    search_list = [start]

    #同时维护一个动作队列，将来向词典里添加新值的时候需要用到
    action_list = [Action(State([0,0,0]),"init")]

    #检索完毕的状态
    history[start] = Action(State([0,0,0]),"init")

    break2 = False
    
    tmp = State([8,0,0])
    while(1):
        item = search_list[0]
        for i in range(0,6):
            tmp = pour(item, i)
            if success(tmp):
                history[tmp] = Action(item, i)
                break2 = True
                break
            if not (tmp in history):
                if not (tmp in search_list):
                    search_list.append(tmp)
                    action_list.append(Action(item, i))

        history[item] = action_list[0]
        del search_list[0]
        del action_list[0]
        if break2:
            break
    
    trace = []
    tmp = State([4,4,0])
    while(1):
        tmp_act = history[tmp]
        trace.insert(0,tmp_act.action)
        tmp = tmp_act.start
        if tmp == start:
            break
    tmp = start
    print(tmp.a, tmp.b, tmp.c)
    for act in trace:
        print(method[act])
        tmp = pour(tmp, act)
        print(tmp.a, tmp.b, tmp.c)
    
if __name__ == "__main__":
    main()