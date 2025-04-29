#pragma once
#include <raylib.h>
#include <vector>

#include "go_node.hpp"

namespace go{
    struct Segment{
        Node tab[2];
    
        Segment(Node node_start, Node node_end);
        Segment();
        bool solve_seg(float x, float y);
        void draw();
    
        void move(Vector2);

        float len();
        
        bool operator<(const Segment &other) const {
            if (tab[0].pos.x != other.tab[0].pos.x)
                return tab[0].pos.x < other.tab[0].pos.x;
            if (tab[0].pos.y != other.tab[0].pos.y)
                return tab[0].pos.y < other.tab[0].pos.y;
            if (tab[1].pos.x != other.tab[1].pos.x)
                return tab[1].pos.x < other.tab[1].pos.x;
            return tab[1].pos.y < other.tab[1].pos.y;
        }
    };
}