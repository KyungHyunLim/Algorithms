'''
요리사

비슷한 맛의 음식을 만들기 위해서는 A음식과 B음식의 맛의 차이가 최소가 되도록 재료를 배분해야 한다
'''
def score(info, selected, N):
    A = 0
    B = 0
    
    not_selected = [i for i in range(N) if i not in selected]
    for i in range(N):
        if i in selected:
            for j in selected:
                A += info[i][j]
        else:
            for j in not_selected:
                B += info[i][j]
    # print(f'A: {selected}, B: {not_selected}')            
    # print(f'A: {A}, B: {B}')
    return abs(A-B)
    

def select(info, selected, N, r, idx, next):
    global min_val
    # 선택을 다 했으면
    if idx == r:
        nums = selected[:r]
        val = score(info, nums, N)
        min_val = min(min_val, val)
        return
        
    if next >= N: return
    
    selected[idx] = next
    # 현재 재료(next) 선택
    select(info, selected, N, r, idx + 1, next + 1)
    # 현재 재료(next) 값 미선택
    select(info, selected, N, r, idx, next + 1)
    
        
T = int(input())
# 여러개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
for test_case in range(1, T + 1):
    # 재료개수 입력
    N = int(input())
    
    # 시너지 정보 입력
    info = [list(map(int, input().split())) for _ in range(N)]
    
    min_val = 999999999
    selected = [0] * N
    select(info, selected, N, N//2, 0, 0)
    print(f'#{test_case} {min_val}')

'''
1
4
0 5 3 8
4 0 4 1
2 5 0 3
7 2 3 0
'''