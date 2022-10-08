"""
BAEKJUN 20058.py 마법사 상어와 파이어스톰

Description:
    BAEKJUN 20058.py 마법사 상어와 파이어스톰 알고리즘 문제 풀이

    2^N x 2^N인 크기 격자, (r, c), 각 칸에는 얼음의 양 존재

    총 Q번 시전
    1. 파이어스톰 시전, 격자를 2^L x 2^L 크기로 나눔
    2. 모든 부분 격자를 90도 회전
    3. 주변(상하좌우)에 얼음이 3개 이상 없으면 양 1 감소
    4. 남아 있는 얼음의 합, 남아 있는 얼음 중 가장 큰 덩어리가 차지하는 칸의 개수

    2 ≤ N ≤ 6
    1 ≤ Q ≤ 1,000
    0 ≤ A[r][c] ≤ 100
    0 ≤ Li ≤ N
    
    재귀로 구역 분할 -> 더이상 분할이 어려울 때 회전
    단계마다 4분할 하면 된다.

    pypy3 통과, python 시간초과
Author:
    Name: KyungHyun Lim
    Email: lkh1075@gmail.com
"""
from collections import deque

N, board = 0, []
dx, dy = [[0, 0, 1, -1], [1, -1, 0, 0]]

def debug(board):
    for item in board:
        print(item)

def search_big_ice(board, visited, i, j):
    global dx, dy

    q = deque()
    q.append((i, j))
    visited[i][j] = True
    count = 0
    amount = 0

    while q:
        cur_x, cur_y = q.popleft()
        count += board[cur_x][cur_y]
        amount += 1
        
        for d in range(4):
            next_x, next_y = cur_x + dx[d], cur_y + dy[d]
            if 0 <= next_x < 2**N and 0 <= next_y < 2**N:
                if not visited[next_x][next_y] and board[next_x][next_y] != 0:
                    q.append((next_x, next_y))
                    visited[next_x][next_y] = True

    return count, amount

def melting(N, board):
    global dx, dy
    cordinates = []
    for i in range(2**N):
        for j in range(2**N):
            count = 0
            for d in range(4):
                nx, ny = i + dx[d], j + dy[d]
                if 0 <= nx < 2**N and 0 <= ny < 2**N:
                    if board[nx][ny] > 0:
                        count += 1 
            if count < 3:
                cordinates.append([i, j])

    for x, y in cordinates:
        if board[x][y] != 0:
            board[x][y] -= 1

def rotation(board, target_lv, sx, sy):
    whole_nemo = target_lv // 2
    # print()
    # print(f"({sx}, {sy}), ({ex}, {ey}), nemo: {whole_nemo}")

    for w in range(whole_nemo):
        r_sx, r_sy = sx + w, sy + w
        r_ex, r_ey = sx + target_lv - w - 1, sy + target_lv - w - 1
        length = r_ex - r_sx
        #print(f"({r_sx}, {r_sy}), ({r_ex}, {r_ey}), length: {length}")

        # 윗줄 백업
        backup = [board[r_sx][r_sy + i] for i in range(length)]
        # 윗줄 채우기 = 왼쪽줄
        for i in range(length): board[r_sx][r_sy + i] = board[r_ex - i][r_sy]
        # 왼쪽줄 채우기 = 아랫줄
        for i in range(length): board[r_ex - i][r_sy] = board[r_ex][r_ey - i]
        # 아랫줄 채우기 = 오른쪽줄
        for i in range(length): board[r_ex][r_ey - i] = board[r_sx + i][r_ey]
        # 오른쪽줄 채우기 = 백업
        for i in range(length): board[r_sx + i][r_ey] = backup[i]

def turn_and_rotation(board, level, target_lv, sx, sy):
    if level == target_lv:
        # print(f"({sx}, {sy}), ({ex}, {ey}), length: {cur_lv}")
        rotation(board, target_lv, sx, sy)
        return

    len = level // 2 
    # 왼위 사각형
    turn_and_rotation(board, level // 2, target_lv, sx, sy)
    # 왼아 사각형
    turn_and_rotation(board, level // 2, target_lv, sx + len, sy)
    # 오위 사각형
    turn_and_rotation(board, level // 2, target_lv, sx, sy + len)
    # 오아 사각형
    turn_and_rotation(board, level // 2, target_lv, sx + len, sy + len)

def solution():
    global N, board
    N, Q = map(int, input().split())

    for _ in range(2**N):
        board.append(list(map(int, input().split())))

    levels = list(map(int, input().split()))
    
    # 0. Q번 파이어스톰 시전
    for turn in range(Q):
        # 1. 구역 나누기 -> 재귀 호출, 분할 후 90도 회전
        level = levels[turn]
        turn_and_rotation(board, int(2**N), int(2**level), 0, 0)
        # print('-'*100)
        # if turn == 1:
        #     debug(board)
        #     exit(0)
        # 2. 얼음 녹기
        melting(N, board)

    # debug(board)  

    # 3. 가장 큰 얼음 찾기 & 4. 남은 얼음 합구하기
    max_ice = 0
    remain_ice = 0
    visited = [[False]*(2**N) for _ in range(2**N)]
    for i in range(2**N):
        for j in range(2**N):
            if board[i][j] != 0 and not visited[i][j]:
                ice_group, kan = search_big_ice(board, visited, i, j)
                max_ice = max(max_ice, kan)
                remain_ice += ice_group

    return max_ice, remain_ice


if __name__ == "__main__":
    max_ice, remain_ice = solution()
    print(remain_ice)
    print(max_ice)

'''
3 1
1 2 3 4 1 2 3 4
9 10 11 12 9 10 11 12
17 18 19 20 17 18 19 20
25 26 27 28 25 26 27 28
1 2 3 4 1 2 3 4
9 10 11 12 9 10 11 12
17 18 19 20 17 18 19 20
25 26 27 28 25 26 27 28
1

2 1
1 2 3 4
5 6 7 8
9 10 11 12
12 14 15 16
1

3 1
1 2 3 4 5 6 7 8
8 7 6 5 4 3 2 1
1 2 3 4 5 6 7 8
8 7 6 5 4 3 2 1
1 2 3 4 5 6 7 8
8 7 6 5 4 3 2 1
1 2 3 4 5 6 7 8
8 7 6 5 4 3 2 1
1

3 2
1 2 3 4 5 6 7 8
8 7 6 5 4 3 2 1
1 2 3 4 5 6 7 8
8 7 6 5 4 3 2 1
1 2 3 4 5 6 7 8
8 7 6 5 4 3 2 1
1 2 3 4 5 6 7 8
8 7 6 5 4 3 2 1
1 2

3 3
1 2 3 4 5 6 7 8
8 7 6 5 4 3 2 1
1 2 3 4 5 6 7 8
8 7 6 5 4 3 2 1
1 2 3 4 5 6 7 8
8 7 6 5 4 3 2 1
1 2 3 4 5 6 7 8
8 7 6 5 4 3 2 1
1 2 0

3 4
1 2 3 4 5 6 7 8
8 7 6 5 4 3 2 1
1 2 3 4 5 6 7 8
8 7 6 5 4 3 2 1
1 2 3 4 5 6 7 8
8 7 6 5 4 3 2 1
1 2 3 4 5 6 7 8
8 7 6 5 4 3 2 1
1 2 0 3

3 6
1 2 3 4 5 6 7 8
8 7 6 5 4 3 2 1
1 2 3 4 5 6 7 8
8 7 6 5 4 3 2 1
1 2 3 4 5 6 7 8
8 7 6 5 4 3 2 1
1 2 3 4 5 6 7 8
8 7 6 5 4 3 2 1
1 2 0 3 2 1

3 7 
1 2 3 4 5 6 7 8
8 7 6 5 4 3 2 1
1 2 3 4 5 6 7 8
8 7 6 5 4 3 2 1
1 2 3 4 5 6 7 8
8 7 6 5 4 3 2 1
1 2 3 4 5 6 7 8
8 7 6 5 4 3 2 1
1 2 0 3 2 1 2

3 8
1 2 3 4 5 6 7 8
8 7 6 5 4 3 2 1
1 2 3 4 5 6 7 8
8 7 6 5 4 3 2 1
1 2 3 4 5 6 7 8
8 7 6 5 4 3 2 1
1 2 3 4 5 6 7 8
8 7 6 5 4 3 2 1
1 2 0 3 2 1 2 3

3 9
1 2 3 4 5 6 7 8
8 7 6 5 4 3 2 1
1 2 3 4 5 6 7 8
8 7 6 5 4 3 2 1
1 2 3 4 5 6 7 8
8 7 6 5 4 3 2 1
1 2 3 4 5 6 7 8
8 7 6 5 4 3 2 1
1 2 0 3 2 1 2 3 2
'''