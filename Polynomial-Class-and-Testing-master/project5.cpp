//test.cpp
#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include "polynomial.h"

using namespace std;


bool testPolynomial(const Polynomial& p, string expected);
bool testOperations(const Polynomial& p, int degree, double expected);
bool testInput(string s);


int main() {

  int errors = 0;

  cerr << "Note: Nearly all of the tests expect a working output operator. If a test fails, check that first" << endl;
  cerr << "Testing default constructor" << endl;
  Polynomial p1;   // test default constructor
  errors += testPolynomial(p1, "0");

  cerr << "Testing explicit value constructor" << endl;
  double c_arr[] =  {1.1, 2, 4, 7};
  int e_arr[] = {6, 3, 2, 0};
  vector<double> c(c_arr, c_arr+4);
  vector<int> e(e_arr, e_arr+4);
  Polynomial p2(c, e);
  errors += testPolynomial(p2, "1.1x^6+2x^3+4x^2+7");
  c.clear(); e.clear();
  Polynomial p3(c, e);
  errors += testPolynomial(p3, "0");


  cerr << "Testing operations" << endl;
  double c2_arr[] =  {-1.1, 2, -4, 7};
  int e2_arr[] = {4, 3, 2, 0};
  vector<double> c2(c2_arr, c2_arr+4);
  vector<int> e2(e2_arr, e2_arr+4);
  Polynomial p4(c2,e2);
  
  //errors += testOperations(p1, 0, 0);

  errors += testOperations(p2, 6, 109.4);
  errors += testOperations(p4, 4, -10.6);
  
  errors += testPolynomial(p1.Derivative(), "0");
  errors += testPolynomial(p2.Derivative(), "6.6x^5+6x^2+8x");
  errors += testPolynomial(p4.Derivative(), "-4.4x^3+6x^2-8x");
 
  

  
  errors += testPolynomial(p1+p2, "1.1x^6+2x^3+4x^2+7");
  errors += testPolynomial(p2+p4, "1.1x^6-1.1x^4+4x^3+14");
  
  errors += testPolynomial(p1*p2, "0");
  errors += testPolynomial(p2*p2, "1.21x^12+4.4x^9+8.8x^8+19.4x^6+16x^5+16x^4+28x^3+56x^2+49");
  
  double c_arr3[] = {-1};
  int e_arr3[] = {0};
  vector<double> c3 = vector<double>(c_arr3, c_arr3+1);
  vector<int> e3 = vector<int>(e_arr3, e_arr3+1);
  Polynomial p5(c3, e3);
  
  errors += testPolynomial(p2 * p5 + p2, "0");
  errors += testPolynomial(p5, "-1");
  

  cerr << "Testing input operator." << endl;
  errors += testInput("0");
  errors += testInput("51");
  errors += testInput("-1.1");
  errors += testInput("3x^2");
  errors += testInput("-5x^3-5");
  errors += testInput("x^5+x-1");
  errors += testInput("-x^4+2");

  return errors;
}

bool testPolynomial(const Polynomial& p, string expected) {
  ostringstream out;
  out << p;
  if (out.str() != expected) {
    cerr << "Test failed: expected " << expected << " got " << out.str() << endl;
    return true;
  } else {
    return false;
  }
}

bool testOperations(const Polynomial& p, int degree, double expected) {
  cerr << p.Degree() << " " << degree << "****" << endl;
  if(p.Degree() != degree) {
    cout << p.Degree();
    cerr << "Failed Degree operation" << endl;
    return true;
    }
  double result = p.Evaluate(2.0);
  if (fabs(result - expected) > 1e-5) {
    cerr << "Failed Evaluation operation" << endl;
  }
  return false;
}

bool testInput(string s) {
  Polynomial p;
  istringstream in(s+" ");
  in >> p;
  ostringstream out;
  out << p;
  if (out.str() != s) {
    cerr << "Failed input test. Expected: " << s << " got " << out.str() << endl;
    return true;
  }
  return false;
}
