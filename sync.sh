#!/bin/sh

#SYNC Makefile SOURCES
sync() {
	DIR=philo
	SOURCES=$(ls $DIR/*.c | sed "s;$DIR/;;g" | tr '\n' ' ')
	SED_COMMAND="s;^SOURCES	.*;SOURCES			=	$SOURCES;"
	if [ $(uname) = "Linux" ];  then
		sed -i -e "$SED_COMMAND" "./$DIR/Makefile"
	else
		sed -i "" "$SED_COMMAND" "./$DIR/Makefile"
	fi
}

sync
