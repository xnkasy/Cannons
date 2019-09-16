#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;
enum state 
{   blackTownhall=-1, 
    whiteTownhall =1, 
    unoccupied=0,
    null=INT_MIN,
    blackSoldier= -2,
    whiteSoldier=2
};
ofstream fout;
//fout.open("a.txt");
// enum cannontype
// {
// 	vertical=0,
// 	hor=1,
// 	rdiag=2,
// 	ldiag=3
// };
//first is soldiers, then townhalls, then cannons
int parameters[]={2,1000,5};
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
	bool operator == ( CannonBoard &other)
	{
		for(int i=0;i<8;i++)
		{
			for(int j=0;j<8;++j)
			{
				if(other.access(i,j)!=access(i, j))
					return false;
			}
		}	
		return true;	

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
	string prints()
	{
		string s;
		for(int i=0;i<8;i++){
			for(int j=0;j<8;++j){
				s=s+to_string(board[i][j])+" ";
			}
			s=s+"\n";
		}   
		return s;
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
					//fout<<"at "<<i<<", "<<j<<endl;
					//fout<<board[i][j]<<" ";
					if(board[i][j]==whiteSoldier)
					{
						//fout<<"white"<<endl;
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
							//cout<<"retreat possible "<<endl;
							if(i-2>=0){
							temp1.move(make_pair(i, j), make_pair(i-2, j));
							possibleBoards.push_back(temp1);
							temp1=temp2;

							}
							if(i-2>=0&&j-2>=0){
							temp1.move(make_pair(i, j), make_pair(i-2, j-2));
							possibleBoards.push_back(temp1);
							temp1=temp2;

							}
							if(i-2>=0&&j+2<8){
							temp1.move(make_pair(i, j), make_pair(i-2, j+2));
							possibleBoards.push_back(temp1);
							temp1=temp2;

							}
							
						}
						//cout<<"at "<<i<<", "<<j<<"before cannons"<<endl;
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
						//cout<<"at "<<i<<", "<<j<<"before retreat"<<endl;
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
						if(access(i-1, j)==unoccupied||access(i-1, j)==whiteSoldier||access(i-1, j)==whiteTownhall){
							temp1.move(make_pair(i, j), make_pair(i-1, j));
							possibleBoards.push_back(temp1);
							temp1=temp2;
						}
						if(access(i-1, j+1)==unoccupied||access(i-1, j+1)==whiteSoldier||access(i-1, j+1)==whiteTownhall){
							temp1.move(make_pair(i, j), make_pair(i-1, j+1));
							possibleBoards.push_back(temp1);
							temp1=temp2;
						}
						if(access(i-1, j-1)==unoccupied||access(i-1, j-1)==whiteSoldier||access(i-1, j-1)==whiteTownhall){
							temp1.move(make_pair(i, j), make_pair(i-1, j-1));
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
							if(i+2<8){
								temp1.move(make_pair(i, j), make_pair(i+2, j));							
								possibleBoards.push_back(temp1);
								temp1=temp2;
							}
							if(i+2<8&&j-2>=0){
								temp1.move(make_pair(i, j), make_pair(i+2, j-2));
								possibleBoards.push_back(temp1);
								temp1=temp2;
							}if(i+2<8&&j+2<8){
								temp1.move(make_pair(i, j), make_pair(i+2, j+2));
								possibleBoards.push_back(temp1);
								temp1=temp2;
							}
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
		// for(auto it=possibleBoards.begin();it!=possibleBoards.end();it++)
		// {
		// 	for(int i=0;i<8;i++){
		// 	for(int j=0;j<8;++j){
		// 		fout<<board[i][j]<<"\t";
		// 	}
		// 	fout<<endl;
		
		// }
		possibleBoards.clear();	
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

	state access_pair(pair<int, int> x)
	{
		return access(x.first, x.second);
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
		int hits_unoccupied=0, hits_black=0, hits_townhall=0;
		vector<pair< pair<int,int>,pair<int,int> > > cannon_pos=getCannons_white();
		for(auto it: cannon_pos){
			pair<int, int> start=it.first;
			pair<int, int> end=it.second;
			if((start.first==end.first+2)&&(start.second==end.second)){
				hits_unoccupied=(access(start.first+2)==unoccupied)+(access(start.first+3)==unoccupied)+(access(end.first-2)==unoccupied)+(access(end.first-3)==unoccupied);
				
			}

		}
		return (soldiers*parameters[0])-((2-townhalls)*parameters[1])+(cannons*parameters[2]);

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

		
		return (soldiers*parameters[0])-((2-townhalls)*parameters[1])+(cannons*parameters[2]);

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



string transform_move(CannonBoard initial, CannonBoard final, bool white)
{
	string move="";
	CannonBoard temp1=initial;
	CannonBoard temp2=initial;
	bool samestate=false;
	if(white){
		for(int i=0;i<8;i++){
			for(int j=0;j<8;++j){
				//cout<<"at "<<i<<", "<<j<<endl;
				if(initial.getBoard()[i][j]!=whiteSoldier)
					continue;
				if(initial.getBoard()[i][j]==whiteSoldier)
				{
					//fout<<"printed at "<<i<<", "<<j<<endl;
					//fout<<initial.prints()<<" ";
					if(initial.access(i+1, j)==unoccupied||initial.access(i+1, j)==blackSoldier||initial.access(i+1, j)==blackTownhall){
						temp1.move(make_pair(i, j), make_pair(i+1, j));
						if(temp1==final)
							return (string)"S "+to_string(i)+(string)" "+to_string(j)+ (string)" M "+to_string(i+1)+ (string)" "+to_string(j);
						temp1=temp2;
					}
					if(initial.access(i+1, j+1)==unoccupied||initial.access(i+1, j+1)==blackSoldier||initial.access(i+1, j+1)==blackTownhall){
						temp1.move(make_pair(i, j), make_pair(i+1, j+1));
						if(temp1==final)
							return (string)"S "+to_string(i)+(string)" "+to_string(j)+ (string)" M "+to_string(i+1)+ (string)" "+to_string(j+1);
						temp1=temp2;
					}
					if(initial.access(i+1, j-1)==unoccupied||initial.access(i+1, j-1)==blackSoldier||initial.access(i+1, j-1)==blackTownhall){
						temp1.move(make_pair(i, j), make_pair(i+1, j-1));
						if(temp1==final)
							return (string)"S "+to_string(i)+(string)" "+to_string(j)+ (string)" M "+to_string(i+1)+ (string)" "+to_string(j-1);
						temp1=temp2;
					}
					if(initial.access(i, j+1)==blackSoldier||initial.access(i, j+1)==blackTownhall){
						temp1.move(make_pair(i, j), make_pair(i, j+1));
						if(temp1==final)
							return (string)"S "+to_string(i)+(string)" "+to_string(j)+ (string)" M "+to_string(i)+ (string)" "+to_string(j+1);
						temp1=temp2;
					}
					if(initial.access(i, j-1)==blackSoldier||initial.access(i, j-1)==blackTownhall){
						temp1.move(make_pair(i, j), make_pair(i, j-1));
						if(temp1==final)
							return (string)"S "+to_string(i)+(string)" "+to_string(j)+ (string)" M "+to_string(i)+ (string)" "+to_string(j-1);
						temp1=temp2;
					}
					//retreat
					if(initial.access(i+1, j)==blackSoldier||initial.access(i+1, j+1)==blackSoldier||initial.access(i+1, j-1)==blackSoldier||initial.access(i, j+1)==blackSoldier||initial.access(i, j-1)==blackSoldier){
						if(i-2>=0){
							temp1.move(make_pair(i, j), make_pair(i-2, j));
							if(temp1==final)
								return (string)"S "+to_string(i)+(string)" "+to_string(j)+ (string)" M "+to_string(i-2)+ (string)" "+to_string(j);
							temp1=temp2;
						}
						if(i-2>=0&&j-2>=0){
							temp1.move(make_pair(i, j), make_pair(i-2, j-2));
							if(temp1==final)
								return (string)"S "+to_string(i)+(string)" "+to_string(j)+ (string)" M "+to_string(i-2)+ (string)" "+to_string(j-2);
							temp1=temp2;
						}
						if(i-2>=0&&j+2<8){
							temp1.move(make_pair(i, j), make_pair(i-2, j+2));
							if(temp1==final)
								return (string)"S "+to_string(i)+(string)" "+to_string(j)+ (string)" M "+to_string(i-2)+ (string)" "+to_string(j+2);
							temp1=temp2;
						}
					}
					//cannons
					if(initial.access(i, j+1)==whiteSoldier&&initial.access(i, j+2)==whiteSoldier)
					{
						if(initial.access(i,j+3)==unoccupied)
						{
							temp1.move(make_pair(i, j), make_pair(i, j+3));
							if(temp1==final)
								return (string)"S "+to_string(i)+(string)" "+to_string(j)+ (string)" M "+to_string(i)+ (string)" "+to_string(j+3);
							temp1=temp2;
							if(initial.access(i,j+4)==blackSoldier||initial.access(i,j+4)==blackTownhall)
							{
								temp1.shoot(make_pair(i, j+2),make_pair(i,j+4));
								if(temp1==final)
									return (string)"S "+to_string(i)+(string)" "+to_string(j+2)+ (string)" B "+to_string(i)+ (string)" "+to_string(j+4);
								temp1=temp2;
							}
							else if(initial.access(i,j+4)==unoccupied)
							{
								if(temp1==final)
									return (string)"S "+to_string(i)+(string)" "+to_string(j+2)+ (string)" B "+to_string(i)+ (string)" "+to_string(j+4);
								if(initial.access(i,j+5)==blackSoldier||initial.access(i,j+5)==blackTownhall)
								{
									temp1.shoot(make_pair(i, j+2),make_pair(i,j+5));
									if(temp1==final)
										return (string)"S "+to_string(i)+(string)" "+to_string(j+2)+ (string)" B "+to_string(i)+ (string)" "+to_string(j+5);
									temp1=temp2;
								}
							}								
						}
						if(initial.access(i,j-1)==unoccupied)
						{
							temp1.move(make_pair(i, j+2), make_pair(i, j-1));
							if(temp1==final)
								return (string)"S "+to_string(i)+(string)" "+to_string(j+2)+ (string)" M "+to_string(i)+ (string)" "+to_string(j-1);
							temp1=temp2;
							if(initial.access(i,j-2)==blackSoldier||initial.access(i,j-2)==blackTownhall)
							{
								temp1.shoot(make_pair(i, j),make_pair(i,j-2));
								if(temp1==final)
									return (string)"S "+to_string(i)+(string)" "+to_string(j)+ (string)" B "+to_string(i)+ (string)" "+to_string(j-2);
								temp1=temp2;
							}
							else if(initial.access(i,j-2)==unoccupied)
							{
								if(temp1==final)
									return (string)"S "+to_string(i)+(string)" "+to_string(j)+ (string)" B "+to_string(i)+ (string)" "+to_string(j-2);
								if(initial.access(i,j-3)==blackSoldier||initial.access(i,j-3)==blackTownhall)
								{
									temp1.shoot(make_pair(i, j),make_pair(i,j-3));
									if(temp1==final)
										return (string)"S "+to_string(i)+(string)" "+to_string(j)+ (string)" B "+to_string(i)+ (string)" "+to_string(j-3);
									temp1=temp2;
								}
							}								
						}
					}

					if(initial.access(i+1, j-1)==whiteSoldier&&initial.access(i+2, j-2)==whiteSoldier)
					{
						if(initial.access(i+3,j-3)==unoccupied)
						{
							temp1.move(make_pair(i, j), make_pair(i+3, j-3));
							if(temp1==final)
								return (string)"S "+to_string(i)+(string)" "+to_string(j)+ (string)" M "+to_string(i+3)+ (string)" "+to_string(j-3);
							temp1=temp2;
							if(initial.access(i+4,j-4)==blackSoldier||initial.access(i+4,j-4)==blackTownhall)
							{
								temp1.shoot(make_pair(i+2, j-2),make_pair(i+4,j-4));
								if(temp1==final)
									return (string)"S "+to_string(i+2)+(string)" "+to_string(j-2)+ (string)" B "+to_string(i+4)+ (string)" "+to_string(j-4);
								temp1=temp2;
							}
							else if(initial.access(i+4,j-4)==unoccupied)
							{
								if(temp1==final)
									return (string)"S "+to_string(i+2)+(string)" "+to_string(j-2)+ (string)" B "+to_string(i+4)+ (string)" "+to_string(j-4);
								if(initial.access(i+5,j-5)==blackSoldier||initial.access(i+5,j-5)==blackTownhall)
								{
									temp1.shoot(make_pair(i+2, j-2),make_pair(i+5,j-5));
									if(temp1==final)
										return (string)"S "+to_string(i+2)+(string)" "+to_string(j-2)+ (string)" B "+to_string(i+5)+ (string)" "+to_string(j-5);
									temp1=temp2;
								}
							}								
						}
						if(initial.access(i-1,j+1)==unoccupied)
						{
							temp1.move(make_pair(i+2, j-2), make_pair(i-1, j+1));
							if(temp1==final)
								return (string)"S "+to_string(i+2)+(string)" "+to_string(j-2)+ (string)" M "+to_string(i-1)+ (string)" "+to_string(j+1);
							temp1=temp2;
							if(initial.access(i-2,j+2)==blackSoldier||initial.access(i-2,j+2)==blackTownhall)
							{
								temp1.shoot(make_pair(i, j),make_pair(i-2,j+2));
								if(temp1==final)
									return (string)"S "+to_string(i)+(string)" "+to_string(j)+ (string)" B "+to_string(i-2)+ (string)" "+to_string(j+2);
								temp1=temp2;
							}
							else if(initial.access(i-2,j+2)==unoccupied)
							{
								if(temp1==final)
									return (string)"S "+to_string(i)+(string)" "+to_string(j)+ (string)" B "+to_string(i-2)+ (string)" "+to_string(j+2);
								if(initial.access(i-3,j+3)==blackSoldier||initial.access(i-3,j+3)==blackTownhall)
								{
									temp1.shoot(make_pair(i, j),make_pair(i-3,j+3));
									if(temp1==final)
									return (string)"S "+to_string(i)+(string)" "+to_string(j)+ (string)" B "+to_string(i-3)+ (string)" "+to_string(j+3);
									temp1=temp2;
								}
							}								
						}
					}

					if(initial.access(i+1, j+1)==whiteSoldier&&initial.access(i+2, j+2)==whiteSoldier)
					{
						if(initial.access(i+3,j+3)==unoccupied)
						{
							temp1.move(make_pair(i, j), make_pair(i+3, j+3));
							if(temp1==final)
								return (string)"S "+to_string(i)+(string)" "+to_string(j)+ (string)" M "+to_string(i+3)+ (string)" "+to_string(j+3);
							temp1=temp2;
							if(initial.access(i+4,j+4)==blackSoldier||initial.access(i+4,j+4)==blackTownhall)
							{
								temp1.shoot(make_pair(i+2, j+2),make_pair(i+2,j+4));
								if(temp1==final)
									return (string)"S "+to_string(i+2)+(string)" "+to_string(j+2)+ (string)" B "+to_string(i+2)+ (string)" "+to_string(j+4);
								temp1=temp2;
							}
							else if(initial.access(i+4,j+4)==unoccupied)
							{
								if(temp1==final)
									return (string)"S "+to_string(i+2)+(string)" "+to_string(j+2)+ (string)" B "+to_string(i+4)+ (string)" "+to_string(j+4);
								if(initial.access(i+5,j+5)==blackSoldier||initial.access(i+5,j+5)==blackTownhall)
								{
									temp1.shoot(make_pair(i+2, j+2),make_pair(i+5,j+5));
									if(temp1==final)
										return (string)"S "+to_string(i+2)+(string)" "+to_string(j+2)+ (string)" B "+to_string(i+5)+ (string)" "+to_string(j+5);
									temp1=temp2;
								}
							}								
						}
						if(initial.access(i-1,j-1)==unoccupied)
						{
							temp1.move(make_pair(i+2, j+2), make_pair(i-1, j-1));
							if(temp1==final)
								return (string)"S "+to_string(i+2)+(string)" "+to_string(j+2)+ (string)" M "+to_string(i-1)+ (string)" "+to_string(j-1);
							temp1=temp2;
							if(initial.access(i-2,j-2)==blackSoldier||initial.access(i-2,j-2)==blackTownhall)
							{
								temp1.shoot(make_pair(i, j),make_pair(i-2,j-2));
								if(temp1==final)
									return (string)"S "+to_string(i)+(string)" "+to_string(j)+ (string)" B "+to_string(i-2)+ (string)" "+to_string(j-2);
								temp1=temp2;
							}
							else if(initial.access(i-2,j-2)==unoccupied)
							{
								if(temp1==final)
									return (string)"S "+to_string(i)+(string)" "+to_string(j)+ (string)" B "+to_string(i)+ (string)" "+to_string(j);
								if(initial.access(i-3,j-3)==blackSoldier||initial.access(i-3,j-3)==blackTownhall)
								{
									temp1.shoot(make_pair(i, j),make_pair(i-3,j-3));
									if(temp1==final)
										return (string)"S "+to_string(i)+(string)" "+to_string(j)+ (string)" B "+to_string(i-3)+ (string)" "+to_string(j-3);
									temp1=temp2;
								}
							}								
						}
					}

					if(initial.access(i+1, j)==whiteSoldier&&initial.access(i+2, j)==whiteSoldier)
					{
						if(initial.access(i+3,j)==unoccupied)
						{
							temp1.move(make_pair(i, j), make_pair(i+3, j));
							if(temp1==final)
								return (string)"S "+to_string(i)+(string)" "+to_string(j)+ (string)" M "+to_string(i+3)+ (string)" "+to_string(j);
							temp1=temp2;
							if(initial.access(i+4,j)==blackSoldier||initial.access(i+4,j)==blackTownhall)
							{
								temp1.shoot(make_pair(i+2, j),make_pair(i+4,j));
								if(temp1==final)
									return (string)"S "+to_string(i+2)+(string)" "+to_string(j)+ (string)" B "+to_string(i+4)+ (string)" "+to_string(j);
								temp1=temp2;
							}
							else if(initial.access(i+4,j)==unoccupied)
							{
								if(temp1==final)
									return (string)"S "+to_string(i+2)+(string)" "+to_string(j)+ (string)" B "+to_string(i+4)+ (string)" "+to_string(j);
								if(initial.access(i+5,j)==blackSoldier||initial.access(i+5,j)==blackTownhall)
								{
									temp1.shoot(make_pair(i+2, j),make_pair(i+5,j));
									if(temp1==final)
										return (string)"S "+to_string(i+2)+(string)" "+to_string(j)+ (string)" B "+to_string(i+5)+ (string)" "+to_string(j);
									temp1=temp2;
								}
							}								
						}
						if(initial.access(i-1,j)==unoccupied)
						{
							temp1.move(make_pair(i+2, j), make_pair(i-1, j));
							if(temp1==final)
								return (string)"S "+to_string(i+2)+(string)" "+to_string(j)+ (string)" M "+to_string(i-1)+ (string)" "+to_string(j);
							temp1=temp2;
							if(initial.access(i-2,j)==blackSoldier||initial.access(i-2,j)==blackTownhall)
							{
								temp1.shoot(make_pair(i, j),make_pair(i-2,j));
								if(temp1==final)
									return (string)"S "+to_string(i)+(string)" "+to_string(j)+ (string)" B "+to_string(i-2)+ (string)" "+to_string(j);
								temp1=temp2;
							}
							else if(initial.access(i-2,j)==unoccupied)
							{
								if(temp1==final)
									return (string)"S "+to_string(i)+(string)" "+to_string(j)+ (string)" B "+to_string(i-2)+ (string)" "+to_string(j);
								if(initial.access(i-3,j)==blackSoldier||initial.access(i-3,j)==blackTownhall)
								{
									temp1.shoot(make_pair(i, j),make_pair(i-3,j));
									if(temp1==final)
										return (string)"S "+to_string(i)+(string)" "+to_string(j)+ (string)" B "+to_string(i-3)+ (string)" "+to_string(j);
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
				if(initial.getBoard()[i][j]==blackSoldier)
				{
					if(initial.access(i+1, j)==unoccupied||initial.access(i+1, j)==whiteSoldier||initial.access(i+1, j)==whiteTownhall){
						temp1.move(make_pair(i, j), make_pair(i+1, j));
						if(temp1==final)
							return (string)"S "+to_string(i)+(string)" "+to_string(j)+ (string)" M "+to_string(i+1)+ (string)" "+to_string(j);
						temp1=temp2;
					}
					if(initial.access(i+1, j+1)==unoccupied||initial.access(i+1, j+1)==whiteSoldier||initial.access(i+1, j+1)==whiteTownhall){
						temp1.move(make_pair(i, j), make_pair(i+1, j+1));
						if(temp1==final)
							return (string)"S "+to_string(i)+(string)" "+to_string(j)+ (string)" M "+to_string(i+1)+ (string)" "+to_string(j+1);
						temp1=temp2;
					}
					if(initial.access(i+1, j-1)==unoccupied||initial.access(i+1, j-1)==whiteSoldier||initial.access(i+1, j-1)==whiteTownhall){
						temp1.move(make_pair(i, j), make_pair(i+1, j-1));
						if(temp1==final)
							return (string)"S "+to_string(i)+(string)" "+to_string(j)+ (string)" M "+to_string(i+1)+ (string)" "+to_string(j-1);
						temp1=temp2;
					}
					if(initial.access(i, j+1)==whiteTownhall||initial.access(i, j+1)==whiteSoldier){
						temp1.move(make_pair(i, j), make_pair(i, j+1));
						if(temp1==final)
							return (string)"S "+to_string(i)+(string)" "+to_string(j)+ (string)" M "+to_string(i)+ (string)" "+to_string(j+1);
						temp1=temp2;
					}
					if(initial.access(i, j-1)==whiteTownhall||initial.access(i, j-1)==whiteSoldier){
						temp1.move(make_pair(i, j), make_pair(i, j-1));
						if(temp1==final)
							return (string)"S "+to_string(i)+(string)" "+to_string(j)+ (string)" M "+to_string(i)+ (string)" "+to_string(j-1);
						temp1=temp2;
					}
					//retreat
					if(initial.access(i-1, j)==whiteSoldier||initial.access(i-1, j+1)==whiteSoldier||initial.access(i-1, j-1)==whiteSoldier||initial.access(i, j+1)==whiteSoldier||initial.access(i, j-1)==whiteSoldier){
						if(i+2<8){
							temp1.move(make_pair(i, j), make_pair(i+2, j));
							if(temp1==final)
								return (string)"S "+to_string(i)+(string)" "+to_string(j)+ (string)" M "+to_string(i+2)+ (string)" "+to_string(j);
							temp1=temp2;
						}
						if(i+2<8&&j-2>=0){
							temp1.move(make_pair(i, j), make_pair(i+2, j-2));
							if(temp1==final)
								return (string)"S "+to_string(i)+(string)" "+to_string(j)+ (string)" M "+to_string(i+2)+ (string)" "+to_string(j-2);
							temp1=temp2;
						}
						if(i+2<8&&j+2<8){
							temp1.move(make_pair(i, j), make_pair(i+2, j+2));
							if(temp1==final)
								return (string)"S "+to_string(i)+(string)" "+to_string(j)+ (string)" M "+to_string(i+2)+ (string)" "+to_string(j+2);
							temp1=temp2;
						}
					}
					//cannon
					if(initial.access(i, j+1)==blackSoldier&&initial.access(i, j+2)==blackSoldier)
					{
						if(initial.access(i,j+3)==unoccupied)
						{
							temp1.move(make_pair(i, j), make_pair(i, j+3));
							if(temp1==final)
								return (string)"S "+to_string(i)+(string)" "+to_string(j)+ (string)" M "+to_string(i)+ (string)" "+to_string(j+3);
							temp1=temp2;
							if(initial.access(i,j+4)==whiteSoldier||initial.access(i,j+4)==whiteTownhall)
							{
								temp1.shoot(make_pair(i, j+2),make_pair(i,j+4));
								if(temp1==final)
									return (string)"S "+to_string(i)+(string)" "+to_string(j+2)+ (string)" B "+to_string(i)+ (string)" "+to_string(j+4);
								temp1=temp2;
							}
							else if(initial.access(i,j+4)==unoccupied)
							{
								if(temp1==final)
									return (string)"S "+to_string(i)+(string)" "+to_string(j+2)+ (string)" B "+to_string(i)+ (string)" "+to_string(j+4);
								if(initial.access(i,j+5)==whiteSoldier||initial.access(i,j+5)==whiteTownhall)
								{
									temp1.shoot(make_pair(i, j+2),make_pair(i,j+5));
									if(temp1==final)
										return (string)"S "+to_string(i)+(string)" "+to_string(j+2)+ (string)" B "+to_string(i)+ (string)" "+to_string(j+5);
									temp1=temp2;
								}
							}								
						}
						if(initial.access(i,j-1)==unoccupied)
						{
							temp1.move(make_pair(i, j+2), make_pair(i, j-1));
							if(temp1==final)
								return (string)"S "+to_string(i)+(string)" "+to_string(j+2)+ (string)" M "+to_string(i)+ (string)" "+to_string(j-1);
							temp1=temp2;
							if(initial.access(i,j-2)==whiteSoldier||initial.access(i,j-2)==whiteTownhall)
							{
								temp1.shoot(make_pair(i, j),make_pair(i,j-2));
								if(temp1==final)
									return (string)"S "+to_string(i)+(string)" "+to_string(j)+ (string)" B "+to_string(i)+ (string)" "+to_string(j-2);
								temp1=temp2;
							}
							else if(initial.access(i,j-2)==unoccupied)
							{
								if(temp1==final)
									return (string)"S "+to_string(i)+(string)" "+to_string(j)+ (string)" B "+to_string(i)+ (string)" "+to_string(j-2);
								if(initial.access(i,j-3)==whiteSoldier||initial.access(i,j-3)==whiteTownhall)
								{
									temp1.shoot(make_pair(i, j),make_pair(i,j-3));
									if(temp1==final)
										return (string)"S "+to_string(i)+(string)" "+to_string(j)+ (string)" B "+to_string(i)+ (string)" "+to_string(j-3);
									temp1=temp2;
								}
							}								
						}
					}

					if(initial.access(i+1, j-1)==blackSoldier&&initial.access(i+2, j-2)==blackSoldier)
					{
						if(initial.access(i+3,j-3)==unoccupied)
						{
							temp1.move(make_pair(i, j), make_pair(i+3, j-3));
							if(temp1==final)
								return (string)"S "+to_string(i)+(string)" "+to_string(j)+ (string)" M "+to_string(i+3)+ (string)" "+to_string(j-3);
							temp1=temp2;
							if(initial.access(i+4,j-4)==whiteSoldier||initial.access(i+4,j-4)==whiteTownhall)
							{
								temp1.shoot(make_pair(i+2, j-2),make_pair(i+4,j-4));
								if(temp1==final)
									return (string)"S "+to_string(i+2)+(string)" "+to_string(j-2)+ (string)" B "+to_string(i+4)+ (string)" "+to_string(j-4);
								temp1=temp2;
							}
							else if(initial.access(i+4,j-4)==unoccupied)
							{
								if(temp1==final)
									return (string)"S "+to_string(i+2)+(string)" "+to_string(j-2)+ (string)" B "+to_string(i+4)+ (string)" "+to_string(j-4);
								if(initial.access(i+5,j-5)==whiteSoldier||initial.access(i+5,j-5)==whiteTownhall)
								{
									temp1.shoot(make_pair(i+2, j-2),make_pair(i+5,j-5));
									if(temp1==final)
										return (string)"S "+to_string(i+2)+(string)" "+to_string(j-2)+ (string)" B "+to_string(i+5)+ (string)" "+to_string(j-5);
									temp1=temp2;
								}
							}								
						}
						if(initial.access(i-1,j+1)==unoccupied)
						{
							temp1.move(make_pair(i+2, j-2), make_pair(i-1, j+1));
							if(temp1==final)
								return (string)"S "+to_string(i+2)+(string)" "+to_string(j-2)+ (string)" M "+to_string(i-1)+ (string)" "+to_string(j+1);
							temp1=temp2;
							if(initial.access(i-2,j+2)==whiteSoldier||initial.access(i-2,j+2)==whiteTownhall)
							{
								temp1.shoot(make_pair(i, j),make_pair(i-2,j+2));
								if(temp1==final)
									return (string)"S "+to_string(i)+(string)" "+to_string(j)+ (string)" B "+to_string(i-2)+ (string)" "+to_string(j+2);
								temp1=temp2;
							}
							else if(initial.access(i-2,j+2)==unoccupied)
							{
								if(temp1==final)
									return (string)"S "+to_string(i)+(string)" "+to_string(j)+ (string)" B "+to_string(i-2)+ (string)" "+to_string(j+2);
								if(initial.access(i-3,j+3)==whiteSoldier||initial.access(i-3,j+3)==whiteTownhall)
								{
									temp1.shoot(make_pair(i, j),make_pair(i-3,j+3));
									if(temp1==final)
									return (string)"S "+to_string(i)+(string)" "+to_string(j)+ (string)" B "+to_string(i-3)+ (string)" "+to_string(j+3);
									temp1=temp2;
								}
							}								
						}
					}

					if(initial.access(i+1, j+1)==blackSoldier&&initial.access(i+2, j+2)==blackSoldier)
					{
						if(initial.access(i+3,j+3)==unoccupied)
						{
							temp1.move(make_pair(i, j), make_pair(i+3, j+3));
							if(temp1==final)
								return (string)"S "+to_string(i)+(string)" "+to_string(j)+ (string)" M "+to_string(i+3)+ (string)" "+to_string(j+3);
							temp1=temp2;
							if(initial.access(i+4,j+4)==whiteSoldier||initial.access(i+4,j+4)==whiteTownhall)
							{
								temp1.shoot(make_pair(i+2, j+2),make_pair(i+2,j+4));
								if(temp1==final)
									return (string)"S "+to_string(i+2)+(string)" "+to_string(j+2)+ (string)" B "+to_string(i+2)+ (string)" "+to_string(j+4);
								temp1=temp2;
							}
							else if(initial.access(i+4,j+4)==unoccupied)
							{
								if(temp1==final)
									return (string)"S "+to_string(i+2)+(string)" "+to_string(j+2)+ (string)" B "+to_string(i+2)+ (string)" "+to_string(j+4);
								if(initial.access(i+5,j+5)==whiteSoldier||initial.access(i+5,j+5)==whiteTownhall)
								{
									temp1.shoot(make_pair(i+2, j+2),make_pair(i+5,j+5));
									if(temp1==final)
									return (string)"S "+to_string(i+2)+(string)" "+to_string(j+2)+ (string)" B "+to_string(i+5)+ (string)" "+to_string(j+5);
									temp1=temp2;
								}
							}								
						}
						if(initial.access(i-1,j-1)==unoccupied)
						{
							temp1.move(make_pair(i+2, j+2), make_pair(i-1, j-1));
							if(temp1==final)
								return (string)"S "+to_string(i+2)+(string)" "+to_string(j+2)+ (string)" M "+to_string(i-1)+ (string)" "+to_string(j-1);
							temp1=temp2;
							if(initial.access(i-2,j-2)==whiteSoldier||initial.access(i-2,j-2)==whiteTownhall)
							{
								temp1.shoot(make_pair(i, j),make_pair(i-2,j-2));
								if(temp1==final)
									return (string)"S "+to_string(i)+(string)" "+to_string(j)+ (string)" B "+to_string(i-2)+ (string)" "+to_string(j-2);
								temp1=temp2;
							}
							else if(initial.access(i-2,j-2)==unoccupied)
							{
								if(temp1==final)
									return (string)"S "+to_string(i)+(string)" "+to_string(j)+ (string)" B "+to_string(i-2)+ (string)" "+to_string(j-2);
								if(initial.access(i-3,j-3)==whiteSoldier||initial.access(i-3,j-3)==whiteTownhall)
								{
									temp1.shoot(make_pair(i, j),make_pair(i-3,j-3));
									if(temp1==final)
										return (string)"S "+to_string(i)+(string)" "+to_string(j)+ (string)" B "+to_string(i-3)+ (string)" "+to_string(j-3);
									temp1=temp2;
								}
							}								
						}
					}

					if(initial.access(i+1, j)==blackSoldier&&initial.access(i+2, j)==blackSoldier)
					{
						if(initial.access(i+3,j)==unoccupied)
						{
							temp1.move(make_pair(i, j), make_pair(i+3, j));
							if(temp1==final)
								return (string)"S "+to_string(i)+(string)" "+to_string(j)+ (string)" M "+to_string(i+3)+ (string)" "+to_string(j);
							temp1=temp2;
							if(initial.access(i+4,j)==whiteSoldier||initial.access(i+4,j)==whiteTownhall)
							{
								temp1.shoot(make_pair(i+2, j),make_pair(i+4,j));
								if(temp1==final)
									return (string)"S "+to_string(i+2)+(string)" "+to_string(j)+ (string)" B "+to_string(i+4)+ (string)" "+to_string(j);
								temp1=temp2;
							}
							else if(initial.access(i+4,j)==unoccupied)
							{
								if(temp1==final)
									return (string)"S "+to_string(i+2)+(string)" "+to_string(j)+ (string)" B "+to_string(i+4)+ (string)" "+to_string(j);
								if(initial.access(i+5,j)==whiteSoldier||initial.access(i+5,j)==whiteTownhall)
								{
									temp1.shoot(make_pair(i+2, j),make_pair(i+5,j));
									if(temp1==final)
										return (string)"S "+to_string(i+2)+(string)" "+to_string(j)+ (string)" B "+to_string(i+5)+ (string)" "+to_string(j);
									temp1=temp2;
								}
							}								
						}
						if(initial.access(i-1,j)==unoccupied)
						{
							temp1.move(make_pair(i+2, j), make_pair(i-1, j));
							if(temp1==final)
								return (string)"S "+to_string(i+2)+(string)" "+to_string(j)+ (string)" M "+to_string(i-1)+ (string)" "+to_string(j);
							temp1=temp2;
							if(initial.access(i-2,j)==whiteSoldier||initial.access(i-2,j)==whiteTownhall)
							{
								temp1.shoot(make_pair(i, j),make_pair(i-2,j));
								if(temp1==final)
									return (string)"S "+to_string(i)+(string)" "+to_string(j)+ (string)" B "+to_string(i-2)+ (string)" "+to_string(j);
								temp1=temp2;
							}
							else if(initial.access(i-2,j)==unoccupied)
							{
								if(temp1==final)
									return (string)"S "+to_string(i)+(string)" "+to_string(j)+ (string)" B "+to_string(i-2)+ (string)" "+to_string(j);
								if(initial.access(i-3,j)==whiteSoldier||initial.access(i-3,j)==whiteTownhall)
								{
									temp1.shoot(make_pair(i, j),make_pair(i-3,j));
									if(temp1==final)
										return (string)"S "+to_string(i-3)+(string)" "+to_string(j)+ (string)" B "+to_string(i-3)+ (string)" "+to_string(j);
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
	return move;
}		
int max_value_action(CannonBoard present, int depth, bool white, int alpha, int beta, bool who);
int min_value_action(CannonBoard present, int depth, bool white,  int alpha, int beta, bool who);


string select_move(CannonBoard present,  int depth, bool white, bool who)
{

	vector<CannonBoard> successors = present.possibleStates(who);
	CannonBoard best_child;
	int alpha=INT_MIN, beta=INT_MAX;
	int max=INT_MIN;
	for(auto it=successors.begin();it!=successors.end();it++){
		int minVal;
		//cout<<"depth sent is "<<depth-1<<endl;
		minVal=min_value_action(*it, depth-1, white, alpha, beta, !who);
		//cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~`minval we got at depth "<<4-depth<<" was "<<minVal<<endl;
		//cout<<"to reach this, you do this"<<endl;
		//it->print();
		if(minVal>max){
			max=minVal;
			best_child=*it;
		}
	}
	//CannonBoard best_child= max_value_action(present, depth, white, INT_MIN, INT_MAX);
	//cout<<"finally chosen max evaluation is "<<max<<endl;
	//best_child.print();
	return transform_move(present, best_child, white);


}
int max_value_action(CannonBoard present, int depth, bool white, int alpha, int beta, bool who)
{
	//<<"max value action before possibleStates with depth "<<depth<<endl;
	vector<CannonBoard> successors = present.possibleStates(who);
	//cout<<"min value action after possibleStates with depth "<<depth<<endl;
	int max=INT_MIN;
	CannonBoard best_child;
	if(depth==0)
		return present.evaluate(white);
	for(auto it=successors.begin();it!=successors.end();it++){
		int minVal;
		if(depth==1){
			//cout<<"went all the way max, value given is"<<it->evaluate(white)<<endl;
			minVal=it->evaluate(white);//changed
		}
		else{
			minVal=min_value_action(*it, depth-1, white, alpha, beta, !who);
		}
		//cout<<"minval we got in maximiser at depth "<<4-depth<<" was "<<minVal<<endl;
		alpha=minVal>alpha?minVal:alpha;
		if (alpha>=beta){
			//cout<<"pruned max at depth "<<depth<<"with value "<<alpha<<" and "<<beta<<endl;
			return minVal;

		} 
		if(minVal>max){
			max=minVal;
			best_child=*it;
		}


	}
	//cout<<endl;
	//cout<<"~~~~~~~!!!!!!!!!!!minVal chosen by maximiser is "<<max<<endl<<endl;
	//cout<<"actual best max evaluation chosen is from depth "<<depth<<" is "<<best_child.evaluate_white()<<" and "<<best_child.evaluate_black()<<endl;
	//best_child.print();
	return max;
}
int min_value_action(CannonBoard present, int depth, bool white, int alpha, int beta, bool who)
{
	//cout<<"min value action before possibleStates with depth "<<depth<<endl;
	vector<CannonBoard> successors = present.possibleStates(who);
	//cout<<"min value action after possibleStates with depth "<<depth<<endl;
	int min=INT_MAX;
	CannonBoard best_child;
	if(depth==0)
		return present.evaluate(white);
	for(auto it=successors.begin();it!=successors.end();it++){

		int maxVal;
		int temp;
		if(depth==1){
			//cout<<"went all the way min, value given is"<<it->evaluate(white)<<endl;
			//it->print();
			maxVal=it->evaluate(white);//changed

		}
		else{
			temp=max_value_action(*it, depth-1, white, alpha, beta, !who);
			maxVal=temp;
		}
		//cout<<"~~~~~~~~maxval we got in minimiser at depth "<<4-depth<<" was "<<maxVal<<endl;
		beta=maxVal<beta?maxVal:beta;
		if (alpha>=beta){
			//cout<<"pruned min at depth "<<depth<<"with value "<<alpha<<" and "<<beta<<endl;
			return maxVal;

		} 
		if(maxVal<min){
			min=maxVal;
			best_child=*it;
		}


	}
	//cout<<endl;
	//cout<<"maxVal chosen by minimiser  is "<<min<<endl<<endl;
	if(depth==3){
		//cout<<"======================================actual best min evaluation chosen is from depth "<<depth<<" is "<<best_child.evaluate_white()<<" and "<<best_child.evaluate_black()<<endl;
	//best_child.print();
	}
	
	return min;
}
CannonBoard oneMove(string command, CannonBoard board)
{
	if(command.length()<11)
			return board;
		pair<int, int> init=make_pair((int)command[2]-48, (int)command[4]-48 );
		pair<int, int> target=make_pair((int)command[8]-48, (int)command[10]-48 );
		//cout<<"To move from "<<init.first<<", "<<init.second<<endl;
		//cout<<"Towards "<<target.first<<", "<<target.second<<endl;
		if(command[6]=='M')
		{
			board.move(init, target);
		}
		else if(command[6]=='B')
		{
			board.shoot(init, target);
		}
	return board;
}
vector<string> split (string s, string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    while ((pos_end = s.find (delimiter, pos_start)) != string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}

int main()
{
	fout.open("a.txt");
	string command1="";
	string command="";
	string command2="";
	
	CannonBoard ourBoard;
	getline (cin, command1); 
	//ourBoard.print();
	while(true){

		getline (cin, command1); 
		fout<<"After user the move "<<command1<<" state is "<<endl;
		vector<string> S1=split(command1," ");
		command=S1[0]+(string)" "+S1[2]+(string)" "+S1[1]+(string)" "+S1[3]+(string)" "+S1[5]+(string)" "+S1[4];
		ourBoard=oneMove(command, ourBoard);

		 fout<<ourBoard.prints();
		//cout<<command<<" done "<<endl;
		//ourBoard.print();

		//getline (cin, command2); 
		//vector<string> S2=split(command2," ");
		//command=S2[0]+(string)" "+S2[2]+(string)" "+S2[1]+(string)" "+S2[3]+(string)" "+S2[5]+(string)" "+S2[4];
		//ourBoard=oneMove(command, ourBoard);
		//cout<<command<<" done "<<endl;
		
		 string AImove;
		 AImove=select_move(ourBoard, 4, true, true);
		 vector<string> S=split(AImove," ");
		 
		
		 cout<<S[0]<<" "<<S[2]<<" "<<S[1]<<" "<<S[3]<<" "<<S[5]<<" "<<S[4]<<endl;
		 fout<<"After AI the move "<<S[0]<<" "<<S[2]<<" "<<S[1]<<" "<<S[3]<<" "<<S[5]<<" "<<S[4];
		 fout<<" state is "<<endl;
		 ourBoard=oneMove(AImove, ourBoard);
		 fout<<ourBoard.prints();
		 //ourBoard.print();
		// fout<<AImove<<" done "<<endl;
		// ourBoard.print();
	}	
	fout.close();
	return 0;
}
