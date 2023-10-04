i=0

while true; do
    i=$((i+1))
    echo "$i second(s) passed"
    sleep 1

    # Add a condition to exit after a certain number of seconds (for example, 5 seconds)
    if [ $i -eq 5 ]; then
        exit 1
    fi
done
