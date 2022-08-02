#!/bin/bash

function test_error(){
	echo -n "" > ./logs/errors.log
	make -s && ./monitoring $1 --times=1 > temp.test.tes.t 2> temp.test.tes.t
	if [ $(cat ./logs/errors.log | wc -l) -eq 0 ]; then
			echo "$2: KO $1"; 
		else 
			echo "$2: OK"; 
	fi
}

function test_success(){
	echo -n "" > ./logs/errors.log
	make -s && ./monitoring $1 --times=1 > temp.test.tes.t 2> temp.test.tes.t
	if [ $(cat ./logs/success.log | wc -l) -eq 0 ]; then
			echo "$2: KO $1"; 
		else 
			echo "$2: OK"; 
	fi
}

test_error "./tests/moc/invalid_http.db" "HTTP"
test_success "./tests/moc/valid_http.db" "HTTP"
test_error "./tests/moc/invalid_ping.db" "PING"
test_success "./tests/moc/valid_ping.db" "PING"
test_error "./tests/moc/invalid_dns.db" "DNS"
test_success "./tests/moc/valid_dns.db" "DNS"
