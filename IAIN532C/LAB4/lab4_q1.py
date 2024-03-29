import time

done = []

def find_next_blank(r, c, m, n, puzzle):
    f = 0
    while r < m:
        while c < n:
            if puzzle[r][c] == 0:
                f = 1
                break
            c += 1
        if f == 1:
            break
        else:
            r += 1
            c = 0
    return (r, c, f)

def is_safe(r, c, m, n, roll_no, friends, puzzle):
    for a in range(r-1, r+2):
    	if (a >= 0 and a < m):
	    	for b in range(c-1, c+2):
	    		if (b >= 0 and b < n):
		    		if ((a != r or b != c) and (puzzle[a][b] != 0)):
		    			if (puzzle[a][b] not in friends[roll_no]):
		    				return False
    return True

def classroom_solver_util(r, c, m, n, students, friends, puzzle):
    for roll_no in students:
    	if roll_no not in done:
	        if is_safe(r, c, m, n, roll_no, friends, puzzle) == True:
	            puzzle[r][c] = roll_no
	            done.append(roll_no)
	            a, b, f = find_next_blank(r, c, m, n, puzzle)
	            if (f == 0):
	                return True
	            else:
	                if classroom_solver_util(a, b, m, n, students, friends, puzzle) == True:
	                    return True
	                puzzle[r][c] = 0
	                done.pop()
    return False
 
def classroom_solver(m, n, students, friends):
	puzzle = [[0 for i in range(n)] for j in range(m)]
	if (classroom_solver_util(0, 0, m, n, students, friends, puzzle)):
		print("\nClassroom Solved:")
		for i in range(m):
			for j in range(n):
				print(puzzle[i][j], end = ' ')
			print()
	else:
		print('Not Possible!')

def init():
    students = []
    friends = {}
    t = int(input())
    while (t):
        m, n = [int(x) for x in input().split()]
        for i in range(m*n):
            L = input().split()
            roll_no = L[0]
            a = int(L[1])
            students.append(roll_no)
            friends[roll_no] = [L[x] for x in range (2, len(L))]        
        classroom_solver(m, n, students, friends)
        t -= 1
init()