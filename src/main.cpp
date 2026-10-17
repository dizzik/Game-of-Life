#include <iostream>
#include <algorithm>
#include "raylib.h"
#include <unordered_set>
#include "raymath.h"
#include <algorithm>

const int screenWidth = 800;
const int screenHeight = 800;

const int GRID_SIZE = 40;
/*
struct Cell {
    int x;
    int y;

    bool operator==(const Cell& other) const {
        return x == other.x && y == other.y;
    }
};

struct CellHash {
    std::size_t operator()(const Cell& cell) const {
        return std::hash<int>()(cell.x) ^ std::hash<int>()(cell.y);
    }
};

std::unordered_set<Cell, CellHash> cells;
*/
int grid[GRID_SIZE][GRID_SIZE] = {0};
int nextGrid[GRID_SIZE][GRID_SIZE] = {0};

int countNeighbors(int i, int j){
    int count = 0;
    for (int I = std::max(i-1, 0); I < std::min(i+2,GRID_SIZE); ++I){
        for (int J = std::max(j-1,0); J < std::min(j+2, GRID_SIZE); ++J){
            if (i == I && j == J) continue;
            if (grid[I][J] == 1) count++;
        }
    }
    return count;
}
void Update(){
    for (int i = 0; i < GRID_SIZE; i++){
        for (int j = 0; j < GRID_SIZE; j++){
            int n = countNeighbors(i,j);

            if (grid[i][j] == 1){
                nextGrid[i][j] = (n == 2 || n == 3) ? 1 : 0;
            }
            else if (grid[i][j] == 0){
                nextGrid[i][j] = (n == 3) ? 1 : 0;
            }
        }
    }

    for (int i = 0; i < GRID_SIZE; i++){
        for (int j = 0; j < GRID_SIZE; j++){
            grid[i][j] = nextGrid[i][j];
        
        }
    }
}


int main() {
    InitWindow(screenWidth, screenHeight, "Game of Life");
    SetTargetFPS(60);
    
    bool generate = false;
    // GLIDER
                    grid[1][2] = 1;
                                    grid[2][3] = 1;
    grid[3][1] = 1; grid[3][2] = 1; grid[3][3] = 1;
    

    while (!WindowShouldClose()) {
        
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mousePos = GetMousePosition();
            
        }
        
        
        BeginDrawing();
        
        ClearBackground(RAYWHITE);
        
        if (IsKeyPressed(KEY_SPACE)) generate = !generate;
        if (generate) {
            Update();
            WaitTime(0.2);
        }

        for (int y = 0; y < GRID_SIZE; ++y) {
            for (int x = 0; x < GRID_SIZE; ++x) {
                Rectangle rect = {
                    (float)(x*(screenWidth/GRID_SIZE)),
                    (float)(y*(screenHeight/GRID_SIZE)),
                    screenWidth/GRID_SIZE,
                    screenHeight/GRID_SIZE
                };

                if (grid[y][x] == 1) {
                    DrawRectangleRec(rect, BLACK);
                }

                DrawRectangleLinesEx(rect, 1.0f, LIGHTGRAY);
            }
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}