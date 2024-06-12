#include <iostream>
#include <bits/stdc++.h>
using namespace std;
bool isPossible(int value,int sudoku[][9],int row,int col){
    //row check
    for(int i=0;i<9;i++){
        if(sudoku[row][i]==value) return false;
    }
    
    //col check
    for(int i=0;i<9;i++){
        if(sudoku[i][col]==value) return false;
    }
    
    //3*3 box chewxk
    for(int i=0;i<9;i++){
        if(sudoku[3*(row/3) + (i/3)][3*(col/3)+(i%3)]==value) return false;
    }
    return true;
}
bool solve(int sudoku[][9],int n){
    
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            
            if(sudoku[i][j]==0){
               for(int value=1;value<=9;value++){
                   
                   if(isPossible(value,sudoku,i,j)){
                       sudoku[i][j]=value;
                       
                       bool sol = solve(sudoku,n);
                       if(sol==true) return true;
                       else{
                           sudoku[i][j]=0;
                       }
                   }
               }
               return false;
               
            }
        }
    }
    return true;
}
int main()
{
    int sudoku[9][9]={
        {4,5,0,0,0,0,0,0,0},
        {0,0,2,0,7,0,6,3,0},
        {0,0,0,0,0,0,0,2,8},
        {0,0,0,9,5,0,0,0,0},
        {0,8,6,0,0,0,2,0,0},
        {0,2,0,6,0,0,7,5,0},
        {0,0,0,0,0,0,4,7,6},
        {0,7,0,0,4,5,0,0,0},
        {0,0,8,0,0,9,0,0,0}
    };
    int n=9;
    solve(sudoku,n);
    
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            cout<<sudoku[i][j]<<" ";
        }
        cout<<endl;
    }

    return 0;
}
