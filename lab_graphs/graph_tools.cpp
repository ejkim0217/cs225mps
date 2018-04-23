/**
 * @file graph_tools.cpp
 * This is where you will implement several functions that operate on graphs.
 * Be sure to thoroughly read the comments above each function, as they give
 *  hints and instructions on how to solve the problems.
 */

#include "graph_tools.h"

/**
 * Finds the minimum edge weight in the Graph graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @return the minimum weighted edge
 *
 * @todo Label the minimum edge as "MIN". It will appear blue when
 *  graph.savePNG() is called in minweight_test.
 *
 * @note You must do a traversal.
 * @note You may use the STL stack and queue.
 * @note You may assume the graph is connected.
 *
 * @hint Initially label vertices and edges as unvisited.
 */
int GraphTools::findMinWeight(Graph& graph)
{
    //TODO: YOUR CODE HERE
    //
    // vector<Edge> edges = graph.getEdges();
    //
    // for(vector<Edge>::iterator eit = edges.begin(); eit != edges.end(); eit++){
    //   edges[eit] = graph.setEdgeLabel(edges[eit], "UNEXPLORED");
    // }

    queue<Vertex> q;
    Vertex initial = graph.getStartingVertex();
    q.push(initial);
    vector<Vertex> adj_vtx = graph.getAdjacent(initial);
    Edge min = Edge(initial, adj_vtx[0]);

    while (!q.empty()){
        initial = q.front();
        q.pop();
        adj_vtx = graph.getAdjacent(initial);

        for(unsigned long vit = 0; vit < adj_vtx.size(); vit++){
          if(graph.getEdgeLabel(initial, adj_vtx[vit]) != "DISCOVERY"){
            q.push(adj_vtx[vit]);
            Edge current = graph.setEdgeLabel(initial, adj_vtx[vit], "DISCOVERY");
            if(graph.getEdgeWeight(min.source, min.dest) > graph.getEdgeWeight(initial, adj_vtx[vit]))
              min = current;
          }
        }
    }
    graph.setEdgeLabel(min.source, min.dest, "MIN");
    return graph.getEdgeWeight(min.source, min.dest);
}

/**
 * Returns the shortest distance (in edges) between the Vertices
 *  start and end.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @param start - the vertex to start the search from
 * @param end - the vertex to find a path to
 * @return the minimum number of edges between start and end
 *
 * @todo Label each edge "MINPATH" if it is part of the minimum path
 *
 * @note Remember this is the shortest path in terms of edges,
 *  not edge weights.
 * @note Again, you may use the STL stack and queue.
 * @note You may also use the STL's unordered_map, but it is possible
 *  to solve this problem without it.
 *
 * @hint In order to draw (and correctly count) the edges between two
 *  vertices, you'll have to remember each vertex's parent somehow.
 */
int GraphTools::findShortestPath(Graph& graph, Vertex start, Vertex end)
{
    //TODO: YOUR CODE HERE
    // vector<Vertex> vertices = getVertices(graph);
    // vector<Edge> edges = getEdges(graph);
    // for(vector<Vertex>::iterator it = vertices.begin(); it != vertices.end(); it++){
    //   vertices[i] = graph.setVertexLabel(vertices[it], "UNEXPLORED");
    // }
    // for(vector<Edge>::iterator eit = edges.begin(); eit != edges.end(); eit++){
    //   edges[i] = graph.setEdgeLabel(edges[i], "UNEXPLORED");
    // }
    // if(start == end)
    //   return 0;
    //
    // int min = INT_MAX;
    // vector<Vertex> adj_vtx = graph.getAdjacent(start);
    //
    // for(unsigned long vit = 0; vit < adj_vtx.size(); vit++){
    //   if(graph.getEdgeLabel(start, adj_vtx[vit]) != "DISCOVERY"){
    //     Edge current = graph.setEdgeLabel(start, adj_vtx[vit], "DISCOVERY");
    //     int pot_min = findShortestPath(graph, adj_vtx[vit], end) + 1;
    //     if(pot_min < min){
    //       min = pot_min;
    //       Edge current = graph.setEdgeLabel(start, adj_vtx[vit], "MINPATH");
    //     }
    //   }
    // }
    // return min;
    queue<Vertex> q;
    q.push(start);
    std::map<Vertex, Vertex> my_map;
    Vertex dummy;
    my_map.insert(std::pair<Vertex, Vertex>(start, dummy));
    Vertex initial;

    while (!q.empty()){
        initial = q.front();
        q.pop();
        vector<Vertex> adj_vtx = graph.getAdjacent(initial);

        for(unsigned long vit = 0; vit < adj_vtx.size(); vit++){
          if(graph.getEdgeLabel(initial, adj_vtx[vit]) != "EXPLORED"){
            q.push(adj_vtx[vit]);
            Edge current = graph.setEdgeLabel(initial, adj_vtx[vit], "EXPLORED");
            my_map.insert(std::pair<Vertex, Vertex>(adj_vtx[vit], initial));
          }
        }
    }
    int min = 0;
    Vertex i = end;
    while(my_map[i] != dummy){
      min++;
      graph.setEdgeLabel(i, my_map[i], "MINPATH");
      i = my_map[i];
    }
    return min;
}

/**
 * Finds a minimal spanning tree on a graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to find the MST of
 *
 * @todo Label the edges of a minimal spanning tree as "MST"
 *  in the graph. They will appear blue when graph.savePNG() is called.
 *
 * @note Use your disjoint sets class from MP 7.1 to help you with
 *  Kruskal's algorithm. Copy the files into the dsets.h and dsets.cpp .
 * @note You may call std::sort instead of creating a priority queue.
 */
void GraphTools::findMST(Graph& graph)
{
    //TODO: YOUR CODE HERE

    //Make a DisjointSets object. This will make an uptree for you
    DisjointSets forest;
    vector<Vertex> vertices = graph.getVertices();
    std::map<Vertex, int> my_map;
    forest.addelements(vertices.size());
    for(unsigned long i=0; i < vertices.size(); i++){
      my_map.insert(std::pair<Vertex, int>(vertices[i], i));
    }

    vector<Edge> my_edges = graph.getEdges();

    //Implement Kruskal's algorithm
    std::sort(my_edges.begin(), my_edges.end());
    std::queue<Edge> q;
    for(unsigned i =0; i < my_edges.size(); i++){
      q.push(my_edges[i]);
    }

    while(!q.empty()){
      Edge temp = q.front();
      q.pop();
      int a = forest.find(my_map[temp.source]);
      int b = forest.find(my_map[temp.dest]);
      if(a != b){
        graph.setEdgeLabel(temp.source, temp.dest, "MST");
        forest.setunion(a, b);

      }
    }

}
