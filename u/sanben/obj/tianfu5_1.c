#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIY "五一金丹" NOR, ({ "wuyi jindan", "jindan", "dan" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIY "五一礼物金丹，四项天赋各加一点。\n" NOR);
                set("unit", "颗");  
                set("no_sell", 1);
                set("weight", 200);  
                set("only_do_effect", 1);
                set("gift_point",110);
        }
}

int do_effect(object me)
{

        message_vision(WHT "$N" WHT "一仰脖，吞下了一" +
                          query("unit") + name() + WHT 
                       "。\n" NOR, me);

        if ( me->query("liwu/wuyi2005/eat") )
        {
                tell_object(me, HIR "不过你觉得这药好像没起到什么"
                                "作用。\n" NOR);
        } else
                // 增加相应的天赋属性
{
        if (me->query("gift/str/succeed") + me->query("gift/str/fail") <= 9)
        {
                me->add("str", 1);
                me->add("gift/str/succeed", 1);
                me->add("gift/str/all", 1);
                tell_object(me, HIR "你的先天膂力增加了！你变得更有力了！\n" NOR);   
        }
        if (me->query("gift/int/succeed") + me->query("gift/int/fail") <= 9) 
        {
                me->add("int", 1);
                me->add("gift/int/succeed", 1);
                me->add("gift/int/all", 1);
                tell_object(me, HIW "你的先天悟性增加了！你变得更聪明了！\n" NOR);  
        }
        if (me->query("gift/con/succeed") + me->query("gift/con/fail") <= 9) 
        {
                me->add("gift/con/succeed", 1);
                me->add("gift/con/all", 1);
                me->add("con", 1);
                tell_object(me, HIY "你的先天根骨增加了！你变得更强壮了！\n" NOR);  
        }
        if (me->query("gift/dex/succeed") + me->query("gift/dex/fail") <= 9) 
        {
                me->add("dex", 1);
                me->add("gift/dex/succeed", 1);
                me->add("gift/dex/all", 1);
                tell_object(me, HIM "你的先天身法增加了！你变得更灵活了！\n" NOR);
        }
         me->set("liwu/wuyi2005/eat",1);
         log_file("static/wuyi", sprintf("%s(%s) eat 天赋 at %s.\n",
                 me->name(1), me->query("id"), ctime(time())));
}
        destruct(this_object());

        return 1;
}


