// /d/xiakedao/shiroom01.c ���͵� ʯ��1

inherit ROOM;

int do_study(string arg);
void create()
{
        set("short", "ʯ��");
        set("long", @LONG
���ǵ�һ��ʯ�ҡ�������������ȥ���Ѿ���Ϊӵ������Щ���е�
עĿ��˼���еĴ����������еı�Ŀ��������е����ڴ������硣
�����ǿ��ĥ�⻬�Ĵ�ʯ��(wall)��ʯ���Ե�ȼ�Ż�ѣ�������ʯ��
��ҫ�ð�����¡�
LONG );
        set("exits", ([
                "south" : __DIR__"shihole1",
        ]));
        set("item_desc", ([
                "wall" : @WALL
ǽ�����Ϸ����š��Կ��Ϻ�ӧ���������֡��ֵ��·�����һ��ͼ��ͼ
����һ�������������ֳ��ȣ����ַ��ƣ���̬��������������������
һ��ע���ƣ�������͸�Ӳ�����֡���������С�֣��������顣
WALL
        ]));

        set("no_fight", 1);
        set("no_beg", 1);
        set("no_clean_up", 0);
        setup();
}
void init()
{
        add_action("do_study","think");
}
#include "/d/xiakedao/shiroom.h"