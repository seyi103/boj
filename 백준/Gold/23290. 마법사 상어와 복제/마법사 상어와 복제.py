def move_fish(shark_r, shark_c):
    global grounds
    temp_grounds = list()
    for r in range(1, 5):
        for c in range(1, 5):
            for idx in range(1, 9):
                if grounds[r][c][idx]:
                    direction = idx
                    orig_direction = direction
                    for _ in range(8):
                        cr = r + dr[direction]
                        cc = c + dc[direction]
                        # 범위 내에 있으면서 상어도 없고 냄새도 없다면
                        if 1 <= cr <= 4 and 1 <= cc <= 4 and (cr != shark_r or cc != shark_c) and smell[cr][cc] == 0:
                            temp_grounds.append([cr, cc, direction, grounds[r][c][idx]])
                            break
                        else:
                            direction -= 1
                            if direction <= 0:
                                direction += 8
                    # 그 자리에 있기
                    else:
                        temp_grounds.append([r, c, orig_direction, grounds[r][c][idx]])

    grounds = [[[0] * 9 for _ in range(5)] for _ in range(5)]
    for tr, tc, tdirection, num in temp_grounds:
        grounds[tr][tc][tdirection] += num
    return

#     0 좌 좌상 상 우상 우 우하 하 좌하
dr = [0, 0, -1, -1, -1, 0, 1, 1, 1]
dc = [0, -1, -1, 0, 1, 1, 1, 0, -1]

# 0, 상 좌 하 우
shark_dr = [0, -1, 0, 1, 0]
shark_dc = [0, 0, -1, 0, 1]

M, S = map(int, input().split())
grounds = [[[0] * 9 for _ in range(5)] for _ in range(5)]
smell = [[0] * 5 for _ in range(5)]
for _ in range(M):
    r, c, d = map(int, input().split())
    grounds[r][c][d] += 1

shark_r, shark_c = map(int, input().split())

for idx in range(1, S + 1):

    # 1. 상어가 모든 물고기에 복제 마법 시전
    copy_list = [[[0] * 9 for _ in range(5)] for _ in range(5)]
    for r in range(1, 5):
        for c in range(1, 5):
            for i in range(1, 9):
                copy_list[r][c][i] = grounds[r][c][i]

    # 2. 모든 물고기가 한 칸 이동
    move_fish(shark_r, shark_c)

    # 3. 상어가 연속해서 3칸 이동한다. 가장 물고기를 많이 먹을 수 있는 방법으로 이동
    # 경우의 수가 많다면 사전 순으로
    choice = list()
    maximum = 0
    temp_shark_r = 0
    temp_shark_c = 0

    temp_grounds_list = [[[0] * 9 for _ in range(5)] for _ in range(5)]
    for r in range(1, 5):
        for c in range(1, 5):
            for i in range(1, 9):
                temp_grounds_list[r][c][i] = grounds[r][c][i]

    for i in range(1, 5):
        cr1 = shark_r + shark_dr[i]
        cc1 = shark_c + shark_dc[i]
        if cr1 <= 0 or cr1 >= 5 or cc1 <= 0 or cc1 >= 5:
            continue
        sum1 = sum(temp_grounds_list[cr1][cc1])
        temp_grounds_list[cr1][cc1] = [0] * 9
        for j in range(1, 5):
            cr2 = cr1 + shark_dr[j]
            cc2 = cc1 + shark_dc[j]
            if cr2 <= 0 or cr2 >= 5 or cc2 <= 0 or cc2 >= 5:
                continue
            sum2 = sum(temp_grounds_list[cr2][cc2])
            temp_grounds_list[cr2][cc2] = [0] * 9
            for k in range(1, 5):
                cr3 = cr2 + shark_dr[k]
                cc3 = cc2 + shark_dc[k]
                if cr3 <= 0 or cr3 >= 5 or cc3 <= 0 or cc3 >= 5:
                    continue

                sum3 = sum(temp_grounds_list[cr3][cc3])
                # 물고기 최대로 많이 먹을 수 있는 방법
                if sum1 + sum2 + sum3 > maximum:
                    maximum = sum1 + sum2 + sum3
                    choice = [[cr1, cc1], [cr2, cc2], [cr3, cc3]]
                    temp_shark_r = cr3
                    temp_shark_c = cc3

                # 물고기 못먹을 때 방지
                if choice == []:
                    choice = [[cr1, cc1], [cr2, cc2], [cr3, cc3]]
                    temp_shark_r = cr3
                    temp_shark_c = cc3
            for i in range(1, 9):
                temp_grounds_list[cr2][cc2][i] = grounds[cr2][cc2][i]
        for i in range(1, 9):
            temp_grounds_list[cr1][cc1][i] = grounds[cr1][cc1][i]

    shark_r = temp_shark_r
    shark_c = temp_shark_c

    # 상어 이동, 물고기 제거됐다면 냄새를 남긴다.
    for cr, cc in choice:
        if sum(grounds[cr][cc]) > 0:
            # 물고기 먹기
            grounds[cr][cc] = [0] * 9
            smell[cr][cc] = idx

    # 4. 두 번 전 연습에서 생긴 물고기의 냄새가 격자에서 사라진다.
    for r in range(1, 5):
        for c in range(1, 5):
            if smell[r][c] + 2 <= idx:
                smell[r][c] = 0

    # 5.1에서 사용한 복제 마법이 완료된다.
    for r in range(1, 5):
        for c in range(1, 5):
            for i in range(1, 9):
                grounds[r][c][i] += copy_list[r][c][i]


# 숫자 세기
result = 0
for r in range(1, 5):
    for c in range(1, 5):
        for k in range(1, 9):
            result += grounds[r][c][k]

print(result)