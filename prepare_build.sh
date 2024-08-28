#!/bin/bash
SCRIPT=`realpath $0`
SCRIPTPATH=`dirname $SCRIPT`
SCRIPTPATH_FOLDER=$(basename $SCRIPTPATH)

echo "PREBUILD_IMAGES"
GROUP_ID=$(id -g)
GROUP_NAME=$(id -gn)
USER_ID=$(id -u)
USER_NAME=$(id -un)

rm -rf .env
touch .env

if [ $? -gt 0 ]; then
	echo "UNABLE TO SET DOCKER-COMPOSE ENVIRONMENT FILE"
	exit 1
fi

echo "WORKDIR=$SCRIPTPATH" >> .env
echo "GROUP_ID=$GROUP_ID" >> .env
echo "GROUP_NAME=$GROUP_NAME" >> .env
echo "USER_ID=$USER_ID" >> .env
echo "USER_NAME=$USER_NAME" >> .env
echo "BUILD_FOLDER=$SCRIPTPATH_FOLDER" >> .env

## prebuild OS builder images, not to rebuild them on every push
## OS builder images should be built using separate repo,
## ideally enm-docker every day build

# armdocker.rnd.ericsson.se/proj_oss_releases/enm/eric-enm-os-builders/rhel7/native-scl10:1.1.0-1
# armdocker.rnd.ericsson.se/proj_oss_releases/enm/eric-enm-os-builders/sles15/native-gcc10:1.1.0-1
#
# armdocker.rnd.ericsson.se/proj_oss_releases/eric-enm-native-builders
export IMAGE_REPOSITORY=armdocker.rnd.ericsson.se/proj_oss_releases/enm/eric-enm-os-builders
export IMAGE_TAG=1.1.1-4-SNAPSHOT
export IMAGE_ARTIFACT=ops-parser
export CONTEXT=builder


echo "IMAGE_REPOSITORY=$IMAGE_REPOSITORY" >> .env
echo "IMAGE_TAG=$IMAGE_TAG" >> .env

prebuild_docker_images(){
    local OS=$1
    local FULL_IMAGE_PATH="$IMAGE_REPOSITORY/$OS/$IMAGE_ARTIFACT:$IMAGE_TAG"
    echo "Preparing image for $FULL_IMAGE_PATH"
    docker pull $FULL_IMAGE_PATH
    local pull_result=$?
    echo "PULL RESULT $?"
    ## if image is not found, or unable to pull the image, build it locally
    if [ $pull_result -gt 0 ]; then
        echo "Unable to find image $FULL_IMAGE_PATH in registry, building and trying to push it to registry"
        docker build --force-rm -t "$FULL_IMAGE_PATH" --file "$CONTEXT/Dockerfile_$OS" "."
        docker push "$FULL_IMAGE_PATH"
    fi
    return 0
}
prebuild_docker_images rhel7
prebuild_docker_images sles15
exit 0
