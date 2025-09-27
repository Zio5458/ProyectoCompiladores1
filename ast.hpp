// ast.hpp
#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <memory>

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
        std::cout << std::string(indent,' ') << "Number(" << value << ")\n";
    }
};

struct BoolLit : Expr {
    bool value;
    BoolLit(bool v) : value(v) {}
    void print(int indent=0) const override {
        std::cout << std::string(indent,' ') << "Bool(" << value << ")\n";
    }
};

struct Identifier : Expr {
    std::string name;
    Identifier(const std::string &n) : name(n) {}
    void print(int indent=0) const override {
        std::cout << std::string(indent,' ') << "Identifier(" << name << ")\n";
    }
};

struct Binary : Expr {
    std::string op;
    std::unique_ptr<Expr> left, right;
    Binary(Expr* l, const std::string &o, Expr* r) : op(o), left(l), right(r) {}
    void print(int indent=0) const override {
        std::cout << std::string(indent,' ') << "Binary(" << op << ")\n";
        left->print(indent+2);
        right->print(indent+2);
    }
};

struct Unary : Expr {
    std::string op;
    std::unique_ptr<Expr> expr;
    Unary(const std::string &o, Expr* e) : op(o), expr(e) {}
    void print(int indent=0) const override {
        std::cout << std::string(indent,' ') << "Unary(" << op << ")\n";
        expr->print(indent+2);
    }
};

struct LetStmt : Stmt {
    std::string name;
    std::unique_ptr<Expr> value;
    LetStmt(const std::string &n, Expr* v) : name(n), value(v) {}
    void print(int indent=0) const override {
        std::cout << std::string(indent,' ') << "LetStmt(" << name << ")\n";
        value->print(indent+2);
    }
};

struct ReturnStmt : Stmt {
    std::unique_ptr<Expr> value;
    ReturnStmt(Expr* v) : value(v) {}
    void print(int indent=0) const override {
        std::cout << std::string(indent,' ') << "ReturnStmt\n";
        if (value) value->print(indent+2);
    }
};

struct ExprStmt : Stmt {
    std::unique_ptr<Expr> expr;
    ExprStmt(Expr* e) : expr(e) {}
    void print(int indent=0) const override {
        std::cout << std::string(indent,' ') << "ExprStmt\n";
        if (expr) expr->print(indent+2);
    }
};

struct Block : Node {
    std::vector<std::unique_ptr<Stmt>> statements;
    void add(Stmt* s) { statements.emplace_back(s); }
    void print(int indent=0) const override {
        std::cout << std::string(indent,' ') << "Block\n";
        for (auto &s : statements) s->print(indent+2);
    }
};

struct IfStmt : Stmt {
    std::unique_ptr<Expr> condition;
    std::unique_ptr<Block> then_block;
    std::unique_ptr<Block> else_block;
    IfStmt(Expr* cond, Block* then_blk, Block* else_blk) 
        : condition(cond), then_block(then_blk), else_block(else_blk) {}
    void print(int indent=0) const override {
        std::cout << std::string(indent,' ') << "IfStmt\n";
        condition->print(indent+2);
        then_block->print(indent+2);
        if (else_block) else_block->print(indent+2);
    }
};

struct Param : Node {
    std::string name;
    std::string type;
    Param(const std::string &n, const std::string &t) : name(n), type(t) {}
    void print(int indent=0) const override {
        std::cout << std::string(indent,' ') << "Param(" << name << ":" << type << ")\n";
    }
};

struct Func : Node {
    std::string name;
    std::vector<std::string> params;
    std::unique_ptr<Block> body;
    std::string ret_type;
    Func(const std::string &n) : name(n) {}
    void print(int indent=0) const override {
        std::cout << std::string(indent,' ') << "Func(" << name << ", ret=" << ret_type << ")\n";
        std::cout << std::string(indent+2,' ') << "Params:";
        for(auto &p : params) std::cout << " " << p;
        std::cout << "\n";
        if(body) body->print(indent+2);
    }
};

struct Program : Node {
    std::vector<std::unique_ptr<Func>> functions;
    void add(Func* f) { functions.emplace_back(f); }
    void print(int indent=0) const override {
        std::cout << "Program\n";
        for (auto &f : functions) f->print(indent+2);
    }
};

extern Program* g_program;