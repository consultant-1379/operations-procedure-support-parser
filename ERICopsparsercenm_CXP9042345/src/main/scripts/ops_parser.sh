#!/bin/bash -a

set -a

OPS_HOME="/opt/ops/ops_parser"
VISIBROKER_HOME="/opt/MicroFocus/VisiBroker"

if [ -d $VISIBROKER_HOME ] && [ -d $OPS_HOME ]; then
    echo "Starting the ops_parser... "
else
	echo "Check for the visibroker or ops_parser installation. Failed to start ops_parser. Exiting !!!";
	exit 1;
fi

VBROKER_ADM=$VISIBROKER_HOME/var/vbroker/adm
VBROKER_LIB=$VISIBROKER_HOME/lib/
LIB_DIR=$OPS_HOME/lib

PROCNAME=OPS_Parser

export OPS_SMTP_SERVER="$(cat /ericsson/tor/data/global.properties|grep -w lvsrouter|awk '{split($0,server,"="); split(server[2],ips,","); print ips[1]}')"
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$VBROKER_LIB:$LIB_DIR
export VBROKER_ADM

export OPSNameServiceHost="localhost"
export OPSNameServicePort="49251"

#configurable timeout for reading response from node (in seconds).
export READ_DATA_RETRY_COUNT=2400

umask 0022

#The first variable is assumed to contain the DISPLAY.
DISPLAY=$1
exec -a $PROCNAME $OPS_HOME/bin/ops_parser "$@" >$HOME/parser.txt 2>&1
