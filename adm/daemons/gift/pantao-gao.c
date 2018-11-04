// pantao-gao.c 蟠桃糕
// By Alf, Last Update 2001.11

#include <ansi.h>
inherit ITEM;
inherit F_FOOD;

void create()
{
    set_name(HIW"蟠桃糕"NOR, ({"pantao gao", "pantaogao"}));
    set_weight(40);
    if (clonep())
        set_default_object(__FILE__);
    else
    {
        set("long", "这是用昆仑山中特产的蟠桃制成的糕点，闻起来香气扑鼻。\n");
        set("unit", "块");
        set("value", 80);
    }
}

void init()
{
    add_action("do_eat", "eat");
}

int do_eat(string arg)
{
    object me = this_player();
    if (!id(arg))
        return notify_fail("你要吃什么？\n");
    if(arg=="pantao gao" || "pantaogao") 
    {
        me->set("food",(int)me->max_food_capacity());
        me->set("water",(int)me->max_water_capacity());
        message_vision(HIW"$N吃下一块蟠桃糕，只觉得口齿留香，不再感到饥渴。\n"NOR,me);
        destruct(this_object());
    }
    return 1;
}


