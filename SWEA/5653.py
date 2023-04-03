"""
Author:
    Name: KyungHyun Lim
    Email: lkh1075@gmail.com
"""
from collections import defaultdict

def simulation(can_active, activate, K):
    dx = [0, 0, -1, 1]
    dy = [-1, 1, 0, 0]
    generate = defaultdict(list)
    dead_cell = defaultdict(list)
    for time in range(K + 1):
        new_can_active = defaultdict(list)
        # 이번 시간에 생성되는 세포 추가
        for cord, item in generate.items():
            put_time, life = item
            for d in range(4):
                nx, ny = cord[0] + dx[d], cord[1] + dy[d]
                if (nx, ny) not in can_active and (nx, ny) not in activate and (nx, ny) not in generate and (nx, ny) not in dead_cell: # 세포가 있는 자리가 아니면
                    if (nx, ny) in new_can_active:
                        life = max(life, new_can_active[(nx, ny)][1]) # 주변에 세포 생성
                        new_can_active[(nx, ny)] = [time, life]
                    else:
                        new_can_active[(nx, ny)] = [time, life]
        
            activate[cord] = item
        
        # 이번 시간에 활성화 되는 세포, 다음 타임에 생성하도록 추가
        generate = defaultdict(list)
        for cord, item in can_active.items():
            put_time, life = item
            if put_time + life == time: # 활성화됨, + 1 time에 생성
                generate[(cord)] = item
            else: # 활성화 되지 않으면 유지
                new_can_active[(cord)] = item
        
        new_active = defaultdict(list)
        # 죽음 처리
        for cord, item in activate.items():
            put_time, life = item
            if time < put_time + (life*2):
                new_active[cord] = item
            else:
                dead_cell[cord] = item
                
        activate = new_active
        can_active = new_can_active
        
        # print(f'T: {time}')
        # print(f'activated cell: {generate}')
        # print(f'deactivated cell: {can_active}')
        # print(f'alive cell: {activate}')
        # print(f'dead_cell: {dead_cell}')
        
            
    return len(activate) + len(can_active) + len(generate)

T = int(input())
# 여러개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
for test_case in range(1, T + 1):
    # 세로크기, 가로크기, 시뮬레이션 시간
    N, M, K = list(map(int, input().split()))
    grid = [list(map(int, input().split())) for i in range(N)]
    
    activate = defaultdict(list)
    can_active = defaultdict(list)
    
    for i in range(N):
        for j in range(M):
            # [수명, 시작 시간]
            if grid[i][j] != 0: can_active[(i, j)] = [0, grid[i][j]]
    
    print(f'#{test_case} {simulation(can_active, activate, K)}')

'''
1
2 2 10
1 1
0 2

1
5 5 19
3 2 0 3 0
0 3 0 0 0
0 0 0 0 0
0 0 1 0 0
0 0 0 0 2
'''
        
        
'''
for time in range(0, K):
        new_can_active = defaultdict(list)
        
        # 비활성화 세포 중 활성화될 세포가 있는지 검사
        loops = list(can_active.keys())
        print(time)
        print('activate:', activate)
        print('can_active:', can_active)
        for cord in loops:
            k, life = can_active[cord]
            if k + life == time: # 활성화될 시간이고,
                activate[cord] = [k, life]
            else: # 활성화될 시간이 아니면, 유지 (원래 세포가 있던 곳 이므로)
                new_can_active[cord] = [k, life]
        
        print('mid - activate:', activate)
        
        new_activate = defaultdict(list)
        for cord, item in activate.items():
            k, life = item
            if  k + life + 1 == time:
                for d in range(4):
                    nx, ny = cord[0] + dx[d], cord[1] + dy[d]
                    if (nx, ny) not in can_active and (nx, ny) not in activate: # 세포가 있는 자리가 아니면
                        if (nx, ny) in new_can_active:
                            life = max(life, new_can_active[(nx, ny)][1]) # 주변에 세포 생성
                            new_can_active[(nx, ny)] = [time, life]
                        else:
                            new_can_active[(nx, ny)] = [time, life]
            
            if k + life >= time: # 수명이 지난 세포는 사망
                new_activate[cord] = [k, life]
                        
        activate = new_activate
        can_active = new_can_active
        
        print('activate:', activate)
        print('can_active:', can_active)
            
    return len(activate) + len(can_active)


'''