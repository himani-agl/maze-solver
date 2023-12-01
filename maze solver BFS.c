#include <stdio.h>
#include <stdlib.h>

#define MAX 100
#define WALL '#'
#define PATH ' '
#define START 'S'
#define END 'E'

int visited[MAX][MAX] = {0};
int adjacencyMatrix[MAX * MAX][MAX * MAX] = {0};
//defining the coordinates
typedef struct {
    int x, y;
} Point;
//defining queue
Point queue[MAX * MAX];
int front = 0, rear = -1;

void enqueue(Point p) {
    if (rear < MAX * MAX - 1)
        queue[++rear] = p;
}

Point dequeue() {
    return queue[front++];
}

int isEmpty() {
    return front > rear;
}
//creating adjacncy matrix for given maze
void createAdjacencyMatrix(char maze[MAX][MAX], int rows, int cols) {
    for (int i = 0; i < rows * cols; i++) {
        for (int j = 0; j < rows * cols; j++) {
            adjacencyMatrix[i][j] = 0;
        }
    }

    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (maze[i][j] != WALL) {
                for (int k = 0; k < 4; k++) {
                    int x = i + dx[k];
                    int y = j + dy[k];

                    if (x >= 0 && x < rows && y >= 0 && y < cols && maze[x][y] != WALL) {
                        adjacencyMatrix[i * cols + j][x * cols + y] = 1;// sets to 1 if path is there
                    }
                }
            }
        }
    }
}
//display adjacancy matrix
void displayAdjacencyMatrix(int rows, int cols) {
    printf("\nAdjacency Matrix:\n");
    for (int i = 0; i < rows * cols; i++) {
        for (int j = 0; j < rows * cols; j++) {
            printf("%d ", adjacencyMatrix[i][j]);
        }
        printf("\n");
    }
}
//BFS for solving maze 
//returns 1 if maze is solvable else 0
int BFS(char maze[MAX][MAX], Point start, Point end, int rows, int cols) {
    Point parent[MAX][MAX];

    enqueue(start);
    visited[start.x][start.y] = 1;

    while (!isEmpty()) {
        Point current = dequeue();

        if (current.x == end.x && current.y == end.y) {
            Point current = end;
            while (!(current.x == start.x && current.y == start.y)) {
                current = parent[current.x][current.y];
            }
            return 1;
        }

        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (dx * dy != 0 || dx + dy == 0)
                    continue;

                Point next = {current.x + dx, current.y + dy};

                if (next.x >= 0 && next.x < rows && next.y >= 0 && next.y < cols &&
                    maze[next.x][next.y] != WALL && !visited[next.x][next.y]) {
                    enqueue(next);
                    visited[next.x][next.y] = 1;
                    parent[next.x][next.y] = current;
                }
            }
        }
    }

    return 0;
}

int main() {
    FILE *file = fopen("maze1.txt", "r");//change the input files for testing other maze
    char maze[MAX][MAX];
    Point start, end;
    int rows = 0, cols = 0;

    while (fgets(maze[rows], MAX, file) != NULL) {
        for (cols = 0; maze[rows][cols] != '\n'; cols++) {
            if (maze[rows][cols] == START)
                start = (Point){rows, cols};
            else if (maze[rows][cols] == END)
                end = (Point){rows, cols};
        }
        rows++;
    }

    createAdjacencyMatrix(maze, rows, cols);
    displayAdjacencyMatrix(rows, cols);

    if (BFS(maze, start, end, rows, cols)) {
        printf("\nThe maze is solvable\n");
    } else {
        printf("\nThe maze is not solvable.\n");
    }

    /* Displaying BFS traversal */

    return 0;
}
