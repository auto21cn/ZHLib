// By yuchang@zhyx
inherit ROOM;
#include <ansi.h>  

void create()
{
        set("short", "宝库");
        set("long", @LONG  
这是一个宽阔的房间，室顶四角均有通气口，两边 
平排放置共几百个该是装载奇珍异宝的箱子(xiang)，贴
墙有几百个兵器架(jia)，放满各种，兵器 ,足够装备一
个万人的军队了!
LONG
        ); 
        set("item_desc", ([       
"xiang" : "箱子里刻着一些字符，好象是一样武功，你不由想仔细看(think)一下!\n",          
   "jia" : "兵器架上其中有一跟棍特别吸引人，你要拿(pick)出来看看吗?\n",      

                          ]));
        set("exits", ([
              "north" : __DIR__"baokudt",
                      ]));
        set("no_stab", 1);
        set("no_clean_up", 0);
        setup();
}
void init()
{
  object me = this_player(); 
    add_action("do_pick", "pick");  
    add_action("do_push", "push");     } 

int do_pick(string arg)
{
        object sword, me=this_player();

        if( !arg || arg=="" ) return 0;

        if( arg=="jia" )
                             {  
if(query_temp("nasword")){ 
   message_vision("$N想去拿鞭子结果发现已经给人拿了\n", this_player());
     return 1;
 }
                                message_vision(
HIY"$N在兵器架上拿下了一根鞭子!\n"NOR, this_player());
                    sword = new(__DIR__"obj/suixin-whip");
                        sword->move(me);   
set_temp("nasword",1);
 message("channel:chat", HBRED HIW"【宝藏】"+me->query("name")+"在杨公宝库里发现了碎心鞭了!\n"NOR,users()); 
return 1;
                }
        return 1;
}
int do_push(string arg)
{
  object me = this_player();
        if(!arg || arg!="door")
                return notify_fail("你要推什么？\n");
   if(query("exits/south"))
           return notify_fail("门已经开了,你推个头？\n");
  message_vision(HIG"$N轻轻推开墙壁，发现有道暗门!\n"NOR,me);
   set("exits/south", "/d/changan/dong-chengmen"); 
  call_out("on_guanmen", 5);
return 1;
}
void on_guanmen(object room)
{
      message_vision(HIG"突然出现咔咔的响声,墙壁又合上了!\n"NOR, this_player());
delete("exits/south");
}

