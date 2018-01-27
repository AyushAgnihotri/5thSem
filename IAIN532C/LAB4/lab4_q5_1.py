import time, sys
from collections import deque

students = []
friends = {}
done = []
domain = {}
neighbors = {}
'''row = [-1, -1, -1, 0, 0, 1, 1, 1]
col = [-1, 0, 1, -1, 1, -1, 0, 1]'''

def min_remaining_values(m, n, puzzle):
    min = sys.maxsize
    a = -1
    b = -1
    f = 0
    count = 0
    h_flag = 0
    tuples = []
    for i in range(m):
        for j in range(n):
            if puzzle[i][j] == 0:
                f = 1
                c = 0
                for roll_no in students:
                    if roll_no not in done:
                        if is_safe(i, j, m, n, roll_no, puzzle) == True:
                            c += 1
                d = degree(i, j, m, n, puzzle)
                tuples.append((i, j, c, d))
                if c < min:
                    min = c

    max = -sys.maxsize - 1
    for t in tuples:
        if t[2] == min:
            count += 1
            if t[3] > max:
                max = t[3]
                a = t[0]
                b = t[1]
    if count > 1:
        h_flag = 1

    return (a, b, f, h_flag)

def degree(r, c, m, n, puzzle):
    d = 0
    for a in range(r-1, r+2):
        if (a >= 0 and a < m):
            for b in range(c-1, c+2):
                if (b >= 0 and b < n):
                    if ((a != r or b != c) and (puzzle[a][b] == 0)):
                        d += 1
    return d

def is_safe(r, c, m, n, roll_no, puzzle):
    for a in range(r-1, r+2):
    	if (a >= 0 and a < m):
	    	for b in range(c-1, c+2):
	    		if (b >= 0 and b < n):
		    		if ((a != r or b != c) and (puzzle[a][b] != 0)):
		    			if (puzzle[a][b] not in friends[roll_no]):
		    				return False
    return True

def classroom_solver_util(r, c, m, n, h_flag, puzzle):
    if h_flag == 0:
        for roll_no in domain[(r, c)]:
            if roll_no not in done:
                if is_safe(r, c, m, n, roll_no, puzzle) == True:
    	            puzzle[r][c] = roll_no

    	            done.append(roll_no)
    	            a, b, f, h_flag = min_remaining_values(m, n, puzzle)
    	            if (f == 0):
    	                return True
    	            else:
    	                if classroom_solver_util(a, b, m, n, h_flag, puzzle) == True:
    	                    return True
    	                puzzle[r][c] = 0
    	                done.pop()
        return False
    else:
        safe = []
        for roll_no in domain[(r, c)]:
            if roll_no not in done:
                if is_safe(r, c, m, n, roll_no, puzzle) == True:
                    safe.append(roll_no)

        if not safe:
            return False
        max = -sys.maxsize - 1
        for roll_no in safe:
            puzzle[r][c] = roll_no
            count = 0
            for i in range(m):
                for j in range(n):
                    if puzzle[i][j] == 0:
                        for roll in students:
                            if roll not in done:
                                if is_safe(i, j, m, n, roll, puzzle) == True:
                                    count += 1
            if count > max:
                max = count
                roll_to_set = roll_no
        roll_no = roll_to_set
        puzzle[r][c] = roll_no

        done.append(roll_no)
        a, b, f, h_flag = min_remaining_values(m, n, puzzle)
        if (f == 0):
            return True
        else:
            if classroom_solver_util(a, b, m, n, h_flag, puzzle) == True:
                return True
            puzzle[r][c] = 0
            done.pop()
        return False

def arc_consistency(m, n):
    for i in range(m):
        for j in range(n):
            domain[(i, j)] = students
            neighbors[(i, j)] = []

    queue = deque()
    for i in range(m):
        for j in range(n):
            queue.append((i, j))
            for a in range(i-1, i+2):
                if (a >= 0 and a < m):
                    for b in range(j-1, j+2):
                        if (b >= 0 and b < n):
                            if (a != i or b != j):
                                neighbors[(i, j)].append((a, b))

    print()
    for i in range(m):
        for j in range(n):
            print(neighbors[(i, j)])
    print()

    while queue:
        X = queue.popleft()
        if removed_inconsistent_values(X):
            for Z in neighbors[X]:
                queue.append(Z)

def removed_inconsistent_values(X):
    f = 1

    '''for roll_x in domain[X]:
        for roll_y in domain[Y]:
            if roll_y in friends[roll_x]:
                f = 0
                break
        if f == 0:
            break

    if f == 1:
        print('Hello')
        domain[X].remove(roll_x)'''

    for roll_x in domain[X]:
        if (len(friends[roll_x]) >= len(neighbors[(X[0], X[1])])):
            f = 0
            break

    if f == 1:
        print('Hello')
        domain[X].remove(roll_x)

    return f

def classroom_solver(m, n):
	puzzle = [[0 for i in range(n)] for j in range(m)]
	arc_consistency(m, n)
	print()
	for i in range(m):
		for j in range(n):
			print(domain[(i, j)])
	print()

	if (classroom_solver_util(0, 0, m, n, 0, puzzle)):
		print("\nClassroom Solved:")
		for i in range(m):
			for j in range(n):
				print(puzzle[i][j], end = ' ')
			print()
	else:
		print('Not Possible!')

def init():
    t = int(input())
    while (t):
        m, n = [int(x) for x in input().split()]
        for i in range(m*n):
            L = input().split()
            roll_no = L[0]
            a = int(L[1])
            students.append(roll_no)
            friends[roll_no] = [L[x] for x in range (2, len(L))]        
        classroom_solver(m, n)
        t -= 1
init()