#!/bin/bash
# build project
PROFILE=$1
if [[ "$PROFILE" = "rhel7" ]]; then
   echo "Rhel7, environment, sourcing devtoolset-11"
   source scl_source enable devtoolset-11
fi
printenv
echo "STARTING_BUILD in $HOSTNAME"
cd $HOME
MAVEN_GOALS="clean install"
## execute the deploy phase, only when the maven release:perform is executed
## by default it will checkout the latest code into checkout subfolder of $project/target
## so this folder becomes the hostname prefix
if [[ "$HOSTNAME" =~ ^checkout.* ]]; then
   MAVEN_GOALS="clean deploy pmd:pmd jacoco:report -U"
fi
echo "Listing rw files"
ls -ltr /tmp/RW2021_LIBS/rw/
echo "Listed suuccessfully"
echo "Executing GOALS : $MAVEN_GOALS in path $HOME"
maven --settings $HOME/.m2/settings.xml -Dmaven.repo.local=$HOME/.m2/repository -Duser.home=$HOME "-P$PROFILE,local_build" ${MAVEN_GOALS}

EXIT_CODE=$?
echo "exit_code $EXIT_CODE"
exit $EXIT_CODE
