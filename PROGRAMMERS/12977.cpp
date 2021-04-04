/*
소수 만들기

완전 탐색 (3중 for 문)
소수면 개수 증가
*/
#include <vector>
#include <iostream>
#include <cmath>
using namespace std;

bool isprime(int num) { 	
    if (num < 2) return false; 	
    int a = (int) sqrt(num); 	
    for (int i = 2; i <= a; i++) 
        if (num % i == 0) return false; 	
    return true; 
}

int solution(vector<int> nums) {
    int answer = 0;

     for(int i=0; i<nums.size()-2; i++){
         for(int j=i+1; j<nums.size()-1; j++){
            for(int k=j+1; k<nums.size(); k++){
                int sum = nums[i] + nums[j] + nums[k];
                if(isprime(sum)) answer++;
            }
         }
     }

    return answer;
}
