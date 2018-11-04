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
        set_name(HIR "����а���ס�" NOR, ({ "pixie jianpu", "jianpu", "book", "pixie"}));
        set_weight(600);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", HIR "������ּ��ղ���������ġ���а���ס����ഫ�Ǵ���������͵�����ġ�\n" NOR);
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
                write("��������æ���ء�\n");
                return 1;
        }
        if (me->is_fighting())
        {
                write("���޷���ս����ר�������ж���֪��\n");
                return 1;
        }
        if (where->query("no_fight"))
        {
                write("���޷������ﾲ�������ж����䡣\n");
                return 1;
        }
        if ((string)me->query("gender") == "Ů��")
        {
                write("�Թ�û����˵Ů�˿��Զ����������䡷�ġ�\n");
                return 1;
        }
        if ((string)me->query("gender") == "����")
        {
               write("���������䡷�ĵ�һҳд�ţ������񹦣������Թ���\n");
               return 1;
        }
        if (! me->query_skill("literate", 1))
        {
                write("���Ǹ���ä����ѧ���Ļ�(literate)�ɡ�\n");
                return 1;
        }
        if (me->query_skill("pixie-jian", 1) >= 180)
        {
                write("�Ȿ�����Ѿ��о��ò���ˣ�ûʲô�ö����ˡ�\n");
                return 1;
        }
        if ((int)me->query("combat_exp") < 200000 )
        {
                        write("���ʵս���鲻�㣬����ô��Ҳû�á�\n");
                        return 1;
        }
        if ((int)me->query("max_neili") < 500)
        {
                        write("�������̫��޷������˵��񹦡�\n");
                        return 1;
        }
        switch(random(3))
        {
        case 0:
                message("vision", me->name() + "͵͵��������һ�����ڶ���\n", environment(me), me);
                break;
        case 1:
                message("vision", me->name() + "�߶����ɧ��Ū�ˣ�������ģ��Ů�ˡ�\n", environment(me), me);
                break;
        case 2:
                message("vision", me->name() + "�߶���߰�����Ť��Ťȥ����Ϊ���졣\n", environment(me), me);
                break;
        }
        if ((int)me->query("jing") < 30)
        {
                write("�����ڹ���ƣ�룬�޷�ר�������ж���֪��\n");
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
                write("�������������޷�������ô������书��\n");
                return 1;
        }

        if (! me->can_improve_skill("pixie-jian", 1))
        {
                write("���ʵս���鲻�㣬����ô��Ҳû�á�\n");
                return 1;
        }

        if (plvl > 10 && con / 2 + random(con) < 40 && random(100) == 1)
        {
                tell_object(me, HIR "�������ű�����ʾ��ת��Ϣ��ͻȻֻ����Ϣ�������ϣ���֫�������Ļ���\n"
                                    "�٣��Һ�һ�������˹�ȥ��\n" NOR);

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
        write("���ж����������䡷�������ĵá�\n");
        return 1;
}