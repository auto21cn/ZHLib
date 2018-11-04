// hujiao.c

#include <ansi.h>

inherit F_CLEAN_UP;

int help(object me);

void create()
{
        seteuid(getuid());
}

int main(object me, string arg)
{
        object obj;

        if( ((int)me->query("jing") < 50) &&(!wizardp(me)))
                return notify_fail("你的口水都快干了，歇会再念传音咒吧。\n");
         if (me->is_busy()) 
          return notify_fail("稍安勿躁，稍安勿躁。\n"); 
        if(!arg || arg == "")
        {
           message_vision(CYN"$N鬼鬼祟祟的比划了几个手势，忽然想不起自己到底要干什么了。\n"NOR,me);
           return 1;
        }
        obj = find_player(arg);
        if(!obj || !me->visible(obj)) 
           return notify_fail("没有这个人....\n");
        if(obj->query("id") == me->query("id"))
        {
           message_vision(CYN"$N鬼鬼祟祟的比划了几个手势，嘴里嘟嘟囔囔念道：“沙子一屋子金子一袋子....”\n"NOR,me);
           return 1;
        }
    message_vision(CYN"$N鬼鬼祟祟的比划了几个手势，一边偷偷念道：“天灵灵，地灵灵，传音精灵快显形....”\n"NOR,me);
    tell_object(obj,HIW"“叮叮、叮叮”，是"+me->name(1)+"在念传音咒呼叫你！\n"+
BEEP BEEP NOR);
        call_out("do_beep",1,obj);
    call_out("do_beep",2,obj);
    call_out("do_beep",4,obj);
        if( !wizardp(me) )
        {
         me->start_busy(2); 
                me->receive_damage("jing", 50);
        }
        return 1;
}

int do_beep(object obj)
{
   if(!obj)   return 1;
   tell_object(obj,
BEEP);
   return 1;
}


int help(object me)
{
        write(@HELP
指令格式：hujiao <某人>

只要念出这段传音咒，你想呼叫的人的音箱内便会有提示音发出。

HELP
        );
        return 1;
}


