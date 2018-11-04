//  jitan.c 祭坛

inherit ROOM;

void create()
{
        set("short","雪山祭坛");
        set("long",@LONG
这里是雪山寺雪山祭坛，中间一个高台，青石砌就。
周围摆满了木柴和酥油，旁边一个盛水的颅钵搁着摆着一
只法铃。一些痛苦和可怜的亡灵可以在这里获得超度。
LONG );
        set("outdoors","xueshan");
        set("no_fight","1");
        set("exits",([
                "north" : __DIR__"chang",
        ]));
        set("objects",([
                __DIR__"npc/x_lama": 2,
                __DIR__"npc/fsgelun": 2,
                __DIR__"obj/jitan2": 1,
        ]));
        set("no_clean_up", 0);
        setup();
}

int valid_leave(object me, string dir)
{
        object ob;
        ob=(present("fa tan", (environment(me))));
        if ( me->query("name") == ob->query("pending")
        && ob->query("burning"))
                return notify_fail("你法事没做完就想走？\n");
        return ::valid_leave(me, dir);
}

