"""
Author:
    Name: KyungHyun Lim
    Email: lkh1075@gmail.com
"""

from collections import defaultdict

# 원자 이동 가능 방향
# 상, 하, 좌, 우
dx = [0, 0, -0.5, 0.5]
dy = [0.5, -0.5, 0, 0]

N = 0 # 원자개수
energy = 0 # 에너지 총량

def move(atom_info, ):
    global dx, dy, N, energy

    while len(atom_info) > 1:
        grid = defaultdict(list)
        for atom in atom_info: # 원자 위치 표시
            x, y, d, k = atom
            grid[(x + dx[d], y + dy[d])].append([x + dx[d], y + dy[d], d, k])
        atom_info = []
        
        for cord, atoms in grid.items():
            if len(atoms) > 1: # 동일 위치에 있는 원자 제거
                for values in atoms:
                    energy += values[-1]
            else: # 범위 내 원자 정보 저장
                if -1000 <= cord[0] <= 1000 and -1000 <= cord[1] <= 1000:
                    atom_info += atoms

T = int(input())
# 여러개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
for test_case in range(1, T + 1):
    N = int(input()) # 원자 개수 입력
    
    atom_info = []
    energy = 0
    for _ in range(N): # 원자 정보 입력
        # x, y, d(이동 방향), k(에너지)
        atom_info.append(list(map(int, input().split())))

    move(atom_info)
    print(f'#{test_case} {energy}')

'''
1
4
-1000 0 3 5
1000 0 2 3
0 1000 1 7
0 -1000 0 9
'''
