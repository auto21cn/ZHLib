// by yuchang
inherit ROOM;
#include <ansi.h>
#include <room.h>
int do_press(string arg);

void create()
{
      set("short", "藏剑庐");
      set("long",
                "这里就是傲剑山庄的藏剑庐。只见靠墙处有一个巨大的\n"
                "红木制武器架(shelf)，场中是一个巨大的剑炉(stove)"
                "，里\n面燃烧着熊熊烈火，隐约可看到烈火中有一把赤红色"
                "的宝剑。\n");
      set("exits",([
           "south" : __DIR__"cjl2",
      ]));

      set("item_desc", ([
      "shelf" : "这是一只由名贵红木所制用来存放配剑的架子，\n"
                "里面似乎有块令牌可以拿出来(take lingpai)。\n",
      "stove" : HIR"剑炉里面燃烧着熊熊烈火，隐约可看到烈火中有一把赤红色\n"
                "的宝剑。你何不试试(get sword)?\n"NOR,
      ])); 

       setup();
}

void init()
{
      add_action("do_get", "get");
      add_action("do_press", "press");
      add_action("do_take", "take"); 
}
/*
int do_press(string arg)
{
    string p;
    object me,obj;
    object ob;
    me = this_player();
    ob = this_object();

    p = this_player()->query("reborn_start/jshj/pswd"); 

    if ( me->query(query("reborn_start/jshj/get")) ); 
       return notify_fail("你不是已经拿到剑了吗？\n");

    if( ! arg )
       return notify_fail("你要输入的密码是啥？\n");

    if( arg == p )
    {
        message_vision("$N只听得一阵隆隆的响声由远及近。\n", me);
        message_vision("剑炉缓缓移了开来，露出一个洞。一把宝剑呈现在$N面前。\n", me);
        obj = new ("/d/zhuanshi/obj/jiushi");
        obj->move(me);
        return 1;
    }
    else
    {
            message_vision("$N一阵乱按，突然石板的缝隙间射出一支毒箭！。\n", me);
            me->unconcious();
            return 1;
    }
}*/

int do_get(string arg)
{
    object me = this_player();   

    if( !arg || arg != "sword" ) 
       return 0;

    if ( ! me->query_temp("reborn_start/jshj/key") )
    {
       message_vision(HIC"$N仔细一看才发现原来剑炉上有锁，没有钥匙是打不开的！\n" NOR, me);       
       return 1;
    }
    return 0;
}


int do_take(string arg)
{
       object me,obj;
       object ob;
       me = this_player();
       ob = this_object();

       if( !arg || arg != "lingpai" && arg !="ling" && arg != "pai" ) 
           return notify_fail("你要拿什么？\n");

       if (me->query("reborn_start/jshj/ling")) 
       {
          write("你不是已经有一块令牌了吗？\n");
          return 1;
       }

       obj = new (__DIR__"npc/obj/ling");      
       obj->move(me);      

       message_vision(HIC"$N伸手从架子上取下一块令牌来。\n" NOR, me);      
       me->set("reborn_start/jshj/ling",1);
       me->start_busy(2);
       return 1;
}



