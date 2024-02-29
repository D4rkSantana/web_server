#!/bin/bash

name="./webserv"
comando=-1
function next(){
	echo
	echo "                                            Press to Next -------------->"
	read END
	echo
}

function check(){
	local esperado="$1"
	if [ "$retorno" -eq "$esperado" ]; then
		echo "	-> 🟢 Sucesso"
	else
		echo "	-> 🔴 Fail";
	fi
}


make re &
wait
clear




echo
echo "████████╗███████╗███████╗████████╗     █████╗ ██████╗  ██████╗ "
echo "╚══██╔══╝██╔════╝██╔════╝╚══██╔══╝    ██╔══██╗██╔══██╗██╔════╝ "
echo "   ██║   █████╗  ███████╗   ██║       ███████║██████╔╝██║  ███╗"
echo "   ██║   ██╔══╝  ╚════██║   ██║       ██╔══██║██╔══██╗██║   ██║"
echo "   ██║   ███████╗███████║   ██║██╗    ██║  ██║██║  ██║╚██████╔╝"
echo "   ╚═╝   ╚══════╝╚══════╝   ╚═╝╚═╝    ╚═╝  ╚═╝╚═╝  ╚═╝ ╚═════╝ "
echo
echo


next
argumento=
esperado=0
((comando++))#0
echo " ☢️	$comando - Testando Numero de Argumento ( 0 ) -> ./webserv"
echo "<----------------------------------------------------------------------->"
echo
$name $argumento
retorno="$?"
echo
echo "	Retorno Esperado: 0 (rigth)"
echo "	Retorno Recebido: $retorno"
check $esperado
echo


next
argumento=" lucas.txt ricardo.txt"
esperado=1
((comando++))#1
echo " ☢️	$comando - Testando Numero de Argumento ( 2 ) -> ./webserv lucas.txt ricardo.txt"
echo "<----------------------------------------------------------------------->"
echo
$name $argumento
retorno="$?"
echo
echo "	Retorno Esperado: 1 (Error)"
echo "	Retorno Recebido: $retorno"
check $esperado
echo



next
argumento=" lucas.txt"
esperado=0
((comando++))#2
echo " ☢️	$comando - Testando Numero de Argumento ( 1 ) -> ./webserv lucas.txt"
echo "<----------------------------------------------------------------------->"
echo
$name $argumento
retorno="$?"
echo
echo "	Retorno Esperado: 0 (rigth)"
echo "	Retorno Recebido: $retorno"
check $esperado
echo



next
argumento=" lucas.txt"
esperado=0
((comando++))#3
echo " ☢️	$comando - Testando Sginal "ctrl+c" -> ./webserv lucas.txt"
echo "<----------------------------------------------------------------------->"
echo
$name $argumento &
pid=$!
sleep 1
kill -SIGINT $pid
wait $pid
retorno="$?"
echo
echo "	Retorno Esperado: 0 (rigth)"
echo "	Retorno Recebido: $retorno"
check $esperado
echo




next
make fclean
clear
