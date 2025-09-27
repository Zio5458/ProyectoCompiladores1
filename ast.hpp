#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <memory>
using namespace std;

struct Node {
    virtual ~Node() = default;
    virtual void print(int indent = 0) const = 0;
};

struct Expr : Node {};
struct Stmt : Node {};

struct Number : Expr {
    long long value;
    Number(long long v) : value(v) {}
    void print(int indent=0) const override {
        cout << string(indent,' ') << "Number(" << value << ")\n";
    }
};

struct BoolLit : Expr {
    bool value;
    BoolLit(bool v) : value(v) {}
    void print(int indent=0) const override {
        cout << string(indent,' ') << "Bool(" << value << ")\n";
    }
};

struct Identifier : Expr {
    string name;
    Identifier(const string &n) : name(n) {}
    void print(int indent=0) const override {
        cout << string(indent,' ') << "Identifier(" << name << ")\n";
    }
};

struct Binary : Expr {
    string op;
    unique_ptr<Expr> left, right;
    Binary(Expr* l, const string &o, Expr* r) : op(o), left(l), right(r) {}
    void print(int indent=0) const override {
        cout << string(indent,' ') << "Binary(" << op << ")\n";
        left->print(indent+2);
        right->print(indent+2);
    }
};

struct Unary : Expr {
    string op;
    unique_ptr<Expr> expr;
    Unary(const string &o, Expr* e) : op(o), expr(e) {}
    void print(int indent=0) const override {
        cout << string(indent,' ') << "Unary(" << op << ")\n";
        expr->print(indent+2);
    }
};

struct LetStmt : Stmt {
    string name;
    unique_ptr<Expr> value;
    LetStmt(const string &n, Expr* v) : name(n), value(v) {}
    void print(int indent=0) const override {
        cout << string(indent,' ') << "LetStmt(" << name << ")\n";
        value->print(indent+2);
    }
};

struct ReturnStmt : Stmt {
    unique_ptr<Expr> value;
    ReturnStmt(Expr* v) : value(v) {}
    void print(int indent=0) const override {
        cout << string(indent,' ') << "ReturnStmt\n";
        if (value) value->print(indent+2);
    }
};

struct ExprStmt : Stmt {
    unique_ptr<Expr> expr;
    ExprStmt(Expr* e) : expr(e) {}
    void print(int indent=0) const override {
        cout << string(indent,' ') << "ExprStmt\n";
        if (expr) expr->print(indent+2);
    }
};

struct Block : Node {
    vector<unique_ptr<Stmt>> statements;
    void add(Stmt* s) { statements.emplace_back(s); }
    void print(int indent=0) const override {
        cout << string(indent,' ') << "Block\n";
        for (auto &s : statements) s->print(indent+2);
    }
};

struct IfStmt : Stmt {
    unique_ptr<Expr> condition;
    unique_ptr<Block> then_block;
    unique_ptr<Block> else_block;
    IfStmt(Expr* cond, Block* then_blk, Block* else_blk) : condition(cond), then_block(then_blk), else_block(else_blk) {}
    void print(int indent=0) const override {
        cout << string(indent,' ') << "IfStmt\n";
        condition->print(indent+2);
        then_block->print(indent+2);
        if (else_block) else_block->print(indent+2);
    }
};

struct Param : Node {
    string name;
    string type;
    Param(const string &n, const string &t) : name(n), type(t) {}
    void print(int indent=0) const override {
        cout << string(indent,' ') << "Param(" << name << ":" << type << ")\n";
    }
};

struct Func : Node {
    string name;
    vector<std::string> params;
    unique_ptr<Block> body;
    string ret_type;
    Func(const string &n) : name(n) {}
    void print(int indent=0) const override {
        cout << string(indent,' ') << "Func(" << name << ", ret=" << ret_type << ")\n";
        cout << string(indent+2,' ') << "Params:";
        for(auto &p : params) std::cout << " " << p;
        cout << "\n";
        if(body) body->print(indent+2);
    }
};

struct Program : Node {
    vector<unique_ptr<Func>> functions;
    void add(Func* f) { functions.emplace_back(f); }
    void print(int indent=0) const override {
        cout << "Program\n";
        for (auto &f : functions) f->print(indent+2);
    }
};

extern Program* g_program;