#!/bin/bash
# btrfs建立cpe帳戶與資料夾與權限
# group資料夾放置的位置
G_NAME=ccugrp
G_PASSWD=password
U_NAME=${1}
U_PASSWD=${2}
G_PATH=/home/${G_NAME}
U_PATH=${G_PATH}/${1}
G_QID=3/0
G_LIMIT=20G
U_LIMIT=200M

# 判斷有兩個參數 參數1=username 參數2=password
[ "$#" -lt 2 ] && echo "less than 2 parameters: username password." && exit 0
U_NAME=${U_NAME:?user名稱錯誤}
U_PASSWD=${U_PASSWD:?user密碼錯誤}
G_NAME=${G_NAME:?group名稱錯誤}
G_PASSWD=${G_PASSWD:?group密碼錯誤}
G_LIMIT=${G_LIMIT:?group quota錯誤}
U_LIMIT=${U_LIMIT:?user quota錯誤}


# 建group管理員
if [ ! -d "${G_PATH}" ]; then
    btrfs quota enable /home    #啟動btrfs quota
    useradd -s /bin/bash ${G_NAME}
    echo "${G_NAME}:${G_PASSWD}" | chpasswd
	# 建subvolume dir並設quota group size
	btrfs qgroup create ${G_QID} /   #建group的qgroup並指定QID
    btrfs subvolume create -i ${G_QID} ${G_PATH}   #建group subvolume並指向group qgroup
	btrfs qgroup limit -c ${G_LIMIT} ${G_QID} ${G_PATH} #quota setting
	# 設group的dir權限
    chown ${G_NAME}:${G_NAME} ${G_PATH}
    chmod 755 ${G_PATH}
    echo "group:${G_NAME} created"
fi

# 建帳號user,設group,家目錄,權限
if [ -d "${U_PATH}" ]; then
    echo "user:${U_NAME} exist"
else
    useradd -s /bin/bash -d ${U_PATH} ${U_NAME}
    echo "${U_NAME}:${U_PASSWD}" | chpasswd
	# 建subvolume dir並設quota group size
    btrfs sub create ${U_PATH} #建立user subvolume
	sub_id=$(btrfs subvolume list / | grep ${U_NAME} | cut -d' ' -f2) #找此subvolume的id
	btrfs qgroup create 1/${sub_id} ${G_PATH} #建此user的qgroup
	btrfs qgroup assign 0/${sub_id} 1/${sub_id} ${G_PATH} #將此user subvolume指向user qgroup
	btrfs qgroup assign 1/${sub_id} ${G_QID} ${G_PATH} #user qgroup在指向group qgroup
	btrfs qgroup limit -c ${U_LIMIT} 1/${sub_id} ${G_PATH} #quota setting
	# 設user的dir權限
    chown ${U_NAME}:${G_NAME} ${U_PATH}
    chmod 2770 ${U_PATH}
    echo "user:${U_NAME} created"
fi

exit 0
