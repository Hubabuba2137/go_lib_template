#include <raylib.h>
#include <vector>
#include <algorithm>
#include <string>
#include <math.h>

#include "go_lib.hpp"

namespace go{
    Node::Node(float x_in, float y_in){
        //pos = (Vector2){x_in, SCREEN_HEIGHT-y_in}; //normalny ukłąd współrzędnych
        pos = (Vector2){x_in, y_in};
    }

    Node::Node(Vector2 pos_in){
        pos = pos_in;
    }

    Node::Node(){
        pos = (Vector2){0,0};
    }

    void Node::draw(){
        DrawCircle(pos.x, pos.y, radius, GREEN);
    }

    void Node::move(Vector2 vec){
        this->pos.x += vec.x;
        this->pos.y += vec.y;
    }
}