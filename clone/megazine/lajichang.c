// Room: /u/wfoxd/lajichang.c

inherit ROOM;

void create()
{
	set("short", "焚化室");
	set("long", @LONG
这是一个焚化室，你可以在这里焚化物品。
LONG	);
	set("exits", ([ /* sizeof() == 1 */
  		"north" : __DIR__"xiaohuayuan",
	]));

	setup();
	replace_program(ROOM);
}
