// /guanwai/shichang.c

inherit ROOM;

void create()
{
	set("short", "采石场");
	set("long", @LONG
这里是山脚，眼前蓦然耸立着一座大山，不过一侧已经被炸的支离
破碎，工人们开开往往，搬运着石料。在北方也有这么大的石山，你不
禁有些惊讶。眼前有一个人，开起来像个监工。
LONG );
	set("exits", ([
		"west" : __DIR__"tulu",
	]));

        set("objects", ([
                __DIR__"npc/jiangong" : 1,
        ]));

        set("no_fight", 1);

	set("outdoors", "guanwai");
	setup();
	replace_program(ROOM);
}

