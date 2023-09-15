#include <iostream>
#include <math.h>
#include <fstream>
#include <iomanip>
using namespace std;
// u > Rabbit, v > Fox
float dudt(float u,float v){
    return 0.05*u*(1-0.01*v);  
}
float dvdt(float u, float v){
    return 0.1*v*(0.005*u-2);
}
int main(){
    ofstream myfile;
    myfile.open ("ODESolver.txt");
    float h = 0.1, t0 = 0, u0 = 1500, v0 = 100; // 1500 Rabbit and 100 Fox
    while (t0 < 600 + h/1000){ 
        cout<<setprecision(6)<<t0<<" "<<u0<<" "<<v0<<endl;
        myfile <<t0<<" "<<u0<<" "<<v0<<endl;
        float k1 = dudt(u0,v0);  
        float k2 = dvdt(u0,v0);
        float k11 = dudt(u0+h*k1,v0+h*k2);
        float k22 = dvdt(u0+h*k1,v0+h*k2);
        t0 +=h;
        u0 +=0.5*h*(k1+k11);
        v0 +=0.5*h*(k2+k22);
    }
    myfile.close();
    return 0;
}