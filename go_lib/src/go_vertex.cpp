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

namespace go{
    Vertex::Vertex(std::vector<Node> nodes) {
        float centroidX = 0.0f, centroidY = 0.0f;
        for (const auto& node : nodes) {
            centroidX += node.pos.x;
            centroidY += node.pos.y;
        }
        centroidX /= nodes.size();
        centroidY /= nodes.size();

        std::sort(nodes.begin(), nodes.end(), [centroidX, centroidY](const Node& a, const Node& b) {
            float angleA = atan2(a.pos.y - centroidY, a.pos.x - centroidX);
            float angleB = atan2(b.pos.y - centroidY, b.pos.x - centroidX);
            return angleA < angleB;
        });

        vertices = nodes;
        create_edges();
    }
    
    void Vertex::create_edges(){
        std::vector<Segment> temp;
        std::vector<Node> vert = this->vertices;
    
        
        for(long long unsigned int i=0; i<vertices.size();i++){
    
            if(i<vertices.size()-1){
                Segment temp_line(vert[i], vert[i+1]);
                temp.push_back(temp_line);
            }
            else{
                Segment temp_line(vert[i], vert[0]);
                temp.push_back(temp_line);
            }
        }
    
        this->edges = temp;
    }
    void Vertex::draw_nodes(){
        for(long long unsigned int i =0; i<vertices.size();i++){
            vertices[i].draw();
        }
    }
    
    void Vertex::draw(){
        for(long long unsigned int i =0; i<edges.size();i++){
            edges[i].draw();
        }
    
        for(long long unsigned int i =0; i<vertices.size();i++){
            vertices[i].draw();
        }
    }
    
    void Vertex::add_vertex(Node node){
        vertices.push_back(node);
        create_edges();
    }

    //------------------Lab 3 -----------------//

    float Vertex::area(){
        if(this->edges.size() == 3 && this->edges.size()==3){
            float p = (this->edges[0].len()+this->edges[1].len()+this->edges[2].len())/2;
            return sqrt(p*(p - this->edges[0].len())*(p - this->edges[1].len())*p - this->edges[2].len());
        }
        else{
            return 0;
        }
    }

    std::vector<float> Vertex::get_bounds() {
        float min_x = std::numeric_limits<float>::max();
        float max_x = std::numeric_limits<float>::lowest();
        float min_y = std::numeric_limits<float>::max();
        float max_y = std::numeric_limits<float>::lowest();
    
        for (const auto& node : this->vertices) { 
            min_x = std::min(min_x, node.pos.x);
            max_x = std::max(max_x, node.pos.x);
            min_y = std::min(min_y, node.pos.y);
            max_y = std::max(max_y, node.pos.y);
        }
    
        return {min_x, max_x, min_y, max_y};
    }

    //-----------------lab4------------------

    void Vertex::set_convex_shape(){
       this->convex_hull_shape = convex_hull(this->vertices);
    }

    void Vertex::draw_convex_hull(){
        set_convex_shape();
        Vertex temp(this->convex_hull_shape);
        temp.draw();
    }

    void Vertex::move(int dx, int dy){
        for(auto& it: this->vertices){
            it.pos.x += dx;
            it.pos.y += dy;
        }

        create_edges();
        set_convex_shape();
    }

    void Vertex::set_pos(int x, int y){
        if(this->vertices.empty()){
            return;
        }
        
        float centroidX = 0.0f, centroidY = 0.0f;
        for (auto node : this->vertices) {
            centroidX += node.pos.x;
            centroidY += node.pos.y;
        }
        centroidX /= this->vertices.size();
        centroidY /= this->vertices.size();

        int dx = x - static_cast<int>(centroidX);
        int dy = y - static_cast<int>(centroidY);

        move(dx, dy);
    }



    std::vector<Node> Vertex::gen_bp(int n){
        std::vector<Node> points;
        if (vertices.empty() || n <= 0) {
            return vertices;
        }

    
        float perimeter = 0.0f;
        for(auto& edge : this->edges){
            perimeter += edge.len();
        }
        //std::cout << perimeter << "\n";

        float spacing = perimeter / n;

        for(auto& edge : this->edges) {
            Node point_a = edge.tab[0];
            Node point_b = edge.tab[1];
            points.push_back(point_a);

            float seg_length = edge.len();
            int num_points = static_cast<int>(seg_length / spacing);

            for (int i = 1; i < num_points; i++){
                float t = static_cast<float>(i) / num_points;
                float x = point_a.pos.x + t * (point_b.pos.x - point_a.pos.x);
                float y = point_a.pos.y + t * (point_b.pos.y - point_a.pos.y);
                points.push_back(Node(Vector2{ x, y }));
            }
        }

        if(points.empty() || points.back().pos.x != vertices.front().pos.x ||
           points.back().pos.y != vertices.front().pos.y){
               points.push_back(vertices.front());
        }

        return points;
    }

}//namespace go