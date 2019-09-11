#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
#include <stack>
#include <string.h>

using namespace std;

vector<vector<char>> tmp(9, vector<char>(9, '0'));

typedef struct node
{
	int value;
	int index;
	char board[81];
}Node, *Tree;

void boardToStr(vector<vector<char>> board, char layout[81])
{
	for(int i = 0; i < 9; i ++)
		for(int j = 0; j < 9; j ++)
			layout[i*9+j] = board[i][j];
}

void strToBoard(vector<vector<char>> &board, char layout[81])
{
	for(int i = 0; i < 9; i ++)
		for(int j = 0; j < 9; j ++)
			board[i][j] = layout[i*9+j];
}

bool ifduplicated(vector<char> test)
{
    for(int i = 0; i < 9; i ++)
    {
        if(test[i] == '.')
            continue;
        for(int j = i + 1; j < 9; j ++)
		{
			if(test[j] == test[i])
			    return false;
		}
    }
	return true;
}

bool isValid(char* layout, int index)
{
	
	for(int i = 0; i < 9; i ++)
		for(int j = 0; j < 9; j ++)
			tmp[i][j] = layout[i*9+j];
	
	int row = index / 9;
	int col = index % 9;
	
	if(!ifduplicated(tmp[row]))
		return false;
		
	vector<char> foo;
	for(int i = 0; i < 9; i ++)
		foo.push_back(tmp[i][col]) ;
	if(!ifduplicated(foo))
	{
		foo.clear();
		return false;
	}
	foo.clear();
	
	int i = (row / 3) * 3 + col / 3;
	for(int m = 0; m < 3; m ++)
		for(int n = 0; n < 3; n ++)
			foo.push_back(tmp[i-i%3+m][(i%3)*3+n]);

	if(!ifduplicated(foo))
	{
		foo.clear();
		return false;
	}
	
	return true;
}

int main()
{	
	/*
	[["5","3",".",".","7",".",".",".","."],
	["6",".",".","1","9","5",".",".","."],
	[".","9","8",".",".",".",".","6","."],
	["8",".",".",".","6",".",".",".","3"],
	["4",".",".","8",".","3",".",".","1"],
	["7",".",".",".","2",".",".",".","6"],
	[".","6",".",".",".",".","2","8","."],
	[".",".",".","4","1","9",".",".","5"],
	[".",".",".",".","8",".",".","7","9"]]*/
	
	/*
	[[".",".","9","7","4","8",".",".","."],
	["7",".",".",".",".",".",".",".","."],
	[".","2",".","1",".","9",".",".","."],
	[".",".","7",".",".",".","2","4","."],
	[".","6","4",".","1",".","5","9","."],
	[".","9","8",".",".",".","3",".","."],
	[".",".",".","8",".","3",".","2","."],
	[".",".",".",".",".",".",".",".","6"],
	[".",".",".","2","7","5","9",".","."]]*/
	
	vector<char> row_1 = {'5', '3', '.', '.', '7', '.', '.', '.', '.'};
	vector<char> row_2 = {'6', '.', '.', '1', '9', '5', '.', '.', '.'};
	vector<char> row_3 = {'.', '9', '8', '.', '.', '.', '.', '6', '.'};
	vector<char> row_4 = {'8', '.', '.', '.', '6', '.', '.', '.', '3'};
	vector<char> row_5 = {'4', '.', '.', '8', '.', '3', '.', '.', '1'};
	vector<char> row_6 = {'7', '.', '.', '.', '2', '.', '.', '.', '6'};
	vector<char> row_7 = {'.', '6', '.', '.', '.', '.', '2', '8', '.'};
	vector<char> row_8 = {'.', '.', '.', '4', '1', '9', '.', '.', '5'};
	vector<char> row_9 = {'.', '.', '.', '.', '8', '.', '.', '7', '9'};
	
	int num_solution = 0;
	vector<char*> solution;
	//vector<vector<char>> board = {row_1, row_2, row_3, row_4, row_5, row_6, row_7, row_8, row_9};
	vector<vector<char>> board =  {{'.', '.', '9', '7', '4', '8', '.', '.', '.'},
								   {'7', '.', '.', '.', '.', '.', '.', '.', '.'},
								   {'.', '2', '.', '1', '.', '9', '.', '.', '.'},
								   {'.', '.', '7', '.', '.', '.', '2', '4', '.'},
								   {'.', '6', '4', '.', '1', '.', '5', '9', '.'},
								   {'.', '9', '8', '.', '.', '.', '3', '.', '.'},
								   {'.', '.', '.', '8', '.', '3', '.', '2', '.'},
								   {'.', '.', '.', '.', '.', '.', '.', '.', '6'},
								   {'.', '.', '.', '2', '7', '5', '9', '.', '.'}};
	
	char *layout = new char[81];
	boardToStr(board, layout);
	
	stack<Node*> s;
	bool addNewNode = true;
	
	Tree head = new Node();
	head->value = -1;
	head->index = 0;
	boardToStr(board, head->board);

	s.push(head);
	while(!s.empty())
	{
		Node* top = s.top();
		s.pop();	
		int n = top->index;
		int value = top->value; 
		
		if(value != -1)
			layout = top->board;

		while(layout[n] != '.' && n < 81)
		{
			n ++;
		}
		
		if(n == 81)
		{
			num_solution ++;
			solution.push_back(layout); 
			continue;
		}
			
		for(int i = 1; i < 10; i ++)
		{
			layout[n] = '0' + i;
			if(!isValid(layout, n))
				continue;
			else
			{
				Node* newNode = new Node();
				newNode->value = i;
				newNode->index = n;
				strcpy(newNode->board, layout);
				s.push(newNode); 
			}
		}		
				
	}
	
	strToBoard(board, solution[0]);	
	for(int i = 0; i < 9; i ++)
	{
		for(int j = 0; j < 9; j ++)
			cout << board[i][j] << " ";
		cout << endl;		
	}

	return 0;	
	
} 
