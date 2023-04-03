"""
Author:
    Name: KyungHyun Lim
    Email: lkh1075@gmail.com
"""

from collections import deque

# NxM 맵크기
# (R, C) 맨홀 뚜껑 위치
# L시간 후 가능한 위치
N, M, R, C, L = 0, 0, 0, 0, 0

grid = [[0] * 50 for _ in range(50)] # 맵정보
visited = [[0] * 50 for _ in range(50)] # 맵 탐색용
c = 0 # 탈주범이 있을 수 있는 곳 위치 개수

pipes = [ # 파이프별 이동 가능 방향
    [],
    [0, 1, 2, 3], # 1. 상하좌우
	[0, 1], # 2. 상하
	[2, 3], # 3. 좌우
	[0, 3], # 4. 상우
	[1, 3], # 5. 하우
	[1, 2], # 6. 하좌
	[0, 2], # 7. 상좌
]

# 0: 상, 1: 하, 2: 좌, 3: 우
dx = [-1, 1, 0, 0]
dy = [0, 0, -1, 1]
connected = [
    [0, 1, 1, 0, 0, 1, 1, 0],
	[0, 1, 1, 0, 1, 0, 0, 1],
	[0, 1, 0, 1, 1, 1, 0, 0],
	[0, 1, 0, 1, 0, 0, 1, 1]    
]

def search(x, y):
    global grid, visited, pipes, connected, c, N, M, dx, dy
    q = deque()
    q.append((1, x, y))
    visited[x][y] = 1
    
    while q:
        l, cx, cy = q.popleft()
        kind = grid[cx][cy]
        visited[cx][cy] = 1
        
        if l >= L: continue # 시간 초가 지나면 못감
        
        for i in range(len(pipes[kind])):
            nx, ny = cx + dx[pipes[kind][i]], cy + dy[pipes[kind][i]]
            if nx < 0 or nx >= N or ny < 0 or ny >= M: continue # 격자 벗어난 경우
            if visited[nx][ny]: continue # 중복 방문인 경우
            if grid[nx][ny] == 0: continue # 파이프가 아닌 경우
            if connected[pipes[kind][i]][grid[nx][ny]] != 1: continue # 연결된 파이프가 아닌 경우
            
            q.append((l + 1, nx, ny))
            visited[nx][ny] = 1
            c += 1

T = int(input())
# 여러개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
for test_case in range(1, T + 1):
    
    N, M, R, C, L = list(map(int, input().split()))
    visited = [[0] * 50 for _ in range(50)] # 맵 탐색용
    for i in range(N):
        grid[i] = list(map(int, input().split()))
            
    c = 1
    search(R, C)
    
    print(f'#{test_case} {c}')
    
'''
1
5 6 2 1 3
0 0 5 3 6 0
0 0 2 0 2 0
3 3 1 3 7 0
0 0 0 0 0 0
0 0 0 0 0 0
'''