"""
BAEKJUN 3190.py 뱀

Description:
    BAEKJUN 3190.py 뱀 알고리즘 문제 풀이

    deque 자료구조를 활용해 뱀을 표현 (머리가 늘어나고, 꼬리가 가만히 있거나 이동함)
    머리가 늘어나고 => deque.append([x, y])
    꼬리가 이동하고 => deque.popleft()

    #주의#
    - 시작좌표가 0,0 인지 1,1인지 잘보자

Author:
    Name: KyungHyun Lim
    Email: lkh1075@gmail.com
"""

from collections import deque

def solution():
    snake = deque() # 뱀
    snake.append([0, 0])

    # 상 우 하 좌
    dx = [-1, 0, 1, 0]
    dy = [0, 1, 0, -1]

    N = int(input()) # 보드판 크기

    APPLE = int(input()) # 사과개수
    apples = []
    for _ in range(APPLE):
        apples.append(list(map(int, input().split())))
    
    TIMES = int(input())
    times = []
    dirs = []
    for _ in range(TIMES):
        time, dir = list((map(str, input().split())))
        times.append(time)
        dirs.append(dir)

    d = 1 # 초기 방향은 오른쪽
    time_idx = 0
    answer = 0
    head_x, head_y = 1, 1
    while True:
        # 1. 뱀 머리 다음 좌표 계산
        next_head_x = head_x + dx[d]
        next_head_y = head_y + dy[d]
        
        # 2. 조건 검사 보드 밖을 벗어나거나 자기 몸에 닿으면 종료
        if (not (1 <= next_head_x <= N and 1 <= next_head_y <= N)) or [next_head_x, next_head_y] in snake:
            answer += 1
            return answer
        
        # 3. 뱀 머리 이동하기
        head_x, head_y = next_head_x, next_head_y
        snake.append([next_head_x, next_head_y])

        # 4. 사과 유무에 따라 처리
        if [next_head_x, next_head_y] not in apples: 
            # 사과가 없으면
            snake.popleft() # 꼬리 제거
        else: # 사과가 있으면 사과 제거하고 진행
            apples.remove([next_head_x, next_head_y])

        # 5. 시간 초 끝난후 방향전환
        answer += 1
        if time_idx < TIMES and answer == int(times[time_idx]):
            # 방향전환
            if dirs[time_idx] == 'D': # 오른쪽 90도 회전
                d = (d + 1) % 4
            else: # 왼쪽 90도 회전
                d = (d + 3) % 4
            time_idx += 1

def main():
    answer = solution()
    print(answer)

if __name__ == '__main__':
    main()