#include "AST.h"
//  It's necessary because we need to clone objects without
// knowing the exact type.

Program::Program() {};
void Program::addStatement(Statement* st) {
	nodes.push_back(st);
}
void Program::execute() {
	for(int i = 0; i < nodes.size(); i++) {
		delete nodes[i]->value();
	}
}

Program::~Program(){
	for(int i = 0; i < nodes.size(); i++){
		delete nodes[i];
	}
}

DocumentWrite::DocumentWrite(int lineN){
	lineNumber = lineN;
};

void DocumentWrite::addExpression(Expression* expr) {
	WriteBuffer.push_back(expr);
}

Value * DocumentWrite::value() {
	for(int i = 0; i < WriteBuffer.size(); i++){
		//	delete WriteBuffer[i]->value();
		Value * result = WriteBuffer[i] -> value();
		if(	result -> getType() == INT) {
			printf("%d", result->getInt());
		} else if (result ->getType() == STRING) {
			if(result ->getStr() == "<br />") {
				printf("\n");
			} else {
				printf("%s", result->getStr().c_str());
			}
		} else if (result ->getType() == BOOL) {

			printf("%s", result->getBoo()? "true" : "false");
		}
		else if (result->getType() == OBJECT || result->getType() == ARRAY) {
			fprintf(stderr, "Line %d, type violation\n",lineNumber);
		} else {
		//	printf("Line %d, undefined\n", lineNumber);
		//	fprintf(stderr, "Line %d, %s\n", lineNumber, result->getStr().c_str());
		}
		delete result;
	}
}

DocumentWrite::~DocumentWrite() {
	for(int i =0; i < WriteBuffer.size(); i++) {
		delete WriteBuffer[i];
	}
}

Expression * DocumentWrite::clone() {
	return new DocumentWrite (*this);
}



// The value represented by the expression
Expression::~Expression() {}

bool SimpleVar::isDeclaired() {
	if (symTBL.count(varName) > 0 ){
		return true;
	}
	else {
		return false;
	}
}


SimpleVar::SimpleVar(string name, map <string, Value*> & table, int lineN): varName(name), symTBL(table) {
lineNumber = lineN;
};

void SimpleVar::setDecl(bool d) {
	decl = d;
}
void SimpleVar::setValue(Value* val) {
//	if(symTBL[varName] != NULL ) {
	if(val == NULL)
	{
		fprintf(stderr, "Value is null!\n");
	}
	else {
	//	fprintf(stderr, "Phew..\n");
	}
	if(decl) {
		symTBL[varName] = new Value(*val);
	} else {
	//	printf("\'%s\'\n", varName.c_str());
	//	printf("%\n", symTBL[varName]);
	//	printf("%d\n", val->getInt());
		if(isDeclaired()) {
			delete symTBL[varName];
			symTBL[varName] = new Value(*val);
		} else {
			// To do:
			// ERROR MESSAGE
			fprintf(stderr, "Line %d, undeclaired\n", lineNumber);
		}
	}
}

Value * SimpleVar::value(){
	if(!isDeclaired()) {
		return new Value("undefined", INVALID);
	}
	Value * result = new Value(*symTBL[varName]);
	//printf("%d\n", result->getInt());
	return result;
}

Variable * SimpleVar::clone () { return new SimpleVar (*this); }

Assign::Assign(Variable * left, Expression * right, int lineN): child_left(left), child_right(right) {
lineNumber = lineN;
};

Value * Assign::value() {
	Value *temp = child_right->value();
	child_left->setValue(temp);
	return temp;
}
/*
Value * Variable::value() {
	return NULL;
}
*/
Expression * Assign::clone () { return new Assign (*this); }

Assign::~Assign(){
	delete child_left;
	delete child_right;
}

Value::Value(int intVal) {
	this->intVal = intVal;
	varType = INT;
}

Value::Value(string strVal) {
	this->strVal = strVal;
	varType = STRING;
}

Value::Value(bool booVal) {
	this->booVal = booVal;
	varType = BOOL;
}

Value::Value(ObjTable & ot) {
	objTable = ot;
	varType = OBJECT;
}

Value::Value(string strVal, Type t) {
	this->strVal = strVal;
	varType = t;
}

Value::Value(Type t) {
	varType = t;
}

Value::Value(Array & at) {
	array = at;
	varType = ARRAY;
}

void Value::print() {
		if(	varType == INT) {
			printf("%d", getInt());
		} else if (varType == STRING) {
			printf("%s", getStr().c_str());
		} else {
			fprintf(stderr, "Invalid Type: %d '%s'\n",
					(int) getType(),
					getStr().c_str());
		}
}

Value::Value() {};

Value::Value(const Value &other){
	intVal = other.intVal;
	strVal = other.strVal;
	objTable = other.objTable;
	varType = other.varType;
	array = other.array;
}

bool Value::isTrue() {
	if(varType == INT) {
		if(getInt() != 0) {
			return true;
		} else {
			return false;
		}
	} else if (varType == STRING) {
		if(getStr().size() > 0 ) {
			return true;
		} else {
			return false;
		}
	} else if (varType == BOOL) {
		if(getBoo() == true) {
			return true;
		} else {
			return false;
		}
	}
	return false;
}

Type Value::getType(){
	return varType;
}

int Value::getInt() {
	return intVal;
}

string & Value::getStr() {
	return strVal;
}

bool Value::getBoo(){
	return booVal;
}

ObjTable & Value::getObj(){
	return objTable;
}

Array & Value::getArray(){
	return array;
}

void Expression::setLine(int lineN) {
	lineNumber = lineN;
}

// For addictive expressions

Plus::Plus (Expression *left, Expression *right, int lineN): child_left (left), child_right (right) {
lineNumber = lineN;
}

// Copy constructor
Plus::Plus (const Plus &other) {
	child_left = other.child_left->clone ();
	child_right = other.child_right->clone ();
		lineNumber = other.lineNumber;
}

Plus::~Plus ()
{
	delete child_left;
	delete child_right;
}

Plus & Plus::operator = (const Plus &other) {
	if (&other != this) {
		delete child_left;
		delete child_right;

		child_left = other.child_left->clone ();
		child_right = other.child_right->clone ();
		lineNumber = other.lineNumber;
	}
	return *this;
}


Expression * Plus::clone () { return new Plus (*this); }

Value * Plus::value () {
	Value * result;
	Value * left = child_left->value();
	Value * right = child_right->value();
	if(left->getType() == right->getType() && left->getType() == INT) {
		result = new Value(left->getInt() + right->getInt());
	}
	else if(left->getType() == right->getType() && left->getType() == STRING) {
		result = new Value(left->getStr() + right->getStr());
	}
	else {
		result = new Value("type violation", INVALID);
	}


	delete left;
	delete right;
	return result;
}


// For multiplicative expressions

Times::Times (Expression *left, Expression *right, int lineN): child_left (left), child_right (right) {
lineNumber = lineN;
}

// Copy constructor
Times::Times (const Times &other) {
	child_left = other.child_left->clone ();
	child_right = other.child_right->clone ();
		lineNumber = other.lineNumber;
}

Times::~Times ()
{
	delete child_left;
	delete child_right;
}

Times & Times::operator = (const Times &other) {
	if (&other != this) {
		delete child_left;
		delete child_right;

		child_left = other.child_left->clone ();
		child_right = other.child_right->clone ();
		lineNumber = other.lineNumber;
	}
}


Expression * Times::clone () { return new Times (*this); }

Value * Times::value () {
	Value * result;
	Value * left = child_left->value();
	Value * right = child_right->value();
	if(left->getType() == right->getType() && left->getType()  == INT) {
		result =  new Value (left->getInt() * right->getInt());
	}
	else {
		result = new Value("type violation", INVALID);
	}
	delete left;
	delete right;
	return result;
}


// Substraction


Minus::Minus (Expression *left, Expression *right, int lineN): child_left (left), child_right (right) {
	lineNumber = lineN;
}

// Copy constructor
Minus::Minus (const Minus &other) {
	child_left = other.child_left->clone ();
	child_right = other.child_right->clone ();
		lineNumber = other.lineNumber;
}

Minus::~Minus ()
{
	delete child_left;
	delete child_right;
}

Minus & Minus::operator = (const Minus &other) {
	if (&other != this) {
		delete child_left;
		delete child_right;

		child_left = other.child_left->clone ();
		child_right = other.child_right->clone ();
		lineNumber = other.lineNumber;
	}
}


Expression * Minus::clone () { return new Minus (*this); }

Value * Minus::value () {
	Value * result;
	Value * left = child_left->value();
	Value * right = child_right->value();
	if(left->getType() == right->getType() && left->getType() == INT) {
		result = new Value(left->getInt() - right->getInt());
	}
	else {
		result = new Value("type violation", INVALID);
	}
	delete left;
	delete right;
	return result;
}

Divide::Divide (Expression *left, Expression *right, int lineN): child_left (left), child_right (right) {
lineNumber = lineN;
}

// Copy constructor
Divide::Divide (const Divide &other) {
	child_left = other.child_left->clone ();
	child_right = other.child_right->clone ();
	lineNumber = other.lineNumber;
}

Divide::~Divide ()
{
	delete child_left;
	delete child_right;
}

Divide & Divide::operator = (const Divide &other) {
	if (&other != this) {
		delete child_left;
		delete child_right;

		child_left = other.child_left->clone ();
		child_right = other.child_right->clone ();
		lineNumber = other.lineNumber;
	}
}


Expression * Divide::clone () { return new Divide (*this); }

Value * Divide::value () {
	Value * result;
	Value * left = child_left->value();
	Value * right = child_right->value();
	if(left->getType() == right->getType() && left->getType() == INT) {
		result =  new Value(left->getInt() / right->getInt());
	}
	else {
		result = new Value("type violation", INVALID);
	}

	delete left; delete right;
	return result;
}

Var_Decl::Var_Decl(string name, map <string, Value*> & table, int lineN): symTBL(table){
		varName = name;
		lineNumber = lineN;
}

bool Var_Decl::isDeclaired() {
	if (symTBL.count(varName) > 0 ){
		return true;
	}
	else {
		return false;
	}
}

Value * Var_Decl::value() {
	Value * result;
	if (symTBL.count(varName) > 0 ) {
		// TO DO:
		// ERROR MESSAGE
		result = new Value("ERROR MESSAGE", INVALID);
	}
	else {
		symTBL[varName] = new Value(UNINIT);
		result = new Value(*symTBL[varName]);
	}
	return result;
}

Comparison::Comparison(OP op, Expression * child_left, Expression * child_right, int lineN) {
	this->child_left = child_left;
	this->child_right = child_right;
	this->op = op;
	lineNumber = lineN;
}

Comparison::Comparison (const Comparison &other ){
	if (&other != this) {
		delete child_left;
		delete child_right;

		child_left = other.child_left->clone ();
		child_right = other.child_right->clone ();
		op = other.op;
		lineNumber = other.lineNumber;
	}
}

Comparison::~Comparison(){
	delete child_left;
	delete child_right;
}

Comparison * Comparison::clone() {
	return new Comparison (*this);
}


Value * Comparison::value() {
	//                        EQ     NE    GE     LE     GT       LT   AND   OR
	bool allowDiffTypes[] = {false, false, false, false, false, false, true, true};
	bool allowString[]    = {true, true, false, false, false, false, true, true};
	bool allowBool[]      = {true, true, false, false, false, false, true, true};
	bool allowInt[]       = {true,   true, true,  true,   true,  true,  true, true};
	Value * left = child_left->value();
	Value * right = child_right->value();
	if(left->getType() != right->getType() && !allowDiffTypes[op]) {
		fprintf(stderr, "Line %d, type violation\n", lineNumber);
		return new Value("Type Violation", INVALID);
	} else if (left->getType() == STRING && !allowString[op]) {
		fprintf(stderr, "Line %d, type violation\n", lineNumber);
		return new Value("Type Vilation", INVALID);
	} else if (left->getType() == INT && !allowInt[op]){
		fprintf(stderr, "Line %d, type violation\n", lineNumber);
		return new Value("Type Vilation", INVALID);
	} else if (left->getType() == BOOL && !allowBool[op]) {
		fprintf(stderr, "Line %d, type violation\n", lineNumber);
		return new Value("Type Vilation", INVALID);
	}
	if(op == EQ) {
		if(left->getType() == INT) {
			if(left->getInt() == right->getInt()) {
				return new Value(true);
			} else {
				return new Value(false);
			}
		} else if (left->getType() == STRING) {
			if(left->getStr() == right->getStr()){
				return new Value(true);
			} else {
				return new Value(false);
			}
		} else if (left->getType() == BOOL) {
			if(left->getBoo() == right->getBoo()){
				return new Value(true);
			} else {
				return new Value(false);
			}
		}
	}	 else if (op == NE) {
			if(left->getType() == INT) {
				if(left->getInt() != right->getInt()){
					return new Value(true);
				} else {
					return new Value(false);
				}
			} else if (left->getType() == STRING) {
				if(left->getStr() != right->getStr()){
					return new Value(true);
				} else {
					return new Value(false);
				}
			} else if (left->getType() == BOOL) {
				if(left->getBoo() != right->getBoo()){
					return new Value(true);
				} else {
					return new Value(false);
				}
			}
		} else if (op == GE) {
			if(left->getType() == INT) {
				if(left->getInt() >= right->getInt()){
					return new Value(true);
				} else {
					return new Value(false);
				}
			}
		} else if (op == LE) {
			if(left->getType() == INT) {
				if(left->getInt() <= right->getInt()){
					return new Value(true);
				} else {
					return new Value(false);
				}
			}
		} else if (op == GT) {
			if(left->getType() == INT) {
				if(left->getInt() > right->getInt()){
					return new Value(true);
				} else {
					return new Value(false);
				}
			}
		} else if (op == LT) {
			if(left->getType() == INT) {
				if(left->getInt() < right->getInt()){
					return new Value(true);
				} else {
					return new Value(false);
				}
			}
		} else if (op == AND) {
			if(left->isTrue() && right->isTrue()){
				return new Value(true);
			} else {
				return new Value(false);
			}
		} else if (op == OR) {
			if(left->isTrue() || right->isTrue()){
				return new Value(true);
			} else {
				return new Value(false);
			}
		}
	}

Expression * Var_Decl::clone() {return new Var_Decl(*this);}

// For numbers
Number::Number (int val, int lineN): num (val) {
	lineNumber = lineN;
}

// Copy constructor
Number::Number (const Number &other) { num = other.num; lineNumber = other.lineNumber;}

Number & Number::operator = (const Number &other) {
	if (&other != this)
		num = other.num;
		lineNumber = other.lineNumber;
}

Expression * Number::clone () { return new Number (*this); }

Value * Number::value () { return new Value(num); }

//For Boolean
Boolean::Boolean (bool val, int lineN): boo(val) {
	lineNumber = lineN;
}

Boolean::Boolean (const Boolean &other) { boo = other.boo; lineNumber = other.lineNumber;}

Boolean & Boolean::operator = (const Boolean &other) {
	if (&other != this)
		boo = other.boo;
		lineNumber = other.lineNumber;
}

Value * Boolean::value() {return new Value(boo);}

Expression * Boolean::clone() { return new Boolean(*this);}

// For Word
Word::Word (string val, int lineN): word (val) {
	lineNumber =lineN;
}

// Copy constructor
Word::Word (const Word &other) { word = other.word;}

Word & Word::operator = (const Word &other) {
	if(&other != this) {
		word = other.word;
		lineNumber = other.lineNumber;
	}
}

ObjectDef::ObjectDef(int lineN) {
	lineNumber = lineN;
}

ObjectDef * ObjectDef::clone() {
	return new ObjectDef(*this);
}

Value * ObjectDef::value(){
	ObjTable objTable;
	for(int i =0 ; i < names.size(); i++){
		objTable[names[i]] = exprs[i]->value();
	}
	Value * result = new Value(objTable);
	return result;
}

void ObjectDef::addProperty(string name, Expression* expr) {
	names.push_back(name);
	exprs.push_back(expr);
}

ObjectDef::~ObjectDef() {
	for(int i =0 ; i < exprs.size(); i++ ) {
		delete exprs[i];
	}
}

Array::Array(){
	tbl = new map<int, Value*>();
}

Array::Array(const Array &other)
{
	this->tbl = new map<int, Value*>(*other.tbl);
	this->maxIndex = other.maxIndex;
}

Array & Array::operator = (const Array &other) {
	if (&other != this)
	{
		delete this->tbl;

		this->tbl = new map<int, Value*>(*other.tbl);
		this->maxIndex = other.maxIndex;
	}
}

void Array::addElement(int index, Value* val) {
	if(index > maxIndex) {
		// To do:
		// expand array
		maxIndex = index;
	}
	(*tbl)[index] = new Value(*val);
	fprintf(stderr, "%p\n", &this->tbl);
	if(val->getType() == STRING) {
		fprintf(stderr, "Adding element, in %d with %s\n", index, (*tbl)[index]->getStr().c_str());
	} else if (val ->getType() == INT) {
		fprintf(stderr, "Adding element, in %d with %d\n", index, (*tbl)[index]->getInt());
	}
}

Value * Array::getElement(int index) {
	if(index > maxIndex) {
		//To do
		//out of bound index exception
		return new Value("out of bound", INVALID);
	} else {
		if(tbl->count(index) > 0 ) {
			Value * val = (*tbl)[index];
	fprintf(stderr, "%p\n", &this->tbl);
			if(val->getType() == STRING) {
				fprintf(stderr, "Getting element, in %d with %s\n", index, val->getStr().c_str());
			} else if (val ->getType() == INT) {
				fprintf(stderr, "Getting element, in %d with %d\n", index, val->getInt());
			} else {
			}
			return new Value (*(*tbl)[index]);
		} else {
			return new Value ("I ain't got no value", UNINIT);
		}
	}
}

Array::~Array() {
	delete tbl;
}

int Array::size(){
	return tbl->size();
}

int Array::count(int in) {
	if ( in <= maxIndex) {
		return 1;
	}
	else { return 0;}
}

ArrayDef::~ArrayDef() {
	for(int i =0; i < exprs.size(); i++ ) {
		delete exprs[i];
	}
}

ArrayDef * ArrayDef::clone(){
	return new ArrayDef(*this);
}

Value * ArrayDef::value(){
	Array array;
	for(int i = 0; i < exprs.size(); i++) {
		array.addElement(i, exprs[i]->value());
	}
	Value * result = new Value(array);
	return result;
}

void ArrayDef::addProperty(Expression * expr) {
	exprs.push_back(expr);
}

Expression * Word::clone() { return new Word (*this);}

Value * Word::value() {return new Value(word);}

ArrayVar::ArrayVar(Expression * i, Variable* var, int lineN) {
	index = i;
	variable = var;
	lineNumber = lineN;
}

void ArrayVar::setValue(Value * val){
	Value * value = variable->value();
	if( value->getType() == ARRAY) {
		Array & array = value->getArray();

		Value * v = index->value();
		int i = v ->getInt();
		delete v;
		array.addElement( i, new Value(*val));
	} else {
		fprintf(stderr, "Line %d, type violation\n", lineNumber);
	}
}

Value * ArrayVar::value(){
	Value * value = variable->value();
	if ( value->getType() == ARRAY) {
		Array & array = value->getArray();

		if(	isDeclaired() ) {
			Value * val = index->value();
			int i = val->getInt();
			delete val;
			Value * result = (array.getElement(i));
			if(result->getType() == UNINIT) {
				fprintf(stderr, "Line %d, has no value\n", lineNumber);
			}
			if( result->getType() == INVALID) {
				fprintf(stderr, "Line %d, undeclaired1\n", lineNumber);
			}
			return result;
		} else {
			//To do:
			//ERROR Message for undefined
			fprintf(stderr, "Line %d, undeclaired2\n", lineNumber);
			return new Value(UNDECLAIRED);
		}
	} else {
			fprintf(stderr, "Line %d, type violation\n", lineNumber);
			return new Value(INVALID);
	}
}

ArrayVar::ArrayVar (const ArrayVar &other) {
	if (&other != this) {
		delete variable;
		delete index;
		index = other.index->clone();
		variable = other.variable->clone();
		lineNumber = other.lineNumber;

	}
}


bool ArrayVar::isDeclaired() {
	if ( !variable->isDeclaired() ) {
		return false;
	}
	Value * value = variable->value();
	if( value->getType() == ARRAY) {
		Array & array = value->getArray();
		Value * val = index->value();
		int i = val->getInt();
		delete val;

		if(array.count(i) > 0 ) {
			return true;
		} else
		{
			return false;
		}
	} else {
		fprintf(stderr, "Line %d, type violation\n", lineNumber);
	}
	return false;
}

Variable * ArrayVar::clone() {
	return new ArrayVar(*this);

}
ObjectVar::ObjectVar(string vname, Variable * var, int lineN) {
	varName = vname;
	variable = var;
	lineNumber = lineN;
}

void ObjectVar::setValue(Value * val) {
	Value * value = variable->value();
	if ( value->getType() == OBJECT) {
		ObjTable & obj = value->getObj();
		obj[varName] = new Value(*val);
	} else
	{
		fprintf(stderr, "Line %d, type violation\n", lineNumber);
	}
}

Value * ObjectVar::value() {
	Value * value = variable->value();
	if ( value->getType() == OBJECT) {
		ObjTable & obj = value->getObj();
		if(	isDeclaired() ) {
			Value * result = new Value(*obj[varName]);
			return result;
		} else {
			//To do:
			//ERROR Message for undefined
			return new Value("undefined", INVALID);
		}
	} else {
		return new Value("type violation", INVALID);
	}
}

ObjectVar::ObjectVar (const ObjectVar &other) {
	if (&other != this) {
		delete variable;
		varName = other.varName;
		variable = other.variable->clone();
		lineNumber = other.lineNumber;

	}
}

bool ObjectVar::isDeclaired() {
	if ( !variable->isDeclaired() ) {
		return false;
	}
	Value * value = variable->value();
	if( value->getType() == OBJECT) {
		ObjTable & obj = value->getObj();
		if(obj.count(varName) > 0 ) {
			return true;
		} else
		{
			return false;
		}
	} else {
		fprintf(stderr, "Line %d, type violation\n", lineNumber);
	}
	return false;
}

Variable * ObjectVar::clone() {
	return new ObjectVar(*this);

}

ArrayDef::ArrayDef(int lineN){
	lineNumber=lineN;
}


/*
void Value::printAST() {
	fprintf(stderr, " [ Value ");
	if(varType == INT) {
		fprintf(stderr, "%d", intVal);
	}
	else if (varType == STRING) {
		fprintf(stderr, "%s", strVal);
	}
	else if (varType == OBJECT) {
		fprintf(stderr, "OJBECT");
	}
	fprintf(stderr, "]\n");
}
*/
void SimpleVar::printAST() {
	fprintf(stderr, " [ Simple %s %d ]\n", varName.c_str(), decl);
}

void ObjectVar::printAST() {
	fprintf(stderr, " [ objectVar " );
	variable->printAST();
	fprintf(stderr, " , %s ]\n", varName.c_str());
}

void ArrayDef::printAST() {
	fprintf(stderr, " [ ArrayDef ");
	bool first = true;
	for(int i = 0; i < exprs.size(); i++) {
		if(!first) {
			fprintf(stderr, " , ");
		}
		first = false;
		exprs[i] -> printAST();
	}
	fprintf(stderr, "]\n");
}

void ObjectDef::printAST() {
	fprintf(stderr, " [ objectDef ");
	bool first = true;
	for(int i = 0; i < names.size(); i++) {
		if(!first) {
			fprintf(stderr, " , ");
		}
		first = false;
		fprintf(stderr, "[ param  %s , ", names[i].c_str());
		exprs[i] -> printAST();
		fprintf(stderr, " ] \n");
	}
	fprintf(stderr, "]\n");
}

void DocumentWrite::printAST(){
	fprintf(stderr, " [ docuwrite ");
	bool first = true;
	for(int i = 0; i < WriteBuffer.size(); i++) {
		if(!first) {
			fprintf(stderr, " , ");
		}
		first = false;
		WriteBuffer[i] -> printAST();
	}
	fprintf(stderr, "]\n");
}

void Var_Decl::printAST(){
	fprintf(stderr, " [ var_decl %s ]\n", varName.c_str() );
}

void Assign::printAST() {
	fprintf(stderr, " [ Assign " ) ;
	child_left->printAST();
	fprintf(stderr, " , ");
	child_right->printAST();
	fprintf(stderr, " ] \n");
}

void Program::printAST() {
	fprintf(stderr, " [ Program ");
	bool first = true;
	for(int i = 0 ; i < nodes.size(); i++) {
		if(!first) {
			fprintf(stderr," , ");

		}
		first = false;
		nodes[i]->printAST();
	}
	fprintf(stderr, "] \n");
}

void Word::printAST() {
	fprintf(stderr, "[ word %s ]\n", word.c_str());
}

void Number::printAST() {
	fprintf(stderr, "[ num %d ]\n", num);
}

void ArrayVar::printAST() {
	fprintf(stderr, "[ arrayVar ");
	variable->printAST();
	fprintf(stderr, " , ");
	index->printAST();
	fprintf(stderr, " ] \n");
}

void Times::printAST() {

	fprintf(stderr, "[ * ");
	child_left->printAST();
	fprintf(stderr, " , ");
	child_right->printAST();
	fprintf(stderr, " ] \n");
}

void Plus::printAST() {

	fprintf(stderr, "[ + ");
	child_left->printAST();
	fprintf(stderr, " , ");
	child_right->printAST();
	fprintf(stderr, " ] \n");
}

void Minus::printAST() {

	fprintf(stderr, "[ - ");
	child_left->printAST();
	fprintf(stderr, " , ");
	child_right->printAST();
	fprintf(stderr, " ] \n");
}

void Divide::printAST() {
	fprintf(stderr, "[ / ");
	child_left->printAST();
	fprintf(stderr, " , ");
	child_right->printAST();
	fprintf(stderr, " ] \n");
}

void Comparison::printAST() {
	const char  * const tab[] = {"==", "!=", ">=", "<=", ">", "<", "&&", "||"};
	fprintf(stderr, "[ comparison %s ", tab[op]);
	child_left->printAST();
	fprintf(stderr, " , ");
	child_right->printAST();
	fprintf(stderr, " ] \n");
}

void Boolean::printAST(){
	fprintf(stderr, " [ Bool %s ]\n", boo? "true" : "false");
}
