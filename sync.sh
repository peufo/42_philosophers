#!/bin/sh

#SYNC Makefile SOURCES
sync() {

	SOURCES=$(ls src/*.c | sed 's;src/;;g' | tr '\n' ' ')
	SED_COMMAND="s;^SOURCES	.*;SOURCES			=	$SOURCES;"
	if [ $(uname) = "Linux" ];  then
		sed -i -e "$SED_COMMAND" Makefile
	else
		sed -i "" "$SED_COMMAND" Makefile
	fi
}

sync
