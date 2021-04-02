/*
두개 뽑아서 더하기

1. 브루투포스
2. check를 활용한 중복 정답 입력 방지
3. 정답 정렬
*/
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool check[201] = {0};

vector<int> solution(vector<int> numbers) {
    vector<int> answer;
    int size = numbers.size();
    
    sort(numbers.begin(), numbers.end());
    
    for(int i=0; i<size-1; i++){
        for(int j=i+1; j<size; j++){
            int sum = numbers[i] + numbers[j];
            if(!check[sum]) {
                answer.push_back(sum);
                check[sum] = true;
            }
        }
    }
    
    return answer;
}
