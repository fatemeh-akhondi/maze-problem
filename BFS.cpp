#include <iostream>
#include <bits/stdc++.h>
#include <queue>
using namespace std;
struct node{
    int row;
    int col;
    node* prev;
};
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
	return 0;
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
	return 0;
}//fuction to return next adress of col
queue <char> push(int m[7][6], bool visited[7][6], queue <char> safe, int row, int col){
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
}//function to push allnext safe nodes
char diagnose3(node* d){
    if( d->row == d->prev->row +1 ){
        return 'D';
    }
    if( d->row == d->prev->row -1 ){
        return 'U';
    }
    if( d->col == d->prev->col +1 ){
        return 'L';
    }
    if( d->col == d->prev->col -1 ){
        return 'R';
    }
	return ' ';
}
void PrintPath(node D){
    node* d = &D;
	cout<<"nodes you'll have to cross = ";
    while ( d != NULL ){
        cout<<"{"<<d->row<<", "<<d->col<<"}, ";
        d = d->prev;
    }
    cout<<endl;
    d = &D;
    stack <char> path;
    while ( d != NULL && d->prev != NULL ){
        path.push( diagnose3(d) );
        d = d->prev;
    }
	cout<<"path = ";
    while ( !path.empty() ){
        cout<<path.top();
        path.pop();
    }
}//prints the path and the nodes you'll have to cross
void BFS(int m[7][6], bool visited[7][6], queue <node> NextToVisit, int row, int col, int z, int w){
	node* tmp = new node;
	tmp->row = row;
	tmp->col = col;
    tmp->prev = NULL;
	NextToVisit.push((*tmp));//push the start node
    while( !NextToVisit.empty() ){
        visited[row][col] = true;
        if( row == z && col == w ){
            PrintPath( NextToVisit.front() );
            return;
        }
        queue <char> safe;
	    safe = push(m, visited, safe, row, col);
	    int a = safe.size();
        for( int i = 0; i < a; i++ ){
			node * temp = new node;
			temp->row = diagnose1(safe.front(), row);
			temp->col = diagnose2(safe.front(), col);
            temp->prev = &NextToVisit.front();
            NextToVisit.push((*temp));
            safe.pop();
        }//push all childs to queue
		NextToVisit.pop();
        row = NextToVisit.front().row;
        col = NextToVisit.front().col;
    }
    cout<<"there is no way"<<endl;
	return;
}
void WorldModel(int m[7][6], int row, int col, int z, int w){
	bool visited[7][6];// to mark visirted cells and avoid creation of loop
	memset(visited, false, sizeof(visited));
	queue <char> safe;
    queue <node> NextToVisit;
    BFS(m, visited, NextToVisit, row, col, z, w);
    return;
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