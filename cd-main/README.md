1)https://github.com/duckmaniac/simple-calculator <br>
2,3) lex scanner.l <br>
gcc lex.yy.c -o scanner -ll <br>
./scanner <br>
4) bison -d calculator.y <br>
gcc calculator.tab.c -o calculator -lfl <br>
./calculator <br>
