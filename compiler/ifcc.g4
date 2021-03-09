grammar ifcc;

axiom : prog       
      ;

prog : 'int' 'main' '(' ')' '{' declaration RETURN CONST ';' '}' ;

// STATEMENT : DECLARATION ;
declaration : 'int' VARIABLE ';' ;

RETURN : 'return' ;
CONST : [0-9]+ ;
VARIABLE : [a-z][a-zA-Z0-9_]* ;
COMMENT : '/*' .*? '*/' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS    : [ \t\r\n] -> channel(HIDDEN);
