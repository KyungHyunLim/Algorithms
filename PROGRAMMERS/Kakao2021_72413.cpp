#include <string>
#include <vector>
#include <algorithm>

using namespace std;

#define INF 4000000

int dist[200][200];

void search(int n){
    for(int k=0; k<n; k++){
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                if(dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }
}

int solution(int n, int s, int a, int b, vector<vector<int>> fares) {
    int answer = INF;
    
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(i==j) dist[i][j] = 0;
            else dist[i][j] = INF;
        }
    }
    
    for(auto edge : fares){
        dist[edge[0]-1][edge[1]-1] = edge[2];
        dist[edge[1]-1][edge[0]-1] = edge[2];
    }
    
    search(n);
    
    for(int k=0; k<n; k++){
        answer = min(answer, dist[s-1][k] + dist[k][a-1] + dist[k][b-1]);
    }
    
    return answer;
}
