#include <iostream>
#include <string>

using namespace std;

#include "ExprVisitor.h"
#include "Expr.h"
#include "Binary.h"
#include "Uniary.h"
int main () {
	//Expr* ex = new And( new And( new Literal(true), new Literal(true) ), new Literal(true) );

	//Expr* ex =new Negate( new Negate (new Negate( new And( new Variable("X"), new Literal(true) ) ) ) );
	Expr* ex  =new Equivalence(new And ((new Variable("X", true)),new Literal(true)), new Variable("A", true)); 
	//Expr* ex  =new Equivalence( new Literal(true), new Literal(false));
	cout<< ex->compute()->getValue()<< endl;
	//cout<< ex->compute() << endl;
	return 0;
}


