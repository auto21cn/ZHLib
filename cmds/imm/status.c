// status.c

#include <localtime.h>

inherit F_CLEAN_UP;

int main(object me,string arg)
{
	string msg;
	mixed lt;

	lt = localtime(time());
	msg = sprintf("%d/%d/%d  %d:%d:%d\n",
		      lt[LT_YEAR], lt[LT_MON] + 1, lt[LT_MDAY],
		      lt[LT_HOUR], lt[LT_MIN], lt[LT_SEC]);
	msg += (string)mud_status(arg=="detail" ? 1 : 0);
	write(msg);

	return 1;
}

int help(object me)
{
  write(@HELP
指令格式 : status [detail]
 
这个指令可以显示出目前游戏的一些相关资料及状况.
 
HELP
    );
    return 1;
}
 
