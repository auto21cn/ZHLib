// Room: /yuelaoci.c
#define QIUQIAN __DIR__"qiuqian"

#include <ansi.h> 

#include <room.h>
inherit ROOM;
int is_chat_room() { return 1;}
void create(){
	set("short", "月老祠");
	set("long", @LONG
月老是神话中掌管姻缘的仙人，传说他有红线，若把它系在男女朋方的脚
上，虽仇人或相隔千里，终会结成姻缘。月老祠一间小院、三五瓦屋。正屋中
央的神龛里坐着月下老人：红风帽红披肩，鹤发童颜，笑容满面。神龛前面照
例是供桌、香炉、烛台、签筒，当然，蒲团也是少不了的。两旁一副黑漆的小
对联：愿天下有情人，都成了眷属；是前生注定事，莫错过姻缘。令人拍案叫
绝。你可以在这里求签（qiuqian）问一下姻缘情事，门口有替人解签的书生。
LONG );
	set("no_fight", "1");
	set("no_steal", "1");
	set("no_sleep_room","1");
    
	set("exits", ([
		"south" : __DIR__"yuanyuan-tai",
        
        ]));
    setup();
}
void init()
{
	add_action("do_qiuqian","qiuqian");
}

int do_qiuqian(string arg)
{ 
	    object me;
	     
        if (! objectp(me = this_player()) ||
            ! userp(me))
                return 1;

        if (time() - me->query("last_qiuqian_time") < 600)
                return notify_fail("这么频繁的求签干嘛？心不诚则签不灵，过十分钟再来吧。\n");

        write(HIC "
你虔诚地向月老像拜了几拜，口中念念有词：“月老月老，赐给我好姻缘吧！”
你闭着眼擎了支签，又祈祷了一会，这才睁开眼睛看签文。\n
" NOR, me);
        write(HIC "签上写着：" + QIUQIAN->query_qiuqian() + "。\n" NOR, me);
        me->set("last_qiuqian_time",time());
        return 1;
}


