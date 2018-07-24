#include<iostream>
#include<string>
#include<map>
#include<vector>
#include<queue>
using namespace std;

class node;
struct pset;

std::string route; //Final route.
int p_length;		//Final length.

std::vector<std::string> cities; //All cities.
std::map<std::string, node*> city_map; //Stores references to every vertex.

//Could not be stored as static members of node. :(
std::map<std::string, int> visit;	//BFS utilty array for visited vertices. Stores minimum visit cost.
std::queue<pset> q;					//BFS execution queue.

struct pset		// A set of path parameters.
{
	node *source;
	std::string path;
	int len;
	
	pset() {}
	pset(node *s, std::string p, int l) : source(s), path(p), len(l) {}
};

class node
{
private:
	std::string city;
	vector<node*> e; //Connected edges.
	vector<int> w; //Weight of edges.

public:
	node() {}
	
	node(string n) : city(n) {}
	
	void connect(node *p, int d)
	{
		e.push_back(p);
		w.push_back(d);
		p->e.push_back(this);
		p->w.push_back(d);
	}
	
	void find_route(node *t)
	{
		//Setting up the data structures.
		for(auto i = cities.begin(); i != cities.end(); i++)
			visit[*i] = 9999;
		
		pset p_args(this, "", 0); //Path arguments to be queued for BFS.
		
		q.push(p_args);
		
		while(!q.empty())
		{
			node *n = q.front().source;
			int d = q.front().len;
			if(d < visit[n->city])
				n->BFS(t, q.front());
			q.pop();
		}
	}
	void BFS(node *target, pset args)
	{
		if(this == target)
		{
			args.path += city + std::string(".");
			p_length = args.len;
			route = args.path;
		}
		else
		{
			auto C = e.begin();
			auto D = w.begin();
			for(int i = 0; i < e.size(); i++)
				q.push(pset(*(C +i), args.path + city + std::string(" -> "), args.len + *(D + i)));
		}
		visit[city] = args.len;
	}
	
	//Testing tools...
	/*void debug()
	{
		cout << "\nCity: "<< city << ".\n";
		cout << "Connections:\n";
		auto i1 = e.begin();
		auto i2 = w.begin();
		for(int i = 0; i < e.size(); i++)
			cout << "\t" << (*(i1+i))->city << " (" << *(i2+i) << ")\n";
	}*/
};

int main()
{
	//Build Graph.
	cities = {"Mumbai", "Pune", "Hyderabad", "Bengaluru", "Chennai", "Ahmedabad", "Jaipur", "Delhi", "Nagpur", "Kolkata", "Chandigarh", "Jammu", "Kolhapur", "Panji", "Tiruvantpuram"};
	for(auto i = cities.begin(); i != cities.end(); i++)
	{
		node *p = new node(*i);
		city_map[*i] = p;
	} //Creating cities.
	
	//Connecting cities.
	city_map["Mumbai"]->connect(city_map["Pune"], 180);
	city_map["Mumbai"]->connect(city_map["Ahmedabad"], 520);
	city_map["Mumbai"]->connect(city_map["Nagpur"], 820);
	city_map["Mumbai"]->connect(city_map["Panji"], 545);
	
	city_map["Pune"]->connect(city_map["Hyderabad"], 520);
	city_map["Pune"]->connect(city_map["Kolhapur"], 230);
	city_map["Pune"]->connect(city_map["Nagpur"], 715);
	
	city_map["Kolhapur"]->connect(city_map["Bengaluru"], 615);
	city_map["Kolhapur"]->connect(city_map["Panji"], 200);
	
	city_map["Hyderabad"]->connect(city_map["Bengaluru"], 570);
	city_map["Hyderabad"]->connect(city_map["Chennai"], 630);
	city_map["Hyderabad"]->connect(city_map["Nagpur"], 500);
	
	city_map["Bengaluru"]->connect(city_map["Chennai"], 350);
	city_map["Bengaluru"]->connect(city_map["Tiruvantpuram"], 685);
	
	city_map["Panji"]->connect(city_map["Tiruvantpuram"], 980);
	
	
	city_map["Ahmedabad"]->connect(city_map["Nagpur"], 850);
	city_map["Ahmedabad"]->connect(city_map["Jaipur"], 675);
	city_map["Jaipur"]->connect(city_map["Delhi"], 280);
	
	city_map["Delhi"]->connect(city_map["Kolkata"], 1500);
	city_map["Delhi"]->connect(city_map["Nagpur"], 1080);
	city_map["Delhi"]->connect(city_map["Chandigarh"], 245);
	
	city_map["Kolkata"]->connect(city_map["Nagpur"], 1230);
	
	city_map["Chandigarh"]->connect(city_map["Jammu"], 340);
	
	//Menu.
	char choice = 'n';
	
	//For debugging purposes.
	/*for(auto i = cities.begin(); i != cities.end(); i++)
		city_map[*i]->debug();
	cin.ignore();
	*/
	
	while((choice != 'y') && (choice != 'Y'))
	{
		p_length = 9999;
		cout << "\n\t\tMAP-SEARCH USING BFS\n\nCities:\n";
		for(auto i = cities.begin(); i != cities.end(); i++)
			cout << "\t" << *i << endl;
		cout << "\nEnter source city: ";
		string s, d;
		while(s.empty()) 	//Dump garbage.
			getline(cin, s);
		cout << "Enter destination city: ";
		while(d.empty()) 	//Dump garbage.
			getline(cin, d);
		try
		{
			if((city_map[s] == NULL) || (city_map[d] == NULL))
			{
				std::string message = "Invalid city. Enter a city from among the list.\n\n";
				throw message;
			}
			cout << "\nSearching for the shortest path between " << s << " and " << d << "...\n\n";
			city_map[s]->find_route(city_map[d]); 		//BFS call.
			cout << "Shortest route:\t" << route << "\nDistance:\t" << p_length << " km.\n";
		}
		catch (std::string &e)
		{
			std::cout << e;
  		}
		cout << "\nDo you want to quit? (Enter 'Y' to quit): ";
		cin >> choice;
	}
}
