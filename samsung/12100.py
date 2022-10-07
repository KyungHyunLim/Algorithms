"""
BAEKJUN 12100.py 2048(Easy)

Description:
    BAEKJUN 12100.py 2048(Easy) 알고리즘 문제 풀이

    DFS 활용, 이동 가능한 경로를 끝까지(5회) 이동한 후 최대값 갱신

    #주의#
    - python의 경우 list, dict를 함수 인자로 줄경우 Object를 넘이기 때문에 Call by reference 처럼 작용한다.
    - DFS, BFS를 사용할 때 주의하자

Author:
    Name: KyungHyun Lim
    Email: lkh1075@gmail.com
"""

import sys
import copy
from collections import deque

def dfs(board, count, path):
    if count == 5: # 5번 움직였으면 최대값 반환
        find_max_value(board)
        return
    
    for d in range(4): # 움직일 수 있는 모든 가지수 탐색
        temp_board = [l[:] for l in board]#copy.deepcopy(board) #(안됨) #list(map(list, board)) # 현재 상태 복사 call by reference로 인한 문제 방지
        temp_board = move_block(temp_board, d) # 블록 옮기기
        dfs(temp_board, count + 1, path + str(d)) # 다음 행동 진행 path는 디버깅용

max_value = 0
def find_max_value(board):
    global max_value
    for values in board:
        temp = max(values)
        max_value = max(max_value, temp)

def place(q, board, sx, sy, dx, dy):
    before = -1
    
    while q:
        cur = q.popleft()
        if before == cur:
            board[sx - dx][sy - dy] *= 2
            board[sx][sy] = 0
            before = -1
        elif board[sx][sy] == 0:
            board[sx][sy] = cur
            before = cur
            sx += dx
            sy += dy
    return board

def move_block(board, d):
    # 상하좌우
    N = len(board)
    
    if d == 0:
        for j in range(N):
            q = deque()
            for i in range(N):
                if board[i][j] != 0:
                    q.append(board[i][j])
                    board[i][j] = 0
            board = place(q, board, 0, j, 1, 0)
    elif d == 1:
        for j in range(N):
            q = deque()
            for i in range(N-1, -1, -1):
                if board[i][j] != 0:
                    q.append(board[i][j])
                    board[i][j] = 0
            board = place(q, board, N-1, j, -1, 0)
    elif d == 2:
        for i in range(N):
            q = deque()
            for j in range(0, N):
                if board[i][j] != 0:
                    q.append(board[i][j])
                    board[i][j] = 0
            board = place(q, board, i, 0, 0, 1)
    else:
        for i in range(N):
            q = deque()
            for j in range(N-1, -1, -1):
                if board[i][j] != 0:
                    q.append(board[i][j])
                    board[i][j] = 0
            board = place(q, board, i, N-1, 0, -1)
    return board

def solution():
    input = sys.stdin.readline

    N = int(input())
    board = [list(map(int, input().split())) for _ in range(N)]
    dfs(board, 0, "") # 탐색 상하좌우 모든 가지수 5번

def test_print(board):
    for item in board:
        print(item)
    print('='*100)

def main():
    global max_value
    solution()
    print(max_value)

if __name__=='__main__':
    main()

'''
3
2 4 8
2 4 8
2 4 8
3
2 2 2
4 4 4
8 8 16
4
8 4 4 16
0 0 0 0
0 0 0 0
0 0 0 0
4
2 2 4 16
0 0 0 0
0 0 0 0
0 0 0 0
10
0 0 64 32 32 0 0 0 0 0
0 32 32 64 0 0 0 0 0 0
0 0 128 0 0 0 0 0 0 0
64 64 128 0 0 0 0 0 0 0
0 0 64 32 32 0 0 0 0 0
0 32 32 64 0 0 0 0 0 0
0 0 128 0 0 0 0 0 0 0
64 64 128 0 0 0 0 0 0 0
128 32 0 0 0 0 0 0 0 0
0 0 128 0 0 0 0 0 0 0
5
0 0 64 32 32
0 32 32 64 0
0 0 128 0 0
64 64 128 0 0
0 0 64 32 32
'''
# 상하좌우
# 우상우하상
# 30310