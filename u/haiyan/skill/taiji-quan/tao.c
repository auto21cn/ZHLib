// tao.c ̫��ȭ���ס��־�

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;

        if (! target) target = offensive_target(me);

        if (userp(me) && ! me->query("can_perform/taiji-quan/tao")) 
                return notify_fail("�㻹����ʹ�á��ס��־���\n"); 

        if (! target || ! me->is_fighting(target))
                return notify_fail("���ס��־�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (objectp(me->query_temp("weapon")))
                return notify_fail("�������ֲ���ʹ�á��ס��־���\n");         
                
        if ((int)me->query_skill("taiji-quan", 1) < 300)
                return notify_fail("���̫��ȭ������죬����ʹ�á��ס��־���\n");
                                
        if ((int)me->query("neili", 1) < 200)
                return notify_fail("����������̫��������ʹ�á��ס��־���\n");
                        
        msg = HIW "$N" HIW "ʹ��̫��ȭ���ס��־������ֻ�Ȧ����ȭ��������$n"
              HIW "��Ȼ�����\n" NOR;
        me->add("neili", -100);

        if (random(me->query_skill("force")) > target->query_skill("force") / 2)
        {
                me->start_busy(3);
                target->start_busy(random(3));
                damage = ((int)me->query_skill("force", 1) + 
                         (int)me->query_skill("taiji-quan", 1)) / 2;
                damage = damage / 3 + random(damage / 2);
                
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK,
                                           damage, 40,
                                           HIR "$n" HIR "��$N" HIR "�������ţ�ֻ��˫��"
                                           HIR "����ʩչ����$N" HIR "��ȭ�ݺݻ��У�\n"
                                           ":����@?");
        } else 
        {
                me->start_busy(3);
                msg += CYN "����$p" CYN "������$P"
                       CYN "����ͼ������Ӳ����һ�У����������\n" NOR;
        }
        message_combatd(msg, me, target);
        return 1;
}
