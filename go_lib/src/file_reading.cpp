#include <iostream>
#include <raylib.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>

#include "go_lib.hpp"
#include "file_reading.hpp"

namespace go{
    std::vector<Node> read_nodes(std::string filename){
        std::fstream plik;
        plik.open(filename);

        if(!plik.good()){
            std::cout<<"Couldn't read a file"<<std::endl;
        }

        std::vector<Node> nodes;
        std::string temp_line;
        
        while(getline(plik, temp_line)){
            if(temp_line != "*ELEMENTS"){
                if(temp_line != "*NODES"){
                    //cout<<temp_line<<"\n";
                    std::istringstream iss(temp_line);
                    std::string temp_id, temp_x, temp_y;
                    iss >> temp_id >> temp_x >> temp_y;

                    int id = atoi(temp_id.c_str());
                    float x = atoi(temp_x.c_str());
                    float y = atoi(temp_y.c_str());

                    if(id != 0){
                        Node temp_node((Vector2){x,y});
                        nodes.push_back(temp_node);
                    }
                }
            }
            else{
                break;
            }
        }

        return nodes;
    }

    std::vector<std::string> load_vertex_info(std::string filename){
        std::vector<std::string> vertex_info;
        std::fstream plik;
        plik.open(filename);

        if(!plik.good()){
            std::cout<<"Couldn't read a file"<<std::endl;
        }

        std::string temp_line;
        
        while(temp_line!="*ELEMENTS"){
            plik>>temp_line;
        }
        while(getline(plik, temp_line)){
            vertex_info.push_back(temp_line);
        }

        return vertex_info;
    }

    std::vector<go::Vertex> load_vertexes_from_file(std::vector<go::Node> &nodes, std::vector<std::string> &vertex_info){
        std::vector<go::Vertex> result;

        for( std::string temp_line: vertex_info){
            std::vector<int> node_ids;
            std::vector<go::Node> temp_nodes; 

            std::istringstream iss(temp_line);
            std::string token;
            iss >> token;

            if(atoi(token.c_str()) != 0){

                while (iss >> token) {
                    int id_temp = atoi(token.c_str());
                    node_ids.push_back(id_temp);
                }

                for(long long unsigned int i = 0; i < node_ids.size(); i++){
                    temp_nodes.push_back(nodes[node_ids[i]-1]);
                    
                    //cout<<"\t"<<node_ids[i]<<": x="<<nodes[node_ids[i]-1].pos.x;
                    //cout<<" y="<<nodes[node_ids[i]-1].pos.y<<"\n";
                }

                go::Vertex temp_vertex(temp_nodes);
                result.push_back(temp_vertex);
            }
        }
        return result;
    }

    void create_nodes(int n, std::string filepath, std::string filename) {
        std::string full_path = filepath + "\\" + filename;
        std::ofstream file(full_path);

        if (!file.is_open()) {
            std::cout << "Failed to create the file: " << full_path << std::endl;
            return;
        }

        std::srand(std::time(nullptr));

        file << "*NODES" << std::endl;

        for (int i = 1; i <= n; ++i) {
            int x = std::rand() % (751-100) + 50; 
            int y = std::rand() % (751-100) + 50; 
            file << i << " " << x << " " << y << std::endl;
        }

        file.close();
        std::cout << "File created successfully: " << full_path << std::endl;
    }

    std::vector<go::Vertex> create_vertexes(int number_of_vert, int lower_nodes, int upper_nodes, std::vector<go::Node> nodes){
        std::vector<go::Vertex> result;
        std::vector<go::Node> result_nodes;
        std::srand(std::time(nullptr));

        for(int i=0; i<number_of_vert; i++){
            int number_of_nodes = std::rand() % (upper_nodes-lower_nodes) + lower_nodes;
            for(int j = 0; j<number_of_nodes; j++){
                int x = std::rand() % 801; 
                int y = std::rand() % 801;
                Node temp(x, y);
                result_nodes.push_back(temp);

            }
            go::Vertex res(result_nodes);
            result.push_back(res);
        }

        return result;
    }

    void prep_file(std::string filepath, std::string filename, std::string newfile){
        std::string full_path = filepath + "\\" + filename;

        std::fstream plik;
        plik.open(full_path);

        if(!plik.good()){
            std::cout<<"Couldn't read a file"<<std::endl;
        }

        std::vector<Node> nodes;
        std::string temp_line;
        
        while(getline(plik, temp_line)){
            std::istringstream iss(temp_line);
            std::string temp_x, temp_y;
            iss >> temp_x >> temp_y;

            float x = atoi(temp_x.c_str())*2;
            float y = atoi(temp_y.c_str())*2;

            Node temp_node((Vector2){x,y});
            nodes.push_back(temp_node);
        }

        std::string new_full_path = filepath + "\\" + newfile;

        std::ofstream file(new_full_path);

        if (!file.is_open()) {
            std::cout << "Failed to create the file: " << new_full_path << std::endl;
            return;
        }

        int n = nodes.size();
        file << "*NODES" << std::endl;
        for (int i = 1; i <= n; ++i) {
            file << i <<" " << nodes[i].pos.x<<" " << nodes[i].pos.y<<std::endl;
        }

        file.close();
        
    }
}