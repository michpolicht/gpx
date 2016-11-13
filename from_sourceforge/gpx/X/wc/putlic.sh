#!/bin/sh
#
# Copyright (c) 2010, Michal Policht. This file is dually licensed under terms of 
# either WTFPL or BEER-WARE LICENSE. You may obtain the copy of WTFPL or BEER-WARE
# LICENSE by googling it. NO WARRANTY. YOU WILL PAY ALL COSTS FOR ANY REPAIRS.
#
# A chain of commands to strip and put license into file.
#
# usage: putlic.sh target_file license_file [comment] [qualifier]
# example: putlic.sh script.cmake LICENSE "hash" "MYID"
#
# parameters:
# target_file - where to put license.
# license_file - file containing license.
# comment - comment type. Passed as "comment" variable to striplic.awk. 
#           Check striplic.awk for possible values.
# qualifier - copyright notice qualifier. See stiplic.awk for details.
#
# required tools: sh, awk, echo, find (findutils), cat, rm, striplic.awk


function usage()
{
    echo "usage: $0 file license [comment] [qualifier]"
}

if [ ! -e $1 ]; then
	echo $1 "doesnt't exist"
	exit 1
fi	

if [ ! -e $2 ]; then
	echo $2 "doesnt't exist"
	exit 1
fi	

if [ $# -lt 2 ]; then
    echo "error: too few arguments"
    usage
    exit 0
fi

if [ $# -gt 2 ]; then
    comment=$3;
else
    comment="dslash"
fi

if [ $# -gt 3 ]; then
    qualifier=$4;
else
    qualifier=""
fi

echo $1
awk -v comment="$comment" -v qualifier="$qualifier" -f striplic.awk $1 > $1.strip
cat $1.strip $2 > $1
rm $1.strip
