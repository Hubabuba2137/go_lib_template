#include <iostream>
#include <vector>
#include <cmath>

#include "go_lib.hpp"

namespace go{
    bool is_node_inside(Vertex vert, Node node) {
        if (vert.edges.size() == 3 && vert.vertices.size() == 3) {
            return is_node_inside_trian(vert, node);
        } 
        else {
            int intersections = 0;
            for (const Segment &seg : vert.edges) {
                if (ray_intersects_segment(node, seg)) {
                    ++intersections;
                }
            }
            if(intersections%2 == 0){
                return false;
            }
            else{
                return true;
            }
        }
    }

    bool is_inside_polygon(go::Node &point, std::vector<go::Node> &polygon) {
        bool inside = false;
        int n = polygon.size();
        for (int i = 0; i < n; i++){
            int j = (i + 1) % n;
            if (((polygon[i].pos.y > point.pos.y) != (polygon[j].pos.y > point.pos.y)) &&
                (point.pos.x < (polygon[j].pos.x - polygon[i].pos.x) *
                (point.pos.y - polygon[i].pos.y) / (polygon[j].pos.y - polygon[i].pos.y) + polygon[i].pos.x)){
                    inside = !inside;
            }
        }
        return inside;
    }
    

    bool is_node_inside_trian(Vertex vert, Node node) {
        Node a = vert.vertices[0];
        Node b = vert.vertices[1];
        Node c = vert.vertices[2];
    
        Vector2 p = node.pos;
    
        float cross1 = (b.pos.x - a.pos.x) * (p.y - a.pos.y) - (b.pos.y - a.pos.y) * (p.x - a.pos.x);
        float cross2 = (c.pos.x - b.pos.x) * (p.y - b.pos.y) - (c.pos.y - b.pos.y) * (p.x - b.pos.x);
        float cross3 = (a.pos.x - c.pos.x) * (p.y - c.pos.y) - (a.pos.y - c.pos.y) * (p.x - c.pos.x);
    
        bool has_same_sign = (cross1 >= 0 && cross2 >= 0 && cross3 >= 0) || (cross1 <= 0 && cross2 <= 0 && cross3 <= 0);
        return has_same_sign;
    }

    float cross(const Vector2& a, const Vector2& b, const Vector2& c) {
        return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    }

    bool is_convex(const Vector2& prev, const Vector2& curr, const Vector2& next) {
        return cross(prev, curr, next) > 0; 
    }


    bool is_ear(const std::vector<Node>& poly, int i) {
        int prev = (i - 1 + poly.size()) % poly.size();
        int next = (i + 1) % poly.size();

        if (!is_convex(poly[prev].pos, poly[i].pos, poly[next].pos)){
            return false;
        }

        Vertex triangle({ poly[prev], poly[i], poly[next] });

        for (int j = 0; j < poly.size(); ++j) {
            if (j == prev || j == i || j == next){
                continue;
            }
            if (is_node_inside_trian(triangle, poly[j])){
                return false;
            }
        }

        return true;
    }

    std::vector<Vertex> ear_cut_triangulation(const Vertex& polygon) {
        std::vector<Node> verts = polygon.vertices;
        std::vector<Vertex> triangles;

        if (verts.size() < 3) {
            std::cout << "Polygon too small to triangulate\n";
            return {};
        }

        while (verts.size() > 3) {
            bool ear_found = false;

            for (size_t i = 0; i < verts.size(); ++i) {
                if (is_ear(verts, i)) {
                    int prev = (i - 1 + verts.size()) % verts.size();
                    int next = (i + 1) % verts.size();

                    std::vector<Node> tri = { verts[prev], verts[i], verts[next] };
                    triangles.push_back(Vertex(tri));
                    verts.erase(verts.begin() + i);
                    ear_found = true;
                    break;
                }
            }

            if (!ear_found) {
                break;
            }
        }

        if (verts.size() == 3) {
            triangles.push_back(Vertex(verts));
        }

        return triangles;
    }

    int calc_nodes_inside(const std::vector<Node> &nodes, Vertex shape, std::vector<Node> *inside_nodes) {
        int n = 0;
        std::vector<Vertex> triangulation = ear_cut_triangulation(shape);

        std::vector<float> shape_bounds = shape.get_bounds();
        float min_x = shape_bounds[0];
        float max_x = shape_bounds[1];
        float min_y = shape_bounds[2];
        float max_y = shape_bounds[3];

        for (const Node &it : nodes) {
            if (it.pos.x < min_x || it.pos.x > max_x || it.pos.y < min_y || it.pos.y > max_y) {
                continue;
            }

            bool is_inside = false;
            for (Vertex &trian : triangulation) {
                float min_x_t = trian.get_bounds()[0];
                float max_x_t = trian.get_bounds()[1];
                float min_y_t = trian.get_bounds()[2];
                float max_y_t = trian.get_bounds()[3];

                if (it.pos.x < min_x_t || it.pos.x > max_x_t || it.pos.y < min_y_t || it.pos.y > max_y_t) {
                    continue;
                }

                if (is_node_inside_trian(trian, it)) {
                    is_inside = true;
                    //inside_nodes->push_back(it);
                    break;
                }
            }

            if (is_inside) {
                ++n;
            }
        }

        return n;
    }
}

//--------------------porównanie metod triangulacji-------------------//
/*
void basic(std::vector<go::Node> &nodes, go::Vertex shape){
    int n=0;
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    for(go::Node it: nodes){
        if(go::is_node_inside(shape, it)){
            ++n;
        }
    }

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cout << "Basic approach time = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[us]" << std::endl;
    std::cout<<"Number of nodes inside shape = "<<n<<"\n";
}

void improved(std::vector<go::Node> &nodes, go::Vertex shape){
    int n=0;
    std::chrono::steady_clock::time_point begin_2 = std::chrono::steady_clock::now();
    std::vector<float> bounds = shape.get_bounds(); //min_x, max_x, min_y, max_y

    for(go::Node it: nodes){
        if(it.pos.x >= bounds[0] || it.pos.y <= bounds[1], it.pos.y >= bounds[2], it.pos.y <= bounds[3]){
            if(go::is_node_inside(shape, it)){
                ++n;
            }
        }
    }
    std::chrono::steady_clock::time_point end_2 = std::chrono::steady_clock::now();

    std::cout << "Improved basic approach time = " << std::chrono::duration_cast<std::chrono::microseconds>(end_2 - begin_2).count() << "[us]" << std::endl;
    std::cout<<"Number of nodes inside shape = "<<n<<"\n";
}

void triangulation(std::vector<go::Node> &nodes, go::Vertex shape){
    int n=0;
    std::chrono::steady_clock::time_point begin_3 = std::chrono::steady_clock::now();

    std::vector<go::Node> nodes_inside;

    n = go::calc_nodes_inside(nodes, shape, &nodes_inside);

    std::chrono::steady_clock::time_point end_3 = std::chrono::steady_clock::now();

    std::cout << "Triangulation approach time = " << std::chrono::duration_cast<std::chrono::microseconds>(end_3 - begin_3).count() << "[us]" << std::endl;
    std::cout<<"Number of nodes inside shape = "<<n<<"\n";
}
*/