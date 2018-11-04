// Room: /d/city/jiaowai1.c
#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
    set("short", "草地");
    set("long", @LONG
这是扬州郊外的一片芳草地，落英缤纷，蜂歌蝶舞，朝露
夕光，沁人心脾。真是好时光。偶有几对小男女结伴踏青，莺
声丽影，嬉闹动人。
LONG );

    set("exits", ([
        "north" : __DIR__"dongmen",
        "south" : __DIR__"jiaowai2",
    ]));

    set("no_clean_up", 0);
    set("outdoors", "yangzhou");
    setup();
}
