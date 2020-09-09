#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h> 
using namespace std;
bool IsSafe(int m[7][6], bool visited[7][6], int row, int col ){
	if(m[row][col] == 0 or visited[row][col] or row < 0 or col < 0 or row > 6 or col > 5 ){
		return false;
	}
	return true;
}
void PrintPathTil(int m[7][6], bool visited[7][6], vector <char> &path, vector < vector<char> > &paths, int row, int col, int z, int w){
	if(!IsSafe(m, visited, row , col)){
		return;
	}
	if(row == z && col == w){
		paths.push_back(path);
		return;
	}
	visited[row][col] = true;
	if(IsSafe(m, visited, row+1, col)){
		path.push_back('D');
		PrintPathTil(m, visited, path, paths, row+1,  col, z, w);
		path.pop_back();
	}
	if(IsSafe(m, visited, row, col+1)){
		path.push_back('R');
		PrintPathTil(m, visited, path, paths, row, col+1, z, w);
		path.pop_back();
	}
	if(IsSafe(m, visited, row, col-1)){
		path.push_back('L');
		PrintPathTil(m, visited, path, paths, row,  col-1, z, w);
		path.pop_back();
	}
	if(IsSafe(m, visited, row-1, col)){
		path.push_back('U');
		PrintPathTil(m, visited, path, paths, row-1,  col, z, w);
		path.pop_back();
	}
	visited[row][col] = false;
}
void BrouteForce(int m[7][6], int x, int y, int z, int w){
	vector < vector<char> > paths;
	vector <char> path;
	bool visited[7][6];
	memset(visited, false, sizeof(visited));//to equal all memebers tto false
	PrintPathTil(m, visited, path, paths, x,  y, z, w);
	for (int i = 0; i < paths.size(); i++){
		for(int j =0 ; j< paths.at(i).size() ; j++){
	    	cout << paths.at(i).at(j) << " ";
		}
		cout<<endl;
	}
}
//applies broute force algorithm on the given 2D array
int main(){
	int m[7][6] = { {1, 1, 1, 1, 0, 1},
					{1, 0, 1, 1, 1, 1},
					{1, 1, 0, 0, 0, 0},
					{1, 0, 0, 1, 1, 1},
					{1, 1, 1, 1, 0, 1},
					{1, 0, 0, 0, 0, 1},
					{1, 1, 1, 1, 1, 1}  };
	int x,y,z,w;
	x = 6;
	y = 2;
	z = 0;
	w = 5;
	BrouteForce(m, x, y, z, w);		
}
