"""
링크: https://www.codetree.ai/training-field/frequent-problems/santa-gift-factory-2/

"시간 초과"

1. 공장 설립
    - n개의 벨트 설치
    - m개 물건 준비
    - m개의 선물 위치
    - 각각 선물의 번호는 오름차순으로 벨트에 쌓임

2. 물건 모두 옮기기
    - m_src 번째 벨트에 있는 선물들을 모드 m_dst번째 벨트로 이동
    - m_src에 없으면 안옮겨도 됨
    - 옮겨진 선물들은 m_dst 벨트 앞에 위치
    - 옮긴뒤 m_dst에 있는 선물 개수 출력

3. 앞 물건만 교체하기
    - m_src 벨트에 있는 선물 중 가장 앞에 있는 선물을 m_dst 벨트의 가장 앞 선물과 교체
    - 둘 중 하나에 선물이 없으면 교체 없이, 있는 것만 옮김
    - 옮긴뒤 m_dst에 있는 선물 개수 출력
    
4. 물건 나누기
    - m_src 벨트에 있는 선물개수 n개 -> floor(n/2) 번째 까지 선물을 m_dst벨트 앞으로 옮기기
    - 옮긴뒤 m_dst에 있는 선물 개수 출력
    
5. 선물 정보 얻기
    - 선물 번호 p_num이 주어질 때, 
    - 해당 선물의 앞 선물의 앞번호 a와 뒤 번호 b라고 할 때, a + 2*b 출력
    - 없을 경우 -1

6. 벨트 정보 얻기
    - 벨트 번호 b_num이 주어질 떄, 
    - 해당 벨트의 맨앞 a, 맨뒤 선물 번호를 b, 선물개수 c
    - a + 2*b + 3*c 값 출력
    - 선물이 없으면 a와 b 모두 -1
    
q번에 걸쳐 명령은 순서대로 진행

Author:
    Name: KyungHyun Lim
    Email: lkh1075@gmail.com
"""

from collections import defaultdict

def make_factory(belts, gift_loc, n, infos):
    for _ in range(n + 1):
        belts.append(list())
    
    for idx, belt_num in enumerate(infos):
        gift_loc[idx + 1] = [belt_num, len(belts[belt_num])]
        belts[belt_num].append(idx + 1)

def move_all(belts, gift_loc, src, dst): ##
    src_list = belts[src]
    belts[dst] = src_list + belts[dst]
    belts[src] = list()
    
    for idx, gift in enumerate(belts[dst]):
        gift_loc[gift] = [dst, idx]
    
    print(len(belts[dst]))
    
def move_front(belts, gift_loc, src, dst): ##
    src_front = belts[src][0] if len(belts[src]) > 0 else -1
    dst_front = belts[dst][0] if len(belts[dst]) > 0 else -1
    
    if src_front != -1 and dst_front != -1: # 둘다 있는 경우
        belts[src] = [dst_front] + belts[src][1:]
        gift_loc[dst_front] = [src, 0]
        
        belts[dst] = [src_front] + belts[dst][1:]
        gift_loc[src_front] = [dst, 0]
    elif src_front == -1 and dst_front != -1: # src가 빈경우
        belts[dst] = belts[dst][1:]
        belts[src] = [dst_front] + belts[src][1:]
        gift_loc[dst_front] = [src, 0]
    elif src_front != -1 and dst_front == -1: # dst가 빈경우
        belts[src] = belts[src][1:]
        belts[dst] = [src_front] + belts[dst][1:]
        gift_loc[src_front] = [dst, 0]
    
    for idx, gift in enumerate(belts[dst]):
        gift_loc[gift] = [dst, idx]
    
    for idx, gift in enumerate(belts[src]):
        gift_loc[gift] = [src, idx]
    
    print(len(belts[dst]))

def divide(belts, gift_loc, src, dst):
    amount = len(belts[src]) // 2
    
    belts[dst] = belts[src][:amount] + belts[dst]
    belts[src] = belts[src][amount:]
    
    for idx, gift in enumerate(belts[dst]):
        gift_loc[gift] = [dst, idx]
    
    for idx, gift in enumerate(belts[src]):
        gift_loc[gift] = [src, idx]
    
    print(len(belts[dst]))

def get_gift_info(belts, gift_loc, gift):
    belt, index = gift_loc[gift]
    
    if index == 0: a = -1
    else: a = belts[belt][index - 1]

    if index == len(belts[belt]) - 1: b = -1
    else: b = belts[belt][index + 1]
    
    print(a + (2*b))

def get_belt_info(belts, belt):
    c = len(belts[belt])
    if c > 0:
        a, b = belts[belt][0], belts[belt][-1]
    else:
        a, b = -1, -1  
    
    print(a + (2*b) + (3*c))

# 선물 위치 관리
gift_loc = defaultdict(list)

# 벨트 관리
belts = list()

# 명령 실행 횟수
q = int(input())
for _ in range(q):
    infos = list(map(int, input().split()))
    if infos[0] == 100:
        # 1. 공장 설립
        n, m, infos = infos[1], infos[2], infos[3:] 
        make_factory(belts, gift_loc, n, infos)
    elif infos[0] == 200:
        # 2. 물건 모두 옮기기
        m_src, m_dst = infos[1], infos[2]
        move_all(belts, gift_loc, m_src, m_dst)
    elif infos[0] == 300:
        # 3. 앞 물건만 교체하기
        m_src, m_dst = infos[1], infos[2]
        move_front(belts, gift_loc, m_src, m_dst)
    elif infos[0] == 400:
        # 4. 물건 나누기
        m_src, m_dst = infos[1], infos[2]
        divide(belts, gift_loc, m_src, m_dst)
    elif infos[0] == 500:
        # 5. 선물 정보 얻기
        gift = infos[1]
        get_gift_info(belts, gift_loc, gift)
    elif infos[0] == 600:
        # 6. 벨트 정보 얻기
        belt = infos[1]
        get_belt_info(belts, belt)