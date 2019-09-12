#include <iostream>
#include <vector>
#include <string>
using namespace std;
enum state 
{   blackTownhall=-1, 
    whiteTownhall =1, 
    unoccupied=0,
    blackSoldier= -2,
    whiteSoldier=2
};
vector<state> seedVec(8, unoccupied);
class CannonBoard
{
	vector< vector<state> > board;
	public:
	CannonBoard(): board(8, seedVec)
	{
		for(int i=0;i<8;i++){
			for(int j=0;j<8;++j){
				if((i==0)&&(j==0||j==2||j==4||j==6))
					board[i][j]=whiteTownhall;
				else if((i==0||i==1||i==2)&&(j==1||j==3||j==5||j==7))
					board[i][j]=whiteSoldier;
				else if((i==7||i==6||i==5)&&(j==0||j==2||j==4||j==6))
					board[i][j]=blackSoldier;
				else if((i==7)&&(j==1||j==3||j==5||j==7))
					board[i][j]=blackTownhall;
			}
		}
	}
	bool move(pair<int, int> start, pair<int, int> end)
	{
		state dum=board[start.first][start.second];
		board[start.first][start.second]=unoccupied;
		board[end.first][end.second]=dum;
		return true;
	}
	bool shoot(pair<int, int> start, pair<int, int> end)
	{
		board[end.first][end.second]=unoccupied;
		return true;
	}

	void print()
	{
		for(int i=0;i<8;i++){
			for(int j=0;j<8;++j){
				cout<<board[i][j]<<"\t";
			}
			cout<<endl;
		}
	}
};
int main()
{
	string command="";
	CannonBoard ourBoard;
	ourBoard.print();
	while(true){
		getline (cin, command); 
		if(command.length()<11)
			break;
		pair<int, int> init=make_pair((int)command[2]-48, (int)command[4]-48 );
		pair<int, int> target=make_pair((int)command[8]-48, (int)command[10]-48 );
		if(command[6]=='M')
		{
			ourBoard.move(init, target);
		}
		else if(command[6]=='S')
		{
			ourBoard.shoot(init, target);
		}
		ourBoard.print();

	}
	
	return 0;
}
