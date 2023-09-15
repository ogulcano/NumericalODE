#include <iostream>
#include <math.h>
#include <fstream>
#include <iomanip>
using namespace std;

float r(float t){
    return sqrt(1+t)*cos(t);
}
float s(float t){
    return sqrt(1+t)*sin(t);
}
float drdt(float t){
    return 0.5*cos(t)/sqrt(1+t) - sqrt(1+t)*sin(t);
}
float dsdt(float t){
    return 0.5*sin(t)/sqrt(1+t) + sqrt(1+t)*cos(t);
}
float dxdt(float x,float y,float r, float s, float dr,float ds,float k){
    float R = (k*sqrt(pow(dr,2)+pow(ds,2)))/(sqrt(pow((r-x),2)+pow((s-y),2)));
    return R*(r-x);
}
float dydt(float x,float y,float r, float s, float dr,float ds,float k){
    float R = (k*sqrt(pow(dr,2)+pow(ds,2)))/(sqrt(pow((r-x),2)+pow((s-y),2)));
    return R*(s-y);
}  

int main(){
    ofstream myfile;
    myfile.open ("ODESolver.txt");
    float h = 0.1, k = 1.1,t0 = 0, r0 = 1, s0 = 0;
    float x0 = 3, y0 = 0;
    while (t0 < 5.5 + h/1000){
        myfile <<t0<<" "<<r(t0)<<" "<<s(t0)<<" "<<x0<<" "<<y0<<endl;
        float k1 = dxdt(x0,y0,r(t0),s(t0),drdt(t0),dsdt(t0),k);
        float k2 = dydt(x0,y0,r(t0),s(t0),drdt(t0),dsdt(t0),k);
        t0 +=h, r0 +=r(t0),s0 +=s(t0), x0 +=h*k1, y0 +=h*k2;
    }
    myfile.close();
    return 0;
}