// sea.c
// Modified by haiyan

#include <ansi.h>
inherit ROOM;
 
void create()
{
        set("short", "大海");
        set("long",@LONG
你正处在茫茫大海之中。你极目远望，只见海天一线，周围连个黑点都没有。
耳边只有海浪的拍打声。
LONG);   
        set("no_clean_up", 0);
        setup();
}

void init()
{
      add_action("do_swimming", "swimming");
      add_action("do_swimming", "youyong");
}

int do_swimming()
{
    object me = this_player();
    tell_object(me, "你奋力挥动双臂，漫无目的地向前游去。\n");
    me->receive_damage("qi", 20 + random(20));

    if (random(10) < 3)
       tell_object(me, HIC"突然你看见一条鲨鱼向你游来。你急忙转身，拼命向前游去。\n"NOR);

    if ((int)me->query("qi") < 0)
    {
       me->set("qi", 0);
       tell_object(me, "你筋疲力尽，渐渐失去了知觉。\n");
       me->unconcious();
       me->move("/d/shenlong/haitan");
       message("vision", "你发现一个浑身水淋淋的家伙被海水冲上岸来，不由得走近一看，原来是" +
                me->name() + "。\n", environment(me), me);
    }       
    return 1;
}

