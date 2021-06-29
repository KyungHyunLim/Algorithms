# 광고삽입
#
# * 타임라인을 초단위로 배열화
# * 타임라인 배열에 초별, 누적 시청자 수 입력
# * 광고의 길이 만큼 탐색
#
#

# 360,000
def string_to_time(s):
    times = s.split(':')
    h = int(times[0])
    m = int(times[1])
    s = int(times[2])
    
    return h*3600 + m*60 + s

def time_to_string(t):
    h = t // 3600
    h = '0' + str(h) if h < 10 else str(h)
    t = t % 3600
    m = t // 60
    m = '0' + str(m) if m < 10 else str(m)
    t = t % 60
    s = t
    s = '0' + str(s) if s < 10 else str(s)
    
    return h + ":" + m + ":" + s

def solution(play_time, adv_time, logs):
    answer = ''
    play_times = string_to_time(play_time)
    ad_times = string_to_time(adv_time)
    
    # 타임 라인별 시작, 끝에 추가인원, 제거인원 수 표시
    timeline = [0 for i in range(play_times+1)]
    for log in logs:
        log_time = log.split('-')
        start_time = string_to_time(log_time[0])
        end_time = string_to_time(log_time[1])
        
        timeline[start_time] += 1
        timeline[end_time] -= 1
    
    # 구간 별 누적 시청자 수
    for i in range(1, len(timeline)):
        timeline[i] = timeline[i] + timeline[i - 1]
    
    # 전체 누적 시청자수
    for i in range(1, len(timeline)):
        timeline[i] = timeline[i] + timeline[i - 1]
        
    # 최고 시청자수 구간 찾기
    max_count = 0 # 최고 시청자수
    ad_time = 0 # 광고 시작시간
    # 광고 길이 부터 ~ 플레이 타임 까지 탐색
    for i in range(ad_times - 1, play_times):
        # 광고 길이 이후
        if i >= ad_times:
            if max_count < timeline[i] - timeline[i - ad_times]:
                max_count = timeline[i] - timeline[i - ad_times]
                ad_time = i - ad_times + 1
        else:
            if max_count < timeline[i]:
                max_count = timeline[i]
                ad_time = i - ad_times + 1
                
    return time_to_string(ad_time)
    
