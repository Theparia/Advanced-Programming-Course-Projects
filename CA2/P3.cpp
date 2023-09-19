#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;
void find_way(vector <vector<int> > path,int row,int col,int m ,int n,int &max_sum,int sum,vector <vector<int> > &visited);
bool is_valid(vector <vector<int> > path,int row,int col,int m ,int n,vector <vector<int> > visited);
int find_max(vector <vector<int> > path,int m ,int n,int &max_sum,vector <vector<int> > &visited);
void initialize_matrix(vector<vector <int> > &visited,int m , int n,int value);

int main()
{
vector <vector<int> > path;
vector <vector<int> > visited;
int m,n,value;
int max_sum=0;
cin>>m>>n;
for(int row=0;row<m;row++)
{
    vector <int> temp;
    for (int col=0;col<n;col++)
    {
        cin>>value;
        temp.push_back(value);
    }
    path.push_back(temp);
}
cout<<find_max(path,m,n,max_sum,visited)<<endl;
}

bool is_valid(vector <vector<int> > path,int row,int col,int m ,int n,vector <vector<int> > visited)
{
    if (row >= 0 && row < n && col >= 0 && col < m && path[row][col] != 0 && visited[row][col]==0)
        return true;
        return false;
}

void find_way(vector <vector<int> > path,int row,int col,int m ,int n,int &max_sum,int sum,vector <vector<int> > &visited)
{
    vector <int> delta_row={1,-1,0,0};
    vector <int> delta_col={0,0,1,-1};
    visited[row][col]=1;
    for(int index=0;index<4;index++)
    {
        if(is_valid(path,row+delta_row[index],col+delta_col[index],m,n,visited))
        find_way(path,row+delta_row[index],col+delta_col[index],m,n,max_sum,sum+path[row+delta_row[index]][col+delta_col[index]],visited);
    }
    visited[row][col]=0;

    if(!is_valid(path,row+1,col,m,n,visited) && !is_valid(path,row-1,col,m,n,visited)&& !is_valid(path,row,col+1,m,n,visited) && !is_valid(path,row,col-1,m,n,visited))
    {
        max_sum=max(max_sum,sum);
        return;
    }
   
}
int find_max(vector <vector<int> > path,int m ,int n,int &max_sum,vector <vector <int> > &visited)
{
    for(int row=0;row<m;row++)
    {
        for(int col=0;col<n;col++)
        {
            initialize_matrix(visited,m,n,0);
            find_way(path,row,col,n,m,max_sum,0,visited);
        }
    }
    return max_sum;
}

void initialize_matrix(vector<vector <int> > &visited,int m , int n,int value)
{
    vector <int> temp;
    for(int row=0;row<m;row++)
    {
        for (int col=0;col<n;col++)
        {
            temp.push_back(value);
        }
        visited.push_back(temp);
    }
    return;
}