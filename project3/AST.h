#include <string>
#include <stdio.h>
#include <map>
#include <vector>
#include <stack>
using namespace std;
enum Type {INT, STRING, BOOL, OBJECT, ARRAY, INVALID, UNINIT, UNDECLAIRED};
enum OP {EQ, NE, GE, LE, GT, LT, AND, OR};
class Statement;
class Value;
typedef map <string, Value *> ObjTable;
typedef vector <Statement*> Block;

class Array {
	int maxIndex;
	map <int , Value*> * tbl;
	public:
	Array();
	void addElement(int, Value*);
	Value * getElement(int);
	int count(int);
	Array (const Array &other);
  	Array &operator = (const Array &other);
	~Array();
	int size();
};

class Value  {
	int intVal;
	string strVal;
	Type varType;
	ObjTable objTable;
	bool booVal;
	Array array;

	public:
	Value (int intVal);

	Value (string strVal);

	Value (string strVal, Type t);

	Value (Type t);

	Value (bool);

	Value (ObjTable &);

	Value (Array &);

	// Copy constructor
	Value (const Value &other);

	Value ();
	virtual Type getType() ;
	virtual int getInt() ;
	virtual bool getBoo();
	virtual string & getStr() ;
	virtual ObjTable & getObj();
	virtual Array & getArray();
	virtual void print();
	virtual bool isTrue();
};

class Expression {
	protected:	int lineNumber;
public:
	virtual void setLine(int);
	virtual void printAST() = 0;
  //  It's necessary because we need to clone objects without
  // knowing the exact type.
  virtual Expression *clone () = 0;

  // The value represented by the expression
  virtual Value * value () = 0;

  virtual ~Expression();

};

class Variable : public Expression {
	public:
		virtual void setValue(Value*) = 0;
		virtual Variable *clone() = 0;
		virtual bool isDeclaired()= 0;
	virtual void printAST() = 0;
};

class Comparison : public Expression {
	Expression * child_left;
	Expression * child_right;
	OP op;
	public:

  Comparison (OP op, Expression *left, Expression *right, int);


  // Copy constructor
 Comparison (const Comparison &other);

  virtual ~Comparison ();

  Comparison &operator = (const Comparison &other);

  virtual Comparison *clone ();
	virtual void printAST();

  virtual Value * value ();

};

class SimpleVar : public Variable {
	string varName;
	map <string, Value*>& symTBL;
	bool decl;

	public:
		SimpleVar(string name, map <string, Value*> & table, int);
		virtual void setValue(Value*);
		virtual Value * value();
		virtual Variable *clone ();
		virtual bool isDeclaired();
		virtual void setDecl(bool);
	virtual void printAST();
};

class ObjectVar : public Variable{
	string varName;
	Variable *variable;
	public:
		ObjectVar(string, Variable * , int);
		virtual void setValue(Value*);
		virtual Value * value();
		virtual Variable *clone ();
		virtual bool isDeclaired();
	virtual void printAST();
		// Copy constructor
		ObjectVar (const ObjectVar &other);
};

class ArrayVar : public Variable {
	Expression * index;
	Variable * variable;
	public:
		ArrayVar(Expression *, Variable*, int);
		virtual void setValue(Value*);
		virtual Value * value();
		virtual Variable *clone ();
		virtual bool isDeclaired();
		virtual void printAST();
		ArrayVar(const ArrayVar &other);
};

class Statement : public Expression{

};

class ObjectDef : public Expression {
	vector <string> names;
	vector <Expression *> exprs;
	public:
	ObjectDef(int);
  //  It's necessary because we need to clone objects without
  // knowing the exact type.
  virtual ObjectDef *clone () ;

  virtual void addProperty(string, Expression*);

  // The value represented by the expression
  virtual Value * value () ;
virtual void printAST();

  virtual ~ObjectDef();
};

class ArrayDef : public Expression {
	vector <Expression *> exprs;
	public:
	virtual ArrayDef *clone();
	virtual void addProperty( Expression *);
	virtual Value * value();
	virtual void printAST();
	virtual ~ArrayDef();
	ArrayDef(int);
};

class DocumentWrite : public Statement {
	vector <Expression* >  WriteBuffer;
	//map <string, Value*> & symTBL;

	public:
		DocumentWrite(int);
		virtual void addExpression(Expression*);
		virtual Value * value();
		virtual Expression * clone();
	virtual void printAST();
		~DocumentWrite();
};

class Var_Decl : public Statement {
	string varName;
	map <string, Value*>& symTBL;
	public:
		Var_Decl(string, map <string, Value*>& , int);
		virtual bool isDeclaired();
		virtual Value * value ();
		virtual Expression * clone();
	virtual void printAST();
};

class Assign : public Statement {
	Variable * child_left;
	Expression * child_right;
	public:
	~Assign();
		Assign (Variable * left, Expression * right, int);
		virtual Value * value();
  virtual Expression *clone ();
	virtual void printAST();
};

class Program {
	vector <Statement*> nodes;
	public:
	Program();
	void addStatement(Statement*);
	void execute();
	virtual void printAST();
	virtual ~Program();
};
class Word : public Expression{
	string word;

	public:

  Word (string val, int);

  // Copy constructor
  Word (const Word &other);

  Word &operator = (const Word &other);

  virtual Expression *clone ();
	virtual void printAST();

  virtual Value * value ();
};

// For numbers
class Number : public Expression {
  int num;

public:

  Number (int val, int);

  // Copy constructor
  Number (const Number &other);

  Number &operator = (const Number &other);

  virtual Expression *clone ();
	virtual void printAST();

  virtual Value * value ();
};

class Boolean : public Expression {
	bool boo;
	public:
	Boolean (bool, int);
	Boolean (const Boolean &other);
	Boolean &operator = (const Boolean &other);
	virtual Expression * clone();
	virtual void printAST();
	virtual Value * value();
};

// For addictive expressions
class Plus : public Expression {
  Expression *child_left, *child_right;

public:

  Plus (Expression *left, Expression *right, int);

  // Copy constructor
  Plus (const Plus &other);

  virtual ~Plus ();

  Plus &operator = (const Plus &other);


  virtual Expression *clone ();
	virtual void printAST();

  virtual Value * value ();

};

// For multiplicative expressions
class Times : public Expression {
  Expression *child_left, *child_right;

public:

  Times (Expression *left, Expression *right, int);

  // Copy constructor
  Times (const Times &other);

  virtual ~Times ();

  Times &operator = (const Times &other);

  virtual Expression *clone ();
	virtual void printAST();

  virtual Value * value ();

};


// For substraction expressions
class Minus : public Expression {
  Expression *child_left, *child_right;

public:

  Minus (Expression *left, Expression *right, int);

  // Copy constructor
  Minus (const Minus &other);

  virtual ~Minus ();

  Minus &operator = (const Minus &other);

  virtual Expression *clone ();
	virtual void printAST();

  virtual Value * value ();

};


// For divide expressions
class Divide : public Expression {
  Expression *child_left, *child_right;

public:

  Divide (Expression *left, Expression *right, int);

  // Copy constructor
  Divide (const Divide &other);

  virtual ~Divide ();

  Divide &operator = (const Divide &other);

  virtual Expression *clone ();
	virtual void printAST();

  virtual Value * value ();

};
