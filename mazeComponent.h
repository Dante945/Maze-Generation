//
// Created by dante on 2/19/2022.
//

#ifndef CS_210_PROJECT_4_V1_MAZECOMPONENT_H
#define CS_210_PROJECT_4_V1_MAZECOMPONENT_H

//Maze Component
struct mazeComponent {
    bool isRoom;
    bool visited = false;
    std::pair<int, int> coords;
};


#endif //CS_210_PROJECT_4_V1_MAZECOMPONENT_H
