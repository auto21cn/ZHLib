// wuchang3.c

inherit ROOM;

void create()
{
        set("short", "东练武场");
	set("long", @LONG
这里是华山派的练武场，场上立这几个木人，地处偏僻，有些荒凉。
LONG );
        set("exits", ([ /* sizeof() == 2 */
            "west"     : __DIR__"wuchang1",
        ]));
        set("objects", ([
            "/clone/npc/mu-ren" : 3,
        ]));
        set("outdoors", "huashan");

        setup();
	replace_program(ROOM);
}

