// zhang.c ��������

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	string msg;
        int ap, dp;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("��������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (target->is_busy())
		return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɣ�\n");
		
	if ((int)me->query_skill("jiuyin-shengong", 1) < 100)
		return notify_fail("��ľ����񹦲�����񣬲���ʹ�þ������ơ�\n");

	msg = HIY "$N" HIY "˫��һ�����û���������Ӱ����������$n"
              HIY "��ȥ��\n" NOR;

        ap = me->query_skill("jiuyin-shengong", 1) * 3 / 2 +
             me->query_skill("martial-cognize", 1);
        dp = target->query_skill("parry") +
             target->query_skill("martial-cognize", 1);

	if (ap / 2 + random(ap) > dp)
        {
		msg += HIR "���$p" HIR "��$P" HIR "�Ƶ�ʩչ���������ʽ��\n" NOR;
		target->start_busy(ap / 45 + 2);
	} else
        {
		msg += CYN "����$p" CYN "������$P" CYN "��������·��"
                       "��������Ӧ�����硣\n" NOR;
		me->start_busy(1);
	}
	message_combatd(msg, me, target);

	return 1;
}