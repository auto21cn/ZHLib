// pixie-jian.c 辟邪剑法
// looo/6/21/2001/update
// modified by Venus Oct.1997
// updated by Doing Lu 4/11/2000
// updated by Haiyan@huaxia 2003.9

#include <ansi.h>
inherit SKILL;

string *dodge_msg = ({
    "突然之间，白影急幌，$n向后滑出丈余，立时又回到了原地，躲过了$N这一招。\n",
    "$n手臂回转，在$N手肘下一推，顺势闪到一旁。\n",
    "$n右手伸出，在$N手腕上迅速无比的一按，顺势跳到一旁。\n",
    "$n身形飘忽，有如鬼魅，转了几转，移步到$N的身后，躲过了$N这一招。\n",
    "$N只觉眼前一花，似乎见到$n身形一幌，但随即又见$n回到原地，却似从未离开。\n",
    "$N眼睛一花，$n已没了踪影。突然$n从身后拍了一下$N的头，轻轻跃开。\n",
    "$n嫣然一笑，诡异之极，$N竟不知如何是好，停住了攻击。\n",
});

mapping *action = ({
([  "action":"突然之间，白影急幌，$N向后滑出丈余，立时又回到了原地",
    "force" : 270,
    "attack": 180,
    "parry" : 20,
    "dodge" : 130,
    "damage": 220,
    "lvl" : 0,
    "skill_name" : "白影急幌",
    "damage_type":  "刺伤"
]),
([  "action":"$N右手伸出，在$n手腕上迅速无比的一按，$n险些击中自己小腹",
    "force" : 260,
    "attack": 180,
    "parry" : 30,
    "dodge" : 165,
    "damage": 250,
    "lvl" : 12,
    "skill_name" : "自己小腹",
    "damage_type":  "刺伤"
]),
([  "action":"蓦地里$N猱身而上，蹿到$n的身后，又跃回原地",
    "force" : 300,
    "attack": 190,
    "parry" : 35,
    "dodge" : 185,
    "damage": 280,
    "lvl" : 25,
    "skill_name" : "猱身而上",
    "damage_type":  "刺伤"
]),
([  "action":"$N突然间招法一变，$w忽伸忽缩，招式诡奇绝伦。$n惊骇之中方寸大乱",
    "force" : 330,
    "attack": 200,
    "parry" : 40,
    "dodge" : 120,
    "damage": 270,
    "lvl" : 5,
    "skill_name" : "招法一变",
    "damage_type":  "刺伤"
]),
([  "action":"$N身形飘忽，有如鬼魅，转了几转，移步到$n的左侧",
    "force" : 310,
    "attack": 210,
    "parry" : 50,
    "dodge" : 120,
    "damage": 260,
    "lvl" : 35,
    "skill_name" : "有如鬼魅",
    "damage_type":  "刺伤"
]),
([  "action":"$N一声冷笑，蓦地里疾冲上前，一瞬之间，与$n相距已不到一尺，$w随即递出",
    "force" : 330,
    "attack": 210,
    "parry" : 40,
    "dodge" : 165,
    "damage": 290,
    "lvl" : 45,
    "skill_name" : "疾冲上前",
    "damage_type":  "刺伤"
]),
([  "action":"$N喝道：“好！”，便即拔出$w，反手刺出，跟着转身离去",
    "force" : 300,
    "attack": 220,
    "parry" : 45,
    "dodge" : 180,
    "damage": 300,
    "lvl" : 55,
    "skill_name" : "反手刺出",
    "damage_type":  "刺伤"
]),
([  "action":"$n只觉眼前一花，似乎见到$N身形一幌，但随即又见$N回到原地，却似从未离开",
    "force" : 300,
    "attack": 230,
    "parry" : 40,
    "dodge" : 150,
    "damage": 280,
    "lvl" : 65,
    "skill_name" : "眼前一花",
    "damage_type":  "刺伤"
]),
([  "action":"$N向后疾退，$n紧追两步，突然间$N闪到$n面前，手中$w直指$n的$l",
    "force" : 310,
    "attack": 210,
    "parry" : 50,
    "dodge" : 170,
    "damage": 300,
    "lvl" : 75,
    "skill_name" : "向后疾退",
    "damage_type":  "刺伤"
]),
([  "action":"$N蓦地冲到$n面前，手中$w直刺$n右眼！$n慌忙招架，不想$N的$w突然转向",
    "force" : 350,
    "attack": 210,
    "parry" : 55,
    "dodge" : 144,
    "damage": 280,
    "lvl" : 85,
    "skill_name" : "直刺右眼",
    "damage_type":  "刺伤"
]),
([  "action":"$N飞身跃起，$n抬眼一望，但见得$N从天直落而下，手中$w刺向$n的$l",
    "force" : 340,
    "attack": 230,
    "parry" : 50,
    "dodge" : 180,
    "damage": 310,
    "lvl" : 94,
    "skill_name" : "飞身跃起",
    "damage_type":  "刺伤"
]),
([  "action":"$N腰枝猛摆，$n眼前仿佛突然出现了七八个$N，七八只$w一起刺向$n",
    "force" : 350,
    "attack": 210,
    "parry" : 60,
    "dodge" : 140,
    "damage": 320,
    "lvl" : 120,
    "skill_name" : "腰枝猛摆",
    "damage_type":  "刺伤"
]),
});

int can_not_hubo() {return 1;} 

int valid_enable(string usage)
{
        return usage == "sword" ||
               usage == "parry";
}

int double_attack() { return 1; }

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action) - 1; i >= 0; i--)
                if (level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("pixie-jian", 1);
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
        if (me->query("gender") == "女性")
                return notify_fail("自古以来没听说过女人可以修习葵花宝典。\n");

        if (me->query("gender") == "男性" && !me->query("tianmo_jieti"))
                return notify_fail("你觉得内息忽然大乱，几欲焚身。\n");

        return 1;
}

mixed hit_by(object ob, object me, int damage)
{
        string result;
        int shang;

        if (me->query("gender") == "无性")   return damage;

        if (!living(me) || (me->is_busy() && random(3) == 0))   return damage;

        if (damage <= 0)   return damage;

        if (random(3) == 0)
        {
              shang = damage / 5;
              result = HIR "$n" HIR "默念辟邪剑诀，忽感内息运行粘滞，" +
                       HIR "胸口犹如千斤重压，喘不过气来。\n" NOR;
              me->receive_damage("qi", shang);
              me->receive_wound("qi", shang / 2 + random(shang / 2));
              return ([ "msg" : result, "damage" : damage ]);
        } else   return damage;
}

/*
mixed valid_damage(object target, object me, int damage, object weapon)
{
        mapping result;
        string msg;
        int ap, dp;

        if ((int) me->query_skill("pixie-jian", 1) < 300)
        return;

        dp = target->query_skill("force", 1) + target->query_skill("dodge",1) / 4;
        ap = me->query_skill("dodge", 1) / 4 +
             me->query_skill("pixie-jian", 1);

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
*/

int practice_skill(object me)
{
        return notify_fail("辟邪剑法只能通过研习《辟邪剑谱》或《葵花"
                           "宝典》来学习。\n");
}

string perform_action_file(string action)
{
        return __DIR__"pixie-jian/perform/" + action;
}

int difficult_level()
{
        return 400;
}

