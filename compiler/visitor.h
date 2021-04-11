
// Generated from ifcc.g4 by ANTLR 4.7.2

#pragma once

// System includes
#include <map>
#include <algorithm>
#include <list>
#include <vector>

// ANTLR includes
#include "antlr4-runtime.h"
#include "antlr4-generated/ifccBaseVisitor.h"

// Personal includes
#include "ldconst.h"
#include "copy.h"
#include "add.h"
#include "sub.h"
#include "mul.h"
#include "or.h"
#include "xor.h"
#include "and.h"
#include "program.h"
#include "basic_block.h"
#include "cfg.h"
#include "IR.h"
#include "call.h"
#include "cmp_eq.h"
#include "write_label.h"
#include "jmp.h"

/**
 * This class provides an empty implementation of ifccVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */

class Visitor : public ifccBaseVisitor
{
  // Public methods and attributes of the class Visitor
public:
  // Destructor
  ~Visitor()
  {
    delete this->program;
  }

  /**
   * VISITORS METHODS
   */

  // Method to visit the program
  virtual antlrcpp::Any visitProg(ifccParser::ProgContext *ctx) override
  {
    int variableOffset = 0; // initializes the offset for the first variable
    this->maxOffset = variableOffset;
    this->ifCounter = 2;
    this->program = new Program(); // We initialise the Program one we visit the axiom of the grammar
    this->program->add_cfg(new CFG(this->program));
    //this->program->get_cfg_by_index(0)->add_bb(new BasicBlock(this->program->get_cfg_by_index(0), "main"));
    visitChildren(ctx);
    return 0;
  }

  // Method associated with the block visit by creating a new basic bloc
  virtual antlrcpp::Any visitBloc(ifccParser::BlocContext *ctx) override
  {
    this->program->get_cfg_by_index(0)->add_bb(new BasicBlock(this->program->get_cfg_by_index(0), "main"));
    return visitChildren(ctx);
  }

  // Method associated with the 'return' keyword
  virtual antlrcpp::Any visitRet(ifccParser::RetContext *ctx) override
  {
    int offsetExpr = visit(ctx->expr());

    /**
     *  IT IS AT THIS POINT THAT ASSEMBLY IS GENERATED !
     */
    this->program->gen_asm(cout, offsetExpr);
    return visitChildren(ctx);
  }

  /*
  * DECLARATION / ASSIGNMENT
  */

  // Method for a sole declaration of a variable
  virtual antlrcpp::Any visitDeclaration(ifccParser::DeclarationContext *context) override
  {
    visitChildren(context);
    return 0;
  }

  /*
  * INT
  */ 

  // Method for a  declaration for an integer as assigned
  virtual antlrcpp::Any visitDeclarationSeuleInt(ifccParser::DeclarationSeuleIntContext *context) override
  {
    // Updates the current max offset with the size
    this->maxOffset += 4;

    // Inserts in both tables (symbol/type)
    this->program->get_cfg_by_index(0)->getSymbolTable()->insert({context->ID()->getText(), maxOffset});
    this->program->get_cfg_by_index(0)->getTypeTable()->insert({context->ID()->getText(), "int"});
    return 0;
  }

  // Method for an initialized declaration for an integer as an expression
  virtual antlrcpp::Any visitDeclarationInitialiseeIntExpr(ifccParser::DeclarationInitialiseeIntExprContext *context) override
  {
    // Updates the current max offset with the size
    this->maxOffset += 4;

    // Inserts in both tables (symbol/type)
    this->program->get_cfg_by_index(0)->getSymbolTable()->insert({context->ID()->getText(), maxOffset});
    this->program->get_cfg_by_index(0)->getTypeTable()->insert({context->ID()->getText(), "int"});
    
    // Gets name and offset
    std::string leftVarName = context->ID()->getText();
    int exprOffset = visit(context->expr());

    // Creates the instruction in the current BB
    Copy *copyInstr = new Copy(exprOffset, (*this->program->get_cfg_by_index(0)->getSymbolTable())[leftVarName], leftVarName, this->program->get_cfg_by_index(0)->get_bb_by_index(0));
    IRInstr *instr = dynamic_cast<IRInstr *>(copyInstr);
    this->program->get_cfg_by_index(0)->get_bb_by_index(0)->add_IRInstr(instr);

    return 0;
  }

  // Method for an initialized declaration for an integer as assigned
  virtual antlrcpp::Any visitDeclarationInitialiseeIntAssign(ifccParser::DeclarationInitialiseeIntAssignContext *context) override
  {
    // Updates the current max offset with the size
    this->maxOffset += 4;

    // Inserts in both tables (symbol/type)
    this->program->get_cfg_by_index(0)->getSymbolTable()->insert({context->ID()->getText(), maxOffset});
    this->program->get_cfg_by_index(0)->getTypeTable()->insert({context->ID()->getText(), "int"});
    
    // Gets name and offset
    std::string leftVarName = context->ID()->getText();
    int exprOffset = visit(context->assignment());

    // Creates the instruction in the current BB
    Copy *copyInstr = new Copy(exprOffset, (*this->program->get_cfg_by_index(0)->getSymbolTable())[leftVarName], leftVarName, this->program->get_cfg_by_index(0)->get_bb_by_index(0));
    IRInstr *instr = dynamic_cast<IRInstr *>(copyInstr);
    this->program->get_cfg_by_index(0)->get_bb_by_index(0)->add_IRInstr(instr);

    return 0;
  }

  /*
  * CHAR
  */

  // Method for an declaration for a character
  virtual antlrcpp::Any visitDeclarationSeuleChar(ifccParser::DeclarationSeuleCharContext *context) override
  {
    // Updates the current max offset with the size
    this->maxOffset += 1;

    // Inserts in both tables (symbol/type)
    this->program->get_cfg_by_index(0)->getSymbolTable()->insert({context->ID()->getText(), maxOffset});
    this->program->get_cfg_by_index(0)->getTypeTable()->insert({context->ID()->getText(), "char"});
    return 0;
  }

  // Method for an initialized declaration for a character as an expression
  virtual antlrcpp::Any visitDeclarationInitialiseeCharExpr(ifccParser::DeclarationInitialiseeCharExprContext *context) override
  {
    // Updates the current max offset with the size
    this->maxOffset += 1;

    // Inserts in both tables (symbol/type)
    this->program->get_cfg_by_index(0)->getSymbolTable()->insert({context->ID()->getText(), maxOffset});
    this->program->get_cfg_by_index(0)->getTypeTable()->insert({context->ID()->getText(), "char"});
    
    // Gets name and offset
    std::string leftVarName = context->ID()->getText();
    int exprOffset = visit(context->expr());

    // Creates the instruction in the current BB
    Copy *copyInstr = new Copy(exprOffset, (*this->program->get_cfg_by_index(0)->getSymbolTable())[leftVarName], leftVarName, this->program->get_cfg_by_index(0)->get_bb_by_index(0));
    IRInstr *instr = dynamic_cast<IRInstr *>(copyInstr);
    this->program->get_cfg_by_index(0)->get_bb_by_index(0)->add_IRInstr(instr);
    return 0;
  }

  // Method for an initialized declaration for a character as assigned
  virtual antlrcpp::Any visitDeclarationInitialiseeCharAssign(ifccParser::DeclarationInitialiseeCharAssignContext *context) override
  {
    // Updates the current max offset with the size
    this->maxOffset += 1;

    // Inserts in both tables (symbol/type)
    this->program->get_cfg_by_index(0)->getSymbolTable()->insert({context->ID()->getText(), maxOffset});
    this->program->get_cfg_by_index(0)->getTypeTable()->insert({context->ID()->getText(), "char"});
    
    // Gets name and offset
    std::string leftVarName = context->ID()->getText();
    int exprOffset = visit(context->assignment());


    // Creates the instruction in the current BB
    Copy *copyInstr = new Copy(exprOffset, (*this->program->get_cfg_by_index(0)->getSymbolTable())[leftVarName], leftVarName, this->program->get_cfg_by_index(0)->get_bb_by_index(0));
    IRInstr *instr = dynamic_cast<IRInstr *>(copyInstr);
    this->program->get_cfg_by_index(0)->get_bb_by_index(0)->add_IRInstr(instr);
    return 0;
  }

  /*
  * INT64 METHODS
  */

  // Method for the sole declaration of an int64 variable
  virtual antlrcpp::Any visitDeclarationSeule64(ifccParser::DeclarationSeule64Context *context) override
  {
    // Upadtes the maximum offset with the size
    this->maxOffset += 8;
    // Inserts in both tables (symbol/tables)
    this->program->get_cfg_by_index(0)->getSymbolTable()->insert({context->ID()->getText(), maxOffset});
    this->program->get_cfg_by_index(0)->getTypeTable()->insert({context->ID()->getText(), "int64"});
    
    return 0;
  }

  // Method for initialized declaration of an int64 variable with an expression
  virtual antlrcpp::Any visitDeclarationInitialisee64Expr(ifccParser::DeclarationInitialisee64ExprContext *context) override
  {
    // Updates the maximum offset with the size
    this->maxOffset += 8;
    // Inserts in both tables (symbol/type)
    this->program->get_cfg_by_index(0)->getSymbolTable()->insert({context->ID()->getText(), maxOffset});
    this->program->get_cfg_by_index(0)->getTypeTable()->insert({context->ID()->getText(), "int64"});
    
    // Gets its name and offset
    std::string leftVarName = context->ID()->getText();
    int exprOffset = visit(context->expr());

    // Creates the instruction in the current BB
    Copy *copyInstr = new Copy(exprOffset, (*this->program->get_cfg_by_index(0)->getSymbolTable())[leftVarName], leftVarName, this->program->get_cfg_by_index(0)->get_bb_by_index(0));
    IRInstr *instr = dynamic_cast<IRInstr *>(copyInstr);
    this->program->get_cfg_by_index(0)->get_bb_by_index(0)->add_IRInstr(instr);
    return 0;
  }

  // Method for initialized declaration of an int64 variable as an assignment
  virtual antlrcpp::Any visitDeclarationInitialisee64Assign(ifccParser::DeclarationInitialisee64AssignContext *context) override
  {
    // Updates the maximum offset with the size
    this->maxOffset += 8;
    // Inserts it in both tables (symbol/type)
    this->program->get_cfg_by_index(0)->getSymbolTable()->insert({context->ID()->getText(), maxOffset});
    this->program->get_cfg_by_index(0)->getTypeTable()->insert({context->ID()->getText(), "int64"});
    
    // Gets the name and offset in the expression
    std::string leftVarName = context->ID()->getText();
    int exprOffset = visit(context->assignment());

    // Then creates the instruction to do so in the current BB
    Copy *copyInstr = new Copy(exprOffset, (*this->program->get_cfg_by_index(0)->getSymbolTable())[leftVarName], leftVarName, this->program->get_cfg_by_index(0)->get_bb_by_index(0));
    IRInstr *instr = dynamic_cast<IRInstr *>(copyInstr);
    this->program->get_cfg_by_index(0)->get_bb_by_index(0)->add_IRInstr(instr);

    return 0;
  }

  // Method associated with the expression assignment
  virtual antlrcpp::Any visitAssignmentExpr(ifccParser::AssignmentExprContext *context) override
  {
    // Gets the name as a string and its offset
    std::string leftVarName = context->ID()->getText();
    int exprOffset = visit(context->expr());

    // Then creates a copy instruction in the current BB
    Copy *copyInstr = new Copy(exprOffset, (*this->program->get_cfg_by_index(0)->getSymbolTable())[leftVarName], leftVarName, this->program->get_cfg_by_index(0)->get_bb_by_index(0));
    IRInstr *instr = dynamic_cast<IRInstr *>(copyInstr);
    this->program->get_cfg_by_index(0)->get_bb_by_index(0)->add_IRInstr(instr);

    return exprOffset; //In case of chain assignments
  }

  // Method associated with the chain assignement in the grammar
  virtual antlrcpp::Any visitAssignmentChain(ifccParser::AssignmentChainContext *context) override
  {
    // Gets the chain as a string and its offset in the assignment
    std::string leftVarName = context->ID()->getText();
    int exprOffset = visit(context->assignment());

    // Then creates a copy instruction in the current BB
    Copy *copyInstr = new Copy(exprOffset, (*this->program->get_cfg_by_index(0)->getSymbolTable())[leftVarName], leftVarName, this->program->get_cfg_by_index(0)->get_bb_by_index(0));
    IRInstr *instr = dynamic_cast<IRInstr *>(copyInstr);
    this->program->get_cfg_by_index(0)->get_bb_by_index(0)->add_IRInstr(instr);

    return exprOffset; //In case of chain assignments
  }

  /*
  * EXPRESSION METHODS
  */

  // Method associated with the variable leaf in the expression
  virtual antlrcpp::Any visitVarExpr(ifccParser::VarExprContext *ctx) override
  {
    // Returns the offset in the symbol table
    return (*(this->program->get_cfg_by_index(0)->getSymbolTable()))[ctx->ID()->getText()]; // returns an int
  }

  // Method associated with the constant expression
  virtual antlrcpp::Any visitConstExpr(ifccParser::ConstExprContext *ctx) override
  {
    // Return and creates a new temporary variable according to the constant
    return createTemporaryFromConstant(stoi(ctx->CONST()->getText())); // returns an int
  }

  // Method associated with the '( expr )' case
  virtual antlrcpp::Any visitParExpr(ifccParser::ParExprContext *ctx) override
  {
    // Just visits what's inside the parenthesis
    return visit(ctx->expr());
  }

  // Method associated with the constant character leaf
  virtual antlrcpp::Any visitConstCharExpr(ifccParser::ConstCharExprContext *ctx) override
  {
    // Gets the text
    std::string recup = ctx->CONSTCHAR()->getText();
    char charRecup = recup.at(1);

    // Returns and creates a new temporary variable from this character
    return createTemporaryFromConstant(charRecup);
  }

  // Method associated with either the '+' or the '-' sign in an expression (no priority there)
  virtual antlrcpp::Any visitMinusAddExpr(ifccParser::MinusAddExprContext *ctx) override
  {
    // Gets the value of the right and the left side of an expression as offsets
    int offsetLeft = visit(ctx->expr(0));
    int offsetRight = visit(ctx->expr(1));

    // Updates the value of the current maximum offset
    this->maxOffset += 4;
    // And adds a new temporary variable in the symbol table
    this->program->get_cfg_by_index(0)->getSymbolTable()->insert({"tmp" + std::to_string(this->maxOffset), this->maxOffset});

    // Different cases whether it is '+' or '-' : in every case, create the corresponding instruction in the current BB
    if (ctx->children[1]->getText() == "+")
    {
      Add *addInstr = new Add(offsetLeft, offsetRight, maxOffset, this->program->get_cfg_by_index(0)->get_bb_by_index(0));
      IRInstr *instr = dynamic_cast<IRInstr *>(addInstr);
      this->program->get_cfg_by_index(0)->get_bb_by_index(0)->add_IRInstr(instr);
    }
    else if (ctx->children[1]->getText() == "-")
    {
      Sub *subInstr = new Sub(offsetLeft, offsetRight, maxOffset, this->program->get_cfg_by_index(0)->get_bb_by_index(0));
      IRInstr *instr = dynamic_cast<IRInstr *>(subInstr);
      this->program->get_cfg_by_index(0)->get_bb_by_index(0)->add_IRInstr(instr);
    }

    return maxOffset;
  }

  // Method associated with the '*' sign in an expression
  virtual antlrcpp::Any visitMultExpr(ifccParser::MultExprContext *ctx) override
  {
    // Gets the value of the right and left side of an expression as an offset
    int offsetLeft = visit(ctx->expr(0));
    int offsetRight = visit(ctx->expr(1));

    // Updates the current maximum offset
    this->maxOffset += 4;
    // And adds a new temporary variable in the symbol table
    this->program->get_cfg_by_index(0)->getSymbolTable()->insert({"tmp" + std::to_string(this->maxOffset), this->maxOffset});

    // Adds a new MUL instruction in the current BB
    Mul *mulInstr = new Mul(offsetLeft, offsetRight, maxOffset, this->program->get_cfg_by_index(0)->get_bb_by_index(0));
    IRInstr *instr = dynamic_cast<IRInstr *>(mulInstr);
    this->program->get_cfg_by_index(0)->get_bb_by_index(0)->add_IRInstr(instr);

    return maxOffset;
  }

  // Method associated with the '&' sign in an expression
  virtual antlrcpp::Any visitANDExpr(ifccParser::ANDExprContext *ctx) override
  {
    // Gets the value of the right and left side of an expression as an offset
    int offsetLeft = visit(ctx->expr(0));
    int offsetRight = visit(ctx->expr(1));

    // Updates the current maximum offset
    this->maxOffset += 4;
    // And adds a new temporary variable in the symbol table
    this->program->get_cfg_by_index(0)->getSymbolTable()->insert({"tmp" + std::to_string(this->maxOffset), this->maxOffset});

    // Adds a new AND instruction in the current BB
    And *andInstr = new And(offsetLeft, offsetRight, maxOffset, this->program->get_cfg_by_index(0)->get_bb_by_index(0));
    IRInstr *instr = dynamic_cast<IRInstr *>(andInstr);
    this->program->get_cfg_by_index(0)->get_bb_by_index(0)->add_IRInstr(instr);

    return maxOffset;
  }

  // Method associated with the '^' sign in an expression
  virtual antlrcpp::Any visitXORExpr(ifccParser::XORExprContext *ctx) override
  {
    // Gets the value of the right and left side of an expression as an offset
    int offsetLeft = visit(ctx->expr(0));
    int offsetRight = visit(ctx->expr(1));

    // Updates the current maximum offset...
    this->maxOffset += 4;
    // ...and adds a new temporary variable in the symbol table
    this->program->get_cfg_by_index(0)->getSymbolTable()->insert({"tmp" + std::to_string(this->maxOffset), this->maxOffset});

    // Creates a new XOR instruction in the current BB
    Xor *xorInstr = new Xor(offsetLeft, offsetRight, maxOffset, this->program->get_cfg_by_index(0)->get_bb_by_index(0));
    IRInstr *instr = dynamic_cast<IRInstr *>(xorInstr);
    this->program->get_cfg_by_index(0)->get_bb_by_index(0)->add_IRInstr(instr);

    return maxOffset;
  }

  // Method associated with the '|' sign in an expression
  virtual antlrcpp::Any visitORExpr(ifccParser::ORExprContext *ctx) override
  {
    // Gets the value of right and left side of the expression as offset
    int offsetLeft = visit(ctx->expr(0));
    int offsetRight = visit(ctx->expr(1));

    // Updates the current maximum...
    this->maxOffset += 4;
    // ... and inserts a new tmp var in the symbol table
    this->program->get_cfg_by_index(0)->getSymbolTable()->insert({"tmp" + std::to_string(this->maxOffset), this->maxOffset});

    // Creates a new instruction for the logical OR in the current BB
    Or *orInstr = new Or(offsetLeft, offsetRight, maxOffset, this->program->get_cfg_by_index(0)->get_bb_by_index(0));
    IRInstr *instr = dynamic_cast<IRInstr *>(orInstr);
    this->program->get_cfg_by_index(0)->get_bb_by_index(0)->add_IRInstr(instr);

    return maxOffset;
  }

  /*
  * FUNCTION CALL METHOD
  */

  // Method associated with calling a function
  virtual antlrcpp::Any visitFunctionCallSeul(ifccParser::FunctionCallSeulContext *ctx) override
  {
    int offsetArg = visit(ctx->expr(0));
    // Gets the name of the function to be called
    std::string functionName = ctx->ID()->getText();

    // Specific case of the putchar function
    if (functionName == "putchar")
    {
      functionName = "putchar@PLT";
    }

    // Creates a new call instruction in the current BB for the current function
    Call *callInstr = new Call(offsetArg, functionName, this->program->get_cfg_by_index(0)->get_bb_by_index(0));
    IRInstr *instr = dynamic_cast<IRInstr *>(callInstr);
    this->program->get_cfg_by_index(0)->get_bb_by_index(0)->add_IRInstr(instr);
    return 0;
  }

  /*
  * CONDITIONAL STATEMENT METHODS
  */

  // Method associated with the 'if' keyword
  virtual antlrcpp::Any visitIfStatement(ifccParser::IfStatementContext *ctx) override
  {
    // Visiting what's coming next before actually working
    visitChildren(ctx);

    // Creates the write instruction in the current BB in order to have a new label on which we can jump eventually
    Write_label *write_labelInstr = new Write_label(".L" + to_string(this->ifCounter), this->program->get_cfg_by_index(0)->get_bb_by_index(0));
    IRInstr *instr = dynamic_cast<IRInstr *>(write_labelInstr);
    this->program->get_cfg_by_index(0)->get_bb_by_index(0)->add_IRInstr(instr);
    this->ifCounter++;
    return 0;
  }

  // Method associated with the '==' sign in a comparison
  virtual antlrcpp::Any visitEqualComparison(ifccParser::EqualComparisonContext *ctx) override
  {
    // Gets the left/right value as offsets and the destination label
    int offsetLeft = visit(ctx->expr(0));
    int offsetRight = visit(ctx->expr(1));
    std::string labelDestination = ".L" + to_string(this->ifCounter);

    // Creates a new instruction in the current BB to compare these two values
    Cmp_eq *cmp_eqInstr = new Cmp_eq(offsetLeft, offsetRight, ".L" + to_string(this->ifCounter), "==", this->program->get_cfg_by_index(0)->get_bb_by_index(0));
    IRInstr *instr = dynamic_cast<IRInstr *>(cmp_eqInstr);
    this->program->get_cfg_by_index(0)->get_bb_by_index(0)->add_IRInstr(instr);
    return 0;
  }

  // Method associated with the '!=' sign in a comparison
  virtual antlrcpp::Any visitNotEqualComparison(ifccParser::NotEqualComparisonContext *ctx) override
  {
    // Gets left/right value as offsets and the destination label
    int offsetLeft = visit(ctx->expr(0));
    int offsetRight = visit(ctx->expr(1));
    std::string labelDestination = ".L" + to_string(this->ifCounter);

    // Creates a new instruction in the current CFG to compare these two values
    Cmp_eq *cmp_eqInstr = new Cmp_eq(offsetLeft, offsetRight, ".L" + to_string(this->ifCounter), "!=", this->program->get_cfg_by_index(0)->get_bb_by_index(0));
    IRInstr *instr = dynamic_cast<IRInstr *>(cmp_eqInstr);
    this->program->get_cfg_by_index(0)->get_bb_by_index(0)->add_IRInstr(instr);
    return 0;
  }

  // Method associated with the '<' sign in a comparison
  virtual antlrcpp::Any visitLowerComparison(ifccParser::LowerComparisonContext *ctx) override
  {
    // Gets left/right value as offsets and the destination label
    int offsetLeft = visit(ctx->expr(0));
    int offsetRight = visit(ctx->expr(1));
    std::string labelDestination = ".L" + to_string(this->ifCounter);

    // Creates a new instruction in the current CFG to compare these two values
    Cmp_eq *cmp_eqInstr = new Cmp_eq(offsetLeft, offsetRight, ".L" + to_string(this->ifCounter), "<", this->program->get_cfg_by_index(0)->get_bb_by_index(0));
    IRInstr *instr = dynamic_cast<IRInstr *>(cmp_eqInstr);
    this->program->get_cfg_by_index(0)->get_bb_by_index(0)->add_IRInstr(instr);

    return 0;
  }

  // Method associated with the '>' sign in a comparison
  virtual antlrcpp::Any visitGreaterComparison(ifccParser::GreaterComparisonContext *ctx) override
  {
    // Gets left / right value as offsets and the destination label
    int offsetLeft = visit(ctx->expr(0));
    int offsetRight = visit(ctx->expr(1));
    std::string labelDestination = ".L" + to_string(this->ifCounter);

    // Creates a new instruction in the current CFG to compare these two values
    Cmp_eq *cmp_eqInstr = new Cmp_eq(offsetLeft, offsetRight, ".L" + to_string(this->ifCounter), ">", this->program->get_cfg_by_index(0)->get_bb_by_index(0));
    IRInstr *instr = dynamic_cast<IRInstr *>(cmp_eqInstr);
    this->program->get_cfg_by_index(0)->get_bb_by_index(0)->add_IRInstr(instr);

    return 0;
  }

  // Method associated with the keyword 'else' after an 'if' statement
  virtual antlrcpp::Any visitElse(ifccParser::ElseContext *ctx) override
  {
    this->ifCounter++;

    // Creates a new instruction of jumping to a particular label as an instruction in the CFG
    Jmp *jmpInstr = new Jmp(".L" + to_string(this->ifCounter), this->program->get_cfg_by_index(0)->get_bb_by_index(0));
    IRInstr *instr = dynamic_cast<IRInstr *>(jmpInstr);
    this->program->get_cfg_by_index(0)->get_bb_by_index(0)->add_IRInstr(instr);

    // Creates a new instruction in the current CFG for writing a new label
    Write_label *write_labelInstrElse = new Write_label(".L" + to_string(this->ifCounter - 1), this->program->get_cfg_by_index(0)->get_bb_by_index(0));
    IRInstr *instrElse = dynamic_cast<IRInstr *>(write_labelInstrElse);
    this->program->get_cfg_by_index(0)->get_bb_by_index(0)->add_IRInstr(instrElse);

    // Visit the next block
    visit(ctx->bloc());

    return 0;
  }

  // Method used if there is no particular 'else' keyword after an 'if'
  virtual antlrcpp::Any visitNoElse(ifccParser::NoElseContext *ctx) override
  {
    return 0;
  }

  // Method associated with the keyword 'While'
  virtual antlrcpp::Any visitWhileStatement(ifccParser::WhileStatementContext *ctx) override
  {
    int sortie = this->ifCounter;
    int boucle = this->ifCounter + 1;

    // Creates a new label with the current index as an instruction in the current CFG
    Write_label *write_labelInstrLoop = new Write_label(".L" + to_string(boucle), this->program->get_cfg_by_index(0)->get_bb_by_index(0));
    IRInstr *instrLoop = dynamic_cast<IRInstr *>(write_labelInstrLoop);
    this->program->get_cfg_by_index(0)->get_bb_by_index(0)->add_IRInstr(instrLoop);

    // Checks the current condition
    visit(ctx->condition());

    this->ifCounter += 2;

    // Checks the current block...
    visit(ctx->bloc());

    // Creates a new instruction in the current CFG in order to jump to the newly created label
    Jmp *jmpInstr = new Jmp(".L" + to_string(boucle), this->program->get_cfg_by_index(0)->get_bb_by_index(0));
    IRInstr *instr = dynamic_cast<IRInstr *>(jmpInstr);
    this->program->get_cfg_by_index(0)->get_bb_by_index(0)->add_IRInstr(instr);

    // Creates a new instruction in the current CFG for the end label
    Write_label *write_labelInstrEnd = new Write_label(".L" + to_string(sortie), this->program->get_cfg_by_index(0)->get_bb_by_index(0));
    IRInstr *instrEnd = dynamic_cast<IRInstr *>(write_labelInstrEnd);
    this->program->get_cfg_by_index(0)->get_bb_by_index(0)->add_IRInstr(instrEnd);

    return 0;
  }

  /**
   * UTIL METHODS
   */

  // Util method that removes last char from a char*
  // Example : 'PLD-COMP' -> 'PLD-COM'
  std::string removeLastCharFromString(std::string str)
  {
    return str.substr(0, str.size() - 1);
  }

  // Util method that creates a temporary variable given a integer value in parameter
  int createTemporaryFromConstant(int val)
  {
    // Updates the offset with the size of an integer
    this->maxOffset += 4;
    // Creates a new temporary name with the offset (tmp4 for example)
    std::string temporaryName = "tmp" + std::to_string(this->maxOffset);
    // Inserts this new variable in both tables (symbol/type)
    this->program->get_cfg_by_index(0)->getSymbolTable()->insert({"tmp" + std::to_string(this->maxOffset), this->maxOffset});
    this->program->get_cfg_by_index(0)->getTypeTable()->insert({"tmp" + std::to_string(this->maxOffset), "int"});
    // Uses instructions with this new variable
    ldconst *ldconstInstr = new ldconst(val, this->maxOffset, temporaryName, this->program->get_cfg_by_index(0)->get_bb_by_index(0));
    IRInstr *instr = dynamic_cast<IRInstr *>(ldconstInstr);
    this->program->get_cfg_by_index(0)->get_bb_by_index(0)->add_IRInstr(instr);

    // returns the current offset
    return this->maxOffset;
  }

  // Method that creates a temporary variable given a character in parameter.
  int createTemporaryFromConstant(char val)
  {
    // Updates the offset with the size of a character
    this->maxOffset += 1;
    // Creates a new temporary name with the offset (tmp1 stands for a temporary variable which offset is -4)
    std::string temporaryName = "tmp" + std::to_string(this->maxOffset);
    // Inserts this variable in both tables (symbol/type)
    this->program->get_cfg_by_index(0)->getSymbolTable()->insert({"tmp" + std::to_string(this->maxOffset), this->maxOffset});
    this->program->get_cfg_by_index(0)->getTypeTable()->insert({"tmp" + std::to_string(this->maxOffset), "char"});
    // Uses instructions with this new variable
    ldconst *ldconstInstr = new ldconst(val, this->maxOffset, temporaryName, this->program->get_cfg_by_index(0)->get_bb_by_index(0));
    IRInstr *instr = dynamic_cast<IRInstr *>(ldconstInstr);
    this->program->get_cfg_by_index(0)->get_bb_by_index(0)->add_IRInstr(instr);

    // returns the current offset
    return this->maxOffset;
  }

  // Protected methods and attributes of the class
protected:
  int maxOffset;
  int ifCounter;
  Program *program;
};
