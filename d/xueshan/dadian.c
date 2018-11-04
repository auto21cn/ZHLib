
#include <ansi.h>
#include <room.h>

inherit ROOM;

void create()
{
        set("short", HIY"大殿"NOR);
    set("long", @LONG
大殿内光线昏暗，烟雾缭绕，隐约可见华丽的柱子上，横梁上，
佛像上都积了厚厚一层酥油。许多喇嘛和信徒们对着大大小小的佛像
叩拜，祈祷，添酥油。殿内供奉的释迦牟尼像相传是文成公主下嫁时
带来的，由于年久失修，像上的金漆以剥脱了许多，斑斑驳驳的。
LONG
        );

    set("exits", ([
                "east"  : __DIR__"cedian1",
              "west"  : __DIR__"cedian2",
              "south" : __DIR__"guangchang",

    ]));

    set("time", time());

    set("objects", ([
                                __DIR__"obj/xiang" : 1,
                                    __DIR__"npc/zhirilama" : 1,
                                CLASS_D("xueshan")+"/lazhang" : 1,
                                __DIR__"npc/xiang-ke" : 2,
    ]));

    setup();
        "/clone/board/xueshan_b"->foo();
  
}

void  init()
{
        return;
}


