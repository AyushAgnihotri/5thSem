

def pprint(grid) :
	for i in range(m) :
		for j in range(n) :
			print(grid[i][j],end = ' ')
		print()
	print()

def inrange(x,y) :
	if(x >= 0 and x < m and y >= 0 and y < n) :
		return True
	return False
	
def check(grid,x,y) :
	l = []
	count = 1
	for i in range(n) :
		if(len(l) == 0) :
			l.append(grid[x][i])
		elif(l[len(l)-1] == chance and grid[x][i] == l[len(l)-1]) :
			count += 1
			l.append(chance)
		else :
			count = 1
			l.append(grid[x][i])
		if(count == 4) :
			return True
	l = []
	count = 1
	for i in range(m) :
		if(len(l) == 0) :
			l.append(grid[i][y])
		elif(l[len(l)-1] == chance and grid[i][y] == l[len(l)-1]) :
			count += 1
			l.append(chance)
		else :
			count = 1
			l.append(grid[i][y])
		if(count == 4) :
			return True
	g = x
	h = y
	count = 1
	l = []	
	while(inrange(g,h)) :
		if(len(l) == 0) :
			l.append(grid[g][h])
		elif(l[len(l)-1] == chance and grid[g][h] == l[len(l)-1]) :
			count += 1
			l.append(chance)
		else :
			count = 1
			l.append(grid[g][h])
		if(count == 4) :
			return True
		g -= 1
		h += 1
	g = x
	h = y
	count = 1
	l = []	
	while(inrange(g,h)) :
		if(len(l) == 0) :
			l.append(grid[g][h])
		elif(l[len(l)-1] == chance and grid[g][h] == l[len(l)-1]) :
			count += 1
			l.append(chance)
		else :
			count = 1
			l.append(grid[g][h])
		if(count == 4) :
			return True
		g -= 1
		h -= 1
	g = x
	h = y
	count = 1
	l = []	
	while(inrange(g,h)) :
		if(len(l) == 0) :
			l.append(grid[g][h])
		elif(l[len(l)-1] == chance and grid[g][h] == l[len(l)-1]) :
			count += 1
			l.append(chance)
		else :
			count = 1
			l.append(grid[g][h])
		if(count == 4) :
			return True
		g += 1
		h -= 1
	g = x
	h = y
	count = 1
	l = []	
	while(inrange(g,h)) :
		if(len(l) == 0) :
			l.append(grid[g][h])
		elif(l[len(l)-1] == chance and grid[g][h] == l[len(l)-1]) :
			count += 1
			l.append(chance)
		else :
			count = 1
			l.append(grid[g][h])
		if(count == 4) :
			return True
		g += 1
		h += 1	
			
t = int(input())
while(t > 0) :
	t -= 1
	m,n,a = map(int,input().split())
	moves = list(map(int,input().split()))
	grid = [[0]*n for i in range(m) ]
	chance = 1
	flag = False
	for choice in moves :
		for insert in range(m-1,-1,-1) :
			if(grid[insert][choice] == 0) :
				grid[insert][choice] = chance
				flag = check(grid,insert,choice)
				break
		if(chance == 1) :
			chance = 2
		else :
			chance = 1
		pprint(grid)
		if(flag == True) :
			break
	
	if(flag == True) :
		print(1)
	else :
		print(0)
	
	 
	
	

