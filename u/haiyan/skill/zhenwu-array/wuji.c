//真武剑阵 天地无极 wuji.c

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int extra,i;
        string *style = ({ 
HIM "$N手持$w，前进中一阵急骤，手中$w猛然刺向$n！"NOR,
HIM "$N着地一滚，手中$w上挑，已刺向$n小腹！"NOR, 
HIM "$N反手握住$w，化出一道白弧，剑尖直指$n眉心！"NOR,
HIM "$N向前一纵，略退半步，突然一个急进，手中$w向$n猛扑过去！"NOR,
HIM "$N与$w合而为一，飞身而起，挺身刺向$n的两处要害！"NOR, 
HIM "$N左手捻一个剑诀，手中$w忽而向下，刺向$n下盘！"NOR, 
HIM "$N纵身一跃，手中$w叮叮作响，已向$n连刺三剑！"NOR, 
HIM "$N手中$w疾挥，划出道道剑光，身形一转，迅速刺向$n！"NOR
});
        object weapon,*obs;
        if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("「天地无极」只能对战斗中的对手使用。\n");

        if(!pointerp(obs=me->query_team()) || !me->is_team_leader())
                return notify_fail("只有队伍领袖才可以发动此式！\n");

        if(me->query_skill_mapped("array") != "zhenwu-array") 
                return notify_fail("你还没有准备好真武剑阵！\n");

        if(me->query_skill("zhenwu-array",1) < sizeof(obs)*20 ) 
                return notify_fail("你的真武剑阵阵法修为不够！\n");

        if(sizeof(obs) > 8 )
                return notify_fail("剑阵队伍最多只能由八个人组成！\n");

        for( i = 0; i < sizeof(obs); i++ ) 
        { 
           if(!obs[i]) 
                return notify_fail("你的队伍中有人离开，需要重新组合队伍。\n");

           if(environment(obs[i]) != environment(me)) 
                return notify_fail("你的队伍成员不全在你身边。\n");

           if(obs[i]->query_skill("zhenwu-array",1) < 80 ) 
                return notify_fail("你队伍中有人的真武剑阵阵法还未入门。\n");

           if (! objectp(weapon = obs[i]->query_temp("weapon")) || 
                (string)weapon->query("skill_type") != "sword") 
                return notify_fail("你的队伍中有人没有装备剑。\n"); 

           if(obs[i]->query_skill("sword",1) < 120 ) 
                return notify_fail("你的队伍中有人的基本剑法造诣太低。\n");

           if(obs[i]->query_skill_mapped("array") != "zhenwu-array") 
                return notify_fail("你的队伍中有人未准备好真武剑阵阵法！\n");
        } 

        message_vision(HIG "只听$N一声低啸，手中" + weapon->name() +
                       HIG "一荡，与众人排成真武剑阵之「天地无极」式，挺剑向$n" 
                       HIG "刺去。\n"NOR,me,target);

        for (i = 0; i < sizeof(obs); i++ ) 
        {
           weapon=obs[i]->query_temp("weapon");
           msg = style[i];
           extra = obs[i]->query_skill("sword", 1) / 10; 
           extra *= (i+1); 
           obs[i]->add_temp("apply/attack", extra);
           obs[i]->add_temp("apply/damage", extra);
           COMBAT_D->do_attack(obs[i],target, weapon, 0,msg);
           obs[i]->kill_ob(target); 
           obs[i]->add_temp("apply/attack", -extra);
           obs[i]->add_temp("apply/damage", -extra);
           obs[i]->start_busy(3);
        }
        return 1;
}

