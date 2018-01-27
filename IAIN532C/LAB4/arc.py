def pprint(grid) :
	for i in range(m) :
		for j in range(n) :
			print(grid[i][j],end = " ")
		print()

def next(grid,x,y) :
	if(y == n-1) :
		return solve(grid,x+1,0,x,y)
	else :
		return solve(grid,x,y+1,x,y)
def issafe(x,y) :
	if(x >= 0 and x < m and y >= 0 and y < n):
		return True
	else :
		return False
		
		

def arc(notavailable,mem) :
	for student in slist : 
		if(student not in adj[mem]):
			notavailable.add(student)
	#print (notavailable)
	return notavailable
	
	

def solve(grid,x,y, prev_x, prev_y) :
	if(x == m) :
		return True

	if(grid[x][y] != " ") :
		return next(grid,x,y)

	available = set()
	notavailable = set()
	if(prev_x != -1) :
		if((prev_x+1 == x and prev_y-1 == y) or (prev_x+1 == x and prev_y+1 == y) or (prev_x+1 == x and prev_y == y)) : 
			notavailable = arc(notavailable,grid[prev_x][prev_y])
	#notavailable = set()
	for student in slist :
		if(not mark[student]) :
			available.add(student)
	row = [-1,-1,-1,1,1,1,0,0]
	col = [0,1,-1,0,1,-1,1,-1]
	for student in available :
		for i in range(8) :
			xindex = x + row[i]
			yindex = y + col[i]
			if(issafe(xindex,yindex)) :
				if(grid[xindex][yindex] != " " and grid[xindex][yindex] not in adj[student] and grid[xindex][yindex]  != student) :
					notavailable.add(student)
					break

	available = sorted(list(available.difference(notavailable)))

	if(len(available) == 0) :
		return False
	for student in available :
		grid[x][y] = student
		mark[student] = True
		if(next(grid,x,y) == True) :
			return True
		grid[x][y] = " "
		mark[student] = False
				
	return False			



t = int(input())
m = 0
n = 0
adj = {}
slist = []
mark = {}
while(t != 0) :
	t -= 1
	m,n = map(int,input().split())
	adj = {}
	slist = []
	for i in range(m*n) :
		temp = input().split()
		roll = temp[0]
		slist.append(roll)
		a = temp[1]
		adj[roll] = temp[2:]

	slist = sorted(slist)
	grid = [[" "]*n for i in range(m)]

	for i in slist :
		mark[i] = False

	if(solve(grid,0,0,-1,-1)) :
		pprint(grid)
	else :
		print("not possible")

