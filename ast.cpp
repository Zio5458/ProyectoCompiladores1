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
    Unary(std::string o, Expr* e):op(std::move(o)),rhs(e){}; 
    void print(std::ostream& os,int indent) const override { 
        ind(os,indent); 
        os<<"Unary(\""<<op<<"\")\n"; 
        rhs->print(os,indent+2);
    } 
};
struct Binary : Expr { 
    std::string op; 
    std::unique_ptr<Expr> lhs,rhs; 
    Binary(Expr* l,std::string o,Expr* r):op(std::move(o)),lhs(l(),rhsr){}; 
    void print(std::ostream& os,int indent) const override { ind(os,indent); 
        os<<"Binary(\""<<op<<"\")\n"; 
        lhs->print(os,indent+2); 
        rhs->print(os,indent+2);
    } 
};
struct Call : Expr { 
    std::string callee; 
    std::vector<std::unique_ptr<Expr>> args; explicit Call(std::string c):callee(std::move(c)){}; 
    void add(Expr* e){ args.emplace_back(e);} 
    void print(std::ostream& os,int indent) const override { 
        ind(os,indent); 
        os<<"Call(\""<<callee<<"\")\n"; 
        for(auto& a:args) a->print(os,indent+2);
    } 
};
