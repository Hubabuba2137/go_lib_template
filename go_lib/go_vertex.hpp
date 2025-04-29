#pragma once
#include <raylib.h>
#include <vector>

#include "go_node.hpp"
#include "go_segment.hpp"

namespace go{
    struct Vertex{
        std::vector<Node> vertices;
        std::vector<Segment> edges;
        std::vector<Node> convex_hull_shape;
    
        Vertex(std::vector<Node> nodes);
        Vertex();
        void create_edges();
        void draw();
        void draw_nodes();
        void add_vertex(Node node);
        
        float area();
        std::vector<float> get_bounds();

        void set_convex_shape();
        void draw_convex_hull();
        void move(int dx, int dy);
        void set_pos(int x, int y);

        std::vector<Node> gen_bp(int n);
    };
}