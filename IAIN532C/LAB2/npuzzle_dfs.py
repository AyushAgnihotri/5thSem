from copy import deepcopy

#initial = [[8, 1, 2], [0, 4, 3], [7, 6, 5]] #NOT SOLVABLE
#initial = [[1, 8, 2], [0, 4, 3], [7, 6, 5]]
#initial = [[1, 2, 3], [6, 4, 5], [7, 0, 8]]
#initial = [[0, 1, 3], [4, 2, 5], [7, 8, 6]]
#initial = [[1, 2, 3], [5, 6, 0], [7, 8, 4]]
#initial = [[1, 5, 3], [6, 7, 2], [0, 4, 8]] 
#initial = [[1, 2, 3], [6, 4, 5], [0, 7, 8]]
initial = [[8, 1, 3], [4, 0, 2], [7, 6, 5]]

#initial = []
final = []
row = [1, 0, -1, 0]
col = [0, -1, 0, 1]
n = int(input())
steps = -1

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
	stack = []
	root = node(initial, None, a, b, a, b)
	if (check(root.matrix, final)):
		printPath(root)
		return

	stack.append(root)
	visited = []
	visited.append(root.matrix)
	while (stack):
		mini = stack.pop()
		if (check(mini.matrix, final)):
			printPath(mini)
			print("Steps taken = " + str(steps))
			return

		for i in range(4):
			if (isSafe(mini.x + row[i], mini.y + col[i])):

				newmatrix = deepcopy(mini.matrix)
				change(newmatrix, mini.x, mini.y, mini.x + row[i], mini.y + col[i])
				child = node(newmatrix, mini, mini.x, mini.y, mini.x + row[i], mini.y + col[i])

				if child.matrix not in visited:					
					stack.append(child)
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