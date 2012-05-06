#include<map>
#include<list>
#include<vector>
using namespace std;

struct Environment;
struct Expression {
  virtual Expression* eval(Environment*){
    return this;
  }
  virtual string toString()=0;
};
struct Environment{
  Environment* parent;
  map<string,Expression*> m;
  Environment():parent(0){}
  bool has(string s);
  void put(string s,Expression* e);
  Expression* get(string s);
  void show();
};
struct Null:Expression{
  virtual string toString();
};
struct ExpSequence: public Expression{
  vector<Expression*> es;
  virtual Expression* eval(Environment* e);
  virtual string toString();
};
struct BoolValue: public Expression{
  bool v;
  BoolValue(bool v):v(v){}
  virtual string toString();
};
struct IntValue:public Expression{
  int v;
  IntValue(int v):v(v){}
  virtual string toString();
};
struct Label:public Expression{
  string s;
  Label(string s):s(s){}
  virtual Expression* eval(Environment* e);
  virtual string toString();
};
struct Lambda:public Expression{
  vector<string> args;
  Expression* body;
  Environment* e;
  Lambda():e(0){}
  Lambda(Environment* e):e(e){}
  virtual Expression* eval(Environment* e);
  virtual string toString();
};
struct Pair:public Expression{
  Expression *a,*b;
  Pair(Expression*a,Expression*b):a(a),b(b){}
  virtual string toString();
};
struct Application:Expression{
  Expression* op;
  vector<Expression*> args;
  virtual string toString();
  virtual Expression* eval(Environment* e);
};
struct If:Expression{
  Expression *condition, *thenPart, *elsePart;
  virtual string toString();
  virtual Expression* eval(Environment* e);
};
struct Define:Expression{
  Label *label;
  Expression* exp;
  virtual string toString();
  virtual Expression* eval(Environment* e);
};
