
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

class PreVisitor : public ifccBaseVisitor
{
public:
   antlrcpp::Any visitProg(ifccParser::ProgContext *ctx) 
  {
    visitChildren(ctx);
    return 0;
  }

   antlrcpp::Any visitRet(ifccParser::RetContext *ctx)  {
    int offsetExpr = visit(ctx->expr());
    return visitChildren(ctx);
  }

    antlrcpp::Any visitDeclaration(ifccParser::DeclarationContext *context) 
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

  antlrcpp::Any visitDeclarationSeule(ifccParser::DeclarationSeuleContext *context) 
  {
    if(this->symbolTable.insert({context->VARIABLE()->getText(), variableOffset}).second == true) {
        this->variableOffset -=4;
    } else {
        std::cerr << "The variable "
                  << context->VARIABLE()->getText()
                  << " is already declared."
                  << std::endl;
        this->correctCode=false;
    };

    return 0;
  }

  antlrcpp::Any visitDeclarationInitialiseeConst(ifccParser::DeclarationInitialiseeConstContext *context) 
  {
    if(symbolTable.insert({context->VARIABLE()->getText(), variableOffset}).second == true) {
        this->variableOffset -=4;
    } else {
        std::cerr << "The variable "
                  << context->VARIABLE()->getText()
                  << " is already declared."
                  << std::endl;
        this->correctCode=false;
    };
    return 0;
  }
  
  antlrcpp::Any visitDeclarationInitialiseeVar(ifccParser::DeclarationInitialiseeVarContext *context) 
  {
    std::string leftVarName = context->VARIABLE(0)->getText();
    std::string rightVarName = context->VARIABLE(1)->getText();
    if(symbolTable.insert({leftVarName, variableOffset}).second == true) {
        this->variableOffset -=4;
    } else {
        std::cerr << "The variable "
                  << leftVarName
                  << " is already declared."
                  << std::endl;
        this->correctCode=false;
    };
    if(symbolTable.find(rightVarName) == symbolTable.end()) {
      std::cerr << "The variable "
                  << rightVarName
                  << " doesn't exist."
                  << std::endl;
      this->correctCode=false;
    }
    return 0;
  }

   antlrcpp::Any visitAffectation(ifccParser::AffectationContext *context) 
  {
    std::string leftVarName = context->VARIABLE()->getText();
    if(this->symbolTable.count(leftVarName) == 1) {
        int exprOffset = visit(context->expr());
    } else {
        std::cerr << "The variable " 
                  << leftVarName
                  << " is not declared."
                  << std::endl;
        this->correctCode=false;
    }
    return 0;
  }

   antlrcpp::Any visitVarExpr(ifccParser::VarExprContext *ctx) 
  {
    if(this->symbolTable.count(ctx->VARIABLE()->getText()) == 1){
        return symbolTable[ctx->VARIABLE()->getText()];
    } else {
        std::cerr << "The variable " 
                  << ctx->VARIABLE()->getText()
                  << " is not declared."
                  << std::endl;
        this->correctCode=false;
    }
    return symbolTable[ctx->VARIABLE()->getText()]; // returns an int
  }

   antlrcpp::Any visitConstExpr(ifccParser::ConstExprContext *ctx) 
  {
    return createTemporaryFromConstant(stoi(ctx->CONST()->getText())); // returns an int
  }

   antlrcpp::Any visitParExpr(ifccParser::ParExprContext *ctx) 
  {
    return visit(ctx->expr());
  }

   antlrcpp::Any visitMinusAddExpr(ifccParser::MinusAddExprContext *ctx) 
  {
    int offsetLeft = visit(ctx->expr(0));
    int offsetRight = visit(ctx->expr(1));
    return createTemporaryVariable();
  }

   antlrcpp::Any visitMultExpr(ifccParser::MultExprContext *ctx) 
  {
    int offsetLeft = visit(ctx->expr(0));
    int offsetRight = visit(ctx->expr(1));
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
    return this->maxOffset;
  }

  int createTemporaryVariable() 
  {

    this->maxOffset += 4;
    this->symbolTable.insert({"tmp" + std::to_string(this->maxOffset), this->maxOffset});
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

  bool getCorrectCode() {
      return this->correctCode;
  }

protected:
  std::map<std::string, int> symbolTable;
  int maxOffset;
  int variableOffset;
  bool correctCode = true;
};
