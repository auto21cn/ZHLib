// /guanwai/xiaowu.c

inherit ROOM;

void create()
{
    set("short", "小茅屋");
    set("long", @LONG
这是一座用长白山松木垒成的小屋，屋内打扫的很干净。四周的墙壁上
挂满了兽皮和雪橇，一张小小的桌旁坐着一个虬髯大汉。
LONG );
    set("exits", ([
        "south" : __DIR__"xiaoyuan",
        "north" : __DIR__"houyuan",
    ]));
    set("objects", ([
        CLASS_D("hu") + "/hufei" : 1,
    ]));
    set("valid_startroom", 1);
    setup();
    "/clone/board/hu_b"->foo();
}

