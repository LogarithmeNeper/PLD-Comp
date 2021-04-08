
// Generated from ifcc.g4 by ANTLR 4.7.2

#pragma once

#include <map>
#include <algorithm>
#include <list>
#include <vector>

#include "antlr4-runtime.h"
#include "antlr4-generated/ifccBaseVisitor.h"
#include "ldconst.h"
#include "copy.h"
#include "add.h"
#include "sub.h"
#include "mul.h"
#include "program.h"
#include "basic_block.h"
#include "cfg.h"
#include "IR.h"
#include "call.h"

/**
 * This class provides an empty implementation of ifccVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */

class Visitor : public ifccBaseVisitor
{
public:
  ~Visitor() {
    delete this->program;
  }

  virtual antlrcpp::Any visitProg(ifccParser::ProgContext *ctx) override
  {
    this->program = new Program(); // We initialise the Program one we visit the axiom of the grammar
    visitChildren(ctx);
    return 0;
  }

  virtual antlrcpp::Any visitDefinitionFunction(ifccParser::DefinitionFunctionContext *ctx) override 
  {
    std::string functionName = ctx->ID(0)->getText();
    int nbArguments = ctx->ID().size()-1;
    this->program->add_cfg(new CFG(this->program, functionName, nbArguments));
    for(int i = 1; i <= nbArguments; i++)
    {
      this->program->cfgs.back()->maxOffset += 4;
      this->program->cfgs.back()->symbolTable->insert({ctx->ID(i)->getText(), this->program->cfgs.back()->maxOffset});
      
    }
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBloc(ifccParser::BlocContext *ctx) override {
    this->program->cfgs.back()->add_bb(new BasicBlock(this->program->cfgs.back()));
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitRet(ifccParser::RetContext *ctx) override {
    int offsetExpr = visit(ctx->expr());
    this->program->cfgs.back()->gen_asm_prologue(cout);
    this->program->cfgs.back()->gen_asm(cout);
    this->program->cfgs.back()->gen_asm_epilogue(cout, offsetExpr);
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDeclaration(ifccParser::DeclarationContext *context) override
  {
    visitChildren(context);
    return 0;
  }

  virtual antlrcpp::Any visitDeclarationSeuleInt(ifccParser::DeclarationSeuleIntContext *context) override
  {
    this->program->cfgs.back()->maxOffset +=4;
    this->program->cfgs.back()->getSymbolTable()->insert({context->ID()->getText(), this->program->cfgs.back()->maxOffset});
    return 0;
  }

  virtual antlrcpp::Any visitDeclarationInitialiseeInt(ifccParser::DeclarationInitialiseeIntContext *context) override
  {
    this->program->cfgs.back()->maxOffset +=4;
    this->program->cfgs.back()->getSymbolTable()->insert({context->ID()->getText(), this->program->cfgs.back()->maxOffset});
    std::string leftVarName = context->ID()->getText();
    int exprOffset = visit(context->expr());
    
    Copy* copyInstr = new Copy(exprOffset, (*this->program->cfgs.back()->getSymbolTable())[leftVarName], this->program->cfgs.back()->get_bb_by_index(0));
    IRInstr* instr = dynamic_cast<IRInstr*> (copyInstr);
    this->program->cfgs.back()->get_bb_by_index(0)->add_IRInstr(instr);

    return 0;
  }

  virtual antlrcpp::Any visitDeclarationSeuleChar(ifccParser::DeclarationSeuleCharContext *context) override
  {
    this->program->cfgs.back()->maxOffset +=1;
    this->program->cfgs.back()->getSymbolTable()->insert({context->ID()->getText(), this->program->cfgs.back()->maxOffset});
    return 0;
  }

  virtual antlrcpp::Any visitDeclarationInitialiseeChar(ifccParser::DeclarationInitialiseeCharContext *context) override
  {
    this->program->cfgs.back()->maxOffset +=1;
    this->program->cfgs.back()->getSymbolTable()->insert({context->ID()->getText(), this->program->cfgs.back()->maxOffset});
    std::string leftVarName = context->ID()->getText();
    int exprOffset = visit(context->expr());
    
    Copy* copyInstr = new Copy(exprOffset, (*this->program->cfgs.back()->getSymbolTable())[leftVarName], this->program->cfgs.back()->get_bb_by_index(0));
    IRInstr* instr = dynamic_cast<IRInstr*> (copyInstr);
    this->program->cfgs.back()->get_bb_by_index(0)->add_IRInstr(instr);
    return 0;
  }

    virtual antlrcpp::Any visitDeclarationSeule64(ifccParser::DeclarationSeule64Context *context) override
  {
    this->program->cfgs.back()->maxOffset +=8;
    this->program->cfgs.back()->getSymbolTable()->insert({context->ID()->getText(), this->program->cfgs.back()->maxOffset});
    return 0;
  }
 
  virtual antlrcpp::Any visitDeclarationInitialisee64(ifccParser::DeclarationInitialisee64Context *context) override
  {
    this->program->cfgs.back()->maxOffset +=8;
    this->program->cfgs.back()->getSymbolTable()->insert({context->ID()->getText(), this->program->cfgs.back()->maxOffset});
    std::string leftVarName = context->ID()->getText();
    int exprOffset = visit(context->expr());
    
    Copy* copyInstr = new Copy(exprOffset, (*this->program->cfgs.back()->getSymbolTable())[leftVarName], this->program->cfgs.back()->get_bb_by_index(0));
    IRInstr* instr = dynamic_cast<IRInstr*> (copyInstr);
    this->program->cfgs.back()->get_bb_by_index(0)->add_IRInstr(instr);
    return 0;
  }

  virtual antlrcpp::Any visitAffectation(ifccParser::AffectationContext *context) override
  {
    std::string leftVarName = context->ID()->getText();
    int exprOffset = visit(context->expr());
    Copy* copyInstr = new Copy(exprOffset, (*this->program->cfgs.back()->getSymbolTable())[leftVarName], this->program->cfgs.back()->get_bb_by_index(0));
    IRInstr* instr = dynamic_cast<IRInstr*> (copyInstr);
    this->program->cfgs.back()->get_bb_by_index(0)->add_IRInstr(instr);
    return 0;
  }

  virtual antlrcpp::Any visitVarExpr(ifccParser::VarExprContext *ctx) override
  {
    return (*(this->program->cfgs.back()->getSymbolTable()))[ctx->ID()->getText()]; // returns an int
  }

  virtual antlrcpp::Any visitConstExpr(ifccParser::ConstExprContext *ctx) override
  {
    return createTemporaryFromConstant(stoi(ctx->CONST()->getText())); // returns an int
  }

  virtual antlrcpp::Any visitParExpr(ifccParser::ParExprContext *ctx) override
  {
    return visit(ctx->expr());
  }

  virtual antlrcpp::Any visitConstCharExpr(ifccParser::ConstCharExprContext *ctx) override
  {
    std::string recup = ctx->CONSTCHAR()->getText();
    char charRecup = recup.at(1);
    return createTemporaryFromConstant(charRecup);
  }

  virtual antlrcpp::Any visitMinusAddExpr(ifccParser::MinusAddExprContext *ctx) override
  {
    int offsetLeft = visit(ctx->expr(0));
    int offsetRight = visit(ctx->expr(1));

    this->program->cfgs.back()->maxOffset += 4;
    this->program->cfgs.back()->getSymbolTable()->insert({"tmp" + std::to_string(this->program->cfgs.back()->maxOffset), this->program->cfgs.back()->maxOffset});

    if(ctx->children[1]->getText() == "+")
    {
      Add* addInstr = new Add(offsetLeft, offsetRight, this->program->cfgs.back()->maxOffset, this->program->cfgs.back()->get_bb_by_index(0));
      IRInstr* instr = dynamic_cast<IRInstr*> (addInstr);
      this->program->cfgs.back()->get_bb_by_index(0)->add_IRInstr(instr);
    }
    else if(ctx->children[1]->getText() == "-")
    {
      Sub* subInstr = new Sub(offsetLeft, offsetRight, this->program->cfgs.back()->maxOffset, this->program->cfgs.back()->get_bb_by_index(0));
      IRInstr* instr = dynamic_cast<IRInstr*> (subInstr);
      this->program->cfgs.back()->get_bb_by_index(0)->add_IRInstr(instr);
    }

    return this->program->cfgs.back()->maxOffset;
  }

  virtual antlrcpp::Any visitMultExpr(ifccParser::MultExprContext *ctx) override
  {
    int offsetLeft = visit(ctx->expr(0));
    int offsetRight = visit(ctx->expr(1));

    this->program->cfgs.back()->maxOffset += 4;
    this->program->cfgs.back()->getSymbolTable()->insert({"tmp" + std::to_string(this->program->cfgs.back()->maxOffset), this->program->cfgs.back()->maxOffset});

    Mul* mulInstr = new Mul(offsetLeft, offsetRight, this->program->cfgs.back()->maxOffset, this->program->cfgs.back()->get_bb_by_index(0));
    IRInstr* instr = dynamic_cast<IRInstr*> (mulInstr);
    this->program->cfgs.back()->get_bb_by_index(0)->add_IRInstr(instr);

    return this->program->cfgs.back()->maxOffset;
  }

  virtual antlrcpp::Any visitFunctionCallSeul(ifccParser::FunctionCallSeulContext *ctx) override
  {
    int offsetArg = visit(ctx->expr(0));
    std::string functionName = ctx->ID()->getText();
    if(functionName == "putchar")
    {
      functionName = "putchar@PLT";
    }
    this->program->cfgs.back()->maxOffset += 4;
    this->program->cfgs.back()->getSymbolTable()->insert({"tmp" + std::to_string(this->program->cfgs.back()->maxOffset), this->program->cfgs.back()->maxOffset});
    Call* callInstr = new Call(offsetArg, functionName, this->program->cfgs.back()->maxOffset, this->program->cfgs.back()->get_bb_by_index(0));
    IRInstr* instr = dynamic_cast<IRInstr*> (callInstr);
    this->program->cfgs.back()->get_bb_by_index(0)->add_IRInstr(instr);
    return this->program->cfgs.back()->maxOffset;

  }

  std::string removeLastCharFromString(std::string str)
  {
    return str.substr(0, str.size() - 1);
  }

  int createTemporaryFromConstant(int val) 
  {
    this->program->cfgs.back()->maxOffset += 4;
    this->program->cfgs.back()->getSymbolTable()->insert({"tmp"+std::to_string(this->program->cfgs.back()->maxOffset), this->program->cfgs.back()->maxOffset});

    ldconst* ldconstInstr = new ldconst(val, this->program->cfgs.back()->maxOffset, this->program->cfgs.back()->get_bb_by_index(0));
    IRInstr* instr = dynamic_cast<IRInstr*> (ldconstInstr);
    this->program->cfgs.back()->get_bb_by_index(0)->add_IRInstr(instr);

    return this->program->cfgs.back()->maxOffset;
  }

  int createTemporaryFromConstant(char val) 
  {
    val = (int) val;
    this->program->cfgs.back()->maxOffset += 1;
    this->program->cfgs.back()->getSymbolTable()->insert({"tmp"+std::to_string(this->program->cfgs.back()->maxOffset), this->program->cfgs.back()->maxOffset});

    ldconst* ldconstInstr = new ldconst(val, this->program->cfgs.back()->maxOffset, this->program->cfgs.back()->get_bb_by_index(0));
    IRInstr* instr = dynamic_cast<IRInstr*> (ldconstInstr);
    this->program->cfgs.back()->get_bb_by_index(0)->add_IRInstr(instr);

    return this->program->cfgs.back()->maxOffset;
  }

protected:
  Program* program;
};
