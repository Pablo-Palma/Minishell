
AST ESTRUCTURE

-Command: ls | grep subject | wc
-Estructure:
----------------------- |
						|
      Pipe
     /    \
   ls     Pipe
          /    \
     grep subject  wc 	|
------------------------|

Análisis de tu Función "build_ast.c"
La función actualmente:

1.Divide la entrada en tokens separados por |.
2.Itera sobre estos tokens.
3.Para el primer token (i == 0), crea un nodo de comando.
4.Para los tokens siguientes, crea un nodo pipe y un nodo de comando para cada uno.
5Asigna el nodo de comando actual al lado derecho del nodo pipe y el comando o pipe previo al lado izquierdo.
