#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <math.h>
using namespace std;

unordered_map<string, int> FoodMaps[11];
int maxCnt[11] = { 0 };

void comb(string str, int pos, string candi) {
    if (pos >= str.length()) {
        cout << candi << endl;
        int len = candi.length();
        if (len >= 2) {
            FoodMaps[len][candi]++;
            maxCnt[len] = max(maxCnt[len], FoodMaps[len][candi]);
        }
        return;
    }
    
    comb(str, pos + 1, candi + str[pos]);
    comb(str, pos + 1, candi);
}

vector<string> solution(vector<string> orders, vector<int> course) {
    for (string str : orders) {
        sort(str.begin(), str.end());
        comb(str, 0, "");
    }

    vector<string> answer;
    for (int len : course) {
        for (auto item : FoodMaps[len]) {
            if (item.second >= 2 && item.second == maxCnt[len]) {
                answer.push_back(item.first);
            }
        }
    }

    sort(answer.begin(), answer.end());

    return answer;
}

int main() {
    comb("ABCD", 0, "");

    return 0;
}
