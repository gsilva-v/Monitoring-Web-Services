#!/bin/bash
function test_success(){
	echo -n "" > ./logs/success.log
	make -s && ./monitoring $1 --times=1 > tests/test.log 2> tests/test.log
	if [ $(cat ./logs/success.log | wc -l) -eq 0 ]; then
			echo "$2: KO $1 see test.log"; 
		else 
			echo "$2: OK"; 
	fi
}

test_success "./tests/moc/valid_http.db" "HTTP"