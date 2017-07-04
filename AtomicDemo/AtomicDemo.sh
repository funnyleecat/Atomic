# !/bin/bash
#服务运行脚本
#初次部署时，必须先执行setup.sh脚本
#脚本可带一个值为stop的参数，表示停止服务


#脚本参数
RUN_EXE=AtomicDemo
RUN_DIR=$(cd `dirname $0`; pwd)
RUN_LOG=${RUN_DIR}/AtomicDemo_run.log


#脚本参数为stop，即停止服务
if [[ ! -z $1 ]] && [[ $1 == "stop" ]];
then
	killall -9 ${RUN_EXE}
	echo "$(date '+%Y-%m-%d %H:%M:%S') [${RUN_EXE}] all stoped" >> ${RUN_LOG}
	exit 1
fi


#执行函数：RUN_DIR + RUN_EXE + RUN_LOG
RUN_FUNC()
{
	cd $1
    #添加执行权限
	chmod +x ./$2
    ./$2 &
	echo "$(date '+%Y-%m-%d %H:%M:%S') [$2] start" >> $3
}

#加载系统环境变量
source /etc/profile
#加载当前目录下的so路径
export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
#宕机产生core文件
ulimit -c unlimited
#数据库环境变量
export NLS_LANG="SIMPLIFIED CHINESE_CHINA.ZHS16GBK"
#DBUtils要求的路径oci.so，必须的呀
export OCI_PATH="./"

#启动服务
RUN_FUNC ${RUN_DIR} ${RUN_EXE} ${RUN_LOG}

