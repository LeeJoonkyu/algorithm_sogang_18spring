#include <cstdio>
#include <algorithm>

void MergeSort(int[], int, int);
void ArrMerge(int[], int, int);
int U[9] = { 0, };
int main() {
	int A[] = { 9,7,5,4,3,6,6,4,2 };
	MergeSort(A, 0, 8);

	for (int x : A) printf("%d ", x);

	return 0;
}

void ArrMerge(int A[],int left, int right) {
	int mid = (left + right) / 2;
	int i = left;
	int j = mid + 1;
	int k = left;
	while (i <= mid && j <= right) {
		if (A[i] <= A[j]) {
			U[k] = A[i];
			i++;
		}
		else {
			U[k] = A[j];
			j++;
		}
		k++;
	}
	int t;
	if (i>mid) t = j;
	else t = i;
	for (k; k <= right; k++, t++) U[k] = A[t];
	for (k = 0; k <= right; k++) A[k] = U[k];
}

void MergeSort(int A[], int left, int right) {
	int mid;
	if (left<right) {
		mid = (left + right) / 2;
		MergeSort(A, left, mid);
		MergeSort(A, mid + 1, right);
		ArrMerge(A, left, right);
	}
}
