#include <string>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int n;

//Function to write grid wirh order of longest path traversed
template <typename T>
void write_grid(vector<string> &grid, vector<T> order){

  int len = order.size();
  for(int i=0;i<len;i++){
    int a=order[i][0];
    int b=order[i][1];
    int c=order[i][2];

    string temp = to_string(len-c);
    grid[a].replace(b,1,temp);
  }
}

//Dynamic program to find the length of longest path from a given entry point
template <typename T>
int longest_path(int i, int j,vector<string> grid, vector<T> arr,vector<T> visited, vector<T> &order){
    if(i<0 || i>=n || j< 0 || j>=n)
      return 0;

    visited[i][j] = 1;

    if(arr[i][j] != -1)
      return arr[i][j];


    int l = INT8_MIN, r = INT8_MIN, t = INT8_MIN, b = INT8_MIN;

    if(j < n-1 && (grid[i][j+1] == '.') && (visited[i][j+1] != 1))
      l = 1 + longest_path(i,j+1,grid,arr,visited,order);

    if(j > 0 && (grid[i][j-1] == '.') && (visited[i][j-1] != 1))
      r = 1 + longest_path(i,j-1,grid,arr,visited,order);

    if(i < n-1 && (grid[i+1][j] == '.') && (visited[i+1][j] != 1))
      b = 1 + longest_path(i+1,j,grid,arr,visited,order);

    if(i > 0 && (grid[i-1][j] == '.') && (visited[i-1][j] != 1))
      t = 1 + longest_path(i-1,j,grid,arr,visited,order);

    arr[i][j] = max(l, max(r, max(b, max(t,1))));

    vector<int> temp;
    temp.push_back(i);
    temp.push_back(j);
    temp.push_back(arr[i][j]);

    if(order.empty())
      order.push_back(temp);
    else if(order.back()[2] < arr[i][j])
      order.push_back(temp);

    return arr[i][j];
}

//Function to traverse all possible paths and find longest path
int longest(vector<string> &grid){
  int res = -1;

  vector<vector<int>> table(n,vector<int> (n,-1));
  vector<vector<int>> visited(n,vector<int> (n,-1));
  vector<vector<int>> order;
  vector<vector<vector<int>>> orderarr;

  for(int i=0; i < n; i++){
    if(grid[0][i] == '.'){
      order.clear();
      table[0][i] = longest_path(0,i,grid,table,visited,order);
      orderarr.push_back(order);
    }

    res = max(res, table[0][i]);
  }

  order=orderarr[0];
  for(int i=1;i<orderarr.size();i++){
    if(orderarr[i].size() > order.size())
      order=orderarr[i];
  }

  write_grid(grid,order);

  return res;
}

//Funtion to draw the grid
void draw_grid(vector<string> grid){

  for(int i=0;i<grid.size();i++){
    cout<<grid[i]<<endl;
  }
}

int main(){
  fstream file1;
  fstream file2;
  vector<string> layout;

  file1.open("inp1.txt",ios::in);
  file2.open("inp2.txt",ios::in);


  //Hard-coded for given tests (sorry)
  //Reading file1
  cout<<"\nTest 1:\ninput:\n";
  if(file1.is_open()){
    string temp;

    int i=0;
    while(getline(file1,temp)){
      layout.push_back(temp);
      cout<<layout[i]<<endl;
      i++;
    }
    file1.close();
  }

  //Finding largest path
  n = layout[0].size();
  cout<<"\noutput:\n";
  cout<<longest(layout)<<endl;
  draw_grid(layout);

  layout.clear();

  //Reading file2
  cout<<"\nTest 2:\ninput:\n";
  if(file2.is_open()){
    string temp;

    int i=0;
    while(getline(file2,temp)){
      layout.push_back(temp);
      cout<<layout[i]<<endl;
      i++;
    }
    file2.close();
  }

  //Finding largest path
  n = layout[0].size();
  cout<<"\noutput:\n";
  cout<<longest(layout)<<endl;
  draw_grid(layout);

}
