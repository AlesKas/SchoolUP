#!/bin/bash

pID=$1

ps -ef | grep $pID | grep -v grep | awk '{print $2}' | xargs kill -9

#usage: sh killall.sh sleep