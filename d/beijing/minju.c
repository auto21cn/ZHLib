// Updated by rama

inherit ROOM;
#include <ansi.h>

int do_open(string arg);
int do_knock(string arg);

void create() {
        set("short", "民居");
        set("long", @LONG 
这里是一件普普通通的民居，家里什么摆设也没有，全屋只有一
张床（chuang）还象模象样。
LONG );
        set("outdoors", "suzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "east" : __DIR__"shi_1",
        ]));
        set("item_desc", ([
                "chuang" : "木板作成的小床，但是没有一丝尘埃。\n" ,
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
        if(arg=="chuang")
        return notify_fail("你用力拉了拉床板，结果一点动静都没有！\n");
        else return 0;
}

int do_knock(string arg)
{
        object me;
        me = this_player();
        if (!arg||arg=="") 
                return notify_fail("你要敲什么？\n");
          if (arg != "chuang")
                return notify_fail("你要敲什么？\n");
          if( arg=="chuang" ) {
                message_vision("$N试著敲了敲床板。\n", me);
                if (me->query("bang_bad/name")=="修罗门")
                {
                        message_vision(HIB"床板吱呀一声开了，从里面探出个头来，看了$N两眼说道：“原来是自家兄弟啊！”，
说完一把把$N拉了进去。\n"NOR, me);
                        me->move(__DIR__"xlm_bjfb");
                        return 1;
                }
                if (me->query("bang_bad/name")!="修罗门" && (int)me->query("shen") <= 0)
                {
                        message_vision(HIB"床板吱呀一声开了，从里面探出个头来，看了$N两眼说道：“是来投靠咱们修罗门的吧！”，
说完一把把$N拉了进去。\n"NOR, me);
                        me->move(__DIR__"xlm_bjfb");
                        return 1;
                }
                if( me->query("bang_good") || (int)me->query("shen") > 0 ) 
                { 
                        message_vision("床板吱呀一声开了，从里面探出个头来，看了$N两眼说道：“你这种人也敢来此，活的不耐烦了么？”\n门被重重的关上了。\n",me);  
                        return 1; 
                } 
                message_vision("门板吱呀一声开了，从里面探出个头来，看了$N两眼说道：“既然是本门的兄弟，就进来吧！”，
说完一把把$N拉了进去。\n",me);
                me->move(__DIR__"xlm_bjfb"); 
                return 1; 
        }
        
        return 1;
}
  
