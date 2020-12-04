/*---------------
Nombre: Johann Palomino Galvan
Matricula: A00517153
Actividad: Act 3.3
---------------*/

#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <fstream>
#include <bits/stdc++.h>
#pragma once

class Graph{
    private: 
        std::vector<std::vector<int>> adj_matrix,adj_list;
        int nu_vert, nu_edges;
    public:
        Graph();
        std::string printAdjMat();
        std::string printAdjList();
		std::string DFS(int init_v, int target_v);
		std::string BFS(int init_v, int target_v);
		std::string to_string(int i);
		std::string print_vector(std::vector<int> vec);
		void loadGraphMat(std::string filename, int v, int edges);
		void loadGraphList(std::string filename, int v, int edges);
};

Graph::Graph():nu_vert(0),nu_edges(0){}


std::string Graph::printAdjMat(){
	std::string res="";
	for(int i=0; i<adj_matrix.size();i++){
		for(int j=0;j<adj_matrix[i].size();j++){
			res+=to_string(adj_matrix[i][j])+" ";
		}
	}
	return res;
}

std::string Graph::printAdjList(){
	std::string res = "";
	for(int i=0; i<adj_list.size(); i++){
		res += "vertex " + to_string(i) + " : ";
		sort(adj_list[i].begin(), adj_list[i].end());
		for(int j=0; j<adj_list[i].size(); j++){
			res += to_string(adj_list[i][j]) + " ";
		}
	}
	return res;
}

std::string Graph::DFS(int init_v, int target_v){
	std::vector<std::vector<int>> adj_list_copy;
	for(int i=0;i<adj_list.size();i++){
	    adj_list_copy.push_back(adj_list[i]);
	}
	std::vector<int> stack;
	std::vector<int> visit;
	int current = init_v;
	bool find = false;	
	while(!find && !(visit.size()>=nu_vert)){
		bool already_visited=false;
		for(int i=0;i<visit.size();i++){
			if(current==visit[i]){
				already_visited=true;
				break;
			}
		}
		if(!already_visited){visit.push_back(current);}
		if(current==target_v){
			find=true;
			break;
		}
		for(int i=0;i<adj_list_copy[current].size();i++){
			for(int j=0;j<visit.size();j++){
				if(adj_list_copy[current][i]==visit[j])
					adj_list_copy[current].erase(adj_list_copy[current].begin()+i);
			}
		}
		if(adj_list_copy[current].size()>0){
			stack.push_back(current);
			int temp_index = current;
			current=adj_list_copy[current].back();
			adj_list_copy[temp_index].pop_back();
		}else{
			current = stack[stack.size()-1];
			stack.pop_back();
		}
	}
	stack.push_back(current);
	std::string visited_str=print_vector(visit);
	std::string path_str=print_vector(stack);
	std::string res="visited: "+visited_str+"path: "+path_str;
	res=res.substr(0,res.size()-1);
	return res;
}

std::string Graph::BFS(int init_v, int target_v){
	std::vector<std::vector<int>>queue;
	std::vector<std::vector<int>>visit;
	int current=init_v;
	int parent=-1;
	bool find=false;

	while(true){
		visit.push_back(std::vector<int>({parent, current}));
		if (current == target_v){
			find = true;
			break;
		}
		for(int i=0;i<adj_list[current].size();i++){
			int val=adj_list[current][i];
			bool already_visited=false;
			for(int j=0;j<visit.size();j++){
				if(visit[j][1]==val){
					already_visited=true;
					break;
				}
			}
			if(!already_visited)queue.push_back(std::vector<int>({current,val}));
		}
		parent=queue[0][0];
		current=queue[0][1];
		queue.erase(queue.begin());
	}
	std::vector<int>path;
	int fnd=target_v;	
	do{
		for(int i=0;i<visit.size();i++){
			if(visit[i][1]==fnd){
				path.insert(path.begin(),fnd);
				fnd=visit[i][0];
			}
		}
	}while(fnd!=-1);

	std::vector<int>converted_visited;
	for(int i=0;i<visit.size();i++){
		converted_visited.push_back(visit[i][1]);
	}
	std::string visited_str=print_vector(converted_visited);
	std::string path_str=print_vector(path);
	std::string res="visited: "+visited_str+"path: "+path_str;
	res=res.substr(0,res.size()-1);
	return res;	
}

std::string Graph::to_string(int i){
	std::stringstream aux;
	aux<<i;
	return aux.str();
}

std::string Graph::print_vector(std::vector<int> vec){
	std::string result="";
	for(int i=0;i<vec.size();i++){
		result=result+to_string(vec[i])+" ";
	}
	return result;
}

void Graph::loadGraphMat(std::string filename, int v, int edges){
	nu_vert=v;
	nu_edges=edges;
	for(int i=0;i<v;i++){
		std::vector<int>row(v,0);
		adj_matrix.push_back(row);
	}
	std::ifstream file;
	file.open(filename.c_str());
	while(file.good()){
		std::string init_vertex;
		std::string end_vertex;
		getline(file,init_vertex,',');
		getline(file,end_vertex,'\n');
		init_vertex=init_vertex.substr(1,init_vertex.length()-1);
		end_vertex=end_vertex.substr(1,end_vertex.length()-2);
		std::stringstream init(init_vertex);
		int init_node;
		init>>init_node;
		std::stringstream end(end_vertex);
		int end_node;
		end>>end_node;
		adj_matrix[init_node][end_node]=1;
		adj_matrix[end_node][init_node]=1;
	}
}

void Graph::loadGraphList(std::string filename, int v, int edges){
	nu_vert=v;
	nu_edges=edges;
	for(int i=0;i<v;i++){
		std::vector<int> row;
		adj_list.push_back(row);
	}
	std::ifstream file;
	file.open(filename.c_str());
	while(file.good()){
		std::string init_vertex;
		std::string end_vertex;
		getline(file,init_vertex,',');
		getline(file,end_vertex,'\n');
		init_vertex=init_vertex.substr(1,init_vertex.length()-1);
		end_vertex=end_vertex.substr(1,end_vertex.length()-2);
		std::stringstream init(init_vertex);
		
		int init_node;
		init>>init_node;
		std::stringstream end(end_vertex);
		int end_node;
		end>>end_node;
		adj_list[init_node].push_back(end_node);
		adj_list[end_node].push_back(init_node);
	}
}

#endif