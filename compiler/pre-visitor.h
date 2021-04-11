
// Generated from ifcc.g4 by ANTLR 4.7.2

#pragma once

#include <map>
#include <set>
#include <algorithm>

#include "antlr4-runtime.h"
#include "antlr4-generated/ifccBaseVisitor.h"
#include "cfg.h"
#include "program.h"

/**
 * This class provides an empty implementation of ifccVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */

class PreVisitor : public ifccBaseVisitor
{
public:
  antlrcpp::Any visitProg(ifccParser::ProgContext *context)
  {
    this->program = new Program();
    visitChildren(context);
    return 0;
  }

  antlrcpp::Any visitDefinitionFunction(ifccParser::DefinitionFunctionContext *ctx)
  {
    
    std::string functionName = ctx->ID(0)->getText();
    int nbArguments = ctx->ID().size()-1;
    this->program->cfgs.push_back(new CFG(this->program, functionName, nbArguments));
    for(int i = 1; i <= nbArguments; i++ )
    {
      if (this->program->cfgs.back()->symbolTable->insert({ctx->ID(i)->getText(), this->program->cfgs.back()->maxOffset}).second == true)
      {
        this->program->cfgs.back()->maxOffset += 4;
      }

    }
    
    visitChildren(ctx);
    return 0;
  }

  antlrcpp::Any visitRet(ifccParser::RetContext *context)
  {
    int offsetExpr = visit(context->expr());
    return visitChildren(context);
  }

  antlrcpp::Any visitDeclaration(ifccParser::DeclarationContext *context)
  {
    visitChildren(context);
    return 0;
  }

  antlrcpp::Any visitDeclarationSeuleInt(ifccParser::DeclarationSeuleIntContext *context)
  {
    if (this->program->cfgs.back()->symbolTable->insert({context->ID()->getText(), this->program->cfgs.back()->maxOffset}).second == true)
    {
      this->program->cfgs.back()->maxOffset += 4;
    }
    else
    {
      printAlreadyDeclaredError(context->ID()->getText(), context->start->getLine());
      this->correctCode = false;
    };
    return 0;
  }

  antlrcpp::Any visitDeclarationInitialiseeInt(ifccParser::DeclarationInitialiseeIntContext *context)
  {
    int currentOffset = this->program->cfgs.back()->maxOffset;

    // Checks if the variable has indeed been added to the symbolTable.
    // If not, it means that that variable name is already declared.
    if (this->program->cfgs.back()->symbolTable->insert({context->ID()->getText(), this->program->cfgs.back()->maxOffset}).second == true)
    {
      this->program->cfgs.back()->maxOffset += 4;
    }
    else
    {
      printAlreadyDeclaredError(context->ID()->getText(), context->start->getLine());
      this->correctCode = false;
    };

    int exprOffset = visit(context->expr());

    // Checks if the expr is effectively in the symbolTable (see visitVarExpr)
    // Then, checks if the expr is affected, if not, prints a warning in the error output.
    if (exprOffset != -1)
    {
      if (affectedOffsets.count(exprOffset) == 1)
      {
        this->affectedOffsets.insert(currentOffset);
      }
      else
      {
        printUnitializedWarning(findVariableNameFromOffset(exprOffset), context->start->getLine());
      }
    }
    return 0;
  }

  antlrcpp::Any visitDeclarationSeuleChar(ifccParser::DeclarationSeuleCharContext *context)
  {
    if (this->program->cfgs.back()->symbolTable->insert({context->ID()->getText(), this->program->cfgs.back()->maxOffset}).second == true)
    {
      this->program->cfgs.back()->maxOffset += 1;
    }
    else
    {
      printAlreadyDeclaredError(context->ID()->getText(), context->start->getLine());
      this->correctCode = false;
    };
    return 0;
  }

  antlrcpp::Any visitDeclarationInitialiseeChar(ifccParser::DeclarationInitialiseeCharContext *context)
  {
    int currentOffset = this->program->cfgs.back()->maxOffset;

    // Checks if the variable has indeed been added to the symbolTable.
    // If not, it means that that variable name is already declared.
    if (this->program->cfgs.back()->symbolTable->insert({context->ID()->getText(), this->program->cfgs.back()->maxOffset}).second == true)
    {
      this->program->cfgs.back()->maxOffset += 1;
    }
    else
    {
      printAlreadyDeclaredError(context->ID()->getText(), context->start->getLine());
      this->correctCode = false;
    };

    int exprOffset = visit(context->expr());

    // Checks if the expr is effectively in the symbolTable (see visitVarExpr)
    // Then, checks if the expr is affected, if not, prints a warning in the error output.
    if (exprOffset != -1)
    {
      if (affectedOffsets.count(exprOffset) == 1)
      {
        this->affectedOffsets.insert(currentOffset);
      }
      else
      {
        printUnitializedWarning(findVariableNameFromOffset(exprOffset), context->start->getLine());
      }
    }
    return 0;
  }

  antlrcpp::Any visitDeclarationSeule64(ifccParser::DeclarationSeule64Context *context)
  {
    if (this->program->cfgs.back()->symbolTable->insert({context->ID()->getText(), this->program->cfgs.back()->maxOffset}).second == true)
    {
      this->program->cfgs.back()->maxOffset += 8;
    }
    else
    {
      printAlreadyDeclaredError(context->ID()->getText(), context->start->getLine());
      this->correctCode = false;
    };
    return 0;
  }

  antlrcpp::Any visitDeclarationInitialisee64(ifccParser::DeclarationInitialisee64Context *context)
  {
    int currentOffset = this->program->cfgs.back()->maxOffset;

    // Checks if the variable has indeed been added to the symbolTable.
    // If not, it means that that variable name is already declared.
    if (this->program->cfgs.back()->symbolTable->insert({context->ID()->getText(), this->program->cfgs.back()->maxOffset}).second == true)
    {
      this->program->cfgs.back()->maxOffset += 8;
    }
    else
    {
      printAlreadyDeclaredError(context->ID()->getText(), context->start->getLine());
      this->correctCode = false;
    };

    int exprOffset = visit(context->expr());

    // Checks if the expr is effectively in the symbolTable (see visitVarExpr)
    // Then, checks if the expr is affected, if not, prints a warning in the error output.
    if (exprOffset != -1)
    {
      if (affectedOffsets.count(exprOffset) == 1)
      {
        this->affectedOffsets.insert(currentOffset);
      }
      else
      {
        printUnitializedWarning(findVariableNameFromOffset(exprOffset), context->start->getLine());
      }
    }
    return 0;
  }

  antlrcpp::Any visitAffectation(ifccParser::AffectationContext *context)
  {
    // Checks if the variable is declared in the symbolTable, if not prints an error to the output error.
    // Then, checks if the expr is affected, if not, prints a warning in the error output.
    std::string leftVarName = context->ID()->getText();
    if (this->program->cfgs.back()->symbolTable->count(leftVarName) == 1)
    {
      int exprOffset = visit(context->expr());
      if (exprOffset != -1)
      {
        if (affectedOffsets.count(exprOffset) == 1)
        {
          this->affectedOffsets.insert((*(this->program->cfgs.back()->symbolTable))[leftVarName]);
        }
        else
        {
          printUnitializedWarning(findVariableNameFromOffset(exprOffset), context->start->getLine());
        }
      }
    }
    else
    {
      printNotDeclaredError(leftVarName, context->start->getLine());
      this->correctCode = false;
    }
    return 0;
  }

  antlrcpp::Any visitVarExpr(ifccParser::VarExprContext *context)
  {
    // Checks if the Var is declared in the symbolTable.
    // If not, prints an error to the error output.
    if (this->program->cfgs.back()->symbolTable->count(context->ID()->getText()) == 1)
    {
      return (*(this->program->cfgs.back()->symbolTable))[context->ID()->getText()];
    }
    else
    {
      printNotDeclaredError(context->ID()->getText(), context->start->getLine());
      this->correctCode = false;
      return -1;
    }
    return (*(this->program->cfgs.back()->symbolTable))[context->ID()->getText()]; // returns an int
  }

  antlrcpp::Any visitConstExpr(ifccParser::ConstExprContext *context)
  {
    return createTemporaryFromConstant(stoi(context->CONST()->getText())); // returns an int
  }

  antlrcpp::Any visitParExpr(ifccParser::ParExprContext *context)
  {
    int closingParCounter = 0, openingParCounter = 0;
    for (int i = 0; i < context->children.size(); i++)
    {
      if (context->children[i]->getText() == "(")
      {
        openingParCounter++;
      }
      if (context->children[i]->getText() == ")")
      {
        closingParCounter++;
      }
    }
    if (openingParCounter != closingParCounter)
    {
      printMissingParenthesis(context->start->getLine());
      this->correctCode = false;
    }
    return visit(context->expr());
  }

  antlrcpp::Any visitConstCharExpr(ifccParser::ConstCharExprContext *context)
  {
    std::string recup = context->CONSTCHAR()->getText();
    char charRecup = recup.at(1);
    return createTemporaryFromConstant(charRecup);
  }

  // Checks if both variables are initialized.
  // If not, sends one or two warnings to the error output.
  antlrcpp::Any visitMinusAddExpr(ifccParser::MinusAddExprContext *context)
  {
    int offsetLeft = visit(context->expr(0));
    if (offsetLeft != -1)
    {
      if (affectedOffsets.count(offsetLeft) != 1)
      {
        printUnitializedWarning(findVariableNameFromOffset(offsetLeft), context->start->getLine());
      }
    }
    int offsetRight = visit(context->expr(1));
    if (offsetRight != -1)
    {
      if (affectedOffsets.count(offsetRight) != 1)
      {
        printUnitializedWarning(findVariableNameFromOffset(offsetRight), context->start->getLine());
      }
    }
    return createTemporaryVariable();
  }

  // Checks if both variables are initialized.
  // If not, sends one or two warnings to the error output.
  antlrcpp::Any visitMultExpr(ifccParser::MultExprContext *context)
  {
    int offsetLeft = visit(context->expr(0));
    if (offsetLeft != -1)
    {
      if (affectedOffsets.count(offsetLeft) != 1)
      {
        printUnitializedWarning(findVariableNameFromOffset(offsetLeft), context->start->getLine());
      }
    }
    int offsetRight = visit(context->expr(1));
    if (offsetRight != -1)
    {
      if (affectedOffsets.count(offsetRight) != 1)
      {
        printUnitializedWarning(findVariableNameFromOffset(offsetRight), context->start->getLine());
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
    this->program->cfgs.back()->maxOffset += 4;
    this->program->cfgs.back()->symbolTable->insert({"tmp" + std::to_string( this->program->cfgs.back()->maxOffset),  this->program->cfgs.back()->maxOffset});
    this->affectedOffsets.insert(this->program->cfgs.back()->maxOffset);
    return this->program->cfgs.back()->maxOffset;
  }

  int createTemporaryFromConstant(char val)
  {
    val = (int)val;
    this->program->cfgs.back()->maxOffset += 1;
    this->program->cfgs.back()->symbolTable->insert({"tmp" + std::to_string(this->program->cfgs.back()->maxOffset), this->program->cfgs.back()->maxOffset});
    this->affectedOffsets.insert(this->program->cfgs.back()->maxOffset);
    return this->program->cfgs.back()->maxOffset;
  }

  int createTemporaryVariable()
  {

    this->program->cfgs.back()->maxOffset += 4;
    this->program->cfgs.back()->symbolTable->insert({"tmp" + std::to_string(this->program->cfgs.back()->maxOffset), this->program->cfgs.back()->maxOffset});
    this->affectedOffsets.insert(this->program->cfgs.back()->maxOffset);
    return this->program->cfgs.back()->maxOffset;
  }

  std::string findVariableNameFromOffset(int offset)
  {
    for (auto it = this->program->cfgs.back()->symbolTable->begin(); it != this->program->cfgs.back()->symbolTable->end(); ++it)
    {
      if (it->second == offset)
      {
        return it->first;
      }
    }
    return "";
  }

  bool getCorrectCode()
  {
    return this->correctCode;
  }

void printUnitializedWarning(std::string variableName, int line){
  std::cerr << "The variable "
            << variableName
            << " is not yet initialized. Line : "
            << line
            << std::endl;
}

void printAlreadyDeclaredError(std::string variableName, int line){
  std::cerr << "The variable "
            << variableName
            << " is already declared. Line : "
            << line
            << std::endl;
}
antlrcpp::Any visitFunctionCallSeul(ifccParser::FunctionCallSeulContext *ctx)
  {
    std::string functionName = ctx->ID()->getText();
    for(int i = 0; i < this->program->cfgs.size(); i++)
    {
      if(this->program->cfgs[i]->name == functionName)
      {
        return createTemporaryVariable();
      }
      
    }
    printNotDeclaredError(functionName,ctx->start->getLine());
    this->correctCode = false;
    return -1;
  }

void printMissingParenthesis(int line){
  std::cerr << "ERROR : Missing parenthesis. Line : "
                << line
                << std::endl;
}

void printNotDeclaredError(std::string variableName, int line){
  std::cerr << "ERROR : "
                << "The variable or function"
                << variableName
                << " is not declared. Line : "
                << line
                << std::endl;
}

protected:
  std::set<int> affectedOffsets;
  bool correctCode = true;
  std::vector<CFG*> cfgs;
  Program* program;
};
