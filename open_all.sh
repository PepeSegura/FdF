#!/bin/bash

# Loop over each file in the "maps" folder
for file in maps/*; do
    # Check if the file is a regular file
    if [[ -f "$file" ]]; then
        # Execute your program with the current file as input
		echo "Opening [$file]"
        ./fdf "$file" &
    fi
done

sleep 20

kill $(ps -e | grep fdf | awk '{print $1}')
