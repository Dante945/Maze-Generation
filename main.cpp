// Author: Dante Viscuso
// San Diego State University
// CS210/CS496: Data Structures
//
// File: main.cpp
//
// Demonstrates use of stack data structure in order to preform a depth first search in the context of Maze generation.
// Utilizes helper functions for cleaner code and readability.
// Includes option to run program through command line arguments.



#include <iostream>
#include <utility> //Pairs for coords
#include <stack> //DFS Stack
#include <stdlib.h> // Random Num
#include <vector> //Vector to break down random wall at random idx
#include "mazeComponent.h" // Maze component struct
using namespace std;
//Maze Printer
void printMaze(mazeComponent **maze, int size) {
    int widthOfMaze = size * 2 + 1;
    int heightOfMaze = size * 2 + 1;
    cout << endl;
    cout << "Randomly Generated Maze: " << endl;

    for (int i = 0; i < widthOfMaze; i++) {
        for (int j = 0; j < heightOfMaze; j++) {
            if (maze[i][j].isRoom == true) { cout << " " << " " ;}
            else { cout << " " << "*" << ""; }
        }
        cout << std::endl;
    }
    cout << endl;
}

bool checkValidNeighbor(int width, pair<int,int> coords){
    if (coords.first >= 1 && coords.second >= 1 && coords.first <= width - 2 &&
            coords.second <= width - 2){
        return true;
    }
    else{
        return false;
    }
}

//DFS
mazeComponent **depthFirstSearch(int size, mazeComponent **maze){
    int widthOfMaze = size * 2 + 1;
    stack<mazeComponent> workSpace;
    workSpace.push(maze[1][1]);

    while (!workSpace.empty()) {
        //Grabs top of the stack to work with and pops it off
        mazeComponent currComponent = workSpace.top();
        workSpace.pop();

        //Holds neighbors of current room to randomly choose
        vector<mazeComponent> listOfNeighbors;

        //Holds coordinates of neighbors
        pair<int, int> south(currComponent.coords.first + 2, currComponent.coords.second);
        pair<int, int> north(currComponent.coords.first - 2, currComponent.coords.second);
        pair<int, int> east(currComponent.coords.first, currComponent.coords.second + 2);
        pair<int, int> west(currComponent.coords.first, currComponent.coords.second - 2);

        //Checks to make sure the current room has not been visited
        if (!currComponent.visited) {

            //Makes sure the neighbors are valid, not out of bounds or visited already
            if (checkValidNeighbor(widthOfMaze,north)) {
                if (!maze[north.first][north.second].visited) {
                    workSpace.push(maze[north.first][north.second]);
                    listOfNeighbors.push_back(maze[north.first][north.second]);
                }
            }
            if (checkValidNeighbor(widthOfMaze,east)) {
                if (!maze[east.first][east.second].visited) {
                    workSpace.push(maze[east.first][east.second]);
                    listOfNeighbors.push_back(maze[east.first][east.second]);
                }
            }
            if (checkValidNeighbor(widthOfMaze,south)) {
                if (!maze[south.first][south.second].visited) {
                    workSpace.push(maze[south.first][south.second]);
                    listOfNeighbors.push_back(maze[south.first][south.second]);
                }
            }
            if (checkValidNeighbor(widthOfMaze,west)) {
                if (!maze[west.first][west.second].visited) {
                    workSpace.push(maze[west.first][west.second]);
                    listOfNeighbors.push_back(maze[west.first][west.second]);
                }
            }
            // By the end off all the checks there will be a vector of all the valid neighbors of the current room
            // As well as an updated stack with these same neighbors

            //If there are neighbors to work with, grab a random one and break down the wall
            if (!listOfNeighbors.empty()) {
                int randNum = rand() % listOfNeighbors.size();
                mazeComponent newComponent = listOfNeighbors.at(randNum);

                //Went South
                if (newComponent.coords.first > currComponent.coords.first) {
                    maze[south.first - 1][south.second].isRoom = true;
                }

                //Went East
                if (newComponent.coords.second > currComponent.coords.second) {
                    maze[east.first][east.second - 1].isRoom = true;
                }

                //Went North
                if (newComponent.coords.first < currComponent.coords.first) {
                    maze[north.first + 1][north.second].isRoom = true;
                }

                //Went West
                if (newComponent.coords.second < currComponent.coords.second) {
                    maze[west.first][west.second + 1].isRoom = true;
                }
            }
            //Mark current room as visited and go again.
            maze[currComponent.coords.first][currComponent.coords.second].visited = true;
        }
    }
    return maze;
}

//Maze Generator
mazeComponent **generateMaze(int size) {
    //Creates a base maze with a given number of 1x1 rooms
    // Maze is represented by a 2D array of maze components
    mazeComponent **maze = 0;
    int widthOfMaze = size * 2 + 1;
    int heightOfMaze = size * 2 + 1;
    maze = new mazeComponent *[heightOfMaze];

    for (int i = 0; i < heightOfMaze; i++) {
        maze[i] = new mazeComponent[widthOfMaze];
        for (int j = 0; j < widthOfMaze; j++) {
            if (i == 0 || j == 0 || i == heightOfMaze - 1 || j == widthOfMaze - 1 || i % 2 == 0 || j % 2 == 0) {
                //Walls are the edges of the maze and the even number coordinates
                maze[i][j].isRoom = false;
                maze[i][j].coords.first = i;
                maze[i][j].coords.second = j;
            } else {
                //Rooms are the remaining components, also stores the coordinates of said rooms
                maze[i][j].isRoom = true;
                maze[i][j].coords.first = i;
                maze[i][j].coords.second = j;
            }
        }
    }
    return depthFirstSearch(size,maze);
}

int main(int argc, char **argv) {
    //Random Maze each time
    srand(time(0));

    //Manual Entry of Maze Width
    //cout << "What is the width of your Maze?: " << std::endl;
    //int width;
    //cin >> width;

    //Command Line Entry of Maze Width
    int width;
    if(argc > 1){
        width = atoi(argv[1]);
    }

    //Creates Maze
    mazeComponent **maze = generateMaze(width);
    printMaze(maze, width);
    cout << "Complete!" << endl;
}




