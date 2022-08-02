#!/bin/bash

function test_error(){
	echo -n "" > ./logs/errors.log
	make -s -C ./
	./monitoring $1 --times=1 > tests/test.log 2> tests/test.log
	if [ $(cat ./logs/errors.log | wc -l) -eq 0 ]; then
			echo "$2: KO $1 see test.log";
		else 
			echo "$2: OK"; 
	fi
}

test_error "./tests/moc/invalid_http.db" "HTTP"
test_error "./tests/moc/invalid_ping.db" "PING"
test_error "./tests/moc/invalid_dns.db" "DNS"
test_error "./tests/moc/invalid_services.db" "All services"
