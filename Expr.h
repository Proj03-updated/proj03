#ifndef EXPR_H
#define EXPR_H

#include <iostream>
#include <string>

using namespace std;

#include "ExprVisitor.h"


class Expr {
protected:
	bool _value;
	bool _hasValue = false;
public:
	Expr() {};
	virtual ~Expr() {};
	Expr( Expr& other ) {};
	Expr& operator=( const Expr& other ) { return *this; };

	virtual Expr* compute() = 0;

	virtual bool getValue() = 0;
	virtual bool hasValue() = 0;
	virtual void accept( ExprVisitor* ) = 0;

};

//
//	Values: Either a literal or variable
//


class Literal : public Expr {
private:
	bool _hasValue = true;
	bool _value;
public:
	Literal( bool val ) : _value(val) {};

	virtual Expr* compute() { return this; };

	virtual bool getValue() { return _value; };
	virtual bool hasValue() { return _hasValue; };
	virtual void accept( ExprVisitor* v ) { v->visitLiteral(this); };
};

class Variable : public Expr {
private:
	Literal* _value;
	string _name;
public:
	Variable( string name ) : _name(name) {
		_hasValue = false;
	};
	Variable( string name, bool value ) : _name(name) { 
		_hasValue = true;
		_value = new Literal(value); 
	};

	virtual Expr* compute() { 
		if ( this->hasValue() )
			return (new Literal( _value->getValue() ) );
		else
			return this; 
	};

	virtual bool getValue() { return _value->getValue(); };
	virtual bool hasValue() { return _hasValue; };

	virtual void accept( ExprVisitor* v ) { v->visitVariable(this); };
};

//
//	Operators: AND OR IMPLICATION EQUIVALENCE
//

#endif
