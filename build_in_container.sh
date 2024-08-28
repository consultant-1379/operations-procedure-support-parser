#!/bin/bash
SCRIPT=`realpath $0`
SCRIPTPATH=`dirname $SCRIPT`

echo $SCRIPT
echo $SCRIPTPATH

# build project
PROFILE=$1
COMMON_OPTIONS="-f ${SCRIPTPATH}/docker-compose-builder.yml --no-ansi --env-file ${SCRIPTPATH}/.env"
echo " going to call docker-compose : ${SCRIPTPATH}/docker-compose-local $COMMON_OPTIONS build $PROFILE"
${SCRIPTPATH}/docker-compose-local $COMMON_OPTIONS build $PROFILE
EXIT_CODE=$?
echo "Exit code : $EXIT_CODE"
if [ $EXIT_CODE -gt 0 ]; then
   echo "BUILDING CONTAINER FOR $PROFILE failed"
   exit $EXIT_CODE
fi
echo "built successfully. going to make up"
${SCRIPTPATH}/docker-compose-local $COMMON_OPTIONS up --abort-on-container-exit $PROFILE
EXIT_CODE=$?
echo "EXIT_CODE = $EXIT_CODE"
if [ $EXIT_CODE -gt 0 ]; then
   echo "EXECUTING OF BUILD FOR $PROFILE failed"
fi
exit $EXIT_CODE
