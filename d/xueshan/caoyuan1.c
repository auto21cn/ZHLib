//      caoyuan.c 草原
//      Designed by secret (秘密)
//      97/04/08

inherit ROOM;

void create()
{
        set("short","草原");
        set("long",@LONG
这里是雪山脚下的一片草原。北面是起伏的群山，山
顶上积着终年不化的雪。西边有一条土路。
LONG );
        set("outdoors","xueshan");
        set("exits",([
                "north"      : __DIR__"caoyuan",
        ]));
        set("objects",([
                __DIR__"npc/maoniu" : 2 ,
        ]));
        setup();
        replace_program(ROOM);
}
