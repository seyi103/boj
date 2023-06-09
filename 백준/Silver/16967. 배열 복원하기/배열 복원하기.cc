#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

int arr[601][601];
int ans[600][600];

int main() {
	int H, W, X, Y;
	scanf("%d %d %d %d", &H, &W, &X, &Y);
	
	for (int i = 0; i < H + X; i++)
		for (int j = 0; j < W + Y; j++)
			scanf("%d", &arr[i][j]);

	for (int i = X; i < H; i++) 
		for (int j = Y; j < W; j++)
			arr[i][j] -= arr[i - X][j - Y];
	
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}
		
	return 0;
}