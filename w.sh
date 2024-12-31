#!/bin/bash

info() {
	echo -e "\033[36m$1\033[0m"
}
warning() {
	echo -e "\033[31m$1\033[0m"
}
success() {
	echo -e "\033[32m$1\033[0m"
}

watch() {
	STATE_A=""
	PROG_PID=""
	while [[ true ]]
	do
		STATE_B=$(get_state)
		if [[ $STATE_A != $STATE_B ]]; then
			STATE_A=$STATE_B
			if [ $PROG_PID != "" ]; then
				kill $PROG_PID
			fi
			clear
			info "HEY BRO 👋 $(date)"
			./sync.sh

			NORM_ERROR=$(sed -e '/.*: OK!/d' <(norminette ./philo))
			if [[ $NORM_ERROR == "" ]] ; then
				success "\nNORMINETTE OK\n"
			else
				warning "\nNORMINETTE ERROR"
				echo -e "$NORM_ERROR\n\n\n"
			fi

			PROG="./philo/philo"
			rm -f "$PROG"
			make -C philo
			if [ ! -f "$PROG" ]; then
				warning "COMPILATION FAILED"
			else
				success "COMPILATION OK"
				#valgrind --leak-check=full --track-origins=yes --log-file=leaks.log -s $PROG &
				$PROG "3" "3000" "1000" "1000" "3" &
				PROG_PID=$!
				trap 'kill "$PROG_PID" & return' 2
			fi
		fi
		sleep 0.1
	done
}

get_state() {
	if [[ $(uname) == "Linux" ]];  then
		MD5="md5sum"
	else
		MD5="md5"
	fi
	echo $(find -L ./philo -type f -name "*.[ch]" -exec $MD5 {} \;)
}

watch