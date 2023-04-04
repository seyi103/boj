#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <unordered_map>
using namespace std;
using ll = long long;
/*
* 졸리다...졸려...자고싶다
* 설계
* 반을 나눠서 sum을 기록
* 0~N/2 : um에 개수 기록
* N/2 ~ N: um[S-sum] -> 기존 값 + 부분 수열의 합 = S인 경우 ++

32 1000000
100000 100000 100000 100000 100000 100000 100000 100000 100000 100000 100000 100000 100000 100000 100000 100000 100000 100000 100000 100000 100000 -100000 -100000 -100000 -100000 -100000 -100000 -100000 -100000 -100000 -100000 -100000
*/

int N, S;
int arr[41];
unordered_map<int, int> um;
ll res;

void dfs(int now, int sum) {
    // 기저조건 -> N/2까지 봤을때
    if (now == N / 2) {
        um[sum]++;
        return;
    }

    // 안더한다
    dfs(now + 1, sum);
    // 더한다
    dfs(now + 1, sum + arr[now]);
}

void dfs2(int now, int sum) {
    // 기저조건 -> N까지 봤을때
    if (now == N) {
        if (um.find(S - sum) != um.end())
            res += um[S - sum];
        return;
    }
    // 안더한다
    dfs2(now + 1, sum);
    // 더한다
    dfs2(now + 1, sum + arr[now]);
}

int main() {
    scanf("%d %d", &N, &S);
    for (int i = 0; i < N; i++)
        scanf("%d", &arr[i]);
    int de = 1;

    dfs(0, 0);
    dfs2(N / 2, 0);

    if (!S)
        res--;
    printf("%lld\n", res);

    return 0;
}