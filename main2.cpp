#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono> 
#include <map>
#include <sstream>
#include <unordered_map> 
using namespace std;
enum state 
{   blackTownhall=-1, 
    whiteTownhall =1, 
    unoccupied=0,
    null=INT_MIN,
    blackSoldier= -2,
    whiteSoldier=2
};
enum move_type 
{   norm_move=0,
	bomb_empty=1,
	kill_soldier=2, 
    bomb_soldier =3, 
    bomb_townhall=11,
    kill_townhall=10
};
#define N 8
#define M 8
std::chrono::time_point<std::chrono::system_clock> begint;
std::chrono::time_point<std::chrono::system_clock> begintt;
// clock_t begin;
ofstream fout("output2.txt");
// enum cannontype
// {
// 	vertical=0,
// 	hor=1,
// 	rdiag=2,
// 	ldiag=3
// };
//first is soldiers, then cannons, then unoccupiedcannon hits, then occupiedcannon hits, then townhall hits, then townhalls
int parameters[]={45, 1, 1, 2, 50, 500, 0};
vector<state> seedVec(M, unoccupied);
class CannonBoard
{
	vector< vector<state> > board;
	
	public:
	string sig="";
	CannonBoard(): board(N, seedVec)
	{
		for(int i=0;i<N;i++){
			for(int j=0;j<M;++j){
				if((i==0)&&(j%2==0))
					board[i][j]=whiteTownhall;
				else if((i==0||i==1||i==2)&&(j%2==1))
					board[i][j]=whiteSoldier;
				else if((i==7||i==6||i==5)&&(j%2==0))
					board[i][j]=blackSoldier;
				else if((i==7)&&(j%2==1))
					board[i][j]=blackTownhall;
			}
		}
		//sig=sprint();
	}

	 vector< vector<state> >  getBoard() const
	{
		return board;
	}
	CannonBoard(const CannonBoard &copyCannon): board(M, seedVec)
	{
		board=copyCannon.getBoard();
		//sig=sprint();
	}
	state access(int i, int j) const
	{
		if(i<N&&j<M&&i>=0&&j>=0)
			return board[i][j];
		return null;
	}
	bool operator == (const CannonBoard &other) const
	{
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<M;++j)
			{
				if(other.access(i,j)!=access(i, j))
					return false;
			}
		}	
		return true;	

	}
	string sprint() const
	{
		stringstream ss;
		for(int i=0;i<N;i++){
			for(int j=0;j<M;j++){
				ss<<board[i][j];
			}
		}
		return ss.str();   
	}
		bool operator < (const CannonBoard &other) const
	{
		std::hash<string> str_hash;
		return str_hash(sprint())<str_hash(other.sprint());	

	}
	int sum( ) const
	{
		int sum=0;
		int p[]={2,3,7,11,13,19,23};
	
			for(int j=0;j<8;++j)   //change here ?
			{
				sum=sum+p[j]*access(j, 8-j);
				
			}	
		return sum;
	}
	
	bool move(pair<int, int> start, pair<int, int> end)
	{
		state dum=board[start.first][start.second];
		board[start.first][start.second]=unoccupied;
		board[end.first][end.second]=dum;
		//sig[start.first*7+start.second]=char(unoccupied);
		//sig[end.first*7+end.second]=char(dum);
		return true;
	}
	move_type smart_move(pair<int, int> start, pair<int, int> end)
	{
		state dum=board[start.first][start.second];
		board[start.first][start.second]=unoccupied;
		board[end.first][end.second]=dum;
		if(board[end.first][end.second]==unoccupied)
			return norm_move;
		else if(board[end.first][end.second]==abs(blackSoldier))
			return kill_soldier;
		else
			return kill_townhall;
		//return true;
	}
	bool shoot(pair<int, int> start, pair<int, int> end)
	{

		board[end.first][end.second]=unoccupied;
		//sig[end.first*7+end.second]=char(unoccupied);
		return true;
	}
	move_type smart_shoot(pair<int, int> start, pair<int, int> end)
	{

		board[end.first][end.second]=unoccupied;
		if(board[end.first][end.second]==unoccupied)
			return bomb_empty;
		else if(board[end.first][end.second]==abs(blackSoldier))
			return bomb_soldier;
		else
			return bomb_townhall;
		//return true;
	}
	vector<pair< pair<int,int>,pair<int,int> > > getCannons_white()
	{
		vector< pair<pair<int,int> ,pair<int,int> > > toReturn;
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<M;++j)
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
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<M;++j)
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
		for(int i=0;i<N;i++){
			for(int j=0;j<M;++j){
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
			for(int i=0;i<N;i++){
				for(int j=0;j<M;++j){
					if(board[i][j]==whiteSoldier)
					{
						if(access(i+1, j)==blackTownhall){
							temp1.move(make_pair(i, j), make_pair(i+1, j));
							possibleBoards.push_back(temp1);
							temp1=temp2;
						}
						if(access(i+1, j+1)==blackTownhall){
							temp1.move(make_pair(i, j), make_pair(i+1, j+1));
							possibleBoards.push_back(temp1);
							temp1=temp2;
						}
						if(access(i+1, j-1)==blackTownhall){
							temp1.move(make_pair(i, j), make_pair(i+1, j-1));
							possibleBoards.push_back(temp1);
							temp1=temp2;
						}
						if(access(i, j+1)==blackTownhall){
							temp1.move(make_pair(i, j), make_pair(i, j+1));
							possibleBoards.push_back(temp1);
							temp1=temp2;
						}
						if(access(i, j-1)==blackTownhall){
							temp1.move(make_pair(i, j), make_pair(i, j-1));
							possibleBoards.push_back(temp1);
							temp1=temp2;
						}
						//cout<<"at "<<i<<", "<<j<<"before cannons"<<endl;
						//cannons
						if(access(i, j+1)==whiteSoldier&&access(i, j+2)==whiteSoldier)
						{
							if(access(i,j+3)==unoccupied)
							{
								if(access(i,j+4)==blackTownhall)
								{
									temp1.shoot(make_pair(i, j+2),make_pair(i,j+4));
									possibleBoards.push_back(temp1);
									temp1=temp2;
								}
								if(access(i,j+5)==blackTownhall)
								{
									temp1.shoot(make_pair(i, j+2),make_pair(i,j+5));
									possibleBoards.push_back(temp1);
									temp1=temp2;
								}
								if(access(i,j+4)==unoccupied||access(i,j+5)==unoccupied)
								{
									samestate=true;
								}								
							}
							if(access(i,j-1)==unoccupied)
							{
								if(access(i,j-2)==blackTownhall)
								{
									temp1.shoot(make_pair(i, j),make_pair(i,j-2));
									possibleBoards.push_back(temp1);
									temp1=temp2;
								}
								if(access(i,j-3)==blackTownhall)
								{
									temp1.shoot(make_pair(i, j),make_pair(i,j-3));
									possibleBoards.push_back(temp1);
									temp1=temp2;
								}
								if(access(i,j-2)==unoccupied||access(i,j+5)==unoccupied)
								{
									samestate=true;	
								}								
							}
						}

						if(access(i+1, j-1)==whiteSoldier&&access(i+2, j-2)==whiteSoldier)
						{
							if(access(i+3,j-3)==unoccupied)
							{
								if(access(i+4,j-4)==blackTownhall)
								{
									temp1.shoot(make_pair(i+2, j-2),make_pair(i+4,j-4));
									possibleBoards.push_back(temp1);
									temp1=temp2;
								}
								if(access(i+5,j-5)==blackTownhall)
								{
									temp1.shoot(make_pair(i+2, j-2),make_pair(i+5,j-5));
									possibleBoards.push_back(temp1);
									temp1=temp2;
								}
								if(access(i+4,j-4)==unoccupied||access(i+5,j-5)==unoccupied)
								{
									samestate=true;	
								}								
							}
							if(access(i-1,j+1)==unoccupied)
							{
								if(access(i-2,j+2)==blackTownhall)
								{
									temp1.shoot(make_pair(i, j),make_pair(i-2,j+2));
									possibleBoards.push_back(temp1);
									temp1=temp2;
								}
								if(access(i-3,j+3)==blackTownhall)
								{
									temp1.shoot(make_pair(i, j),make_pair(i-3,j+3));
									possibleBoards.push_back(temp1);
									temp1=temp2;
								}
								if(access(i-3,j+3)==unoccupied)
								{
									samestate=true;	
								}								
							}
						}

						if(access(i+1, j+1)==whiteSoldier&&access(i+2, j+2)==whiteSoldier)
						{
							if(access(i+3,j+3)==unoccupied)
							{
								if(access(i+4,j+4)==blackTownhall)
								{
									temp1.shoot(make_pair(i+2, j+2),make_pair(i+2,j+4));
									possibleBoards.push_back(temp1);
									temp1=temp2;
								}
								if(access(i+5,j+5)==blackTownhall)
								{
									temp1.shoot(make_pair(i+2, j+2),make_pair(i+5,j+5));
									possibleBoards.push_back(temp1);
									temp1=temp2;
								}
								if(access(i+4,j+4)==unoccupied||access(i+5,j+5)==unoccupied)
								{
									samestate=true;
									
								}								
							}
							if(access(i-1,j-1)==unoccupied)
							{
								if(access(i-2,j-2)==blackTownhall)
								{
									temp1.shoot(make_pair(i, j),make_pair(i-2,j-2));
									possibleBoards.push_back(temp1);
									temp1=temp2;
								}
								if(access(i-3,j-3)==blackTownhall)
								{
									temp1.shoot(make_pair(i, j),make_pair(i-3,j-3));
									possibleBoards.push_back(temp1);
									temp1=temp2;
								}
								if(access(i-2,j-2)==unoccupied||access(i-3,j-3)==unoccupied)
								{
									samestate=true;
									
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
								if(access(i+4,j)==blackTownhall)
								{
									temp1.shoot(make_pair(i+2, j),make_pair(i+4,j));
									possibleBoards.push_back(temp1);
									temp1=temp2;
								}
								if(access(i+5,j)==blackTownhall)
								{
									temp1.shoot(make_pair(i+2, j),make_pair(i+5,j));
									possibleBoards.push_back(temp1);
									temp1=temp2;
								}
								if(access(i+4,j)==unoccupied||access(i+5,j)==unoccupied)
								{
									samestate=true;
									
								}								
							}
							if(access(i-1,j)==unoccupied)
							{
								if(access(i-2,j)==blackTownhall)
								{
									temp1.shoot(make_pair(i, j),make_pair(i-2,j));
									possibleBoards.push_back(temp1);
									temp1=temp2;
								}
								if(access(i-3,j)==blackTownhall)
									{
										temp1.shoot(make_pair(i, j),make_pair(i-3,j));
										possibleBoards.push_back(temp1);
										temp1=temp2;
									}
								else if(access(i-2,j)==unoccupied||access(i-3,j)==unoccupied)
								{
									samestate=true;	
								}								
							}
						}
						//end cannon moves/shoots
					}
				}
			}

			for(int i=0;i<N;i++){
				for(int j=0;j<M;++j){
					if(board[i][j]==whiteSoldier)
					{
						if(access(i+1, j)==blackSoldier){
							temp1.move(make_pair(i, j), make_pair(i+1, j));
							possibleBoards.push_back(temp1);
							temp1=temp2;
						}
						if(access(i+1, j+1)==blackSoldier){
							temp1.move(make_pair(i, j), make_pair(i+1, j+1));
							possibleBoards.push_back(temp1);
							temp1=temp2;
						}
						if(access(i+1, j-1)==blackSoldier){
							temp1.move(make_pair(i, j), make_pair(i+1, j-1));
							possibleBoards.push_back(temp1);
							temp1=temp2;
						}
						if(access(i, j+1)==blackSoldier){
							temp1.move(make_pair(i, j), make_pair(i, j+1));
							possibleBoards.push_back(temp1);
							temp1=temp2;
						}
						if(access(i, j-1)==blackSoldier){
							temp1.move(make_pair(i, j), make_pair(i, j-1));
							possibleBoards.push_back(temp1);
							temp1=temp2;
						}

						//cout<<"at "<<i<<", "<<j<<"before cannons"<<endl;
						//cannons
						if(access(i, j+1)==whiteSoldier&&access(i, j+2)==whiteSoldier)
						{
							if(access(i,j+3)==unoccupied)
							{
								if(access(i,j+4)==blackSoldier)
								{
									temp1.shoot(make_pair(i, j+2),make_pair(i,j+4));
									possibleBoards.push_back(temp1);
									temp1=temp2;
								}
								if(access(i,j+5)==blackSoldier)
									{
										temp1.shoot(make_pair(i, j+2),make_pair(i,j+5));
										possibleBoards.push_back(temp1);
										temp1=temp2;
									}								
							}
							if(access(i,j-1)==unoccupied)
							{
								if(access(i,j-2)==blackSoldier)
								{
									temp1.shoot(make_pair(i, j),make_pair(i,j-2));
									possibleBoards.push_back(temp1);
									temp1=temp2;
								}
								if(access(i,j-3)==blackSoldier)
								{
									temp1.shoot(make_pair(i, j),make_pair(i,j-3));
									possibleBoards.push_back(temp1);
									temp1=temp2;
								}							
							}
						}

						if(access(i+1, j-1)==whiteSoldier&&access(i+2, j-2)==whiteSoldier)
						{
							if(access(i+3,j-3)==unoccupied)
							{
								if(access(i+4,j-4)==blackSoldier)
								{
									temp1.shoot(make_pair(i+2, j-2),make_pair(i+4,j-4));
									possibleBoards.push_back(temp1);
									temp1=temp2;
								}
								if(access(i+5,j-5)==blackSoldier)
									{
										temp1.shoot(make_pair(i+2, j-2),make_pair(i+5,j-5));
										possibleBoards.push_back(temp1);
										temp1=temp2;
									}								
							}
							if(access(i-1,j+1)==unoccupied)
							{
								if(access(i-2,j+2)==blackSoldier)
								{
									temp1.shoot(make_pair(i, j),make_pair(i-2,j+2));
									possibleBoards.push_back(temp1);
									temp1=temp2;
								}
								if(access(i-3,j+3)==blackSoldier)
								{
									temp1.shoot(make_pair(i, j),make_pair(i-3,j+3));
									possibleBoards.push_back(temp1);
									temp1=temp2;
								}							
							}
						}

						if(access(i+1, j+1)==whiteSoldier&&access(i+2, j+2)==whiteSoldier)
						{
							if(access(i+3,j+3)==unoccupied)
							{
								if(access(i+4,j+4)==blackSoldier)
								{
									temp1.shoot(make_pair(i+2, j+2),make_pair(i+2,j+4));
									possibleBoards.push_back(temp1);
									temp1=temp2;
								}
								if(access(i+5,j+5)==blackSoldier)
								{
									temp1.shoot(make_pair(i+2, j+2),make_pair(i+5,j+5));
									possibleBoards.push_back(temp1);
									temp1=temp2;
								}								
							}
							if(access(i-1,j-1)==unoccupied)
							{
								if(access(i-2,j-2)==blackSoldier)
								{
									temp1.shoot(make_pair(i, j),make_pair(i-2,j-2));
									possibleBoards.push_back(temp1);
									temp1=temp2;
								}
								if(access(i-3,j-3)==blackSoldier)
								{
									temp1.shoot(make_pair(i, j),make_pair(i-3,j-3));
									possibleBoards.push_back(temp1);
									temp1=temp2;
								}							
							}
						}
						//cout<<"at "<<i<<", "<<j<<"before retreat"<<endl;
						if(access(i+1, j)==whiteSoldier&&access(i+2, j)==whiteSoldier)
						{
							if(access(i+3,j)==unoccupied)
							{
								if(access(i+4,j)==blackSoldier)
								{
									temp1.shoot(make_pair(i+2, j),make_pair(i+4,j));
									possibleBoards.push_back(temp1);
									temp1=temp2;
								}
								if(access(i+5,j)==blackSoldier)
									{
										temp1.shoot(make_pair(i+2, j),make_pair(i+5,j));
										possibleBoards.push_back(temp1);
										temp1=temp2;
									}								
							}
							if(access(i-1,j)==unoccupied)
							{
								if(access(i-2,j)==blackSoldier)
								{
									temp1.shoot(make_pair(i, j),make_pair(i-2,j));
									possibleBoards.push_back(temp1);
									temp1=temp2;
								}
								if(access(i-3,j)==blackSoldier)
								{
										temp1.shoot(make_pair(i, j),make_pair(i-3,j));
										possibleBoards.push_back(temp1);
										temp1=temp2;
								}				
							}
						}
						//end cannon moves/shoots
					}
				}
			}

			for(int i=0;i<N;i++){
				for(int j=0;j<M;++j){
					if(board[i][j]==whiteSoldier)
					{
						if(access(i+1, j)==unoccupied){
							temp1.move(make_pair(i, j), make_pair(i+1, j));
							possibleBoards.push_back(temp1);
							temp1=temp2;
						}
						if(access(i+1, j+1)==unoccupied){
							temp1.move(make_pair(i, j), make_pair(i+1, j+1));
							possibleBoards.push_back(temp1);
							temp1=temp2;
						}
						if(access(i+1, j-1)==unoccupied){
							temp1.move(make_pair(i, j), make_pair(i+1, j-1));
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
							if(i-2>=0&&j+2<M){
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
							}
							if(access(i,j-1)==unoccupied)
							{
								temp1.move(make_pair(i, j+2), make_pair(i, j-1));
								possibleBoards.push_back(temp1);
								temp1=temp2;							
							}
						}

						if(access(i+1, j-1)==whiteSoldier&&access(i+2, j-2)==whiteSoldier)
						{
							if(access(i+3,j-3)==unoccupied)
							{
								temp1.move(make_pair(i, j), make_pair(i+3, j-3));
								possibleBoards.push_back(temp1);
								temp1=temp2;							
							}
							if(access(i-1,j+1)==unoccupied)
							{
								temp1.move(make_pair(i+2, j-2), make_pair(i-1, j+1));
								possibleBoards.push_back(temp1);
								temp1=temp2;							
							}
						}

						if(access(i+1, j+1)==whiteSoldier&&access(i+2, j+2)==whiteSoldier)
						{
							if(access(i+3,j+3)==unoccupied)
							{
								temp1.move(make_pair(i, j), make_pair(i+3, j+3));
								possibleBoards.push_back(temp1);
								temp1=temp2;							
							}
							if(access(i-1,j-1)==unoccupied)
							{
								temp1.move(make_pair(i+2, j+2), make_pair(i-1, j-1));
								possibleBoards.push_back(temp1);
								temp1=temp2;							
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
							}
							if(access(i-1,j)==unoccupied)
							{
								temp1.move(make_pair(i+2, j), make_pair(i-1, j));
								possibleBoards.push_back(temp1);
								temp1=temp2;							
							}
						}
						//end cannon moves/shoots
					}
				}
			}
		}
		else{
			for(int i=0;i<N;i++){
				for(int j=0;j<M;++j){
					if(board[i][j]==blackSoldier)
					{
						if(access(i-1, j)==whiteTownhall){
							temp1.move(make_pair(i, j), make_pair(i-1, j));
							possibleBoards.push_back(temp1);
							temp1=temp2;
						}
						if(access(i-1, j+1)==whiteTownhall){
							temp1.move(make_pair(i, j), make_pair(i-1, j+1));
							possibleBoards.push_back(temp1);
							temp1=temp2;
						}
						if(access(i-1, j-1)==whiteTownhall){
							temp1.move(make_pair(i, j), make_pair(i-1, j-1));
							possibleBoards.push_back(temp1);
							temp1=temp2;
						}
						if(access(i, j+1)==whiteTownhall){
							temp1.move(make_pair(i, j), make_pair(i, j+1));
							possibleBoards.push_back(temp1);
							temp1=temp2;
						}
						if(access(i, j-1)==whiteTownhall){
							temp1.move(make_pair(i, j), make_pair(i, j-1));
							possibleBoards.push_back(temp1);
							temp1=temp2;
						}
						//cannon
						if(access(i, j+1)==blackSoldier&&access(i, j+2)==blackSoldier)
						{
							if(access(i,j+3)==unoccupied)
							{
								if(access(i,j+4)==whiteTownhall)
								{
									temp1.shoot(make_pair(i, j+2),make_pair(i,j+4));
									possibleBoards.push_back(temp1);
									temp1=temp2;
								}
								if(access(i,j+5)==whiteTownhall)
									{
										temp1.shoot(make_pair(i, j+2),make_pair(i,j+5));
										possibleBoards.push_back(temp1);
										temp1=temp2;
									}
								if(access(i,j+4)==unoccupied||access(i,j+5)==unoccupied)
								{
									samestate=true;
								}								
							}
							if(access(i,j-1)==unoccupied)
							{
								if(access(i,j-2)==whiteTownhall)
								{
									temp1.shoot(make_pair(i, j),make_pair(i,j-2));
									possibleBoards.push_back(temp1);
									temp1=temp2;
								}
								if(access(i,j-3)==whiteTownhall)
									{
										temp1.shoot(make_pair(i, j),make_pair(i,j-3));
										possibleBoards.push_back(temp1);
										temp1=temp2;
									}
								if(access(i,j-2)==unoccupied||access(i,j-3)==unoccupied)
								{
									samestate=true;						
								}								
							}
						}

						if(access(i+1, j-1)==blackSoldier&&access(i+2, j-2)==blackSoldier)
						{
							if(access(i+3,j-3)==unoccupied)
							{
								if(access(i+4,j-4)==whiteTownhall)
								{
									temp1.shoot(make_pair(i+2, j-2),make_pair(i+4,j-4));
									possibleBoards.push_back(temp1);
									temp1=temp2;
								}
								if(access(i+5,j-5)==whiteTownhall)
									{
										temp1.shoot(make_pair(i+2, j-2),make_pair(i+5,j-5));
										possibleBoards.push_back(temp1);
										temp1=temp2;
									}
								if(access(i+4,j-4)==unoccupied||access(i+5,j-5)==unoccupied)
								{
									samestate=true;
									
								}								
							}
							if(access(i-1,j+1)==unoccupied)
							{
								if(access(i-2,j+2)==whiteTownhall)
								{
									temp1.shoot(make_pair(i, j),make_pair(i-2,j+2));
									possibleBoards.push_back(temp1);
									temp1=temp2;
								}
								if(access(i-3,j+3)==whiteTownhall)
									{
										temp1.shoot(make_pair(i, j),make_pair(i-3,j+3));
										possibleBoards.push_back(temp1);
										temp1=temp2;
									}
								if(access(i-2,j+2)==unoccupied||access(i-3,j+3)==unoccupied)
								{
									samestate=true;
									
								}								
							}
						}

						if(access(i+1, j+1)==blackSoldier&&access(i+2, j+2)==blackSoldier)
						{
							if(access(i+3,j+3)==unoccupied)
							{
								if(access(i+4,j+4)==whiteTownhall)
								{
									temp1.shoot(make_pair(i+2, j+2),make_pair(i+2,j+4));
									possibleBoards.push_back(temp1);
									temp1=temp2;
								}
								if(access(i+5,j+5)==whiteTownhall)
									{
										temp1.shoot(make_pair(i+2, j+2),make_pair(i+5,j+5));
										possibleBoards.push_back(temp1);
										temp1=temp2;
									}
								if(access(i+4,j+4)==unoccupied||access(i+5,j+5)==unoccupied)
								{
									samestate=true;
									
								}								
							}
							if(access(i-1,j-1)==unoccupied)
							{
								if(access(i-2,j-2)==whiteTownhall)
								{
									temp1.shoot(make_pair(i, j),make_pair(i-2,j-2));
									possibleBoards.push_back(temp1);
									temp1=temp2;
								}
								if(access(i-3,j-3)==whiteTownhall)
									{
										temp1.shoot(make_pair(i, j),make_pair(i-3,j-3));
										possibleBoards.push_back(temp1);
										temp1=temp2;
									}
								if(access(i-2,j-2)==unoccupied||access(i-3,j-3)==unoccupied)
								{
									samestate=true;									
								}								
							}
						}

						if(access(i+1, j)==blackSoldier&&access(i+2, j)==blackSoldier)
						{
							if(access(i+3,j)==unoccupied)
							{
								if(access(i+4,j)==whiteTownhall)
								{
									temp1.shoot(make_pair(i+2, j),make_pair(i+4,j));
									possibleBoards.push_back(temp1);
									temp1=temp2;
								}
								if(access(i+5,j)==whiteTownhall)
									{
										temp1.shoot(make_pair(i+2, j),make_pair(i+5,j));
										possibleBoards.push_back(temp1);
										temp1=temp2;
									}
								if(access(i+4,j)==unoccupied||access(i+5,j)==unoccupied)
								{
									samestate=true;
									
								}								
							}
							if(access(i-1,j)==unoccupied)
							{
								if(access(i-2,j)==whiteTownhall)
								{
									temp1.shoot(make_pair(i, j),make_pair(i-2,j));
									possibleBoards.push_back(temp1);
									temp1=temp2;
								}
								if(access(i-3,j)==whiteTownhall)
									{
										temp1.shoot(make_pair(i, j),make_pair(i-3,j));
										possibleBoards.push_back(temp1);
										temp1=temp2;
									}
								if(access(i-2,j)==unoccupied||access(i-3,j)==unoccupied)
								{
									samestate=true;
									
								}								
							}
						}
						//end cannon moves/shoots
					}
				}
			}

			for(int i=0;i<N;i++){
				for(int j=0;j<M;++j){
					if(board[i][j]==blackSoldier)
					{
						if(access(i-1, j)==whiteSoldier){
							temp1.move(make_pair(i, j), make_pair(i-1, j));
							possibleBoards.push_back(temp1);
							temp1=temp2;
						}
						if(access(i-1, j+1)==whiteSoldier){
							temp1.move(make_pair(i, j), make_pair(i-1, j+1));
							possibleBoards.push_back(temp1);
							temp1=temp2;
						}
						if(access(i-1, j-1)==whiteSoldier){
							temp1.move(make_pair(i, j), make_pair(i-1, j-1));
							possibleBoards.push_back(temp1);
							temp1=temp2;
						}
						if(access(i, j+1)==whiteSoldier){
							temp1.move(make_pair(i, j), make_pair(i, j+1));
							possibleBoards.push_back(temp1);
							temp1=temp2;
						}
						if(access(i, j-1)==whiteSoldier){
							temp1.move(make_pair(i, j), make_pair(i, j-1));
							possibleBoards.push_back(temp1);
							temp1=temp2;
						}
						//cannon
						if(access(i, j+1)==blackSoldier&&access(i, j+2)==blackSoldier)
						{
							if(access(i,j+3)==unoccupied)
							{
								if(access(i,j+4)==whiteSoldier)
								{
									temp1.shoot(make_pair(i, j+2),make_pair(i,j+4));
									possibleBoards.push_back(temp1);
									temp1=temp2;
								}
								if(access(i,j+5)==whiteSoldier)
									{
										temp1.shoot(make_pair(i, j+2),make_pair(i,j+5));
										possibleBoards.push_back(temp1);
										temp1=temp2;
									}								
							}
							if(access(i,j-1)==unoccupied)
							{
								if(access(i,j-2)==whiteSoldier)
								{
									temp1.shoot(make_pair(i, j),make_pair(i,j-2));
									possibleBoards.push_back(temp1);
									temp1=temp2;
								}
								if(access(i,j-3)==whiteSoldier)
									{
										temp1.shoot(make_pair(i, j),make_pair(i,j-3));
										possibleBoards.push_back(temp1);
										temp1=temp2;
									}							
							}
						}

						if(access(i+1, j-1)==blackSoldier&&access(i+2, j-2)==blackSoldier)
						{
							if(access(i+3,j-3)==unoccupied)
							{
								if(access(i+4,j-4)==whiteSoldier)
								{
									temp1.shoot(make_pair(i+2, j-2),make_pair(i+4,j-4));
									possibleBoards.push_back(temp1);
									temp1=temp2;
								}
								if(access(i+5,j-5)==whiteSoldier)
									{
										temp1.shoot(make_pair(i+2, j-2),make_pair(i+5,j-5));
										possibleBoards.push_back(temp1);
										temp1=temp2;
									}							
							}
							if(access(i-1,j+1)==unoccupied)
							{
								if(access(i-2,j+2)==whiteSoldier)
								{
									temp1.shoot(make_pair(i, j),make_pair(i-2,j+2));
									possibleBoards.push_back(temp1);
									temp1=temp2;
								}
								if(access(i-3,j+3)==whiteSoldier)
									{
										temp1.shoot(make_pair(i, j),make_pair(i-3,j+3));
										possibleBoards.push_back(temp1);
										temp1=temp2;
									}							
							}
						}

						if(access(i+1, j+1)==blackSoldier&&access(i+2, j+2)==blackSoldier)
						{
							if(access(i+3,j+3)==unoccupied)
							{
								if(access(i+4,j+4)==whiteSoldier)
								{
									temp1.shoot(make_pair(i+2, j+2),make_pair(i+2,j+4));
									possibleBoards.push_back(temp1);
									temp1=temp2;
								}
								if(access(i+5,j+5)==whiteSoldier)
									{
										temp1.shoot(make_pair(i+2, j+2),make_pair(i+5,j+5));
										possibleBoards.push_back(temp1);
										temp1=temp2;
									}								
							}
							if(access(i-1,j-1)==unoccupied)
							{
								temp1.move(make_pair(i+2, j+2), make_pair(i-1, j-1));
								possibleBoards.push_back(temp1);
								temp1=temp2;
								if(access(i-2,j-2)==whiteSoldier)
								{
									temp1.shoot(make_pair(i, j),make_pair(i-2,j-2));
									possibleBoards.push_back(temp1);
									temp1=temp2;
								}
								if(access(i-3,j-3)==whiteSoldier)
								{
									temp1.shoot(make_pair(i, j),make_pair(i-3,j-3));
									possibleBoards.push_back(temp1);
									temp1=temp2;
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
								if(access(i+4,j)==whiteSoldier)
								{
									temp1.shoot(make_pair(i+2, j),make_pair(i+4,j));
									possibleBoards.push_back(temp1);
									temp1=temp2;
								}
								if(access(i+5,j)==whiteSoldier)
									{
										temp1.shoot(make_pair(i+2, j),make_pair(i+5,j));
										possibleBoards.push_back(temp1);
										temp1=temp2;
									}								
							}
							if(access(i-1,j)==unoccupied)
							{
								temp1.move(make_pair(i+2, j), make_pair(i-1, j));
								possibleBoards.push_back(temp1);
								temp1=temp2;
								if(access(i-2,j)==whiteSoldier)
								{
									temp1.shoot(make_pair(i, j),make_pair(i-2,j));
									possibleBoards.push_back(temp1);
									temp1=temp2;
								}
								if(access(i-3,j)==whiteSoldier)
									{
										temp1.shoot(make_pair(i, j),make_pair(i-3,j));
										possibleBoards.push_back(temp1);
										temp1=temp2;
									}								
							}
						}
						//end cannon moves/shoots
					}
				}
			}

			for(int i=0;i<N;i++){
				for(int j=0;j<M;++j){
					if(board[i][j]==blackSoldier)
					{
						if(access(i-1, j)==unoccupied){
							temp1.move(make_pair(i, j), make_pair(i-1, j));
							possibleBoards.push_back(temp1);
							temp1=temp2;
						}
						if(access(i-1, j+1)==unoccupied){
							temp1.move(make_pair(i, j), make_pair(i-1, j+1));
							possibleBoards.push_back(temp1);
							temp1=temp2;
						}
						if(access(i-1, j-1)==unoccupied){
							temp1.move(make_pair(i, j), make_pair(i-1, j-1));
							possibleBoards.push_back(temp1);
							temp1=temp2;
						}
						//retreat
						if(access(i-1, j)==whiteSoldier||access(i-1, j+1)==whiteSoldier||access(i-1, j-1)==whiteSoldier||access(i, j+1)==whiteSoldier||access(i, j-1)==whiteSoldier){
							if(i+2<N){
								temp1.move(make_pair(i, j), make_pair(i+2, j));							
								possibleBoards.push_back(temp1);
								temp1=temp2;
							}
							if(i+2<N&&j-2>=0){
								temp1.move(make_pair(i, j), make_pair(i+2, j-2));
								possibleBoards.push_back(temp1);
								temp1=temp2;
							}if(i+2<N&&j+2<M){
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
							}
							if(access(i,j-1)==unoccupied)
							{
								temp1.move(make_pair(i, j+2), make_pair(i, j-1));
								possibleBoards.push_back(temp1);
								temp1=temp2;								
							}
						}

						if(access(i+1, j-1)==blackSoldier&&access(i+2, j-2)==blackSoldier)
						{
							if(access(i+3,j-3)==unoccupied)
							{
								temp1.move(make_pair(i, j), make_pair(i+3, j-3));
								possibleBoards.push_back(temp1);
								temp1=temp2;								
							}
							if(access(i-1,j+1)==unoccupied)
							{
								temp1.move(make_pair(i+2, j-2), make_pair(i-1, j+1));
								possibleBoards.push_back(temp1);
								temp1=temp2;								
							}
						}

						if(access(i+1, j+1)==blackSoldier&&access(i+2, j+2)==blackSoldier)
						{
							if(access(i+3,j+3)==unoccupied)
							{
								temp1.move(make_pair(i, j), make_pair(i+3, j+3));
								possibleBoards.push_back(temp1);
								temp1=temp2;								
							}
							if(access(i-1,j-1)==unoccupied)
							{
								temp1.move(make_pair(i+2, j+2), make_pair(i-1, j-1));
								possibleBoards.push_back(temp1);
								temp1=temp2;								
							}
						}

						if(access(i+1, j)==blackSoldier&&access(i+2, j)==blackSoldier)
						{
							if(access(i+3,j)==unoccupied)
							{
								temp1.move(make_pair(i, j), make_pair(i+3, j));
								possibleBoards.push_back(temp1);
								temp1=temp2;								
							}
							if(access(i-1,j)==unoccupied)
							{
								temp1.move(make_pair(i+2, j), make_pair(i-1, j));
								possibleBoards.push_back(temp1);
								temp1=temp2;								
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
		// 		//fout<<board[i][j]<<"\t";
		// 	}
		// 	//fout<<endl;
		
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
	int evaluate_white();
	int evaluate_black();
	int evaluate(bool white);
	

	void print()
	{
		for(int i=0;i<N;i++){
			for(int j=0;j<M;++j){
				cout<<board[i][j]<<"\t";
			}
			cout<<endl;
		}   
	}

};
namespace std {

  template <>
  struct hash<CannonBoard >
  {
    std::size_t operator()(const CannonBoard& k) const
    {
      using std::size_t;
      using std::hash;
      using std::string;
      std::hash<string> str_hash;

      // Compute individual hash values for first,
      // second and third and combine them using XOR
      // and bit shifting:

      return str_hash(k.sig);
    }
  };

}
unordered_map<string, long> ohoho;
unordered_map<CannonBoard, long> map_state_white;
unordered_map<CannonBoard, long> map_state_black;	
int CannonBoard::evaluate_white()
	{
		int soldiers=0, townhalls=0, cannons=0;
		for(int i=0;i<N;i++){
			for(int j=0;j<M;++j){
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
				hits_unoccupied=(access(start.first+2, start.second)==unoccupied)+(access(start.first+3, start.second )==unoccupied)+(access(end.first-2, start.second)==unoccupied)+(access(end.first-3, start.second)==unoccupied);
				hits_townhall=(access(start.first+2, start.second)==blackTownhall)+(access(start.first+3, start.second)==blackTownhall)+(access(end.first-2, start.second)==blackTownhall)+(access(end.first-3, start.second)==blackTownhall);
				hits_black=(access(start.first+2, start.second)==blackSoldier)+(access(start.first+3, start.second)==blackSoldier)+(access(end.first-2, start.second)==blackSoldier)+(access(end.first-3, start.second)==blackSoldier);
			}
			else if((start.first==end.first-2)&&(start.second==end.second)){
				hits_unoccupied=(access(start.first-2, start.second)==unoccupied)+(access(start.first-3, start.second)==unoccupied)+(access(end.first+2, start.second)==unoccupied)+(access(end.first+3, start.second)==unoccupied);
				hits_townhall=(access(start.first-2, start.second)==blackTownhall)+(access(start.first-3, start.second)==blackTownhall)+(access(end.first+2, start.second)==blackTownhall)+(access(end.first+3, start.second)==blackTownhall);
				hits_black=(access(start.first-2, start.second)==blackSoldier)+(access(start.first-3, start.second)==blackSoldier)+(access(end.first+2, start.second)==blackSoldier)+(access(end.first+3, start.second)==blackSoldier);
			}
			else if((start.first==end.first)&&(start.second==end.second-2)){
				hits_unoccupied=(access(start.first, start.second-2)==unoccupied)+(access(start.first, start.second-3)==unoccupied)+(access(end.first, start.second+2)==unoccupied)+(access(end.first, start.second+3)==unoccupied);
				hits_townhall=(access(start.first, start.second-2)==blackTownhall)+(access(start.first, start.second-3)==blackTownhall)+(access(end.first, start.second+2)==blackTownhall)+(access(end.first, start.second+3)==blackTownhall);
				hits_black=(access(start.first, start.second-2)==blackSoldier)+(access(start.first, start.second-3)==blackSoldier)+(access(end.first, start.second+2)==blackSoldier)+(access(end.first, start.second+3)==blackSoldier);
			}
			else if((start.first==end.first)&&(start.second==end.second+2)){
				hits_unoccupied=(access(start.first, start.second+2)==unoccupied)+(access(start.first, start.second+3)==unoccupied)+(access(end.first, start.second-2)==unoccupied)+(access(end.first, start.second-3)==unoccupied);
				hits_townhall=(access(start.first, start.second+2)==blackTownhall)+(access(start.first, start.second+3)==blackTownhall)+(access(end.first, start.second-2)==blackTownhall)+(access(end.first, start.second-3)==blackTownhall);
				hits_black=(access(start.first, start.second+2)==blackSoldier)+(access(start.first, start.second+3)==blackSoldier)+(access(end.first, start.second-2)==blackSoldier)+(access(end.first, start.second-3)==blackSoldier);
			}

			else if((start.first==end.first+2)&&(start.second==end.second+2)){
				hits_unoccupied=(access(start.first+2, start.second+2)==unoccupied)+(access(start.first+3, start.second+3 )==unoccupied)+(access(end.first-2, end.second-2)==unoccupied)+(access(end.first-3, start.second-3)==unoccupied);
				hits_townhall=(access(start.first+2, start.second+2)==blackTownhall)+(access(start.first+3, start.second+3)==blackTownhall)+(access(end.first-2, end.second-2)==blackTownhall)+(access(end.first-3, start.second-3)==blackTownhall);
				hits_black=(access(start.first+2, start.second+2)==blackSoldier)+(access(start.first+3, start.second+3)==blackSoldier)+(access(end.first-2, end.second-2)==blackSoldier)+(access(end.first-3, start.second-3)==blackSoldier);
			}
			else if((start.first==end.first-2)&&(start.second==end.second+2)){
				hits_unoccupied=(access(start.first-2, start.second+2)==unoccupied)+(access(start.first-3, start.second+3)==unoccupied)+(access(end.first+2, end.second-2)==unoccupied)+(access(end.first+3, end.second-3)==unoccupied);
				hits_townhall=(access(start.first-2, start.second+2)==blackTownhall)+(access(start.first-3, start.second+3)==blackTownhall)+(access(end.first+2, end.second-2)==blackTownhall)+(access(end.first+3, end.second-3)==blackTownhall);
				hits_black=(access(start.first-2, start.second+2)==blackSoldier)+(access(start.first-3, start.second+3)==blackSoldier)+(access(end.first+2, end.second-2)==blackSoldier)+(access(end.first+3, end.second-3)==blackSoldier);
			}
			else if((start.first==end.first+2)&&(start.second==end.second-2)){
				hits_unoccupied=(access(start.first+2, start.second-2)==unoccupied)+(access(start.first+3, start.second-3 )==unoccupied)+(access(end.first-2, end.second+2)==unoccupied)+(access(end.first-3, start.second+3)==unoccupied);
				hits_townhall=(access(start.first+2, start.second-2)==blackTownhall)+(access(start.first+3, start.second-3)==blackTownhall)+(access(end.first-2, end.second+2)==blackTownhall)+(access(end.first-3, start.second+3)==blackTownhall);
				hits_black=(access(start.first+2, start.second-2)==blackSoldier)+(access(start.first+3, start.second-3)==blackSoldier)+(access(end.first-2, end.second+2)==blackSoldier)+(access(end.first-3, start.second+3)==blackSoldier);
			}
			else if((start.first==end.first-2)&&(start.second==end.second-2)){
				hits_unoccupied=(access(start.first-2, start.second-2)==unoccupied)+(access(start.first-3, start.second-3)==unoccupied)+(access(end.first+2, end.second+2)==unoccupied)+(access(end.first+3, end.second+3)==unoccupied);
				hits_townhall=(access(start.first-2, start.second-2)==blackTownhall)+(access(start.first-3, start.second-3)==blackTownhall)+(access(end.first+2, end.second+2)==blackTownhall)+(access(end.first+3, end.second+3)==blackTownhall);
				hits_black=(access(start.first-2, start.second-2)==blackSoldier)+(access(start.first-3, start.second-3)==blackSoldier)+(access(end.first+2, end.second+2)==blackSoldier)+(access(end.first+3, end.second+3)==blackSoldier);
			}


		}
		// int num_black=0;
		// for(int i=0;i<8;i++){
		// 	for(int j=0;j<8;++j){
		// 		if(board[i][j]==blackSoldier)
		// 			num_black++;

		// 	}
		// }
		// if(num_black==0)
		// 	return (soldiers*parameters[0])-((2-townhalls)*parameters[5])+(cannons*parameters[1])+(hits_unoccupied*parameters[2])+(hits_black*parameters[3])+(hits_townhall*parameters[4]) -parameters[6];
		// else
			return (soldiers*parameters[0])-((2-townhalls)*parameters[5])+(cannons*parameters[1])+(hits_unoccupied*parameters[2])+(hits_black*parameters[3])+(hits_townhall*parameters[4]);

	}
int CannonBoard::evaluate_black()
	{
		int soldiers=0, townhalls=0, cannons=0;
		for(int i=0;i<N;i++){
			for(int j=0;j<M;++j){
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
		int hits_unoccupied=0, hits_white=0, hits_townhall=0;
		vector<pair< pair<int,int>,pair<int,int> > > cannon_pos=getCannons_black();
		for(auto it: cannon_pos){
			pair<int, int> start=it.first;
			pair<int, int> end=it.second;
			if((start.first==end.first+2)&&(start.second==end.second)){
				hits_unoccupied=(access(start.first+2, start.second)==unoccupied)+(access(start.first+3, start.second )==unoccupied)+(access(end.first-2, start.second)==unoccupied)+(access(end.first-3, start.second)==unoccupied);
				hits_townhall=(access(start.first+2, start.second)==whiteTownhall)+(access(start.first+3, start.second)==whiteTownhall)+(access(end.first-2, start.second)==whiteTownhall)+(access(end.first-3, start.second)==whiteTownhall);
				hits_white=(access(start.first+2, start.second)==whiteSoldier)+(access(start.first+3, start.second)==whiteSoldier)+(access(end.first-2, start.second)==whiteSoldier)+(access(end.first-3, start.second)==whiteSoldier);
			}
			else if((start.first==end.first-2)&&(start.second==end.second)){
				hits_unoccupied=(access(start.first-2, start.second)==unoccupied)+(access(start.first-3, start.second)==unoccupied)+(access(end.first+2, start.second)==unoccupied)+(access(end.first+3, start.second)==unoccupied);
				hits_townhall=(access(start.first-2, start.second)==whiteTownhall)+(access(start.first-3, start.second)==whiteTownhall)+(access(end.first+2, start.second)==whiteTownhall)+(access(end.first+3, start.second)==whiteTownhall);
				hits_white=(access(start.first-2, start.second)==whiteSoldier)+(access(start.first-3, start.second)==whiteSoldier)+(access(end.first+2, start.second)==whiteSoldier)+(access(end.first+3, start.second)==whiteSoldier);
			}
			else if((start.first==end.first)&&(start.second==end.second-2)){
				hits_unoccupied=(access(start.first, start.second-2)==unoccupied)+(access(start.first, start.second-3)==unoccupied)+(access(end.first, start.second+2)==unoccupied)+(access(end.first, start.second+3)==unoccupied);
				hits_townhall=(access(start.first, start.second-2)==whiteTownhall)+(access(start.first, start.second-3)==whiteTownhall)+(access(end.first, start.second+2)==whiteTownhall)+(access(end.first, start.second+3)==whiteTownhall);
				hits_white=(access(start.first, start.second-2)==whiteSoldier)+(access(start.first, start.second-3)==whiteSoldier)+(access(end.first, start.second+2)==whiteSoldier)+(access(end.first, start.second+3)==whiteSoldier);
			}
			else if((start.first==end.first)&&(start.second==end.second+2)){
				hits_unoccupied=(access(start.first, start.second+2)==unoccupied)+(access(start.first, start.second+3)==unoccupied)+(access(end.first, start.second-2)==unoccupied)+(access(end.first, start.second-3)==unoccupied);
				hits_townhall=(access(start.first, start.second+2)==whiteTownhall)+(access(start.first, start.second+3)==whiteTownhall)+(access(end.first, start.second-2)==whiteTownhall)+(access(end.first, start.second-3)==whiteTownhall);
				hits_white=(access(start.first, start.second+2)==whiteSoldier)+(access(start.first, start.second+3)==whiteSoldier)+(access(end.first, start.second-2)==whiteSoldier)+(access(end.first, start.second-3)==whiteSoldier);
			}

			else if((start.first==end.first+2)&&(start.second==end.second+2)){
				hits_unoccupied=(access(start.first+2, start.second+2)==unoccupied)+(access(start.first+3, start.second+3 )==unoccupied)+(access(end.first-2, end.second-2)==unoccupied)+(access(end.first-3, start.second-3)==unoccupied);
				hits_townhall=(access(start.first+2, start.second+2)==whiteTownhall)+(access(start.first+3, start.second+3)==whiteTownhall)+(access(end.first-2, end.second-2)==whiteTownhall)+(access(end.first-3, start.second-3)==whiteTownhall);
				hits_white=(access(start.first+2, start.second+2)==whiteSoldier)+(access(start.first+3, start.second+3)==whiteSoldier)+(access(end.first-2, end.second-2)==whiteSoldier)+(access(end.first-3, start.second-3)==whiteSoldier);
			}
			else if((start.first==end.first-2)&&(start.second==end.second+2)){
				hits_unoccupied=(access(start.first-2, start.second+2)==unoccupied)+(access(start.first-3, start.second+3)==unoccupied)+(access(end.first+2, end.second-2)==unoccupied)+(access(end.first+3, end.second-3)==unoccupied);
				hits_townhall=(access(start.first-2, start.second+2)==whiteTownhall)+(access(start.first-3, start.second+3)==whiteTownhall)+(access(end.first+2, end.second-2)==whiteTownhall)+(access(end.first+3, end.second-3)==whiteTownhall);
				hits_white=(access(start.first-2, start.second+2)==whiteSoldier)+(access(start.first-3, start.second+3)==whiteSoldier)+(access(end.first+2, end.second-2)==whiteSoldier)+(access(end.first+3, end.second-3)==whiteSoldier);
			}
			else if((start.first==end.first+2)&&(start.second==end.second-2)){
				hits_unoccupied=(access(start.first+2, start.second-2)==unoccupied)+(access(start.first+3, start.second-3 )==unoccupied)+(access(end.first-2, end.second+2)==unoccupied)+(access(end.first-3, start.second+3)==unoccupied);
				hits_townhall=(access(start.first+2, start.second-2)==whiteTownhall)+(access(start.first+3, start.second-3)==whiteTownhall)+(access(end.first-2, end.second+2)==whiteTownhall)+(access(end.first-3, start.second+3)==whiteTownhall);
				hits_white=(access(start.first+2, start.second-2)==whiteSoldier)+(access(start.first+3, start.second-3)==whiteSoldier)+(access(end.first-2, end.second+2)==whiteSoldier)+(access(end.first-3, start.second+3)==whiteSoldier);
			}
			else if((start.first==end.first-2)&&(start.second==end.second-2)){
				hits_unoccupied=(access(start.first-2, start.second-2)==unoccupied)+(access(start.first-3, start.second-3)==unoccupied)+(access(end.first+2, end.second+2)==unoccupied)+(access(end.first+3, end.second+3)==unoccupied);
				hits_townhall=(access(start.first-2, start.second-2)==whiteTownhall)+(access(start.first-3, start.second-3)==whiteTownhall)+(access(end.first+2, end.second+2)==whiteTownhall)+(access(end.first+3, end.second+3)==whiteTownhall);
				hits_white=(access(start.first-2, start.second-2)==whiteSoldier)+(access(start.first-3, start.second-3)==whiteSoldier)+(access(end.first+2, end.second+2)==whiteSoldier)+(access(end.first+3, end.second+3)==whiteSoldier);
			}


		}
		// int num_white=0;
		// for(int i=0;i<8;i++){
		// 	for(int j=0;j<8;++j){
		// 		if(board[i][j]==blackSoldier)
		// 			num_white++;

		// 	}
		// }
//		if(num_white==0)
//			return (soldiers*parameters[0])-((2-townhalls)*parameters[5])+(cannons*parameters[1])+(hits_unoccupied*parameters[2])+(hits_white*parameters[3])+(hits_townhall*parameters[4])-parameters[6];
//		else
			return (soldiers*parameters[0])-((2-townhalls)*parameters[5])+(cannons*parameters[1])+(hits_unoccupied*parameters[2])+(hits_white*parameters[3])+(hits_townhall*parameters[4]);
		

	}
	/*int CannonBoard::evaluate(bool white)
	{
		int eval_white=0, eval_black=0;
		long time_spent=0.0;
		time_spent += (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - begintt)).count();
		if(true){
			if(map_state_white.find(*this)==map_state_white.end()){
				eval_white=evaluate_white();
				map_state_white[*this]=eval_white;
			}
			else{
				////fout<<"!"<<endl;
				eval_white=map_state_white[*this];
			}
			if(map_state_black.find(*this)==map_state_black.end()){
				eval_black=evaluate_black();
				map_state_black[*this]=eval_black;
			}
			else{
				////fout<<"!"<<endl;
				eval_black=map_state_black[*this];
			}
			if(white){
				return eval_white-eval_black;
			}
			else{
				return eval_black-eval_white;
			}
		}
		

		
	}*/
	int CannonBoard::evaluate(bool white)
	{
		if(white)
			return evaluate_white()-evaluate_black();
		else
			return evaluate_black()-evaluate_white();
	}

string transform_move(CannonBoard initial, CannonBoard final, bool white)
{
	string move="";
	CannonBoard temp1=initial;
	CannonBoard temp2=initial;
	bool samestate=false;
	if(white){
		for(int i=0;i<N;i++){
			for(int j=0;j<M;++j){
				//cout<<"at "<<i<<", "<<j<<endl;
				if(initial.getBoard()[i][j]!=whiteSoldier)
					continue;
				if(initial.getBoard()[i][j]==whiteSoldier)
				{
					////fout<<"printed at "<<i<<", "<<j<<endl;
					////fout<<initial.prints()<<" ";
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
						if(i-2>=0&&j+2<M){
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
							if(initial.access(i,j+5)==blackSoldier||initial.access(i,j+5)==blackTownhall)
								{
									temp1.shoot(make_pair(i, j+2),make_pair(i,j+5));
									if(temp1==final)
										return (string)"S "+to_string(i)+(string)" "+to_string(j+2)+ (string)" B "+to_string(i)+ (string)" "+to_string(j+5);
									temp1=temp2;
								}
							if(initial.access(i,j+4)==unoccupied||initial.access(i,j+5)==unoccupied)
							{
								if(temp1==final)
									return (string)"S "+to_string(i)+(string)" "+to_string(j+2)+ (string)" B "+to_string(i)+ (string)" "+to_string(j+4);
								
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
							if(initial.access(i,j-3)==blackSoldier||initial.access(i,j-3)==blackTownhall)
								{
									temp1.shoot(make_pair(i, j),make_pair(i,j-3));
									if(temp1==final)
										return (string)"S "+to_string(i)+(string)" "+to_string(j)+ (string)" B "+to_string(i)+ (string)" "+to_string(j-3);
									temp1=temp2;
								}
							if(initial.access(i,j-2)==unoccupied||initial.access(i,j-3)==unoccupied)
							{
								if(temp1==final)
									return (string)"S "+to_string(i)+(string)" "+to_string(j)+ (string)" B "+to_string(i)+ (string)" "+to_string(j-2);
								
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
							if(initial.access(i+5,j-5)==blackSoldier||initial.access(i+5,j-5)==blackTownhall)
								{
									temp1.shoot(make_pair(i+2, j-2),make_pair(i+5,j-5));
									if(temp1==final)
										return (string)"S "+to_string(i+2)+(string)" "+to_string(j-2)+ (string)" B "+to_string(i+5)+ (string)" "+to_string(j-5);
									temp1=temp2;
								}
							if(initial.access(i+4,j-4)==unoccupied||initial.access(i+5,j-5)==unoccupied)
							{
								if(temp1==final)
									return (string)"S "+to_string(i+2)+(string)" "+to_string(j-2)+ (string)" B "+to_string(i+4)+ (string)" "+to_string(j-4);
								
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
							if(initial.access(i-3,j+3)==blackSoldier||initial.access(i-3,j+3)==blackTownhall)
								{
									temp1.shoot(make_pair(i, j),make_pair(i-3,j+3));
									if(temp1==final)
									return (string)"S "+to_string(i)+(string)" "+to_string(j)+ (string)" B "+to_string(i-3)+ (string)" "+to_string(j+3);
									temp1=temp2;
								}
							if(initial.access(i-2,j+2)==unoccupied||initial.access(i-3,j+3)==unoccupied)
							{
								if(temp1==final)
									return (string)"S "+to_string(i)+(string)" "+to_string(j)+ (string)" B "+to_string(i-2)+ (string)" "+to_string(j+2);
								
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
								temp1.shoot(make_pair(i+2, j+2),make_pair(i+4,j+4));
								if(temp1==final)
									return (string)"S "+to_string(i+2)+(string)" "+to_string(j+2)+ (string)" B "+to_string(i+4)+ (string)" "+to_string(j+4);
								temp1=temp2;
							}
							if(initial.access(i+5,j+5)==blackSoldier||initial.access(i+5,j+5)==blackTownhall)
								{
									temp1.shoot(make_pair(i+2, j+2),make_pair(i+5,j+5));
									if(temp1==final)
										return (string)"S "+to_string(i+2)+(string)" "+to_string(j+2)+ (string)" B "+to_string(i+5)+ (string)" "+to_string(j+5);
									temp1=temp2;
								}
							if(initial.access(i+4,j+4)==unoccupied||initial.access(i+5,j+5)==unoccupied)
							{
								if(temp1==final)
									return (string)"S "+to_string(i+2)+(string)" "+to_string(j+2)+ (string)" B "+to_string(i+4)+ (string)" "+to_string(j+4);
								
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
							if(initial.access(i-3,j-3)==blackSoldier||initial.access(i-3,j-3)==blackTownhall)
								{
									temp1.shoot(make_pair(i, j),make_pair(i-3,j-3));
									if(temp1==final)
										return (string)"S "+to_string(i)+(string)" "+to_string(j)+ (string)" B "+to_string(i-3)+ (string)" "+to_string(j-3);
									temp1=temp2;
								}
							if(initial.access(i-2,j-2)==unoccupied||initial.access(i-3,j-3)==unoccupied)
							{
								if(temp1==final)
									return (string)"S "+to_string(i)+(string)" "+to_string(j)+ (string)" B "+to_string(i)+ (string)" "+to_string(j);
								
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
							if(initial.access(i+5,j)==blackSoldier||initial.access(i+5,j)==blackTownhall)
								{
									temp1.shoot(make_pair(i+2, j),make_pair(i+5,j));
									if(temp1==final)
										return (string)"S "+to_string(i+2)+(string)" "+to_string(j)+ (string)" B "+to_string(i+5)+ (string)" "+to_string(j);
									temp1=temp2;
								}
							if(initial.access(i+4,j)==unoccupied||initial.access(i+5,j)==unoccupied)
							{
								if(temp1==final)
									return (string)"S "+to_string(i+2)+(string)" "+to_string(j)+ (string)" B "+to_string(i+4)+ (string)" "+to_string(j);
								
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
							if(initial.access(i-3,j)==blackSoldier||initial.access(i-3,j)==blackTownhall)
								{
									temp1.shoot(make_pair(i, j),make_pair(i-3,j));
									if(temp1==final)
										return (string)"S "+to_string(i)+(string)" "+to_string(j)+ (string)" B "+to_string(i-3)+ (string)" "+to_string(j);
									temp1=temp2;
								}
							if(initial.access(i-2,j)==unoccupied||initial.access(i-3,j)==unoccupied)
							{
								if(temp1==final)
									return (string)"S "+to_string(i)+(string)" "+to_string(j)+ (string)" B "+to_string(i-2)+ (string)" "+to_string(j);
								
							}								
						}
					}
					//end cannon moves/shoots
				}
			}
		}

	}
	else{
		for(int i=0;i<N;i++){
			for(int j=0;j<M;++j){
				if(initial.getBoard()[i][j]==blackSoldier)
				{
					//cout<<"at i, j"<<i<<", "<<j<<endl;
					if(initial.access(i-1, j)==unoccupied||initial.access(i-1, j)==whiteSoldier||initial.access(i-1, j)==whiteTownhall){
						temp1.move(make_pair(i, j), make_pair(i-1, j));
						if(temp1==final)
							return (string)"S "+to_string(i)+(string)" "+to_string(j)+ (string)" M "+to_string(i-1)+ (string)" "+to_string(j);
						temp1=temp2;
					}
					if(initial.access(i-1, j+1)==unoccupied||initial.access(i-1, j+1)==whiteSoldier||initial.access(i-1, j+1)==whiteTownhall){
						temp1.move(make_pair(i, j), make_pair(i-1, j+1));
						if(temp1==final)
							return (string)"S "+to_string(i)+(string)" "+to_string(j)+ (string)" M "+to_string(i-1)+ (string)" "+to_string(j+1);
						temp1=temp2;
					}
					if(initial.access(i-1, j-1)==unoccupied||initial.access(i-1, j-1)==whiteSoldier||initial.access(i-1, j-1)==whiteTownhall){
						temp1.move(make_pair(i, j), make_pair(i-1, j-1));
						if(temp1==final)
							return (string)"S "+to_string(i)+(string)" "+to_string(j)+ (string)" M "+to_string(i-1)+ (string)" "+to_string(j-1);
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
					//cout<<"retreat"<<endl;
					if(initial.access(i-1, j)==whiteSoldier||initial.access(i-1, j+1)==whiteSoldier||initial.access(i-1, j-1)==whiteSoldier||initial.access(i, j+1)==whiteSoldier||initial.access(i, j-1)==whiteSoldier){
						if(i+2<N){
							temp1.move(make_pair(i, j), make_pair(i+2, j));
							if(temp1==final)
								return (string)"S "+to_string(i)+(string)" "+to_string(j)+ (string)" M "+to_string(i+2)+ (string)" "+to_string(j);
							temp1=temp2;
						}
						if(i+2<N&&j-2>=0){
							temp1.move(make_pair(i, j), make_pair(i+2, j-2));
							if(temp1==final)
								return (string)"S "+to_string(i)+(string)" "+to_string(j)+ (string)" M "+to_string(i+2)+ (string)" "+to_string(j-2);
							temp1=temp2;
						}
						if(i+2<N&&j+2<M){
							temp1.move(make_pair(i, j), make_pair(i+2, j+2));
							if(temp1==final)
								return (string)"S "+to_string(i)+(string)" "+to_string(j)+ (string)" M "+to_string(i+2)+ (string)" "+to_string(j+2);
							temp1=temp2;
						}
					}
					//cannon
					//cout<<"cannon"<<endl;
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
							if(initial.access(i,j+5)==whiteSoldier||initial.access(i,j+5)==whiteTownhall)
								{
									temp1.shoot(make_pair(i, j+2),make_pair(i,j+5));
									if(temp1==final)
										return (string)"S "+to_string(i)+(string)" "+to_string(j+2)+ (string)" B "+to_string(i)+ (string)" "+to_string(j+5);
									temp1=temp2;
								}
							if(initial.access(i,j+4)==unoccupied||initial.access(i,j+5)==unoccupied)
							{
								if(temp1==final)
									return (string)"S "+to_string(i)+(string)" "+to_string(j+2)+ (string)" B "+to_string(i)+ (string)" "+to_string(j+4);
								
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
							if(initial.access(i,j-3)==whiteSoldier||initial.access(i,j-3)==whiteTownhall)
								{
									temp1.shoot(make_pair(i, j),make_pair(i,j-3));
									if(temp1==final)
										return (string)"S "+to_string(i)+(string)" "+to_string(j)+ (string)" B "+to_string(i)+ (string)" "+to_string(j-3);
									temp1=temp2;
								}
							if(initial.access(i,j-2)==unoccupied||initial.access(i,j-3)==unoccupied)
							{
								if(temp1==final)
									return (string)"S "+to_string(i)+(string)" "+to_string(j)+ (string)" B "+to_string(i)+ (string)" "+to_string(j-2);
								
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
							if(initial.access(i+5,j-5)==whiteSoldier||initial.access(i+5,j-5)==whiteTownhall)
								{
									temp1.shoot(make_pair(i+2, j-2),make_pair(i+5,j-5));
									if(temp1==final)
										return (string)"S "+to_string(i+2)+(string)" "+to_string(j-2)+ (string)" B "+to_string(i+5)+ (string)" "+to_string(j-5);
									temp1=temp2;
								}
							if(initial.access(i+4,j-4)==unoccupied||initial.access(i+5,j-5)==unoccupied)
							{
								if(temp1==final)
									return (string)"S "+to_string(i+2)+(string)" "+to_string(j-2)+ (string)" B "+to_string(i+4)+ (string)" "+to_string(j-4);
								
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
							if(initial.access(i-3,j+3)==whiteSoldier||initial.access(i-3,j+3)==whiteTownhall)
								{
									temp1.shoot(make_pair(i, j),make_pair(i-3,j+3));
									if(temp1==final)
									return (string)"S "+to_string(i)+(string)" "+to_string(j)+ (string)" B "+to_string(i-3)+ (string)" "+to_string(j+3);
									temp1=temp2;
								}
							if(initial.access(i-2,j+2)==unoccupied||initial.access(i-3,j+3)==unoccupied)
							{
								if(temp1==final)
									return (string)"S "+to_string(i)+(string)" "+to_string(j)+ (string)" B "+to_string(i-2)+ (string)" "+to_string(j+2);
								
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
								temp1.shoot(make_pair(i+2, j+2),make_pair(i+4,j+4));
								if(temp1==final)
									return (string)"S "+to_string(i+2)+(string)" "+to_string(j+2)+ (string)" B "+to_string(i+4)+ (string)" "+to_string(j+4);
								temp1=temp2;
							}
							if(initial.access(i+5,j+5)==whiteSoldier||initial.access(i+5,j+5)==whiteTownhall)
								{
									temp1.shoot(make_pair(i+2, j+2),make_pair(i+5,j+5));
									if(temp1==final)
									return (string)"S "+to_string(i+2)+(string)" "+to_string(j+2)+ (string)" B "+to_string(i+5)+ (string)" "+to_string(j+5);
									temp1=temp2;
								}
							if(initial.access(i+4,j+4)==unoccupied||initial.access(i+5,j+5)==unoccupied)
							{
								if(temp1==final)
									return (string)"S "+to_string(i+2)+(string)" "+to_string(j+2)+ (string)" B "+to_string(i+4)+ (string)" "+to_string(j+4);
								
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
							if(initial.access(i-3,j-3)==whiteSoldier||initial.access(i-3,j-3)==whiteTownhall)
								{
									temp1.shoot(make_pair(i, j),make_pair(i-3,j-3));
									if(temp1==final)
										return (string)"S "+to_string(i)+(string)" "+to_string(j)+ (string)" B "+to_string(i-3)+ (string)" "+to_string(j-3);
									temp1=temp2;
								}
							if(initial.access(i-2,j-2)==unoccupied||initial.access(i-3,j-3)==unoccupied)
							{
								if(temp1==final)
									return (string)"S "+to_string(i)+(string)" "+to_string(j)+ (string)" B "+to_string(i-2)+ (string)" "+to_string(j-2);
								
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
							if(initial.access(i+5,j)==whiteSoldier||initial.access(i+5,j)==whiteTownhall)
								{
									temp1.shoot(make_pair(i+2, j),make_pair(i+5,j));
									if(temp1==final)
										return (string)"S "+to_string(i+2)+(string)" "+to_string(j)+ (string)" B "+to_string(i+5)+ (string)" "+to_string(j);
									temp1=temp2;
								}
							if(initial.access(i+4,j)==unoccupied||initial.access(i+5,j)==unoccupied)
							{
								if(temp1==final)
									return (string)"S "+to_string(i+2)+(string)" "+to_string(j)+ (string)" B "+to_string(i+4)+ (string)" "+to_string(j);
								
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
							if(initial.access(i-3,j)==whiteSoldier||initial.access(i-3,j)==whiteTownhall)
								{
									temp1.shoot(make_pair(i, j),make_pair(i-3,j));
									if(temp1==final)
										return (string)"S "+to_string(i)+(string)" "+to_string(j)+ (string)" B "+to_string(i-3)+ (string)" "+to_string(j);
									temp1=temp2;
								}
							if(initial.access(i-2,j)==unoccupied||initial.access(i-3,j)==unoccupied)
							{
								if(temp1==final)
									return (string)"S "+to_string(i)+(string)" "+to_string(j)+ (string)" B "+to_string(i-2)+ (string)" "+to_string(j);
								
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
bool flagcomp=false;
bool compareState(pair<CannonBoard, move_type> p1, pair<CannonBoard, move_type> p2)
{
	return p1.first.evaluate(flagcomp)>p2.first.evaluate(flagcomp);
}

string select_move(CannonBoard present,  int depth, bool white, bool who)
{

	vector<CannonBoard> successors = present.possibleStates(who);
	CannonBoard best_child;
	int alpha=INT_MIN, beta=INT_MAX;
	int max=INT_MIN;
	//cout<<"Num of successors is"<<successors.size()<<endl;
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
		alpha=max>alpha?max:alpha;
	}
	//cout<<"initial board is"<<endl;
	//present.print();
	//cout<<"final board is"<<endl;
	//best_child.print();
	//CannonBoard best_child= max_value_action(present, depth, white, INT_MIN, INT_MAX);
	//cout<<"finally chosen max evaluation is "<<max<<endl;
	//best_child.print();
	string toRet= transform_move(present, best_child, white);
	//cout<<"Move found is"<<toRet<<endl;
	return toRet;

}

int max_value_action(CannonBoard present, int depth, bool white, int alpha, int beta, bool who)
{
	//cout<<"max value action before possibleStates with depth "<<depth<<endl;
	vector<CannonBoard> successors = present.possibleStates(who);
	//cout<<"min value action after possibleStates with depth "<<depth<<endl;
	int max=INT_MIN;
	CannonBoard best_child;
	if(depth==0)
		return present.evaluate(white);
	if(successors.size()==0)
		return 0;
	int i=0;
	for(auto it=successors.begin();it!=successors.end();it++){
		if(successors.size()>15)
		{
			i++;
			if(i>15)
				break;
		}
		int minVal;
		if(depth==1){
			//cout<<"went all the way max, value given is"<<it->evaluate(white)<<endl;
			minVal=it->evaluate(white);//changed
		}
		else{
			minVal=min_value_action(*it, depth-1, white, alpha, beta, !who);
		}
		//cout<<"minval we got in maximiser at depth "<<4-depth<<" was "<<minVal<<endl;
		
		if(minVal>max){
			max=minVal;
			//best_child=*it;
		}
		
		alpha=max>alpha?max:alpha;
		if (alpha>=beta){
			//fout<<"pruned max at depth "<<depth<<"with value "<<alpha<<" and "<<beta<<endl;
			break;

		} 
		


	}
	//cout<<"actual best max evaluation chosen is from depth "<<depth<<" is "<<best_child.evaluate_white()<<" and "<<best_child.evaluate_black()<<endl;
	//best_child.print();
	return max;
}
int min_value_action(CannonBoard present, int depth, bool white, int alpha, int beta, bool who)
{
	//cout<<"min value action before possibleStates with depth "<<depth<<endl;
	vector<CannonBoard> successors = present.possibleStates(who);
	fout<<successors.size()<<" "<<depth<<endl;
	int min=INT_MAX;
	CannonBoard best_child;
	if(depth==0)
		return present.evaluate(white);
	if(successors.size()==0)
		return 0;
	int i=0;
	for(auto it=successors.begin();it!=successors.end();it++){
		if(successors.size()>15)
		{
			i++;
			if(i>15)
				break;
		}

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
		if(maxVal<min){
			min=maxVal;
			//best_child=*it;
		}
		//cout<<"~~~~~~~~maxval we got in minimiser at depth "<<4-depth<<" was "<<maxVal<<endl;
		beta=min<beta?min:beta;
		
		if (alpha>=beta){
			//fout<<"pruned min at depth "<<depth<<"with value "<<alpha<<" and "<<beta<<endl;
			break;

		} 
	}	
	return min;
}
void oneMove(string command, CannonBoard &board)
{
	if(command.length()<11)
			return ;
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
	string command1="";
	string command="";

	CannonBoard ourBoard;

	getline (cin, command1); 
	vector<string> S3=split(command1," ");
	bool white;
	if(S3[0]=="1")
		white=false;
	else
		white=true;
	int num_moves=0;
	long time_spent =0.0;
	
	if(white){
		while(true){
			

			getline (cin, command1); 
			vector<string> S1=split(command1," ");
			command=S1[0]+(string)" "+S1[2]+(string)" "+S1[1]+(string)" "+S1[3]+(string)" "+S1[5]+(string)" "+S1[4];
			oneMove(command, ourBoard);
			begint = std::chrono::system_clock::now();
			// int soldiers=0;
			// for(int i=0;i<8;i++){
			// 	for(int j=0;j<8;++j){
			// 		if(ourBoard.getBoard()[i][j]==blackSoldier)
			// 			soldiers++;
			// 	}
			// }
			string AImove;
			// if(num_moves==0)
			// 	AImove=select_move(ourBoard, 5, true, true);
			// else if(num_moves<2)
			//  	AImove=select_move(ourBoard, 3, true, true);
			// else 
			if(num_moves==0)
				AImove="S 0 3 M 3 3";
				//AImove=select_move(ourBoard, 6, true, true);
			else if(num_moves<=3)
				AImove=select_move(ourBoard, 4, true, true);
			 else if(time_spent>=80000)
			 	AImove=select_move(ourBoard, 2, true, true);
			else if(time_spent>=60000){
				AImove=select_move(ourBoard, 4, true, true);
				////fout<<time_spent<<" 1"<<endl;
			}
			// else if (soldiers<3){
			// 	AImove=select_move(ourBoard, 5, true, true);
			// }
			else {
			 	AImove=select_move(ourBoard, 6, true, true);
			 	////fout<<time_spent<<" 2"<<endl;
			 }
			 vector<string> S=split(AImove," ");
			 cout<<S[0]<<" "<<S[2]<<" "<<S[1]<<" "<<S[3]<<" "<<S[5]<<" "<<S[4]<<endl;
			 fout<<"After AI the move "<<S[0]<<" "<<S[2]<<" "<<S[1]<<" "<<S[3]<<" "<<S[5]<<" "<<S[4]<<endl;
			 oneMove(AImove, ourBoard);
			 num_moves++;
			 time_spent += (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - begint)).count();
		}
	}	
	else

	{
		while(true){
			
			int soldiers=0;
			begint = std::chrono::system_clock::now();
			// for(int i=0;i<8;i++){
			// 	for(int j=0;j<8;++j){
			// 		if(ourBoard.getBoard()[i][j]==blackSoldier)
			// 			soldiers++;
			// 	}
			// }
			string AImove;
			if(num_moves==0)
				AImove="S 7 0 M 4 0";	//AImove="S 9 0 M 6 0"; for 10*8 
				//AImove=select_move(ourBoard, 6, false, false);	
			else if(num_moves<=3)
			 	AImove=select_move(ourBoard, 4, false, false);
			// else if(time_spent>=85000)
			//  	AImove=select_move(ourBoard, 1, false, false);
			 else if(time_spent>=80000)
			 	AImove=select_move(ourBoard, 2, false, false);
			else if(time_spent>=60000){
				AImove=select_move(ourBoard, 4, false, false);
				////fout<<time_spent<<" 1"<<endl;
			}
			// else if (soldiers<3){
			// 	AImove=select_move(ourBoard, 5, true, true);
			// }
			else{
			 	AImove=select_move(ourBoard, 6, false, false);
			 	////fout<<time_spent<<" 2"<<endl;
			}

			vector<string> S=split(AImove," ");
			 
			cout<<S[0]<<" "<<S[2]<<" "<<S[1]<<" "<<S[3]<<" "<<S[5]<<" "<<S[4]<<endl;
			fout<<"After AI the move "<<S[0]<<" "<<S[2]<<" "<<S[1]<<" "<<S[3]<<" "<<S[5]<<" "<<S[4]<<endl;
			//cout<<"After AI the move "<<S[0]<<" "<<S[2]<<" "<<S[1]<<" "<<S[3]<<" "<<S[5]<<" "<<S[4];
			oneMove(AImove, ourBoard);
			////fout<<ourBoard.prints();
			time_spent += (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - begint)).count();
			getline (cin, command1); 
			////fout<<"After user the move "<<command1<<" state is "<<endl;
			vector<string> S1=split(command1," ");
			command=S1[0]+(string)" "+S1[2]+(string)" "+S1[1]+(string)" "+S1[3]+(string)" "+S1[5]+(string)" "+S1[4];
			oneMove(command, ourBoard);
			num_moves++;
			

		}
	}	
	return 0;
}
