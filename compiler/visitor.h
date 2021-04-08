
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
#include "cmp_eq.h"
#include "write_label.h"

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

  /**
   * VISITORS METHODS
   */

  virtual antlrcpp::Any visitProg(ifccParser::ProgContext *ctx) override
  {
    int variableOffset = 0; // initializes the offset for the first variable
    this->maxOffset = variableOffset;
    this->program = new Program(); // We initialise the Program one we visit the axiom of the grammar
    this->program->add_cfg(new CFG(this->program));
    //this->program->get_cfg_by_index(0)->add_bb(new BasicBlock(this->program->get_cfg_by_index(0), "main"));
    visitChildren(ctx);
    return 0;
  }

  virtual antlrcpp::Any visitBloc(ifccParser::BlocContext *ctx) override {
    this->program->get_cfg_by_index(0)->add_bb(new BasicBlock(this->program->get_cfg_by_index(0), "main"));
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitRet(ifccParser::RetContext *ctx) override {
    int offsetExpr = visit(ctx->expr());
    this->program->gen_asm(cout, offsetExpr);
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDeclaration(ifccParser::DeclarationContext *context) override
  {
    visitChildren(context);
    return 0;
  }

  virtual antlrcpp::Any visitDeclarationSeuleInt(ifccParser::DeclarationSeuleIntContext *context) override
  {
    this->maxOffset +=4;
    this->program->get_cfg_by_index(0)->getSymbolTable()->insert({context->ID()->getText(), maxOffset});
    this->program->get_cfg_by_index(0)->getTypeTable()->insert({context->ID()->getText(), "int"});
    return 0;
  }

  virtual antlrcpp::Any visitDeclarationInitialiseeInt(ifccParser::DeclarationInitialiseeIntContext *context) override
  {
    this->maxOffset +=4;
    this->program->get_cfg_by_index(0)->getSymbolTable()->insert({context->ID()->getText(), maxOffset});
    this->program->get_cfg_by_index(0)->getTypeTable()->insert({context->ID()->getText(), "int"});
    std::string leftVarName = context->ID()->getText();
    int exprOffset = visit(context->expr());
    
    Copy* copyInstr = new Copy(exprOffset, (*this->program->get_cfg_by_index(0)->getSymbolTable())[leftVarName], leftVarName, this->program->get_cfg_by_index(0)->get_bb_by_index(0));
    IRInstr* instr = dynamic_cast<IRInstr*> (copyInstr);
    this->program->get_cfg_by_index(0)->get_bb_by_index(0)->add_IRInstr(instr);

    return 0;
  }

  virtual antlrcpp::Any visitDeclarationSeuleChar(ifccParser::DeclarationSeuleCharContext *context) override
  {
    this->maxOffset +=1;
    this->program->get_cfg_by_index(0)->getSymbolTable()->insert({context->ID()->getText(), maxOffset});
    this->program->get_cfg_by_index(0)->getTypeTable()->insert({context->ID()->getText(), "char"});
    return 0;
  }

  virtual antlrcpp::Any visitDeclarationInitialiseeChar(ifccParser::DeclarationInitialiseeCharContext *context) override
  {
    this->maxOffset +=1;
    this->program->get_cfg_by_index(0)->getSymbolTable()->insert({context->ID()->getText(), maxOffset});
    this->program->get_cfg_by_index(0)->getTypeTable()->insert({context->ID()->getText(), "char"});
    std::string leftVarName = context->ID()->getText();
    int exprOffset = visit(context->expr());
    
    Copy* copyInstr = new Copy(exprOffset, (*this->program->get_cfg_by_index(0)->getSymbolTable())[leftVarName], leftVarName, this->program->get_cfg_by_index(0)->get_bb_by_index(0));
    IRInstr* instr = dynamic_cast<IRInstr*> (copyInstr);
    this->program->get_cfg_by_index(0)->get_bb_by_index(0)->add_IRInstr(instr);
    return 0;
  }

    virtual antlrcpp::Any visitDeclarationSeule64(ifccParser::DeclarationSeule64Context *context) override
  {
    this->maxOffset +=8;
    this->program->get_cfg_by_index(0)->getSymbolTable()->insert({context->ID()->getText(), maxOffset});
    this->program->get_cfg_by_index(0)->getTypeTable()->insert({context->ID()->getText(), "int64"});
    return 0;
  }
 
  virtual antlrcpp::Any visitDeclarationInitialisee64(ifccParser::DeclarationInitialisee64Context *context) override
  {
    this->maxOffset +=8;
    this->program->get_cfg_by_index(0)->getSymbolTable()->insert({context->ID()->getText(), maxOffset});
    this->program->get_cfg_by_index(0)->getTypeTable()->insert({context->ID()->getText(), "int64"});
    std::string leftVarName = context->ID()->getText();
    int exprOffset = visit(context->expr());
    
    Copy* copyInstr = new Copy(exprOffset, (*this->program->get_cfg_by_index(0)->getSymbolTable())[leftVarName], leftVarName, this->program->get_cfg_by_index(0)->get_bb_by_index(0));
    IRInstr* instr = dynamic_cast<IRInstr*> (copyInstr);
    this->program->get_cfg_by_index(0)->get_bb_by_index(0)->add_IRInstr(instr);
    return 0;
  }

  virtual antlrcpp::Any visitAffectation(ifccParser::AffectationContext *context) override
  {
    std::string leftVarName = context->ID()->getText();
    int exprOffset = visit(context->expr());
    Copy* copyInstr = new Copy(exprOffset, (*this->program->get_cfg_by_index(0)->getSymbolTable())[leftVarName], leftVarName, this->program->get_cfg_by_index(0)->get_bb_by_index(0));
    IRInstr* instr = dynamic_cast<IRInstr*> (copyInstr);
    this->program->get_cfg_by_index(0)->get_bb_by_index(0)->add_IRInstr(instr);
    return 0;
  }

  virtual antlrcpp::Any visitVarExpr(ifccParser::VarExprContext *ctx) override
  {
    return (*(this->program->get_cfg_by_index(0)->getSymbolTable()))[ctx->ID()->getText()]; // returns an int
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

    this->maxOffset += 4;
    this->program->get_cfg_by_index(0)->getSymbolTable()->insert({"tmp" + std::to_string(this->maxOffset), this->maxOffset});

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
    this->program->get_cfg_by_index(0)->getSymbolTable()->insert({"tmp" + std::to_string(this->maxOffset), this->maxOffset});

    Mul* mulInstr = new Mul(offsetLeft, offsetRight, maxOffset, this->program->get_cfg_by_index(0)->get_bb_by_index(0));
    IRInstr* instr = dynamic_cast<IRInstr*> (mulInstr);
    this->program->get_cfg_by_index(0)->get_bb_by_index(0)->add_IRInstr(instr);

    return maxOffset;
  }

  virtual antlrcpp::Any visitFunctionCallSeul(ifccParser::FunctionCallSeulContext *ctx) override
  {
    // if(ctx->expr()->size() == 1){
    int offsetArg = visit(ctx->expr(0));
    std::string functionName = ctx->ID()->getText();
    if(functionName == "putchar")
    {
      functionName = "putchar@PLT";
    }
    Call* callInstr = new Call(offsetArg, functionName, this->program->get_cfg_by_index(0)->get_bb_by_index(0));
    IRInstr* instr = dynamic_cast<IRInstr*> (callInstr);
    this->program->get_cfg_by_index(0)->get_bb_by_index(0)->add_IRInstr(instr);
    return 0;

  }

  virtual antlrcpp::Any visitIfStatement(ifccParser::IfStatementContext *ctx) override {
    visit(ctx->condition());
    visit(ctx->bloc());

    Write_label* write_labelInstr = new Write_label(".L2", this->program->get_cfg_by_index(0)->get_bb_by_index(0));
    IRInstr* instr = dynamic_cast<IRInstr*> (write_labelInstr);
    this->program->get_cfg_by_index(0)->get_bb_by_index(0)->add_IRInstr(instr);
    return 0;
  }

  virtual antlrcpp::Any visitEqualComparison(ifccParser::EqualComparisonContext *ctx) override {
    int offsetLeft = visit(ctx->expr(0));
    int offsetRight = visit(ctx->expr(1));
    std::string labelDestination = ".L2";

    Cmp_eq* cmp_eqInstr = new Cmp_eq(offsetLeft, offsetRight, ".L2", "==", this->program->get_cfg_by_index(0)->get_bb_by_index(0));
    IRInstr* instr = dynamic_cast<IRInstr*> (cmp_eqInstr);
    this->program->get_cfg_by_index(0)->get_bb_by_index(0)->add_IRInstr(instr);
    return 0;
  }

  virtual antlrcpp::Any visitNotEqualComparison(ifccParser::NotEqualComparisonContext *ctx) override {
    int offsetLeft = visit(ctx->expr(0));
    int offsetRight = visit(ctx->expr(1));
    std::string labelDestination = ".L2";

    Cmp_eq* cmp_eqInstr = new Cmp_eq(offsetLeft, offsetRight, ".L2", "!=", this->program->get_cfg_by_index(0)->get_bb_by_index(0));
    IRInstr* instr = dynamic_cast<IRInstr*> (cmp_eqInstr);
    this->program->get_cfg_by_index(0)->get_bb_by_index(0)->add_IRInstr(instr);
    return 0;
  }

  virtual antlrcpp::Any visitLowerComparison(ifccParser::LowerComparisonContext *ctx) override {
    int offsetLeft = visit(ctx->expr(0));
    int offsetRight = visit(ctx->expr(1));
    std::string labelDestination = ".L2";

    Cmp_eq* cmp_eqInstr = new Cmp_eq(offsetLeft, offsetRight, ".L2", "<", this->program->get_cfg_by_index(0)->get_bb_by_index(0));
    IRInstr* instr = dynamic_cast<IRInstr*> (cmp_eqInstr);
    this->program->get_cfg_by_index(0)->get_bb_by_index(0)->add_IRInstr(instr);
    return 0;
  }

  virtual antlrcpp::Any visitGreaterComparison(ifccParser::GreaterComparisonContext *ctx) override {
    int offsetLeft = visit(ctx->expr(0));
    int offsetRight = visit(ctx->expr(1));
    std::string labelDestination = ".L2";

    Cmp_eq* cmp_eqInstr = new Cmp_eq(offsetLeft, offsetRight, ".L2", ">", this->program->get_cfg_by_index(0)->get_bb_by_index(0));
    IRInstr* instr = dynamic_cast<IRInstr*> (cmp_eqInstr);
    this->program->get_cfg_by_index(0)->get_bb_by_index(0)->add_IRInstr(instr);
    return 0;
  }
  


  /**
   * UTIL METHODS
   */

  std::string removeLastCharFromString(std::string str)
  {
    return str.substr(0, str.size() - 1);
  }

  int createTemporaryFromConstant(int val) 
  {
    this->maxOffset += 4;
    std::string temporaryName = "tmp"+std::to_string(this->maxOffset);
    this->program->get_cfg_by_index(0)->getSymbolTable()->insert({"tmp"+std::to_string(this->maxOffset), this->maxOffset});
    this->program->get_cfg_by_index(0)->getTypeTable()->insert({"tmp"+std::to_string(this->maxOffset), "int"});
    ldconst* ldconstInstr = new ldconst(val, this->maxOffset, temporaryName, this->program->get_cfg_by_index(0)->get_bb_by_index(0));
    IRInstr* instr = dynamic_cast<IRInstr*> (ldconstInstr);
    this->program->get_cfg_by_index(0)->get_bb_by_index(0)->add_IRInstr(instr);

    return this->maxOffset;
  }

  int createTemporaryFromConstant(char val) 
  {
    //val = (int) val;
    this->maxOffset += 1;
    std::string temporaryName = "tmp"+std::to_string(this->maxOffset);
    this->program->get_cfg_by_index(0)->getSymbolTable()->insert({"tmp"+std::to_string(this->maxOffset), this->maxOffset});
    this->program->get_cfg_by_index(0)->getTypeTable()->insert({"tmp"+std::to_string(this->maxOffset), "char"});
    ldconst* ldconstInstr = new ldconst(val, this->maxOffset, temporaryName, this->program->get_cfg_by_index(0)->get_bb_by_index(0));
    IRInstr* instr = dynamic_cast<IRInstr*> (ldconstInstr);
    this->program->get_cfg_by_index(0)->get_bb_by_index(0)->add_IRInstr(instr);

    return this->maxOffset;
  }

protected:
  int maxOffset;
  Program* program;
};
