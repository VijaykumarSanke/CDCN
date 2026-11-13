
def dijkstra(graph, source):
    n = len(graph)
    dist = [float('inf')] * n
    visited = [False] * n
    parent = [-1] * n

    dist[source] = 0

    for _ in range(n):
        u = -1
        for i in range(n):
            if not visited[i] and (u == -1 or dist[i] < dist[u]):
                u = i

        if u == -1 or dist[u] == float('inf'):
            break

        visited[u] = True

        for v in range(n):
            if graph[u][v] > 0 and not visited[v]:
                new_dist = dist[u] + graph[u][v]

                if new_dist < dist[v]:
                    dist[v] = new_dist
                    parent[v] = u

    print("\nShortest distances and paths:")

    for i in range(n):
        if dist[i] == float('inf'):
            print("To", i, ": No path")
        else:
            path = []
            j = i

            while j != -1:
                path.append(j)
                j = parent[j]

            path.reverse()
            print("To", i, ":", dist[i], "Path:", *path)


n = int(input("Enter number of vertices: "))

graph = []

print("Enter adjacency matrix (0 if no edge):")

for i in range(n):
    row = list(map(int, input().split()))
    graph.append(row)

source = int(input("Enter source vertex (0 to " + str(n-1) + "): "))

dijkstra(graph, source)
