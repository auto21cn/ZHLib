// 转世神器之 魔戒
// Create by yuchang

#include <ansi.h>

#include <armor.h> 
inherit CLOTH; 

int is_magic_item() { return 1; }

void create()
{
        set_name(NOR + WHT + "魔戒" NOR, ({ "mo jie", "mojie", "jie" }) );
        set_weight(800);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "枚");
                set("long", NOR + WHT "这是一枚传说中的戒只，周身泛着眩目的光华，据\n"
                                      "说是天神浪翻云为了打通天地交界处所用。\n"
                                      "可用之来打开(chuansong)虚空，进入太虚境界。\n" NOR);
                set("material", "steel");
                set("wear_msg", NOR + WHT "$N" NOR + WHT "将魔戒戴在中指，顿时一"
                                           "道蓝光闪过。\n" NOR);
                set("remove_msg", NOR + WHT "$N" NOR + WHT "将魔戒从手指上取下来。\n" NOR);

        }
        setup();
}

void init()
{
        add_action("do_chuansong", "chuansong");       
}

int do_chuansong(string arg)
{
        object me;
        
        me = this_player();
        
        if(! objectp(present("mo jie", me)))return 0;
        
        if (me->is_fighting() || me->is_busy())
                 return notify_fail("你正忙呢！\n");
        
        if (! environment(me)->query("outdoors"))
                 return notify_fail("你得先到户外去。\n");
                 
        message_sort(NOR + WHT + "\n$N" NOR + WHT "举起双手手中的魔戒发出耀眼蓝光，"
                     "刹那间天空中露出一道裂痕，魔戒化做一道奇异的光芒将$N" NOR + WHT +
                     "卷进太虚之中。\n" NOR, me);
                
        me->move("/d/zhuanshi/sky/sky1");
        destruct(this_object());

        return 1;
}

