# Compilador-ESHTML
Este proyecto se centra en crear un compilador que pueda traducir instrucciones en español a código HTML. Su propósito principal es hacer más simple el aprendizaje de HTML para quienes comienzan, ayudándoles a construir estructuras web básicas con un lenguaje más familiar y fácil de entender. 

### Comandos Flex y bison

1. Procesar el código del parser en Bison:

```
bison -d parser.y
```

2. Procesar el código del parser en Flex:

```
flex lexer.l
```

3. Generar archivo .exe:

```
gcc lex.yy.c parser.tab.c
```

4. En caso de que exista el .exe o este recién generado:

```
./a
```