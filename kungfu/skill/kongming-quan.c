// kongming.c
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "$N使出「空」字诀，单拳击出，拳式若有若无，似乎毫无着力处，却又径直袭向$n",
        "force" : 100,
        "dodge" : 5,
        "parry" : 1,
        "lvl" : 0,
        "damage" : 20,
        "skill_name" : "空字诀",
        "damage_type" : "瘀伤"
]),
([      "action" : "$N使出「朦」字诀，拳招胡里胡涂，看似不成章法，但拳势却直指$n的$l",
        "force" : 120,
        "dodge" : -2,
        "parry" : 2,
        "lvl" : 0,
        "damage" : 20,
        "skill_name" : "朦字诀",
        "damage_type" : "瘀伤"
]),
([      "action" : "$N使出「洞」字诀，单拳似乎由洞中穿出，劲道内敛，招式却咄咄逼人，狠狠地击向$n",
        "force" : 140,
        "dodge" : 3,
        "parry" : -2,
        "lvl" : 6,
        "damage" : 20,
        "skill_name" : "洞字诀",
        "damage_type" : "瘀伤"
]),
([      "action" : "$N使出「松」字诀，出拳浑似无力，软绵绵地划出，轻飘飘地挥向$n的$l",
        "force" : 160,
        "dodge" : -5,
        "parry" : -1,
        "lvl" : 12,
        "damage" : 30,
        "skill_name" : "松字诀",
        "damage_type" : "瘀伤"
]),
([      "action" : "$N使出「风」字诀，单拳击出，带起一股柔风，$n刚觉轻风拂体，拳招竟已袭到了面前",
        "force" : 180,
        "dodge" : -3,
        "parry" : 2,
        "lvl" : 20,
        "damage" : 30,
        "skill_name" : "风字诀",
        "damage_type" : "瘀伤"
]),
([      "action" : "$N使出「通」字诀，拳力聚而不散，似有穿通之形，直击$n的$l",
        "force" : 200,
        "dodge" : 5,
        "parry" : -3,
        "lvl" : 28,
        "damage" : 30,
        "skill_name" : "通字诀",
        "damage_type" : "瘀伤"
]),
([      "action" : "$N使出「容」字诀，拳走空明，外包内容，似轻实重，正对着$n当胸而去",
        "force" : 220,
        "dodge" : 1,
        "parry" : 1,
        "lvl" : 35,
        "damage" : 40,
        "skill_name" : "容字诀",
        "damage_type" : "瘀伤"
]),
([      "action" : "$N使出「梦」字诀，拳势如梦，又在半梦半醒，$n一时神弛，拳风已然及体",
        "force" : 250,
        "dodge" : 4,
        "parry" : -1,
        "lvl" : 40,
        "damage" : 40,
        "skill_name" : "梦字诀",
        "damage_type" : "瘀伤"
]),
([      "action" : "$N使出「冲」字诀，单拳直击，拳式举重若轻，向$n的$l打去",
        "force" : 280,
        "dodge" : 3,
        "parry" : 2,
        "lvl" : 46,
        "damage" : 40,
        "skill_name" : "冲字诀",
        "damage_type" : "瘀伤"
]),
([      "action" : "$N使出「穷」字诀，正显潦倒之形，拳势虽然显出穷途末路，却暗含杀机，窥$n不备而猛施重拳",
        "force" : 310,
        "dodge" : -3,
        "parry" : 0,
        "lvl" : 53,
        "damage" : 70,
        "skill_name" : "穷字诀",
        "damage_type" : "瘀伤"
]),
([      "action" : "$N使出「中」字诀，单拳缓缓击出，不偏不倚，虽是指向正中，拳力却将$n的周身笼住",
        "force" : 340,
        "dodge" : -3,
        "parry" : 4,
        "lvl" : 59,
        "damage" : 80,
        "skill_name" : "中字诀",
        "damage_type" : "瘀伤"
]),
([      "action" : "$N使出「弄」字诀，拳招陡然花俏，似在作弄$n，却又暗伏后招",
        "force" : 370,
        "dodge" : 1,
        "parry" : 3,
        "lvl" : 65,
        "damage" : 100,
        "skill_name" : "弄字诀",
        "damage_type" : "瘀伤"
]),
([      "action" : "$N使出「童」字诀，出拳如稚童般毫无章法，胡乱击向$n的$l",
        "force" : 400,
        "dodge" : 3,
        "parry" : 4,
        "lvl" : 72,
        "damage" : 100,
        "skill_name" : "童字诀",
        "damage_type" : "瘀伤"
]),
([      "action" : "$N使出「庸」字诀，单拳击出时是最简单的招式，平平无奇，可是却阻住了$n的退路",
        "force" : 440,
        "dodge" : 3,
        "parry" : -2,
        "lvl" : 78,
        "damage" : 110,
        "skill_name" : "庸字诀",
        "damage_type" : "瘀伤"
]),
([      "action" : "$N使出「弓」字诀，身体弯曲如弓，拳出似箭，迅捷地袭向$n",
        "force" : 480,
        "dodge" : 5,
        "parry" : 2,
        "lvl" : 85,
        "damage" : 150,
        "skill_name" : "弓字诀",
        "damage_type" : "瘀伤"
]),
([      "action" : "$N使出「虫」字诀，身子柔软如虫，拳招也随着蠕动，$n竟无法判断这一拳的来势",
        "force" : 530,
        "dodge" : 8,
        "parry" : -1,
        "lvl" : 95,
        "damage" : 180,
        "skill_name" : "虫字诀",
        "damage_type" : "瘀伤"
]),
});

int valid_enable(string usage) { return usage == "cuff" ||  usage == "parry"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("练空明拳必须空手。\n");

	if ((int)me->query("max_neili") < 1000)
                return notify_fail("你的内力太弱，无法练空明拳。\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的内功火候不够，无法练空明拳。\n");

        if ((int)me->query_skill("cuff", 1) < 120)
                return notify_fail("你的基本拳法火候不够，无法练空明拳。\n");

        if ((int)me->query_skill("chunyang-quan", 1) < 120)
                return notify_fail("你的纯阳拳基本功不够扎实，无法练空明拳。\n");

        if ((int)me->query_skill("cuff", 1) < (int)me->query_skill("kongming-quan", 1))
                return notify_fail("你的基本拳法水平有限，无法领会更高深的空明拳。\n");

	return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action)-1; i >= 0; i--)
                if (level >= action[i-1]["lvl"])
                        return action[i-1]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int)me->query_skill("kongming-quan", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	if ((int)me->query("qi") < 60)
		return notify_fail("你的体力太低了。\n");

	if ((int)me->query("neili") < 70)
                return notify_fail("你的内力不够了。\n");

	me->receive_damage("qi", 50);
	me->add("neili", -60);
	return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        if (damage_bonus < 250) return 0;

	if (!me->query_temp("kongming")) return 0;

        if (random(10) > 5)
        {
                victim->receive_wound("qi", (damage_bonus - 250) / 5, me);
                return HIR + me->name() + HIR + "气势如虹，右手虚握空拳，凝重一击，" + victim->name() + HIR + "一声闷哼，吐出一口鲜血。\n" NOR;
        }
	return 0;
}


string perform_action_file(string action)
{
      return __DIR__"kongming-quan/" + action;
}
