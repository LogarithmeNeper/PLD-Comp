grammar ifcc;

axiom : prog       
      ;

prog : 'int' 'main' '(' ')' '{' declaration* affectation* ret ';' '}' ;
declaration : (declarationint | declarationchar | declaration64) ;
declarationint : 'int' (declarationvarint ',')* declarationvarint ';' ;
declarationchar : 'char' (declarationvarchar ',')* declarationvarchar ';';
declaration64 : 'int64_t' (declarationvar64',')* declarationvar64 ';' ;

declarationvarint : VARIABLE #DeclarationSeuleInt
            | VARIABLE '=' CONST #DeclarationInitialiseeConstInt
            | VARIABLE '=' VARIABLE #DeclarationInitialiseeVarInt
              ;

declarationvarchar : VARIABLE #DeclarationSeuleChar
            | VARIABLE '=' CONST #DeclarationInitialiseeConstCharNum
            | VARIABLE '=' CONSTCHAR #DeclarationInitialiseeConstChar
            | VARIABLE '=' VARIABLE #DeclarationInitialiseeVarChar
              ;

declarationvar64 : VARIABLE #DeclarationSeule64
            | VARIABLE '=' CONST #DeclarationInitialiseeConst64
            | VARIABLE '=' VARIABLE #DeclarationInitialiseeVar64
              ;

affectation : VARIABLE '=' expr ';';

expr : '(' expr ')' #parExpr
      | expr '*' expr #multExpr
      | expr ('+'|'-') expr #minusAddExpr
      | CONST #constExpr
      | VARIABLE #varExpr
      ; 

ret : RETURN expr;

RETURN : 'return' ;
CONST : [0-9]+ ;
CONSTCHAR : '\'' [!-~] '\'' ; //matche tous les caractères ASCII de 0x20 (!) à 0x7E (~), ne prend pas en compte l'espace car cause des erreurs
VARIABLE : [a-z][a-zA-Z0-9_]* ;
COMMENT : '/*' .*? '*/' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS    : [ \t\r\n] -> channel(HIDDEN);
