// 纽约港

#include <ansi.h> 
inherit ROOM;

void create()
{
	set("short", "纽约港外小道");
	set("long", @LONG
这里是纽约港外的一条小道，可以通向纽约市中心。
LONG );
	set("exits", ([		
		"west"        : __DIR__"road2",
              "east"        : __DIR__"newyork",
	]));
	setup();	
}

