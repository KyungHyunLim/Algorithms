"""
BAEKJUN 23291.py 어항 정리

Description:
    BAEKJUN 23291.py 어항 정리 알고리즘 문제 풀이

    어항 = 정육면체 모양, 한변의 길이는 모두 1, N개의 어항을 가지고 있음
    어항에는 1마리 이상의 물고기 존재
    어항 8개가 바닥에 있는 상태 => [5, 2, 3, 14, 9, 2, 11, 8]

    1. 물고기의 수가 가장 적은 어항에 물고기를 한마리 넣는다. (여러개면 모두다 넣는다.)
        [5, 2, 3, 14, 9, 2, 11, 8] => [5, 3, 3, 14, 9, 3, 11, 8]
    2. 맨 왼쪽 어항을, 바로 오른쪽에 있는 어항에 쌓는다.
        [5]
        [3, 3, 14, 9, 3, 11, 8]
    3. 이제 두개 이상 쌓여있는 어항을, 시계방향으로 90도 회전시켜 쌓는다.
        공중 부향 시켜 쌓는 어항의 가장 오른쪽 아래가 비지 않을 때 까지 반복한다.
        [3, 5]
        [3, 14, 9, 3, 11, 8]
    4. 인접한 두 어항에 대해 물고기 차이를 5로 나눈 몫 d,
        d가 0보다 크면 물고기가 많은 곳에서 적은 곳으로 d 마리 이동
        이과정은 모든 칸에서 동시에 발생
    5. 어항을 다시 일열로 배치
        [5, 3]
        [10, 6]
        [9, 5, 10, 8] => [9, 10, 5, 5, 6, 3, 10, 8]
    6. 다시 공중 부양 작업
        가운데를 중심으로 왼쪽 N/2개를 공중 부양시켜, 시계방향으로 180도 회전시켜 놓는다. 2번 반복
                                                        [3, 6]
                                                        [5, 5]
                                      [5, 5, 10, 9]     [10, 9]
        [9, 10, 5, 5, 6, 3, 10, 8] => [6, 3, 10, 8] =>  [10, 8]
    7. 물고기 정리 (4와 동일)
    8. 일렬로 다시 배치

    물고기가 가장 많이 들어있는 어항과 가장 적게 들어있는 어항의 차이가 K 이하가 되려면
    정리를 몇번 반복해야 할까?

    4 ≤ N ≤ 100
    N은 4의 배수
    0 ≤ K ≤ 10
    1 ≤ 각 어항에 들어있는 물고기의 수 ≤ 10,000

Author:
    Name: KyungHyun Lim
    Email: lkh1075@gmail.com
"""

def linearize(N, fish_bowls):
    l = []

    for j in range(1, N):
        for i in range(N-1, -1, -1):
            if fish_bowls[i][j] > 0:
                l.append(fish_bowls[i][j])

    fish_bowls[N-1] = l

def arrange_fishs(N, fish_bowls, max_fish_count, min_fish_count):
    diff_fish_bowls = [[0] * N for _ in range(N)]

    dx, dy = [[0,0,1,-1], [1,-1,0,0]]
    for x in range(N-1, -1, -1):
        for y in range(N):
            if fish_bowls[x][y] > 0:
                for d in range(4):
                    nx, ny = x+dx[d], y+dy[d]
                    if 0 <= nx < N and 0 <= ny < N and fish_bowls[nx][nx] > 0:
                        diff = abs(fish_bowls[x][y] - fish_bowls[nx][nx]) // 5
                        if diff > 0:
                            if fish_bowls[nx][nx] > fish_bowls[x][y]:
                                diff_fish_bowls[nx][nx] -= diff
                                diff_fish_bowls[x][y] += diff

    for x in range(N):
        for y in range(N):
            fish_bowls[x][y] += diff_fish_bowls[x][y]
            if min_fish_count > fish_bowls[x][y]:
                min_fish_count = fish_bowls[x][y]
            if max_fish_count < fish_bowls[x][y]:
                max_fish_count = fish_bowls[x][y]

    return max_fish_count, min_fish_count

def folding_bowls(N, fish_bowls):
    d = N//4
    candis = [fish_bowls[N-1][i: i+d] for i in range(0, N-d, d)]
    fish_bowls[N-1][:N-d] = [0]*(N-d)

    for idx, candi in enumerate(candis):
        if idx != 1:
            candi.reverse()
        fish_bowls[N-2-idx][N-d:] = candi

def rotate_bowls(N, fish_bowls):
    
    pass

def debug(fish_bowls):
    for item in fish_bowls:
        print(item)

def solution():
    answer = 0

    N, K = map(int, input().split())
    fish_bowl = list(map(int, input().split()))

    fish_bowls = [[0] * N for _ in range(N)]
    
    min_fish_count = 10010
    max_fish_count = 0
    for i in range(N):
        fish_bowls[N-1][i] = fish_bowl[i]
        if min_fish_count > fish_bowl[i]:
            min_fish_count = fish_bowl[i]
        if max_fish_count < fish_bowl[i]:
            max_fish_count = fish_bowl[i]

    if max_fish_count - min_fish_count <= K:
        return 0

    count = 0
    while True:
        # 1. 가장 적은 물고기 수에 물고기 넣기 O(N)
        for i in range(N):
            if fish_bowls[N-1][i] == min_fish_count:
                fish_bowls[N-1][i] += 1
        
        # 2. 왼쪽 어항 오른쪽 어항 위로 O(1)
        fish_bowls[N-2][1] = fish_bowls[N-1][0]
        fish_bowls[N-1][0] = 0

        # 3. 어항 공중부양해서 쌓기
        rotate_bowls(N, fish_bowls)

        # 4. 물고기 정리 (최소 최대값 업데이트) O(N*N*4 + N*N)
        max_fish_count, min_fish_count = arrange_fishs(N, fish_bowls, max_fish_count, min_fish_count)

        # 5. 어항 일렬로 만들기
        linearize(N, fish_bowls)

        # 6. 2번 접기
        folding_bowls(N, fish_bowls)

        # 7. 물고기 정리
        max_fish_count, min_fish_count = arrange_fishs(N, fish_bowls, max_fish_count, min_fish_count)

        # 8. 어항 일렬로 만들기
        linearize(N, fish_bowls)

        count += 1
        if max_fish_count - min_fish_count <= K:
            return count

if __name__ == "__main__":
    # answer = solution()
    # print(answer)
    
    # folding test
    fish_bowls = [
        [0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0],
        [1,2,3,4,5,6,7,8,9,10,11,12],
    ]
    
    print("fold case # 1")
    folding_bowls(12, fish_bowls)
    debug(fish_bowls)
    print()

    fish_bowls = [
        [0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0],
        [1,2,3,4,5,6,7,8]
    ]

    print("fold case # 2")
    folding_bowls(8, fish_bowls)
    debug(fish_bowls)
    print()

    fish_bowls = [
        [0,0,0,0],
        [0,0,0,0],
        [0,0,0,0],
        [1,2,3,4]
    ]
    print("fold case # 3")
    folding_bowls(4, fish_bowls)
    debug(fish_bowls)
    print()
