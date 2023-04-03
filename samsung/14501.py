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

def dfs_choose_schadule(N, customers, idx, sum):
    global global_max

    if idx >= len(customers):
        global_max = max(sum, global_max)
        return

    # 고객 상담
    if idx + customers[idx][0] <= N:
        dfs_choose_schadule(N, customers, idx + customers[idx][0], sum + customers[idx][1])
    # 고객 상담 x
    dfs_choose_schadule(N, customers, idx + 1, sum)

def dp_choose_schedule(dp, N, customers):
    max_money = 0
    for idx in range(N + 1):
        #
        dp[idx] = max(max_money, dp[idx])
        
        # idx번째 업무 + 걸리는 일수
        next = idx + customers[idx][0]
        if (next < N + 1): # 퇴사일을 넘어가지 않으면  
            dp[next] = max(dp[next], customers[idx][1] + dp[idx])
        max_money = max(max_money, dp[idx])    
    return max_money

# chatGPT 최적화
def caht_dp_choose_schedule(customers):
    dp = [0] * (len(customers))
    max_money = 0
    for idx, (duration, reward) in enumerate(customers):
        max_money = max(max_money, dp[idx])
        next = idx + duration
        if next < len(customers):
            dp[next] = max(dp[next], reward + max_money)
    return max_money

def solution():
    global global_max
    N = int(input())

    customers = []
    for _ in range(N):
        customers.append(list(map(int, input().split())))
    
    dfs_choose_schadule(N, customers, 0, 0)
    
    customers.append([0, 0])
    # 해당 일자(index)에 최대로 받을 수 있는 금액
    dp = [0] * (N + 20)
    max_money = dp_choose_schedule(dp, N, customers)
    
    chat_max_money = caht_dp_choose_schedule(customers)
    
    return global_max, max_money, chat_max_money

if __name__ == "__main__":
    answer = solution()
    print(answer)