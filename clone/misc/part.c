// part.c ����ĳ��λ

#include <ansi.h>

inherit ITEM;
inherit F_FOOD;
inherit F_CUTABLE;
inherit F_SILENTDEST;

void eat_effect();
int is_body_part() { return 1; }

void create()
{
        set_name(RED "��֫" NOR, ({ "body part"}));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("value", 0);
        	set("food_supply", 15);
        	set("food_remaining", 4);
        }
}

string long() { return ::long() + extra_desc(); }

int set_from(object owner)
{
        apply_effect((: eat_effect :));
        switch (name())
        {
        case "����":
        case "����":
        case "����":
        case "��ͷ":
        	set("food_supply", 10);
	        set("food_remaining", 1);
                break;
        case "����":
        case "�˽�":
        	set("food_supply", 15);
	        set("food_remaining", 2);
                break;
        case "�ֱ�":
        case "����":
        	set("food_supply", 20);
	        set("food_remaining", 5);
                break;
        default:
        	set("food_supply", 5);
	        set("food_remaining", 2);
        }
        return 1;
}

int finish_eat()
{
        object ob;
        if (name() != "�ֱ�" && name() != "����")
                return 0;
        ob = new("/clone/misc/bone");
        ob->move(environment());
        return 0;
}

void eat_effect()
{
        object me;

        me = this_player();
        me->add("combat/eatman", 1);
        if (me->query("shen") > -1000)
                me->set("shen", -1000);
}
