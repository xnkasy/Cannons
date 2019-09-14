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

	 vector< vector<state> >  getBoard() const
	{
		return board;
	}
	CannonBoard(const CannonBoard &copyCannon): board(8, seedVec)
	{
		board=copyCannon.getBoard();
	}
	state access(int i, int j)
	{
		if(i<8&&j<8&&i>=0&&j>=0)
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
	bool shoot(pair<int, int> start, pair<int, int> end) // add braces cause dangling else can happen
	{
		// if((start.first-end.first)==-2 && (start.second-end.second)==-2)
		// 	if(board[start.first+1][start.second+1]!=unoccupied)
		// 		return false;
		// else if((start.first-end.first)==-3 && (start.second-end.second)==-3)
		// 	if(board[start.first+1][start.second+1]!=unoccupied)
		// 		return false;
		// if((start.first-end.first)==-2 && (start.second-end.second)==0)
		// 	if(board[start.first+1][start.second]!=unoccupied)
		// 		return false;
		// else if((start.first-end.first)==-3 && (start.second-end.second)==0)
		// 	if(board[start.first+1][start.second]!=unoccupied)
		// 		return false;	
		// if((start.first-end.first)==-2 && (start.second-end.second)==2)
		// 	if(board[start.first+1][start.second-1]!=unoccupied)
		// 		return false;
		// else if((start.first-end.first)==-3 && (start.second-end.second)==3)
		// 	if(board[start.first+1][start.second-1]!=unoccupied)
		// 		return false;

		// if((start.first-end.first)==0 && (start.second-end.second)==-2)
		// 	if(board[start.first][start.second+1]!=unoccupied)
		// 		return false;
		// else if((start.first-end.first)==0 && (start.second-end.second)==-3)
		// 	if(board[start.first][start.second+1]!=unoccupied)
		// 		return false;	
		// if((start.first-end.first)==0 && (start.second-end.second)==2)
		// 	if(board[start.first][start.second-1]!=unoccupied)
		// 		return false;
		// else if((start.first-end.first)==0 && (start.second-end.second)==3)
		// 	if(board[start.first][start.second-1]!=unoccupied)
		// 		return false;

		// if((start.first-end.first)==2 && (start.second-end.second)==-2)
		// 	if(board[start.first-1][start.second+1]!=unoccupied)
		// 		return false;
		// else if((start.first-end.first)==3 && (start.second-end.second)==-3)
		// 	if(board[start.first-1][start.second+1]!=unoccupied)
		// 		return false;
		// if((start.first-end.first)==2 && (start.second-end.second)==0)
		// 	if(board[start.first-1][start.second]!=unoccupied)
		// 		return false;
		// else if((start.first-end.first)==3 && (start.second-end.second)==0)
		// 	if(board[start.first-1][start.second]!=unoccupied)
		// 		return false;	
		// if((start.first-end.first)==2 && (start.second-end.second)==2)
		// 	if(board[start.first-1][start.second-1]!=unoccupied)
		// 		return false;
		// else if((start.first-end.first)==3 && (start.second-end.second)==3)
		// 	if(board[start.first-1][start.second-1]!=unoccupied)
		// 		return false;

		board[end.first][end.second]=unoccupied;
		return true;
	}
	vector<pair< pair<int,int>,pair<int,int> > > getCannons_white()
	{
		vector< pair<pair<int,int> ,pair<int,int> > > toReturn;
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
	vector<pair<pair<int,int>,pair<int,int> > > getCannons_black()
	{
		vector<pair<pair<int,int>,pair<int,int> > > toReturn;
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
					toReturn.push_back(make_pair(make_pair(i+2,j),make_pair(i,j)));			
			}
		}	
		return toReturn;	
	}


	vector<CannonBoard> possibleStates(bool white) //rk:removed else from else ifs
	{
		CannonBoard temp1=*this;
		CannonBoard temp2=*this;
		vector<CannonBoard> possibleBoards;
		bool samestate=false;
		if(white){
			for(int i=0;i<8;i++){
				for(int j=0;j<8;++j){
					cout<<"at "<<i<<", "<<j<<endl;
					if(board[i][j]==whiteSoldier)
					{
						if(access(i+1, j)==unoccupied||access(i+1, j)==blackSoldier||access(i+1, j)==blackTownhall){
							temp1.move(make_pair(i, j), make_pair(i+1, j));
							possibleBoards.push_back(temp1);
							temp1=temp2;
						}
						if(access(i+1, j+1)==unoccupied||access(i+1, j+1)==blackSoldier||access(i+1, j+1)==blackTownhall){
							temp1.move(make_pair(i, j), make_pair(i+1, j+1));
							possibleBoards.push_back(temp1);
							temp1=temp2;
						}
						if(access(i+1, j-1)==unoccupied||access(i+1, j-1)==blackSoldier||access(i+1, j-1)==blackTownhall){
							temp1.move(make_pair(i, j), make_pair(i+1, j-1));
							possibleBoards.push_back(temp1);
							temp1=temp2;
						}
						if(access(i, j+1)==blackSoldier||access(i, j+1)==blackTownhall){
							temp1.move(make_pair(i, j), make_pair(i, j+1));
							possibleBoards.push_back(temp1);
							temp1=temp2;
						}
						if(access(i, j-1)==blackSoldier||access(i, j-1)==blackTownhall){
							temp1.move(make_pair(i, j), make_pair(i, j-1));
							possibleBoards.push_back(temp1);
							temp1=temp2;
						}
						//retreat
						if(access(i+1, j)==blackSoldier||access(i+1, j+1)==blackSoldier||access(i+1, j-1)==blackSoldier||access(i, j+1)==blackSoldier||access(i, j-1)==blackSoldier){
							temp1.move(make_pair(i, j), make_pair(i-2, j));
							possibleBoards.push_back(temp1);
							temp1=temp2;
							temp1.move(make_pair(i, j), make_pair(i-2, j-2));
							possibleBoards.push_back(temp1);
							temp1=temp2;
							temp1.move(make_pair(i, j), make_pair(i-2, j+2));
							possibleBoards.push_back(temp1);
							temp1=temp2;
						}
						//cannons
						if(access(i, j+1)==whiteSoldier&&access(i, j+2)==whiteSoldier)
						{
							if(access(i,j+3)==unoccupied)
							{
								temp1.move(make_pair(i, j), make_pair(i, j+3));
								possibleBoards.push_back(temp1);
								temp1=temp2;
								if(access(i,j+4)==blackSoldier||access(i,j+4)==blackTownhall)
								{
									temp1.shoot(make_pair(i, j+2),make_pair(i,j+4));
									possibleBoards.push_back(temp1);
									temp1=temp2;
								}
								else if(access(i,j+4)==unoccupied)
								{
									samestate=true;
									if(access(i,j+5)==blackSoldier||access(i,j+5)==blackTownhall)
									{
										temp1.shoot(make_pair(i, j+2),make_pair(i,j+5));
										possibleBoards.push_back(temp1);
										temp1=temp2;
									}
								}								
							}
							if(access(i,j-1)==unoccupied)
							{
								temp1.move(make_pair(i, j+2), make_pair(i, j-1));
								possibleBoards.push_back(temp1);
								temp1=temp2;
								if(access(i,j-2)==blackSoldier||access(i,j-2)==blackTownhall)
								{
									temp1.shoot(make_pair(i, j),make_pair(i,j-2));
									possibleBoards.push_back(temp1);
									temp1=temp2;
								}
								else if(access(i,j-2)==unoccupied)
								{
									samestate=true;
									if(access(i,j-3)==blackSoldier||access(i,j-3)==blackTownhall)
									{
										temp1.shoot(make_pair(i, j),make_pair(i,j-3));
										possibleBoards.push_back(temp1);
										temp1=temp2;
									}
								}								
							}
						}

						if(access(i+1, j-1)==whiteSoldier&&access(i+2, j-2)==whiteSoldier)
						{
							if(access(i+3,j-3)==unoccupied)
							{
								temp1.move(make_pair(i, j), make_pair(i+3, j-3));
								possibleBoards.push_back(temp1);
								temp1=temp2;
								if(access(i+4,j-4)==blackSoldier||access(i+4,j-4)==blackTownhall)
								{
									temp1.shoot(make_pair(i+2, j-2),make_pair(i+4,j-4));
									possibleBoards.push_back(temp1);
									temp1=temp2;
								}
								else if(access(i+4,j-4)==unoccupied)
								{
									samestate=true;
									if(access(i+5,j-5)==blackSoldier||access(i+5,j-5)==blackTownhall)
									{
										temp1.shoot(make_pair(i+2, j-2),make_pair(i+5,j-5));
										possibleBoards.push_back(temp1);
										temp1=temp2;
									}
								}								
							}
							if(access(i-1,j+1)==unoccupied)
							{
								temp1.move(make_pair(i+2, j-2), make_pair(i-1, j+1));
								possibleBoards.push_back(temp1);
								temp1=temp2;
								if(access(i-2,j+2)==blackSoldier||access(i-2,j+2)==blackTownhall)
								{
									temp1.shoot(make_pair(i, j),make_pair(i-2,j+2));
									possibleBoards.push_back(temp1);
									temp1=temp2;
								}
								else if(access(i-2,j+2)==unoccupied)
								{
									samestate=true;
									if(access(i-3,j+3)==blackSoldier||access(i-3,j+3)==blackTownhall)
									{
										temp1.shoot(make_pair(i, j),make_pair(i-3,j+3));
										possibleBoards.push_back(temp1);
										temp1=temp2;
									}
								}								
							}
						}

						if(access(i+1, j+1)==whiteSoldier&&access(i+2, j+2)==whiteSoldier)
						{
							if(access(i+3,j+3)==unoccupied)
							{
								temp1.move(make_pair(i, j), make_pair(i+3, j+3));
								possibleBoards.push_back(temp1);
								temp1=temp2;
								if(access(i+4,j+4)==blackSoldier||access(i+4,j+4)==blackTownhall)
								{
									temp1.shoot(make_pair(i+2, j+2),make_pair(i+2,j+4));
									possibleBoards.push_back(temp1);
									temp1=temp2;
								}
								else if(access(i+4,j+4)==unoccupied)
								{
									samestate=true;
									if(access(i+5,j+5)==blackSoldier||access(i+5,j+5)==blackTownhall)
									{
										temp1.shoot(make_pair(i+2, j+2),make_pair(i+5,j+5));
										possibleBoards.push_back(temp1);
										temp1=temp2;
									}
								}								
							}
							if(access(i-1,j-1)==unoccupied)
							{
								temp1.move(make_pair(i+2, j+2), make_pair(i-1, j-1));
								possibleBoards.push_back(temp1);
								temp1=temp2;
								if(access(i-2,j-2)==blackSoldier||access(i-2,j-2)==blackTownhall)
								{
									temp1.shoot(make_pair(i, j),make_pair(i-2,j-2));
									possibleBoards.push_back(temp1);
									temp1=temp2;
								}
								else if(access(i-2,j-2)==unoccupied)
								{
									samestate=true;
									if(access(i-3,j-3)==blackSoldier||access(i-3,j-3)==blackTownhall)
									{
										temp1.shoot(make_pair(i, j),make_pair(i-3,j-3));
										possibleBoards.push_back(temp1);
										temp1=temp2;
									}
								}								
							}
						}

						if(access(i+1, j)==whiteSoldier&&access(i+2, j)==whiteSoldier)
						{
							if(access(i+3,j)==unoccupied)
							{
								temp1.move(make_pair(i, j), make_pair(i+3, j));
								possibleBoards.push_back(temp1);
								temp1=temp2;
								if(access(i+4,j)==blackSoldier||access(i+4,j)==blackTownhall)
								{
									temp1.shoot(make_pair(i+2, j),make_pair(i+4,j));
									possibleBoards.push_back(temp1);
									temp1=temp2;
								}
								else if(access(i+4,j)==unoccupied)
								{
									samestate=true;
									if(access(i+5,j)==blackSoldier||access(i+5,j)==blackTownhall)
									{
										temp1.shoot(make_pair(i+2, j),make_pair(i+5,j));
										possibleBoards.push_back(temp1);
										temp1=temp2;
									}
								}								
							}
							if(access(i-1,j)==unoccupied)
							{
								temp1.move(make_pair(i+2, j), make_pair(i-1, j));
								possibleBoards.push_back(temp1);
								temp1=temp2;
								if(access(i-2,j)==blackSoldier||access(i-2,j)==blackTownhall)
								{
									temp1.shoot(make_pair(i, j),make_pair(i-2,j));
									possibleBoards.push_back(temp1);
									temp1=temp2;
								}
								else if(access(i-2,j)==unoccupied)
								{
									samestate=true;
									if(access(i-3,j)==blackSoldier||access(i-3,j)==blackTownhall)
									{
										temp1.shoot(make_pair(i, j),make_pair(i-3,j));
										possibleBoards.push_back(temp1);
										temp1=temp2;
									}
								}								
							}
						}
						//end cannon moves/shoots
					}
				}
			}

		}
		else{
			for(int i=0;i<8;i++){
				for(int j=0;j<8;++j){
					if(board[i][j]==blackSoldier)
					{
						if(access(i+1, j)==unoccupied||access(i+1, j)==whiteSoldier||access(i+1, j)==whiteTownhall){
							temp1.move(make_pair(i, j), make_pair(i+1, j));
							possibleBoards.push_back(temp1);
							temp1=temp2;
						}
						if(access(i+1, j+1)==unoccupied||access(i+1, j+1)==whiteSoldier||access(i+1, j+1)==whiteTownhall){
							temp1.move(make_pair(i, j), make_pair(i+1, j+1));
							possibleBoards.push_back(temp1);
							temp1=temp2;
						}
						if(access(i+1, j-1)==unoccupied||access(i+1, j-1)==whiteSoldier||access(i+1, j-1)==whiteTownhall){
							temp1.move(make_pair(i, j), make_pair(i+1, j-1));
							possibleBoards.push_back(temp1);
							temp1=temp2;
						}
						if(access(i, j+1)==whiteTownhall||access(i, j+1)==whiteSoldier){
							temp1.move(make_pair(i, j), make_pair(i, j+1));
							possibleBoards.push_back(temp1);
							temp1=temp2;
						}
						if(access(i, j-1)==whiteTownhall||access(i, j-1)==whiteSoldier){
							temp1.move(make_pair(i, j), make_pair(i, j-1));
							possibleBoards.push_back(temp1);
							temp1=temp2;
						}
						//retreat
						if(access(i-1, j)==whiteSoldier||access(i-1, j+1)==whiteSoldier||access(i-1, j-1)==whiteSoldier||access(i, j+1)==whiteSoldier||access(i, j-1)==whiteSoldier){
							temp1.move(make_pair(i, j), make_pair(i+2, j));
							possibleBoards.push_back(temp1);
							temp1=temp2;
							temp1.move(make_pair(i, j), make_pair(i+2, j-2));
							possibleBoards.push_back(temp1);
							temp1=temp2;
							temp1.move(make_pair(i, j), make_pair(i+2, j+2));
							possibleBoards.push_back(temp1);
							temp1=temp2;
						}
						//cannon
						if(access(i, j+1)==blackSoldier&&access(i, j+2)==blackSoldier)
						{
							if(access(i,j+3)==unoccupied)
							{
								temp1.move(make_pair(i, j), make_pair(i, j+3));
								possibleBoards.push_back(temp1);
								temp1=temp2;
								if(access(i,j+4)==whiteSoldier||access(i,j+4)==whiteTownhall)
								{
									temp1.shoot(make_pair(i, j+2),make_pair(i,j+4));
									possibleBoards.push_back(temp1);
									temp1=temp2;
								}
								else if(access(i,j+4)==unoccupied)
								{
									samestate=true;
									if(access(i,j+5)==whiteSoldier||access(i,j+5)==whiteTownhall)
									{
										temp1.shoot(make_pair(i, j+2),make_pair(i,j+5));
										possibleBoards.push_back(temp1);
										temp1=temp2;
									}
								}								
							}
							if(access(i,j-1)==unoccupied)
							{
								temp1.move(make_pair(i, j+2), make_pair(i, j-1));
								possibleBoards.push_back(temp1);
								temp1=temp2;
								if(access(i,j-2)==whiteSoldier||access(i,j-2)==whiteTownhall)
								{
									temp1.shoot(make_pair(i, j),make_pair(i,j-2));
									possibleBoards.push_back(temp1);
									temp1=temp2;
								}
								else if(access(i,j-2)==unoccupied)
								{
									samestate=true;
									if(access(i,j-3)==whiteSoldier||access(i,j-3)==whiteTownhall)
									{
										temp1.shoot(make_pair(i, j),make_pair(i,j-3));
										possibleBoards.push_back(temp1);
										temp1=temp2;
									}
								}								
							}
						}

						if(access(i+1, j-1)==blackSoldier&&access(i+2, j-2)==blackSoldier)
						{
							if(access(i+3,j-3)==unoccupied)
							{
								temp1.move(make_pair(i, j), make_pair(i+3, j-3));
								possibleBoards.push_back(temp1);
								temp1=temp2;
								if(access(i+4,j-4)==whiteSoldier||access(i+4,j-4)==whiteTownhall)
								{
									temp1.shoot(make_pair(i+2, j-2),make_pair(i+4,j-4));
									possibleBoards.push_back(temp1);
									temp1=temp2;
								}
								else if(access(i+4,j-4)==unoccupied)
								{
									samestate=true;
									if(access(i+5,j-5)==whiteSoldier||access(i+5,j-5)==whiteTownhall)
									{
										temp1.shoot(make_pair(i+2, j-2),make_pair(i+5,j-5));
										possibleBoards.push_back(temp1);
										temp1=temp2;
									}
								}								
							}
							if(access(i-1,j+1)==unoccupied)
							{
								temp1.move(make_pair(i+2, j-2), make_pair(i-1, j+1));
								possibleBoards.push_back(temp1);
								temp1=temp2;
								if(access(i-2,j+2)==whiteSoldier||access(i-2,j+2)==whiteTownhall)
								{
									temp1.shoot(make_pair(i, j),make_pair(i-2,j+2));
									possibleBoards.push_back(temp1);
									temp1=temp2;
								}
								else if(access(i-2,j+2)==unoccupied)
								{
									samestate=true;
									if(access(i-3,j+3)==whiteSoldier||access(i-3,j+3)==whiteTownhall)
									{
										temp1.shoot(make_pair(i, j),make_pair(i-3,j+3));
										possibleBoards.push_back(temp1);
										temp1=temp2;
									}
								}								
							}
						}

						if(access(i+1, j+1)==blackSoldier&&access(i+2, j+2)==blackSoldier)
						{
							if(access(i+3,j+3)==unoccupied)
							{
								temp1.move(make_pair(i, j), make_pair(i+3, j+3));
								possibleBoards.push_back(temp1);
								temp1=temp2;
								if(access(i+4,j+4)==whiteSoldier||access(i+4,j+4)==whiteTownhall)
								{
									temp1.shoot(make_pair(i+2, j+2),make_pair(i+2,j+4));
									possibleBoards.push_back(temp1);
									temp1=temp2;
								}
								else if(access(i+4,j+4)==unoccupied)
								{
									samestate=true;
									if(access(i+5,j+5)==whiteSoldier||access(i+5,j+5)==whiteTownhall)
									{
										temp1.shoot(make_pair(i+2, j+2),make_pair(i+5,j+5));
										possibleBoards.push_back(temp1);
										temp1=temp2;
									}
								}								
							}
							if(access(i-1,j-1)==unoccupied)
							{
								temp1.move(make_pair(i+2, j+2), make_pair(i-1, j-1));
								possibleBoards.push_back(temp1);
								temp1=temp2;
								if(access(i-2,j-2)==whiteSoldier||access(i-2,j-2)==whiteTownhall)
								{
									temp1.shoot(make_pair(i, j),make_pair(i-2,j-2));
									possibleBoards.push_back(temp1);
									temp1=temp2;
								}
								else if(access(i-2,j-2)==unoccupied)
								{
									samestate=true;
									if(access(i-3,j-3)==whiteSoldier||access(i-3,j-3)==whiteTownhall)
									{
										temp1.shoot(make_pair(i, j),make_pair(i-3,j-3));
										possibleBoards.push_back(temp1);
										temp1=temp2;
									}
								}								
							}
						}

						if(access(i+1, j)==blackSoldier&&access(i+2, j)==blackSoldier)
						{
							if(access(i+3,j)==unoccupied)
							{
								temp1.move(make_pair(i, j), make_pair(i+3, j));
								possibleBoards.push_back(temp1);
								temp1=temp2;
								if(access(i+4,j)==whiteSoldier||access(i+4,j)==whiteTownhall)
								{
									temp1.shoot(make_pair(i+2, j),make_pair(i+4,j));
									possibleBoards.push_back(temp1);
									temp1=temp2;
								}
								else if(access(i+4,j)==unoccupied)
								{
									samestate=true;
									if(access(i+5,j)==whiteSoldier||access(i+5,j)==whiteTownhall)
									{
										temp1.shoot(make_pair(i+2, j),make_pair(i+5,j));
										possibleBoards.push_back(temp1);
										temp1=temp2;
									}
								}								
							}
							if(access(i-1,j)==unoccupied)
							{
								temp1.move(make_pair(i+2, j), make_pair(i-1, j));
								possibleBoards.push_back(temp1);
								temp1=temp2;
								if(access(i-2,j)==whiteSoldier||access(i-2,j)==whiteTownhall)
								{
									temp1.shoot(make_pair(i, j),make_pair(i-2,j));
									possibleBoards.push_back(temp1);
									temp1=temp2;
								}
								else if(access(i-2,j)==unoccupied)
								{
									samestate=true;
									if(access(i-3,j)==whiteSoldier||access(i-3,j)==whiteTownhall)
									{
										temp1.shoot(make_pair(i, j),make_pair(i-3,j));
										possibleBoards.push_back(temp1);
										temp1=temp2;
									}
								}								
							}
						}
						//end cannon moves/shoots
					}
				}
			}

		}
		if(samestate)
			possibleBoards.push_back(temp1);
		return possibleBoards;		
	}

	bool retreat_white(pair<int,int> start, pair<int, int> end)
	{
		if(board[start.first+1][start.second]==unoccupied && board[start.first][start.second+1]==unoccupied && board[start.first][start.second-1]==unoccupied && board[start.first+1][start.second+1]==unoccupied && board[start.first+1][start.second-1]==unoccupied)
			return false;
		if((start.first-end.first)!=2)
			return false;
		move(start,end);
		return true;
	}
	bool retreat_black(pair<int,int> start, pair<int, int> end)
	{
		if(board[start.first-1][start.second]==unoccupied && board[start.first][start.second+1]==unoccupied && board[start.first][start.second-1]==unoccupied && board[start.first-1][start.second+1]==unoccupied && board[start.first-1][start.second-1]==unoccupied)
			return false;
		if((start.first-end.first)!=-2 && ((start.second-end.second)!=2 || (start.second-end.second)!=0 || (start.second-end.second)!=-2))
			return false;
		move(start,end);
		return true;
	}
	bool attack_sol_white(pair<int,int> start, pair<int, int> end)
	{
		if(board[end.first][end.second]!=unoccupied)
			return false;
		if(((start.first-end.first)!=-1 && ((start.second-end.second)!=1 || (start.second-end.second)!=0 || (start.second-end.second)!=-1)) || ((start.first-end.first)!=0 && ((start.second-end.second)!=1 || (start.second-end.second)!=-1)))
			return false;
		move(start,end);
		return true;
	}
	bool attack_sol_black(pair<int,int> start, pair<int, int> end)
	{
		if(board[end.first][end.second]!=unoccupied)
			return false;
		if(((start.first-end.first)!=1 && ((start.second-end.second)!=1 || (start.second-end.second)!=0 || (start.second-end.second)!=-1)) || ((start.first-end.first)!=0 && ((start.second-end.second)!=1 || (start.second-end.second)!=-1)))
			return false;
		move(start,end);
		return true;
	}
	// bool move_cannon(pair<int,int> start, pair<int, int> end)
	// {
		
	// }
	// bool retreat_attack(pair<int,int> start, pair<int, int> end)
	// {

	// }

	
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
CannonBoard max_value_action(CannonBoard present, int depth, bool white);
CannonBoard min_value_action(CannonBoard present, int depth, bool white);
string transform_move(CannonBoard initial, CannonBoard final)
{
	string move="";


	return move;
}
string select_move(CannonBoard present, string move, int depth, bool white)
{

	CannonBoard best_child= max_value_action(present, depth, white);
	return transform_move(present, best_child);


}
CannonBoard max_value_action(CannonBoard present, int depth, bool white)
{
	vector<CannonBoard> successors = present.possibleStates(white);
	int max=INT_MIN;
	CannonBoard best_child;
	for(auto it=successors.begin();it!=successors.end();it++){
		int minVal=min_value_action(*it, depth-1, !white).evaluate(white);
		if(minVal>max){
			max=minVal;
			best_child=*it;
		}


	}
	return best_child;
}
CannonBoard min_value_action(CannonBoard present, int depth, bool white)
{
	vector<CannonBoard> successors = present.possibleStates(white);
	int min=INT_MAX;
	CannonBoard best_child;
	for(auto it=successors.begin();it!=successors.end();it++){
		int maxVal=min_value_action(*it, depth-1, !white).evaluate(white);
		if(maxVal<min){
			min=maxVal;
			best_child=*it;
		}


	}
	return best_child;
}

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
		vector<CannonBoard> possibles=ourBoard.possibleStates(true);
		cout<<"Evealuations done"<<endl;
		for(auto it=possibles.begin();it!=possibles.end();it++){
			//it->print();
			cout<<it->evaluate(true)<<endl;
			}

	}
	
	return 0;
}
