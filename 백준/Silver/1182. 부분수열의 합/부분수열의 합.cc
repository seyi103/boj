#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
using namespace std;

int N, S;
int arr[21];
int res;

void dfs(int idx, int sum) {
    for (int i = idx; i < N; i++) 
        dfs(i + 1, sum + arr[i]);
    
    if (sum == S)
        res++;
}

int main() {
    scanf("%d %d", &N, &S);
    for (int i = 0; i < N; i++)
        scanf("%d", &arr[i]);

    dfs(0, 0);
    if (0 == S)
        res--;
    printf("%d", res);
    return 0;
}