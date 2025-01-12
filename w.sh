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

DIR="philo_bonus"

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

			NORM_ERROR=$(sed -e '/.*: OK!/d' <(norminette ./philo ./philo_bonus))
			if [[ $NORM_ERROR == "" ]] ; then
				success "\nNORMINETTE OK\n"
			else
				warning "\nNORMINETTE ERROR"
				echo -e "$NORM_ERROR\n\n\n"
			fi
			
			PROG="./$DIR/$DIR"
			rm -f "$PROG"
			make -C $DIR
			if [ ! -f "$PROG" ]; then
				warning "COMPILATION FAILED"
			else
				success "COMPILATION OK"

				if [ $(uname) = "Linux" ]; then
					valgrind --leak-check=full --track-origins=yes --log-file=leaks.log -s $PROG "5" "320" "100" "150" "3" &
					#valgrind --tool=helgrind --log-file=leaks.log -s $PROG "5" "2500" "1000" "1500" "3" &
				else
					#leaks -quiet --atExit -- $PROG "25" "4000" "1000" "1500" &
					$PROG "5" "1500" "1000" "1400" "3" &
				fi
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
	echo $(find -L $DIR -type f -name "*.[ch]" -exec $MD5 {} \;)
}

watch