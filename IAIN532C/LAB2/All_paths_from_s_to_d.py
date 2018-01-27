from collections import deque

'''def bfs(graph, s):
        visited = [False]*(len(graph)+1)
        queue = deque([s])
        visited[s] = True
 
        while queue:
            s = queue.popleft()
            print(s, end = ' ')
            for i in graph[s]:
                if visited[i] == False:
                    queue.append(i)
                    visited[i] = True
        print()'''

def dfs_paths_util(graph, u, d, visited, path):
        visited[u]= True
        path.append(u)

        if u == d:
            print(path)
        else:
            for i in graph[u]:
                if visited[i] == False:
                    dfs_paths_util(graph, i, d, visited, path)

        path.pop()
        visited[u]= False

def dfs_paths(graph, s, d):
        visited =[False]*(len(graph)+1)
        path = []
        dfs_paths_util(graph, s, d, visited, path)

def bfs_paths(graph, queue, u, d):
    path = [u]
    
    queue.append(path)
    
    while (queue):
        path = queue.popleft()
        last = path[len(path)-1]
        if last == d:
            print(path)
        for i in graph[last]:
            if i not in path:
                new_path = []
                new_path = path + [i]
                queue.append(new_path)

def init():
    graph = {1: [3, 2], 2: [1, 4, 5], 3: [1, 4, 6], 4: [3, 2], 5: [2, 6], 6: [3, 5]}
    #bfs(graph, 1)
    s, d = map(int, input().split())
    if ((s > len(graph)) or (d > len(graph))):
        print("Invalid input!")
        return
    print("All paths from %d to %d using DFS:" % (s, d))
    dfs_paths(graph, s, d)
    print("All paths from %d to %d using BFS:" % (s, d))
    queue = deque()
    bfs_paths(graph, queue, s, d)

init()