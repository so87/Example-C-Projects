//#polynomial.h
//Simon Owens
//CS 215 MP5
//polynomial.h
#ifndef	POLYNOMIAL_H
#define POLYNOMIAL_H

#include <vector>
#include <iostream>
#include "term.h"
#include <stdexcept>

using namespace std;

class Polynomial {
 private:
  // Node that has a term and pointer to next node
  struct Node{
    Term data;
    Node* next;

    Node(const Term& d = Term(),
	 Node* n = 0): data(d), next(n){}
    };


 public:
  // constructors 
  Polynomial(vector<double> Icoef, vector<int> Iexp);
  Polynomial();
  ~Polynomial();
      
  // accessors
  int Degree() const;
  double Evaluate(double x) const;
  
  //derivative doesn't change poly
  Polynomial Derivative() const;
  Polynomial& operator=(const Polynomial& source);
  Polynomial(const Polynomial& source);
  void Insert(double coefficient, int exponent);
  
  
  //operators
  friend Polynomial operator+(const Polynomial& lP, const Polynomial& rP);
  friend Polynomial operator*(const Polynomial& lP, const Polynomial& rP);
  friend ostream& operator<<(ostream& out, const Polynomial& aPoly);
  friend istream& operator>>(istream& in, Polynomial& aPoly);


 private:

  //headPtr variable
  Node* headPtr;

  void delete_all_nodes();
  void copy_all_from(const Polynomial& l);
  void push_back(Term data);
  
};

#endif
