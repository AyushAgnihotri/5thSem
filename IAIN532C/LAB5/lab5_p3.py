from queue import heappush,heappop
from math import sqrt

def is_safe(curr) :
	if(curr[0]>=0 and curr[0]<dim[0] and curr[1]>=0 and curr[1]<dim[1] ) :
		if(grid[curr[0]][curr[1]] != -1) :
			return True
	return False

def turnanticlock(x) :
	if(x == 0) :
		return 7
	else :
		return x - 1

def turnclock(x) :
	if(x == 7) :
		return 0
	else :
		return x + 1

def search(src) :

	pq = []
	parent = [[(-1,-1)]*dim[1] for i in range(dim[0])]
	direction = [(0,1),(1,1),(1,0),(1,-1),(0,-1),(-1,-1),(-1,0),(-1,1)]
	vis[src[0]][src[1]] = 0
	heappush(pq,(0,0,tuple(src)))
	
	while(len(pq) != 0) :
		curr_cost,go,u = heappop(pq)
		if(grid[u[0]][u[1]] == 1) :
			break
		#go in direction
		v = (u[0]+direction[go][0],u[1]+direction[go][1])
		if(abs(direction[go][0]) == 1 and abs(direction[go][1]) == 1) :
			cost = 1.414
		else :
			cost = 1
		if(is_safe(v) and vis[v[0]][v[1]] == -1 ) :
			vis[v[0]][v[1]] = curr_cost + cost
			heappush(pq,(vis[v[0]][v[1]],go,v))
			parent[v[0]][v[1]] = (u[0],u[1])
		
		#change direction clockwise
		heappush(pq,(curr_cost+5,turnclock(go),u))
		#change direction anticlockwise
		heappush(pq,(curr_cost+5,turnanticlock(go),u))

	return (parent,u)

t = int(input())
for _ in range(0,t) :
	dim = list(map(int,input().split()))
	grid = [list(map(int,input().split())) for i in range(0,dim[0])]
	src = list(map(int,input().split()))
	vis = [[-1]*dim[1] for i in range(0,dim[0])]
	parent = []
	path = []
	dest = []
	(parent,dest) = search(src)

	if(grid[dest[0]][dest[1]] != 1) :
		print(-1)
	else :
		temp = dest
		while(parent[temp[0]][temp[1]] != (-1,-1)) :
			path.append((temp[0],temp[1]))
			temp = parent[temp[0]][temp[1]]
		path.append(src)
		path.reverse()
		for i in path :
			print(i[0],i[1],end=' ')
		if(_!=t-1) :
			print()


