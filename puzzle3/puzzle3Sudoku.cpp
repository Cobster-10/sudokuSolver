#include<iostream>
#include <bits/stdc++.h> 
#include <fstream>
using namespace std; 

int main() {
    
    ofstream file; 
    file.open("puzzle3.smt2");

    //variables generation
    for(int i=1; i<=9; i++) {
        for(int j=1; j<=9; j++) {
            for(int n=1; n<=9; n++) {
                file<<"(declare-const P_" << i << "_" << j << "_" << n << " Bool)\n";
            }
        }
    }

    //partially filled cells

    int Sboard[9][9] =   {2,0,1,0,0,0,0,4,0,
                          0,0,0,3,2,0,0,0,0,
                          0,0,0,0,5,0,0,7,6,
                          0,0,0,0,0,8,0,0,0,
                          4,5,0,0,0,7,0,0,0,
                          0,0,8,0,1,3,0,0,7,
                          0,0,0,0,0,0,8,0,5,
                          6,8,0,0,0,0,0,0,0,
                          0,0,3,6,0,0,0,0,1};
    cout << Sboard[0][0];

    for (int row =0; row <9; ++row){
        for(int col =0; col <9; ++col){
            if (Sboard[row][col]!=0){
                file << "(assert P_" << row +1 << "_" << col+1 << "_" << Sboard[row][col] << ")\n";
            }
        }
    }     
    


    //Row rules generation
    for(int i=1; i<=9; i++) {
        for(int n=1; n<=9; n++) {
            file<< "(assert (or";
            for(int j=1; j<=9; j++) {
                 file<< " " << "P_" << i << "_" << j <<"_" << n;
            }
            file<< "))\n";
        }
    }
    //Column rules generation
    for(int j=1; j<=9; j++) {
        for(int n=1; n<=9; n++) {
            file<<"(assert (or";
            for(int i=1; i<=9; i++) {
                file<< " " << "P_" << i << "_" << j <<"_" << n;
            }
            file<< "))\n";
        }
    }
    //Block rules generation
    for(int r=0; r<=2; r++) {
        for(int c=0; c<=2; c++) {
            for(int n=1; n<=9; n++) {
              file<<"(assert (or";
                for(int i=1; i<=3; i++) {
                    for(int j=1; j<=3; j++) {
                      file<<" " << "P_" << (3*r+i) << "_" << (3*c+j) <<"_" << n;
                    }
                }
                file<< "))\n"; 
            }
        }
    }
    //Cell rules generation
    for(int i=1; i<=9; i++) {
        for(int j=1; j<=9; j++) {
            for(int n=1; n<=9; n++) {
                file<<"(assert (or (not " << "P_" << i << "_" << j << "_" << n <<  ") (not (or";
                for(int n1=1; n1<=9; n1++) {
                    if(n==n1)
                        continue;
                    file<< " " << "P_" << i << "_" << j <<"_" << n1;
                }
                file<<"))))\n";
            }
        }
    }
    file<<"(check-sat)\n";
    file<<"(get-model)";
    file.close();
    return 0;
}