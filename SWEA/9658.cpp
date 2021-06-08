/*
9658. 유효숫자 표기

* 문자열로 치환해 숫자 다루기

*/
#include<iostream>
#include<cstring>
using namespace std;

int main(int argc, char** argv)
{
	int test_case;
	int T;
	
	cin>>T;
	/*
	   여러 개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
	*/
	for(test_case = 1; test_case <= T; ++test_case)
	{
		string answer = "";
        // 문자열로 받기
        cin >> answer;
        
        // 정수 부분과 소수부분으로 분리
        string inteager = answer.substr(0,1);
        string floating = answer.substr(1);
        // 소수점 부분 길이 계산
        int f_length = answer.length() - 1;
        
        // 소수 둣째자리가 5 이상이면 반올림 발생
        if(floating[1] - '0' >= 5) {
            // 소수 첫째자리가 9이고
            if(floating[0] == '9'){
                // 정수 부분도 9 이면
                if(inteager[0] == '9'){
                    // 1.0 * xxxx 형태가 되고 소수점 길이 한개 증가
                    inteager = "1";
                    floating[0] = '0';
                    f_length += 1;
                // 정수 부분이 9 미만 이면
                }else{
                   	//x.0 * xxxx 형태
                    floating[0] = '0';
                    inteager[0] += 1;
                }
            }else{
                // 아니면 반올림 처리
                    floating[0] = floating[0] + 1;
                }
        }
        // 소수 첫째자리 이후 나머지 부분은 버림
        floating = floating[0] + '\0';
        
        // 정답 형식 문자열로 변환
        answer = inteager + "." + floating + "*10^" + to_string(f_length);
        
        // 출력
		cout << "#" << test_case << " " << answer << endl;
 	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
