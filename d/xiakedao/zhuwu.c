// zhuwu.c

inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
����һ������ڴִ�����Ӵ�����ӣ���ز������ߡ���һС����
�����ſڡ�
LONG );
        set("exits", ([
                "east" : __DIR__"haibin",
                "enter": __DIR__"zhuwu2",
        ]));
        set("outdoors", "xiakedao");
        setup();
        replace_program(ROOM);
}