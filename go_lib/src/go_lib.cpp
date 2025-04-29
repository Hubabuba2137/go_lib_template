#include <raylib.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <math.h>

#include "go_lib.hpp"
#include "go_node.hpp"
#include "go_line.hpp"
#include "go_segment.hpp"
#include "go_vertex.hpp"
#include "intersect.hpp"

namespace go{
    bool is_on_segment(Node node, Segment seg){
    
        if(node.pos.x < std::min(seg.tab[0].pos.x, seg.tab[1].pos.x) || node.pos.x > std::max(seg.tab[0].pos.x, seg.tab[1].pos.x)){
            return false;
        }
    
        if(node.pos.y < std::min(seg.tab[0].pos.y, seg.tab[1].pos.y) || node.pos.y > std::max(seg.tab[0].pos.y, seg.tab[1].pos.y)){
            return false;
        }
    
        return true;
    }
    
    bool is_on_line(Node node, Line line){
        return line.solve_equation(node.pos.x, node.pos.y);
    }

    bool line_segment_intersection(Line line, Segment seg){
        if(is_on_line(seg.tab[0], line) || is_on_line(seg.tab[1], line)){
            return true;
        }

        float d1, d2;
        if(line.start.x == line.end.x){
            d1 = seg.tab[0].pos.x - line.start.x;
            d2 = seg.tab[1].pos.x - line.start.x;
        }
        else{
            d1 = seg.tab[0].pos.y - (line.a_coe * seg.tab[0].pos.x + line.b_coe);
            d2 = seg.tab[1].pos.y - (line.a_coe * seg.tab[1].pos.x + line.b_coe);
        }

        // jeżeli < 0 to przecina linie, jeżeli > 0 to nie
        return (d1 * d2 < 0);
    }
    
    bool is_on_right_of_line(Node node, Line line) {
        float dx = line.end.x - line.start.x;
        float dy = line.end.y - line.start.y;
        float rx = node.pos.x - line.start.x;
        float ry = node.pos.y - line.start.y;
        
        float cross = dx * ry - dy * rx;
        
        return cross < 0;
    }
    
    Node flip_node_around_line(Node node, Line line){
        float x_s, y_s;
    
        if(line.start.x == line.end.x){
            x_s = line.start.x;
            y_s = node.pos.y;
        }
    
        else if(fabs(line.a_coe) < 1e-6){  // a_coe ~ 0
            x_s = node.pos.x;
            y_s = line.b_coe;
        }
    
        else{
            float m = line.a_coe;
            float c = line.b_coe;
            x_s = (node.pos.x + m * (node.pos.y - c)) / (1 + m * m);
            y_s = (m * node.pos.x + m * m * node.pos.y + c) / (1 + m * m);
        }
    
        float x_prim = 2 * x_s - node.pos.x;
        float y_prim = 2 * y_s - node.pos.y;
    
        return Node(x_prim, y_prim);
    }
    
    Node flip_node_around_segment(Node node, Segment seg){
        Line temp(seg.tab[0], seg.tab[1]);
    
        return flip_node_around_line(node, temp);
    }
    
    float angle(const Segment &seg1, const Segment &seg2) {
        Vector2 v1 = { seg1.tab[1].pos.x - seg1.tab[0].pos.x, seg1.tab[1].pos.y - seg1.tab[0].pos.y };
        Vector2 v2 = { seg2.tab[1].pos.x - seg2.tab[0].pos.x, seg2.tab[1].pos.y - seg2.tab[0].pos.y };
    
        float dot = v1.x * v2.x + v1.y * v2.y;
        float len1 = sqrt(v1.x * v1.x + v1.y * v1.y);
        float len2 = sqrt(v2.x * v2.x + v2.y * v2.y);
        
        if(len1 == 0 || len2 == 0) {
            return 0;
        }
    
        float angle = acos(dot / (len1 * len2));
        return angle;
    }

    bool ray_intersects_segment(Node point, Segment seg) {
        float x = point.pos.x, y = point.pos.y;
        float x1 = seg.tab[0].pos.x, y1 = seg.tab[0].pos.y;
        float x2 = seg.tab[1].pos.x, y2 = seg.tab[1].pos.y;
    
        if ((y1 > y) != (y2 > y)) {
            float intersectX = x1 + (y - y1) * (x2 - x1) / (y2 - y1);
            return x < intersectX;
        }
        return false;
    }

    //-------------lab4---------------------

    std::vector<Node> convex_hull(std::vector<Node> &nod){
        std::vector<go::Node> nodes = nod;
        std::vector<go::Node> hull;
    
        if(nodes.size() < 3 ){
            std::cout<<"Convec hull not possible"<<"\n";
            return hull;
        }
    
        int leftmost = 0;
        int n = nodes.size();
    
        for(int i = 1; i < n; i++){
            if(nodes[i].pos.x < nodes[leftmost].pos.x){
                leftmost = i;
            }
        }
        
        int p = leftmost;
        int q;
        
        do {
            hull.push_back(nodes[p]);
            q = (p + 1) % n;
            
            for(int i = 0; i < n; i++){

                float val = (nodes[q].pos.y - nodes[p].pos.y) * (nodes[i].pos.x - nodes[q].pos.x) -
                            (nodes[q].pos.x - nodes[p].pos.x) * (nodes[i].pos.y - nodes[q].pos.y);

                
                if(val < 0){
                    q = i;
                }
            }
            p = q;
        } while(p != leftmost);
        
        return hull;
    }
}