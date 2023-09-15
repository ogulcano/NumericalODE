#include <iostream>
#include <math.h>
#include <fstream>
#include <iomanip>
using namespace std;

float dHdt(float H,float Z, float b){
    return -b*H*Z;
}
float dZdt(float H,float Z,float R,float a,float b, float g){
    return b*H*Z+g*R-a*H*Z;
}
float dRdt(float H,float Z,float R,float a,float b, float g){
    return a*H*Z-g*R;
}

int main(){
    ofstream myfile;
    myfile.open ("ODESolver.txt");
    float h = 0.01, t0 = 0, H0 = 500, Z0 = 5, R0 = 0;
    float a = 0.005, b = 0.01, g = 0.2;
    while (t0 < 10 + h/1000){
        cout<<setprecision(6)<<t0<<" "<<H0<<" "<<Z0<<" "<<R0<<" "<<H0+Z0+R0<<endl;
        myfile <<t0<<" "<<H0<<" "<<Z0<<" "<<R0<<" "<<H0+Z0+R0<<endl;
        float k1 = dHdt(H0,Z0,b);
        float k2 = dZdt(H0,Z0,R0,a,b,g);
        float k3 = dRdt(H0,Z0,R0,a,b,g);
        float k11 = dHdt(H0+h*k1,Z0+h*k2,b);
        float k22 = dZdt(H0+h*k1,Z0+h*k2,R0+h*k3,a,b,g);
        float k33 = dRdt(H0+h*k1,Z0+h*k2,R0+h*k3,a,b,g);
        t0 +=h;
        H0 +=0.5*h*(k1+k11);
        Z0 +=0.5*h*(k2+k22);
        R0 +=0.5*h*(k3+k33);
    }
    myfile.close();




    return 0;
}