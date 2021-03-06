#include <ansi.h>
 
inherit F_CLEAN_UP;
string time_period(int timep);
int main(object me, string arg)
{
        int nowtime = time();
        mapping quest;
        if(!(quest =  me->query("quest"))) {
               write("你现在没有任何任务！\n");
               if ( me->query("fail_time") )
                       write("距离你上一次任务失败，已经" + time_period(time()-me->query("fail_time")) + "了。\n");
               return 1;
               }
               
        write("你现在的任务是" + quest["type"] + quest["quest"] + "。\n"
);
        nowtime = quest["task_time"] - time();
        if( nowtime  > 0 )
                write("你还有" + time_period(nowtime) + "去完成它。\n");
        else
                write("但是你已经没有足够的时间来完成它了。\n");
 
        return 1;
}
string time_period(int timep)
{
        int t, d, h, m, s;
        string time;
        t = timep;
        s = t % 60;             t /= 60;
        m = t % 60;             t /= 60;
        h = t % 24;             t /= 24;
        d = t;
 
        if(d) time = chinese_number(d) + "天";
        else time = "";
 
        if(h) time += chinese_number(h) + "小时";
        if(m) time += chinese_number(m) + "分";
        time += chinese_number(s) + "秒";

        return time;
}
 
int help(object me)
{
        write(@HELP
指令格式 : renwu 这个指令可以显示出你当前的任务。
HELP
        );
        return 1;
}

