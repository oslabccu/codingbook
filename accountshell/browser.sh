#!/bin/bash
PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/usr/lib/jvm/java-13-oracle/bin:/usr/lib/jvm/java-13-oracle/db/bin:/usr/mybin
export PATH
filebrowser config init

filebrowser users add ${1} ${2} --scope /home/ccugrp/${1} #--lockPassword

exit 0
