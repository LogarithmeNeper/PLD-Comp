grammar ifcc;

axiom : prog       
      ;

prog : 'int' 'main' '(' ')' '{' declaration* affectation* RETURN CONST ';' '}' ;
declaration : 'int' (declarationvar ',')* declarationvar ';' ;
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

valRet : VARIABLE #varReturn
      | CONST #constReturn
      ;

declarationvar : VARIABLE #DeclarationSeule
            | VARIABLE '=' CONST #DeclarationInitialiseeConst
            | VARIABLE '=' VARIABLE #DeclarationInitialiseeVar
              ;
RETURN : 'return' ;
CONST : [0-9]+ ;
VARIABLE : [a-z][a-zA-Z0-9_]* ;
COMMENT : '/*' .*? '*/' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS    : [ \t\r\n] -> channel(HIDDEN);
