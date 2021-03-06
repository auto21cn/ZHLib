// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// ruyi-dao.c 如意刀
// 逍遥派的空手武功厉害，刀法不是强项，故如意刀攻击力设计为一般强。

#include <ansi.h> 
inherit SKILL;

mapping *action_msg = ({
        "$N手中$w斜指，一招"HIY"「双宿双飞」"NOR"，反转$w，以刀背向$n的$l敲去",
        "一式"HIR"「随心所欲」"NOR"，$N左手持刀著著进攻，蓦地里$w急旋，缓缓逼向$n的$l",
        "$N接着使出"HIW"「心有灵犀」"NOR"，陡然间风声飒然，右手持$w，一刀自後袭到，跟著又是一刀，拦腰斩向$n",
        "$N一招"MAG"「意乱情迷」"NOR"，$w如影随形的再反手一刀，笔直砍向$n的$l",
        "$N一式"HIG"「海枯石烂」"NOR"，一个旋身，双手紧握$w，由左肩斜劈$n的$l",
        "$N挥舞$w，一招"HIC"「吹笛萧萧」"NOR"，连砍数刀，每一刀的力道和角度都不同，忽轻忽重，齐齐劈向$n",
        "$N一招"HIW+BLK"「携手天涯」"NOR"，借跃空之势，又是双手运刀，$w破空而下，挟风声劈向$n的$l，发出尖锐破空的刀啸声",
        "$N一招"HIR"「情"NOR+MAG"归"NOR+HIG"何"NOR+HIY"处"NOR+HIR"」"NOR"，暴喝声中双手不住舞起$w，每刀都高举过头，时而直劈，时而斜削",
});


int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }

int valid_learn(object me)
{
             int level; 
           level = me->query_skill("riyi-dao", 1); 
        if ((int)me->query_skill("xiaowuxiang", 1) < 25
                && (int)me->query_skill("bahuang-gong", 1) < 25
                && (int)me->query_skill("beiming-shengong", 1) < 25)
                return notify_fail("你的逍遥派内功火候不够，无法学习如意刀。\n");
                
        if ((int)me->query("max_neili") < 100)
                return notify_fail("你的内力太弱，无法学习如意刀。\n");
            if (me->query_skill("blade", 1) < level) 
                return notify_fail("你的基本刀法火候不够，无法学习如意刀。\n");
        return 1;
}

mapping query_action(object me, object weapon)
{
        return ([
                "action": action_msg[random(sizeof(action_msg))],
                "damage": 120 + random(30),
                "attack": 60 - random(10),
                "dodge" : 60 - random(10),
                "parry" : 60 - random(10),
                "damage_type" : "割伤",
        ]);
}

int practice_skill(object me)
{
        object weapon;

        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "blade")
                return notify_fail("你使用的武器不对。\n");
                
        if ((int)me->query("qi") < 60)
                return notify_fail("你的体力不够练如意刀。\n");
                
        if ((int)me->query("neili") < 60)
                return notify_fail("你的内力不够。\n");
                
        me->receive_damage("qi", 50);
        me->add("neili", -50);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"ruyi-dao/" + action;
}

