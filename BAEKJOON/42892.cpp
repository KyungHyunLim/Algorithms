/*
kakao blind 2019 길 찾기 게임

1. 조건에 따라 이진 트리 생성
2. 전위 순회
3. 후위 순회
4. 결과 

*/
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct node {
    int num, x, y;
    node* left = NULL;
    node* right = NULL;
};

bool cmp(pair<int, pair<int, int>> a, pair<int, pair<int, int>> b) {
    if (a.second.second > b.second.second) return true;
    else if (a.second.second == b.second.second) {
        if (a.second.first < b.second.first) return true;
    }
    return false;
}

vector<int> pre;
void pre_order(node* rt) {
    if (rt == NULL) return;
    pre.push_back(rt->num);
    pre_order(rt->left);
    pre_order(rt->right);
}
vector<int> post;
void post_order(node* rt) {
    if (rt == NULL) return;
    post_order(rt->left);
    post_order(rt->right);
    post.push_back(rt->num);
}

vector<vector<int>> solution(vector<vector<int>> nodeinfo) {
    vector<pair<int, pair<int, int>>> info;
    for (int i = 0; i < nodeinfo.size(); i++) {
        info.push_back(make_pair(i + 1, make_pair(nodeinfo[i][0], nodeinfo[i][1])));
    }

    sort(info.begin(), info.end(), cmp);

    // 트리생성
    node* root = new node;
    node* new_node;
    // 노드 순회
    for (int i = 0; i < info.size(); i++) {
        // 루트 생성
        if (i == 0) {
            root->num = info[i].first;
            root->x = info[i].second.first;
            root->y = info[i].second.second;
        }
        else {
            node* temp = root;
            while (temp != NULL) {
                // x좌표가 부모 보다 크면 오른쪽
                if (info[i].second.first > temp->x) {
                    if (temp->right == NULL) break;
                    temp = temp->right;
                }
                // x좌표가 부모 보다 작으면 왼쪽
                else {
                    if (temp->left == NULL) break;
                    temp = temp->left;
                }
            }
            new_node = new node;
            new_node->num = info[i].first;
            new_node->x = info[i].second.first;
            new_node->y = info[i].second.second;
            if (info[i].second.first > temp->x) temp->right = new_node;
            // x좌표가 부모 보다 작으면 왼쪽
            else temp->left = new_node;
        }
    }

    vector<vector<int>> answer;
    // 전위 순회
    node* t = root;
    pre_order(t);
    answer.push_back(pre);
    // 후위 순회
    t = root;
    post_order(t);
    answer.push_back(post);

    return answer;
}
