#pragma once
#include <raylib.h>
#include <vector>

namespace go{
    struct Node{
        Vector2 pos;
        float radius = 2.0;

        Node(float x_in, float y_in);
        Node(Vector2 pos_in);
        Node();
        void draw();

        void move(Vector2 vec);
    };
    
    inline bool operator==(const Node& n1, const Node& n2) {
        return (n1.pos.x == n2.pos.x && n1.pos.y == n2.pos.y);
    }
    inline bool operator!=(const Node& n1, const Node& n2) {
        return (n1.pos.x != n2.pos.x && n1.pos.y != n2.pos.y);
    }
    
}