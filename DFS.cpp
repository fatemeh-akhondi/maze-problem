#include <iostream>
#include <stack>
#include <string>
#include <bits/stdc++.h>
using namespace std;
string paths;
bool IsSafe(int m[7][6], bool visited[7][6], int row, int col ){
	if(m[row][col] == 0 or visited[row][col] or row < 0 or col < 0 or row > 6 or col > 5 ){
		return false;
	}
	return true;
}
int diagnose1(char c, int row){
	if( c == 'U' ){
		return row-1;
	}
	if( c == 'D' ){
		return row +1;
	}
	if( c == 'R' or c == 'L'){
		return row;
	}
}//fuction to return next adress of row
int diagnose2(char c, int col){
	if( c == 'L' ){
		return col-1;
	}
	if( c == 'R' ){
		return col +1;
	}
	if( c == 'U' or c == 'D'){
		return col;
	}
}//fuction to return next adress of col
stack <char> push(int m[7][6], bool visited[7][6], string path, stack <char> safe, int row, int col){
	if(IsSafe(m, visited, row+1, col)){
		safe.push('D');
	}
	if(IsSafe(m, visited, row, col+1)){
		safe.push('R');
	}
	if(IsSafe(m, visited, row, col-1)){
		safe.push('L');
	}
	if(IsSafe(m, visited, row-1, col)){
		safe.push('U');
	}
	return safe;
}
void DFS(int m[7][6],bool visited[7][6], string &path, stack <char> safe, int shortest, int row, int col, int z, int w){
	cout<<"path = "<<path<<endl;
	cout<<"entered DFS"<<endl;
	if(!IsSafe(m, visited, row, col)){
		cout<<path<<", unsafe"<<endl;
		path.pop_back();
		return;
	}
	cout<<"safe"<<endl;
	if (row == z && col == w){
		cout<<"reached the end"<<endl;
		cout<<"paths = "<<path<<endl;
		if( !paths.empty() && path.size() < shortest ){
			shortest = path.size();
		}
		if ( paths.empty() ){
			shortest = path.size();
		}
		paths = path;
		exit;
	}
	cout<<"not the end"<<endl;
	if( !paths.empty() && path.size() >= shortest ){
		cout<<"path.size() >= shortest"<<endl;
		for (int j = 0; j < path.size(); j++){
			path.pop_back();
		}
		return;
	}
	cout<<"not bigger than shortest"<<endl;
	visited[row][col] = true;
	for (int i = 0; i < safe.size(); i++){ 
		safe.pop();
	}//empty the stack
	safe = push(m, visited, path, safe, row, col);//push all safe next nodes
	cout<<"safe.size = "<<safe.size()<<endl;
	cout<<"row = "<<row<<" col = "<<col<<endl;
	if( safe.size() < 1 ){
		cout<<"safe.size() = 0"<<endl;
		cout<<path<<endl;
		path.pop_back();
		cout<<path<<endl;
		return;
	}
	int a = safe.size();
	for (int i = 0; i< a; i++){
		cout<<"in loop"<<endl;
		char tmp = safe.top();//char to store the name of next node
		path.push_back(safe.top());
		safe.pop();
		cout<<"before recall"<<endl;
		cout<<"next node = "<<tmp<<endl;
		DFS(m, visited, path, safe, shortest, diagnose1(tmp, row), diagnose2(tmp, col), z, w);//ROW  AND COLUMN BY DIAGNOSE OR STH
		cout<<"after dfs"<<endl;
	}//calls DFS for all childs of current node
}
void WorldModel(int m[7][6], int row, int col, int z, int w){
	string path;// to store the path found with the algorithm
	bool visited[7][6];// to mark visirted cells and avoid creation of loop
	memset(visited, false, sizeof(visited));
	stack <char> safe;//to store all safe next nodes
	int shortest;//to stroe the least amounnt
	DFS(m, visited, path, safe, shortest, row, col, z, w);
	cout<<"*path = "<<paths;
}
int main(){
    int m[7][6] = { {1, 1, 1, 1, 0, 1},
					{1, 0, 1, 1, 1, 1},
					{1, 1, 0, 0, 0, 0},
					{1, 0, 0, 1, 1, 1},
					{1, 1, 1, 1, 0, 1},
					{1, 0, 0, 0, 0, 1},
					{1, 1, 1, 1, 1, 1}  };
    int x, y, z, w;
	x = 6;
	y = 2;
	z = 0;
	w = 5;
	WorldModel( m, x, y, z, w );
}
