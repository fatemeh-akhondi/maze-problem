#include <iostream>
#include <cstdlib>
#include <bits/stdc++.h>
using namespace std;
struct dis{
	int val;
	char charc;
};
bool IsSafe(int m[7][6], bool visited[7][6], int row, int col ){
	if(m[row][col] == 0 or m[row][col] == 2 or visited[row][col] or row < 0 or col < 0 or row > 6 or col > 5 ){
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
bool compare(dis i1, dis i2){
	return (i1.val < i2.val);
}
void sort(int U, int D, int L, int R, char arr[4]){
	dis sorted[4];
	sorted[0].charc = 'U';
	sorted[0].val = U;
	sorted[1].charc = 'D';
	sorted[1].val = 'D';
	sorted[2].charc = 'L';
	sorted[2].val = L;
	sorted[3].charc = 'R';
	sorted[3].val = R;
	sort(sorted, sorted+4, compare);
	for ( int i = 0; i < 4; i++){
		arr[i] = sorted[i].charc;
	}
}//sorts the variables indecending order and returns an array of char
char closest(int m[7][6], bool visited[7][6], int row, int col, int z, int w){
	int U, D, L, R;//integers to keep the distance from m[row][col] to m[z][w]
	U = abs(z - (row - 1)) + abs((w - col)); 
	D = abs(z - (row + 1))+ abs((w - col));
	L = abs(z - row) + abs(w - (col - 1));
	R = abs(z - row) + abs(w - (col + 1));
	char sorted[4];//array to keep the next nodes by descending distance to the destination node
	sort(U, D, L, R, sorted);
	int i = 0;
	for ( i = 0; i < 4;  i++){
	    if  (IsSafe( m, visited, diagnose1( sorted[i], row ), diagnose2( sorted[i], col ) ) ){
	        return sorted[i];
	    }
	}
	if  ( !IsSafe( m, visited, diagnose1( sorted[i], row ), diagnose2( sorted[i], col ) ) ){
	    m[row][col] = 2;
	    return NULL;
	}
}//function to return the closest to the end safe next node
void greedy(int m[7][6],bool visited[7][6], string path, int row, int col, int z, int w){
	if(!IsSafe(m, visited, row, col)){
		return;
	}
	if (row == z && col == w){
	    cout<<"path = "<<path<<endl;
		return;
	}
	visited[row][col]  = true;
	int q = closest(m, visited, row, col, z, w);//character to store the address of the closer next node
	if (q == NULL ){
	    return;
	}
	path.push_back(q);
	greedy(m, visited, path, diagnose1(q,row), diagnose2(q,col), z, w);
	if ( m[diagnose1(q,row)][diagnose2(q,col)] == 2 ){
	    visited[row][col] = false;
	    path.pop_back();
	    greedy(m, visited, path, row, col, z, w);
	}
}
void WorldModel(int m[7][6], int row, int col, int z, int w){
	string path;// to store the path found with the algorithm
	bool visited[7][6];// to mark visirted cells and avoid creation of loop
	memset(visited, false, sizeof(visited));
	greedy(m, visited, path, row, col, z, w);
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
	x = 0;
	y = 5;
	z = 6;
	w = 2;
	WorldModel(m, x, y, z, w);
}
