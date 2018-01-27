from collections import deque
from copy import deepcopy

initial = []
row = [-1, 0, 0, 1]
col = [0, -1, 1, 0]

distance = -1
path = []

class node:
	def __init__(self, g, h, matrix, parent, x, y, xnew, ynew):
		self.matrix = matrix
		self.parent = parent
		self.x = xnew
		self.y = ynew
		self.g = g
		self.h = h

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

def H(x1, y1, x2, y2):
	return (abs(x1-x2) + abs(y1-y2))

def isSafe(matrix, r, c, x, y):
	return (x >= 0 and x < r and y >= 0 and y < c and matrix[x][y] != 37)

def printOutput():
	print(distance)
	[print (str(p[0]) + ' ' + str(p[1])) for p in path]

def solve(initial, p1, p2, f1, f2, r, c):
	priority_queue = deque()
	root = node(0, H(p1, p2, f1, f2), initial, None, p1, p2, p1, p2)
	if (root.x == f1 and root.y == f2):
		tracePath(root)
		printOutput()
		return

	priority_queue.append(root)
	visited = [[0] * c for i in range(r)]
	visited[p1][p2] = 1
	while (priority_queue):
		priority = sorted(priority_queue, key=lambda node: (node.g+node.h))
		priority_queue.clear()
		for p in priority:
			priority_queue.append(p)

		parent = priority_queue.popleft()
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
				h = H(newx, newy, f1, f2)
				child = node((parent.g)+1, h, newmatrix, parent, parent.x, parent.y, newx, newy)

				if visited[newx][newy] == 0:					
					priority_queue.append(child)
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