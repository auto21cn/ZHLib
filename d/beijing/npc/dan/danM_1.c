#include <ansi.h>
inherit ITEM;
void create()
{
        set_name(HIM"龙涎丹"NOR, ({"longxian dan", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "粒");
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        mapping my;

        if (time() - me->query_temp("last_eat/dan(M)") < 400)
        {
                write("你刚服用过药，需药性发挥完效用以后才能继续服用。\n");
                return 1;
        }

        my = me->query_entire_dbase();

        if( me->is_busy() )
                return notify_fail("急什么，小心别噎着了。\n");

        me->set_temp("last_eat/dan(M)", time());

        message_vision(HIM "$N吃下一粒龙涎丹，感到内力又雄厚了一些。\n" NOR, me);
        me->add("max_neili", 1);

        me->start_busy(6);
        destruct(this_object());
        return 1;
}

