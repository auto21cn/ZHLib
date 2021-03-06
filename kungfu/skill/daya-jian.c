// daya-jian.c
// 华夏玩家golden的自创武功：大雅剑法
// Modified by smallfish@huaxia Sep.1998
#include <ansi.h>

inherit SKILL;

string is_private_skill() {return "golden";}
int can_not_hubo() {return 1;}

mapping *action = ({
([      "skill_name":    "盘庚式",
        "action":  "$N手中$w舞动出一片网状，使出大雅古剑法第一式『盘庚式』将$n周围尽皆罩住",
        "dodge" : 80,
        "damage": 180,
        "force" : 330,
        "attack": 130,
        "parry" : 80,
        "lvl"   : 0,
        "damage_type":  "刺伤"
]),
([      "skill_name":    "毕命式",
        "action":  "$N手中$w挥动一股霸道的剑气，正是大雅古剑法第二式『毕命式』，对着$n左右斜劈，凛然有风",
        "dodge" : 90,
        "damage": 190,
        "force" : 340,
        "attack": 135,
        "parry" : 85,
        "lvl"   : 120,
        "damage_type":  "刺伤"
]),
([      "skill_name":    "罔命式",
        "action":  "$N手中$w闪出点点剑光，联成一线，正是大雅古剑法第三式『罔命式』，$w带动光线，在$n面前挥舞",
        "dodge" : 95,
        "damage": 200,
        "force" : 350,
        "attack": 140,
        "parry" : 90,
        "lvl"   : 140,
        "damage_type":  "刺伤"
]),
([      "skill_name":    "大畜式",
        "action":  "$N舞动$w，正是大雅古剑法第四式『大畜式』，剑光霍霍之中，从一个意想不到的角度突然挑出一剑，向$n的$l直刺",
        "dodge" : 95,
        "damage": 200,
        "force" : 350,
        "attack": 140,
        "parry" : 90,
        "lvl"   : 140,
        "damage_type":  "刺伤"
]),
([      "skill_name":    "瞽蒙式",
        "action":  "$N手中$w发出龙吟之声，阴阳相和，高声琨，正声缓，正是大雅古剑法第五式『瞽蒙式』，剑锋直向$n$l刺过去",
        "dodge" : 105,
        "damage": 210,
        "force" : 360,
        "attack": 145,
        "parry" : 95,
        "lvl"   : 160,
        "damage_type":  "刺伤"
]),
([      "skill_name":    "述而式",
        "action":  "$N身体在原地游走，脚步散而不乱，正是大雅古剑法第六式『述而式』，手中$w摆动，不时向$n刺出一剑",
        "dodge" : 110,
        "damage": 220,
        "force" : 370,
        "attack": 150,
        "parry" : 100,
        "lvl"   : 180,
        "damage_type":  "刺伤"
]),
([      "skill_name":    "至诚式",
        "action":  "$N身体十分稳重，正是大雅古剑法第七式『至诚式』，手中$w若有若无，缓缓击出一剑，向$n的$l搭了过去",
        "dodge" : 115,
        "damage": 230,
        "force" : 380,
        "attack": 155,
        "parry" : 105,
        "lvl"   : 200,
        "damage_type":  "刺伤"
]),
([      "skill_name":    "止戢式",
        "action":  "$N使出的正是大雅古剑法第八式『止戢式』，手中$w剑光柔和，隐隐有风雷之声，向$n扑面涌去，令其顿生退避之意",
        "dodge" : 115,
        "damage": 230,
        "force" : 380,
        "attack": 155,
        "parry" : 105,
        "lvl"   : 200,
        "damage_type":  "刺伤"
]),
});

int valid_learn(object me)
{
    object ob;
    if( (int)me->query("max_neili") < 1000 )
        return notify_fail("你的内力不够，没有办法练大雅剑法。\n");

    if( (int)me->query_skill("martial-cognize",1) < 300 )
        return notify_fail("你的武学修养不够，没有办法练大雅剑法。\n");

    if( !(ob = me->query_temp("weapon"))
    ||      (string)ob->query("skill_type") != "sword" )
        return notify_fail("你必须先找一把剑才能练剑法。\n");

    return 1;
}

int valid_enable(string usage)
{
    return usage=="sword" || usage=="parry";
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
    level   = (int) me->query_skill("daya-jian",1);
    for(i = sizeof(action); i > 0; i--)
        if(level > action[i-1]["lvl"])
            return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
    if ((int)me->query("qi") < 60)
        return notify_fail("你的体力不足以练习大雅剑法。\n");

    if ((int)me->query("neili") < 60 )
        return notify_fail("你的内力不够，没有办法练习大雅剑法。\n");

    me->receive_damage("qi", 50);
    me->add("neili", -50);

    return 1;
}

string perform_action_file(string action)
{
        return __DIR__"daya-jian/" + action;
}
