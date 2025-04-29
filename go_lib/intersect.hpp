#pragma once
#include <iostream>
#include <vector>
#include <cmath>

#include "go_lib.hpp"

namespace go
{
    bool is_node_inside(Vertex vert, Node node);
    bool is_node_inside_trian(Vertex vert, Node node);
    bool is_inside_polygon(go::Node &point, std::vector<go::Node> &polygon);

    float cross(const Vector2& a, const Vector2& b, const Vector2& c);
    bool is_convex(const Vector2& prev, const Vector2& curr, const Vector2& next);
    bool is_ear(const std::vector<Node>& poly, int i);
    std::vector<Vertex> ear_cut_triangulation(const Vertex& polygon);
    int calc_nodes_inside(const std::vector<Node> &nodes, Vertex shape, std::vector<Node> *inside_nodes);
} // namespace go
