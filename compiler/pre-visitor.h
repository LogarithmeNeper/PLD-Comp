
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
    int variableOffset = 0;                 // initializes the offset for the first variable
    std::map<std::string, int> symbolTable; // SymbolTable
    this->symbolTable = symbolTable;        // Copy the symbolTable for the whole visitor object
    this->maxOffset = variableOffset;       // Sets the current max offset in the class to the variable offset

    // then visits all children of the context
    visitChildren(context);
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
    if (this->symbolTable.insert({context->ID()->getText(), maxOffset}).second == true)
    {
      // If this works, then we update the current maxOffset in which variables are defined
      this->maxOffset += 4;
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

  // Method for an initialized declaration of an integer
  antlrcpp::Any visitDeclarationInitialiseeIntExpr(ifccParser::DeclarationInitialiseeIntExprContext *context)
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
        // If we find a unknown variable in the table, then we raise a warning.
        printUnitializedWarning(findVariableNameFromOffset(exprOffset), context->start->getLine());
      }
    }
    return 0;
  }

  antlrcpp::Any visitDeclarationInitialiseeIntAssign(ifccParser::DeclarationInitialiseeIntAssignContext *context)
  {
    int currentOffset = maxOffset;

    // Checks if the variable has indeed been added to the symbolTable.
    // If not, it means that that variable name is already declared.
    if (symbolTable.insert({context->ID()->getText(), maxOffset}).second == true)
    {
      this->maxOffset += 4;
    }
    else
    {
      printAlreadyDeclaredError(context->ID()->getText(), context->start->getLine());
      this->correctCode = false;
    };

    int exprOffset = visit(context->assignment());

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

  /*
  * CHAR METHODS
  */

  // Method for a char declaration.
  antlrcpp::Any visitDeclarationSeuleChar(ifccParser::DeclarationSeuleCharContext *context)
  {
    // Chekcs if the char variable has been added to the symbol table...
    if (this->symbolTable.insert({context->ID()->getText(), maxOffset}).second == true)
    {
      // If this works, then we update the max offset (+=1 as char is on one byte)
      this->maxOffset += 1;
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

  // Method for an initialized declaration of a character
  antlrcpp::Any visitDeclarationInitialiseeCharExpr(ifccParser::DeclarationInitialiseeCharExprContext *context)
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
        // If we found an unknown variable for the symbol table, then we throw the corresponding exception
        printUnitializedWarning(findVariableNameFromOffset(exprOffset), context->start->getLine());
      }
    }
    return 0;
  }

  antlrcpp::Any visitDeclarationInitialiseeCharAssign(ifccParser::DeclarationInitialiseeCharAssignContext *context)
  {
    int currentOffset = maxOffset;

    // Checks if the variable has indeed been added to the symbolTable.
    // If not, it means that that variable name is already declared.
    if (symbolTable.insert({context->ID()->getText(), maxOffset}).second == true)
    {
      this->maxOffset += 1;
    }
    else
    {
      printAlreadyDeclaredError(context->ID()->getText(), context->start->getLine());
      this->correctCode = false;
    };

    int exprOffset = visit(context->assignment());

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

  /*
  * INT 64 METHODS
  */

  // Method for the declaration of an int 64
  antlrcpp::Any visitDeclarationSeule64(ifccParser::DeclarationSeule64Context *context)
  {
    // Checks if the variable is already in the symbol table...
    if (this->symbolTable.insert({context->ID()->getText(), maxOffset}).second == true)
    {
      // If this works, then offset is updated (+=8 because of the type)
      this->maxOffset += 8;
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

  // Method for an initialized declaration of an int 64 variable
  antlrcpp::Any visitDeclarationInitialisee64Expr(ifccParser::DeclarationInitialisee64ExprContext *context)
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
        // If we found an uninitialized variable, we throw the corresponding warning with name and line
        printUnitializedWarning(findVariableNameFromOffset(exprOffset), context->start->getLine());
      }
    }
    return 0;
  }

  antlrcpp::Any visitDeclarationInitialisee64Assign(ifccParser::DeclarationInitialisee64AssignContext *context)
  {
    int currentOffset = maxOffset;

    // Checks if the variable has indeed been added to the symbolTable.
    // If not, it means that that variable name is already declared.
    if (symbolTable.insert({context->ID()->getText(), maxOffset}).second == true)
    {
      this->maxOffset += 8;
    }
    else
    {
      printAlreadyDeclaredError(context->ID()->getText(), context->start->getLine());
      this->correctCode = false;
    };

    int exprOffset = visit(context->assignment());

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

  antlrcpp::Any visitAssignmentExpr(ifccParser::AssignmentExprContext *context)
  {
    // Checks if the variable is declared in the symbolTable, if not prints an error to the output error.
    // Then, checks if the expr is affected, if not, prints a warning in the error output.
    std::string leftVarName = context->ID()->getText();
    // If there is the variable name in the symbol table
    if (this->symbolTable.count(leftVarName) == 1)
    {
      // Get the offset of the corresponding expression
      int exprOffset = visit(context->expr());
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

  // Method for visiting the variable leaf in an expression
  antlrcpp::Any visitAssignmentChain(ifccParser::AssignmentChainContext *context)
  {
    // Checks if the variable is declared in the symbolTable, if not prints an error to the output error.
    // Then, checks if the expr is affected, if not, prints a warning in the error output.
    std::string leftVarName = context->ID()->getText();
    if (this->symbolTable.count(leftVarName) == 1)
    {
      int exprOffset = visit(context->assignment());
      if (exprOffset != -1)
      {
        if (affectedOffsets.count(exprOffset) == 1)
        {
          this->affectedOffsets.insert(this->symbolTable[leftVarName]);
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
    if (this->symbolTable.count(context->ID()->getText()) == 1)
    {
      // we get the corresponding offset
      return symbolTable[context->ID()->getText()];
    }
    else
    {
      // Error handler
      printNotDeclaredError(context->ID()->getText(), context->start->getLine());
      this->correctCode = false;
      return -1;
    }
    return symbolTable[context->ID()->getText()]; // returns an int
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
    // We check if there is the same number of opening and closing parenthesis by counting them
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
    // If there are more ( than ) or more ) than ( we throw an exception, and locate it in the code
    if (openingParCounter != closingParCounter)
    {
      printMissingParenthesis(context->start->getLine());
      // code is indeed false
      this->correctCode = false;
    }
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
      if (affectedOffsets.count(offsetLeft) != 1)
      {
        // If we found an unitialized variable, we throw a warning with the name and the line
        printUnitializedWarning(findVariableNameFromOffset(offsetLeft), context->start->getLine());
      }
    }

    // Same with the right offset
    int offsetRight = visit(context->expr(1));
    if (offsetRight != -1)
    {
      if (affectedOffsets.count(offsetRight) != 1)
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
      if (affectedOffsets.count(offsetLeft) != 1)
      {
        // If we found an unitialized variable, we throw a warning with the name and the line
        printUnitializedWarning(findVariableNameFromOffset(offsetLeft), context->start->getLine());
      }
    }
  
    // Same with the right variable
    int offsetRight = visit(context->expr(1));
    if (offsetRight != -1)
    {
      if (affectedOffsets.count(offsetRight) != 1)
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
    this->maxOffset += 4;
    // Inserts in the symbol table
    this->symbolTable.insert({"tmp" + std::to_string(this->maxOffset), this->maxOffset});
    // Inserts in the assigned offsets
    this->affectedOffsets.insert(this->maxOffset);
    // Return the offset
    return this->maxOffset;
  }

  // Utility method for creating a temporary from a constant given a char value 
  int createTemporaryFromConstant(char val)
  {
    // Explicit cast in integer
    val = (int) val;
    // Updates the offset for a char
    this->maxOffset += 1;
    // Inserts in the symbol tabme
    this->symbolTable.insert({"tmp" + std::to_string(this->maxOffset), this->maxOffset});
    // Inserts in the assigned offsets
    this->affectedOffsets.insert(this->maxOffset);
    // Return the offset
    return this->maxOffset;
  }

  // Utility method for creating a temporary variable
  int createTemporaryVariable()
  {
    // Updates the current maximum offset
    this->maxOffset += 4;
    // Insert in the symbol table
    this->symbolTable.insert({"tmp" + std::to_string(this->maxOffset), this->maxOffset});
    // Inserts in the assigned offset
    this->affectedOffsets.insert(this->maxOffset);
    // Return the offset
    return this->maxOffset;
  }

  // Utility method for reversing the symbol table (we go int -> string in a string -> int map)
  // The key is supposed to be UNIQUE (otherwise we get a segfault)
  std::string findVariableNameFromOffset(int offset)
  {
    // Iterating on the whole symbol table from the beginning to the end of the symbol table
    for (auto it = this->symbolTable.begin(); it != symbolTable.end(); ++it)
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
  void printUnitializedWarning(std::string variableName, int line)
  {
    std::cerr << "The variable "
              << variableName
              << " is not yet initialized. Line : "
              << line
              << std::endl;
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

  // Void method for missing parenthesis
  void printMissingParenthesis(int line)
  {
    std::cerr << "ERROR : Missing parenthesis. Line : "
              << line
              << std::endl;
  }

  // Void method for undeclared variables
  void printNotDeclaredError(std::string variableName, int line)
  {
    std::cerr << "ERROR : "
              << "The variable "
              << variableName
              << " is not declared. Line : "
              << line
              << std::endl;
  }

// protected attributes of the class
protected:
  std::map<std::string, int> symbolTable;
  std::set<int> affectedOffsets;
  int maxOffset;
  bool correctCode = true;
};
