#pragma once
#include <raylib.h>
#include <vector>

#include "go_node.hpp"
#include "go_segment.hpp"

namespace go{
    struct Triangle{
        Node points[3];
        Segment edges[3];

        Triangle(Node a, Node b, Node c);
        Triangle();

        void draw();
    };

    
    inline bool operator==(const Triangle& t1, const Triangle& t2) {
        for (int i = 0; i < 3; ++i) {
            bool found = false;
            for (int j = 0; j < 3; ++j) {
                if(t1.points[i] == t2.points[j]) {
                    found = true;
                    break;
                }
            }
            if (!found) return false;
        }
        return true;
    }
}//namespace go