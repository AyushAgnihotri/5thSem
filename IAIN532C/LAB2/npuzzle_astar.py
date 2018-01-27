from collections import deque
from copy import deepcopy

#initial = [[8, 1, 2], [0, 4, 3], [7, 6, 5]] #NOT SOLVABLE
#initial = [[1, 8, 2], [0, 4, 3], [7, 6, 5]]
#initial = [[1, 2, 3], [6, 4, 5], [7, 0, 8]]
#initial = [[0, 1, 3], [4, 2, 5], [7, 8, 6]]
#initial = [[1, 2, 3], [5, 6, 0], [7, 8, 4]]
#initial = [[1, 5, 3], [6, 7, 2], [0, 4, 8]] 
initial = [[1, 2, 3], [6, 4, 5], [0, 7, 8]]

#initial = []
final = []
row = [1, 0, -1, 0]
col = [0, -1, 0, 1]
n = int(input())
steps = -1

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

def printPath(root):
	if root is None:
		return
	printPath(root.parent)
	global steps
	steps = steps + 1
	display_board(root.matrix)

def display_board(matrix):
	for i in range(n):
		print(matrix[i])
	print('\n')

def H(S, D):
	summ = 0
	for i in range(n*n):
		for x1 in range(n):
			for y1 in range(n):
				if (S[x1][y1] == i):
					break
			break

		for x2 in range(n):
			for y2 in range(n):
				if (D[x2][y2] == i):
					break
			break
		summ = summ + abs(x1-x2) + abs(y1-y2)

	return summ

def isSafe(x, y):
	return (x >= 0 and x < n and y >= 0 and y < n)

def isSolvable(matrix):
	arr = []
	for i in range(n):
		for j in range(n):
			arr.append(matrix[i][j])
	
	inv_count = 0
	for i in range(8):
		for j in range(i+1, 9):
			if arr[i] and arr[j] and arr[i] > arr[j]:
				inv_count = inv_count + 1
	return (inv_count % 2 == 0)

def check(current, final):
	if current == final:
		return True
	else :
		return False

def solve(initial, final, a, b):
	priority_queue = deque()
	root = node(0, H(initial, final), initial, None, a, b, a, b)
	if (check(root.matrix, final)):
		printPath(root)
		return

	priority_queue.append(root)
	visited = []
	visited.append(root.matrix)
	while (priority_queue):
		priority = sorted(priority_queue, key=lambda node: (node.g+node.h))
		priority_queue.clear()
		for p in priority:
			priority_queue.append(p)

		min = priority_queue.popleft()
		if (check(min.matrix, final)):
			printPath(min)
			print("Steps taken = " + str(steps))
			return

		for i in range(4):
			if (isSafe(min.x + row[i], min.y + col[i])):

				newmatrix = deepcopy(min.matrix)
				change(newmatrix, min.x, min.y, min.x + row[i], min.y + col[i])
				h = H(newmatrix, final)
				child = node((min.g)+1, h, newmatrix, min, min.x, min.y, min.x + row[i], min.y + col[i])

				if child.matrix not in visited:
					priority_queue.append(child)
					visited.append(child.matrix)

def initialise():
	'''print("Enter Initial State:")
	for _ in range(n):
		a = input().strip().split(' ')
		initial.append([int(x) for x in a])'''

	print("Enter Final State:")
	for _ in range(n):
		a = input().strip().split(' ')
		final.append([int(x) for x in a])

	if (n == 3 and not isSolvable(initial)):
		print("Not Solvable!")
		return

	for i in range(n):
		for j in range(n):
			if (initial[i][j] == 0):
				v1 = i
				v2 = j
		
	solve(initial, final, v1, v2)

initialise()