#include <cstdio>
#include <algorithm>
#pragma warning(disable:4996)
int QuickSelect(int[],int,int,int);
int Partition(int[],int,int);
int main(){
  int left,right,k,result;
  left=0,right=9;
  int A[]={1,10,8,6,4,5,3,2,7,9};
  printf("몇 번째 정수를 찾고 싶은지 입력하세요 : ");
  scanf("%d",&k);
  result = QuickSelect(A,left,right,k);
  printf("%d",result);

  return 0;
}
int QuickSelect(int A[],int left,int right,int k){
    int pos = Partition(A,left,right);
    if (k == pos){
      return A[pos];
    }
    else if (k<pos){
      return QuickSelect(A,left,pos-1,k);
    }
    else {
      return QuickSelect(A,pos+1,right,k);
    }
}
int Partition(int A[],int left, int right) {
	int i, cur, temp;
	int pitem;
	i = left - 1; cur = left;
	pitem = A[right];
	for (cur = left; cur<right; cur++) {
		if (A[cur]<pitem) {
			i++;
			temp = A[cur];
			A[cur] = A[i];
			A[i] = temp;
		}
	}
	temp = A[i + 1];
	A[i + 1] = A[right];
	A[right] = temp;
	return i + 1;
}
