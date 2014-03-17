#ifndef PRINTVISITOR_H
#define PRINTVISITOR_H

using namespace std;

#include <stack>
#include <iostream>

#include "ExprVisitor.h"
#include "Uniary.h"
#include "Binary.h"

class PrintVisitor : public ExprVisitor{
public:
	virtual void visitLiteral(Literal* lit ) = 0;
	virtual void visitVariable (Variable*) = 0;
	virtual void visitAnd (And*) = 0;
	virtual void visitOr (Or*) = 0;
	virtual void visitImplication (Implication*) = 0;
	virtual void visitEquivalence (Equivalence*) = 0;
	virtual void visitNegate (Negate*) = 0;





#endif
