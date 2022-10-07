"""
BAEKJUN 14499.py 주사위 굴리기

Description:
    BAEKJUN 14499.py 주사위 굴리기 알고리즘 문제 풀이

    주사위만 잘 굴리면 어렵지 않은 문제...
    주사위를 잘 굴리기가 생각보다 어렵다.

Author:
    Name: KyungHyun Lim
    Email: lkh1075@gmail.com
"""

def roll_dice(dice, d):
    if d == 1:
        dice[1], dice[3], dice[4], dice[6] = dice[3], dice[6], dice[1], dice[4]
    elif d == 2:
        dice[1], dice[3], dice[4], dice[6] = dice[4], dice[1], dice[6], dice[3]
    elif d == 3:
        dice[1], dice[2], dice[5], dice[6] = dice[2], dice[6], dice[1], dice[5]
    elif d == 4:
        dice[1], dice[2], dice[5], dice[6] = dice[5], dice[1], dice[6], dice[2]

def solution():
    dice = [0 for _ in range(7)]

    dx = [0, 0, 0, -1, 1]
    dy = [0, 1, -1, 0, 0]

    N, M, x, y, K = map(int, input().split())
    board = [[0]*M for _ in range(N)]
    for i in range(N):
        board[i] = list(map(int, input().split())) 

    orders = list(map(int, input().split()))

    for order in orders:
        # 1. 이동 좌표 확인
        nx = x + dx[order]
        ny = y + dy[order]

        # 2. 지도 안쪽이면 진행
        if 0 <= nx < N and 0 <= ny < M:
            # 주사위 굴리기
            roll_dice(dice, order)

            # 보드 값이 0이면 주사위값 복사, 0이 아니면 주사위로 값 복사
            if board[nx][ny] == 0:
                board[nx][ny] = dice[6]
            else:
                dice[6] = board[nx][ny]
                board[nx][ny] = 0

            print(dice[1])
            
            x, y = nx, ny
    
def main():
    solution()

if __name__ == '__main__':
    main()