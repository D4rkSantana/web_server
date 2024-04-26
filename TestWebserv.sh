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
$name $argumento &
retorno="$?"
pid=$!
sleep 1
kill -SIGINT $pid
echo
echo "	Retorno Esperado: $esperado (rigth)"
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
echo "	Retorno Esperado: $esperado (Error)"
echo "	Retorno Recebido: $retorno"
check $esperado
echo



next
argumento=" lucas.txt"
esperado=1
((comando++))#2
echo " ☢️	$comando - Testando Numero de Argumento Errado( 1 ) -> ./webserv lucas.txt"
echo "<----------------------------------------------------------------------->"
echo
$name $argumento
retorno="$?"
echo
echo "	Retorno Esperado: $esperado (rigth)"
echo "	Retorno Recebido: $retorno"
check $esperado
echo



next
argumento=
esperado=0
((comando++))#3
echo " ☢️	$comando - Testando Sginal "ctrl+c" -> ./webserv"
echo "<----------------------------------------------------------------------->"
echo
$name $argumento &
pid=$!
sleep 1
kill -SIGINT $pid
wait $pid
retorno="$?"
echo
echo "	Retorno Esperado: $esperado (rigth)"
echo "	Retorno Recebido: $retorno"
check $esperado
echo


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
esperado=404
saidaSever=servidor.log
((comando++))#2
echo " ☢️	$comando - Testando Error 404(Not Found) -> 127.0.0.1:3007/naoexiste"
echo "<----------------------------------------------------------------------->"
echo
nohup $name > $saidaSever 2>&1 &
sleep 5
pid=$(pgrep -f $name)
retorno=$(curl -s -o /dev/null -w "%{http_code}" http://127.0.0.1:3007/naoexiste)


echo
echo "	Retorno Esperado: $esperado (rigth)"
echo "	Retorno Recebido: $retorno"
#check $esperado
kill $pid
echo



next
make fclean
clear
