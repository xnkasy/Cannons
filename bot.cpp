#include <iostream>
#include <vector>
#include <string>
using namespace std;
enum state 
{   blackTownhall=-1, 
    whiteTownhall =1, 
    unoccupied=0,
    null=INT_MIN,
    blackSoldier= -2,
    whiteSoldier=2
};
// enum cannontype
// {
// 	vertical=0,
// 	hor=1,
// 	rdiag=2,
// 	ldiag=3
// };

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
	state access(int i, int j)
	{
		if(i<8&&j<8)
			return board[i][j];
		return null;
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
		if((start.first-end.first)==-2 && (start.second-end.second)==-2)
			if(board[start.first+1][start.second+1]!=unoccupied)
				return false;
		else if((start.first-end.first)==-3 && (start.second-end.second)==-3)
			if(board[start.first+1][start.second+1]!=unoccupied)
				return false;
		if((start.first-end.first)==-2 && (start.second-end.second)==0)
			if(board[start.first+1][start.second]!=unoccupied)
				return false;
		else if((start.first-end.first)==-3 && (start.second-end.second)==0)
			if(board[start.first+1][start.second]!=unoccupied)
				return false;	
		if((start.first-end.first)==-2 && (start.second-end.second)==2)
			if(board[start.first+1][start.second-1]!=unoccupied)
				return false;
		else if((start.first-end.first)==-3 && (start.second-end.second)==3)
			if(board[start.first+1][start.second-1]!=unoccupied)
				return false;

		if((start.first-end.first)==0 && (start.second-end.second)==-2)
			if(board[start.first][start.second+1]!=unoccupied)
				return false;
		else if((start.first-end.first)==0 && (start.second-end.second)==-3)
			if(board[start.first][start.second+1]!=unoccupied)
				return false;	
		if((start.first-end.first)==0 && (start.second-end.second)==2)
			if(board[start.first][start.second-1]!=unoccupied)
				return false;
		else if((start.first-end.first)==0 && (start.second-end.second)==3)
			if(board[start.first][start.second-1]!=unoccupied)
				return false;

		if((start.first-end.first)==2 && (start.second-end.second)==-2)
			if(board[start.first-1][start.second+1]!=unoccupied)
				return false;
		else if((start.first-end.first)==3 && (start.second-end.second)==-3)
			if(board[start.first-1][start.second+1]!=unoccupied)
				return false;
		if((start.first-end.first)==2 && (start.second-end.second)==0)
			if(board[start.first-1][start.second]!=unoccupied)
				return false;
		else if((start.first-end.first)==3 && (start.second-end.second)==0)
			if(board[start.first-1][start.second]!=unoccupied)
				return false;	
		if((start.first-end.first)==2 && (start.second-end.second)==2)
			if(board[start.first-1][start.second-1]!=unoccupied)
				return false;
		else if((start.first-end.first)==3 && (start.second-end.second)==3)
			if(board[start.first-1][start.second-1]!=unoccupied)
				return false;

		board[end.first][end.second]=unoccupied;
		return true;
	}
	

	bool retreat_white(pair<int,int> start, pair<int, int> end)
	{
		if(board[start.first+1][start.second]==unoccupied && board[start.first][start.second+1]==unoccupied && board[start.first][start.second-1]==unoccupied && board[start.first+1][start.second+1]==unoccupied && board[start.first+1][start.second-1]==unoccupied)
			return false;
		if((start.first-end.first)!=2)
			return false;
		move(start,end);
	}
	bool retreat_black(pair<int,int> start, pair<int, int> end)
	{
		if(board[start.first-1][start.second]==unoccupied && board[start.first][start.second+1]==unoccupied && board[start.first][start.second-1]==unoccupied && board[start.first-1][start.second+1]==unoccupied && board[start.first-1][start.second-1]==unoccupied)
			return false;
		if((start.first-end.first)!=-2 && ((start.second-end.second)!=2 || (start.second-end.second)!=0 || (start.second-end.second)!=-2))
			return false;
		move(start,end);
	}
	bool attack_sol_white(pair<int,int> start, pair<int, int> end)
	{
		if(board[end.first][end.second]!=unoccupied)
			return false;
		if(((start.first-end.first)!=-1 && ((start.second-end.second)!=1 || (start.second-end.second)!=0 || (start.second-end.second)!=-1)) || ((start.first-end.first)!=0 && ((start.second-end.second)!=1 || (start.second-end.second)!=-1)))
			return false;
		move(start,end);
	}
	bool attack_sol_black(pair<int,int> start, pair<int, int> end)
	{
		if(board[end.first][end.second]!=unoccupied)
			return false;
		if(((start.first-end.first)!=1 && ((start.second-end.second)!=1 || (start.second-end.second)!=0 || (start.second-end.second)!=-1)) || ((start.first-end.first)!=0 && ((start.second-end.second)!=1 || (start.second-end.second)!=-1)))
			return false;
		move(start,end);
	}
	// bool move_cannon(pair<int,int> start, pair<int, int> end)
	// {
		
	// }
	// bool retreat_attack(pair<int,int> start, pair<int, int> end)
	// {

	// }

	vector<pair<pair<int,int>,pair<int,int>> getCannons_white()
	{
		vector<pair<pair<int,int>,pair<int,int>> toReturn;
		for(int i=0;i<8;i++)
		{
			for(int j=0;j<8;++j)
			{
				if(access(i,j)==whiteSoldier&&access(i, j+1)==whiteSoldier&&access(i, j+2)==whiteSoldier)
					toReturn.push_back(make_pair(make_pair(i,j),make_pair(i,j+2)));
				if(access(i,j)==whiteSoldier&&access(i+1, j-1)==whiteSoldier&&access(i+2, j-2)==whiteSoldier)
					toReturn.push_back(make_pair(make_pair(i,j),make_pair(i+2,j-2)));
				if(access(i,j)==whiteSoldier&&access(i+1, j+1)==whiteSoldier&&access(i+2, j+2)==whiteSoldier)
					toReturn.push_back(make_pair(make_pair(i,j),make_pair(i+2,j+2)));
				if(access(i,j)==whiteSoldier&&access(i+1, j)==whiteSoldier&&access(i+2, j)==whiteSoldier)
					toReturn.push_back(make_pair(make_pair(i,j),make_pair(i+2,j)));
			}
		}	
		return toReturn;	
	}
	vector<pair<pair<int,int>,pair<int,int>> getCannons_black()
	{
		vector<pair<pair<int,int>,pair<int,int>> toReturn;
		for(int i=0;i<8;i++)
		{
			for(int j=0;j<8;++j)
			{
				if(access(i,j)==blackSoldier&&access(i, j+1)==blackSoldier&&access(i, j+2)==blackSoldier)
					toReturn.push_back(make_pair(make_pair(i,j+2),make_pair(i,j)));
				if(access(i,j)==blackSoldier&&access(i+1, j-1)==blackSoldier&&access(i+2, j-2)==blackSoldier)
					toReturn.push_back(make_pair(make_pair(i+2,j-2),make_pair(i,j)));
				if(access(i,j)==blackSoldier&&access(i+1, j+1)==blackSoldier&&access(i+2, j+2)==blackSoldier)
					toReturn.push_back(make_pair(make_pair(i+2,j+2),make_pair(i,j)));
				if(access(i,j)==blackSoldier&&access(i+1, j)==blackSoldier&&access(i+2, j)==blackSoldier)
					toReturn.push_back(make_pair(make_pair(i+2,j),make_pair(i,j)));			}
		}	
		return toReturn;	
	}

	int evaluate_white()
	{
		int soldiers=0, townhalls=0, cannons=0;
		for(int i=0;i<8;i++){
			for(int j=0;j<8;++j){
				if(board[i][j]==whiteSoldier)
					soldiers++;
				else if(board[i][j]==whiteTownhall)
					townhalls++;
				if(access(i,j)==whiteSoldier&&access(i, j+1)==whiteSoldier&&access(i, j+2)==whiteSoldier)
					cannons++;
				if(access(i,j)==whiteSoldier&&access(i-1, j+1)==whiteSoldier&&access(i-2, j+2)==whiteSoldier)
					cannons++;
				if(access(i,j)==whiteSoldier&&access(i+1, j+1)==whiteSoldier&&access(i+2, j+2)==whiteSoldier)
					cannons++;
				if(access(i,j)==whiteSoldier&&access(i+1, j)==whiteSoldier&&access(i+2, j)==whiteSoldier)
					cannons++;
			}
		}
		int parameters[]={2,10,5};
		return soldiers*parameters[0]+townhalls*parameters[1]+cannons*parameters[2];

	}
	int evaluate_black()
	{
		int soldiers=0, townhalls=0, cannons=0;
		for(int i=0;i<8;i++){
			for(int j=0;j<8;++j){
				if(board[i][j]==blackSoldier)
					soldiers++;
				else if(board[i][j]==blackTownhall)
					townhalls++;
				if(access(i,j)==blackSoldier&&access(i, j+1)==blackSoldier&&access(i, j+2)==blackSoldier)
					cannons++;
				if(access(i,j)==blackSoldier&&access(i-1, j+1)==blackSoldier&&access(i-2, j+2)==blackSoldier)
					cannons++;
				if(access(i,j)==blackSoldier&&access(i+1, j+1)==blackSoldier&&access(i+2, j+2)==blackSoldier)
					cannons++;
				if(access(i,j)==blackSoldier&&access(i+1, j)==blackSoldier&&access(i+2, j)==blackSoldier)
					cannons++;


			}
		}
		int parameters[]={2,10,5};
		return soldiers*parameters[0]+townhalls*parameters[1]+cannons*parameters[2];

	}
	int evaluate(bool white)
	{
		if(white)
			return evaluate_white()-evaluate_black();
		else
			return evaluate_black()-evaluate_white();
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
