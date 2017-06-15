#!/bin/bash
ts=$(date +%s%3N) ; $@ ; tt=$((($(date +%s%3N) - $ts))) ; echo "Time taken: $tt milliseconds"



