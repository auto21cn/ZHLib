inherit ROOM;

void create()
{
	set("short", "【幽风山庄广场】");
	set("long", @LONG
你轻轻的打开了铁门，走了进来，一个宏伟的山庄映如你的眼帘。原
来这里就是传说中的幽风山庄，你只觉得整个山庄都笼罩在一片幽风当中。
你不觉打了个冷颤。正对着大门有一个八丈来高的旗杆上面挂着“幽
风山庄”四个大字的大旗。你可以看到山庄的正殿就在你前面。
LONG
	);
	set("exits", ([ 
           	"east" : __DIR__"eroom",
           	"out" : __DIR__"men",
           	"west" : __DIR__"wroom",
	]));
	set("objects", ([ 
	]));
	replace_program(ROOM);
}
