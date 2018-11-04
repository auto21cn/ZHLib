// Updated by rama

inherit ROOM;
#include <ansi.h>

void create()
{
        set("short", "胡同");
        set("long", @LONG
这里是襄阳城内老百姓的居住区。只见胡同两边是有些小
店面，有米行、小杂货铺等。一些居民从这里进进出出。你似
乎觉得这里有些诡秘。旁边有个小木门（door）。
LONG );
        set("outdoors", "xiangyang");
        set("exits", ([
                "south" : __DIR__"jiekou1",
        ]));
        set("objects", ([
                __DIR__"npc/girl" : 2,
        ]));

        set("item_desc", ([
                "door" : "厚厚的木板门，看起来相当陈旧。\n" ,
        ]));

        setup();
}
void init()
{
        add_action("do_knock", "knock");
        add_action("do_open","open");
}
int do_open(string arg)
{
        if(arg=="door")
        return notify_fail("你用力推了推门，结果一点动静都没有！看来是从里面反锁了。\n");
        else return 0;
}

int do_knock(string arg)
{
        object me;
        me = this_player();
        if (!arg||arg=="") 
                return notify_fail("你要敲什么？\n");
          if (arg != "door")
                return notify_fail("你要敲什么？\n");
          if( arg=="door" ) {
                message_vision("$N试著敲了敲木门。\n", me);
                if (me->query("bang_bad/name")!="黑白道" && (int)me->query("shen") <= 0)
                {
                        message_vision(HIB"木门吱呀一声开了，从里面探出个头来，看了$N两眼说道：“是来投靠咱们黑白道的吧！”，
说完一把把$N拉了进去。\n"NOR, me);
                        me->move(__DIR__"hbd_xyfb");
                        return 1;
                }
                if( me->query("bang_good") || (int)me->query("shen") > 0 ) 
                { 
                        message_vision("木门吱呀一声开了，从里面探出个头来，看了$N两眼说道：“你这种人也敢来此，活的不耐烦了么？”\n门被重重的关上了。\n",me);  
                        return 1; 
                } 
                message_vision("门板吱呀一声开了，从里面探出个头来，看了$N两眼说道：“既然是本帮的兄弟，就进来吧！”，
说完一把把$N拉了进去。\n",me);
                me->move(__DIR__"hbd_xyfb"); 
                return 1; 
        }
        
        return 1;
}
  
