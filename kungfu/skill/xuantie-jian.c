inherit SKILL;

mapping *action = ({
([      "action": "$N手中的$w荡出，就如大江东去，势不可挡",
        "force" : 250,
        "attack": 170,
        "dodge" : 30,
        "damage": 150,
        "parry" : 70,
        "lvl"   : 0,
        "damage_type": "割伤"
]),
([      "action": "$N踏上一步，手中$w舞出一道剑光劈向$n的$l",
        "force" : 310,
        "attack": 180,
        "dodge" : 33,
        "parry" : 79,
        "damage": 180,
        "lvl"   : 40,
        "damage_type": "割伤"
]),
([      "action": "$N手中$w一抖，一剑刺出，攻向$n的$l，没有半点花巧",
        "force" : 330,
        "attack": 130,
        "dodge" : 41,
        "parry" : 85,
        "damage": 200,
        "lvl"   : 80,
        "damage_type": "割伤"
]),
([      "action": "$N手中$w微微颤动，忽然刺出，一道剑光射向$n的$l",
        "force" : 360,
        "attack": 155,
        "dodge" : 45,
        "parry" : 92,
        "damage": 200,
        "lvl"   : 120,
        "damage_type": "刺伤"
]),
([      "action": "$N横过$w，蓦然横扫$n，气势如宏",
        "force" : 380,
        "attack": 147,
        "dodge" : 47,
        "parry" : 99,
        "damage": 200,
        "lvl"   : 160,
        "damage_type": "割伤"
]),
([      "action": "$N手中的$w连削带刺，夹带着一阵旋风掠过$n全身",
        "force" : 400,
        "attack": 160,
        "dodge" : 50,
        "parry" : 100,
        "damage": 250,
        "lvl"   : 200,
        "damage_type": "刺伤"
])
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }

int valid_learn(object me)
{
        if ((int)me->query_skill("force") < 200)
                return notify_fail("你的内功火候不到，无法学习玄铁剑法。\n");

        if (me->query("max_neili") < 2000)
                return notify_fail("你的内力太差，无法学习玄铁剑法。\n");

        if (me->query_str() < 45)
                return notify_fail("你现在膂力太差，无法学习玄铁剑法。\n");

        if (me->query_skill("force", 1) < me->query_skill("xuantie-jian", 1))
                return notify_fail("你的内功底子还不够，无法领会更高深的玄铁剑法。\n");

        if (me->query_skill("sword", 1) < me->query_skill("xuantie-jian", 1))
                return notify_fail("你的基本剑法水平有限，无法领会更高深的玄铁剑法。\n");

        return 1;
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("xuantie-jian", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
        object weapon;

        if (!objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不对。\n");

        if ((int)me->query("qi") < 80)
                return notify_fail("你的体力不够练玄铁剑法。\n");

        if ((int)me->query("neili") < 100)
                return notify_fail("你的内力不够练玄铁剑法。\n");

        me->receive_damage("qi", 70);
        me->add("neili", -90);

        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"xuantie-jian/" + action;
}
