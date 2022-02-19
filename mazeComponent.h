// Author: Dante Viscuso
// San Diego State University
// CS210/CS496: Data Structures
//
// File: mazeComponent.h
//
// Defines the structure that will represent the rooms of the maze
// Holds if the room has been visited for DFS purposes
// The coordinates of the rooms in terms of the maze
// And a flag indicating if it's a room or just a wall

#ifndef RANDOM_MAZE_GENERATOR_MAZECOMPONENT_H
#define RANDOM_MAZE_GENERATOR_MAZECOMPONENT_H

struct mazeComponent {
    bool isRoom;
    bool visited = false;
    std::pair<int, int> coords;
};

#endif //RANDOM_MAZE_GENERATOR_MAZECOMPONENT_H
