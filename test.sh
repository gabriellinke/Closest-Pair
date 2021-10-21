#!/bin/bash

for i in {2..3000}
do
    ./genpoints $i
    ./closest input.txt
done
