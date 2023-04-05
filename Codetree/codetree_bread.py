"""
https://www.codetree.ai/training-field/frequent-problems/codetree-mon-bread/

m명의 사람들, m분에 각자의 베이스캠프에서 출발해 편의점으로 이동

1분동안 다음과 같은 행동 진행
    1. 본인이 가고 싶은 편의점 방향을 향해서 1칸 이동
        - 최단거리로 움직임
        - 최단거리가 여러가지 이면, 상, 좌, 우, 하 순서로 움직임
    2. 편의점에 도착하면, 해당 편의점에서 멈춤
        - 이때부터 다른 사람들은 이곳을 지나갈 수 없음
    3. 현재 시간이 t분이고, t <= m을 만족하면, t번 사람은 자신이 가고 싶은 편의 점과 가장 가까이 있는 베이스 캠프에 입장
        - 여러가지면, 행이 작은순, 열이 작은 순
        - t번 사람이 베이스 캠프로 이동하는 데에는 시간이 소요되지 않음
        - 이때부터 다른 사람들은 이곳을 지나갈 수 없음

요약: 사람들이 위와 같은 방식으로 움직일 때 총 몇 분 후에 모두 편의점에 도착하는지를 구하는 프로그램을 작성해보세요.

Author:
    Name: KyungHyun Lim
    Email: lkh1075@gmail.com
"""

from collections import defaultdict, deque

def find_road(n, grid, cord, store_cord):
    # 상, 좌, 우, 하
    dx = [-1, 0, 0, 1]
    dy = [0, -1, 1, 0]
    visited = [[False] * n for _ in range(n)]
    
    q = deque()
    q.append((cord[0], cord[1], 0, [[cord[0], cord[1]]]))
    visited[cord[0]][cord[1]] = 0
    
    g_cost = n * n + 1
    g_path = []
    
    while q:
        cx, cy, cost, path = q.popleft()
        if store_cord: 
            # 편의점 도착 검사
            if cx == (store_cord[0]-1) and cy == (store_cord[1]-1):
                if cost < g_cost:
                    g_cost = cost
                    g_path = path
        else:
            # 베이스 캠프 도착 검사
            if grid[cx][cy] == 1:
                if cost < g_cost:
                    g_cost = cost
                    g_path = path
            
        for d in range(4):
            nx, ny = cx + dx[d], cy + dy[d]
            if 0 <= nx < n and 0 <= ny < n: # 맵 벗어나지 않음
                if not visited[nx][ny]: # 방문한 적이 없으면
                    if grid[nx][ny] != -1: # 갈수 있는 곳이면
                        n_path = path[:]
                        n_path.append([nx, ny])
                        q.append([nx, ny, cost + 1, n_path])
                        visited[nx][ny] = True
        
    return g_path
        
n, m = list(map(int, input().split())) # 맵크기, 사람수
grid = [list(map(int, input().split())) for _ in range(n)] # 맵 상태 (0: 빈공간, 1: 베이스캠프)
store = [list(map(int, input().split())) for _ in range(m)] # idx번째 사람이 가고싶은 편의점 좌표 (-1 필수)
person = defaultdict(list) # 맵에 들어온 사람의 번호 및 위치

arrived = 0
time = 0

while arrived < m:
    time += 1
    # print(f'time: {time} /', arrived)
    # 1. 가고 싶은 편의점 최단거리 방향을 향해 1칸 이동
    for order, cord in person.items():
        if cord[-1] != -1:
            path = find_road(n, grid, cord, store[order])
            # print(f'{order + 1} move:', path, f'target: {store[order]}')
            if path[1][0] == (store[order][0] - 1) and path[1][1] == (store[order][1] -1):
                # 편의점에 도착한 것이면
                grid[path[1][0]][path[1][1]] = -1 # 지나갈 수 없는 곳
                person[order][-1] = -1 # 더이상 움직이지 않도록
                arrived += 1 # 도착한 사람 증가
            else: 
                # 위치 업데이트
                person[order] = [path[1][0], path[1][1], 1]
    
    # 2. t <= m을 만족하면, t번 사람 베이스 캠프로 이동
    if time <= m:
        store_x, store_y = store[time - 1] # 사람이 가야할 편의점 위치
        path = find_road(n, grid, [store_x-1, store_y-1], None) # 베이스 캠프 찾기
        # print(f'{time} base camp:', path[-1])
        person[time - 1] = [path[-1][0], path[-1][1], 1] # 사람 추가
        grid[path[-1][0]][path[-1][1]] = -1 # 지나 갈 수 없는 곳
    
    # print('p:', person)
print(time)
    