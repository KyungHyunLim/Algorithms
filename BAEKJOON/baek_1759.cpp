#define MAX(A,B) A>B?A:B;

#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

vector<string> list;
vector<string> candidate;
int L, C;

int dx[4] = { 1, -1, 0, 0 };
int dy[4] = { 0, 0, 1, -1 };

void solution(int l, int c, string target, bool* alpha) {
    if (c == L) {
        int m = 0;
        int j = 0;
        for (int i = 0; i < l; i++) {
            if (target[i] == 'a' || target[i] == 'e' || target[i] == 'i' || target[i] == 'o' || target[i] == 'u') {
                m++;
            }
            else {
                j++;
            }
        }
        if(m >= 1 && j >=2) cout << target << endl;        
        return;
    }
    for (int i = 0; i < candidate.size(); i++) {
        //이미 사용한 알파벳
        if (alpha[candidate[i][0] - 'a']) continue;
        if (!target.empty() && candidate[i][0] < target[target.length() - 1]) continue;
        alpha[candidate[i][0] - 'a'] = true;
        solution(l , c + 1, target + candidate[i], alpha);
        alpha[candidate[i][0] - 'a'] = false;
    }
}

int main() {
    cin >> L >> C;
    for (int i = 0; i < C; i++) {
        string temp;
        cin >> temp;
        candidate.push_back(temp);
    }
    bool alpha[26] = { false, };
    sort(candidate.begin(), candidate.end());
    solution(L, 0, "", alpha);

    return 0;
}
