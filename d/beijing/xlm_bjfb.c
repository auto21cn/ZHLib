
#include <ansi.h>

inherit ROOM;

#define PLACE "bjw"
#define TYPE  "bad"

int sort_by_id(mapping quest1, mapping quest2);

void create()
{
        set("short", "修罗门分坛");
        set("long", @LONG
这里是黑道组织修罗门的北京分坛，没想到堂堂的修罗门
分坛，竟然设立在这样一个不起眼的建筑下面，可能是天子脚
下，皇城根儿的缘故，这里的分坛格外的隐秘，而且恐怖。正
中的镶金椅上正卧着一位妖艳的女子。旁边的墙上挂着一个任
务牌（paizi）。
LONG);

        set("objects", ([
               __DIR__"npc/boss-hu"   : 1,
        ]));

        set("no_fight",1);

        set("exits", ([
                "up" : __DIR__"minju",
        ]));

        setup();
}
#include <bang_bad.h>

