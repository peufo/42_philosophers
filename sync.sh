#!/bin/sh

#SYNC Makefile SOURCES
sync() {

	SOURCES=$(ls philo/*.c | sed 's;philo/;;g' | tr '\n' ' ')
	SED_COMMAND="s;^SOURCES	.*;SOURCES			=	$SOURCES;"
	if [ $(uname) = "Linux" ];  then
		sed -i -e "$SED_COMMAND" ./philo/Makefile
	else
		sed -i "" "$SED_COMMAND" ./philo/Makefile
	fi
}

sync
