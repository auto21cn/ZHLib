// feifeng-whip.c �ɷ�޷�

#include <ansi.h>

inherit SKILL;

mapping *action = ({
([      "action": "$N����Ծ��һ�С����չ�᡹������$w���¶��ϣ�����$n������",
        "force" : 100,
        "dodge" : 50,
        "attack" :30,
        "damage": 40,
        "lvl"   : 15,
        "skill_name" : "���չ��",
        "damage_type":  "����"
]),
([      "action": "$Nһ�С��ʷ����ࡹ������$wֱ����$n��$l",
        "force" : 140,
        "dodge" : -10,
        "attack" :70,
        "damage": 80,
        "lvl"   : 20,
        "skill_name" : "�ʷ�����",
        "damage_type":  "����"
]),
([      "action": "$Nһ�С��������������$w�ڿ�һ����һ���������࣬�͵���$n��ͷ����",
        "force" : 150,
        "attack" :30,
        "dodge" : -15,
        "damage": 140,
        "lvl"   : 40,
        "skill_name" : "�����",
        "damage_type":  "����"
]),
([      "action": "$N̤��һ��������$n��٬һЦ������$wȴ����ͣ����һ�С�����Ϸ���"
                  "ɨ��$n��$l",
        "force" : 190,
        "dodge" : -30,
        "attack" :80,
        "damage": 130,
        "lvl"   : 50,
        "skill_name" : "����Ϸ��",
        "damage_type":  "����"
]),
([      "action": "$NԾ�ڰ�գ�һ�С����ɷ��衹������$w������ϴ�գ�����Ϸ��"
                  "���������ֵ�$n����",
        "force" : 250,
        "dodge" : -35,
        "damage": 90,
        "attack" :130,
        "lvl"   : 60,
        "skill_name" : "���ɷ���",
        "damage_type":  "����"
]),
([      "action": "$N��ǰ����������$wȦת��磬һ�С�������项������$nǰ��",
        "force" : 240,
        "dodge" : -40,
        "attack" :130,
        "damage": 105,
        "lvl"   : 75,
        "skill_name" : "�������",
        "damage_type":  "����"
])
});

int valid_enable(string usage) { return (usage == "whip") || (usage == "parry"); }

int valid_learn(object me)
{
        object weapon;

        if ((int)me->query_skill("force") < 30)
                return notify_fail("����ڹ����̫ǳ��\n");

        if ( me->query("gender") != "Ů��")
                return notify_fail("����ү��ѧ��ɷ�ޣ����ʲ���ɡ�\n");

        if ( !objectp(weapon = me->query_temp("weapon"))
        || ( string)weapon->query("skill_type") != "whip" )
                return notify_fail("���������һ�����޲������޷���\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level   = (int) me->query_skill("feifeng-whip",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        object weapon;

        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "whip")
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if ((int)me->query("qi") < 60)
                return notify_fail("��������������ɷ�޷���\n");

        if ((int)me->query("neili") < 20)
                return notify_fail("��������������ɷ�޷���\n");

        me->receive_damage("qi", 12);
        return 1;
}
string perform_action_file(string action)
{
        return __DIR__"feifeng-whip/" + action;
}
