from collections import deque
from copy import deepcopy

initial = []
row = [-1, 0, 0, 1]
col = [0, -1, 1, 0]

E = 0
distance = -1
explored = []
path = []

class node:
	def __init__(self, matrix, parent, x, y, xnew, ynew):
		self.matrix = matrix
		self.parent = parent
		self.x = xnew
		self.y = ynew

def change(matrix, x, y, xnew, ynew):
	temp = matrix[x][y]
	matrix[x][y] = matrix[xnew][ynew]
	matrix[xnew][ynew] = temp

def tracePath(root):
	if root is None:
		return
	tracePath(root.parent)
	global distance
	distance += 1
	path.append([root.x, root.y])

def isSafe(matrix, r, c, x, y):
	return (x >= 0 and x < r and y >= 0 and y < c and matrix[x][y] != 37)

def printOutput():
	print(E)
	[print (str(x[0]) + ' ' + str(x[1])) for x in explored]
	print(distance)
	[print (str(p[0]) + ' ' + str(p[1])) for p in path]

def solve(initial, p1, p2, f1, f2, r, c):
	queue = deque()
	root = node(initial, None, p1, p2, p1, p2)
	if (root.x == f1 and root.y == f2):
		tracePath(root)
		printOutput()
		return

	queue.append(root)
	visited = [[0] * c for i in range(r)]
	visited[p1][p2] = 1
	while (queue):
		parent = queue.popleft()
		global E
		E += 1
		explored.append([parent.x, parent.y])
		if (parent.x == f1 and parent.y == f2):
			tracePath(parent)
			printOutput()
			return

		for i in range(4):
			newx = parent.x + row[i]
			newy = parent.y + col[i]
			if (isSafe(parent.matrix, r, c, newx, newy)):

				newmatrix = deepcopy(parent.matrix)
				change(newmatrix, parent.x, parent.y, newx, newy)
				child = node(newmatrix, parent, parent.x, parent.y, newx, newy)

				if visited[newx][newy] == 0:					
					queue.append(child)
					visited[newx][newy] = 1

def initialise():

	p1, p2 = map(int, input().split())
	f1, f2 = map(int, input().split())
	r, c = map(int, input().split())

	for _ in range(r):
		a = input().strip()
		initial.append([ord(x) for x in a])
				
	solve(initial, p1, p2, f1, f2, r, c)

initialise()