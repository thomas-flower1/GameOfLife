### Game of Life clone using C++ and SFML

Simple implementation of Conway's game of life using C++ and SFML.

There are 3 rules to the game of life:
1. An alive cell with less than 2 live neighbors will die in the next generation due to underpopulation.
2. An alive cell with more than 3 live neighbors will die in the next generation due to overpopulation.
3. A dead cell with 3 live neighbors will become a live cell due to repopulation.

Requirements:
Need to have SFML installed, the version used in this is SFML 2.6.1

To play, compile using:
<br>
 ```g++ main.cpp -lsfml-graphics -lsfml-window -lsfml-system```

and run using:
<br>
```./a.out```

Once compiled just draw using the mouse and press enter to start.


## Demo
![Game of Life DEMO GIF](https://github.com/user-attachments/assets/c23dc6ea-19dc-450d-bcac-4b46dddf8188)
