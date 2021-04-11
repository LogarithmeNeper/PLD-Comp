
// Generated from ifcc.g4 by ANTLR 4.7.2

#pragma once

// INCLUDE

// General includes
#include <map>
#include <set>
#include <algorithm>

// ANTLR INcludes
#include "antlr4-runtime.h"
#include "antlr4-generated/ifccBaseVisitor.h"
#include "cfg.h"
#include "program.h"

/**
 * This class provides an empty implementation of ifccVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 * 
 * Derives from ifccBaseVisitor in ANTLR (no need to duplicate several methods)
 */

class PreVisitor : public ifccBaseVisitor
{
  // Public methods of the PreVisitor Class
public:
  // Method when visiting a prog node
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

  // Method when visiting the return node
  antlrcpp::Any visitRet(ifccParser::RetContext *context)
  {
    // Gets the offset of the expression return with a visitor in the context...
    int offsetExpr = visit(context->expr());
    // ...then visits all children of the context
    return visitChildren(context);
  }

  // Method for the declaration of variables
  antlrcpp::Any visitDeclaration(ifccParser::DeclarationContext *context)
  {
    // visits all children of the context
    visitChildren(context);
    return 0;
  }


  /*
  * INT METHODS
  */

  // Method for an integer declaration
  antlrcpp::Any visitDeclarationSeuleInt(ifccParser::DeclarationSeuleIntContext *context)
  {
    // Checks whether or not the variable is in the symbol table and adds it if succeded
    // We get the current name with the text in the ID in the context
    if (this->program->cfgs.back()->symbolTable->insert({context->ID()->getText(), this->program->cfgs.back()->maxOffset}).second == true)
    {
      // If this works, then we update the current maxOffset in which variables are defined
      this->program->cfgs.back()->maxOffset += 4;
    }
    else
    {
      // If this fails, then we can throw an exception as the variable is already declared somewhere
      // We give information of the name of the variable, and the line where the error is produced
      printAlreadyDeclaredError(context->ID()->getText(), context->start->getLine());
      // And the code is said to be incorrect
      this->correctCode = false;
    };
    return 0;
  }

  // Method for an initialized declaration of an integer with an expression
  antlrcpp::Any visitDeclarationInitialiseeIntExpr(ifccParser::DeclarationInitialiseeIntExprContext *context)
  {
    int currentOffset = this->program->cfgs.back()->maxOffset;

    // Checks if the variable has indeed been added to the symbolTable.
    // If not, it means that that variable name is already declared.
    if (this->program->cfgs.back()->symbolTable->insert({context->ID()->getText(), this->program->cfgs.back()->maxOffset}).second == true)
    {
      // Updates the current max offset if it worked
      this->program->cfgs.back()->maxOffset += 4;
    }
    else
    {
      // Failed case : print an error with the name of the variable and the line on which the error occured
      printAlreadyDeclaredError(context->ID()->getText(), context->start->getLine());
      // Code is said to be incorrect
      this->correctCode = false;
    };

    int exprOffset = visit(context->expr());

    // Checks if the expr is effectively in the symbolTable (see visitVarExpr)
    // Then, checks if the expr is affected, if not, prints a warning in the error output.
    if (exprOffset != -1)
    {
      if (this->program->cfgs.back()->affectedOffsets->count(exprOffset) == 1)
      {
        this->program->cfgs.back()->affectedOffsets->insert(currentOffset);
      }
      else
      {
        // If we find a unknown variable in the table, then we raise a warning.
        printUnitializedWarning(findVariableNameFromOffset(exprOffset), context->start->getLine());
      }
    }
    return 0;
  }

  // Method for an initialized declaration of an integer in a chain of assignments
  antlrcpp::Any visitDeclarationInitialiseeIntAssign(ifccParser::DeclarationInitialiseeIntAssignContext *context)
  {
    int currentOffset = maxOffset;

    // Checks if the variable has indeed been added to the symbolTable.
    // If not, it means that that variable name is already declared.
    if (symbolTable.insert({context->ID()->getText(), maxOffset}).second == true)
    {
      // Updates the current max offset if it worked
      this->maxOffset += 4;
    }
    else
    {
      // Failed case : print an error with the name of the variable and the line on which the error occured
      printAlreadyDeclaredError(context->ID()->getText(), context->start->getLine());
      // Code is said to be incorrect
      this->correctCode = false;
    };

    int exprOffset = visit(context->assignment());

    // Checks if the left side of the child assignment is in the symbolTable.
    // Checks if the assignment is correctly done (it returns the value assigned), if not, prints a warning in the error output.
    if (exprOffset != -1)
    {
      if (affectedOffsets.count(exprOffset) == 1)
      {
        this->affectedOffsets.insert(currentOffset);
      }
      else
      {
        // If we find a unknown variable in the table, then we raise a warning.
        printUnitializedWarning(findVariableNameFromOffset(exprOffset), context->start->getLine());
      }
    }
    return 0;
  }

  /*
  * CHAR METHODS
  */

  // Method for a char declaration.
  antlrcpp::Any visitDeclarationSeuleChar(ifccParser::DeclarationSeuleCharContext *context)
  {
    // Chekcs if the char variable has been added to the symbol table...
    if (this->program->cfgs.back()->symbolTable->insert({context->ID()->getText(), this->program->cfgs.back()->maxOffset}).second == true)
    {
      // If this works, then we update the max offset (+=1 as char is on one byte)
      this->program->cfgs.back()->maxOffset += 1;
    }
    else
    {
      // Otherwise, the varaible is already declared and we throw an error with the name and the line.
      printAlreadyDeclaredError(context->ID()->getText(), context->start->getLine());
      // Code is indeed false
      this->correctCode = false;
    };
    return 0;
  }

  // Method for an initialized declaration of a character with an expression
  antlrcpp::Any visitDeclarationInitialiseeCharExpr(ifccParser::DeclarationInitialiseeCharExprContext *context)
  {
    int currentOffset = this->program->cfgs.back()->maxOffset;

    // Checks if the variable has indeed been added to the symbolTable.
    // If not, it means that that variable name is already declared.
    if (this->program->cfgs.back()->symbolTable->insert({context->ID()->getText(), this->program->cfgs.back()->maxOffset}).second == true)
    {
      // Updates if true
      this->program->cfgs.back()->maxOffset += 1;
    }
    else
    {
      // Else, is already declared, we print an error and the code is false
      printAlreadyDeclaredError(context->ID()->getText(), context->start->getLine());
      this->correctCode = false;
    };

    int exprOffset = visit(context->expr());

    // Checks if the expr is effectively in the symbolTable (see visitVarExpr)
    // Then, checks if the expr is affected, if not, prints a warning in the error output.
    if (exprOffset != -1)
    {
      if (this->program->cfgs.back()->affectedOffsets->count(exprOffset) == 1)
      {
        this->program->cfgs.back()->affectedOffsets->insert(currentOffset);
      }
      else
      {
        // If we found an unknown variable for the symbol table, then we throw the corresponding exception
        printUnitializedWarning(findVariableNameFromOffset(exprOffset), context->start->getLine());
      }
    }
    return 0;
  }

  // Method for an initialized declaration of a character in a chain of assignments
  antlrcpp::Any visitDeclarationInitialiseeCharAssign(ifccParser::DeclarationInitialiseeCharAssignContext *context)
  {
    int currentOffset = maxOffset;

    // Checks if the variable has indeed been added to the symbolTable.
    // If not, it means that that variable name is already declared.
    if (symbolTable.insert({context->ID()->getText(), maxOffset}).second == true)
    {
      // Updates if true
      this->maxOffset += 1;
    }
    else
    {
      // Else, is already declared, we print an error and the code is false
      printAlreadyDeclaredError(context->ID()->getText(), context->start->getLine());
      this->correctCode = false;
    };

    int exprOffset = visit(context->assignment());

    // Checks if the left side of the child assignment is in the symbolTable.
    // Checks if the assignment is correctly done (it returns the value assigned), if not, prints a warning in the error output.
    if (exprOffset != -1)
    {
      if (affectedOffsets.count(exprOffset) == 1)
      {
        this->affectedOffsets.insert(currentOffset);
      }
      else
      {
        // If we found an unknown variable for the symbol table, then we throw the corresponding exception
        printUnitializedWarning(findVariableNameFromOffset(exprOffset), context->start->getLine());
      }
    }
    return 0;
  }

  /*
  * INT 64 METHODS
  */

  // Method for the declaration of an int 64
  antlrcpp::Any visitDeclarationSeule64(ifccParser::DeclarationSeule64Context *context)
  {
    // Checks if the variable is already in the symbol table...
    if (this->program->cfgs.back()->symbolTable->insert({context->ID()->getText(), this->program->cfgs.back()->maxOffset}).second == true)
    {
      // If this works, then offset is updated (+=8 because of the type)
      this->program->cfgs.back()->maxOffset += 8;
    }
    else
    {
      // Otherwise, variable is already declared and we throw the corresponding error with the name of the variable and the line
      printAlreadyDeclaredError(context->ID()->getText(), context->start->getLine());
      // Code is indeed incorrect
      this->correctCode = false;
    };
    return 0;
  }

  // Method for an initialized declaration of an int 64 variable with an expression
  antlrcpp::Any visitDeclarationInitialisee64Expr(ifccParser::DeclarationInitialisee64ExprContext *context)
  {
    int currentOffset = this->program->cfgs.back()->maxOffset;

    // Checks if the variable has indeed been added to the symbolTable.
    // If not, it means that that variable name is already declared.
    if (this->program->cfgs.back()->symbolTable->insert({context->ID()->getText(), this->program->cfgs.back()->maxOffset}).second == true)
    {
      // Updated max offset if it worked
      this->program->cfgs.back()->maxOffset += 8;
    }
    else
    {
      // Otherwise error of redeclaration
      printAlreadyDeclaredError(context->ID()->getText(), context->start->getLine());
      // code is incorrect
      this->correctCode = false;
    };

    int exprOffset = visit(context->expr());

    // Checks if the expr is effectively in the symbolTable (see visitVarExpr)
    // Then, checks if the expr is affected, if not, prints a warning in the error output.
    if (exprOffset != -1)
    {
      if (this->program->cfgs.back()->affectedOffsets->count(exprOffset) == 1)
      {
        this->program->cfgs.back()->affectedOffsets->insert(currentOffset);
      }
      else
      {
        // If we found an uninitialized variable, we throw the corresponding warning with name and line
        printUnitializedWarning(findVariableNameFromOffset(exprOffset), context->start->getLine());
      }
    }
    return 0;
  }

  // Method for an initialized declaration of an int 64 variable in a chain of assignments
  antlrcpp::Any visitDeclarationInitialisee64Assign(ifccParser::DeclarationInitialisee64AssignContext *context)
  {
    int currentOffset = maxOffset;

    // Checks if the variable has indeed been added to the symbolTable.
    // If not, it means that that variable name is already declared.
    if (symbolTable.insert({context->ID()->getText(), maxOffset}).second == true)
    {
      // Updated max offset if it worked
      this->maxOffset += 8;
    }
    else
    {
      // Otherwise error of redeclaration
      printAlreadyDeclaredError(context->ID()->getText(), context->start->getLine());
      // code is incorrect
      this->correctCode = false;
    };

    int exprOffset = visit(context->assignment());

    // Checks if the left side of the child assignment is in the symbolTable.
    // Checks if the assignment is correctly done (it returns the value assigned), if not, prints a warning in the error output.
    if (exprOffset != -1)
    {
      if (affectedOffsets.count(exprOffset) == 1)
      {
        this->affectedOffsets.insert(currentOffset);
      }
      else
      {
        // If we found an uninitialized variable, we throw the corresponding warning with name and line
        printUnitializedWarning(findVariableNameFromOffset(exprOffset), context->start->getLine());
      }
    }
    return 0;
  }

  /*
  * ASSIGNMENT METHODS
  */

  antlrcpp::Any visitAssignmentExpr(ifccParser::AssignmentExprContext *context)
  {
    // Checks if the variable is declared in the symbolTable, if not prints an error to the output error.
    // Then, checks if the expr is affected, if not, prints a warning in the error output.
    std::string leftVarName = context->ID()->getText();
    // If there is the variable name in the symbol table
    if (this->program->cfgs.back()->symbolTable->count(leftVarName) == 1)
    {
      // Get the offset of the corresponding expression
      int exprOffset = visit(context->expr());
      if (exprOffset != -1)
      {
        if (this->program->cfgs.back()->affectedOffsets->count(exprOffset) == 1)
        {
          this->program->cfgs.back()->affectedOffsets->insert((*(this->program->cfgs.back()->symbolTable))[leftVarName]);
        }
        else
        {
          // If we found an uninitialized variable, we throw the corresponding warning with name and line
          printUnitializedWarning(findVariableNameFromOffset(exprOffset), context->start->getLine());
        }
      }
    }
    else
    {
      // If the variable was not declared before, then the code is false, and we throw the exception
      printNotDeclaredError(leftVarName, context->start->getLine());
      this->correctCode = false;
    }
    return 0;
  }

  antlrcpp::Any visitAssignmentChain(ifccParser::AssignmentChainContext *context)
  {
    // Checks if the variable is declared in the symbolTable, if not prints an error to the output error.
    // Then, checks if the assignment is correct, if not, prints a warning in the error output.
    std::string leftVarName = context->ID()->getText();
    // If there is the variable name in the symbol table
    if (this->symbolTable.count(leftVarName) == 1)
    {
      // Get the offset of the corresponding assignment
      int exprOffset = visit(context->assignment());
      if (exprOffset != -1)
      {
        if (affectedOffsets.count(exprOffset) == 1)
        {
          this->affectedOffsets.insert(this->symbolTable[leftVarName]);
        }
        else
        {
          // If we found an uninitialized variable, we throw the corresponding warning with name and line
          printUnitializedWarning(findVariableNameFromOffset(exprOffset), context->start->getLine());
        }
      }
    }
    else
    {
      // If the variable was not declared before, then the code is false, and we throw the exception
      printNotDeclaredError(leftVarName, context->start->getLine());
      this->correctCode = false;
    }
    return 0;
  }

  /*
  * EXPR METHODS
  */

  antlrcpp::Any visitVarExpr(ifccParser::VarExprContext *context)
  {
    // Checks if the Var is declared in the symbolTable.
    // If not, prints an error to the error output.
    if (this->program->cfgs.back()->symbolTable->count(context->ID()->getText()) == 1)
    {
      // we get the corresponding offset
      return (*(this->program->cfgs.back()->symbolTable))[context->ID()->getText()];
    }
    else
    {
      // Error handler
      printNotDeclaredError(context->ID()->getText(), context->start->getLine());
      this->correctCode = false;
      return -1;
    }
    return (*(this->program->cfgs.back()->symbolTable))[context->ID()->getText()]; // returns an int
  }

  // Method for visiting the constant leaf in an expression
  antlrcpp::Any visitConstExpr(ifccParser::ConstExprContext *context)
  {
    // We create an tmp variable given the context 
    return createTemporaryFromConstant(stoi(context->CONST()->getText())); // returns an int
  }

  // Method for parenthesis around an expression
  antlrcpp::Any visitParExpr(ifccParser::ParExprContext *context)
  {
    return visit(context->expr());
  }

  // Method for a constant char expression
  antlrcpp::Any visitConstCharExpr(ifccParser::ConstCharExprContext *context)
  {
    std::string recup = context->CONSTCHAR()->getText();
    // gets the character after the first '
    char charRecup = recup.at(1);
    return createTemporaryFromConstant(charRecup);
  }

  // Method for an expression linked with a + or a - as the root operator
  antlrcpp::Any visitMinusAddExpr(ifccParser::MinusAddExprContext *context)
  {
    // Gets the offset of the left variable
    int offsetLeft = visit(context->expr(0));
    if (offsetLeft != -1)
    {
      if (this->program->cfgs.back()->affectedOffsets->count(offsetLeft) != 1)
      {
        // If we found an unitialized variable, we throw a warning with the name and the line
        printUnitializedWarning(findVariableNameFromOffset(offsetLeft), context->start->getLine());
      }
    }

    // Same with the right offset
    int offsetRight = visit(context->expr(1));
    if (offsetRight != -1)
    {
      if (this->program->cfgs.back()->affectedOffsets->count(offsetRight) != 1)
      {
        // Same
        printUnitializedWarning(findVariableNameFromOffset(offsetRight), context->start->getLine());
      }
    }

    // then we create and return a temporary variable
    return createTemporaryVariable();
  }

  // Method for an expression liked with a * as the root operator
  antlrcpp::Any visitMultExpr(ifccParser::MultExprContext *context)
  {
    // Gets the offset of the left variable
    int offsetLeft = visit(context->expr(0));
    if (offsetLeft != -1)
    {
      if (this->program->cfgs.back()->affectedOffsets->count(offsetLeft) != 1)
      {
        // If we found an unitialized variable, we throw a warning with the name and the line
        printUnitializedWarning(findVariableNameFromOffset(offsetLeft), context->start->getLine());
      }
    }
  
    // Same with the right variable
    int offsetRight = visit(context->expr(1));
    if (offsetRight != -1)
    {
      if (this->program->cfgs.back()->affectedOffsets->count(offsetRight) != 1)
      {
        // If we found an unitialized variable, we throw a warning with the name and the line
        printUnitializedWarning(findVariableNameFromOffset(offsetRight), context->start->getLine());
      }
    }

    // Creates and return the temporary variable
    return createTemporaryVariable();
  }

  /*
  * UTILITY METHODS
  */ 

  // Utility method for removing the last character of a string
  // Ex : 'PLD-COMP' -> 'PLD-COM'
  std::string removeLastCharFromString(std::string str)
  {
    return str.substr(0, str.size() - 1);
  }

  // Utility method for creating a temporary from a constant given an int value
  int createTemporaryFromConstant(int val)
  {
    // Updates the offset for an int
    this->program->cfgs.back()->maxOffset += 4;
    // Inserts in the symbol table
    this->program->cfgs.back()->symbolTable->insert({"tmp" + std::to_string( this->program->cfgs.back()->maxOffset),  this->program->cfgs.back()->maxOffset});
    // Inserts in the assigned offsets
    this->program->cfgs.back()->affectedOffsets->insert(this->program->cfgs.back()->maxOffset);
    // Return the offset
    return this->program->cfgs.back()->maxOffset;
  }

  // Utility method for creating a temporary from a constant given a char value 
  int createTemporaryFromConstant(char val)
  {
    // Explicit cast in integer
    val = (int)val;
    // Updates the offset for a char
    this->program->cfgs.back()->maxOffset += 1;
    // Inserts in the symbol tabme
    this->program->cfgs.back()->symbolTable->insert({"tmp" + std::to_string(this->program->cfgs.back()->maxOffset), this->program->cfgs.back()->maxOffset});
    // Inserts in the assigned offsets
    this->program->cfgs.back()->affectedOffsets->insert(this->program->cfgs.back()->maxOffset);
    // Return the offset
    return this->program->cfgs.back()->maxOffset;
  }

  // Utility method for creating a temporary variable
  int createTemporaryVariable()
  {
    // Updates the current maximum offset
    this->program->cfgs.back()->maxOffset += 4;
    // Insert in the symbol table
    this->program->cfgs.back()->symbolTable->insert({"tmp" + std::to_string(this->program->cfgs.back()->maxOffset), this->program->cfgs.back()->maxOffset});
    // Inserts in the assigned offset
    this->program->cfgs.back()->affectedOffsets->insert(this->program->cfgs.back()->maxOffset);
    // Return the offset
    return this->program->cfgs.back()->maxOffset;
  }

  // Utility method for reversing the symbol table (we go int -> string in a string -> int map)
  // The key is supposed to be UNIQUE (otherwise we get a segfault)
  std::string findVariableNameFromOffset(int offset)
  {
    // Iterating on the whole symbol table from the beginning to the end of the symbol table
    for (auto it = this->program->cfgs.back()->symbolTable->begin(); it != this->program->cfgs.back()->symbolTable->end(); ++it)
    {
      // If the value is the found value, then we return it
      if (it->second == offset)
      {
        return it->first;
      }
    }
    // If not found, we return the empty string
    return "";
  }

  // Utility method to check if the code is correct or not
  bool getCorrectCode()
  {
    return this->correctCode;
  }

  /*
  * ERRORS and WARNINGS
  */

  // Void method for uninitialized variable warning
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

  // Void method for a variable that has been already declared
  void printAlreadyDeclaredError(std::string variableName, int line)
  {
    std::cerr << "The variable "
              << variableName
              << " is already declared. Line : "
              << line
              << std::endl;
  }

  // Void method for undeclared variables
void printNotDeclaredError(std::string variableName, int line){
  std::cerr << "ERROR : "
                << "The variable or function "
                << variableName
                << " is not declared. Line : "
                << line
                << std::endl;
}

// protected attributes of the class
protected:
  bool correctCode = true;
  std::vector<CFG*> cfgs;
  Program* program;
};
