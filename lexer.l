%option noyywrap
%{
#include "parser.h"
#include <iostream>
#include <QString>
int columna=0;
%}


letra [a-zñA-ZÑ]
comentario1 "/*"[^'*']*"*/"
comentario2 "//"[^'\n']*"\n"
digito [0-9]
id [a-zñA-ZÑ][a-zñA-ZÑ{0-9}{"_"}]*
numero {digito}+
cadenas "\""[^'\"']*"\""

%%
"clase" {columna=columna+strlen(yylval.TEXT); strcpy (yylval.TEXT,yytext);return clase;}
"returnar" {columna=columna+strlen(yylval.TEXT); strcpy (yylval.TEXT,yytext);return retornar;}
"ninguno" {columna=columna+strlen(yylval.TEXT); strcpy (yylval.TEXT,yytext);return ninguno;}
"ref" {columna=columna+strlen(yylval.TEXT); strcpy (yylval.TEXT,yytext);return ref;}
"caracter" {columna=columna+strlen(yylval.TEXT); strcpy (yylval.TEXT,yytext);return caracter;}
"cadena" {columna=columna+strlen(yylval.TEXT); strcpy (yylval.TEXT,yytext);return cadena;}
"entero" {columna=columna+strlen(yylval.TEXT); strcpy (yylval.TEXT,yytext);return entero;}
"bool" {columna=columna+strlen(yylval.TEXT); strcpy (yylval.TEXT,yytext);return booleano;}
"decattr" {columna=columna+strlen(yylval.TEXT); strcpy (yylval.TEXT,yytext);return decattr;}
"decarr" {columna=columna+strlen(yylval.TEXT); strcpy (yylval.TEXT,yytext);return decarr;}
"este" {columna=columna+strlen(yylval.TEXT); strcpy (yylval.TEXT,yytext);return este;}
"imprimir" {columna=columna+strlen(yylval.TEXT); strcpy (yylval.TEXT,yytext);return imprimir;}
"Principal" {columna=columna+strlen(yylval.TEXT); strcpy (yylval.TEXT,yytext);return Principal;}
"instanciar" {columna=columna+strlen(yylval.TEXT); strcpy (yylval.TEXT,yytext);return instanciar;}
"extiende" {columna=columna+strlen(yylval.TEXT); strcpy (yylval.TEXT,yytext);return extiende;}
"true" {columna=columna+strlen(yylval.TEXT); strcpy (yylval.TEXT,yytext);return true;}
"false" {columna=columna+strlen(yylval.TEXT); strcpy (yylval.TEXT,yytext);return false;}
"para_todos" {columna=columna+strlen(yylval.TEXT); strcpy (yylval.TEXT,yytext);return para_todos;}
"protegido" {columna=columna+strlen(yylval.TEXT); strcpy (yylval.TEXT,yytext);return protegido;}
"privado" {columna=columna+strlen(yylval.TEXT); strcpy (yylval.TEXT,yytext);return privado;}
"traer" {columna=columna+strlen(yylval.TEXT); strcpy (yylval.TEXT,yytext);return traer;}
"&&" {columna=columna+strlen(yylval.TEXT); strcpy (yylval.TEXT,yytext);return and;}
"||" {columna=columna+strlen(yylval.TEXT); strcpy (yylval.TEXT,yytext);return or;}
[!] {columna=columna+strlen(yylval.TEXT); strcpy (yylval.TEXT,yytext);return not;}
"repetir_mientras" {columna=columna+strlen(yylval.TEXT); strcpy (yylval.TEXT,yytext);return repetir_mientras;}
"para" {columna=columna+strlen(yylval.TEXT); strcpy (yylval.TEXT,yytext);return para;}
"detener" {columna=columna+strlen(yylval.TEXT); strcpy (yylval.TEXT,yytext);return detener;}
"si_cumple" {columna=columna+strlen(yylval.TEXT); strcpy (yylval.TEXT,yytext);return si_cumple;}
"sino_intente" {columna=columna+strlen(yylval.TEXT); strcpy (yylval.TEXT,yytext);return sino_intente;}
"sino_cumple" {columna=columna+strlen(yylval.TEXT); strcpy (yylval.TEXT,yytext);return sino_cumple;}
"enviar" {columna=columna+strlen(yylval.TEXT); strcpy (yylval.TEXT,yytext);return enviar;}
"def" {columna=columna+strlen(yylval.TEXT); strcpy (yylval.TEXT,yytext);return to;}
"<=" {columna=columna+strlen(yylval.TEXT); strcpy (yylval.TEXT,yytext);return menorIgual;}
">=" {columna=columna+strlen(yylval.TEXT); strcpy (yylval.TEXT,yytext);return mayorIgual;}
"==" {columna=columna+strlen(yylval.TEXT); strcpy (yylval.TEXT,yytext);return igualIgual;}
"!¡" {columna=columna+strlen(yylval.TEXT); strcpy(yylval.TEXT,yytext);return esNulo;}
"!=" {columna=columna+strlen(yylval.TEXT); strcpy(yylval.TEXT,yytext);return diferente;}
"++" {columna=columna+strlen(yylval.TEXT); strcpy(yylval.TEXT,yytext);return incrementar;}
"--" {columna=columna+strlen(yylval.TEXT); strcpy(yylval.TEXT,yytext);return decrementar;}
"**" {columna=columna+strlen(yylval.TEXT); strcpy(yylval.TEXT,yytext);return doble;}
"##" {columna=columna+strlen(yylval.TEXT); strcpy(yylval.TEXT,yytext);return dividirDos;}
[;] {columna=columna+strlen(yylval.TEXT); strcpy(yylval.TEXT,yytext);return puntoYComa;}
//[:] {columna=columna+strlen(yylval.TEXT); strcpy(yylval.TEXT,yytext);return dpuntos;}
[=] {columna=columna+strlen(yylval.TEXT); strcpy(yylval.TEXT,yytext);return igual;}
[@] {columna=columna+strlen(yylval.TEXT); strcpy(yylval.TEXT,yytext);return at;}
[,] {columna=columna+strlen(yylval.TEXT); strcpy(yylval.TEXT,yytext);return coma;}
[.] {columna=columna+strlen(yylval.TEXT); strcpy(yylval.TEXT,yytext);return punto;}
[+] {columna=columna+strlen(yylval.TEXT); strcpy(yylval.TEXT,yytext);return mas;}
[^] {columna=columna+strlen(yylval.TEXT); strcpy(yylval.TEXT,yytext);return por;}
[*] {columna=columna+strlen(yylval.TEXT); strcpy(yylval.TEXT,yytext);return por;}
[-] {columna=columna+strlen(yylval.TEXT); strcpy(yylval.TEXT,yytext);return menos;}
[/] {columna=columna+strlen(yylval.TEXT); strcpy(yylval.TEXT,yytext);return division;}
[(] {columna=columna+strlen(yylval.TEXT); strcpy(yylval.TEXT,yytext);return abreParentesis;}
[)] {columna=columna+strlen(yylval.TEXT); strcpy(yylval.TEXT,yytext);return cierraParentesis;}
[{] {columna=columna+strlen(yylval.TEXT); strcpy(yylval.TEXT,yytext);return abreLlave;}
[}] {columna=columna+strlen(yylval.TEXT); strcpy(yylval.TEXT,yytext);return cierraLlave;}
["] {columna=columna+strlen(yylval.TEXT); strcpy(yylval.TEXT,yytext);return comillas;}
[<] {columna=columna+strlen(yylval.TEXT); strcpy(yylval.TEXT,yytext);return menor;}
[>] {columna=columna+strlen(yylval.TEXT); strcpy(yylval.TEXT,yytext);return mayor;}
{id} {columna=columna+strlen(yylval.TEXT); strcpy(yylval.TEXT,yytext); return id;}
{numero} {columna=columna+strlen(yylval.TEXT); strcpy(yylval.TEXT,yytext);return numero;}
{cadenas} {columna=columna+strlen(yylval.TEXT); strcpy(yylval.TEXT,yytext);return cadenas;}
{comentario1} {}
{comentario2} {}
[[:blank:]] { /*Se ignoran*/ }
. {std::cout <<yytext<<"Error Lexico "<< std::endl;  columna=columna+strlen(yylval.TEXT); strcpy(yylval.TEXT, yytext); return error_lexico;}

%%
