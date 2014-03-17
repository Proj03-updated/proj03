#ifndef BINARY_H
#define BINARY_H

#include <iostream>
#include <string>

using namespace std;

#include "ExprVisitor.h"
#include "Expr.h"
#include "Uniary.h"

class Binary : public Expr
{
private:
	Expr* _leftPtr;
	Expr* _rightPtr;

protected:
	Binary( Expr* left, Expr* right ) : _leftPtr( left ), _rightPtr( right ) {};
	virtual ~Binary() { delete _leftPtr; delete _rightPtr; };

public:
	Expr* getLeftOperand() { return _leftPtr; };
	Expr* getRightOperand() { return _rightPtr; };

	virtual bool getValue() { 
		cout << "problem" << endl;
		return false;
	};
	virtual bool hasValue() {
		cout << "problem" << endl;
		return false;
	};
};

class And : public Binary {
public:
  And( Expr* left, Expr* right) : Binary( left, right ) {};

  //should return a type Expr, because it should be able to repersent either a Literal or a Operator
  virtual Expr* compute() { 
    Expr* computedLeft = getLeftOperand()->compute();
    Expr* computedRight = getRightOperand()->compute();
    if ( computedLeft->hasValue() && computedRight->hasValue() ) 
    {
      this->_hasValue = true;
      return new Literal(computedLeft->getValue() && computedRight->getValue() ); 
    } 
    else if ( computedLeft->hasValue() != computedRight->hasValue()   ) 
    { 
      if (computedLeft->hasValue() )
      {
	if ( computedLeft->getValue() == true ) 
	{
	  this-> _hasValue = false;
	  return getRightOperand();
	} 
	else 
	{ 
	  this-> _hasValue = true;
	  return new Literal ( false );
	}
      } 
      else 
      {
	if ( computedRight->getValue() ) 
	{
	  this-> _hasValue = false;
	  return getLeftOperand();
	} 
	else 
	{
	  this-> _hasValue = true;
	  return new Literal ( false );
	}
      }
	    //return new Literal(false);
    } 
    else 
    {
	    // two undefined vars
      this-> _hasValue = false;
      return this;
    }
  };
  virtual bool hasValue() 
  {
    return _hasValue;
  };
  virtual bool getValue() 
  {
    Expr* computedLeft = getLeftOperand()->compute();
    Expr* computedRight = getRightOperand()->compute();
    return computedLeft->getValue() && computedRight->getValue();
  };
  virtual void accept( ExprVisitor* v ) { v->visitAnd(this); };
};

class Or : public Binary {
public:
  Or( Expr* left, Expr* right) : Binary( left, right ) {};
  virtual Expr* compute() { 
    Expr* computedLeft = getLeftOperand()->compute();
    Expr* computedRight = getRightOperand()->compute();
    if ( computedLeft->hasValue() && computedRight->hasValue() ) 
    {  
      this->_hasValue = true;
      return new Literal(computedLeft->getValue() || computedRight->getValue() ); 
    } 
    else if ( computedLeft->hasValue() != computedRight->hasValue()   ) 
    { 	
      if (computedLeft->hasValue() )
      {
	if ( computedLeft->getValue() == true ) 
	{
	//  this-> _hasValue = false;
	  return new Literal(true) ;
	} 
	else 
	{ 
	//  this-> _hasValue = true;
	  return getRightOperand();
	}
	} 
	else 
	{
	  if ( computedRight->getValue() == true ) 
	  {
	    //  this-> _hasValue = false;
	    return new Literal ( true ); 
	  } 
	  else 
	  { 
	    //  this-> _hasValue = true;
	    return getLeftOperand();
	  }
	}
    //    return new Literal(false);
    } 
    else 
    {
      this-> _hasValue = false;
      return this;
    }
  };
  virtual bool hasValue() 
  {
    return _hasValue;
  };
  virtual bool getValue() 
  {
    Expr* computedLeft = getLeftOperand()->compute();
    Expr* computedRight = getRightOperand()->compute();
    return computedLeft->getValue() || computedRight->getValue();
  };
  virtual void accept( ExprVisitor* v ) { v->visitOr(this); };
};

class Implication : public Binary {
public:
  Implication( Expr* left, Expr* right) : Binary( left, right ) {};
  virtual Expr* compute() { 
    Expr* computedLeft = getLeftOperand()->compute();
    Expr* computedRight = getRightOperand()->compute();
    if ( computedLeft->hasValue() && computedRight->hasValue() ) 
    {
      this->_hasValue = true;
      return new Literal(!computedLeft->getValue() || computedRight->getValue() ); 
    } 
    else if ( computedLeft->hasValue() != computedRight->hasValue()   ) 
    { 	
      if (computedLeft->hasValue() )
      {
	if ( computedLeft->getValue() == true ) 
	{
	//  this-> _hasValue = false;
	  return getRightOperand();
	} 
	else 
	{ 
	//  this-> _hasValue = true;
	  return new Literal(true) ;
	}
      } 
      else 
      {
	if ( computedRight->getValue() == true ) 
	{
	  //  this-> _hasValue = false;
	  return new Literal ( true ); 
	} 
	else 
	{ 
	  //  this-> _hasValue = true;
	  return (new Negate (getLeftOperand()));
	}
      }
    //    return new Literal(false);
    } 
    else 
    {
      this-> _hasValue = false;
      return this;
    }

  };
  virtual bool hasValue() 
  {
    return _hasValue;
  };
  virtual bool getValue() 
  {
    Expr* computedLeft = getLeftOperand()->compute();
    Expr* computedRight = getRightOperand()->compute();
    return (!computedLeft->getValue() || computedRight->getValue());
  };
  virtual void accept( ExprVisitor* v ) { v->visitImplication(this); };
};

class Equivalence : public Binary {
public:
    Equivalence( Expr* left, Expr* right) : Binary( left, right ) {};
    virtual Expr* compute() { 
    Expr* computedLeft = getLeftOperand()->compute();
    Expr* computedRight = getRightOperand()->compute();
    if ( computedLeft->hasValue() && computedRight->hasValue() ) 
    {
	    this->_hasValue = true;
	    return new Literal(computedLeft->getValue() == computedRight->getValue() ); 
    } 
    else if ( computedLeft->hasValue() != computedRight->hasValue()   ) 
    { 	
      if (computedLeft->hasValue())
      {
	if ( computedLeft->getValue() == true ) 
	{
	//  this-> _hasValue = false;
	  return getRightOperand();
	} 
	else 
	{ 
	//  this-> _hasValue = true;
	  return (new Negate (getRightOperand()));
	}
      } 
      else 
      {
	if ( computedRight->getValue() == true ) 
	{
	  //  this-> _hasValue = false;
	  return getLeftOperand();
	} 
	else 
	{ 
	  //  this-> _hasValue = true;
	  return (new Negate (getLeftOperand()));
	}
      }
    //    return new Literal(false);
    } 
    else 
    {
      this-> _hasValue = false;
      return this;
    }

  };
  virtual bool hasValue() 
  {
    return _hasValue;
  };
  virtual bool getValue() 
  {
    Expr* computedLeft = getLeftOperand()->compute();
    Expr* computedRight = getRightOperand()->compute();
    return (computedLeft->getValue() == computedRight->getValue());
  };
  virtual void accept( ExprVisitor* v ) { v->visitEquivalence(this); };
};

#endif
