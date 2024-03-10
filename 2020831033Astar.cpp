#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

// Define node structure
struct Node {
    int x, y; // coordinates of the node
    int g, h, f; // cost parameters for pathfinding
    Node* parent; // pointer to parent node
};

// Function to calculate Manhattan distance heuristic
int calculateH(Node* current, Node* end) {
    return abs(current->x - end->x) + abs(current->y - end->y);
}

// Function to check if the node is within the grid
bool isValid(int x, int y, int rows, int cols) {
    return (x >= 0 && x < rows && y >= 0 && y < cols);
}

// Function to implement A* algorithm
vector<pair<int, int>> AStar(vector<vector<int>>& grid, Node* start, Node* end) {
    int rows = grid.size();
    int cols = grid[0].size();
    
    // Define moves in 4 directions: up, down, left, right
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    // Priority queue to store nodes to be explored
    priority_queue<pair<int, Node*>> pq;
    start->h = calculateH(start, end);
    start->f = start->g + start->h;
    
    pq.push({-start->f, start});

    // Initialize visited array
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));

    while (!pq.empty()) {
        Node* current = pq.top().second;
        pq.pop();

        // Check if current node is the end node
        if (current->x == end->x && current->y == end->y) {
            vector<pair<int, int>> path;
            while (current != NULL) {
                path.push_back({current->x, current->y});
                current = current->parent;
            }
            reverse(path.begin(), path.end());
            return path;
        }

        visited[current->x][current->y] = true;

        for (int i = 0; i < 4; i++) {
            int newx = current->x + dx[i];
            int newy = current->y + dy[i];
            
            if (isValid(newx, newy, rows, cols) && grid[newx][newy] != 1 && !visited[newx][newy]) {
                Node* newNode = new Node({newx, newy});
                newNode->g = current->g + 1;
                newNode->h = calculateH(newNode, end);
                newNode->f = newNode->g + newNode->h;
                newNode->parent = current;

                pq.push({-newNode->f, newNode});
            }
        }
    }

    return {};
}

int main() {
    int rows, cols;
    cout << "Enter the number of rows and columns of the grid: ";
    cin >> rows >> cols;

    vector<vector<int>> grid(rows, vector<int>(cols, 0));

    // Input the grid
    cout << "Enter the grid (0 for empty, 1 for obstacle):" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cin >> grid[i][j];
        }
    }

    int startX, startY, endX, endY;
    cout << "Enter the starting point coordinates (x y): ";
    cin >> startX >> startY;
    cout << "Enter the ending point coordinates (x y): ";
    cin >> endX >> endY;

    Node* startNode = new Node({startX, startY});
    Node* endNode = new Node({endX, endY});

    vector<pair<int, int>> path = AStar(grid, startNode, endNode);

    if (path.empty()) {
        cout << "No path found!" << endl;
    } else {
        cout << "Path found:" << endl;
        for (auto& p : path) {
            cout << "(" << p.first << ", " << p.second << ") ";
        }
        cout << endl;
    }

    return 0;
}
