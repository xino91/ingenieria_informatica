#!/bin/bash

echo "Ver mas"

cat series.txt | grep -E '[SIPNOSIS: ].*' | tr -d "Ver mas"
