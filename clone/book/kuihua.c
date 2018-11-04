inherit ITEM;

#include <ansi.h>; 

void setup()
{}

void init()
{
        add_action("do_du", "du");
        add_action("do_du", "study");
}

void create()
{
        set_name(HIR "《辟邪剑谱》" NOR, ({ "pixie jianpu", "jianpu", "book", "pixie"}));
        set_weight(600);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long", HIR "这就是林家收藏在袈裟里的《辟邪剑谱》，相传是从少林寺里偷出来的。\n" NOR);
                set("value", 1);
                set("material", "paper");
                set("no_sell", 1);
        }
}

int do_du(string arg)
{
        object me = this_player();
        object where = environment(me);
        object ob;
        mapping skill;
        int plvl, con, improve;
        int neili_lost;

        if (! arg || !id(arg))
                return 0;
        if (me->is_busy())
        {
                write("你现在正忙着呢。\n");
                return 1;
        }
        if (me->is_fighting())
        {
                write("你无法在战斗中专心下来研读新知！\n");
                return 1;
        }
        if (where->query("no_fight"))
        {
                write("你无法在这里静下心来研读宝典。\n");
                return 1;
        }
        if ((string)me->query("gender") == "女性")
        {
                write("自古没有听说女人可以读《葵花宝典》的。\n");
                return 1;
        }
        if ((string)me->query("gender") == "男性")
        {
               write("《葵花宝典》的第一页写着：欲练神功，必先自宫。\n");
               return 1;
        }
        if (! me->query_skill("literate", 1))
        {
                write("你是个文盲，先学点文化(literate)吧。\n");
                return 1;
        }
        if (me->query_skill("pixie-jian", 1) >= 180)
        {
                write("这本书你已经研究得差不多了，没什么好读的了。\n");
                return 1;
        }
        if ((int)me->query("combat_exp") < 200000 )
        {
                        write("你的实战经验不足，再怎么读也没用。\n");
                        return 1;
        }
        if ((int)me->query("max_neili") < 500)
        {
                        write("你的内力太差，无法修炼此等神功。\n");
                        return 1;
        }
        switch(random(3))
        {
        case 0:
                message("vision", me->name() + "偷偷摸摸翻出一本书在读。\n", environment(me), me);
                break;
        case 1:
                message("vision", me->name() + "边读书边骚首弄姿，好象在模仿女人。\n", environment(me), me);
                break;
        case 2:
                message("vision", me->name() + "边读书边把腰身扭来扭去，甚为诡异。\n", environment(me), me);
                break;
        }
        if ((int)me->query("jing") < 30)
        {
                write("你现在过于疲倦，无法专心下来研读新知。\n");
                return 1;
        }

        plvl = me->query_skill("pixie-jian", 1);
        if (plvl > 170) neili_lost = 80; else
        if (plvl > 150) neili_lost = 50; else
        if (plvl > 120) neili_lost = 25; else
        if (plvl > 100) neili_lost = 15; else
        if (plvl > 50)  neili_lost = 12;
                    else neili_lost = 8;

        con = me->query_con();

        if ((int)me->query("neili") < neili_lost)
        {
                write("你内力不够，无法钻研这么高深的武功。\n");
                return 1;
        }

        if (! me->can_improve_skill("pixie-jian", 1))
        {
                write("你的实战经验不足，再怎么读也没用。\n");
                return 1;
        }

        if (plvl > 10 && con / 2 + random(con) < 40 && random(100) == 1)
        {
                tell_object(me, HIR "你依照着宝典所示运转内息，突然只觉内息逆流而上，四肢冰凉，心火如\n"
                                    "焚，惨嚎一声，晕了过去。\n" NOR);

                if ((int)me->query("max_neili") > 10 )
                {
                        me->add("max_neili", -10);
                }
                me->unconcious(); 
		return 1;
        }

        if (plvl < 60)
           improve = 10; else
        if (plvl < 90)
           improve = 10 + random((int)me->query("int") - 9); else
        if (plvl < 140)
           improve = 10 + random((int)me->query("int") * 2 - 9); else
        if (plvl < 180)
           improve = 10 + random((int)me->query("int") * 4 - 9); else
           improve = 10 + random((int)me->query("int") * 8 - 9);

        me->receive_damage("jing", random(30) + 30);
        me->add("neili", -neili_lost);
        me->improve_skill("pixie-jian", improve);
        me->start_busy(random(1) + 1);
        write("你研读《葵花宝典》，颇有心得。\n");
        return 1;
}
