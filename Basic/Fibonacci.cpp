#include <iostream>
using namespace std;

int recursive_fibo(int n){
  if(n == 1) return 1;
  if(n == 2) return 2;
  return recursive_fibo(n-1) + recursive_fibo(n-2);
}

int arr[11];
int memo_fibo(int n){
  if(n == 1) return 1;
  if(n == 2) return 2;
  if(arr[n] != 0) return arr[n];
  return arr[n] = recursive_fibo(n-1) + recursive_fibo(n-2);
}

int main(){
  int n = 10;
  
  // 재귀 사용
  int recursive_result = recursive_fibo(n); 
  cout << "recursive_result" << recursive_result << endl;
  
  // 반복문 사용
  int a = 1;
  int b = 1;
  for(int i=0; i<n; i++){
      int temp = a + b;
      a = b;
      b = temp;
  }
  int iteration_result = b;
  cout << "iteration_result" << b << endl:
  
  // 메모제이션(동적계획법)
  int memo_result = memo_fibo(n);
  cout << "memo_result" << memo_result << endl;
  
  return 0; 
}
