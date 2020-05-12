#!/bin/bash
#刪除cpe帳戶
G_NAME=ccugrp
G_QID=3/0
G_PATH=/home/${G_NAME}
G_NAME=${G_NAME:?群組錯誤}
if [ -d ${G_PATH} ]; then
	cd ${G_PATH}
	for username in *
    do
		if [ -d $username ]; then
			sub_id=$(btrfs subvolume list / | grep $username | cut -d' ' -f2)
			btrfs qgroup destroy 0/${sub_id} .
			btrfs qgroup destroy 1/${sub_id} .
			btrfs sub delete -C $username
			userdel $username
			echo "$username deleted"
		fi
	done
    cd ..
	sub_id=$(btrfs subvolume list / | grep ${G_NAME} | cut -d' ' -f2)
	btrfs qgroup destroy 0/${sub_id} .
	btrfs qgroup destroy ${G_QID} .
	btrfs sub delete -C ${G_NAME}
	userdel ${G_NAME}
	echo "${G_NAME} deleted"
else
	echo "already deleted"
fi

exit 0
