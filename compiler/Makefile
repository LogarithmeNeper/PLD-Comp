OUTPUT=output
GENERATED=antlr4-generated
GRAMMAR=ifcc.g4

#override with your local installation
ANTLR4_BINDIR=/usr/bin
ANTLR4_INCDIR=/shares/public/tp/ANTLR4-CPP/antlr4-runtime
ANTLR4_LIBDIR=/shares/public/tp/ANTLR4-CPP/lib

CC=clang++
CCARGS=-g -c -I $(ANTLR4_INCDIR) -I $(GENERATED) -std=c++11 -Wno-defaulted-function-deleted -Wno-unknown-warning-option
LDARGS=-g

all: ifcc

ifcc: dirs antlr  main.cpp visitor.cpp visitor.h IR.h ldconst.cpp ldconst.h Copy.cpp Copy.h add.cpp add.h sub.cpp sub.h mul.cpp mul.h
	$(CC) $(CCARGS) main.cpp  -o $(OUTPUT)/main.o 
	$(CC) $(CCARGS) $(GENERATED)/ifccBaseVisitor.cpp -o $(OUTPUT)/ifccBaseVisitor.o 
	$(CC) $(CCARGS) $(GENERATED)/ifccLexer.cpp -o $(OUTPUT)/ifccLexer.o 
	$(CC) $(CCARGS) $(GENERATED)/ifccVisitor.cpp -o $(OUTPUT)/ifccVisitor.o 
	$(CC) $(CCARGS) $(GENERATED)/ifccParser.cpp -o $(OUTPUT)/ifccParser.o 
	$(CC) $(CCARGS) visitor.cpp -o $(OUTPUT)/visitor.o 
	$(CC) $(CCARGS) ldconst.cpp -o $(OUTPUT)/ldconst.o
	$(CC) $(CCARGS) Copy.cpp -o $(OUTPUT)/copy.o
	$(CC) $(CCARGS) add.cpp -o $(OUTPUT)/add.o
	$(CC) $(CCARGS) sub.cpp -o $(OUTPUT)/sub.o
	$(CC) $(CCARGS) mul.cpp -o $(OUTPUT)/mul.o
	$(CC) $(LDARGS) $(OUTPUT)/main.o $(OUTPUT)/ifccBaseVisitor.o $(OUTPUT)/ifccLexer.o $(OUTPUT)/ifccVisitor.o $(OUTPUT)/ifccParser.o $(OUTPUT)/visitor.o $(OUTPUT)/ldconst.o $(OUTPUT)/copy.o $(OUTPUT)/add.o $(OUTPUT)/sub.o $(OUTPUT)/mul.o $(ANTLR4_LIBDIR)/libantlr4-runtime.a -o ifcc

antlr: $(GRAMMAR)
	$(ANTLR4_BINDIR)/antlr4 -visitor -no-listener -Dlanguage=Cpp -o $(GENERATED) $(GRAMMAR)

dirs:
	mkdir -p $(OUTPUT) 
	mkdir -p $(GENERATED) 

clean:
	rm -rf $(OUTPUT)
	rm -rf $(GENERATED)
