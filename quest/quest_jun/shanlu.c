inherit ROOM;
#include <ansi.h>;

void create()
{
        set("short", "山麓");
        set("long",
"这里是襄阳城外的山麓，也是南下蒙古军队的必经之路，道路曲折
盘旋，十分难走，但是对于出征的大军来说，走这样难走的路都好象已经
成了极平常的事了。"
);
        set("outdoors", "xiangyang");
        set("no_magic",1);

        set("exits", ([
               "south"  : __DIR__"conglin1",
               "north"  : __DIR__"shanlu1",
        ]));

        setup();
} 

