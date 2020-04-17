#!/bin/bash

set -v

./ping_win
./ping_win -
./ping_win --
./ping_win -y
./ping_win -ta
./ping_win -ca
./ping_win -c
./ping_win -c0
./ping_win -c5
./ping_win -c 5
./ping_win -t
./ping_win -t0
./ping_win -t10 & sleep 1; pkill ping_win
./ping_win -t 10 & sleep 1; pkill ping_win
./ping_win aaaa & sleep 1; pkill ping_win
