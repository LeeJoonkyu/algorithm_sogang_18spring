#include <cstdio>
#include <algorithm>
int Selection(A[], left, right, k)
int main(){


  return 0;
}
int Selection(A[], left, right, k){
  //input: A[l]~A[R]과 k, 여기서 1<=k<=|A|
  //output: A[L]~A[R]에서 k번재 짝은 원소.
  partition(A[],left,right,&p);
  s=(p-1)-left+1; //s==small group size
  if(k<=s) return Selection(A,left,p-1,k);
  else if (k=s+1) return A[p];
  else return Selection(A,p+1,right,k-s-1);
}
