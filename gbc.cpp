#include <iostream>
#include <bits/stdc++.h>

#define SVART 1
#define VIT 2

using std::cin;
using std::cout;
using std::pair;
using std::vector;
using std::queue;
using std::endl;


void
read_data(int* n, int* k, int* l)
{
    cout << "Type your n, k and l: ";
    cin >> *n >> *k >> *l;
    //cout << "your n is: " << *n << "\n your k is: " << *k << "\n your l is: " << *l;
    cout.flush();
}

void
print_matrix(int **M, int *n){
  for(int i = 0; i < *n; i++){
    for(int j = 0; j < *n; j++){
        if (M[i][j] == SVART){
          cout << "s  ";
        }
        else if (M[i][j] == VIT){
          cout << "v  ";
        }
        else {
          cout << M[i][j] << "  ";
        }

    }
    cout << "\n";
  }
  cout << "\n";
  cout.flush();
}

int
opposite_color(int color){
  if (color == SVART)
    return VIT;
  return SVART;
}

void
BFS(int **M, vector<vector<vector< pair<int, int> >>> &adj_list,int *n)
{
  for (int i = 0; i<*n; i++){
    for(int j = 0; j<*n; j++){
      if(M[i][j] == 0){
        M[i][j] = SVART;
        queue<pair<int,pair<int,int>>> queue;
        queue.push({i,{j,SVART}});
        while(!queue.empty()){
          int x = queue.front().first;
          int y = queue.front().second.first;
          int color = queue.front().second.second;
          queue.pop();
          for(int u = 0; u < adj_list[x][y].size(); u++){
            int a,b;
            a = adj_list[x][y][u].first;
            b = adj_list[x][y][u].second;
            if (M[a][b] == 0){
              int opCol = opposite_color(color);
              M[a][b] = opCol;
              queue.push({a,{b,opCol}});
            }
          }
        }
      }
    }
  }
}


void
board_coloring(int **M, int *n, int* k, int* l)
{
  if (*k > *n/2 or *l > *n/2){
    cout << "Too small n";
    cout.flush();
    return;
  }
  vector<vector<vector< pair<int, int> >>> adj_list;
  for(int x=0;x<*n;x++){
   vector<vector<pair<int, int>>> v2d;
   for(int y=0;y<*n;y++)
   {
     vector<pair<int, int>> v1d;
      int added = 0;
       if (x + *k>=0 && x + *k <= *n-1 && y + *l >= 0 && y + *l <= *n-1){
         v1d.push_back({x+*k,y+*l});
         added++;
       }
       if (x + *k>=0 && x + *k <= *n-1 && y - *l >= 0 && y - *l <= *n-1){
         v1d.push_back({x+*k,y-*l});
         added++;
       }
       if (x - *k>=0 && x - *k <= *n-1 && y + *l >= 0 && y + *l <= *n-1){
         v1d.push_back({x-*k,y+*l});
         added++;
       }
       if (x - *k>=0 && x - *k <= *n-1 && y - *l >= 0 && y - *l <= *n-1){
         v1d.push_back({x-*k,y-*l});
         added++;
       }

       if (x + *l>=0 && x + *l <= *n-1 && y + *k >= 0 && y + *k <= *n-1){
         v1d.push_back({x+*l,y+*k});
         added++;
       }
       if (x + *l>=0 && x + *l <= *n-1 && y - *k >= 0 && y - *k <= *n-1){
         v1d.push_back({x+*l,y-*k});
         added++;
       }
       if (x - *l>=0 && x - *l <= *n-1 && y + *k >= 0 && y + *k <= *n-1){
         v1d.push_back({x-*l,y+*k});
         added++;
       }
       if (x - *l>=0 && x - *l <= *n-1 && y - *k >= 0 && y - *k <= *n-1){
         v1d.push_back({x-*l,y-*l});
         added++;
       }

     if (added == 0){
       cout << "M["<<x<<"]["<<y<<"] "<< " has no possible moves";
       cout.flush();
       return;
     }
     v2d.push_back(v1d);


   }
   adj_list.push_back(v2d);
 }
  ///* PRINT ADJ_list
cout << "POSSIBLE MOVES FROM: \n";
 for(int i=0;i<*n;i++)
  {
    for(int j=0;j<*n;j++)
    {
      cout<<"M["<<i<<"]["<<j<<"] ::: ";
      for(int z=0;z<adj_list[i][j].size();z++)
      {
        cout<<" -> ("<<adj_list[i][j][z].first<<", "<<adj_list[i][j][z].second << ")";
      }
      cout<<endl;
    }
    cout<<endl;
  }
  //*/
  BFS(M, adj_list, n);
  for (int i = 0; i<*n; i++){
    for(int j = 0; j<*n; j++){
      int opCol = opposite_color(M[i][j]);
      for(int u = 0; u < adj_list[i][j].size(); u++){
        int a,b;
        a = adj_list[i][j][u].first;
        b = adj_list[i][j][u].second;
        if (M[a][b] != opCol){
          cout << "ERROR: M["<<i<<"]["<<j<<"] wants " << opCol << " but has " << M[a][b] << " at M["<<a<<"]["<<b<<"]\n";
          cout.flush();
          return;
        }
      }
    }
  }
}



int
main(void)
{
  int n,k,l;
  read_data(&n,&k,&l);
  int **M;
  M = new int *[n];
  for(int i = 0; i <n; i++)
    M[i] = new int[n];

  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
        M[i][j]=0;
    }
  }

  board_coloring(M, &n,&k,&l);

  print_matrix(M,&n);



  return 0;
}
