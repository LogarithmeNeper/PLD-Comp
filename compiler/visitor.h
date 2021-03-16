
// Generated from ifcc.g4 by ANTLR 4.7.2

#pragma once

#include "antlr4-runtime.h"
#include "antlr4-generated/ifccBaseVisitor.h"

/**
 * This class provides an empty implementation of ifccVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */

// Base pointer offset for the affectations of multiple variables
inline int offsetBP = 4;

class Visitor : public ifccBaseVisitor
{
public:
  virtual antlrcpp::Any visitAxiom(ifccParser::AxiomContext *ctx) override
  {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitProg(ifccParser::ProgContext *ctx) override
  {

    int retval = stoi(ctx->CONST()->getText());
    std::cout << ".globl	main\n"
              << " main: \n"
              << "\tpushq %rbp\n"
              << "\tmovq %rsp, %rbp\n";
    visitChildren(ctx);
    std::cout << "\tmovl	$"
              << retval 
              << ", %eax\n"
              << "\tpopq %rbp\n"
              << "\tret\n";

    return 0;
  }

  virtual antlrcpp::Any visitDeclaration(ifccParser::DeclarationContext *context) override
  {
    return 0;
  }

  virtual antlrcpp::Any visitAffectation(ifccParser::AffectationContext *context) override
  {
    int varValue = stoi(context->CONST()->getText());
    std::cout << "\tmovl $" << varValue << ", -" << offsetBP << "(%rbp)" << std::endl;
    offsetBP += 4; 
    return visitChildren(context);
  }

  virtual antlrcpp::Any visitExpression(ifccParser::ExpressionContext *context) override
  {
    int constValue = stoi(context->CONST()->getText());
    std::cout << "\tmovl $" << varValue << ", -4(%rbp)" << std::endl;
    return 0;
  }

};
