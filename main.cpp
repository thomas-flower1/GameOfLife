#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <thread>
#include <mutex>


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

    cells_to_kill.clear();
}

void revive(std::vector<std::vector<int>>& grid, std::vector<sf::Vector2i>& cells_to_revive) {
    for(sf::Vector2i coord: cells_to_revive) {
        int row{coord.x};
        int col{coord.y};
        grid[row][col] = 1;


    }

    cells_to_revive.clear();
}


int main() {

    const int pixel_size{16};
    const int height{pixel_size * 40};
    const int width{pixel_size * 60};

   

    // WINDOW
    sf::RenderWindow window(sf::VideoMode({width, height}), "Game of Life");

    // SEPARATOR LINE
    sf::Vector2f size{width, 2};
    sf::RectangleShape border;
    border.setSize(size);
    border.setPosition(0, 35 * pixel_size);
    border.setFillColor(sf::Color::Black);


    // GRID
    std::vector<std::vector<int>> grid(35, std::vector<int>(60, 0));
    int number_of_rows = static_cast<int>(grid.size());
    int number_of_cols = static_cast<int>(grid[0].size());

    // A SINGLE PIXEL
    sf::RectangleShape pixel{sf::Vector2f{pixel_size, pixel_size}};
    pixel.setPosition(-1, -1);
    pixel.setFillColor(sf::Color::Black);

    // keeping track of what to kill and revive
    std::vector<sf::Vector2i> cells_to_kill{};
    std::vector<sf::Vector2i> cells_to_revive{};

    // keeping track
    int number_of_generations{0};
    bool playing = false;


    // font
    sf::Font font;
    font.loadFromFile("Ubuntu-Regular.ttf");
                        

    // Create a text
    sf::Text text("Generation: " + std::to_string(number_of_generations), font);
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::Black);
    sf::Vector2f text_coord{10,575};
    text.setPosition(text_coord);


    while(window.isOpen()) {

        // dealing with the events loop
        sf::Event event;
        while(window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {

                window.close();

            } else if(event.type == sf::Event::KeyPressed && sf::Keyboard::Enter) {

                playing = true;
                
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

      
        if (playing) {
            
            // updating the text
            text.setString("Generation: " + std::to_string(number_of_generations));
            

            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            for(int i = 0; i < number_of_rows; i++) {
                for(int j = 0; j < number_of_cols; j++) {
                    rules(grid, i, j, cells_to_kill, cells_to_revive);
                    

                }
                
            }  

            // then we can update
            kill(grid, cells_to_kill);
            revive(grid, cells_to_revive);

            number_of_generations ++;

        }


        



        // drawing the background colour, order does matter
        sf::Color white = sf::Color::White;
        window.clear(white);
        window.draw(border);
        window.draw(text);
       
    
        for(int i = 0; i < number_of_rows; i++) {
            for(int j = 0; j < number_of_cols; j++) {
                if(grid[i][j]){
                    pixel.setPosition(sf::Vector2f{static_cast<float>(j * pixel_size), static_cast<float>(i * pixel_size)});
                    window.draw(pixel);

                }
            }
        }


        window.display();


    }


    return 0;
    
}

