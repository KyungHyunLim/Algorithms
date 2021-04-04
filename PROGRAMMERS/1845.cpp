/*
폰켓몬

N/2 마리 선택 가능
총 종류가 N/2 보다 작으면 총 종류의 수만큼,
총 종류의 수가 N/2 보다 크면 N/2 종류 만큼 최대로 데려갈 수 있음.

*/
#include <vector>
#include <set>
using namespace std;

int solution(vector<int> nums)
{
    int answer = 0;
    
    set<int> pocket;
    for(int i=0; i<nums.size(); i++){
        pocket.insert(nums[i]);
    }
    
    if(pocket.size() <= nums.size()/2){
        answer = pocket.size();
    }
    else{
        answer = nums.size()/2;
    }
       
    return answer;
}
