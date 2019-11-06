#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono> 
#include <map>
using namespace std;;
long bottleneck_size=30;
template <class T>
class hashmaps{
	unordered_map<pair<T, bool>, long> mainMap;
	vector< pair<T, bool> > lastUsed;
	void Add(T element, bool b, long eval)
	{
		if(mainMap.size()>=bottleneck_size){
			mainMap.erase(lastUsed[0]);
			lastUsed.erase(lastUsed.begin());
			mainMap.insert(make_pair(make_pair(element, b), eval));
			lastUsed.push_back(make_pair(make_pair(element, b), eval));
		}
		else{
			mainMap.insert(make_pair(make_pair(element, b), eval));
			lastUsed.push_back(make_pair(make_pair(element, b), eval));
		}
	}
	T findeval(T elem, bool b){
			if(mainMap.find(make_pair(elem, b))==mainMap.end())
				throw "NotFound";
			else
				mainMap.find(make_pair(elem, b));
	}
}