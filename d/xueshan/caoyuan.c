//      caoyuan.c ��ԭ
//      Designed by secret (����)
//      97/04/08

inherit ROOM;

void create()
{
        set("short","��ԭ");
        set("long",@LONG
������ѩɽ���µ�һƬ��ԭ�������������Ⱥɽ��ɽ
���ϻ������겻����ѩ��������һ����·��
LONG );
        set("outdoors","xueshan");
        set("exits",([
                "west"      : __DIR__"tulu1",
                "northeast" : "/d/xingxiu/silk4" ,
                "south"     : __DIR__"caoyuan1",
        ]));
        set("objects",([
                __DIR__"npc/yetu" : 4 ,
        ]));
        setup();
        replace_program(ROOM);
}