"""
BAEKJUN 23290.py 마법사 상어와 복제

Description:
    BAEKJUN 23290.py 마법사 상어와 복제 알고리즘 문제 풀이

    4x4 격자, 물고기 M마리 존재, 상어 1마리 존재
    물고기와 상어는 같은 곳에 있을 수 있고, 물고기 여러마리가 같은칸에 존재할 수 있음

    1. 복제 마법 시전 -> 5단계에서 추가됨
    2. 모든 물고기 한칸 이동
        - 상어, 냄새가 있는 칸, 격자 밖 이동 불가
        - 이동 불가시 45도 반시계 회전
        - 모두 불가면 가만히
    3. 상어 이동
        - 3칸 연속 이동 (상좌하우)
        - 격자를 벗어나면 안됨
        - 가능한 경로중 물고기가 가장 많은 경로 선택
        - 상어가 이동한 경로에 물고기는 사라지고, 냄새를 남김
    4. 두 번 전 연습에서 생긴 물고기의 냄새 사라짐
    5. 복제했던 물고기가 추가됨

    연습을 S번 반복

Author:
    Name: KyungHyun Lim
    Email: lkh1075@gmail.com
"""
# ←, ↖, ↑, ↗, →, ↘, ↓, ↙
fdx, fdy = [
    [0, -1, -1, -1, 0, 1, 1, 1],
    [-1, -1, 0, 1, 1, 1, 0, -1]]
sdx, sdy = [
    [-1, 0, 1, 0],
    [0, -1, 0, 1]]

max_cnt = 0
max_path = 0
shark = (0, 0)
def move_shark(fish_board, sx, sy, depth, cnt, visit):
    global shark, max_cnt, max_path, sdx, sdy
    if depth == 3:
        if cnt > max_cnt:
            max_cnt = cnt
            max_path = visit[:]
            shark = (sx, sy) 
        return
    
    for d in range(4):
        nsx, nsy = sx + sdx[d], sy + sdy[d]
        if 0 <= nsx < 4 and 0 <= nsy < 4:
            if (nsx, nsy) not in visit:
                visit.append((nsx, nsy))
                move_shark(fish_board, nsx, nsy, depth + 1, cnt + sum(fish_board[nsx][nsy]), visit)
                visit.pop()
            else:
                move_shark(fish_board, nsx, nsy, depth + 1, cnt, visit)

def move_fish(fish_board, smell_board, shark_x, shark_y):
    global fdx, fdy
    new_fish_board = [[[0] * 8 for _ in range(4)] for __ in range(4)]

    for x in range(4):
        for y in range(4):
            for d in range(8):
                if fish_board[x][y][d] > 0:
                    #print(f'({x}, {y}), {d}, am: {fish_board[x][y][d]}')
                    nd = d
                    flag = False
                    while True:
                        nx, ny = x + fdx[nd], y + fdy[nd]
                        #print(f'\tnon ({nx}, {ny}), {nd}')
                        if 0 <= nx < 4 and 0 <= ny < 4:
                            if smell_board[nx][ny] == 0:
                                if nx != shark_x or ny != shark_y:
                                    flag = True
                                    break
                        nd = (nd - 1) % 8
                        if d == nd: break
                    if flag:
                        # print(f'({x}, {y}), {d} move ({nx}, {ny}), {nd}')
                        new_fish_board[nx][ny][nd] += fish_board[x][y][d]
                    else:
                        # print(f'({x}, {y}), {d} non_move ({nx}, {ny}), {nd}')
                        new_fish_board[x][y][d] += fish_board[x][y][d]
    return new_fish_board

def eat(fish_board, smell_board):
    global max_path
    for x, y in max_path:
        if sum(fish_board[x][y]) > 0:
            fish_board[x][y] = [0]*8
            smell_board[x][y] = 3

def disappear_smell(smell_board):
    for x in range(4):
        for y in range(4):
            if smell_board[x][y] > 0: 
                smell_board[x][y] -= 1

def add_fish(fish_board, copied_fish):
    for x, y, d, cnt in copied_fish:
        fish_board[x][y][d] += cnt

def copy_fish(fish_board):
    copied_fish = []
    for x in range(4):
        for y in range(4):
            for d in range(8):
                if fish_board[x][y][d] > 0:
                    copied_fish.append((x, y, d, fish_board[x][y][d]))
    return copied_fish

def counting(fish_board):
    count = 0
    for x in range(4):
        for y in range(4):
            count += sum(fish_board[x][y])
    return count

def debug(fish_board):
    for item in fish_board:
        print(item)

def solution():
    global max_cnt, max_path, shark
    answer = 0
    fish_board = [[[0] * 8 for _ in range(4)] for __ in range(4)]
    smell_board = [[0] * 4 for _ in range(4)]

    M, S = map(int, input().split())
    for _ in range(M):
        x, y, d = map(int, input().split())
        fish_board[x-1][y-1][d-1] += 1
        
    shark_x, shark_y = map(int, input().split())
    shark_x, shark_y = shark_x-1, shark_y-1

    for s in range(S):
        # print(f"{s} init")
        # debug(fish_board)
        # print('-'*50)
        # 1. copy fish
        copied_fish = copy_fish(fish_board)
        # print(f"after copy fish")
        # print(copied_fish)
        # print('-'*50)

        # 2. move fish
        fish_board = move_fish(fish_board, smell_board, shark_x, shark_y)
        # print(f"after move fish")
        # debug(fish_board)
        # print('-'*50)

        # 3. move shark
        max_cnt = -1
        max_path = []
        shark = (-10, -10)
        move_shark(fish_board, shark_x, shark_y, 0, 0, list())
        eat(fish_board, smell_board)
        
        # print(f"after move shark")
        # print(f"({shark_x}, {shark_y}) -> ({shark[0]}, {shark[1]})")
        # print(max_path)
        # debug(fish_board)
        # print('-'*50)

        shark_x, shark_y = shark

        # 4. disappear smell
        disappear_smell(smell_board) 
        
        # print(f"after disappear smell")
        # debug(smell_board)
        # print('-'*50)

        # 5. add copied fish
        add_fish(fish_board, copied_fish)

        # print(f"after add copied fish")
        # debug(fish_board)
        # print('-'*50)
        # print('Next!')

    answer = counting(fish_board)
    return answer

if __name__ == "__main__":
    answer = solution()
    print(answer)

'''
5 1
4 3 5
1 3 5
2 4 2
2 1 6
3 4 4
4 2

5 3
4 3 5
1 3 5
2 4 2
2 1 6
3 4 4
4 2
'''