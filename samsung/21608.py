"""
BAEKJUN 21608.py 상어 초등학교

Description:
    BAEKJUN 21608.py 상어 초등학교 알고리즘 문제 풀이

    NxN 크기 교실, 학생의 수는 N**2 명
    (1,1) ~ (r, c)
    |r1 - r2| + |c1 - c2| = 1을 만족해야 인접하다고 할 수 있음

    1. 비어있는 칸 중에서 좋아하는 학생이 인접한 칸에 가장 많은 칸으로 자리 정함
    2. 1을 만족하는 칸이 여러개이면, 인접한 칸 중에서 비어있는 칸이 가장 많은 칸으로 자리 정함
    3. 2를 만족하는 칸이 여러개이면, 행의 번호가 가장 작은 칸으로, 그것도 많으면, 열의 번호가 가장 작은 칸으로 자리 정함

    우선순위: 좋아하는 학생이 많은칸 -> 비어있는 칸이 많은 칸 -> 행번호가 작은칸 -> 열번호가 작은칸

    학생 순서마다, 
        1. 각 칸의 정보 저장 (좋아하는 학생 수, 비어있는 칸수, 행번호, 열번호)
        2. 정렬
        3. 자리배치
        4. 모든 학생이 앉을 때 까지, 1-3 반복

    3 ≤ N ≤ 20
    
    학생 만족도 구하기
    인접한 칸에 좋아하는 학생의 수 0= 0, 1= 1, 2= 10, 3= 100, 4= 1000

    학생 만족도의 총합은?

Author:
    Name: KyungHyun Lim
    Email: lkh1075@gmail.com
"""
N, order, prefer, board = 0, [], {}, []
dx, dy = [[0, 0, 1, -1], [1, -1, 0, 0]]

def get_candidate(board, student):
    global N, prefer, dx, dy   
    
    seats = []
    for i in range(N):
        for j in range(N):
            vacn_count = 0
            pref_count = 0
            if board[i][j] == 0: # 빈자리 일때만
                for _ in range(4): # 4 방향 탐색
                    nx, ny = i + dx[_], j + dy[_]
                    if 0 <= nx < N and 0 <= ny < N: # 격자 안에서만 탐색
                        if board[nx][ny] == 0: vacn_count += 1 # 0이면 빈공간
                        if board[nx][ny] in prefer[student]: pref_count += 1 # 좋아하는 학생?

                seats.append((-pref_count, -vacn_count, i, j))

    return sorted(seats)

def debug(board):
    for item in board:
        print(item)

def solution():
    global N, order, prefer, board, dx, dy
    answer = 0
    score_dict = {0: 0, 1: 1, 2: 10, 3: 100, 4: 1000}

    N = int(input())

    for _ in range(N*N):
        infos = list(map(int, input().split()))
        prefer[infos[0]] = infos[1:]
        order.append(infos[0])

    board = [[0]*N for _ in range(N)]
    # 첫번째 학생은 무조건 (1, 1)위치에 앉게됨 (비어있는 칸수가 4개인 자리중 행,열이 가장 작은 곳)
    board[1][1] = order[0]

    # 1. 학생들을 차례대로 앉히기
    for i in order[1:]:
        # 각 자리에 대한 (좋아하는 학생 수, 비어있는 칸수, 행번호, 열번호) 정보 저장
        candidates = get_candidate(board, i)

        # 학생배치
        x, y = candidates[0][2], candidates[0][3]

        # print(f'배치완료! {i}: ({x}, {y})')
        # print(candidates)
        # debug(board)
        # print('-'* 100)

        board[x][y] = i

    # debug(board)

    # 2. 만족도 점수 계산하기
    for i in range(N):
        for j in range(N):
            student = board[i][j]
            pref_count = 0
            for _ in range(4):
                nx, ny = i + dx[_], j + dy[_]
                if 0 <= nx < N and 0 <= ny < N: # 격자 안에서만 탐색
                    if board[nx][ny] in prefer[student]:
                        pref_count += 1
            answer += (score_dict[pref_count])

    return answer

if __name__ == "__main__":
    answer = solution()
    print(answer)

