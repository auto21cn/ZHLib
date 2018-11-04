//lingshe_zhangfa.c �����ȷ�

#include "ansi.h"

inherit SKILL;

mapping *action = ({
([	"action": "$Nʹ��һ�С����߳�����������$w�󿪴���ɨ��$n��$l",
	"force" : 380,
        "attack": 85,
	"dodge" : 35,
	"parry" : 50,
	"damage": 85,
	"skill_name" : "���߳���",
	"damage_type": "����"
]),
([	"action": "$N����$w������죬һ�С�ҡͷ��β����$n��$l��ȥ",
	"force" : 370,
        "attack": 87,
	"dodge" : 25,
	"parry" : 45,
	"damage": 88,
	"skill_name" : "ҡͷ��β",
	"damage_type": "����"
]),
([	"action": "$N����$w���Ӹ�����ʹһ�С������½�������$n��$l",
	"force" : 365,
        "attack": 80,
	"dodge" : 35,
	"parry" : 43,
	"damage": 80,
	"skill_name" : "�����½�",
	"damage_type": "����"
]),
([	"action": "$Nһ�С�����ͦ����������$w����ɨ��$n��$l",
	"force" : 410,
        "attack": 85,
	"dodge" : 35,
	"parry" : 40,
	"damage": 100,
	"skill_name" : "����ͦ��",
	"damage_type": "����"
]),
([	"action": "$Nʹ��һ�С��������ߡ���$w�����ػ���$n��$lɨȥ",
	"force" : 350,
        "attack": 89,
	"dodge" : 35,
	"parry" : 50,
	"damage": 95,
	"skill_name" : "��������",
	"damage_type": "����"
]),
([	"action": "$N����$wһ�ӣ�ʹ��һ�С��߲����ҡ����������ɨ��$n��$l",
	"force" : 340,
        "attack": 90,
	"dodge" : 45,
	"parry" : 35,
	"damage": 110,
	"skill_name" : "�߲�����",
	"damage_type": "����"
]),
([	"action": "$Nʹ��һ�С�������ɽ�����߾�����$w����ͷ����$n��$l",
	"force" : 390,
        "attack": 97,
	"dodge" : 40,
	"parry" : 45,
	"damage": 115,
	"skill_name" : "������ɽ",
	"damage_type": "����"
]),
([	"action": "$Nʹ��һ�С����߳�����������$w��һ̽��ֱɨ$n��$l",
	"force" : 410,
        "attack": 105,
	"dodge" : 45,
	"parry" : 45,
	"damage": 135,
	"skill_name" : "���߳���",
	"damage_type": "����"
]),
});

string query_skill_name(int level)
{
        return action[random(sizeof(action))]["skill_name"];
}

mapping query_action(object me, object weapon)
{
	if (random(me->query_skill("staff")) > 60
	&& me->query_skill("force") > 90
	&& me->query("neili") > 120 && random(3) == 0) {
		return ([
		"action": HIB"$NͻȻ˫�ֳŵأ�˫���ס$w"+HIB"������һ���������$n"NOR,
		"force" : 500,
		"damage": 180,
		"damage_type": "����"]);
	}
       return action[random(sizeof(action))];
}

int valid_enable(string usage) { return (usage == "staff") || (usage == "parry"); }

int valid_learn(object me)
{
	if ((int)me->query("max_neili") < 1000)
		return notify_fail("�������������\n");

	if ((int)me->query_skill("force") < 150)
		return notify_fail("����ڹ���򲻹���\n");

        if ((int)me->query_skill("staff", 1) < 100)
                return notify_fail("��Ļ����ȷ��������ң�����ѧϰ�����ȷ���\n");

        if ((int)me->query_skill("staff", 1) < me->query_skil("linshe-zhangfa", 1))
                return notify_fail("��Ļ����ȷ�ˮƽ�������޷���������������ȷ���\n");

	return 1;
}

int practice_skill(object me)
{
	object weapon;

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "staff")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if ((int)me->query("qi") < 70)
		return notify_fail("������������������ȷ���\n");

	if ((int)me->query("neili") < 80)
		return notify_fail("������������������ȷ���\n");

	me->receive_damage("qi", 60);
        me->add("neili", -69);
	return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
       int lvl,flvl;
       lvl = me->query_skill("lingshe-zhangfa",1);
       flvl = me->query("jiali");
       if (lvl < 80 || flvl < 10 || ! damage_bonus)
	       return;
        if (!me->query_temp("weapon") || !(me->query_temp("weapon"))->query("snake_type"))
       	return; 

       if (flvl * 2 + random(lvl) > victim->query_skill("force") &&
              victim->affect_by("snake_poison",
                              ([ "level" : flvl + random(flvl),
                                 "id"    : me->query("id"),
                                 "duration" : lvl / 100 + random(lvl / 10) ])))
       {
                return HIR "ֻ��$nʹ����һ����ȴ�Ǳ����ȶ��˵�С��ҧ�˸����ţ�\n" NOR;
       }
}

string perform_action_file(string action)
{
        return __DIR__"lingshe-zhangfa/" + action;
}