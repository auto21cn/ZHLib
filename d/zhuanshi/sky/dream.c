#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIG "【梦境】" NOR);
        set("long", CYN @LONG
这里是梦境。你感觉到迷迷糊糊的，意识很不清晰。
四处都是白茫茫一片，看什么都不真切。
LONG NOR );
 /*       set("exits", ([
                "enter" : __DIR__"sky1",
]));*/
        set("sleep_room", 1);
        set("no_fight", 1);
        set("objects", ([
                "/adm/npc/buddha2": 1,
        ]));

        setup();
}

