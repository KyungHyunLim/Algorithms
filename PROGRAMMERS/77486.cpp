/*
다단계 칫솔판매

1. 각 직원의 부모정보 저장
2. 재귀를 이용해 부모에게 0.1% 전달, 나머지는 자신의 이익에 추가
3. 모든 seller에 대해 2번 진행
4. 모든 직원의 profit 값 answer에 push.

*/
#include <string>
#include <vector>
#include <map>
using namespace std;

map<string, string> parent;
map<string, int> profit;
void Calc(string staff, int amount){
    // 부모면 종료
    if(staff == "center") return;
    
    // 0.1% 반환
    int rub = amount * 0.1; 
    // 0.1% 제외한 금액 더해 주기
    profit[staff] += (amount - rub);
    // 부모 호출해 재귀로 진행
    Calc(parent[staff], rub);
}

vector<int> solution(vector<string> enroll, vector<string> referral, vector<string> seller, vector<int> amount) {
    // 부모 정보 입력
    for(int i =0; i<enroll.size(); i++){
        if(referral[i] == "-") parent[enroll[i]] = "center";
        else parent[enroll[i]] = referral[i];
    }

    // 각 직원별 이익 계산
    for(int i=0; i<seller.size(); i++){
        Calc(seller[i], amount[i]*100);
    }
    
    // 등록순으로 이익 입력
    vector<int> answer;
    for(int i=0; i<enroll.size(); i++) answer.push_back(profit[enroll[i]]);
    return answer;
}
