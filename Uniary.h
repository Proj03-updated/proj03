#ifndef UNIARY_
#define UNIARY_

#include <iostream>
#include <string>

using namespace std;

#include "ExprVisitor.h"
#include "Expr.h"


class Uniary : public Expr {
protected:
	Expr* _opPtr;
	Uniary( Expr* opPtr ) : _opPtr( opPtr ) {};
	virtual ~Uniary() { delete _opPtr; };

public:
	Expr* getOperand() { return _opPtr; };

	virtual bool hasValue() {
		return false;
	}
	virtual bool getValue() {
		return false;
	}
};

class Negate : public Uniary {
public:
	Negate( Expr* opr ) : Uniary( opr ) {};

	virtual Expr* compute() { 
		if ( getOperand()->hasValue() )  {
			_hasValue = true;
			return new Literal( !( _opPtr->getValue() ) );
		} 
		else 
		{
			return this;
		}
	};

	virtual bool hasValue() {
		return _hasValue;
	}
	virtual bool getValue() {
		return !( _opPtr->getValue() );
	}
	virtual void accept( ExprVisitor* v ) { v->visitNegate(this); };
};

#endif
