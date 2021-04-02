
// Generated from ifcc.g4 by ANTLR 4.7.2

#pragma once

#include <map>
#include <algorithm>
#include <list>
#include <vector>

#include "antlr4-runtime.h"
#include "antlr4-generated/ifccBaseVisitor.h"
#include "ldconst.h"
#include "Copy.h"
#include "add.h"
#include "sub.h"
#include "mul.h"

/**
 * This class provides an empty implementation of ifccVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */

class Visitor : public ifccBaseVisitor
{
public:
  virtual antlrcpp::Any visitProg(ifccParser::ProgContext *ctx) override
  {
    this->program = new Program(); // We initialise the Program one we visit the axiom of the grammar
    this->program->add_cfg(new CFG(this->program));
    this->program->get_cfg_by_index(0)->add_bb(new BasicBlock(this->program->get_cfg_by_index(0), "main"));
    visitChildren(ctx);
    return 0;
  }

  virtual antlrcpp::Any visitRet(ifccParser::RetContext *ctx) override {
    int offsetExpr = visit(ctx->expr());
    this->program->gen_asm(cout, offsetExpr);
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDeclaration(ifccParser::DeclarationContext *context) override
  {
    int variablesNumber = context-> declarationvar().size();
    int variableOffset = variablesNumber*4; // initializes the highest offset for the first variable
    std::map<std::string, int> symbolTable; // SymbolTable
    this->symbolTable = symbolTable; // Copy the symbolTable for the whole visitor object
    this->variableOffset = variableOffset;
    this->maxOffset = variableOffset;
    visitChildren(context);
    return 0;
  }

  virtual antlrcpp::Any visitDeclarationSeule(ifccParser::DeclarationSeuleContext *context) override
  {
    symbolTable.insert({context->VARIABLE()->getText(), variableOffset});
    this->variableOffset -=4;
    return 0;
  }

  virtual antlrcpp::Any visitDeclarationInitialisee(ifccParser::DeclarationInitialiseeContext *context) override
  {
    symbolTable.insert({context->VARIABLE()->getText(), variableOffset});
    this->variableOffset -=4;
    std::string leftVarName = context->VARIABLE()->getText();
    int exprOffset = visit(context->expr());

    Copy* copyInstr = new Copy(exprOffset, this->symbolTable[leftVarName], this->program->get_cfg_by_index(0)->get_bb_by_index(0));
    IRInstr* instr = dynamic_cast<IRInstr*> (copyInstr);
    this->program->get_cfg_by_index(0)->get_bb_by_index(0)->add_IRInstr(instr);
    
    return 0;
  }

  virtual antlrcpp::Any visitAffectation(ifccParser::AffectationContext *context) override
  {
    std::string leftVarName = context->VARIABLE()->getText();
    int exprOffset = visit(context->expr());
    Copy* copyInstr = new Copy(exprOffset, this->symbolTable[leftVarName], this->program->get_cfg_by_index(0)->get_bb_by_index(0));
    IRInstr* instr = dynamic_cast<IRInstr*> (copyInstr);
    this->program->get_cfg_by_index(0)->get_bb_by_index(0)->add_IRInstr(instr);
    return 0;
  }

  virtual antlrcpp::Any visitVarExpr(ifccParser::VarExprContext *ctx) override
  {
    return symbolTable[ctx->VARIABLE()->getText()]; // returns an int
  }

  virtual antlrcpp::Any visitConstExpr(ifccParser::ConstExprContext *ctx) override
  {
    return createTemporaryFromConstant(stoi(ctx->CONST()->getText())); // returns an int
  }

  virtual antlrcpp::Any visitParExpr(ifccParser::ParExprContext *ctx) override
  {
    return visit(ctx->expr());
  }

  virtual antlrcpp::Any visitMinusAddExpr(ifccParser::MinusAddExprContext *ctx) override
  {
    int offsetLeft = visit(ctx->expr(0));
    int offsetRight = visit(ctx->expr(1));

    this->maxOffset += 4;
    this->symbolTable.insert({"tmp" + std::to_string(this->maxOffset), this->maxOffset});

    if(ctx->children[1]->getText() == "+")
    {
      Add* addInstr = new Add(offsetLeft, offsetRight, maxOffset, this->program->get_cfg_by_index(0)->get_bb_by_index(0));
      IRInstr* instr = dynamic_cast<IRInstr*> (addInstr);
      this->program->get_cfg_by_index(0)->get_bb_by_index(0)->add_IRInstr(instr);
    }
    else if(ctx->children[1]->getText() == "-")
    {
      Sub* subInstr = new Sub(offsetLeft, offsetRight, maxOffset, this->program->get_cfg_by_index(0)->get_bb_by_index(0));
      IRInstr* instr = dynamic_cast<IRInstr*> (subInstr);
      this->program->get_cfg_by_index(0)->get_bb_by_index(0)->add_IRInstr(instr);
    }

    return maxOffset;
  }

  virtual antlrcpp::Any visitMultExpr(ifccParser::MultExprContext *ctx) override
  {
    int offsetLeft = visit(ctx->expr(0));
    int offsetRight = visit(ctx->expr(1));

    this->maxOffset += 4;
    this->symbolTable.insert({"tmp" + std::to_string(this->maxOffset), this->maxOffset});

    Mul* mulInstr = new Mul(offsetLeft, offsetRight, maxOffset, this->program->get_cfg_by_index(0)->get_bb_by_index(0));
    IRInstr* instr = dynamic_cast<IRInstr*> (mulInstr);
    this->program->get_cfg_by_index(0)->get_bb_by_index(0)->add_IRInstr(instr);

    return maxOffset;
  }

  std::string removeLastCharFromString(std::string str)
  {
    return str.substr(0, str.size() - 1);
  }

  int createTemporaryFromConstant(int val) 
  {
    this->maxOffset += 4;
    this->symbolTable.insert({"tmp"+std::to_string(this->maxOffset), this->maxOffset});

    ldconst* ldconstInstr = new ldconst(val, this->maxOffset, this->program->get_cfg_by_index(0)->get_bb_by_index(0));
    IRInstr* instr = dynamic_cast<IRInstr*> (ldconstInstr);
    this->program->get_cfg_by_index(0)->get_bb_by_index(0)->add_IRInstr(instr);

    return this->maxOffset;
  }

protected:
  std::map<std::string, int> symbolTable;
  int maxOffset;
  Program* program;
  int variableOffset;
};
