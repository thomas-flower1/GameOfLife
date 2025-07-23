#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>


void print_matrix(const std::vector<std::vector<int>>& matrix){
    for(auto row: matrix){
        for(auto col: row) {
            std::cout << col << " ";
        }
        std::cout << "\n";
    }
}

void underpopulation(std::vector<std::vector<int>>& grid, int row, int col, std::vector<sf::Vector2i>& cells_to_kill) {
    /*
    Checks the 8 square neighbors

    Dies if has fewer than 2 live neighbors

    Given the row and column (the position of the cell) checks its neighbors and sees if it dies by overpopulation

    
    */

    // if the cell is dead just return straight away
    if(grid[row][col] == 0) {
        return;
    }

    int number_of_live_neighbors{0};
    int row_size{static_cast<int>(grid[0].size())};
    int col_size{static_cast<int>(grid.size())};

    int check_y{row-1};


    for (int i = 0; i < 3; i++){
        int check_x{col-1};
        for(int j = 0; j < 3; j++) {


            // check if its the square we are checking
            if(check_x == col && check_y == row) {
                check_x ++;
                continue;
            }

            // check if the x coord is positive and not out of bounds
            else if((check_x >= 0) && (check_y >= 0) && (check_x < row_size) && (check_y < col_size)){
                int current_neighbor{grid[check_y][check_x]};
                if (current_neighbor == 1){
                    number_of_live_neighbors ++;
                }

            }
            check_x ++;
        }
        check_y ++;
        
    }

    if(number_of_live_neighbors < 2) {

        // need to change this instead, create a class to keep track of all the things I need to kill
        sf::Vector2i coord{row, col};
        cells_to_kill.push_back(coord);

    }
}


int main() {

    std::vector<sf::Vector2i> cells_to_kill{};

    std::vector<std::vector<int>> grid{
        {0, 0, 1},
        {0, 1, 0},
        {0, 1, 0}
    };

    for(int row = 0; row < 3; row++) {
        for(int col = 0; col < 3; col++) {
            underpopulation(grid, row, col, cells_to_kill);

        }
    }


 

    for(auto value: cells_to_kill) {
        std::cout << value.x << "\n";
        std::cout << value.y << "\n";
    }





    return 0;
}