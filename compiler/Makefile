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

ifcc: dirs antlr  main.cpp visitor.cpp visitor.h IR.h ldconst.cpp ldconst.h copy.cpp copy.h add.cpp add.h sub.cpp sub.h mul.cpp mul.h basic_block.cpp cfg.cpp program.cpp call.cpp call.h
	$(CC) $(CCARGS) main.cpp  -o $(OUTPUT)/main.o 
	$(CC) $(CCARGS) $(GENERATED)/ifccBaseVisitor.cpp -o $(OUTPUT)/ifccBaseVisitor.o 
	$(CC) $(CCARGS) $(GENERATED)/ifccLexer.cpp -o $(OUTPUT)/ifccLexer.o 
	$(CC) $(CCARGS) $(GENERATED)/ifccVisitor.cpp -o $(OUTPUT)/ifccVisitor.o 
	$(CC) $(CCARGS) $(GENERATED)/ifccParser.cpp -o $(OUTPUT)/ifccParser.o 
	$(CC) $(CCARGS) visitor.cpp -o $(OUTPUT)/visitor.o 
	$(CC) $(CCARGS) pre-visitor.cpp -o $(OUTPUT)/pre-visitor.o
	$(CC) $(CCARGS) ldconst.cpp -o $(OUTPUT)/ldconst.o
	$(CC) $(CCARGS) copy.cpp -o $(OUTPUT)/copy.o
	$(CC) $(CCARGS) add.cpp -o $(OUTPUT)/add.o
	$(CC) $(CCARGS) sub.cpp -o $(OUTPUT)/sub.o
	$(CC) $(CCARGS) mul.cpp -o $(OUTPUT)/mul.o
	$(CC) $(CCARGS) and.cpp -o $(OUTPUT)/and.o
	$(CC) $(CCARGS) or.cpp -o $(OUTPUT)/or.o
	$(CC) $(CCARGS) xor.cpp -o $(OUTPUT)/xor.o
	$(CC) $(CCARGS) basic_block.cpp -o $(OUTPUT)/basic_block.o
	$(CC) $(CCARGS) cfg.cpp -o $(OUTPUT)/cfg.o
	$(CC) $(CCARGS) program.cpp -o $(OUTPUT)/program.o
	$(CC) $(CCARGS) call.cpp -o $(OUTPUT)/call.o
	$(CC) $(CCARGS) cmp_eq.cpp -o $(OUTPUT)/cmp_eq.o
	$(CC) $(CCARGS) write_label.cpp -o $(OUTPUT)/write_label.o
	$(CC) $(CCARGS) jmp.cpp -o $(OUTPUT)/jmp.o
	$(CC) $(LDARGS) $(OUTPUT)/main.o $(OUTPUT)/ifccBaseVisitor.o $(OUTPUT)/ifccLexer.o $(OUTPUT)/ifccVisitor.o $(OUTPUT)/ifccParser.o $(OUTPUT)/visitor.o $(OUTPUT)/ldconst.o $(OUTPUT)/copy.o $(OUTPUT)/add.o $(OUTPUT)/sub.o $(OUTPUT)/mul.o $(OUTPUT)/basic_block.o $(OUTPUT)/cfg.o $(OUTPUT)/program.o $(OUTPUT)/call.o $(OUTPUT)/cmp_eq.o $(OUTPUT)/write_label.o $(OUTPUT)/jmp.o $(OUTPUT)/or.o $(OUTPUT)/xor.o $(OUTPUT)/and.o $(ANTLR4_LIBDIR)/libantlr4-runtime.a -o ifcc

antlr: $(GRAMMAR)
	$(ANTLR4_BINDIR)/antlr4 -visitor -no-listener -Dlanguage=Cpp -o $(GENERATED) $(GRAMMAR)

dirs:
	mkdir -p $(OUTPUT) 
	mkdir -p $(GENERATED) 

clean:
	rm -rf $(OUTPUT)
	rm -rf $(GENERATED)
