
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
    std::cout << ".globl	main\n"
              << " main: \n"
              << "\tpushq %rbp\n"
              << "\tmovq %rsp, %rbp\n";
    visitChildren(ctx);
    return 0;
  }

  virtual antlrcpp::Any visitRet(ifccParser::RetContext *ctx) override {
    int offsetExpr = visit(ctx->expr());
    std::cout << "\tmovl	-"
              << offsetExpr
              << "(%rbp), %eax\n"
              << "\tpopq %rbp\n"
              << "\tret\n";
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDeclaration(ifccParser::DeclarationContext *context) override
  {
    int variableOffset = 0; // initializes the offset for the first variable
    std::map<std::string, int> symbolTable; // SymbolTable
    this->symbolTable = symbolTable; // Copy the symbolTable for the whole visitor object
    this->maxOffset = variableOffset;
    visitChildren(context);
    return 0;
  }

  virtual antlrcpp::Any visitDeclarationSeuleInt(ifccParser::DeclarationSeuleIntContext *context) override
  {
    this->maxOffset -=4;
    symbolTable.insert({context->VARIABLE()->getText(), maxOffset});
    return 0;
  }

  virtual antlrcpp::Any visitDeclarationInitialiseeConstInt(ifccParser::DeclarationInitialiseeConstIntContext *context) override
  {
    this->maxOffset -=4;
    symbolTable.insert({context->VARIABLE()->getText(), maxOffset});
    int varValue = stoi(context->CONST()->getText());
    std::cout << "\tmovl $" << varValue << ", -" << this->symbolTable[context->VARIABLE()->getText()] << "(%rbp)" << std::endl;
    return 0;
  }
  
  virtual antlrcpp::Any visitDeclarationInitialiseeVarInt(ifccParser::DeclarationInitialiseeVarIntContext *context) override
  {
    this->maxOffset -=4;
    symbolTable.insert({context->VARIABLE(0)->getText(), maxOffset});
    std::string leftVarName = context->VARIABLE(0)->getText();
    std::string rightVarName = context->VARIABLE(1)->getText();
    std::cout << "\tmovl -" << this->symbolTable[rightVarName] << "(%rbp), " << "%eax" << std::endl;
    std::cout << "\tmovl %eax, -" << this->symbolTable[leftVarName] << "(%rbp)" << std::endl;
    return 0;
  }

  virtual antlrcpp::Any visitDeclarationSeuleChar(ifccParser::DeclarationSeuleCharContext *context) override
  {
    this->maxOffset -=1;
    symbolTable.insert({context->VARIABLE()->getText(), maxOffset});
    return 0;
  }

  virtual antlrcpp::Any visitDeclarationInitialiseeConstChar(ifccParser::DeclarationInitialiseeConstCharContext *context) override
  {
    this->maxOffset -=1;
    symbolTable.insert({context->VARIABLE()->getText(), maxOffset});
    int varValue = stoi(context->CONSTCHAR()->getText());
    std::cout << "\tmovl $" << varValue << ", -" << this->symbolTable[context->VARIABLE()->getText()] << "(%rbp)" << std::endl;
    return 0;
  }
  
  virtual antlrcpp::Any visitDeclarationInitialiseeVarChar(ifccParser::DeclarationInitialiseeVarCharContext *context) override
  {
    this->maxOffset -=1;
    symbolTable.insert({context->VARIABLE(0)->getText(), maxOffset});
    std::string leftVarName = context->VARIABLE(0)->getText();
    std::string rightVarName = context->VARIABLE(1)->getText();
    std::cout << "\tmovl -" << this->symbolTable[rightVarName] << "(%rbp), " << "%eax" << std::endl;
    std::cout << "\tmovl %eax, -" << this->symbolTable[leftVarName] << "(%rbp)" << std::endl;
    return 0;
  }

    virtual antlrcpp::Any visitDeclarationSeule64(ifccParser::DeclarationSeule64Context *context) override
  {
    this->maxOffset -=8;
    symbolTable.insert({context->VARIABLE()->getText(), maxOffset});
    return 0;
  }

  virtual antlrcpp::Any visitDeclarationInitialiseeConst64(ifccParser::DeclarationInitialiseeConst64Context *context) override
  {
    this->maxOffset -=8;
    symbolTable.insert({context->VARIABLE()->getText(), maxOffset});
    int varValue = stoi(context->CONST()->getText());
    std::cout << "\tmovl $" << varValue << ", -" << this->symbolTable[context->VARIABLE()->getText()] << "(%rbp)" << std::endl;
    return 0;
  }
  
  virtual antlrcpp::Any visitDeclarationInitialiseeVar64(ifccParser::DeclarationInitialiseeVar64Context *context) override
  {
    this->maxOffset -=8;
    symbolTable.insert({context->VARIABLE(0)->getText(), maxOffset});
    std::string leftVarName = context->VARIABLE(0)->getText();
    std::string rightVarName = context->VARIABLE(1)->getText();
    std::cout << "\tmovl -" << this->symbolTable[rightVarName] << "(%rbp), " << "%eax" << std::endl;
    std::cout << "\tmovl %eax, -" << this->symbolTable[leftVarName] << "(%rbp)" << std::endl;
    return 0;
  }

  virtual antlrcpp::Any visitAffectation(ifccParser::AffectationContext *context) override
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
    
    std::cout 
      << "\tmovl -"
      << offsetLeft
      << "(%rbp), %eax"
      << std::endl;
    if(ctx->children[1]->getText() == "+")
    {
      std::cout
      << "\taddl -"
      << offsetRight 
      << "(%rbp), %eax"
      << std::endl;
    } else if (ctx->children[1]->getText() == "-") {
      std::cout
      << "\tsubl -"
      << offsetRight 
      << "(%rbp), %eax"
      << std::endl;
    }
    
    return createTemporaryVariable();
  }

  virtual antlrcpp::Any visitMultExpr(ifccParser::MultExprContext *ctx) override
  {
    int offsetLeft = visit(ctx->expr(0));
    int offsetRight = visit(ctx->expr(1));
    std::cout 
      << "\tmovl -"
      << offsetRight
      << "(%rbp), %eax"
      << std::endl;
    std::cout
      << "\timull -"
      << offsetLeft
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

  /* print a map for debug
  void print_map(std::string comment, const std::map<std::string, int>& m)
  {
      std::cout << comment;
      for (const auto& [key, value] : m) {
          std::cout << key << " = " << value << "; ";
      }
      std::cout << "\n";
  }
*/

protected:
  std::map<std::string, int> symbolTable;
  int maxOffset;
};
