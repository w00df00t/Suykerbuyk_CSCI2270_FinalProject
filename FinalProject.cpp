#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

#ifndef GRAPH_H
#define GRAPH_H

template<class T>
struct vertex;

// Struct for adjacent city stores; includes pointers and distance in miles
template<class T>
struct adjVertex
{
    vertex<string> *v;
    int weight;
};
// Struct for movie data as contained in datafile
template<class T>
struct movieVertex
{
  int rank;
  string title;
  int year;
  int count;
};
// Struct for each city store, including store name, how many different movies
// it has, vector of adjacent stores, and vector of movies in inventory.
template<class T>
struct vertex
{
    string name;
    int movieCount;
    vector< adjVertex<string> > adj;
    vector< movieVertex<string> > mov;
};
// Class declaration
template<class T>
class Graph
{
    public:
        Graph();
        ~Graph();
        int size;
        string hometown;
        bool rent;
        void addEdge(string v1, string v2, int weight);
        void addVertex(string name);
        void displayEdges();
        void displayCities();
        void buildNetwork();
        void buildDB(string filename);
        void introMenu();
        void mainMenu();
        void printStore(string name);
        void printNetwork();
        void addMovie(string name, int rank,string title, int year, int count);
        void findMovie();
        void movieRent(string title, string name);
        void deleteCity(string name);
        int displayDistance(string name, string name2);
        bool findMovie(string title, string name);
        bool checkCity(string name);
    protected:
    private:
        vector<vertex<string> > vertices;

};

// Constructor
template<class T>
Graph<T>::Graph(){}
// Deconstructor
template<class T>
Graph<T>::~Graph(){}
// Function to add a graph edge between two city stores
template<class T>
void Graph<T>::addEdge(string v1, string v2, int weight)
{
  for(int i = 0; i < vertices.size(); i++)
  {
    if(vertices[i].name == v1)
    {
      for(int j = 0; j < vertices.size(); j++)
      {
        if(vertices[j].name == v2 && i != j)
        {
          adjVertex<string> av;
          av.v = &vertices[j];
          av.weight = weight;
          vertices[i].adj.push_back(av);
        }
      }
    }
  }
}
// Function to add a city store to the network
template<class T>
void Graph<T>::addVertex(string name)
{
  bool found = false;
  for(int i = 0; i < vertices.size(); i++)
  {
    if(vertices[i].name == name)
    {
      found = true;
      cout << name << endl;
      cout<<vertices[i].name<<" found."<<endl;
    }
  }
  if(found == false)
  {
    vertex<string> v;
    v.name = name;
    v.movieCount = 0;
    vertices.push_back(v);
  }
}
// Function to return the distance between two cities
template<class T>
int Graph<T>::displayDistance(string name, string name2)
{
  for(int i = 0; i < vertices.size(); i++)
  {
    if (vertices[i].name == name)
    {
      for(int j = 0; j < vertices[i].adj.size(); j++)
      {
        if (vertices[i].adj[j].v->name == name2)
        {
          return vertices[i].adj[j].weight;
        }
      }
    }
  }
  return 0;
}
// Function to display the name of the cities
template<class T>
void Graph<T>::displayCities()
{
  for(int i = 0; i < vertices.size(); i++)
  {
    cout << vertices[i].name << endl;
  }
}
// Function to check if a city is in the network
template<class T>
bool Graph<T>::checkCity(string name)
{
  for(int i = 0; i < vertices.size(); i++)
  {
    if (vertices[i].name == name)
    {
      return true;
    }
  }
  return false;
}
// Function to build the network
template<class T>
void Graph<T>::buildNetwork()
{
  addVertex("BOULDER");addVertex("COSPRINGS");addVertex("LONGMONT");
  addVertex("LOVELAND");addVertex("FOCO");addVertex("DENVER");
  addVertex("CASROCK");
  // Boulder edges:
  addEdge("BOULDER","COSPRINGS",97);
  addEdge("BOULDER","LONGMONT",16);
  addEdge("BOULDER","DENVER",30);
  addEdge("BOULDER","LOVELAND",33);
  addEdge("BOULDER","FOCO",46);
  addEdge("BOULDER","CASROCK",58);
  // Colorado Springs edges:
  addEdge("COSPRINGS","BOULDER",97);
  addEdge("COSPRINGS","LONGMONT",106);
  addEdge("COSPRINGS","LOVELAND",120);
  addEdge("COSPRINGS","FOCO",133);
  addEdge("COSPRINGS","DENVER",70);
  addEdge("COSPRINGS","CASROCK",41);
  // Longmont edges:
  addEdge("LONGMONT","BOULDER",16);
  addEdge("LONGMONT","COSPRINGS",106);
  addEdge("LONGMONT","LOVELAND",17);
  addEdge("LONGMONT","FOCO",30);
  addEdge("LONGMONT","DENVER",38);
  addEdge("LONGMONT","CASROCK",66);
  // Loveland edges:
  addEdge("LOVELAND","BOULDER",33);
  addEdge("LOVELAND","COSPRINGS",120);
  addEdge("LOVELAND","LONGMONT",17);
  addEdge("LOVELAND","FOCO",14);
  addEdge("LOVELAND","DENVER",52);
  addEdge("LOVELAND","CASROCK",80);
  // Fort Collins edges:
  addEdge("FOCO","BOULDER",46);
  addEdge("FOCO","COSPRINGS",133);
  addEdge("FOCO","LONGMONT",30);
  addEdge("FOCO","LOVELAND",14);
  addEdge("FOCO","DENVER",65);
  addEdge("FOCO","CASROCK",93);
  // Denver edges:
  addEdge("DENVER","BOULDER",30);
  addEdge("DENVER","COSPRINGS",70);
  addEdge("DENVER","LONGMONT",38);
  addEdge("DENVER","LOVELAND",52);
  addEdge("DENVER","FOCO",65);
  addEdge("DENVER","CASROCK",31);
  // Castle Rock edges:
  addEdge("CASROCK","BOULDER",58);
  addEdge("CASROCK","COSPRINGS",41);
  addEdge("CASROCK","LONGMONT",66);
  addEdge("CASROCK","LOVELAND",80);
  addEdge("CASROCK","FOCO",93);
  addEdge("CASROCK","DENVER",31);
}
// Function to build the database of movies loaded from datafile.txt
template<class T>
void Graph<T>::buildDB(string filename)
{
  size = 0;
  // First, take in the data from the file.
  string movie[200][5];
  string inputString;
  ifstream input;
  input.open(filename);
  // If the file name is wrong, call the user an idiot.
  if (!input.is_open())
  {
    cout << "Bad file name." << endl;
    exit(1);
  }
  // Take in all the data and save it to a 2D struct.
  while (!input.eof())
  {
    getline(input,inputString);
    stringstream ss(inputString);
    string data;
    int x = 0;
    while(getline(ss,data,','))
    {
      movie[size][x] = data;
      x++;
    }
    size++;
  }
  for (int i = 0;i<size-1;i++)
  {
    addMovie(movie[i][0],atoi(movie[i][1].c_str()),movie[i][2],
      atoi(movie[i][3].c_str()),atoi(movie[i][4].c_str()));
  }
}

template<class T>
void Graph<T>::addMovie(string name, int rank,string title, int year, int count)
{
  for(int i = 0; i < vertices.size(); i++)
  {
    if(vertices[i].name == name)
    {
      movieVertex<string> MV;
      MV.rank = rank;
      MV.title = title;
      MV.year = year;
      MV.count = count;
      vertices[i].movieCount++;
      vertices[i].mov.push_back(MV);
    }
  }
}
// Initial menu to show user the built city network, and take in user city
// before proceeding to main menu.
template<class T>
void Graph<T>::introMenu()
{
  cout << "Welcome to the online movie finder!" << endl;
  cout << "Available options listed below: " << endl;
  displayCities();
  cout << " * * * * * " << endl;
  cout << "Please enter your city to begin: " << endl;
  cin >> hometown;
  if (checkCity(hometown) == true)
  {
    cout << "City found. Welcome to the " << hometown << " store!" << endl;
    cout << "\n" << endl;
    mainMenu();
  }
  else
  {
    cout << "City not found, try again." << endl;
    cout << "\n" << endl;
    introMenu();
  }
}
// Function to print an entire store's current inventory of movies
template<class T>
void Graph<T>::printStore(string name)
{
  for (int i = 0; i<vertices.size();i++)
  {
    if (vertices[i].name == name)
    {
      cout << "\n" << endl;
      cout << "Store has " << vertices[i].movieCount << " movies." << endl;
      cout << "Printing store inventory by IMDB rank, title, " << endl;
      cout << "year of release, and number in stock.\n" << endl;
      for (int j = 0;j<vertices[i].movieCount;j++)
      {
        cout << vertices[i].mov[j].rank << ", ";
        cout << vertices[i].mov[j].title << ", ";
        cout << vertices[i].mov[j].year << ", ";
        cout << vertices[i].mov[j].count << endl;
      }
      cout << "\n" << endl;
    }
  }
}
// Function to display the entire existing network
template<class T>
void Graph<T>::printNetwork()
{
  for (int i = 0; i<vertices.size();i++)
  {
    cout << "Store: " << vertices[i].name << endl;
    cout << "\n * * * * *";
    printStore(vertices[i].name);
  }
}
// Function to search for a movie and see if it's available
template<class T>
bool Graph<T>::findMovie(string title,string name)
{
  for (int i = 0; i<vertices.size();i++)
  {
    if (vertices[i].name == name)
    {
      for (int j = 0;j<vertices[i].movieCount;j++)
      {
        if (vertices[i].mov[j].title == title)
        return true;
      }
    }
  }
  return false;
}
// Function to find a movie. If it's available at hometown store, give user the
// option to order it. If not, give user the option to search other stores to
// see if it's available there, and if found, tell user how far the store is,
// then provide the option to order it.
template<class T>
void Graph<T>::findMovie()
{
  string choice;
  string title;
  bool found = false;
  cout << "Please enter name of movie you wish to order: ";
  getline(cin,title);
  getline(cin,title);
  cout << "Searching " << hometown << " store..." << endl;
  if (findMovie(title,hometown) == true)
  {
    cout << "Movie found. Would you like to order it? Enter Y or N." << endl;
    cin >> choice;
    if (choice == "Y")
    {
      movieRent(title,hometown);
      cout << "Movie ordered!" << endl;
      cout << "Returning to main menu." << endl;
      cout << " * * * * * " << endl;
    }
    else
    {
      cout << "Returning to main menu." << endl;
      cout << " * * * * * " << endl;
    }
  }
  else
  {
    cout << "Movie not available at local store. Would you like to search\n";
    cout << "other stores in the area? Enter Y or N." << endl;
    cin >> choice;
    if (choice == "Y")
    {
      cout << "Checking nearby stores..." << endl;
      for (int k = 0;k<vertices.size();k++)
      {
        if (findMovie(title,vertices[k].name) == true)
        {
          found = true;
          int dist = displayDistance(hometown,vertices[k].name);
          cout << "Movie found at " << vertices[k].name << " store. This ";
          cout << "store is " << dist << " miles away.\n";
          cout << "Would you like to order it? Enter Y or N. If you enter\n";
          cout << "N, program will continue search through the rest of the\n";
          cout << "network for your request." << endl;
          cin >> choice;
          if (choice == "Y")
          {
            movieRent(title,vertices[k].name);
            cout << "Movie ordered!" << endl;
            cout << "Returning to main menu." << endl;
            cout << " * * * * * " << endl;
          }
          else
          {
            cout << " * * * * * " << endl;
            found = false;
          }
        }
      }
      if (found == false)
      {
        cout << "Movie not found... " << endl;
        cout << "Returning to main menu." << endl;
        cout << " * * * * * " << endl;
      }
    }
    else
    {
      cout << "Returning to main menu." << endl;
      cout << " * * * * * " << endl;
    }
  }
  mainMenu();
}
// Function to order a movie; if it's the last one, it deletes it from that
// store's inventory.
template<class T>
void Graph<T>::movieRent(string title, string name)
{
  for (int i = 0;i<vertices.size();i++)
  {
    if (vertices[i].name == name)
    {
      for (int j = 0;j<vertices[i].movieCount;j++)
      {
        if (vertices[i].mov[j].title == title)
        {
          vertices[i].mov[j].count--;
          if (vertices[i].mov[j].count == 0)
          {
            vertices[i].mov.erase(vertices[i].mov.begin()+j);
            vertices[i].movieCount--;
            if (vertices[i].movieCount == 0)
            deleteCity(vertices[i].name);
          }
        }
      }
    }
  }
}
// Function to delete a city from the network
template<class T>
void Graph<T>::deleteCity(string name)
{
  bool found = false;
  for (int i = 0;i<vertices.size();i++)
  {
    if (vertices[i].name == name)
    {
      cout << "Deleting city store " << name << endl;
      vertices.erase(vertices.begin()+i);
      found = true;
    }
  }
  if (found == false)
  {
    cout << "City not found, please try again." << endl;
  }
}
// Main menu
template<class T>
void Graph<T>::mainMenu()
{
  int selection;
  cout << "======Main Menu======" << endl;
  cout << "1. See my store's inventory" << endl;
  cout << "2. See network inventory" << endl;
  cout << "3. Order a movie" << endl;
  cout << "4. Delete a city store" << endl;
  cout << "5. Quit" << endl;
  cout << "=====================" << endl;
  cout << "Selection: ";
  cin >> selection;
  if (selection == 1)
  {
    printStore(hometown);
    mainMenu();
  }
  else if (selection == 2)
  {
    printNetwork();
    mainMenu();
  }
  else if (selection == 3)
  {
    findMovie();
  }
  else if (selection == 4)
  {
    cout << "Enter city store to delete: " << endl;
    string n;
    getline(cin,n);
    getline(cin,n);
    deleteCity(n);
    mainMenu();
  }
  else if (selection == 5)
  {
    cout << "Goodbye!" << endl;
    exit(1);
  }

  else
  {
    cout << "Command not recognized, try again." << endl;
    mainMenu();
  }
}

#endif // GRAPH_H
// Main function to initialize program
int main(int argc, char const *argv[])
{
    Graph<int> g;
    string filename = argv[1];
    g.buildNetwork();
    g.buildDB(filename);
    g.introMenu();
    return 0;
}
