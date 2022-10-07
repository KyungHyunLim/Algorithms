"""
BAEKJUN 13460.py 구슬탈출2

Description:
    BAEKJUN 13460.py 구슬탈출2 알고리즘 문제 풀이

    BFS 탐색을 활용
    4방향으로 움직였을 경우 변화를 이용해 탐색

Author:
    Name: KyungHyun Lim
    Email: lkh1075@gmail.com
"""

import sys
from collections import deque, defaultdict

def test_print(board, rx, ry, bx, by):
    N, M = len(board), len(board[0])
    for i in range(N):
        temp = ""
        for j in range(M):
            if i == rx and j == ry:
                temp += 'R'
            elif i == bx and j == by:
                temp += 'B'
            else:
                temp += board[i][j]
        print(temp)

def bfs(board, rx, ry, bx, by, hx, hy):
    # 이동 방향 상하좌우
    dx = [-1, 1, 0, 0]
    dy = [0, 0, -1, 1]

    visited = defaultdict(int)

    q = deque()
    q.append((rx, ry, bx, by, 0))
    visited[(rx, ry, bx, by)] = 1

    while q:
        crx, cry, cbx, cby, count = q.popleft()
        # test_print(board, crx, cry, cbx, cby) # 테스트용
        # print('-'*100)
        if count > 10: return -1
        if crx == hx and cry == hy: return count
        for i in range(4):
            nrx, nry = move_beeds(board, crx, cry, i) # 빨간구슬 움직이기
            nbx, nby = move_beeds(board, cbx, cby, i) # 파란구슬 움직이기
            if nbx == hx and nby == hy: continue # 파란색이 구멍에 빠지면 안됨
            if nrx == nbx and nry == nby: # 두 구슬의 위치가 같다면 더 많이 이동한 구슬이 한칸 뒤로 가야함
                if abs(nrx-crx) + abs(nry-cry) > abs(nbx-cbx) + abs(nby-cby):
                    nrx -= dx[i] # 빨간 구슬이 더 많이 움직였음으로 빨강이가 뒤로
                    nry -= dy[i]
                else:
                    nbx -= dx[i] # 파랑이가 뒤로
                    nby -= dy[i]
            if visited[(nrx, nry, nbx, nby)] != 1: # 한번도 방문하지 않은 상태라면 큐에 삽입
                q.append((nrx, nry, nbx, nby, count + 1)) # 새 시작점 및 움직인 횟수 증가
                visited[(nrx, nry, nbx, nby)] = 1

    return -1

def move_beeds(board, main_x, main_y, d):
    # 이동 방향 상하좌우
    dx = [-1, 1, 0, 0]
    dy = [0, 0, -1, 1]
    
    while True:
        main_x = main_x + dx[d]
        main_y = main_y + dy[d]
        try:
            if board[main_x][main_y] == '#':
                return main_x - dx[d], main_y - dy[d]
            if board[main_x][main_y] == 'O':
                return main_x, main_y
        except:
            print(main_x, main_y)
def solution():
    input = sys.stdin.readline

    # Board 정보
    N, M = map(int, input().split())
    board = [list(input().strip()) for i in range(N)]
    
    red_x, red_y = 0, 0
    blue_x, blue_y = 0, 0
    hole_x, hole_y = 0, 0 
    for i in range(N):
        for j in range(M):
            if board[i][j] == 'R':
                board[i][j] = '.'
                red_x, red_y = i, j
            elif board[i][j] == 'B':
                board[i][j] = '.'
                blue_x, blue_y = i, j
            elif board[i][j] == 'O':
                hole_x, hole_y = i, j

    return bfs(board, red_x, red_y, blue_x, blue_y, hole_x, hole_y)

def main():
    answer = solution()
    print(answer)

if __name__=='__main__':
    main()

'''
7 7
#######
#...RB#
#.#####
#.....#
#####.#
#O....#
#######
'''