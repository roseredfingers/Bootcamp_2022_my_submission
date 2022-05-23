#include <bits/stdc++.h>  
using namespace std;  
  
class Complex {  
public:  
    int real; 
    int imaginary;  
  
    Complex()  
    {  
        real = 0;  
        imaginary = 0;  
    }  
    Complex(int r, int i)  
    {  
        real = r;   
        imaginary = i; 
    }  
  
    Complex addComplexNumber(Complex C1, Complex C2)  
    {  
  
        Complex res;  
        res.real = C1.real + C2.real;  
        res.imaginary = C1.imaginary + C2.imaginary;  
        return res;  
    }  
};  
  
int main()  
{  
    int r1, r2, i1, i2;
    cout<<"Enter the real and imaginary parts of first complex number:";
    cin>>r1>>i1;
    Complex C1(r1, i1);  
    cout << "Complex number 1 : " << C1.real  
         << " + i" << C1.imaginary << endl;  
    cout<<"Enter the real and imaginary parts of second complex number:";
    cin>>r2>>i2;
    Complex C2(r2, i2);  
    cout << "Complex number 2 : " << C2.real  
         << " + i" << C2.imaginary << endl;  
    Complex C3;  
    C3 = C3.addComplexNumber(C1, C2);  
    cout << "Sum of complex number : "  
         << C3.real << " + i"  
         << C3.imaginary;  
}  