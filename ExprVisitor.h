#ifndef EXPRVISITOR_H
#define EXPRVISITOR_H

class Literal;
class Variable;
class And;
class Or;
class Implication;
class Equivalence;
class Negate;

//
//	Vistors
//

class ExprVisitor{
public:
	virtual void visitLiteral(Literal* ) = 0;
	virtual void visitVariable (Variable*) = 0;
	virtual void visitAnd (And*) = 0;
	virtual void visitOr (Or*) = 0;
	virtual void visitImplication (Implication*) = 0;
	virtual void visitEquivalence (Equivalence*) = 0;
	virtual void visitNegate (Negate*) = 0;
};

#endif
