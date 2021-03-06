// File(/data/room/qiua/yingke.c) of qiua's room
// Create by LUBAN written by Doing Lu

#include <room.h>

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "密实迎客厅");
	set ("long", @LONG
这里是密实的主人净一迎接八方来客的地方。大凡客人来拜见净
一，少不得在这里寒暄叙话，了尽仰慕之情。东面通往一个茶室，是
主人陪同客人品尝天下名茶之处。 
LONG );

	set("exits", ([
		"north"  : __DIR__"yishiting",
                "south"  : __DIR__"zoudao",
                "east"   : __DIR__"chashi",
	]));

        create_door("east", "木门", "west", DOOR_CLOSED);

        set("objects", ([
                "/d/room/roomnpc/yahuan" : 2,
        ]));

        set("no_sleep_room", 1);
        setup();

        set("room_owner", "净一");
        set("room_name", "密实");
        set("room_id", "qiua");
        set("room_owner_id", "qiua");
        set("room_position", "山路");
}
