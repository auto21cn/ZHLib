//      houdian.c 后殿

inherit ROOM;

void create()
{
        set("short","后殿");
        set("long",@LONG
这里是雪山寺的后殿，也是雪山弟子闭门练功的地方。
殿内是一些练功的蒲团和木人，还有一些吊挂着的沙袋和
直竖的木桩。
LONG );
        set("exits",([
                "south" : __DIR__"neidian",
                "north" : __DIR__"tower",
        ]));
        set("objects",([
                "/clone/npc/mu-ren" : 3,
        ]));
        setup();
        replace_program(ROOM);
}

