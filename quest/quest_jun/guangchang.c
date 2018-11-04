inherit ROOM;

void create()
{
	set("short", "中央广场");
	set("long", @LONG
这里是襄阳的中央广场，铺着青石地面。东面通向青龙门，
西面通向白虎门，南面直达朱雀门，远远地你可看到北面是襄
阳安抚使衙门。近年来蒙古大军屡次攻打襄阳，官府为防止蒙
古奸细混杂进来，已经不允许人们在此聚集。只见一队官兵在
此往来巡逻，你还是快离开吧。
LONG );
        set("outdoors", "xiangyang");
	set("exits", ([
		"east"  : __DIR__"eastjie1",
		"west"  : __DIR__"westjie1",
		"south" : "/d/xiangyang/southjie1",
		"north" : "/d/xiangyang/anfupailou",
	]));
	set("objects", ([
		"/d/xiangyang/npc/pian" : 1,
		"/d/xiangyang/npc/bing" : 1,
                "/clone/npc/walker" : 1,
	]));
	set("coor/x",-490);
	set("coor/y",-400);
	set("coor/z",0);
	setup();
	//replace_program(ROOM);
}

