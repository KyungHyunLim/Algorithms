"""
BAEKJUN 21611.py 마법사 상어와 블리자드

Description:
    BAEKJUN 21611.py 마법사 상어와 블리자드 알고리즘 문제 풀이

    NxN 크기 격자에서 마법실험 (N은 항상 홀수)
    가장 위 왼쪽칸은 (1, 1) 가장 아래 오른쪽칸은 (N, N)
    마법사 상어는 [ (N+1)/2, (N+1)/2 ]에 있음

    상어칸 제외 구슬이 하나씩 존재 (1, 2, 3)번 구슬 있음

    0. 소용돌이 모양 1차원 배열로 변경하기!!
    1. 블리자드 마법 시전 (d, s), 4가지 방향(상하좌우=1234)
         d 방향, 거리 s 이하인 모든 칸에 얼음 파편을 던져 구슬 파괴 (빈칸됨)
    2. 빈칸 채우기
    3. 4개이상 연속으로 같은 구슬이 있으면 연속구슬폭발
    4. 빈칸 채우기
    5. 구슬 생성

    M번 시전후
    최종 점수: 1x(폭발한 1번구슬개수) + 2x(2번구슬개수) + 3x(3번구슬개수)

Author:
    Name: KyungHyun Lim
    Email: lkh1075@gmail.com
"""

N, M, magics, board, answer = 0, 0, [], [], 0
cordonate_dict = {}

def make_linear_baord(temp_board):
    global board, cordonate_dict

    # 소용돌이 모양 생성용 움직임 칸수
    mx, my = [[1, 0, -1, 0], [0, 1, 0, -1]]
    move = [1]
    for _ in range(2, N):
        move.append(_)
        move.append(_)
    move.append(_) # 마지막은 한번더 이동

    # 초기값 셋팅
    x, y = (N+1)//2 - 1, (N+1)//2 - 2
    cordonate_dict[(x, y)] = 0
    board.append(temp_board[x][y])
    idx = 1
    d = 0
    for m in move:
        for _ in range(m):
            x, y = x + mx[d], y + my[d]
            cordonate_dict[(x, y)] = idx
            board.append(temp_board[x][y])
            idx += 1
        d = (d + 1) % 4

def blizard(s, d):
    global N, cordonate_dict
    x, y = int((N-1) / 2), int((N-1) / 2)
    # 1, 2, 3, 4 = 상, 하, 좌, 우
    dx, dy = [[0, -1, 1, 0, 0], [0, 0, 0, -1, 1]]
    for _ in range(s):
        x, y = x + dx[d], y + dy[d]
        board[cordonate_dict[(x, y)]] = -1

def remove_empty():
    global board

    empty_cnt = board.count(-1)
    board = [v for v in board if v != -1]
    board.extend([0]*empty_cnt)

def boom():
    global board, answer

    cur = board[0]
    cnt = 1
    flag = False

    for idx, v in enumerate(board[1:]):
        if v == cur:
            cnt += 1
        else:
            if cnt >= 4:
                flag = True
                answer += (cur * cnt)
                for i in range(idx - cnt + 1, idx + 1):
                    board[i] = -1
            if v == 0: break
            cur = v
            cnt = 1
        
    return flag               

def generate_beeds():
    global board, N

    new_board = []
    cnt = 0
    for v in board:
        if cnt == 0:
            cur = v
            cnt += 1
        elif cur == v:
            cnt += 1
        else:
            if len(new_board) == N**2 - 2:
                new_board.append(cnt)
            elif len(new_board) == N**2 - 1:
                break
            else:
                new_board.append(cnt)
                new_board.append(cur)
            cnt = 1
            cur = v
    
    board = [0] * (N**2)
    for idx, v in enumerate(new_board):
        if idx == N**2: break
        board[idx] = new_board[idx]

def solution():
    global N, M, magics, board, cordonate_dict

    
    N, M = map(int, input().split())
    
    temp_board = []
    for _ in range(N):
        temp_board.append(list(map(int, input().split())))

    for _ in range(M):
        magics.append(list(map(int, input().split())))
    
    make_linear_baord(temp_board)    

    for i in range(M):
        # 1. 블리자드 마법 시전 (d, s), 4가지 방향(상하좌우=1234)
        d, s = magics[i]
        blizard(s, d)
       
        # print(f'블리자드 마법 시전 후 {d}, {s}')
        # print(board)
        # print('-'*100)
        
        # 2. 빈칸을 채우기
        remove_empty()

        # print(f'빈칸을 채우기 후')
        # print(board)
        # print('-'*100)

        # 3. 구슬 폭파하기
        while True:
            if not boom(): break
            # print(f'구슬 폭파 후  {answer}')
            # print(board)
            # print('-'*100)

            # 4. 빈칸채우기
            remove_empty()
            # print(f'빈칸을 채우기 후')
            # print(board)
            # print('-'*100)
        
        # 5. 구슬 생성
        generate_beeds()

        # print(f'구슬 생성 후')
        # print(board)
        # print('-'*100)

if __name__ == "__main__":
    solution()
    print(answer)


'''
7 4
1 1 1 2 2 2 3
1 2 2 1 2 2 3
1 3 3 2 3 1 2
1 2 2 0 3 2 2
3 1 2 2 3 2 2
3 1 2 1 1 2 1
3 1 2 2 2 1 1
1 3
2 2
3 1
4 3

7 7
1 1 1 2 2 2 3
1 2 2 1 2 2 3
1 3 3 2 3 1 2
1 2 2 0 3 2 2
3 1 2 2 3 2 2
3 1 2 1 1 2 1
3 1 2 2 2 1 1
1 3
2 2
3 1
4 3
1 3
1 1
1 3

9 1
0 0 0 0 0 0 0 0 0
3 2 1 3 1 3 3 3 0
1 3 3 3 1 3 3 1 0
0 2 2 2 1 2 2 1 0
0 1 2 1 0 2 2 1 0
0 3 3 1 1 2 2 2 0
0 3 3 3 1 1 1 2 0
0 1 1 1 3 3 3 2 0
0 0 0 0 0 0 0 0 0
1 3
'''