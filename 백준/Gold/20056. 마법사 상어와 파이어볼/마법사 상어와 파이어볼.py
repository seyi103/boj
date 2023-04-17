from copy import deepcopy
N, M, K = map(int, input().split())
board = [[[] for _ in range(N)] for _ in range(N)]
fk = 1
for _ in range(M):
    r, c, m, s, d = map(int, input().split())
    if m != 0:
        board[r - 1][c - 1].append([m, s, d])

dirs = [[-1, 0], [-1, 1], [0, 1], [1, 1], [1, 0], [1, -1], [0, -1], [-1, -1]]

for _ in range(K):
    new_board = [[[] for _ in range(N)] for _ in range(N)]

    for y in range(N):
        for x in range(N):
            if board[y][x] != []:
                for i in range(len(board[y][x])):
                    nm, ns, nd = board[y][x][i]
                    ny, nx = y+dirs[nd][0]*ns, x+dirs[nd][1]*ns
                    nx = (nx + N) % N
                    ny = (ny + N) % N
                    new_board[ny][nx].append([nm, ns, nd])

    for y2 in range(N):
        for x2 in range(N):
            if len(new_board[y2][x2]) > 1:
                cm, cs, cd = 0, 0, []
                cnt = len(new_board[y2][x2])
                for j in range(cnt):
                    cm += new_board[y2][x2][j][0]
                    cs += new_board[y2][x2][j][1]
                    cd.append(new_board[y2][x2][j][2]%2)
                cm = int(cm/5)
                cs = int(cs/cnt)
                new_board[y2][x2] = []

                if cm != 0:
                    if sum(cd) == 0 or sum(cd) == cnt:
                        for i in range(4):
                            new_board[y2][x2].append([cm, cs, i*2])
                    else:
                        for j in range(4):
                            new_board[y2][x2].append([cm, cs, j*2+1])

    board = deepcopy(new_board)

total = 0
for y in range(N):
    for x in range(N):
        if board[y][x] != []:
            for i in range(len(board[y][x])):
                total += board[y][x][i][0]

print(total)
