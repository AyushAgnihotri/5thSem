initial = []
for _ in range(7):
	a = input().strip()
	initial.append([ord(x) for x in a])

for x in initial:
	print (x)