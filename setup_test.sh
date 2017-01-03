#!/bin/bash

echo -e "\n======== ${BASH_SOURCE[0]} ========"
repo="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && while [ ! -d .git ] ; do cd ..; done; pwd )"
here="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
source $repo/utils/common_header.bash
cd $repo

echo "########## Setup Test Env"
$repo/utils/setup_dev_env.sh -m docker_host
. $repo/utils/env_config.sh

if ! grep -q "\-G " /etc/default/docker; then
	echo "Add $1 to as primary docker group in /etc/default/docker"
	echo "DOCKER_OPTS=\"\$DOCKER_OPTS -G $1\"" \
			| sudo tee -a /etc/default/docker
	sudo service docker restart ||:
fi

cd $here
pip install -r ../requirements.txt --user

