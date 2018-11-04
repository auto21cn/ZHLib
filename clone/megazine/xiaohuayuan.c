// Room: /u/wfoxd/xiaohuayuan.c

inherit ROOM;

void create()
{
	set("short", "小花园");
	set("long", @LONG
这里是山庄的一个小花园，你可以看见一些五颜六色的花(flower),从这里可以通到西面的院落。
LONG	);
	set("exits", ([ /* sizeof() == 3 */
  		"south" : __DIR__"lajichang",
  		"east" : __DIR__"wroom",
  		"west" : __DIR__"wroom2",
	]));
        set("objects",([
                "/d/foshan/obj/hua1" :1,
                "/d/foshan/obj/hua2" :2,
                "/d/foshan/obj/hua3" :3,
	]));

	set("item_desc", ([
                "flower" : "这里全部都是五颜六色的名贵花种。\n",
	]));
	setup();
	replace_program(ROOM);
}
