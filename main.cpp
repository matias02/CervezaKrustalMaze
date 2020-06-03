//
// Created by Matias on 2020-06-03.
//

#include <iostream>
#include <vector>
#include <time.h>
#include <SFML/Graphics.hpp>

#include "mazeHelper.h"

void mergeGroup(Node nodeList[], int group1, int group2)
{
    for (int i = 0; i < GRID_WIDTH * GRID_HEIGHT; ++i)
    {
        if (nodeList[i].group == group2)
            nodeList[i].group = group1;
    }
}

void addWalls(std::vector<Wall> *wallVec, Node nodeList[], int col, int row)
{
    Node* node1 = &(nodeList[col + row * GRID_WIDTH]);
    for(int side = 0; side < 4; ++side)
    {
        int next_col = nextCol(col, side);
        int next_row = nextRow(row, side);
        if (indexIsValid(next_col, next_row))
        {
            Wall wall;
            wall.node1 = node1;
            wall.node2 = &(nodeList[next_col + next_row * GRID_WIDTH]);
            wallVec->push_back(wall);
        }
    }
}

int main()
{
    srand(time(NULL));

    Node nodeList[GRID_WIDTH * GRID_HEIGHT];
    for (int i = 0; i < GRID_WIDTH * GRID_HEIGHT; ++i)
        nodeList[i].group = i;

    std::vector<Wall> wallVec;
    for (int col = 0; col < GRID_WIDTH; ++col)
        for (int row = 0; row < GRID_HEIGHT; ++row)
        {
            Node* node1 = &(nodeList[col + row * GRID_WIDTH]);
            int check_side[2] = {SIDE_RIGHT, SIDE_DOWN};
            for (int i = 0; i < 2; ++i)
            {
                int next_col = nextCol(col, check_side[i]);
                int next_row = nextRow(row, check_side[i]);
                if (indexIsValid(next_col, next_row))
                {
                    Wall wall;
                    wall.node1 = node1;
                    wall.node2 = &(nodeList[next_col + next_row * GRID_WIDTH]);
                    wallVec.push_back(wall);
                }
            }
        }

    Node nodeList2[GRID_WIDTH * GRID_HEIGHT];

    int cur_col = rand() % GRID_WIDTH;
    int cur_row = rand() % GRID_HEIGHT;

    std::vector<Wall> wallVec2;
    addWalls(&wallVec2, nodeList2, cur_col, cur_row);
    nodeList2[cur_col + cur_row * GRID_WIDTH].visited = true;

    sf::RenderWindow window1(sf::VideoMode(GRID_WIDTH * NODE_SIZE, GRID_HEIGHT * NODE_SIZE), "Kruskal");
    sf::RenderWindow window2(sf::VideoMode(GRID_WIDTH * NODE_SIZE, GRID_HEIGHT * NODE_SIZE), "Prim");
    while(window1.isOpen() && window2.isOpen())
    {
        sf::Event event;
        while(window1.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window1.close();
        }
        window1.clear(sf::Color::Blue);

        if (!wallVec.empty())
        {
            int rndWall = rand() % wallVec.size();
            Wall* wall = &(wallVec.at(rndWall));
            Node* node1 = wall->node1;
            Node* node2 = wall->node2;
            if (node1->group != node2->group)
            {
                joinNodes(nodeList, node1, node2);
                mergeGroup(nodeList, node1->group, node2->group);
            }

            wallVec.erase(wallVec.begin() + rndWall);
        }

        sf::Event event2;

        while(window2.pollEvent(event2))
        {
            if (event2.type == sf::Event::Closed)
                window2.close();
        }
        window2.clear(sf::Color::Blue);

        if (!wallVec2.empty())
        {
            int rndWall = rand() % wallVec2.size();
            Wall wall = wallVec2.at(rndWall);
            Node* node1 = wall.node1;
            Node* node2 = wall.node2;

            if((node1->visited && !node2->visited) || (!node1->visited && node2->visited))
            {
                joinNodes(nodeList2, node1, node2);

                int node_index;
                if(!node1->visited) {
                    node_index = node1 - nodeList2;
                    node1->visited = true;
                } else {
                    node_index = node2 - nodeList2;
                    node2->visited = true;
                }

                cur_row = (int) node_index / GRID_WIDTH;
                cur_col = node_index % GRID_WIDTH;

                addWalls(&wallVec2, nodeList2, cur_col, cur_row);
            }

            // pushing item on std::vector will add it on the tail
            // so deleting at rndWall will delete at the correct location
            wallVec2.erase(wallVec2.begin() + rndWall);
        }

        drawMaze(window1, nodeList);
        drawMaze(window2, nodeList2);

        // sf::sleep(sf::milliseconds(100));
        window1.display();
        window2.display();
    }
}