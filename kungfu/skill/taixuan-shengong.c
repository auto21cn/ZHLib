// taixuan-shengong.c 太玄神功
// By haiyan

#include <ansi.h>
inherit FORCE;

string *dodge_msg = ({
    "$n左手拍出，劲风到处，把$N的招数震到一边。\n",
    "$n手臂回转，抓住$N手肘一推，将$N远远掷开。\n",
    "$n两腿轻蹬，激跃而出，竟已落在十数丈外。\n",
    "$N只觉眼前一花，只见到$n身形一幌，自己的招数居然莫名其妙就落空了。\n",
});

mapping *action = ({
([  "action":"$N左手一推，一股劲气澎湃汹涌而来，逼得$n踉踉后退",
    "force" : 220,
    "attack": 110,
    "parry" : 80,
    "dodge" : 75,
    "damage": 90,
    "lvl" : 0,
    "damage_type":  "瘀伤"
]),
([  "action":"$N身形转个不停，突然一招「一点灵犀」使出，手中$w划出一道银弧，径刺$n$l。",
    "force" : 230,
    "attack": 130,
    "parry" : 102,
    "dodge" : 95,
    "damage": 100,
    "lvl" : 30,
    "damage_type":  "刺伤"
]),
([  "action":"$N右手伸出，在$n臂膀上迅速无比的一按，$n一跤跌了出去",
    "force" : 250,
    "attack": 150,
    "parry" : 120,
    "dodge" : 115,
    "damage": 105,
    "lvl" : 50,
    "damage_type":  "瘀伤"
]),
([  "action":"$N手中$w大开大阖，每一剑向$n劈去，都有似开山大斧一般，好一招势道雄的「鸿飞天外」。",
    "force" : 260,
    "attack": 180,
    "parry" : 130,
    "dodge" : 105,
    "damage": 110,
    "lvl" : 80,
    "damage_type":  "刺伤"
]),
([  "action":"$N大喝一声，张口一股内气向$n脸上喷去",
    "force" : 280,
    "attack": 190,
    "parry" : 135,
    "dodge" : 120,
    "damage": 120,
    "lvl" : 100,
    "damage_type":  "瘀伤"
]),
([  "action":"$N轻轻一跃，使了个「乘风归去」，却在转身之际对准$n$l斜斜挥出一剑。",
    "force" : 290,
    "attack": 210,
    "parry" : 155,
    "dodge" : 115,
    "damage": 130,
    "lvl" : 130,
    "damage_type":  "刺伤"
]),
([  "action":"$N猱身而上，双掌猛地拍向$n",
    "force" : 300,
    "attack": 220,
    "parry" : 140,
    "dodge" : 120,
    "damage": 150,
    "lvl" : 150,
    "damage_type":  "瘀伤"
]),
([  "action":"只见$N单足点地，使出一招「鹗立云端」，手中$w疾进，幻出点点寒星，直刺$n的$l。",
    "force" : 330,
    "attack": 260,
    "parry" : 140,
    "dodge" : 120,
    "damage": 180,
    "lvl" : 180,
    "damage_type":  "刺伤"
]),
([  "action":"$N身体微侧，突然飞起一脚，踢向$n下三路。脚到中途，猛地一抬，踢向$n面门",
    "force" : 350,
    "attack": 220,
    "parry" : 150,
    "dodge" : 120,
    "damage": 210,
    "lvl" : 200,
    "damage_type":  "瘀伤"
]),
([  "action":"只见$N挽出十数朵剑花，化作十数道五彩剑虹将$n罩在其中。",
    "force" : 360,
    "attack": 240,
    "parry" : 150,
    "dodge" : 110,
    "damage": 230,
    "lvl" : 230,
    "damage_type":  "刺伤"
]),
([  "action":"$N纵身一跃，手中$w一招「金光泻地」对准$n的$l斜斜刺出一剑。",
    "force" : 350,
    "attack": 220,
    "parry" : 150,
    "dodge" : 120,
    "damage": 260,
    "lvl" : 250,
    "damage_type":  "刺伤"
]),
([  "action":"$N突然间左手一捺，封住$n退路，右手掌力汹涌而出",
    "force" : 380,
    "attack": 220,
    "parry" : 160,
    "dodge" : 125,
    "damage": 280,
    "lvl" : 280,
    "damage_type":  "瘀伤"
]),
([  "action":"$N蓦地里一声清啸，手中$w冲天而起，直指$n的$l。",
    "force" : 400,
    "attack": 250,
    "parry" : 140,
    "dodge" : 165,
    "damage": 320,
    "lvl" : 300,
    "damage_type":  "刺伤"
]),
});

int valid_enable(string usage)
{
     object me;
     string verb;

     me = this_player();
     if (!me || !userp(me)) return usage == "force";

     verb = me->query("taixuan");

     if (verb == "force")    return usage == "force";
     if (verb == "sword")    return usage == "sword" || usage == "parry";
     if (verb == "dodge")    return usage == "dodge";
     if (verb == "unarmed")  return usage == "unarmed" || usage == "parry";
}

int valid_force(string force)  { return 1; }
int can_not_hubo() {return 1;}

int double_attack()  { return 1; }

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("taixuan-shengong", 1);
        return lvl * lvl * 15 * 22 / 100 / 200;
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int)me->query_skill("taixuan-shengong", 1);
        for (i = sizeof(action); i > 0; i--)
             if (level > action[i-1]["lvl"])
                  return action[NewRandom(i, 20, level/5)];
}

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int valid_learn(object me)
{
        int level, mar;
        string verb;

        mar = (int)me->query_skill("martial-cognize", 1);

        if ((int)me->query_skill("literate", 1) > 200)
             return notify_fail("你饱读诗书，无法领悟古朴的太玄神功。\n");

        if ( ! ultrap(me) )
             return notify_fail("你对武学的研究太过肤浅，"
                                "一时之间难以领会太玄神功。\n");

        if (mar < 200)
             return notify_fail("你觉得太玄神功过于深奥，以"
                                "自己的武学修养全然无法明白。\n");

        level = me->query_skill("taixuan-shengong", 1);

        if ((string)me->query("gender") == "无性" && level > 49)
             return notify_fail("你无根无性，阴阳不调，难以领会高深的太玄神功。\n");

        if (mar < 500 && mar < level)
             return notify_fail("你觉得自己的武学修养有限，难以领会更高深的太玄神功。\n");

        verb = me->query("taixuan");

        switch(verb)
        {
             case "force":
                  if ((int)me->query_skill("force", 1) < level)
                         return notify_fail("你对基本内功的理解还不够，"
                                            "无法继续领会更高深的太玄神功。\n");
                  break;
             case "sword":
                  if ((int)me->query_skill("sword", 1) < level)
                         return notify_fail("你对基本剑法的理解还不够，"
                                            "无法继续领会更高深的太玄神功。\n");
                  break;
             case "dodge":
                  if ((int)me->query_skill("dodge", 1) < level)
                         return notify_fail("你对基本轻功的理解还不够，"
                                            "无法继续领会更高深的太玄神功。\n");
                  break;
             case "unarmed":
                  if ((int)me->query_skill("unarmed", 1) < level)
                         return notify_fail("你对基本拳脚的理解还不够，"
                                            "无法继续领会更高深的太玄神功。\n");
                  break;
        }
        return 1;
}

mixed valid_damage(object target, object me, int damage, object weapon)
{
        mapping result;
        string msg;
        int ap, dp;

        if ((int)me->query_skill("taixuan-shengong", 1) < 100)
             return;

        if ((string)me->query("taixuan") != "dodge")   return;

        if (!living(me) || (me->is_busy() && random(3) == 0)) return;

        dp = target->query_skill("force", 1) + target->query_skill("dodge", 1);
        ap = me->query_skill("dodge", 1) + me->query_skill("taixuan-shengong", 1);

        if (ap / 3 + random(ap) > dp)
        {
                me->add("neili", -30);
                msg = dodge_msg[random(sizeof(dodge_msg))];
                msg = replace_string(msg, "$N", "$N" HIW);
                msg = replace_string(msg, "$n", "$n" HIW);
                msg = HIW + msg + NOR;
                result = ([ "damage": -damage,
                            "msg"   : msg ]);
                return result;
        }
}

int practice_skill(object me)
{
        return notify_fail("太玄神功博大精深，无法简单的通过练习进步。\n");
}

string perform_action_file(string action)
{
        object me = this_player();

        if ((string)me->query("taixuan") == "sword")
             return __DIR__"taixuan-shengong/perform/sword/" + action;

        if ((string)me->query("taixuan") == "unarmed")
             return __DIR__"taixuan-shengong/perform/unarmed/" + action;
}

string exert_function_file(string action)
{
        object me = this_player();

        if ((string)me->query("taixuan") == "force")
             return __DIR__"taixuan-shengong/exert/" + action;
}

