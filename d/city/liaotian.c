inherit ROOM;

int is_chat_room() { return 1; }

void create()
{
        set("short", "客店茶房");
        set("long", @LONG
这里是扬州客栈的茶楼，许多无所事事的人在这里聊天，店小二穿梭在客
人中间，忙个不停。左边有一个小门，那是通往终极地狱的【地狱杂志】社办
公室所在。
LONG );
        set("no_fight", 1);
        set("no_sleep_room",1);
        set("exits", ([
                "north" : __DIR__"kedian",
                "enter" : __DIR__"wfoxd",
        ]));

        setup();
}


