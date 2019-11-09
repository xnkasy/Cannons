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
vector<state> seedVec(8, unoccupied);
class CannonBoard
{
	vector< vector<state> > board;
	
	public:
	string sig="";
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
		sig=sprint();
	}

	 vector< vector<state> >  getBoard() const
	{
		return board;
	}
	CannonBoard(const CannonBoard &copyCannon): board(8, seedVec)
	{
		board=copyCannon.getBoard();
		sig=sprint();
	}
	state access(int i, int j) const
	{
		if(i<8&&j<8&&i>=0&&j>=0)
			return board[i][j];
		return null;
	}
	bool operator == (const CannonBoard &other) const
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
	string sprint() const
	{
		stringstream ss;
		for(int i=0;i<8;i++){
			for(int j=0;j<8;j++){
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
	
			for(int j=0;j<8;++j)
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
		sig[start.first*7+start.second]=char(unoccupied);
		sig[end.first*7+end.second]=char(dum);
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
int main(){

	map<CannonBoard, long> map_state_white;
	map<CannonBoard, long> map_state_black;
	CannonBoard X;
	CannonBoard M;
	map_state_white[X]=10; 
	std::hash<string> str_hash;
	//X.print();
	//M.print();
	cout<<"X= " <<map_state_white[X]<<"   "<<str_hash(X.sprint())<<endl;;
	cout<<"M= " <<map_state_white[M]<<"   "<<str_hash(M.sprint())<<endl;
	X.move(make_pair(1,1), make_pair(3,4));
	CannonBoard Y(X);
	map_state_white[Y]=100;
	cout<<"Y= " <<map_state_white[Y]<<"   "<<str_hash(Y.sprint())<<endl;;
	Y.move(make_pair(3,4), make_pair(7,7));
	CannonBoard Z(Y);
	map_state_white[Z]=90;
	cout<<"Z= " <<map_state_white[Z]<<"   "<<str_hash(Z.sprint())<<endl;;
	
	
	
	//X.print();
	//M.print();
	cout<<"X= " <<map_state_white[X]<<"   "<<str_hash(X.sprint())<<endl;;
	cout<<"M= " <<map_state_white[M]<<"   "<<str_hash(M.sprint())<<endl;
	M.move(make_pair(1,2), make_pair(3,4));
	CannonBoard N=M;
	cout<<"Y= " <<map_state_white[Y]<<"   "<<str_hash(Y.sprint())<<endl;;
	cout<<"N= " <<map_state_white[N]<<"   "<<str_hash(N.sprint())<<endl;
	N.move(make_pair(6,4), make_pair(2,4));
	CannonBoard O=N;
	cout<<"Z= " <<map_state_white[Z]<<"   "<<str_hash(Z.sprint())<<endl;;
	cout<<"O= " <<map_state_white[O]<<"   "<<str_hash(O.sprint())<<endl;
		
		
	return 0;

}
