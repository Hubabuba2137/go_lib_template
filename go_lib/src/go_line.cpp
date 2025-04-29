#include <raylib.h>
#include <vector>
#include <iostream>
#include <string>

#include "go_node.hpp"
#include "go_line.hpp"

namespace go{
    Line::Line(Node a, Node b){
        this->start = a.pos;
        this->end = b.pos;
        
        if(a.pos.x != b.pos.x){
            this->a_coe = (a.pos.y - b.pos.y) / (a.pos.x - b.pos.x);
            this->b_coe = a.pos.y - this->a_coe * a.pos.x;
        }
        else{
            this->a_coe = 0;
            this->b_coe = a.pos.x; 
        }
    }
    
    void Line::draw(int window_x, bool write_text){
        int start_x, start_y, end_x, end_y;
    
        if(this->start.x != this->end.x){
            start_x = 100 - window_x;
            start_y = this->a_coe * start_x + this->b_coe; 
            end_x = window_x + 100;
            end_y = this->a_coe * end_x + this->b_coe;
        }
        else{
            start_x = this->start.x;
            start_y = 100 - window_x; //zakładamy że ekran jest kwadratem
            end_x = start_x;
            end_y = window_x + 100;
        }
    
        DrawLine(start_x, start_y, end_x, end_y, RED);
    
        if(write_text){
            if(this->start.x != this->end.x){
                int text_pos_x = this->start.x;
                int text_pos_y = this->a_coe * text_pos_x + this->b_coe + 50;
            
                std::string text = "y = " + std::to_string(this->a_coe) + "x + " + std::to_string(this->b_coe);
                DrawText(text.c_str(), text_pos_x, text_pos_y, 10, WHITE);
            }
            else{
                int text_pos_x = start_x + 20; 
                int text_pos_y = (start_y + end_y) / 2;
                std::string text = "x = " + std::to_string(start_x);
                DrawText(text.c_str(), text_pos_x, text_pos_y, 10, WHITE);
            }
        }
    }
    
    bool Line::solve_equation(float x, float y){
        if(y == this->a_coe*x + this->b_coe){
            return true;
        }
        else{
            return false;
        }
    }
}