"""
BAEKJUN 23288.py 주사위 굴리기2

Description:
    BAEKJUN 23288.py 주사위 굴리기2 알고리즘 문제 풀이

    역시 핵심은 주사위를 어떻게 잘 굴릴것인가?
    점수획득은 간단한 BFS 탐색으로 해결이 가능하다.

    *주의*
    - 순서 주의 하자!! (방향 전환 후 주사위를 굴려야해)

Author:
    Name: KyungHyun Lim
    Email: lkh1075@gmail.com
"""

from collections import deque

def roll_dice(dice, d):
    #오위왼아
    if d == 0:
        change_dice_value(dice, 2, 1)
    elif d == 1:
        change_dice_value(dice, 3, 4)
    elif d == 2:
        change_dice_value(dice, 1, 2)
    else:
        change_dice_value(dice, 4, 3)

def change_dice_value(dice, l, r):
    dice[l] = dice[0]
    dice[0] = dice[r]
    dice[r] = 7 - dice[l]

def bfs(board, dx, dy, N, M, x, y):
    visited = [[False] * M for _ in range(N)]
    number = board[x][y]
    count = 1

    q = deque()
    q.append((x, y))
    visited[x][y] = True
    
    while q:
        cur_x, cur_y = q.popleft()
        for i in range(4):
            nx, ny = cur_x + dx[i], cur_y + dy[i]
            if 0 <= nx < N and 0 <= ny < M:
                if (not visited[nx][ny]) and board[nx][ny] == number:
                    q.append((nx, ny))
                    visited[nx][ny] = True
                    count += 1
    return count


def solution():
    N, M, K = map(int, input().split())
    board = [list(map(int, input().split())) for i in range(N)]
    
    # 오위왼아
    dx = [0, -1, 0, 1]
    dy = [1, 0, -1, 0]

    dice = [1, 4, 3, 2, 5]

    answer = 0
    d = 0
    x, y = 0, 0
    for i in range(K):
        # 0. 막힌곳이면 방향 재조정
        nx, ny = x + dx[d], y + dy[d]
        if not (0 <= nx < N and 0 <= ny < M):
            d = (d + 2) % 4
            nx, ny = x + dx[d], y + dy[d]

        # 1. 주사위 굴리기
        roll_dice(dice, d)     

        # 2. 점수 계산
        value = board[nx][ny]
        count = bfs(board, dx, dy, N, M, nx, ny)
        dice_value = 7 - dice[0]
        answer += (value * count)

        # 3. 이동 방향 결정
        if dice_value > value:
            d = (d + 3) % 4
        elif dice_value < value:
            d = (d + 1) % 4

        # 4. 좌표값 업데이트
        x, y = nx, ny
    return answer

def test_print(board):
    for item in board:
        print(item)

def main():
    answer = solution()
    print(answer)

if __name__ == '__main__':
    main()