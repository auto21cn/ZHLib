#include <room.h>
inherit ROOM;

void create()
{
	set("short", "鳌拜书房");
	set("long", @LONG
这里是鳌拜书房，却没有一本书。各种古玩琳琅满目，商周青铜、汉瓦
当、唐三彩，珍珠宝石，应有尽有，只要拥有一件，就够你吃一辈子了。北
面墙上有一副画。书桌上有一本书。
LONG );

	set("exits", ([
		"east" : __DIR__"aofu_zoulang3",
	]));
	set("objects", ([
		__DIR__"npc/shizhe" : 1,
	]));
	setup();
}
