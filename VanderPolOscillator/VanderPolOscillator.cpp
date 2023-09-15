#include <iostream>
#include <math.h>
#include <fstream>
#include <iomanip>
using namespace std;
const double PI = 4*atan(1);

float dudv(float v){
    return v;
}
float dvdt(float t,float u,float v){
    return 10*(1-pow(u,2))*v - u + sin(PI*t);
}
int main(){
    ofstream myfile;
    myfile.open ("ODESolver.txt");
    float h = 0.01, t0 = 0, u0 = 1, v0 = 5;
    while (t0 < 100){
        cout<<setprecision(6)<<" "<<t0<<" "<<u0<<" "<<v0<<endl;
        float k1 = dudv(v0);
        float k11 = dudv(v0+h*k1);
        float k2 = dvdt(t0,u0,v0);
        float k22 = dvdt(t0+h,u0+h*k1,v0+h*k2);
        myfile <<t0<<" "<<u0<<" "<<v0<<endl;
        t0 +=h;
        u0 +=0.5*h*(k1+k11);
        v0 +=0.5*h*(k2+k22);
    }
    myfile.close();
    return 0;
}
