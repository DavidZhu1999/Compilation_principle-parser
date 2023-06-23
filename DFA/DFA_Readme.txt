START
	[space | like: \t]     --> START
	[letter  | _ ]         --> [ID   | KEYWORD]
	digit                  --> NUM1
	<	                   --> [LT	 | EQORLT]
	!                      --> [NOT  | NOTEQ]
	>	                   --> [GT   | EQORGT]
	=                      --> [EQ   | ASSIGN]
	/	                   --> [DIV  | NOTE]
	&	                   --> [ADDR | AND]
	:                      --> ENDFUNC
	-	                   --> [MINUS | BGFUNC1]
	|                      --> OR
	\	                   --> ENTER
	[+ | * | , | ; | . | % | ( | ) | [ | ] | { | } | ' | ' | " | " ] --> done(tokentype = (PLUS | MTPLUS | COMMA | SEMI | DOT | MOD | LPAR | RPAR | MLPAR | MRPAR | GLPAR | GRPAR | LSQUOTE | RSQUOTE | LDQUOTE | RDQUOTE ), tokenString = empty) 


ID | KEYWORD
	[ letter | _ | digit ] --> [(ID | KEYWORD) | done(tokentype = (ID | KEYWORD), tokenString = String) ]



NUM1
	digit  --> [NUM1 | NUM2]
	lambda --> done(tokentype = NUM, tokenString = number)
NUM2
	digit --> [ NUM2 | done(tokentype = NUM, tokenString = number) ]



LT  | EQORLT
	other -->  done(tokentype = LT, tokenString = empty)
	=     --> done(tokentype = EQORLT, tokenString = empty)
	
	
	
NOT | NOTEQ
	=     --> done(tokentype = NOTEQ, tokenString = empty)
	other --> done(tokentype = NOT, tokenString = empty)
	
	
	
GT  | EQORGT
	other --> done(tokentype = GT, tokenString = empty)
	=     --> done(tokentype = EQORGT, tokenString = empty)
	
	
	
	
EQ | ASSIGN
	other --> done(tokentype = EQ, tokenString = empty)
	=     --> done(tokentype = ASSIGN, tokenString = empty)
	
	
	
DIV
	other --> done(tokentype = DIV, tokenString = empty)
	*     --> Comment1
	/     --> [ Comment2 | done(tokentype = NOTE, tokenString = String) ]
Comment1
	other --> Comment1
	*     --> Comment3
Comment3
	lambda --> Comment1
	/      --> done(tokentype = NOTE, tokenString = String)
Comment2
	[ other | lambda] --> [ Comment2 | done(tokentype = NOTE, tokenString = String) ]



ADDER | AND
	other --> done(tokentype = ADDR, tokenString = empty)
	&     --> done(tokentype = AND, tokenString = empty)



ENDFUNC
	other --> ERROR
	)     --> done(tokentype = ENDFUNC, tokenString = empty)
	
	

MINUS | BGFUNC1
	other --> done(tokentype = MINUS, tokenString = empty)
	-     --> BGFUNC2
BGFUNC2
	>     --> done(tokentype = BGFUNC, tokenString = empty)
	other --> ERROR
	
	
	
OR
	|     --> done(tokentype = OR, tokenString = empty)
	other --> ERROR
	
	

Enter
	n     --> done(tokentype = ENTER, tokenString = empty)
