#include <iostream>

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
    int row_size{static_cast<int>(grid[0].size())};
    int col_size{static_cast<int>(grid.size())};


    for(int current_row{row-1}; current_row < row+2; current_row++) {

        for(int current_col{col-1}; current_col < col+2; current_col++) {
            // need to check that the col and row are positive, need to check they are not greater than the array size
            if(current_row >= 0 && current_col >= 0 && current_row < row_size && current_col < col_size) {

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

    const int pixel_size{16};
    const int height{pixel_size * 40};
    const int width{pixel_size * 60};

    // window
    sf::RenderWindow window(sf::VideoMode({width, height}), "Game of Life");

    // separator line
    sf::Vector2f size{width, 2};
    sf::RectangleShape border;
    border.setSize(size);
    border.setPosition(0, 35 * pixel_size);
    border.setFillColor(sf::Color::Black);

    // TODO next we want to create a 2d vector tracking the progress
    

    // TODO draw the grid, probably wont use for the final version
    std::vector<std::vector<int>> grid(height / pixel_size, std::vector<int>(width/ pixel_size));

    // TODO create a pixel
    sf::RectangleShape pixel{sf::Vector2f{pixel_size, pixel_size}};
    pixel.setPosition(-1, -1);
    pixel.setFillColor(sf::Color::Black);




  

    while(window.isOpen()) {

        sf::Event event;
        while(window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

            
        // checking for mouse key event, and updating the grid
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2i position{sf::Mouse::getPosition(window)};

            const sf::Vector2f border_pos{border.getPosition()};

            // TODO check if above the border line
            if(position.y < border_pos.y){
                grid[position.y / 16][position.x / 16] = 1;
            
            }
            

        }

        // checking for if the enter key is pressed
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
            ;

        }
        
        

        


        // drawing the background colour, order does matter
        sf::Color white = sf::Color::White;
        window.clear(white);


        window.draw(border);
       
        // drawing all the pixels from the grid onto the screen

        int row_num{0};
        int col_num{0};
        for(auto row: grid) {
            for(auto col: row) {
                if(col) {
                    pixel.setPosition(sf::Vector2f{static_cast<float>(col_num * pixel_size), static_cast<float>(row_num * pixel_size)});
                    window.draw(pixel);
                }
                col_num++;
            }
            col_num = 0;
            row_num++;

        }



        window.display();


    }



    return 0;
    
}