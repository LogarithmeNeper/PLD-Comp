grammar ifcc;

axiom : prog       
      ;

prog : definitionFunction* 'int' 'main' '(' ')' bloc ;
definitionFunction : type ID '(' type* ')' bloc;
type : (INT | CHAR | INT64 | VOID);
bloc : '{' instruction* '}' ;
instruction : (declaration ';' | expr ';'| ret ';') ;


declaration : (declarationint | declarationchar | declaration64) ;
declarationint : 'int' (declarationvarint ',')* declarationvarint ;
declarationchar : 'char' (declarationvarchar ',')* declarationvarchar;
declaration64 : 'int64_t' (declarationvar64',')* declarationvar64;

declarationvarint : ID #DeclarationSeuleInt
            | ID '=' expr #DeclarationInitialiseeInt
              ;

declarationvarchar : ID #DeclarationSeuleChar
            | ID '=' expr #DeclarationInitialiseeChar
              ;

declarationvar64 : ID #DeclarationSeule64
            | ID '=' expr #DeclarationInitialisee64
              ;

expr : '(' expr ')' #parExpr
      | expr '*' expr #multExpr
      | expr ('+'|'-') expr #minusAddExpr
      | ID '=' expr #affectation
      | CONST #constExpr
      | ID #varExpr
      | CONSTCHAR #constCharExpr
      | ID '(' expr* ')' #FunctionCallSeul
      ; 

ret : RETURN expr;

INT : 'int';
CHAR : 'char';
INT64 : 'int64_t';
VOID : 'void';
RETURN : 'return' ;
CONST : [0-9]+ ;
CONSTCHAR : '\'' [!-~] '\'' ; //matche tous les caractères ASCII de 0x20 (!) à 0x7E (~), ne prend pas en compte l'espace car cause des erreurs
ID : [a-z][a-zA-Z0-9_]* ;
COMMENT : '/*' .*? '*/' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS    : [ \t\r\n] -> channel(HIDDEN);
