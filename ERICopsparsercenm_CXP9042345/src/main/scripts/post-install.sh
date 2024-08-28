#!/bin/bash

install_path="/opt/ops/ops_parser"

GRPC_DIR=${install_path}/lib
LIB_DIR=${install_path}/lib
PARSER_DIR=${install_path}/bin
OPS_CENTRALDIR="/etc/opt/ericsson/nms_ops_server/scripts"
OPS_SESSION_FILE="/var/opt/ericsson/nms_ops_server/data/session_id";
OPS_PRIVATEDIR="/cha/cmdfile";
OPS_RESPONSE_DIR="/cha/response";

if [ "$(ls -A $LIB_DIR/lib.tar.gz 2> /dev/null)" == "" ]; then
  echo "libs are not available."
else
  tar -zxvf ${LIB_DIR}/lib.tar.gz -C $LIB_DIR
  rm -rf $LIB_DIR/lib.tar.gz
  chown -R root:root $LIB_DIR/
fi

if [ "$(ls -A $PARSER_DIR/*gz 2> /dev/null)" == "" ]; then
  echo "Parser binary is not available"
else
  tar -zxvf $PARSER_DIR/*.gz -C $PARSER_DIR
  rm -rf $PARSER_DIR/*.gz
  chmod 775 $PARSER_DIR/ops_parser
  chown root:root $PARSER_DIR/ops_parser
fi

#####setting up the parser path#########

#OPS_CENTRALDIR
if [ ! -d $OPS_CENTRALDIR ]; then
    mkdir -p $OPS_CENTRALDIR;
fi

#full access to centralDir
chmod 777 $OPS_CENTRALDIR

export OPS_CENTRALDIR;

#OPS_SESSION_FILE
export OPS_SESSION_FILE;

#OPS_PRIVATEDIR
export OPS_PRIVATEDIR;

#OPS_RESPONSE_DIR
export OPS_RESPONSE_DIR;
#########################################
