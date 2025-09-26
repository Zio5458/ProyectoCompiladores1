#pragma once
#include <string>
#include <vector>
#include <memory>
#include <iostream>
using namespace std

struct Node {
    virtual ~Node() = default;
    virtual void print(ostream& os, int indent = 0;)
};
inline void ind(ostream& os, int n) {
    for (int i = 0; i < n; i++) {
        os << ' ';
    }
}

//Expresiones
struct Expr : Node {};
struct Identifier: Expr {
    string name;
    explicit Identifier(string n) : name(move(n)){};
    void print(ostream& os, int indent) const override {
        ind(os, indent);
        os << "Identifier(\""<<name<<"\")\n";
    }
};
struct Number : Expr
{
    long long value;
    expicit Number(long long v) : value(v){};
    void print(ostream& os, int indent) const override {
        ind(os, indent);
        os << "Number("<<value<<")\n";
    }
};
struct BoolLit : Expr {
    bool value;
    explicit BoolLit(bool v) : value(v){};
    void print(ostream& os, int indent) const override {
        ind(os, indent);
        os<<"Bool("<<(value?"true":"false")<<")\n";
    }
};
struct Unary : Expr { 
    string op;
    unique_ptr<Expr> rhs; 
    Unary(string o, Expr* e) : op(move(o)), rhs(e){}; 
    void print(ostream& os,int indent) const override { 
        ind(os,indent); 
        os<<"Unary(\""<<op<<"\")\n"; 
        rhs->print(os, indent+2);
    } 
};
struct Binary : Expr { 
    string op; 
    unique_ptr<Expr> lhs,rhs; 
    Binary(Expr* l,string o, Expr* r) : op(move(o)), lhs(l(), rhsr){}; 
    void print(ostream& os, int indent) const override { ind(os, indent); 
        os<<"Binary(\""<<op<<"\")\n"; 
        lhs->print(os, indent+2); 
        rhs->print(os, indent+2);
    } 
};
struct Call : Expr { 
    string callee; 
    vector<unique_ptr<Expr>> args; explicit Call(string c) : callee(move(c)){}; 
    void add(Expr* e){ 
        args.emplace_back(e);
    } 
    void print(ostream& os, int indent) const override { 
        ind(os, indent); 
        os<<"Call(\""<<callee<<"\")\n"; 
        for(auto& a : args) a->print(os, indent+2);
    } 
};

//Statements
Struct Stmt : Node {};
struct LetStmt : Stmt { 
    string name; 
    string type; 
    unique_ptr<Expr> init; 
    LetStmt(string n, string t, Expr* e) : name(move(n)), type(move(t)), init(e){}; 
    void print(ostream& os, int indent) const override { 
        ind(os, indent); 
        os<<"Let(name=\""<<name<<"\", type=\""<<type<<"\")\n"; 
        if(init) init->print(os, indent+2);
    } 
};
struct ReturnStmt : Stmt { 
    unique_ptr<Expr> expr; 
    explicit ReturnStmt(Expr* e) : expr(e){}; 
    void print(ostream& os, int indent) const override { 
        ind(os, indent); 
        os<<"Return\n"; 
        if(expr) expr->print(os, indent+2);
    } 
};
struct ExprStmt : Stmt { 
    unique_ptr<Expr> expr; 
    explicit ExprStmt(Expr* e) : expr(e){}; 
    void print(ostream& os, int indent) const override { 
        ind(os, indent); 
        os<<"ExprStmt\n"; 
        expr->print(os, indent+2);
    } 
};
struct Block : Stmt { 
    vector<unique_ptr<Stmt>> stmts; 
    void add(Stmt* s){ 
        stmts.emplace_back(s);
    } 
    void print(ostream& os, int indent) const override { 
        ind(os, indent); 
        os<<"Block\n"; 
        for(auto& s : stmts) s->print(os, indent+2);
    } 
};
struct IfStmt : Stmt { 
    unique_ptr<Expr> cond; 
    unique_ptr<Block> thenBlk; 
    unique_ptr<Block> elseBlk; 
    IfStmt(Expr* c, Block* t, Block* e) : cond(c), thenBlk(t), elseBlk(e){}; 
    void print(ostream& os, int indent) const override { 
        ind(os, indent); 
        os<<"If\n"; ind(os, indent+2); 
        os<<"Cond\n"; 
        cond->print(os, indent+4); 
        ind(os,indent+2); 
        os<<"Then\n"; 
        thenBlk->print(os, indent+4); 
        if(elseBlk){ 
            ind(os, indent+2); 
            os<<"Else\n"; 
            elseBlk->print(os, indent+4);
        } 
    } 
};
