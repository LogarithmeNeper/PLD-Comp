grammar ifcc;

axiom : prog       
      ;

prog : 'int' 'main' '(' ')' '{' declaration* affectation* ret ';' '}' ;
declaration : (declarationint | declarationchar | declaration64) ;
declarationint : 'int' declarationvarint* declarationvarint ';' ;
declarationchar : 'char' declarationvarchar* declarationvarchar ';';
declaration64 : 'int64_t' declarationvar64* declarationvar64 ';' ;

declarationvarint : VARIABLE COMMA? #DeclarationSeuleInt
            | VARIABLE '=' CONST COMMA? #DeclarationInitialiseeConstInt
            | VARIABLE '=' VARIABLE COMMA? #DeclarationInitialiseeVarInt
              ;

declarationvarchar : VARIABLE COMMA? #DeclarationSeuleChar
            | VARIABLE '=' CONST COMMA? #DeclarationInitialiseeConstCharNum
            | VARIABLE '=' '\'' CONSTCHAR '\'' COMMA? #DeclarationInitialiseeConstChar
            | VARIABLE '=' VARIABLE COMMA? #DeclarationInitialiseeVarChar
              ;

declarationvar64 : VARIABLE COMMA? #DeclarationSeule64
            | VARIABLE '=' CONST COMMA? #DeclarationInitialiseeConst64
            | VARIABLE '=' VARIABLE COMMA? #DeclarationInitialiseeVar64
              ;

affectation : VARIABLE '=' expr ';';

expr : expr '*' expr #multExpr
      | expr ('+'|'-') expr #minusAddExpr
      | CONST #constExpr
      | VARIABLE #varExpr
      | '(' expr ')' #parExpr
      ; 

ret : RETURN expr;

COMMA : ',';
RETURN : 'return' ;
CONST : [0-9]+ ;
CONSTCHAR : [^\\s-~] ;
VARIABLE : [a-z][a-zA-Z0-9_]* ;
COMMENT : '/*' .*? '*/' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS    : [ \t\r\n] -> channel(HIDDEN);
