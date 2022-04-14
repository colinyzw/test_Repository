#!/bin/bash

#NAME=JOIN
#NAMELIST="JOIN DAVID TOM JAM"


#echo $NAME
#echo ${NAME}hello
#echo ${NAME}hello ahdofhaodsf
#echo ${NAMELIST}
#echo "${NAMELIST}is a namelist"
#echo '${NAMELIST}is a namelist'




#永久变量
#echo "home dir:${HOME}"

#位置变量
#echo ${2}
#echo $4

#特殊变量
#echo "all parrameters:$*"
#echo "parameters number: $#"
#echo "get last commond PID :$!"
#echo "get last commond return: $?"
#echo "local pid:$$"

#read
#echo "please input user name:"
#read USERNAME
#echo "user name:${USERNAME}"

#expr
#NUM1=5
#NUM2=7


#SUM=`expr ${NUM1} + ${NUM2}`
#echo "sum=${SUM}"

#if test -d ${1}
#then 
#	echo "${1} is a dir."
#elif test -f ${1}
#then
#	echo "${1} is a regular file."
#else
#	echo "${1} is not a regular file."
#fi


#case
#read VAR
#case ${VAR} in
#	'1')
#		echo "石头"
#		;;
#	'2')
#		echo "剪刀"
#		;;
#	'3')
#		echo "布"
#		;;
#esac


#for
#for VAR in ${1} ${2} ${3} ${4}
#do 
#	echo "${VAR} test"
#done

#for VAR in ${1} ${2} ${3} ${4}
#do 
#	if [ ${VAR} == {2}]
#	then
#		break
#	fi
#		echo "${VAR} test"
#done


#for VAR in ${1} ${2} ${3} ${4}
#do 
#	if [ ${VAR} == {2}]
#	then
#		continue
#	fi
#		echo "${VAR} test"
#done

#for((i=1;i<=10;i++))
#{
#	echo "${i} test"
#}

#while
#echo "please input a web:enter ctrl +D end process"
#while read WEB
#do 
#	echo "${WEB} test"
#	echo "please input a web:"
#done

#function
MYFUNCTION()
{
	SUM=`expr $1 + $2`
	echo "sum:${SUM}"
}

VAR=`MYFUNCTION 100 300`
echo "result:${VAR}"








