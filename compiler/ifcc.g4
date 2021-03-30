grammar ifcc;

axiom : prog       
      ;

prog : 'int' 'main' '(' ')' '{' declaration* affectation* ret ';' '}' ;
declaration : 'int' (declarationvar ',')* declarationvar ';' ;
declarationvar : VARIABLE #DeclarationSeule
            | VARIABLE '=' expr #DeclarationInitialisee ;
            
affectation : VARIABLE '=' expr ';';

expr : '(' expr ')' #parExprexpr
      | '*' expr #multExpr
      | expr ('+'|'-') expr #minusAddExpr
      | CONST #constExpr
      | VARIABLE #varExpr
      ; 

ret : RETURN expr;

RETURN : 'return' ;
CONST : [0-9]+ ;
VARIABLE : [a-z][a-zA-Z0-9_]* ;
COMMENT : '/*' .*? '*/' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS    : [ \t\r\n] -> channel(HIDDEN);
