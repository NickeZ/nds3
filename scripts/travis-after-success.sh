#/bin/bash
# Exit on error
set -e
# Print each line
set -v

if [ "${TRAVIS_EVENT_TYPE}" == "cron" ] ; then
	./scripts/deploy_doxygen
fi
