  
#define _CRT_SECURE_NO_WARNINGS
#define MAX 10

#include<iostream>
#include<vector>
using namespace std;

int parent[MAX];
int root[MAX];
int n;

// 부모 찾기
int find(int x) {
	if (x == parent[x]) return x;
	return parent[x] = find(parent[x]);
}

// 부모 합치기
void Union(int x, int y) {
	x = find(x);
	y = find(y);

  if(x==y) return;
  
  // 낮은 값을 부모로
  if(x<y){
    parent[y] = x;
  }else{
    parent[x] = y;
  }
}


int main() {
  //부모를 자기 자신으로 초기화 하고 시작
  for (int i = 0; i < MAX; i++)
    parent[i] = i;

  //활용 크루스칼 or 가장 큰 집합 추적
  

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
