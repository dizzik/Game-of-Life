#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <thread>

using namespace std;

const string RESET_CURSOR = "\033[H";
const int GRID_HIGHT = 40;
const int GRID_WIDTH = 20;

vector<vector<int>> grid(GRID_HIGHT, vector<int> (GRID_WIDTH,0));

int countNeighbors(vector<vector<int>>& grid, int i, int j, int m, int n) {
    int count = 0;
    for (int I = max(i-1, 0); I < min(i + 2, m); ++I)
        for (int J = max(j - 1, 0); J < min(j + 2, n); ++J) {
            if(i == I && j == J) continue;

            if(grid[I][J] == 1 || grid[I][J] == 2)
                count++;
        } 
    return count;
}

void gameOfLife(vector<vector<int>>& grid) {
    int height = grid.size();
    int width = grid[0].size();
    int n;
    for (int i=0; i<height; i++){
        for (int j=0; j<width; j++){
            n = countNeighbors(grid, i, j, height, width);
            if (grid[i][j] == 0){
                if (n == 3) grid[i][j] = 4;
            } else if (grid[i][j] == 1){
                if (n == 2 || n == 3) continue;
                else if (n <= 1 || n >= 4) grid[i][j] = 2;
            } 
        }
    }
    for (int i=0; i<height; ++i)
        for (int j=0; j<width; ++j)
            if (grid[i][j] >= 2) grid[i][j] >>= 2;
}

void render(vector<vector<int>> & grid){
    string frame;
    frame += RESET_CURSOR;
    for (int i = 0; i < grid.size(); i++){
        for (int j = 0; j < grid[0].size(); j++){
            if (grid[i][j] == 0) frame += "  ";
            else frame += "[]";
        }
        frame += '\n';
    }
    cout<<frame<<flush;
}
int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    
    /*// GLIDER
                    grid[1][2] = 1;
                                    grid[2][3] = 1;
    grid[3][1] = 1; grid[3][2] = 1; grid[3][3] = 1;
    //*/

    // BOX 2x2 na "końcach" walca 
    grid[GRID_HIGHT/2][1] = 1;          grid[GRID_HIGHT/2][GRID_WIDTH-1] = 1;
    grid[(GRID_HIGHT/2)+1][1] = 1;      grid[GRID_HIGHT/2][GRID_WIDTH-1] = 1;
    //*/
    while(1){
        gameOfLife(grid);
        render(grid);
        this_thread::sleep_for(chrono::milliseconds(120));
    }
    return 0;
}