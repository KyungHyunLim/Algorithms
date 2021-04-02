/*
3진법 뒤집기

1. 3진법 변환
2. 거꾸로 10진수로 변환
*/

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(int n) {
    int answer = 0;
    vector<int> ll;
    while(1){
        if(n == 0) break;
        int l = n % 3;
        ll.push_back(l);
        n = n / 3;
    }
    
    //reverse(ll.begin(), ll.end());
    
    int co = 1;
    for(int i=ll.size()-1; i>=0; i--){
        answer += (ll[i]*co);
        co *= 3;
    }

    return answer;
}
