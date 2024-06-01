#include<iostream>
#include <bits/stdc++.h> 
#include <fstream>
using namespace std; 

int main() {
    
    ofstream file; 
    file.open("puzzle4.smt2");

    //variables generation
    for(int i=1; i<=9; i++) {
        for(int j=1; j<=9; j++) {
            for(int n=1; n<=9; n++) {
                file<<"(declare-const P_" << i << "_" << j << "_" << n << " Bool)\n";
            }
        }
    }

    //partially filled cells
    file << "(assert P_1_1_8)\n" <<
            "(assert P_1_8_9)\n" <<
            "(assert P_2_7_6)\n" <<
            "(assert P_2_8_7)\n" <<
            "(assert P_3_3_3)\n" <<
            "(assert P_3_4_5)\n" <<
            "(assert P_3_5_8)\n" <<
            "(assert P_3_9_1)\n" <<
            "(assert P_4_4_8)\n" <<
            "(assert P_5_2_5)\n" <<
            "(assert P_5_5_4)\n" <<
            "(assert P_5_8_6)\n" <<
            "(assert P_5_9_3)\n" <<
            "(assert P_6_5_2)\n" <<
            "(assert P_6_9_9)\n" <<
            "(assert P_7_1_9)\n" <<
            "(assert P_7_2_4)\n" <<
            "(assert P_7_6_7)\n" <<
            "(assert P_8_1_2)\n" <<
            "(assert P_9_4_1)\n" <<
            "(assert P_9_6_3)\n";


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