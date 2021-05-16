/*
로또의 최고 순위와 최저 순위

1. boolean 배열에 당첨 숫자표시
2. 당첨 숫자면 count 증가
3. 0이면 zero 증가
4. 최저 당첨 순위 = count 개수
   최고 당첨 순위 = count + zero 개수

*/
#include <string>
#include <vector>
#include <map>
#include <cstring>
#include <iostream>
using namespace std;

int convert(int x){
    if(x < 2) return 6;
    else if(x == 2) return 5;
    else if(x == 3) return 4;
    else if(x == 4) return 3;
    else if(x == 5) return 2;
    else{
        return 1;
    }
}

vector<int> solution(vector<int> lottos, vector<int> win_nums) {
    bool good[46];
    memset(good, false, sizeof(good));
    for(int i=0; i<win_nums.size(); i++) good[win_nums[i]] = true;
    int count = 0;
    int zero = 0;
    for(int i=0; i<lottos.size(); i++){
        if(good[lottos[i]]) count++;
        if(lottos[i] == 0) zero++;
    }
    //cout << count << " " << zero << endl;
    return {convert(count+zero), convert(count)};
}
