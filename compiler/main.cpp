/*************************************************************************
Main : entry point of the program.
*************************************************************************/

// INCLUDE

// System Include
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

// ANTLR Include
#include "antlr4-runtime.h"
#include "antlr4-generated/ifccLexer.h"
#include "antlr4-generated/ifccParser.h"
#include "antlr4-generated/ifccBaseVisitor.h"

// Personal Include
#include "visitor.h"
#include "pre-visitor.h"

// Namespaces
using namespace antlr4;
using namespace std;

// Entry Point of the program.
int main(int argn, const char **argv)
{
  stringstream in;
  if (argn == 2)
  {
    ifstream lecture(argv[1]);
    in << lecture.rdbuf();
  }
  ANTLRInputStream input(in.str());
  ifccLexer lexer(&input);
  CommonTokenStream tokens(&lexer);

  tokens.fill();
  /*for (auto token : tokens.getTokens()) {
    std::cout << token->toString() << std::endl;
  }*/

  ifccParser parser(&tokens);
  tree::ParseTree *tree = parser.axiom();
  // If out parser tree does not find any errors, ...
  if (parser.getNumberOfSyntaxErrors() == 0)
  {
    Visitor visitor;
    PreVisitor preVisitor;

    // we make a first visit before anything else
    preVisitor.visit(tree);

    // if the code is correct...
    if (preVisitor.getCorrectCode())
    {
      // then we can use the visitor and generate
      visitor.visit(tree);
    }
    else
    {
      // otherwise we exit with an exception code
      exit(1);
    }
  }
  else
  {
    // otherwise we exit with an exception code
    exit(1);
  }
  // then, we exit main with the code.
  return 0;
}
