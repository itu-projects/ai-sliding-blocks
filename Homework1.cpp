//Ilay Köksal
//150130051
//4 November 2016#include <vector>
#include <queue>
#include <stack>
#include <iostream>
using namespace std;

class block{
public:	
	int row;
	int col;
	int size;
	char position;	
};

class node{
public:	
	vector<block> blocks;
	vector<vector<int> > emptySpace;
	node *before;
	vector <node> children;

	bool canMoveUp(block block);
	bool canMoveDown(block block);
	bool canMoveRight(block block);
	bool canMoveLeft(block block);

	int newChildren(node &parent);
};

class puzzle{
public:
	node root;
	void DFS();
	void BFS();

	int expandedBfs=0;
	int generatedBfs=0;
	int expandedDfs=0;
	int generatedDfs=0;
	//int Astar1();
	//int Astar2();
};

bool node::canMoveUp(block block){
	if (block.position == 'v'){
		if (block.row > 0){
			if (emptySpace[block.row - 1][block.col] == 0){
				return 1; //UP
			}
		}
	}
	return 0;
};
bool node::canMoveDown(block block){
	if (block.position == 'v'){
		if (emptySpace[block.row + block.size][block.col] == 0 && block.row + block.size < 6){
			return 1; //DOWN
		}
	}
	return 0;
};
bool node::canMoveRight(block block){
	if (block.position == 'h'){
		if (emptySpace[block.row][block.col + block.size] == 0 && block.col + block.size < 6){
			return 1; //RIGHT
		}
	}
	return 0;
};
bool node::canMoveLeft(block block){
	if (block.position == 'h'){
		if (block.col > 0){
			if (emptySpace[block.row][block.col - 1] == 0){
				return 1; //LEFT
			}
		}
	}
	return 0;
}

int node::newChildren(node &parent){
	
	for (int j = 0; j < parent.blocks.size();j++){
		
		node childNode;

		if (parent.canMoveUp(parent.blocks[j])){ //MOVE UP
			childNode.blocks = parent.blocks;
			childNode.emptySpace = parent.emptySpace;
			childNode.before = &parent;
			
			childNode.emptySpace[childNode.blocks[j].row - 1 + childNode.blocks[j].size][childNode.blocks[j].col] = 0; //Now empty cell
			childNode.emptySpace[childNode.blocks[j].row - 1][childNode.blocks[j].col] = 1; //Now full cell
			childNode.blocks[j].row = childNode.blocks[j].row - 1;
			parent.children.push_back(childNode);
		}
		if (parent.canMoveDown(parent.blocks[j])){ //MOVE DOWN
			childNode.blocks = parent.blocks;
			childNode.emptySpace = parent.emptySpace;
			childNode.before = &parent;
			
			childNode.emptySpace[childNode.blocks[j].row][childNode.blocks[j].col] = 0; //Now empty cell
			childNode.emptySpace[childNode.blocks[j].row + childNode.blocks[j].size][childNode.blocks[j].col] = 1; //Now full cell
			childNode.blocks[j].row = childNode.blocks[j].row + 1;
			parent.children.push_back(childNode);
		}
		if (parent.canMoveLeft(parent.blocks[j])){ //MOVE LEFT
			childNode.blocks = parent.blocks;
			childNode.emptySpace = parent.emptySpace;
			childNode.before = &parent;
			
			childNode.emptySpace[childNode.blocks[j].row][childNode.blocks[j].col + childNode.blocks[j].size - 1] = 0; //Now empty cell
			childNode.emptySpace[childNode.blocks[j].row][childNode.blocks[j].col - 1] = 1; //Now full cell
			childNode.blocks[j].col = childNode.blocks[j].col - 1;
			parent.children.push_back(childNode);
		}
		if (parent.canMoveRight(parent.blocks[j])){ //MOVE RIGHT
			childNode.blocks = parent.blocks;
			childNode.emptySpace = parent.emptySpace;
			childNode.before = &parent;
			
			childNode.emptySpace[childNode.blocks[j].row][childNode.blocks[j].col] = 0; //Now empty cell
			childNode.emptySpace[childNode.blocks[j].row][childNode.blocks[j].col + childNode.blocks[j].size] = 1; //Now full cell
			childNode.blocks[j].col = childNode.blocks[j].col + 1;
			parent.children.push_back(childNode);
		}
	}

	return 0;
}

void puzzle::BFS(){

	queue<node> Q;
	Q.push(root);
	generatedBfs++;

	while (!Q.empty()){
		node x = Q.front();
		Q.pop();
		expandedBfs++;
		cout << "expanded" << expandedBfs<<endl;
		x.newChildren(x);

		for (int i = 0; i < x.children.size(); i++){
			if (x.children[i].blocks[0].col == 3){ //çözüm
				
				for (int j = 0; j < x.blocks.size(); j++){
					cout << x.children[i].blocks[j].row << " " << x.children[i].blocks[j].col << " " << x.children[i].blocks[j].size << " " << x.children[i].blocks[j].position << endl;
				}
				return;
			}
			else{
				Q.push(x.children[i]);				
				generatedBfs++;
				cout << "generated" <<generatedBfs << endl;
			}
		}

	}
}

void puzzle::DFS(){
	
	stack<node> S;
	S.push(root);
	generatedDfs++;

	while (!S.empty()){
		node x = S.top();
		S.pop();
		expandedDfs++;
		cout << "expanded" << expandedDfs<<endl;
		x.newChildren(x);

		for (int i = 0; i < x.children.size(); i++){

			if (x.children[i].blocks[0].col == 3){ //çözüm
				for (int j = 0; j < x.children[i].blocks.size(); j++){
					cout << x.children[i].blocks[j].row << " " << x.children[i].blocks[j].col << " " << x.children[i].blocks[j].size << " " << x.children[i].blocks[j].position << endl;
				}
				return;
			}
			else{
				S.push(x.children[i]);
				generatedDfs++;
				cout << "generated" <<generatedDfs << endl;
			}
				
		}

	}
}

int main(){

	puzzle example;
	example.root.before = NULL;

	for (int i = 0; i < 7; i++){
		vector<int> temp;
		for (int j = 0; j < 7; j++){
			temp.push_back(0);
		}
		example.root.emptySpace.push_back(temp);
	}

	for (int i = 0; i < 7; i++){
		block temp;
		example.root.blocks.push_back(temp);
	}

	example.root.blocks[0].row = 2;
	example.root.blocks[0].col = 1;
	example.root.blocks[0].size = 2;
	example.root.blocks[0].position = 'h';
	example.root.emptySpace[2][1] = 1;
	example.root.emptySpace[2][2] = 1;

	example.root.blocks[1].row = 2;
	example.root.blocks[1].col = 0;
	example.root.blocks[1].size = 2;
	example.root.blocks[1].position = 'v';
	example.root.emptySpace[2][0] = 1;
	example.root.emptySpace[3][0] = 1;

	example.root.blocks[2].row = 4;
	example.root.blocks[2].col = 0;
	example.root.blocks[2].size = 2;
	example.root.blocks[2].position = 'v';
	example.root.emptySpace[4][0] = 1;
	example.root.emptySpace[5][0] = 1;

	example.root.blocks[3].row = 3;
	example.root.blocks[3].col = 1;
	example.root.blocks[3].size = 2;
	example.root.blocks[3].position = 'v';
	example.root.emptySpace[3][1] = 1;
	example.root.emptySpace[4][1] = 1;

	example.root.blocks[4].row = 0;
	example.root.blocks[4].col = 3;
	example.root.blocks[4].size = 3;
	example.root.blocks[4].position = 'v';
	example.root.emptySpace[0][3] = 1;
	example.root.emptySpace[1][3] = 1;
	example.root.emptySpace[2][3] = 1;

	example.root.blocks[5].row = 5;
	example.root.blocks[5].col = 2;
	example.root.blocks[5].size = 2;
	example.root.blocks[5].position = 'h';
	example.root.emptySpace[5][2] = 1;
	example.root.emptySpace[5][3] = 1;

	example.root.blocks[6].row = 1;
	example.root.blocks[6].col = 4;
	example.root.blocks[6].size = 2;
	example.root.blocks[6].position = 'v';
	example.root.emptySpace[1][4] = 1;
	example.root.emptySpace[2][4] = 1;

	example.BFS();
	example.DFS();

	return 0;
}
