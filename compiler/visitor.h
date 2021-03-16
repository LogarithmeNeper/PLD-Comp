
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
    int variablesNumber = context-> declarationvar().size();
    int variableOffset = variablesNumber*4; // initializes the highest offset for the first variable
    std::map<std::string, int> symbolTable; // SymbolTable
    this->symbolTable = symbolTable; // Copy the symbolTable for the whole visitor object
    this->variableOffset = variableOffset;
    visitChildren(context);
    /*for(int i=0; i<variablesNumber-1; i++) {
      symbolTable.insert({removeLastCharFromString(context->VARIABLENF()[i]->getText()), variableOffset});
      variableOffset -=4;
    }
    symbolTable.insert({context->VARIABLE()->getText(), variableOffset});
    this->symbolTable = symbolTable; // Copy the symbolTable for the whole visitor object
    */
    return 0;
  }

  virtual antlrcpp::Any visitDeclarationSeule(ifccParser::DeclarationSeuleContext *context) override
  {
    symbolTable.insert({context->VARIABLE()->getText(), variableOffset});
    this->variableOffset -=4;
    return 0;
  }

  virtual antlrcpp::Any visitDeclarationInitialiseeConst(ifccParser::DeclarationInitialiseeConstContext *context) override
  {
    symbolTable.insert({context->VARIABLE()->getText(), variableOffset});
    this->variableOffset -=4;
    int varValue = stoi(context->CONST()->getText());
    std::cout << "\tmovl $" << varValue << ", -" << this->symbolTable[context->VARIABLE()->getText()] << "(%rbp)" << std::endl;
    return 0;
  }
  
  virtual antlrcpp::Any visitDeclarationInitialiseeVar(ifccParser::DeclarationInitialiseeVarContext *context) override
  {
    symbolTable.insert({context->VARIABLE(0)->getText(), variableOffset});
    this->variableOffset -=4;
    std::string leftVarName = context->VARIABLE(0)->getText();
    std::string rightVarName = context->VARIABLE(1)->getText();
    std::cout << "\tmovl -" << this->symbolTable[rightVarName] << "(%rbp), " << "%eax" << std::endl;
    std::cout << "\tmovl %eax, -" << this->symbolTable[leftVarName] << "(%rbp)" << std::endl;
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
    std::cout << "\tmovl -" << this->symbolTable[rightVarName] << "(%rbp), " << "%eax" << std::endl;
    std::cout << "\tmovl %eax, -" << this->symbolTable[leftVarName] << "(%rbp)" << std::endl;
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

  std::string removeLastCharFromString(std::string str) {
    return str.substr(0, str.size()-1);
  }

  protected : 
    std::map<std::string, int> symbolTable;
    int variableOffset;
};
