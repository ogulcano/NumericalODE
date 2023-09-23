#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>
using namespace std;
double f(double x,float p1,float p2){
    return (p1/6.0)*pow(x,3)-(p2/12.0)*pow(x,4)+(9.0*p2/4 - 3*p1/2)*x;
}
int main(){
    ofstream myfile;
    myfile.open("ODESolver.txt");
    int N = 20;
    float p1 = (15.0/4)*pow(10,-4),p2 = (5.0/4)*pow(10,-4);
    double M[N+1][N+1], b[N+1];
    float LW = 0, UL = 3;
    float h = (UL-LW)/float(N);
    float bV1 = 0, bV2 = 0;
    // Zero-valued matrix/vector initilization
    for(int i=0; i<N+1;i++){
        for(int j=0; j<N+1;j++){
            M[i][j] = 0;
        }
        b[i] = 0;
    }

    // Inserting values
    for(int i=0; i<N+1;i++){
        for(int j=0; j<N+1;j++){
            if ((i==0 && j==0) || (i == N && j==N)){
                M[i][j] = 1;
            }
            else{
                if(i>0 && i<N && (i == j)){
                    M[i][i] = -2;
                    M[i][i-1] = 1;
                    M[i][i+1] = 1;
                }
            }
        }
        if (i == 0){
            b[i] = bV1;
        } else{
            if (i == N){
                b[i] = bV2;
            }else{
                b[i] = p1*pow(h,2)*(LW+i*h)-p2*pow(h,2)*pow(LW+i*h,2);
            }
        }
    }
// Equation Solver
    float x0[N], x1[N];
    for (int i=0 ; i<N ; i++){
        x0[i] = 0, x1[i] = 0;
    }
    int iteration = 0;
    float w = 0.93;
    while (iteration < 10000){
        for (int i = 0; i<N+1;i++){
            float k1 = 0, k2 = 0;
            for(int j = 0; j<i; j++){
                k1 += M[i][j]*x1[j];
            }
            for(int j = i+1; j<N+1; j++){
                k1 += M[i][j]*x0[j];
            }
            x1[i] = (w/M[i][i])*(b[i] - k1 - k2) + (1-w)*x0[i];
            x0[i] = x1[i];
        }
        iteration +=1;
    }
    for (int i=0; i<N+1;i++){
        for (int j=0; j<N+1;j++){
            cout<<M[i][j]<<" ";
        }
        cout<<endl;
    }
    for (int i=0; i<N+1;i++){
        cout<<b[i]<<endl;
    }
    for (int i=0; i<N+1;i++){
        cout<<LW+i*h<<" \t"<<x0[i]<<" \t"<<f(LW+i*h,p1,p2)<<endl;
        myfile<<LW+i*h<<" "<<x0[i]<<" "<<f(LW+i*h,p1,p2)<<endl;
    }
    return 0;
}