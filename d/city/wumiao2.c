// Room: /city/wumiao2.c
// YZC 1995/12/04 

#include <room.h>

#define BOARD_TOC "/doc/board/toc"
#define BOARD_DIR "/doc/board/"
inherit ROOM;
string look_shu();

void create()
{
	set("short", "������¥");
	set("long", @LONG
�������������Ķ�¥�����﹩�������ɵĳ������ƺ��������ܣ���������
���������Ӣ��������
LONG );

	set("no_fight", 1);
	set("no_steal", 1);
	set("no_beg", 1);
	set("no_sleep_room", 1);
             set("objects", ([ 
                     "/u/sanben/xquest/npc/zixu" : 1, 
                     "/quest/advance/advance" : 1,                      	
             ])); 


	set("exits", ([
		"down" : __DIR__"wumiao",
	]));
	setup();
}