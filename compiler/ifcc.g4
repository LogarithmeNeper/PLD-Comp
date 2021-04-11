grammar ifcc;

axiom : prog       
      ;

prog : 'int' 'main' '(' ')' bloc ;
bloc : '{' instruction* '}' ;
instruction : (declaration ';' | assignment ';' | expr ';'| ret ';' | ifStatement | whileStatement) ;

whileStatement : WHILE '(' condition ')' bloc ;

ifStatement : IF '(' condition ')' bloc elseBloc ;
condition : expr EQUALCOMP expr #equalComparison
            | expr NOTEQUALCOMP expr #notEqualComparison
            | expr LOWERCOMP expr #lowerComparison
            | expr GREATERCOMP expr #greaterComparison
            ;

elseBloc : ELSE bloc #else
            |#noElse;

declaration : (declarationint | declarationchar | declaration64) ;
declarationint : 'int' (declarationvarint ',')* declarationvarint ;
declarationchar : 'char' (declarationvarchar ',')* declarationvarchar;
declaration64 : 'int64_t' (declarationvar64',')* declarationvar64;

declarationvarint : ID #DeclarationSeuleInt
            | <assoc=right> ID '=' expr #DeclarationInitialiseeIntExpr
            | <assoc=right> ID '=' assignment #DeclarationInitialiseeIntAssign
              ;

declarationvarchar : ID #DeclarationSeuleChar
            | <assoc=right> ID '=' expr #DeclarationInitialiseeCharExpr
            | <assoc=right> ID '=' assignment #DeclarationInitialiseeCharAssign
              ;

declarationvar64 : ID #DeclarationSeule64
            | <assoc=right> ID '=' expr #DeclarationInitialisee64Expr
            | <assoc=right> ID '=' assignment #DeclarationInitialisee64Assign
              ;

expr : '(' expr ')' #parExpr
      | expr '*' expr #multExpr
      | expr ('+'|'-') expr #minusAddExpr
      | expr '&' expr #ANDExpr
      | expr '^' expr #XORExpr
      | expr '|' expr #ORExpr
      | CONST #constExpr
      | ID #varExpr
      | CONSTCHAR #constCharExpr
      | ID '(' expr* ')' #FunctionCallSeul
      ; 

assignment : <assoc=right> ID '=' expr #assignmentExpr
            | <assoc=right> ID '=' assignment #assignmentChain
            ;

ret : RETURN expr;

IF : 'if' ;
ELSE : 'else' ;
WHILE : 'while' ;
EQUALCOMP : '==' ;
LOWERCOMP : '<' ;
GREATERCOMP : '>' ;
NOTEQUALCOMP : '!=';
RETURN : 'return' ;
CONST : [0-9]+ ;
CONSTCHAR : '\'' [!-~] '\'' ; //matche tous les caractères ASCII de 0x20 (!) à 0x7E (~), ne prend pas en compte l'espace car cause des erreurs
ID : [a-z][a-zA-Z0-9_]* ;
COMMENT : '/*' .*? '*/' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS    : [ \t\r\n] -> channel(HIDDEN);
