"""
BAEKJUN 21609.py 상어 중학교

Description:
    BAEKJUN 21609.py 상어 중학교 알고리즘 문제 풀이

    NxN 크기 격자에서 진행되는 게임.
    블록은 검은색(-1), 무지개(0), 일반 블록(M가지 색상-1~M) 존재
    상하좌우를 인접한 칸이라 정의

    블록 그룹 
        - 인접한 블록의 집합 
        - 일반블록이 적어도 하나 필요
        - 일반 블록의 색은 모두 같아야함
        - 검은색 블록은 포함하면 안됨
        - 무지개 블록은 여러개 있을 수 있음
        - 총 블록수는 2 이상이어야함
        - 그룹의 메인 블록
            - 무지개 블록이 아닌 블록
            - 1 순위 행의 번호가 가장 작은 블록
            - 2 순위 열의 번호가 가장 작은 블록

    중력 작용
        - 검은색 블록을 제외, 모든 블록이 행의 번호가 큰칸으로 이동
        - 다른 블록이나 격자의 경계를 만나기 전까지 계속 이동

    게임 플레이
        1. 크기가 가장 큰 블록 그룹을 찾는다. (기준은 다음과 같음)
            - 블록 크기
            - 무지개 블록 수
            - 메인 블록 행이 가장 큰 것
            - 메인 블록 열이 가장 큰 것
        2. 1에서 찾은 블록 그룹의 모든 블록(B개) 제거 (B^2의 점수 획득)
        3. 격자에 중력 작용
        4. 90도 반시계 방향 회전
        5. 다시 격자에 중력이 작용


Author:
    Name: KyungHyun Lim
    Email: lkh1075@gmail.com
"""

from collections import deque

def rotation(N, board):
    nemo_cnt = N // 2
    sx, sy, ex, ey = 0, 0, N-1, N-1
    length = N - 1
    for nemo in range(nemo_cnt):
        #print(sx, sy, ex, ey, length)

        backup = [board[sx][sy + i] for i in range(length)]
        for i in range(length): board[sx][sy + i] = board[sx + i][ey]
        for i in range(length): board[sx + i][ey] = board[ex][ey - i]
        for i in range(length): board[ex][ey - i] = board[ex - i][sy]
        for i in range(length): board[ex - i][sy] = backup[i]

        length -= 2
        sx, sy = sx + 1, sy + 1
        ex, ey = sx + length, sy + length

def apply_gravity(N, board):
    for i in range(N-2, -1, -1):
        for j in range(N):
            if board[i][j] != -1:
                tmp = i
                while tmp + 1 < N and board[tmp+1][j] == -5:
                    board[tmp+1][j] = board[tmp][j]
                    board[tmp][j] = -5
                    tmp += 1

def remove_block(board, block_info):
    for x, y in block_info['blocks']:
        board[x][y] = -5

def search(N, board, visited, x, y):
    dx, dy = [[0, 0, 1, -1], [-1, 1, 0, 0]]

    q = deque()
    q.append((x, y))

    color = board[x][y]

    blocks = [(x, y)]
    rainbows = []

    while q:
        cur_x, cur_y = q.popleft()

        for d in range(4):
            nx, ny = cur_x + dx[d], cur_y + dy[d]
            if 0 <= nx < N and 0 <= ny < N:
                # 방문한적 없고, 무지개 색이나 타겟 색일 경우
                if (not visited[nx][ny]) and (board[nx][ny] in [0, color]):
                    q.append((nx, ny))
                    visited[nx][ny] = True
                    # 그룹에 포함된 무지개색 블록 따로 저장
                    if board[nx][ny] == 0: 
                        rainbows.append((nx, ny))
                    else:
                        # 그룹에 포함된 일반 블록 저장
                        blocks.append((nx, ny))

    for x, y in rainbows:
        visited[x][y] = False

    return rainbows, blocks
    
def find_block(N, board):
    visited = [[False]*N for _ in range(N)]

    big_block = {
        "size": 0,
        "rainbow_size": 0,
        "main_col": 0,
        "main_row": 0,
        "blocks": []
    }
    for i in range(N):
        for j in range(N):
            # 그룹에 포함(방문하지) 않았고, 검은색 또는 무지개색이 아니면
            if (not visited[i][j]) and (board[i][j] not in [-1, 0, -5]):
                flag = False
                visited[i][j] = True
                rainbows, blocks = search(N, board, visited, i, j)
            
                rainbow_counts = len(rainbows)
                whole_counts = len(blocks) + rainbow_counts
                col, row = sorted(blocks)[0]

                if big_block['size'] < whole_counts:
                    flag = True
                elif big_block['size'] == whole_counts:
                    if big_block['rainbow_size'] < rainbow_counts:
                        flag = True
                    elif big_block['rainbow_size'] == rainbow_counts:
                        if big_block['main_col'] < col:
                            flag = True
                        elif big_block['main_col'] == col:
                            if big_block['main_row'] < row:
                                flag=True
                
                if flag:
                    big_block['size'] = whole_counts
                    big_block['rainbow_size'] = rainbow_counts
                    big_block['main_col'] = col
                    big_block['main_row'] = row
                    big_block['blocks'] = blocks + rainbows
    
    return big_block

def debug(board):
    for item in board:
        print(item)

def solution():
    # 격자 크기, 색상 개수
    answer = 0
    N, M = map(int, input().split())

    board = []
    for _ in range(N):
        board.append(list(map(int, input().split())))

    while True:
        block_info = find_block(N, board) # 큰 블록 찾기
        # print(block_info)
        # print('-'*100)
        
        if block_info['size'] <= 1: # 블록이 존재할때 까지 반복
            break
        answer += (block_info['size']**2)
        
        remove_block(board, block_info) # 블록 제거

        # debug(board)
        # print('-'*50)

        apply_gravity(N, board) # 중력 작용

        # debug(board)
        # print('-'*50)

        rotation(N, board) # 90도 반시계 회전S

        # debug(board)
        # print('-'*50)

        apply_gravity(N, board) # 중력 작용

        # debug(board)
        # print('-'*50)
        
    return answer

if __name__ == "__main__":
    answer = solution()
    print(answer)
    
    # gravity test
    # board = [
    #     [2, 1, 2, 3, 4],
    #     [2, 1, -5, -5, 4],
    #     [-5, -5, 2, 3, -5],
    #     [-5, -1, -5, -1, -1],
    #     [-5, -5, -5, -5, -5],
    # ]
    # apply_gravity(5, board)
    # debug(board)