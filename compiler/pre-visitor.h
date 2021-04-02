
// Generated from ifcc.g4 by ANTLR 4.7.2

#pragma once

#include <map>
#include <set>
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
    int variablesNumber = context-> declarationint()->declarationvarint().size();
    int variableOffset = variablesNumber*4; // initializes the highest offset for the first variable
    std::map<std::string, int> symbolTable; // SymbolTable
    this->symbolTable = symbolTable; // Copy the symbolTable for the whole visitor object
    this->variableOffset = variableOffset;
    this->maxOffset = variableOffset;
    visitChildren(context);
    return 0;
  }

  antlrcpp::Any visitDeclarationSeuleInt(ifccParser::DeclarationSeuleIntContext *context) 
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

  antlrcpp::Any visitDeclarationInitialiseeInt(ifccParser::DeclarationInitialiseeIntContext *context) 
  {
    int currentOffset = variableOffset;

    // Checks if the variable has indeed been added to the symbolTable.
    // If not, it means that that variable name is already declared.
    if(symbolTable.insert({context->VARIABLE()->getText(), variableOffset}).second == true) {
        this->variableOffset -=4;
    } else {
        std::cerr << "The variable "
                  << context->VARIABLE()->getText()
                  << " is already declared."
                  << std::endl;
        this->correctCode=false;
    };

    int exprOffset = visit(context->expr());

    // Checks if the expr is effectively in the symbolTable (see visitVarExpr)
    // Then, checks if the expr is affected, if not, prints a warning in the error output.
    if(exprOffset != -1) {
      if(affectedOffsets.count(exprOffset) == 1) {
        this->affectedOffsets.insert(currentOffset);
      } else {
        std::cerr << "WARNING : "
                  << "The variable "
                  << findVariableNameFromOffset(exprOffset)
                  << " is not yet initialized."
                  << std::endl;
      }
        
    }
    return 0;
  }

  antlrcpp::Any visitAffectation(ifccParser::AffectationContext *context) 
  {
    // Checks if the variable is declared in the symbolTable, if not prints an error to the output error.
    // Then, checks if the expr is affected, if not, prints a warning in the error output.
    std::string leftVarName = context->VARIABLE()->getText();
    if(this->symbolTable.count(leftVarName) == 1) {
        int exprOffset = visit(context->expr());
        if(exprOffset != -1) {
          if(affectedOffsets.count(exprOffset) == 1) {
            this->affectedOffsets.insert(this->symbolTable[leftVarName]);
          } else {
            std::cerr << "WARNING : "
                      << "The variable "
                      << findVariableNameFromOffset(exprOffset)
                      << " is not yet initialized."
                      << std::endl;
          }
        }
    } else {
        std::cerr << "ERROR : "
                  << "The variable " 
                  << leftVarName
                  << " is not declared."
                  << std::endl;
        this->correctCode=false;
    }
    return 0;
  }

  antlrcpp::Any visitVarExpr(ifccParser::VarExprContext *ctx) 
  {
    // Checks if the Var is declared in the symbolTable.
    // If not, prints an error to the error output.
    if(this->symbolTable.count(ctx->VARIABLE()->getText()) == 1){
        return symbolTable[ctx->VARIABLE()->getText()];
    } else {
        std::cerr << "ERROR : "
                  << "The variable " 
                  << ctx->VARIABLE()->getText()
                  << " is not declared."
                  << std::endl;
        this->correctCode=false;
        return -1;
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

  // Checks if both variables are initialized.
  // If not, sends one or two warnings to the error output.
  antlrcpp::Any visitMinusAddExpr(ifccParser::MinusAddExprContext *ctx) 
  {
    int offsetLeft = visit(ctx->expr(0));
    if(offsetLeft != -1) {
      if(affectedOffsets.count(offsetLeft) != 1) {
        std::cerr << "The variable "
              << findVariableNameFromOffset(offsetLeft)
              << " is not yet initialized."
              << std::endl;
      }
    }
    int offsetRight = visit(ctx->expr(1));
    if(offsetRight != -1) {
      if(affectedOffsets.count(offsetRight) != 1) {
        std::cerr << "The variable "
              << findVariableNameFromOffset(offsetRight)
              << " is not yet initialized."
              << std::endl;
      }
    }
    return createTemporaryVariable();
  }

  // Checks if both variables are initialized.
  // If not, sends one or two warnings to the error output.
  antlrcpp::Any visitMultExpr(ifccParser::MultExprContext *ctx) 
  {
    int offsetLeft = visit(ctx->expr(0));
    if(offsetLeft != -1) {
      if(affectedOffsets.count(offsetLeft) != 1) {
        std::cerr << "The variable "
              << findVariableNameFromOffset(offsetLeft)
              << " is not yet initialized."
              << std::endl;
      }
    }
    int offsetRight = visit(ctx->expr(1));
    if(offsetRight != -1) {
      if(affectedOffsets.count(offsetRight) != 1) {
        std::cerr << "The variable "
              << findVariableNameFromOffset(offsetRight)
              << " is not yet initialized."
              << std::endl;
      }
    }
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
    this->affectedOffsets.insert(this->maxOffset);
    return this->maxOffset;
  }

  int createTemporaryVariable() 
  {

    this->maxOffset += 4;
    this->symbolTable.insert({"tmp" + std::to_string(this->maxOffset), this->maxOffset});
    this->affectedOffsets.insert(this->maxOffset);
    return this->maxOffset;
  }

  std::string findVariableNameFromOffset(int offset) {
    for (auto it = this->symbolTable.begin(); it != symbolTable.end(); ++it) {
      if (it->second == offset) {
        return it->first;
      }   
    }
    return "";
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
  std::set<int> affectedOffsets;
  int maxOffset;
  int variableOffset;
  bool correctCode = true;
};
