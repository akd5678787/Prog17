# Камиль
# Тагир
# Ксения
# Сергей
start = 0 #the top from which we start

BIG_NUM = 10 ** 9
edge_list = [(0, 1), (1, 3), (1, 6), (3, 2), (3, 7), (4, 2), (6, 3), (7, 4), (7, 5)]
vert_num = 8
weight_list = [-5.4, 12.3, -3.0, 7.7, -1.0, 2.6, -4.1, 10.0, 3.9]

dist = [BIG_NUM for _ in range(vert_num)]
dist[start] = 0
weight_dict = {edge: weight_list[i] for i, edge in enumerate(edge_list)}
stop_flag = False
cycle_flag = False
k = 1

while k < vert_num and not stop_flag:
    k+=1
    stop_flag = True
    for _from, _to in weight_dict.keys():
        if dist[_from] + weight_dict[(_from, _to)] < dist[_to]:
            dist[_to] = dist[_from] + weight_dict[(_from, _to)]
            stop_flag = False
for _from, _to in weight_dict.keys():
    if dist[_from] + weight_dict[(_from, _to)] < dist[_to]:
        dist[_to] = dist[_from] + weight_dict[(_from, _to)]
        cycle_flag = True
        break
if cycle_flag:
    print('the data is incorrect, the graph has a negative cycle!')
else:
    print(dist)
