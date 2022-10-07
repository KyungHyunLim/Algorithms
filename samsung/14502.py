"""
BAEKJUN 14502.py 연구소

Description:
    BAEKJUN 14502.py 연구소 알고리즘 문제 풀이

    바이러스가 퍼지는 것을 최대한 막을 수 있는 곳에 벽세우기
    벽은 꼭 3개만 세워야한다. (0은 빈 칸, 1은 벽, 2는 바이러스)
    바이러스가 퍼진 후 안전영역의 최대값 구하기

    3584ms => pypy3 통과 / python3 시간초과 (알고리즘 개선 필요)

Author:
    Name: KyungHyun Lim
    Email: lkh1075@gmail.com
"""
import copy
from collections import deque

N, M = 0, 0
global_max = 0
safearea = 0

def debugging(board):
    for item in board:
        print(item)

def safe_area(board):
    global N, M

    cnt = 0
    for i in range(N):
        for j in range(M):
            cnt += (1 if board[i][j] == 0 else 0)

    return cnt

def spread(board, virus):
    global N, M, global_max

    t_board = copy.deepcopy(board)

    dx = [0, 0, 1, -1]
    dy = [1, -1, 0, 0]

    visited = [[False]*M for _ in range(N)]
    v_area = len(virus)
    for x, y in virus:
        q = deque()
        q.append((x, y))
        visited[x][y] = True
    
        while q:
            x, y = q.popleft()

            for d in range(4):
                nx = x + dx[d]
                ny = y + dy[d]
                if 0 <= nx < N and 0 <= ny < M:
                    if not visited[nx][ny] and (t_board[nx][ny] not in [1, 2]):
                        visited[nx][ny] = True
                        t_board[nx][ny] = 2
                        q.append((nx, ny))     

    global_max = max(safe_area(t_board), global_max)

def create_wall(N, M, board, virus, cnt):
    if cnt == 3:
        # 벽 3개 세웠으면 바이러스 퍼뜨리고 안전영역 계산
        spread(board, virus)
        return
    
    for i in range(N):
        for j in range(M):
            if board[i][j] == 0:
                board[i][j] = 1
                create_wall(N, M, board, virus, cnt + 1)
                board[i][j] = 0

def solution():
    global N, M
    global global_max
    global safearea
    N, M = map(int, input().split())

    board = []
    virus = []
    for _ in range(N):
        board.append(list(map(int, input().split())))
        for j, v in enumerate(board[_]):
            if board[_][j] == 2:
                virus.append([_, j])
            elif board[_][j] == 0:
                safearea += 1

    # 벽세우기 ~
    create_wall(N, M, board, virus, 0)

    return global_max

if __name__ == "__main__":
    answer = solution()
    print(answer)