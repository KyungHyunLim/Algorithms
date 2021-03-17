#define MAX(A,B) A>B?A:B;

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

vector<int> p_plus;
vector<int> p_minus;

int solution(vector<int> a, int M) {
    int length = a.size()/M;
    int sum = 0;
    int idx = 0;
    while (length > 0) {
        sum += (a[idx]*2);
        idx += M;
        length --;
    }
    if(a.size() > idx) sum += (a[idx] * 2);

    return sum;
}


int main() {
    int N, M;
    cin >> N >> M;

    int longest = 0;
    for (int i = 0; i < N; i++) {
        int temp;
        cin >> temp;
        if (temp < 0) { 
            p_minus.push_back(-temp); 
            longest = MAX(-temp, longest);
        }
        else { 
            p_plus.push_back(temp); 
            longest = MAX(temp, longest);
        }
    }

    int answer = 0;
    if (!p_plus.empty()) {
        sort(p_plus.begin(), p_plus.end(), greater<int>());
        answer += solution(p_plus, M);
    }

    if (!p_minus.empty()) {
        sort(p_minus.begin(), p_minus.end(), greater<int>());
        answer += solution(p_minus, M);
    }

    cout << answer - longest;

    return 0;
}