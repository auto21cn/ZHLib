#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "辕门外"NOR);
        set("long", @LONG
这里就是「蒙古」军营驻扎地了，远远地可以看见大营内飞扬的尘土，不
时有几匹快马飞奔进出，你正欲再看，忽然嗖地一枚冷箭从你头上飞过，还是
赶快离开的好。
LONG
);
        set("defence",120);
        set("no_magic", "1");
        set("exits", ([ /* sizeof() == 5 */   
               "south"  : __DIR__"caoyuan4",
        ]));    

        set("objects", ([

        ]));
    
        setup();
}

void init()
{
        object me = this_player();

        if (me->query_temp("jun_quest/party") == "song")
                add_action("do_break", "break");
}

int do_break()
{
        object room = this_object(), me = this_player();

        if (me->is_busy())
                return notify_fail("你正忙着呢！\n");

        if (room->query("exits/north"))
                return notify_fail("辕门的的防御已经被击破了，快冲进去啊！\n");

        if (room->query("defence") < 1)
        {
                room->set("defence", 0);
                tell_object(me, HIR "辕门的的防御已经被击破了，快冲进去啊！\n" NOR);
                room->set("exits/north", __DIR__"mying");
                call_out("door_close", 20, room);
                return 1;
        } else
        {
                message_vision(
                        HIY "$N带着一支攻城队伍正加紧攻击着辕门的防御工事！\n" NOR, me);
                room->add("defence", -random(me->query_temp("jun_quest/group")));
                me->start_busy(2 + random(2));
                return 1;
        }
}

void door_close(object room)
{
        if (room->query("exits/north"))
        {
                room->delete("exits/north");
                tell_object(all_inventory(room),
                        HIW "蒙古军连忙带着一支队伍把辕门的防御工事修好了！\n" NOR);
        }
        return;
}


