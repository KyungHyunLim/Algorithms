/*
NxN 크기의 체스판에 N개 퀸을 서로 공격 할 수 없게 배치하는 문제

1차원 배열로 가능
배열 인덱스와 그 값을 좌표로 이용해 배치
*/

#include<iostream>

using spacename std;

int N;
int arr[10];

bool isok(int x){
  for(int i=0; i<x; i++){
    // 같은 열 || 대각선
    if(arr[i] == arr[x] || abs(arr[x] - arr[i] == x - i) return false;
  }
   return true;
}

void NQeen(int x){
  if(x == N) count ++;
  else{
    for(int i=0; i<N; i++){
      arr[x] = i;
      if(isok(x)) NQeen(x+1);
    }
  }
}
