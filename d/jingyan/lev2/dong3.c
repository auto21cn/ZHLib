#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", CYN"石洞"NOR);
	set("long", CYN @LONG
这是一个黑漆漆石洞，周围都是坚硬的石壁。 
LONG NOR);
	set("exits", ([
		"west" : __DIR__"dong4",
		"east" : __DIR__"dong2",
                	]));
	set("no_clean_up", 0);
	setup();
	replace_program(ROOM);
}
