#include <cstdio>
#include <algorithm>
void QuickSort(int[], int, int);
int Partition(int[], int, int);
int main() {
	int A[] = { 12,34,56,76,4,3,2,43,435,675,32 };
	int left, right;
	left = 0, right = 10;//A.size()-1 왜안되지?
	QuickSort(A, left, right);
	for (int x : A) printf("%d ", x);
	return 0;
}
void QuickSort(int A[], int left, int right) {
	if (left<right) {
		int p = Partition(A, left, right);
		QuickSort(A, left, p - 1);
		QuickSort(A, p + 1, right);
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
