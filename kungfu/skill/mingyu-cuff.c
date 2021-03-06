// mingyu-cuff.c
// 华夏玩家blacksir的自创武功：明玉拳
// Modified by smallfish@huaxia Sep.1998
#include <ansi.h>

inherit SKILL;

string is_private_skill() {return "blacksir";}
int can_not_hubo() {return 1;}

mapping *action = ({
([      "skill_name":    "冲天炮",
        "action":  "只见$N身形一矮，大喝声中一个「冲天炮」对准$n的鼻子呼！地砸了过去",
        "dodge" : 80,
        "damage": 190,
        "force" : 340,
        "attack": 130,
        "parry" : 80,
        "lvl"   : 0,
        "damage_type":  "瘀伤"
]),
([      "skill_name":    "拔草寻蛇",
        "action":  "$N左手一分，右拳运气，一招「拔草寻蛇」便往$n的$l招呼过去",
        "dodge" : 80,
        "damage": 190,
        "force" : 340,
        "attack": 130,
        "parry" : 80,
        "lvl"   : 0,
        "damage_type":  "瘀伤"
]),
([      "skill_name":    "叶底偷桃",
        "action":  "$N右拳在$n面门一晃，左掌使了个「叶底偷桃」往$n的$l狠命一抓",
        "dodge" : 90,
        "damage": 200,
        "force" : 350,
        "attack": 135,
        "parry" : 85,
        "lvl"   : 120,
        "damage_type":  "瘀伤"
]),
([      "skill_name":    "黑虎掏心",
        "action":  "$N步履一沉，左拳拉开，右拳带风，一招「黑虎掏心」势不可挡地击向$n$l",
        "dodge" : 95,
        "damage": 210,
        "force" : 360,
        "attack": 140,
        "parry" : 90,
        "lvl"   : 140,
        "damage_type":  "瘀伤"
]),
([      "skill_name":    "双风贯耳",
        "action":  "只见$N拉开架式，一招「双风贯耳」使得虎虎有风。底下却飞起一脚踢向$n$l",
        "dodge" : 105,
        "damage": 220,
        "force" : 370,
        "attack": 145,
        "parry" : 95,
        "lvl"   : 160,
        "damage_type":  "瘀伤"
]),
([      "skill_name":    "龙虎相交",
        "action":  "$N打得兴起，大喝一声：看我这招「龙虎相交」！\n左手往$n身后一抄，右拳便往$n面门砸了过去",
        "dodge" : 105,
        "damage": 220,
        "force" : 370,
        "attack": 145,
        "parry" : 95,
        "lvl"   : 160,
        "damage_type":  "瘀伤"
]),
([      "skill_name":    "如封似闭",
        "action":  "$N拉开后弓步，双掌使了个「如封似闭」往$n的$l一推",
        "dodge" : 110,
        "damage": 230,
        "force" : 380,
        "attack": 150,
        "parry" : 100,
        "lvl"   : 180,
        "damage_type":  "瘀伤"
]),
([      "skill_name":    "阳关三叠",
        "action":  "只见$N运足气力，一连三拳击向$n$l，力道一拳高过一拳！\n这一招的名字还相当高雅，叫作「阳关三叠」",
        "dodge" : 115,
        "damage": 240,
        "force" : 390,
        "attack": 155,
        "parry" : 105,
        "lvl"   : 200,
        "damage_type":  "瘀伤"
]),
([      "skill_name":    "老树盘根",
        "action":  "$N往后一纵，就势使了个「老树盘根」，右腿扫向$n的$l",
        "dodge" : 115,
        "damage": 260,
        "force" : 410,
        "attack": 155,
        "parry" : 105,
        "lvl"   : 200,
        "damage_type":  "瘀伤"
]),
([      "skill_name":    "独劈华山",
        "action":  "$N一个转身，左掌护胸，右掌反手使了个「独劈华山」往$n当头一劈",
        "dodge" : 115,
        "damage": 300,
        "force" : 450,
        "attack": 155,
        "parry" : 105,
        "lvl"   : 200,
        "damage_type":  "瘀伤"
]),
([      "skill_name":    "无名",
        "action":  "$N飞身跃起，半空中一脚踢向$n面门，却是个虚招。\n说时迟那时快，只见$N一个倒翻，双掌已到了$n的$l",
        "dodge" : 115,
        "damage": 300,
        "force" : 450,
        "attack": 155,
        "parry" : 105,
        "lvl"   : 200,
        "damage_type":  "瘀伤"
]),
});

int valid_learn(object me)
{
    object ob;
    if( (int)me->query("max_neili") < 1000 )
        return notify_fail("你的内力不够，没有办法练明玉拳。\n");

    if( (int)me->query_skill("martial-cognize",1) < 300 )
        return notify_fail("你的武学修养不够，没有办法练明玉拳。\n");

    if( (ob = me->query_temp("weapon")) || 
        (ob = me->query_temp("handing")) )
        return notify_fail("你只有空着双手才能修炼掌法。\n");

    return 1;
}

int valid_enable(string usage)
{
    return usage=="cuff" || usage=="parry";
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
    level   = (int) me->query_skill("mingyu-cuff",1);
    for(i = sizeof(action); i > 0; i--)
        if(level > action[i-1]["lvl"])
            return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
    if ((int)me->query("qi") < 60)
        return notify_fail("你的体力不足以练习明玉拳。\n");

    if ((int)me->query("neili") < 60 )
        return notify_fail("你的内力不够，没有办法练习明玉拳。\n");

    me->receive_damage("qi", 50);
    me->add("neili", -50);

    return 1;
}

string perform_action_file(string action)
{
        return __DIR__"mingyu-cuff/" + action;
}
