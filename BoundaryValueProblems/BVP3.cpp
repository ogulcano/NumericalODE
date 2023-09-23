#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>
using namespace std;
double f(double x){
    return (1.0/7)*pow(x,2)+(6.0/7)*pow(x,-1);
}
int main(){
    ofstream myfile;
    myfile.open("ODESolver.txt");
    int N = 10;
    double M[N+1][N+1], b[N+1];
    float h = 1/float(N);
    float bV1 = 1, bV2 = 1;
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
                    M[i][i] = -(2+ 2*pow(h,2)/pow(1+i*h,2));
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
                b[i] = 0;
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
        cout<<1+i*h<<" \t"<<x0[i]<<" \t"<<f(1+i*h)<<endl;
        myfile<<1+i*h<<" "<<x0[i]<<" "<<f(1+i*h)<<endl;
    }
    return 0;
}