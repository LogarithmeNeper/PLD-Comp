
// Generated from ifcc.g4 by ANTLR 4.7.2

#pragma once

#include <map>
#include <algorithm>

#include "antlr4-runtime.h"
#include "antlr4-generated/ifccBaseVisitor.h"

/**
 * This class provides an empty implementation of ifccVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */

class Visitor : public ifccBaseVisitor
{
public:
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
    int variablesNumber = context->VARIABLENF().size() + 1; // +1 for the final variable
    int variableOffset = variablesNumber * 4;               // initializes the highest offset for the first variable
    this->maxOffset = variableOffset;
    std::map<std::string, int> symbolTable; // SymbolTable
    for (int i = 0; i < variablesNumber - 1; i++)
    {
      symbolTable.insert({removeLastCharFromString(context->VARIABLENF()[i]->getText()), variableOffset});
      variableOffset -= 4;
    }
    symbolTable.insert({context->VARIABLE()->getText(), variableOffset});
    this->symbolTable = symbolTable; // Copy the symbolTable for the whole visitor object
    return 0;
  }

  virtual antlrcpp::Any visitConstAffectation(ifccParser::ConstAffectationContext *context) override
  {
    int varValue = stoi(context->CONST()->getText());
    std::cout << "\tmovl $" << varValue << ", -" << this->symbolTable[context->VARIABLE()->getText()] << "(%rbp)" << std::endl;
    return 0;
  }

  virtual antlrcpp::Any visitVarToVarAffectation(ifccParser::VarToVarAffectationContext *context) override
  {
    std::string leftVarName = context->VARIABLE(0)->getText();
    std::string rightVarName = context->VARIABLE(1)->getText();
    std::cout << "\tmovl -" << this->symbolTable[rightVarName] << "(%rbp), "
              << "%eax" << std::endl;
    std::cout << "\tmovl %eax, -" << this->symbolTable[leftVarName] << "(%rbp)" << std::endl;
    return 0;
  }

  virtual antlrcpp::Any visitExprAffectation(ifccParser::ExprAffectationContext *context) override
  {
    std::string leftVarName = context->VARIABLE()->getText();
    int exprOffset = visit(context->expr());
    std::cout << "\tmovl -"
              << exprOffset
              << "(%rbp), %eax"
              << std::endl;
    std::cout << "\tmovl %eax, -"
              << this->symbolTable[leftVarName]
              << "(%rbp)"
              << std::endl;
    return 0;
  }

  /*  print a map for debug
  void print_map(std::string comment, const std::map<std::string, int>& m)
  {
      std::cout << comment;
      for (const auto& [key, value] : m) {
          std::cout << key << " = " << value << "; ";
      }
      std::cout << "\n";
  }
*/

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

  virtual antlrcpp::Any visitAddExpr(ifccParser::AddExprContext *ctx) override
  {
    int offsetLeft = visit(ctx->expr(0));
    int offsetRight = visit(ctx->expr(1));
    std::cout 
      << "\tmovl -"
      << offsetLeft
      << "(%rbp), %eax"
      << std::endl;
    std::cout
      << "\taddl -"
      << offsetRight 
      << "(%rbp), %eax"
      << std::endl;
    return createTemporaryVariable();
  }

  virtual antlrcpp::Any visitMultExpr(ifccParser::MultExprContext *ctx) override
  {
    int offsetLeft = visitChildren(ctx->expr(0));
    int offsetRight = visitChildren(ctx->expr(1));
    std::cout 
      << "\tmovl -"
      << offsetRight
      << "(%rbp), %eax"
      << std::endl;
    std::cout
      << "imull -"
      << offsetLeft
      << "(%rbp), %eax"
      << std::endl;
    return createTemporaryVariable();
  }

  virtual antlrcpp::Any visitSublExpr(ifccParser::SublExprContext *ctx) override
  {
    int offsetLeft = visit(ctx->expr(0));
    int offsetRight = visit(ctx->expr(1));
    std::cout 
      << "\tmovl -"
      << offsetLeft
      << "(%rbp), %eax"
      << std::endl;
    std::cout
      << "subl -"
      << offsetRight
      << "(%rbp), %eax"
      << std::endl;
    return createTemporaryVariable();
  }

  std::string removeLastCharFromString(std::string str)
  {
    return str.substr(0, str.size() - 1);
  }

  int createTemporaryFromConstant(int val) 
  {
    this->maxOffset += 4;
    this->symbolTable.insert({"tmp"+std::to_string(this->maxOffset), this->maxOffset});
    std::cout
        << "\tmovl $" 
        << val
        << ", -" 
        << this->maxOffset 
        << "(%rbp)" 
        << std::endl;
    return this->maxOffset;
  }

  int createTemporaryVariable() 
  {

    this->maxOffset += 4;
    this->symbolTable.insert({"tmp" + std::to_string(this->maxOffset), this->maxOffset});
    std::cout
        << "\tmovl %eax, -" 
        << this->maxOffset 
        << "(%rbp)" 
        << std::endl;
    return this->maxOffset;
  }

protected:
  std::map<std::string, int> symbolTable;
  int maxOffset;
};
