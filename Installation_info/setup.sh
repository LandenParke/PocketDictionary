#!/bin/sh

set -eu

REPO_URL="https://github.com/LandenParke/PocketDictionary"

check_cmd() {
    if ! command -v "$1" >/dev/null 2>&1; then
        printf 'Missing required tool: %s\n' "$1" >&2
        return 1
    fi
}

#build nuttx first
#./nuttx
#


#NEED TO DO: Setup checks for simulator

printf '\nSetup checks passed.\n'
printf 'Next step: follow the simulator build instructions'
