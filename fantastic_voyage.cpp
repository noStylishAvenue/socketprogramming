/* This is some practice code to work with graphs */
/* Author: Frances Barker */
/* Source: 311 Labs */

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <limits.h>
#include <queue>
using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::cerr;

class Node {
  public:
    int vertex;
    int distance;
    int discovered;
    int completed;
    bool visited;

    std::shared_ptr<Node> ancestor;  // shared pointer have: Automatic memory management, multiple shared, use count, how many pointer objects are using this share_count
    std::vector<std::shared_ptr<Node>> neighbors; // Inheritence!

    Node();
    Node(int);

};

class Graph {
  public:
    std::vector<std::shared_ptr<Node>> nodes;

    Graph();

    void printAdjList();
    bool isNeighbor(int, int);
    void DFS();
    int DFSVisit(int, int);
    void BFS(int);
    std::vector<int> distancesFrom(int);

    // bool hasCycle;
    // bool hasCycleRecur;
};

Graph makeGraph();

int main() {
    Graph G;

    int operation = 1;
    cout << "\nMaking a Graph:\n\nFirst # is # of V\nSecond # is # of edges\n";
    cout << "For the # of V, enter a space seperated int that will represent edges\nExample: 1 3\n" << endl;
    G = makeGraph();
    
    cout << "What operation would like to run?\n\n1.Adj List\n\n2.BFS from 0\n\n3.Quit\n\n";

    while (operation > 0) {
        switch(operation) {
            case 1:
                cout << "Adj list" << endl;
                G.printAdjList();
                break;
            case 2:
                cout << "BFS from 0\n" << endl;
                G.BFS(0);
                break;
            case 3:
                cout << "DFS\n";
                G.DFS();
                break;
            case 4:
                cout << "Goodbye\n";
                break;
          }
 
    cin >> operation;
    }

    return 0;
}

Node::Node() {
    vertex = 0;
    distance = INT_MAX;
    discovered = -1;
    completed = -1;
    visited = false;

    ancestor = nullptr;
    neighbors = {};
}

Node::Node(int i) {
    vertex = i;
    distance = INT_MAX;
    discovered = -1;
    completed = -1;
    visited = false;

    ancestor = nullptr;
    neighbors = {};

}

Graph::Graph() {
    nodes = {};
}

void Graph::printAdjList() {
    for (unsigned int i = 0; i < nodes.size(); i++) {
        cout << nodes[i]->vertex << ":";
            for (unsigned int j = 0; j < nodes[i]->neighbors.size(); j++) {
                cout << nodes[i]->neighbors[j]->vertex << " ";
            }
            cout << '\n';
    }
}

bool Graph::isNeighbor(int u, int v) {
    for (unsigned int i = 0; i < nodes[u]->neighbors.size(); i++) {
        if (nodes[u]->neighbors[i]->vertex == nodes[v]->vertex) {
            return true;
        }
    }
    return false;
}

/*************************************************************************************************************/
/*************************************************************************************************************/
/*************************************************************************************************************/

void Graph::DFS() {
    for (unsigned int i = 1; i < nodes.size(); i++) {
        nodes[i]->visited = false;
        nodes[i]->ancestor = NULL;
        nodes[i]->distance = -1;
        nodes[i]->completed = -1;
    }
    int time = 0;

    for (unsigned int j = 0; j < nodes.size(); j++) {
        if (nodes[j]->completed == -1) {
            time = DFSVisit(nodes[j]->vertex, time);
        }
    }
}

int Graph::DFSVisit(int s, int time) {
    time++;
    nodes[s]->discovered = time;
    nodes[s]->visited = true;
    cout << "Here is the node:" << s << '\n';
    for (unsigned int i = 0; i < nodes[s]->neighbors.size(); i++) {
        if (nodes[s]->neighbors[i]->visited == false) {
            nodes[s]->neighbors[i]->ancestor = nodes[s];
            time = DFSVisit(nodes[s]->neighbors[i]->vertex, time);

        }
    }
    time++;
    nodes[s]->completed = time;
    return time;
}

/*************************************************************************************************************/
/*************************************************************************************************************/
/*************************************************************************************************************/


void Graph::BFS(int s) {
    for (unsigned int i = 0; i < nodes.size(); i++ ) {
        nodes[i]->distance = INT_MAX;
        nodes[i]->visited = false;
        nodes[i]->ancestor = nullptr;
    }
    nodes[s]->distance = 0;
    nodes[s]->visited = true;
    vector<int> queue = {s};
    while (!queue.empty()) {
        s = queue.front();
        cout << "Here is the node: " << s << '\n';
        queue.erase(queue.begin());
            for (unsigned int i = 0; i < nodes[s]->neighbors.size(); i++) {
                if (nodes[s]->neighbors[i]->visited == false) {
                    nodes[s]->neighbors[i]->visited = true;
                    nodes[s]->neighbors[i]->distance = nodes[s]->distance + 1;
                    queue.push_back(nodes[s]->neighbors[i]->vertex);
                }
            }
    }
}

/*************************************************************************************************************/
/*************************************************************************************************************/
/*************************************************************************************************************/

// After this point, I would like to attempt a function that is "has cycle"


/*************************************************************************************************************/
/*************************************************************************************************************/
/*************************************************************************************************************/

/* This code was taken directly from Carter T's Graph Driver from 311 Lab 8 */

Graph makeGraph() {
    int n = 0; int m = 0;
    cin >> n >> m;
    Graph G;

    for (int i = 0; i < n; i++) {
        std::shared_ptr<Node> v(new Node(i));
        G.nodes.push_back(v);
    }
    for (int i = 0; i < m; i++) {
        int u = -1, v = -1;
        cin >> u >> v;
    
        if (u < 0 || u >= n || v < 0 || v >= n) {
            cerr << "ERROR: INVALID INPUT\n";
        } else {
        G.nodes[u]->neighbors.push_back(G.nodes[v]);
        G.nodes[v]->neighbors.push_back(G.nodes[u]);
        }
    }
    return G;

}
    
