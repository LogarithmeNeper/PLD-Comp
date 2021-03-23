grammar ifcc;

axiom : prog       
      ;

prog : 'int' 'main' '(' ')' '{' declaration* affectation* ret ';' '}' ;

declaration : 'int' VARIABLENF* VARIABLE ';' ;
affectation : VARIABLE '=' CONST ';' #ConstAffectation
      | VARIABLE '=' VARIABLE ';' #VarToVarAffectation
      | VARIABLE '=' expr ';' #ExprAffectation
      ;

expr : expr '*' expr #multExpr
      | expr '+' expr #addExpr
      | expr '-' expr #sublExpr
      | CONST #constExpr
      | VARIABLE #varExpr
      | '(' expr ')' #parExpr
      ; 

ret : RETURN expr;

RETURN : 'return' ;
CONST : [0-9]+ ;
VARIABLENF : [a-z][a-zA-Z0-9_]*',' ;
VARIABLE : [a-z][a-zA-Z0-9_]* ;
COMMENT : '/*' .*? '*/' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS    : [ \t\r\n] -> channel(HIDDEN);
