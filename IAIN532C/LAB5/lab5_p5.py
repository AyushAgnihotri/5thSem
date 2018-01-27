from queue import heappush, heappop
from math import sqrt
from collections import deque

def is_safe(curr) :
	if(curr[0]>=0 and curr[0]<dim[0] and curr[1]>=0 and curr[1]<dim[1] ) :
		if(grid[curr[0]][curr[1]] != -1) :
			return True
	return False


def search(src) :
	parent = [[(-1,-1)]*dim[1] for i in range(0,dim[0]) ]
	#x = [0,1,1,1,0,-1,-1,-1]
	#y = [1,1,0,-1,-1,-1,0,1]
	x = [0,1,1,1,0,-1,-1,-1]
	y = [1,1,0,-1,-1,-1,0,1]
	stack = deque()
	vis[src[0]][src[1]] = 0.0
	stack.append(src)
	while(len(stack)!=0) :
		u = stack.popleft()
		
		if(grid[u[0]][u[1]] == 1) :
			break
		for i in range(0,8) :
			v = [(u[0] + x[i])%dim[0] , (u[1] + y[i])%dim[1]]
			if(is_safe(v) and vis[v[0]][v[1]]==99999999999.0) :
				if(abs(x[i]) == abs(y[i])) :   ###FOR DIAGONAL
					vis[v[0]][v[1]] = vis[u[0]][u[1]] + sqrt(2)
				else :	 
					vis[v[0]][v[1]] = vis[u[0]][u[1]] + 1.0
				parent[v[0]][v[1]] = (u[0],u[1])
				stack.append(v)

	return (parent,u)


t = int(input())
for _ in range(0,t) :
	dim = list(map(int,input().split()))
	grid = [list(map(int,input().split())) for i in range(0,dim[0])]
	src = list(map(int,input().split()))
	vis = [[99999999999.0]*dim[1] for i in range(0,dim[0])]
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
