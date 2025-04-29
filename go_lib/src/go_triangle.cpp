#include <raylib.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <limits>

#include "go_vertex.hpp"
#include "go_node.hpp"
#include "go_segment.hpp"
#include "go_lib.hpp"
#include "go_triangle.hpp"

namespace go{
    Triangle::Triangle(Node a, Node b, Node c){
        points[0] = a;
        points[1] = b;
        points[2] = c;

        edges[0] = Segment(a,b);
        edges[1] = Segment(b,c);
        edges[2] = Segment(a,c);
    }

    Triangle::Triangle()
    {
    }
    void Triangle::draw()
    {
        for(Segment it: edges){
            it.draw();
        }
    }
}