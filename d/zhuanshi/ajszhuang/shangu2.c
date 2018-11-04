//shangu2
#include <ansi.h>
inherit ROOM;

void create()
{ 
        set("short", "山谷迷道");
        set("long", @LONG
这是个大峡谷，四周弥漫着雾气，你胆颤心惊的象前摸索着，到处是一些
迷路人的尸体和骷髅。不时传来一阵阵鬼哭浪嚎，好象有什么东西在暗中
窥视着，你不由的加快了脚步。
LONG );
        set("outdoors", "ajszhuang");
        set("exits", ([
                "east" :  __FILE__,
                "west" :  __DIR__"shangu3",
                "south" : __FILE__,
                "north" : __FILE__,
        ]));             
}

int valid_leave(object me, string dir)
{     

        if ( me->query_skill("dodge") < 1000 )   
        {
                me->receive_damage("qi", 100);
                me->receive_wound("qi", 100);
                message_vision(HIW "\n突然山上一阵落石雷雨般"
                               "落向$N" HIW "。\n\n" NOR, me);               
        }
       return 1;

}
