// Code of JHSH
// /kungfu/skill/hamagong/puji.c  perform ����˻�
// sdong, 10/24/98
// maco 8/17/2000

#include <ansi.h>
#include <armor.h>
#include <combat.h>

inherit F_SSERVER;
//void tie_result(object me, object target);
void tie_hit(object me, object target);
void pu_hit(object me, object target);

int perform(object me, object target)
{
	object armor,weapon;
	int damage;
	string *limb, type, result, str;


	type = "����";

	if( !target ) target = offensive_target(me);

	if( !target
	||	!target->is_character()
	||	!me->is_fighting(target) )
		return notify_fail("�㲻��ս���С�\n");


	if ( objectp(me->query_temp("weapon")) )
		return notify_fail("���ֱֳ������޷�ʩչ��󡹦���Ʒ�������\n");

	if( (int)me->query_skill("hamagong", 1) < 250 )
		return notify_fail("��ĸ�󡹦��Ϊ������\n");

	if ( me->query_skill_mapped("force") != "hamagong")
		return notify_fail("��������ʹ���ڹ����Ǹ�󡹦��\n");

	if ( me->query_skill_mapped("strike") != "hamagong")
		return notify_fail("������װ�����Ʒ����Ǹ�󡹦��\n");

	if( me->query("neili") <= 2000 )
		return notify_fail("�������������\n");

	if( me->query("jingli") <= 500 )
		return notify_fail("��ľ���������\n");

	me->delete_temp("puji_time");
	pu_hit(me, target);

	return 1;
}

void pu_hit(object me, object target)
{
	object armor;
	int damage, time, ap, dp, pp, fap, hmg, force;
	string msg, *limb, type, result, str;
	object weapon;

	if( !target || !me || !me->is_fighting(target) ) return;

	if( !living(me) || me->is_ghost() ) return;

	if( !target || environment(me) != environment(target) || !me->is_fighting() ) return;

	type = "����";

	hmg = (int)me->query_skill("hamagong", 1);
	force = (int)me->query_skill("force", 1);

	ap = COMBAT_D->skill_power(me, "strike", SKILL_USAGE_ATTACK);
	if( ap < 1 ) ap = 1;
	ap = ap*(1+time);

	dp = COMBAT_D->skill_power(target, "dodge", SKILL_USAGE_DEFENSE);
	if( dp < 1 ) dp = 1;
	
	pp = COMBAT_D->skill_power(target, "parry", SKILL_USAGE_DEFENSE);
	if( pp < 1 ) pp = 1;

	me->add_temp("puji_time", 1);
	time = (int)me->query_temp("puji_time");

	if( time == 1 ) msg = HIB "\n$N˫��һ�䣬�������������󡱵�һ����У������󡹦������˫���뷢����ǰ�Ƴ�����һ��ʵ��$P��������֮���ۣ�$n��Ȼ���ܵ�ɽ�麣Х��ľ���Ϯ����\n" NOR;
	else if( time == 2 ) msg = HIM "\n$N��һ�Ƹ��꣬�ڶ�������Ѹ���쳣�ĸϵ���ǰ��δ˥���󾢼������Ʒ�Խ�����ҡ�\n" NOR;
	else msg = HIR "\n$N�ۿ�ǰ����գ�ȴ���޻��ң�˳������һ�ƣ���"+chinese_number(time)+"�Ƶ��Ʒ�����ɳĮ�籩��һ���͹�һ�󣬺�Х����$n������\n"NOR;

	message_vision(msg , me,target);
	
	me->add("neili", -hmg);
	me->add("jingli", -hmg/2);

	fap = random(ap + ap);

	if( living(target) && fap < dp ) {

		if(time == 1) message_vision(HIY "$n�ۼ���һ���������ͣ����Ȳ��ܣ����ֲ��ɣ�����˫��һ�㣬Ծ���ĳߣ��㿪����һ�ơ�\nֻ�������ڵ�һ�����죬$N��һ�Ƶľ�������һ�ɿ����ˣ���ʱ����������˾������ѡ�\n\n" NOR, me, target);
	
		else message_vision(HIY "$n�ۼ���һ���������ڣ�����˫��һ�㣬��Ծ���ߣ��ֶ㿪����һ�ơ�\nֻ�����һ�����죬��󡹦�;����û�������������һƬ����������ƾ��ˡ�\n" NOR, me, target);
		target->start_busy(1);
		me->start_busy(1 + random(2));
		if( me->query_skill("strike") > time*150 && time < 5)
			call_out("pu_hit",2+random(2),me,target);
	}

	else if( random(fap*2/3)< pp && random(4) == 0 && target->query("race") == "����" )
	{
		weapon = target->query_temp("weapon");
		if(weapon)
		{
			weapon->unequip();
			weapon->move(environment(target));
			target->reset_action();
			message_vision(HIR"$N�;��þ�����������֪�������"NOR + weapon->name() + HIR"���ַɳ����Ͻ�Ҳ��˫����ǰƽ�ơ���һ������Ӳ��Ӳ��ɲ��֮�䣬�����ﾹȻ��ס������\n"NOR, target );
		}
		else message_vision(HIR"$N�;�������������֪���Ҳ��˫����ǰƽ�ơ���һ������Ӳ��Ӳ��ɲ��֮�䣬�����ﾹȻ��ס������\n\n"NOR, target );

		message("vision", HIW BLK"���˱��Ǻ��ݺ��ܡ��������Ĳ�����ͻȻ�������߽�ʬ���ƣ�����ָҲ����һ�����ƺ���Ҳ����һ�ڡ�\n\n"NOR, environment(me), ({ me, target }) );

		target->add("neili", -hmg);
		target->add("jingli", -hmg);
		target->start_busy(3+random(2));
		me->start_busy(2+random(2));
		call_out("tie_hit",3+random(2),me,target);
	}

	else {
		if( target->query_temp("armor/cloth") )
			armor = target->query_temp("armor/cloth");

		if( (!living(target) || (!armor || (armor && armor->query("armor_prop/armor") < 150) )) && ( target->query_skill("dodge")+target->query_skill("parry") ) < random((me->query_skill("strike") + me->query_skill("force"))*2/3) && target->query("race") == "����")
		{
			message_vision(HIR"ֻ��$Nһ���ҽУ���һ������С��������$nһ������ͻȻƽƽ�ɳ����ڵ�һ�죬���������������֮�⣬ֱͦͦ�����ڵ��£���Ҳ������\n\n"NOR, target,target );
			target->receive_wound("qi", (int)target->query("eff_qi"), me);
			target->receive_damage("qi", (int)target->query("qi")+1,  me);
			me->add("neili", -(me->query("jiali")+hmg));
		}
		else
		{
			damage = (me->query("jiali") + 1) * (int)me->query_skill("force")/100 + (random(hmg)+force)*time + me->query_temp("apply/damage");

			if(damage > me->query_skill("strike")*(5+time) ) damage = me->query_skill("strike")*(5+time);
			if(damage < me->query_skill("strike")*time ) damage = me->query_skill("strike")*time;
			me->add("neili", -(me->query("jiali")+hmg));

			target->receive_damage("qi", damage,  me);
			target->receive_wound("qi", random(damage/2)+damage/4, me);
			target->start_busy(1+random(3));

			limb = target->query("limbs");

			if(random(2) ) type = "����";
			result = COMBAT_D->damage_msg(damage, type);
			result = replace_string( result, "$l", limb[random(sizeof(limb))]);
			result = replace_string( result, "$p", target->name() );
			message_vision(result, me, target);

			str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
			message_vision("( $N"+str+" )\n", target);
		}
	}

	me->start_busy(3+random(2));
}


void tie_hit(object me, object target)
{
	int sum, n1, n2;
	string msg;

	if( !target || !me || !me->is_fighting(target) ) return;

	if( !living(me) || me->is_ghost() ) return;

	if( !target || environment(me) != environment(target) || !me->is_fighting() ) return;

	sum = me->query_skill("force") + me->query_skill("strike") + target->query_skill("force") + target->query_skill("parry");
	n1 = me->query("neili");
	n2 = target->query("neili");

	me->add("neili", -100 * sum / ( me->query_skill("force") + me->query_skill("strike") ) ); 
	if(me->query("neili")<0)me->set("neili",0);

	target->add("neili", -150 * sum / ( target->query_skill("force") + target->query_skill("strike") ) );
	if(target->query("neili")<0)target->set("neili",0);

	if( n1 > 3000 && n2 > 3000) {
		msg = WHT"��ʱ˫����������ǿ��������ʤ������ʹ�Է��ش����ɡ�\n"NOR;

		if( n1 > n2 )
		msg += HIW"�����ֽ���һ�ᣬ$nͷ��͸��һ���Ƶİ���������Խ��ԽŨ����������һ�㡣\n"NOR;
		else msg += HIW"�����ֽ���һ�ᣬ$Nͷ��͸��һ���Ƶİ���������Խ��ԽŨ����������һ�㡣\n"NOR;
	}

	else {

		if( n1 > n2 ) msg = WHT"$N���ϴ߶���󡹦�;�������˥�Ǽ����Թ�Ƭ�̣�$n����ȫ�������졣\n"NOR;
		else msg = WHT"$N���Ϻ�����ʢ������󡹦���ӵ��˼��¡��Թ�Ƭ�̣�$N����ȫ�������졣$n�ƺ���Ȼ����ʮ�㣬ͷ�������������ϡ�\n"NOR;
		}

	message_vision(msg , me,target );


	if( me->query("neili") > 0 && target->query("neili") > 0 && living(me) && living(target) )
	{
		target->start_busy(3+random(2));
		me->start_busy(3+random(2));
		call_out("tie_hit",2+random(2), me,target);
		return;
	}

	if( target->query("neili") <= 0 )
	{
		message_vision(HIR "\n$NͻȻ������������ȫ��������ԭ��������ȫ���ľ���ͻ��ǰ��һƬ����֮�����ѱ���󡹦һ�ƻ��У���Ҳ�߲���һ����������������˫�۽��գ������ֽ���˵����������ϡ�\n\n" NOR, target);
		target->receive_wound("qi", (int)target->query("eff_qi"), me);
		target->receive_damage("qi", (int)target->query("eff_qi")+1,  me);
		return;
	}

	if( me->query("neili") <= 0 )
	{
		message_vision(HIR "\n$N���Ϻ���������ͻȻ������������ȫ��������ԭ��������ȫ���ľ�����󡹦��ʱȫ����������������ǰ��һƬ����֮������Ҳ�߲���һ��������������˫�۽��գ������ī���˵����������ϡ�\n\n" NOR, me);
		me->receive_wound("qi", (int)me->query("eff_qi"), target);
		me->receive_damage("qi", (int)me->query("eff_qi")+1,  target);
	}
}