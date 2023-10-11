if [ $# -eq 0 ]; then
    echo "Usage: $0 <command>"
    exit 1
fi

# Execute the provided command
"$@"

# Echo the exit code
echo "Exit code: $?"