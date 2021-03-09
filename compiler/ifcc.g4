grammar ifcc;

axiom : prog       
      ;

prog : 'int' 'main' '(' ')' '{' declaration affectation* RETURN CONST ';' '}' ;
declaration : 'int' VARIABLENF* VARIABLE ';' ;
affectation : VARIABLE '=' CONST ';' ;

RETURN : 'return' ;
CONST : [0-9]+ ;
VARIABLENF : [a-z][a-zA-Z0-9_]*',' ;
VARIABLE : [a-z][a-zA-Z0-9_]* ;
COMMENT : '/*' .*? '*/' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS    : [ \t\r\n] -> channel(HIDDEN);
