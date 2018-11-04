#include <weapon.h>
#include <ansi.h>

inherit BLADE;

void create()
{
        set_name(HIR "Ѫ��" NOR,({ "xue dao", "dao", "xue", "blade" }) );
        set_weight(6000);
        if (clonep())
                destruct(this_object());
        else {
                set("long", HIR "����һ�Ѳ�������ı�����������ŵ�����"
                            "ѪӰ��\n" NOR);
                set("unit", "��");
                set("value", 800000);
                set("material", "steel");
                set("no_sell", "�⡭�ⲻ��Ѫ���ŵĶ������һ�Ҫ�Դ�����"
                               "�Ը����Űɣ�");
                set("wield_msg", HIR "$N" HIR "һ����Ц�����һ��Ѫ��ɫ"
                               "�ĵ����߸����𣬿����ж�ʱ������һ��ɱ��"
                               "��\n" NOR);
                set("unwield_msg", HIR "$N" HIR "һ����ߣ�������Ѫ����"
                               "�ر���\n" NOR);
                set("stable", 100);
        }
        init_blade(100);
        setup();
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int n;
        int my_exp, ob_exp;

        if (me->query_skill_mapped("blade") != "xuedao-dafa" ||
            me->query_skill("xuedao-dafa", 1) < 100)
                return damage_bonus / 2;

        switch (random(10))
        {
        case 0:
                if (! victim->is_busy())
                victim->start_busy(me->query_skill("blade") / 10 + 2);
                return HIR "$N" HIR "һ����ȣ�����Ѫ�������ն��������"
                       "��һ����Ѫɫ��â��ֱ�Ƶ�$n" HIR "�������ˣ�\n"
                       NOR;
        case 1:
                n = me->query_skill("blade");
                victim->receive_damage("qi", n, me);
                victim->receive_wound("qi", n, me);
                return HIR "$n" HIR "����ΧѪ�����죬��Ӱ���أ����ɵ���"
                       "��η�壬ֻ�ܹ���ǿ�����ֵ���\n" NOR;
        }
        return damage_bonus;
}

