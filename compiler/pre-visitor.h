
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
   antlrcpp::Any preVisitProg(ifccParser::ProgContext *ctx) 
  {
    visitChildren(ctx);
    return 0;
  }

   antlrcpp::Any preVisitRet(ifccParser::RetContext *ctx)  {
    int offsetExpr = visit(ctx->expr());
    return visitChildren(ctx);
  }

    antlrcpp::Any preVisitDeclaration(ifccParser::DeclarationContext *context) 
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

  antlrcpp::Any preVisitDeclarationSeule(ifccParser::DeclarationSeuleContext *context) 
  {
    symbolTable.insert({context->VARIABLE()->getText(), variableOffset});
    this->variableOffset -=4;
    return 0;
  }

  antlrcpp::Any preVisitDeclarationInitialiseeConst(ifccParser::DeclarationInitialiseeConstContext *context) 
  {
    symbolTable.insert({context->VARIABLE()->getText(), variableOffset});
    this->variableOffset -=4;
    int varValue = stoi(context->CONST()->getText());
    std::cout << "\tmovl $" << varValue << ", -" << this->symbolTable[context->VARIABLE()->getText()] << "(%rbp)" << std::endl;
    return 0;
  }
  
  antlrcpp::Any preVisitDeclarationInitialiseeVar(ifccParser::DeclarationInitialiseeVarContext *context) 
  {
    symbolTable.insert({context->VARIABLE(0)->getText(), variableOffset});
    this->variableOffset -=4;
    std::string leftVarName = context->VARIABLE(0)->getText();
    std::string rightVarName = context->VARIABLE(1)->getText();
    std::cout << "\tmovl -" << this->symbolTable[rightVarName] << "(%rbp), " << "%eax" << std::endl;
    std::cout << "\tmovl %eax, -" << this->symbolTable[leftVarName] << "(%rbp)" << std::endl;
    return 0;
  }

/*   antlrcpp::Any preVisitDeclaration(ifccParser::DeclarationContext *context) 
  {
    int variablesNumber = context->VARIABLE().size() + 1; // +1 for the final variable
    int variableOffset = variablesNumber * 4;               // initializes the highest offset for the first variable
    this->maxOffset = variableOffset;
    std::map<std::string, int> symbolTable; // SymbolTable
    for (int i = 0; i < variablesNumber - 1; i++)
    {
      try(symbolTable.count(removeLastCharFromString(context->VARIABLENF()[i]->getText())) == 0) {
        symbolTable.insert({removeLastCharFromString(context->VARIABLENF()[i]->getText()), variableOffset});
        variableOffset -= 4;
      } catch (int code){
        std::cerr << "The variable " 
                  << removeLastCharFromString(context->VARIABLENF()[i]->getText())
                  << " is already declared. Code : "
                  << code
                  << std::endl;
      }
      
    }
    try(symbolTable.count(context->VARIABLE()->getText()) == 0) {
        symbolTable.insert({context->VARIABLE()->getText()), variableOffset});
        variableOffset -= 4;
      } catch (int code){
        std::cerr << "The variable " 
                  << context->VARIABLE()->getText()
                  << " is already declared. Code : "
                  << code
                  << std::endl;
    symbolTable.insert({context->VARIABLE()->getText(), variableOffset});
    this->symbolTable = symbolTable; // Copy the symbolTable for the whole visitor object
    return 0;
  }
*/
   antlrcpp::Any preVisitAffectation(ifccParser::AffectationContext *context) 
  {
    std::string leftVarName = context->VARIABLE()->getText();
    if(this->symbolTable.count(leftVarName) == 1) {
        int exprOffset = visit(context->expr());
    } else {
        std::cerr << "The variable " 
                  << leftVarName
                  << " is not declared."
                  << std::endl;
    }
    return 0;
  }

   antlrcpp::Any preVisitVarExpr(ifccParser::VarExprContext *ctx) 
  {
    try{
        symbolTable[ctx->VARIABLE()->getText()] ;
        return symbolTable[ctx->VARIABLE()->getText()];
    } catch (int code) {
        std::cerr << "The variable " 
                  << ctx->VARIABLE()->getText()
                  << " is not declard. Code : "
                  << code
                  << std::endl;
    }
    return symbolTable[ctx->VARIABLE()->getText()]; // returns an int
  }

   antlrcpp::Any preVisitConstExpr(ifccParser::ConstExprContext *ctx) 
  {
    return createTemporaryFromConstant(stoi(ctx->CONST()->getText())); // returns an int
  }

   antlrcpp::Any preVisitParExpr(ifccParser::ParExprContext *ctx) 
  {
    return visit(ctx->expr());
  }

   antlrcpp::Any preVisitMinusAddExpr(ifccParser::MinusAddExprContext *ctx) 
  {
    int offsetLeft = visit(ctx->expr(0));
    int offsetRight = visit(ctx->expr(1));
    return createTemporaryVariable();
  }

   antlrcpp::Any preVisitMultExpr(ifccParser::MultExprContext *ctx) 
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
