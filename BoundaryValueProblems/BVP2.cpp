// Taken from https://pythonnumericalmethods.berkeley.edu/notebooks/chapter23.03-Finite-Difference-Method.html
#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <vector>
using namespace std;
float f(float t){
    return 34.5*t-0.5*9.8*pow(t,2);
}
int main(){
    ofstream myfile;
    myfile.open("ODESolver.txt");
    
    int N = 10;
    float h = 5/(float)N;
    vector<vector<float>> M(N+1,vector<float>(N+1));
    //float C[N+1];
    vector<float> C(N+1, 0);
// Matrix
    for (int i=0; i<N+1;i++){
        for(int j=0; j<N+1;j++){
            if (i==0){
                if (j == 0){
                    M[i][j] = 1;
                } else{
                    M[i][j] = 0;
                }
            }
            if (i == N){
                if (j == N){ // Boundary value
                    M[i][j] = 1;
                } else{
                    M[i][j] = 0;
                }
            }
            if (i>0 && i<N){
                if (i == j){
                    M[i][j] = -2;
                    M[i][j-1] = 1;
                    M[i][j+1] = 1;
                }
            }

        }
    }
// The right hand side vector
    for(int i=0; i<N+1;i++){
        if (i == 0){
            C[i] = 0; // Boundary value
        } else {
            if (i == N){
                C[i] = 50;
            } else {
                C[i] = -9.8*pow(h,2);
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
            x1[i] = (w/M[i][i])*(C[i] - k1 - k2) + (1-w)*x0[i];
            x0[i] = x1[i];
        }
        iteration +=1;
    }

    for (int i=0; i<N+1;i++){
        for(int j=0; j<N+1;j++){
            cout<<M[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<"C"<<endl;
    for(int i=0; i<N+1;i++){
        cout<<i*h<<" "<<C[i]<<" "<<x0[i]<<" "<<f(i*h)<<endl;
        myfile<<i*h<<" "<<x0[i]<<" "<<f(i*h)<<endl;
    }

    myfile.close();
    return 0;
}