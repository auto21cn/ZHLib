// Updated by rama

inherit ROOM;
#include <ansi.h>

int do_open(string arg);
int do_knock(string arg);

void create() {
        set("short", "青羊宫");
        set("long", @LONG 
青羊宫是天下第一大道观。观中林木婆娑，冠盖亭亭观中道士匆
匆来去，没人得空理你，更没人接待你。你觉得到一种宽松的失落。
旁边有一个木门（door）。
LONG );
        set("outdoors", "suzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "northeast" : __DIR__"westroad1",
        ]));
        set("item_desc", ([
                "door" : "厚厚的木门紧关着，有些年岁了。\n" ,
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
        return notify_fail("你用力拉了拉木门，结果一点动静都没有，看来是被反锁了！\n");
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
                if (me->query("bang_bad/name")!="修罗门" && (int)me->query("shen") <= 0)
                {
                        message_vision(HIB"木门吱呀一声开了，从里面探出个头来，看了$N两眼说道：“是来投靠咱们修罗门的吧！”，
说完一把把$N拉了进去。\n"NOR, me);
                        me->move(__DIR__"xlm_cdfb");
                        return 1;
                }
                if( me->query("bang_good") || (int)me->query("shen") > 0 ) 
                { 
                                command("say 哪里来的邪魔歪道，找打么？\n"); 
                        return 1; 
                } 
                message_vision("木门吱呀一声开了，从里面探出个头来，看了$N两眼说道：“既然是本门的兄弟，就进来吧！”，
说完一把把$N拉了进去。\n",me);
                me->move(__DIR__"xlm_cdfb"); 
                return 1; 
        }
        
        return 1;
}
  
