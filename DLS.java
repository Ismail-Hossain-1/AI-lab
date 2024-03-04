import java.util.LinkedList;

public class DLS { //DLS=> Dpeth Limited search
        // This example shows if a target node is reachable or not from a
        // source node when its traversal depth is limited
    int V;
    LinkedList<Integer> adj[];
    void addEdge(int v, int w){
        adj[v].add(w);
    }
    boolean DLSmethod(int v ,int des, int limit){
        if(v==des) return true;
        if(limit<=0){
             return false;
        }
        for(int i:adj[v]){
           if(DLSmethod(i, des, limit-1)) return true;

        }
        return false;
    }
    public DLS(int v){
        V=v;
        adj= new LinkedList[v];
        for (int i = 0; i < v; i++) {
            adj[i]=new LinkedList();
        }
    }

    public static void main(String[] args) {
        DLS graph= new DLS(7);
        graph.addEdge(0, 1);
        graph.addEdge(0, 2);
        graph.addEdge(1, 3);
        graph.addEdge(1, 4);
        graph.addEdge(2, 5);
        graph.addEdge(2, 6);

        int target = 6, maxDepth = 3, src = 0;
        if(graph.DLSmethod(src, target, maxDepth)){
            System.out.println("Target is reachable with max depth");
        }
        else System.out.println("Target is not reachable with max depth");
    }

}


