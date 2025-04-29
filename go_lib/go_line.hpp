#pragma once
#include <raylib.h>
#include <vector>

#include "go_node.hpp"

namespace go
{
    struct Line{
        float a_coe;
        float b_coe;
    
        Vector2 start;
        Vector2 end;
    
        Line(Node a, Node b);
        void draw(int window_x, bool write_text);
        bool solve_equation(float x, float y);
    };
} // namespace go
