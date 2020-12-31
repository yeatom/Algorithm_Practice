import java.util.*;

public class Main {
    /*

    6 10
    1 2 4
    1 3 8
    2 3 4
    2 4 4
    2 5 1
    3 4 2
    3 5 2
    4 6 7
    5 4 6
    5 6 3

    */
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int vertices = scanner.nextInt();
        int edges = scanner.nextInt();
        int[][] adj = new int[vertices][vertices];

        Graph graph = new Graph(vertices + 1);

        for (int i = 0; i < edges; i++) {
            int x = scanner.nextInt();
            int y = scanner.nextInt();
            int capacity = scanner.nextInt();
            graph.addEdge(x, y, capacity);
        }

        int maxFlow = maxFlow(graph, 1, vertices);
        System.out.println(maxFlow);
    }

    static class Graph{
        int[][] graph;

        public int[][] getGraph() {
            return graph;
        }

        int vertices;

        public int getVertices() {
            return vertices;
        }

        public Graph(int vertices) {
            this.graph = new int[vertices][vertices];
            this.vertices = vertices;
        }

        public void addEdge(int x, int y, int capacity){
            graph[x][y] += capacity;
        }

        public int getEdge(int x, int y) {
            return graph[x][y];
        }

        public void printGraph(){
            for (int[] x : graph) {
                for (int y : x) {
                    System.out.print(y);
                }
                System.out.println();
            }
        }

        public List<Integer> neighbors(int vertex){
            List<Integer> neighbors = new ArrayList<Integer>();
            for (int i = 0; i < vertices; i++) {
                if (graph[vertex][i] != 0)
                    neighbors.add(i);
            }
            return neighbors;
        }
    }

    static boolean isPathFound_BFS(Graph graph, int src, int dest, int[] parent){
        boolean pathFound = false;

        Queue<Integer> queue = new LinkedList<>();
        queue.add(src);

        parent[src] = -1;

        boolean[] visited = new boolean[graph.getVertices()];
        visited[src] = true;

        while (!queue.isEmpty()){
            int s = queue.poll();
            for (int i : graph.neighbors(s)) {
                if (!visited[i] && graph.getEdge(s,i) > 0){
                    queue.add(i);
                    visited[i] = true;
                    parent[i] = s;
                }
            }
        }
        pathFound = visited[dest];
        return pathFound;
    }

    static int maxFlow(Graph graph, int s, int t){
        int maxFlow = 0;

        int[] parent = new int[graph.getVertices()];

        while (isPathFound_BFS(graph, s, t, parent)){
            int minCut = Integer.MAX_VALUE;

            for (int i = t; i != s; i = parent[i]) {
                int j = parent[i];
                minCut = Math.min(minCut, graph.getEdge(j,i));
            }

            for (int i = t; i != s; i = parent[i]) {
                int j = parent[i];
                graph.addEdge(j, i, -minCut);
                graph.addEdge(i, j, minCut);
            }
            maxFlow += minCut;
        }
        return maxFlow;
    }
}
