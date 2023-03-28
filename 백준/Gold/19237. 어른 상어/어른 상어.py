#어른 상어
n, m, k = map(int, input().split())
board = [list(map(int, input().split())) for _ in range(n)]

#상어의 초기 방향
dir = list(map(int, input().split()))

#방향 우선순위
priority = []
for i in range(m):
    temp = []
    for _ in range(4):
        temp.append(list(map(int, input().split())))
    priority.append(temp)

#상어의 초기 위치를 저장할 리스트
shark = [[0,0] for _ in range(m)]

#상어 번호, 냄새가 머무는 시간, 방향
smell = [[[0, 0]]*n for _ in range(n)]

#이동 방향
dy = [0, 0, -1, 1]
dx = [-1, 1, 0, 0]

#범위 확인
def out_range(x, y):
    return x < 0 or x >= n or y < 0 or y >= n

#냄새 정보 업데이트
def smell_update():
    for i in range(n):
        for j in range(n):
            if smell[i][j][1] > 0:
                smell[i][j][1] -= 1
            if board[i][j] != 0:
                smell[i][j] = [board[i][j], k]

#상어 움직임
def shark_move():
    new_board = [[0]*n for _ in range(n)]
    for x in range(n):
        for y in range(n):
            if board[x][y] != 0:
                direction =dir[board[x][y] - 1]
                found = False
                #상어의 위치이면
                for idx in priority[board[x][y]-1][direction - 1]:
                    nx = x+dx[idx-1]
                    ny = y+dy[idx-1]
                    if not out_range(nx, ny):
                        if smell[nx][ny][1] == 0:   #냄새가 나지 않으면
                            dir[board[x][y] - 1] = idx
                            if new_board[nx][ny] == 0:  #상어 이동
                                new_board[nx][ny] = board[x][y]
                            else:
                                new_board[nx][ny] = min(board[x][y], new_board[nx][ny])
                            found = True
                            break
                if found:
                    continue
                # 주변에 냄새가 모두 남아있다면, 자신의 냄새가 있는 곳으로 이동
                for idx in priority[board[x][y]-1][direction - 1]:
                    nx, ny = x+dx[idx - 1], y+dy[idx-1]
                    if not out_range(nx, ny):
                        # 자신의 냄새가 남아있다면
                        if smell[nx][ny][0] == board[x][y]:
                            #해당 상어 방향 변경
                            dir[board[x][y] -1] = idx
                            #상어 이동
                            new_board[nx][ny] = board[x][y]
                            break
    return new_board

ans = 0
while True:
    smell_update()
    new_board = shark_move()
    board = new_board
    ans += 1

    check = True
    for i in range(n):
        for j in range(n):
            if board[i][j] > 1:
                check = False
    if check:
        print(ans)
        break
    #1000초가 지나면 실패
    if ans >= 1000:
        print(-1)
        break