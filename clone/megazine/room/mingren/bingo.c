#include <ansi.h>
#include <room.h>

inherit ROOM;

void create()
{
        set("short",HIR "屠人魔陈列室" NOR);
	set("long", @LONG
这是【名人堂】收录的第一个名人屠人魔(bingo)的陈列室，你可以
看到和屠人魔一样大小的蜡像。以及他的简介（explain)。
LONG
	);

	set("exits", ([ 
                      "out" : "/clone/megazine/room/mingren",
]));
          set("objects",([
                "/clone/megazine/room/mingren/bingolx":1,
]));
          set("item_desc",([
                          "explain":HIR "【 真  人 】武当派第四代传人「残缺天下-无双剑」屠人魔(bingo)。\n"
                                   HIR "他是终极地狱里不可争议的高手，他的境界是新手们难以逾越地。\n" NOR,
]));
	set ("no_fight",1);
        set("no_clean_up", 0);
     	setup();
}
