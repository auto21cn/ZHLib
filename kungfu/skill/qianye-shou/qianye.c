// qianye.c ǧҶ����
 
#include <ansi.h>
#include <combat.h>
 
inherit F_SSERVER;
 
int perform(object me)
{
	string msg;
	object weapon, target;
	int skill, ap, dp, damage;

        if (! target)
        {
	        me->clean_up_enemy();
	        target = me->select_opponent();
        }

	if (! target || ! me->is_fighting(target))
		return notify_fail("��ǧҶ���֡�ֻ����ս���жԶ���ʹ�á�\n");

        if (me->query_skill_mapped("force") != "hunyuan-yiqi" &&
            me->query_skill_mapped("force") != "yijinjing" &&
            me->query_skill_mapped("force") != "shaolin-xinfa" &&
            me->query_skill_mapped("force") != "jiuyang-shengong")
                return notify_fail("��ʹ�õķ������ڹ����޷�ʩչ��ǧҶ���֡���\n");

	skill = me->query_skill("qianye-shou", 1);

	if (skill < 120)
		return notify_fail("���ǧҶ�ֵȼ�����������ʹ�á�ǧҶ���֡���\n");

	if (me->query("neili") < 100)
		return notify_fail("��������������޷����á�ǧҶ���֡���\n");
 
	if (me->query_skill_mapped("hand") != "qianye-shou") 
		return notify_fail("��û�м���ǧҶ�֣��޷�ʹ�á�ǧҶ���֡���\n");

	msg = HIC "$N" HIC "ٿ�Ŀ���$n" HIC "������һ�Σ�"
	      "����������Ӱ����ͬ����ǧ��ֻ��һ�빥��" HIC
              "$n��\n" NOR;
 
	ap = me->query_skill("force") + me->query_skill("hand");
	dp = target->query_skill("parry") + target->query_skill("dodge");
        if (ap / 2 + random(ap) > dp || !living(target))
	{
		me->add("neili", -100);
		damage = 40 + ap / 11 + random(ap / 11);
		msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 35,
                                           HIR "$p" HIR "�������мܣ����޷���ܣ������$P"
                                           HIR "��������Ū����ͷת������Ҳ���˺����ۡ�\n" NOR);
		me->start_busy(1);
                if (ap / 3 + random(ap) > dp && ! target->is_busy())
                        target->start_busy(ap / 50 + 2);
	} else
	{
		msg += CYN "����$p" CYN "�Ŀ�����$P" CYN
                       "����ʽ����������ȫȻ������$P"
                       CYN "�Ĺ��ơ�\n" NOR;
		me->add("neili",-30);
		me->start_busy(3);
	}
	message_combatd(msg, me, target);

	return 1;
}