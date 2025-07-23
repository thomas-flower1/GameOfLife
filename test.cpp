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


void rules(std::vector<std::vector<int>>& grid, int row, int col, std::vector<sf::Vector2i>& cells_to_kill, std::vector<sf::Vector2i>& cells_to_revive) {


    int number_of_neighbors{0};
    int number_of_rows{static_cast<int>(grid.size())};
    int number_of_cols{static_cast<int>(grid[0].size())};


    for(int current_row{row-1}; current_row < row+2; current_row++) {

        for(int current_col{col-1}; current_col < col+2; current_col++) {
            // need to check that the col and row are positive, need to check they are not greater than the array size
            if(current_row >= 0 && current_col >= 0 && current_row < number_of_rows && current_col < number_of_cols) {

                // check if we are checking the original cell, i.e the cell that we are givent the row and coord of
                if(current_col == col && current_row == row){

                    // then just continue
                    continue;
                } else if (grid[current_row][current_col] == 1) {
                    number_of_neighbors++;
                }
            }
        }
    }



    sf::Vector2i cell{row, col};

    // check for underpopulation, overpopulation and reproduction
    if(number_of_neighbors == 3) {
        cells_to_revive.push_back(cell);
    }

    
    else if(number_of_neighbors < 2 || number_of_neighbors > 3){
        cells_to_kill.push_back(cell);

    }
}

void kill(std::vector<std::vector<int>>& grid, std::vector<sf::Vector2i>& cells_to_kill) {
    for(sf::Vector2i coord: cells_to_kill) {
        int row{coord.x};
        int col{coord.y};
        grid[row][col] = 0;


    }
}

void revive(std::vector<std::vector<int>>& grid, std::vector<sf::Vector2i>& cells_to_revive) {
    for(sf::Vector2i coord: cells_to_revive) {
        int row{coord.x};
        int col{coord.y};
        grid[row][col] = 1;


    }
}




int main() {

    std::vector<sf::Vector2i> cells_to_kill{};
    std::vector<sf::Vector2i> cells_to_revive{};

    std::vector<std::vector<int>> grid{
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0},
        {0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0},
        {0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0},
        {0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0},
        {0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1}
    };

    int number_of_rows{static_cast<int>(grid.size())};
    int number_of_cols{static_cast<int>(grid[0].size())};

    for(int i = 0; i < number_of_rows; i++) {
        for(int j = 0; j < number_of_cols; j++) {
            rules(grid, i, j, cells_to_kill, cells_to_revive);
        }

    }


    kill(grid, cells_to_kill);
    revive(grid, cells_to_revive);
    print_matrix(grid);


    return 0;
}