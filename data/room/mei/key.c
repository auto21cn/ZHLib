// File(/data/room/mei/key.c) of mei's key
// Create by LUBAN written by Doing Lu

#include <ansi.h>

inherit ITEM;

string query_autoload() { return "1"; }

void create()
{
        set_name(YEL "��ʫ��ҵ�Կ��" NOR, ({ "key", "1 of mei" }));
        set_weight(10);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", @LONG
һ��������������֮��(mei)��Կ�ס�
����ԭ��Կ�ס�
LONG );
                set("unit", "��");
                set("no_pawn", 1);
                set("no_sell", 1);
                set("item_make", 1);
                set("value", 1);
        }
}