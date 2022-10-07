"""
BAEKJUN 14501.py 퇴사

Description:
    BAEKJUN 14501.py 퇴사 알고리즘 문제 풀이

    N+1일째 퇴사, 최대 수익을 내고 퇴사하고 싶음.
    최대수익을 낼 수 있는 알고리즘 작성

Author:
    Name: KyungHyun Lim
    Email: lkh1075@gmail.com
"""
global_max = 0

def choose_schadule(N, customers, idx, sum):
    global global_max

    if idx >= len(customers):
        global_max = max(sum, global_max)
        return

    # 고객 상담
    if idx + customers[idx][0] <= N:
        choose_schadule(N, customers, idx + customers[idx][0], sum + customers[idx][1])
    # 고객 상담 x
    choose_schadule(N, customers, idx + 1, sum)

def solution():
    global global_max
    N = int(input())

    customers = []
    for _ in range(N):
        customers.append(list(map(int, input().split())))

    choose_schadule(N, customers, 0, 0)
    return global_max

if __name__ == "__main__":
    answer = solution()
    print(answer)