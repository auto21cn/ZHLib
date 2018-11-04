// Room: /d/xiakedao/xkroad5.c
// Modified by Java on Feb.14.1998
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "渔港");
	set("long", @LONG
这里是个小小渔港。南面海面漂浮着几艘小船，抬眼望，海天相
连，无边无际。海鸥掠过浪尖，悠悠翩然。
LONG );
        set("outdoors", "xiakedao");
	set("exits", ([
		"east"    : __DIR__"xkroad4",
	]));
	set("objects", ([
		__DIR__"npc/shizhe" : 1,
	]));
	setup();
}

void init()
{
    add_action("do_enter", "enter");
}

int do_enter ( string arg )
{
    object ob ;
    string dir;
    if( !arg || arg !="boat" )
       {
         tell_object(this_player() , "你要 enter 哪儿？\n" ) ;
         return 1 ;
       }
    ob = this_player () ;
    message_vision("船夫一见有人上船，忙叫了一声：开船喽！\n", ob);
    message_vision("船夫升起帆，船就向南方航行。\n", ob);
    ob->move("/d/xiakedao/dahai") ;
    tell_object(ob, BLU "你在海上航行了三天三夜.......\n" NOR ) ;
    call_out("home", 10 , ob );
    return 1 ;
}

void home( object ob )
{
    tell_object(ob , "大船终于抵达了海岛岸边。你走下船来。\n" ) ;
    ob->move (__DIR__"haitan") ;
}
