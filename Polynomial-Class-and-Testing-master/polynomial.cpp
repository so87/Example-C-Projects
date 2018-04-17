//#polynomial.cpp
//Simon Owens
//CS 215 MP3
//polynomial.cpp

#include "polynomial.h"
#include "cmath"
#include "stdexcept"
  
// Constructors
Polynomial::Polynomial() 
{
    headPtr = new Node;
    Polynomial::Node* newN = new Node();
    headPtr->next = newN;
    headPtr->data.expo = 0;
    headPtr->data.coeff = 0;
}

Polynomial::Polynomial(vector<double> iC, vector<int> iE) {

    Node* list_tail = new Node();
    headPtr = list_tail;
    headPtr->next = 0;
    int index = iE.size()-1;
    int i = 0;
    do {
        
        // add node before end of vector
        if (index >=  0) {
            Node * new_node = new Node();
	    new_node->data.coeff = iC[i];
	    new_node->data.expo = iE[i];
	    list_tail->next = new_node;
	    list_tail = new_node;
	  
        }
	i++;
	 
    } while (index >= i);
    
   	   
}


//Function:  Degree
//returns the highest exponent
int
Polynomial::Degree() const
{
  // highest exponent is from first node
  return headPtr->next->data.expo;
}

//Function:  Evaluate 
//given a certain variable for x, solves and returns answer
double
Polynomial::Evaluate(double x) const
{
  double answer = 0;
  //loops through all nodes
  for (const Node * p = headPtr->next; p != 0; p = p->next)
   {
   //start from first node
   if(p->data.expo > 0)
     answer += p->data.coeff*pow(x, p->data.expo);
   else
     answer += p->data.coeff;
   }
  
  return answer;
}

//Function:  Derivative
//computes the derivaive of the given polynomial then returns the result
Polynomial
Polynomial::Derivative() const
{
  //make variables
  Polynomial deriv;
  Polynomial::Node* pointer = deriv.headPtr->next;
  delete pointer;
  Node * prev;
  prev = deriv.headPtr;
  //loop through the nodes
  for (Node * p = headPtr->next; p != 0; p = p->next)
    {
      Node * new_node = new Node();
      new_node->next = 0;
      prev->next = new_node;
      new_node->data.coeff = p->data.coeff * p->data.expo;
      //then its a zero or integer
      if (p->data.expo != 0)
	{
	  new_node->data.expo = p->data.expo - 1;
	}
      prev = new_node;
    }
  

  return deriv;

}
  
//Function:: insert
// this is used for the add and multiply
void
Polynomial::Insert(double co, int expo)
{
  // Check first to see if no node
  if(headPtr == 0) 
    {
      headPtr = new Node();
      headPtr->data.expo = expo;
      headPtr->data.coeff = co;
      return;
    }
  //check to see if there is only one other node
  if(headPtr->next == 0)
    {
      if(headPtr->data.expo >= expo)
	{
	   Node* newN= new Node();
	   headPtr->next=newN;
	   headPtr->next->data.expo=expo;
	   headPtr->next->data.coeff=co;
	   return;
	}
      else if(headPtr->data.expo == expo)
	{
	  headPtr->data.coeff += co;
	  return;
	}

      else 
	{
	  Node* newN = new Node();
	  newN->next = headPtr->next;
	  headPtr = newN;
	  headPtr->data.coeff = co;
	  headPtr->data.expo = expo;
	  return;
	}
	
    }  
  // three cases: add coefficients, create new node at end, inbetween or first
  //   when creating inbetween node: creat new node, assign that to
  //   what the previous was pointing to, then assign previous to new node

    // loop through all of the nodes until the end
    for (Node* p = headPtr;p!=0;p=p->next)
      { 
	//if the exponents are equal, add them up
        if (p->next->data.expo == expo)
	  {
            p->next->data.coeff += co;
            return;
	  }
        //last node, add this on to the end
        else if ((p->next->data.expo>expo)&&(p->next->next==0))
	  {
	    Node* newN= new Node();
	    p->next->next=newN;
	    p->next->next->data.expo=expo;
	    p->next->next->data.coeff=co;
	    return;
	  }
	//eithr first or inbetween
        else if (p->next->data.expo < expo)
	  {
	    Node* newN = new Node();
            newN->next = p->next;
	    p->next = newN;
            p->next->data.coeff = co;
            p->next->data.expo = expo;
            return;
	  }
	
      }
    
}
//Function:: add operator
// this function loops through both nodes until the end, inserting them
Polynomial
operator+(const Polynomial& LP, const Polynomial& RP) 
{
  //create variable to return
  Polynomial sum;
  
  
  //loop through all on the left
  for (Polynomial::Node* L = LP.headPtr;L!=0;L=L->next)
    {
      sum.Insert(L->data.coeff, L->data.expo);
    }
  //loop through all on the right 
  for (Polynomial::Node* R = RP.headPtr;R!=0;R=R->next)
    {
      sum.Insert(R->data.coeff, R->data.expo);
    }
  
  return sum;
}


//Function:  Multiply operator
//multiplys the two polynomials together and returns the result
Polynomial
operator*(const Polynomial& LPoly, const Polynomial& RPoly)
{ 
  //variables to loop through
  Polynomial result;
  Polynomial::Node* LL = LPoly.headPtr;
  Polynomial::Node* RR = RPoly.headPtr;
  
  //make sure to check about 0... anything times 0 is 0
  if (LPoly.headPtr->data.coeff == 0 && LPoly.headPtr->next == 0)
    return result;
  if (RPoly.headPtr->data.coeff == 0 && RPoly.headPtr->next == 0)
    return result;


  //loop through all of the nodes
  for(Polynomial::Node* L = LL; L !=0; L = L->next)
    {
      for(Polynomial::Node* R = RR; R != 0; R = R->next)
	{
	  //add exponents, muliply coefficients
	  int expo = (R->data.expo+L->data.expo);
	  double coeff = (R->data.coeff*L->data.coeff);
	  result.Insert(coeff, expo);
	}
    }

  return result;
}




//Function: Output operator
//returns an output operator that has the mathematic formula of a polynomial
ostream&
operator<<(ostream& out, const Polynomial& aPoly)
{ 
 
  int count = 0;
  
  //check and see if just one node and its zero
  if((aPoly.headPtr->data.coeff == 0)&&(aPoly.headPtr->next==0))
    {
      out << '0';
      return out;
    }
  
  //loop through every node 
  //take advantage of output operator from term.h
  for(Polynomial::Node * p = aPoly.headPtr; p != 0; p = p->next)
   {
     if(p->data.coeff != 0)
       {
	 if(count == 0)
	   out << p->data;
	 else if((p->data.coeff > 0) && (count != 0))
	   out << "+" << p->data;
	 else if(p->data.coeff < 0)
	   out << p->data;
	 count++;
       }
   }
  if(count == 0)
    out << '0';

  return out;  
}

//Function:  Input operator
//returns an input stream
istream& 
operator>>(istream& in, Polynomial& aPoly)
{
  Polynomial::Node* pointer = aPoly.headPtr->next;
  delete pointer;
  char ch;
  double c;
  int e;
  int sign;
  Polynomial::Node * Tail = aPoly.headPtr;


  while(isspace(in.peek()))
    in.get(ch);
  
  while(!isspace(in.peek()))
    {
      //read coefficient
      ch =  in.peek();
      if (ch == '+')
	{
	  //cout << "PLAS"<<endl;
	  sign = 1;
	  in >> ch;
	}
      else if(ch == '-')
	{
	  sign = -1;
	  in >> ch;
	}
      else
	sign = 1;

      ch = in.peek();
      if(isdigit(ch))
	{
	  in >> c;
	}
      else
	c = 1.0;

      c *= sign;
      //cout << c<<"  "<<in.peek() << endl;
      //read exponent
      if(in.peek() == 'x')
	{
	  in >> ch;
	  if(in.peek() == '^')
	    {
	      in >> ch;
	      in >> e;
	    }
	  else
	    e = 1;
	}
      else
	e = 0;
      //make this new node and store the variables in its data
      Polynomial::Node* new_node = new Polynomial::Node();
      Tail->next = new_node;
      new_node->data.coeff = c;
      new_node->data.expo = e;
      new_node->next = 0;
      Tail = Tail->next;
    }

  return in;
}

//The Big Three

//Function: Destructor
//This distructs the node that has nothing in it anymore
Polynomial::~Polynomial()
{
  Polynomial::Node* current = headPtr;
  while( current != 0 ) 
  {
    Polynomial::Node* next = current->next;
    delete current;
    current = next;
  }
  
  headPtr = 0;
}


//Function:  Copy constructor
// creates a new polynomial that is identical to an exisiting one
Polynomial::Polynomial(const Polynomial& source)
{
  headPtr = new Node();
  Node* dest = headPtr;
  //loop through all of the ndoes
  for (Node* p = source.headPtr;p!=0;p=p->next) 
    {
      //asign data
      dest->data.coeff = p->data.coeff;
      dest->data.expo = p->data.expo;
      //see if the enxt is going to be null
      if (p->next != 0) 
	{
	  dest->next = new Node;
	  dest = dest->next;
	}
    }
}

//Function:  operator = 
// makes an existing polynomial object identical to the original poly object.
Polynomial&
Polynomial::operator=(const Polynomial& source)
{
  //doesn't need to be deleted or copied 
  if (headPtr == source.headPtr)
  {
    return *this;
  }
  //delete and copy all the ndoes
  delete_all_nodes();
  //equivalent of copy_all_nodes
  headPtr = new Node();
  Node* dest = headPtr;

    for (Node* p = source.headPtr;p!=0;p=p->next) {// for all elements in source
        // copy data
        dest->data.coeff = p->data.coeff;
        dest->data.expo = p->data.expo;
        if (p->next != 0) {// if source has next node, create next node for dest
            dest->next = new Node;
            dest = dest->next;
        }
    }

  return *this;
}
//Function: delete_all_nodes
//returns nothing, deletes all of the nodes
void
Polynomial::delete_all_nodes()
{
  bool flag = false;
  //make infinate loop
  while(flag == false) 
    {
      Node* p = headPtr;
      headPtr = headPtr->next;
      delete p;
      //if the last one get out of loop
      if (headPtr==0)
	break;
    }
}
//Function: cop_all_from
// returns nothing, coppies all the nodes and pushes them back
void
Polynomial::copy_all_from(const Polynomial& l)
{
    Node* dest = l.headPtr;

    for (Node* p = l.headPtr;p!=0;p=p->next) 
      {// for all elements in source
        // copy data
        dest->data.coeff = p->data.coeff;
        dest->data.expo = p->data.expo;
        if (p->next != 0) 
	  {// if source has next node, create next node for dest
            dest->next = new Node;
            dest = dest->next;
	  }
      }
}
//Function: push_back
// creates a new node 
void
Polynomial::push_back(Term data) 
{
  Node * new_node = new Node;
  new_node->data = data;
  new_node->next = headPtr;
}
