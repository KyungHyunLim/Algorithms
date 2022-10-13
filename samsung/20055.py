"""
BAEKJUN 20055.py 컨베이어 벨트 위의 로봇

Description:
    BAEKJUN 20055.py 컨베이어 벨트 위의 로봇 알고리즘 문제 풀이

    길이 N인 컨베이어 벨트, 길이 2N인 벨트가 감싸서 돌고 있음
    벨트는 2N개의 칸으로 분리 되어있음 (1~2N 넘버링)
    1번이 올리는 위치, N번이 내리는 위치

    컨베이어 벨트에 로봇을 올림(올리는 위치에만 둘 수 있음)
    내리는 위치에 도달하면 로봇은 내림
    로봇은 컨베이어 벨트 위에서 움직일 수 있음
    로봇이 올리는 위치에 올라가거나, 이동하면 그 칸의 내구도가 1 감소

    1. 벨트가 각 칸 위에 있는 로봇과 함께 회전
    2. 가장 먼저 벨트에 올라간 로봇부터, 벨트가 회전하는 방향으로 한칸 이동, 못움직이면 이동 X
        - 내구도가 있어야 이동 가능
    3. 올리는 위치에 있는 칸의 내구도가 0아니면 올리는 위치에 로봇을 올린다.
    4. 내구도가 0인 칸의 개수가 K개 이상이라면 과정을 종료한다. 아니면 1번으로 돌아간다.

    종료되었을 때 몇 번째 단계가 진행 중이었는가?

Author:
    Name: KyungHyun Lim
    Email: lkh1075@gmail.com
"""

from collections import deque

def move_robot(N, robot, belt):
    count = 0
    for idx in range(N-2, -1, -1): # 가장 먼저 올라간 로봇부터 이동
        if robot[idx] and not robot[idx+1] and belt[idx+1]:
            belt[idx+1] -= 1
            if belt[idx+1] == 0: count += 1
            robot[idx+1], robot[idx] = robot[idx], 0
    robot[N-1] = 0
    return count

def solution():
    N, K = map(int, input().split())
    
    belt = deque(list(map(int, input().split())))
    robot = deque([0]*N)
    zero_count = 0
    step = 1

    while True:
        # 1. 벨트 회전
        belt.rotate(1)
        robot.rotate(1) # 로봇도 벨트와 같이 이동
        robot[N-1] = 0 # 로봇 내려감

        # 2. 로봇 이동
        count = move_robot(N, robot, belt)
        zero_count += count

        # 3. 로봇 올리기
        if not robot[0] and belt[0]:
            robot[0] = 1
            belt[0] -= 1
        
        # 4. 내구도 확인
        if belt.count(0) >= K:
            break

        step += 1

    return step

if __name__=="__main__":
    answer = solution()
    print(answer)
    