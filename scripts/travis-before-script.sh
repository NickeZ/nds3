#/bin/bash
# Exit on error
set -e
# Print each line
set -v

if [ "${TRAVIS_EVENT_TYPE}" == "cron" ] ; then
	sudo apt-get update -qq
	sudo apt-get install -y doxygen doxygen-doc doxygen-latex doxygen-gui graphviz
fi
