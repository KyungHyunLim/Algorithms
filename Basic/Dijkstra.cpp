#define Max_Node 100

#include<iostrem>
#include<queue>
#include<vector>

using namespace std;

//각 노드까지의 최소거리
dist[Max_Node];
//각 Node의 연결 정보를 가진 벡터
vector<int> Nodes[Max_Node];

//node: 시작노드
int djk(int node){
  priority_queue<pair<int,int>> pq;
  pq.push(make_pair(0, node));
  dist[node] = 0;
  
  while(!pq.empty()){
    int cost = pq.front().first;
    int cur = pq.front().second;
    pq.pop();
    
    for(int i=0; i<Nodes[cur].size(); i++){
      int next_cost = cost + 1;
      int next_cur = Nodes[i];
      
      if(dist[next_cur] > next_cost){
        dist[next_cur] = next_cost;
        pq.push(make_pair(next_cont, next_cur));
      }
    }
  }
}
