/* combatd.c for 4444无锡谁与争锋组改写
主要修改提要：
一、对攻防值计算加入浮点运算，支持更高经验与skill
二、killreward()函数交由专门的文件去执行
三、do_attack()进行了整理。
*/

#pragma optimize all
#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>

inherit F_DBASE;

string *guard_msg = ({
        CYN "$N注视著$n的行动，企图寻找机会出手。\n" NOR,
        CYN "$N正盯著$n的一举一动，随时准备发动攻势。\n" NOR,
        CYN "$N缓缓地移动脚步，想要找出$n的破绽。\n" NOR,
        CYN "$N目不转睛地盯著$n的动作，寻找进攻的最佳时机。\n" NOR,
        CYN "$N慢慢地移动著脚步，伺机出手。\n" NOR,
});

string *catch_hunt_msg = ({
        HIW "$N和$n仇人相见分外眼红，立刻打了起来！\n" NOR,
        HIW "$N一眼瞥见$n，「哼」的一声冲了过来！\n" NOR,
        HIW "$N对著$n大喝：「可恶，又是你！」\n" NOR,
        HIW "$N一见到$n，愣了一愣，大叫：「我宰了你！」\n" NOR,
        HIW "$N喝道：「$n，我们的帐还没算完，看招！」\n" NOR,
});

string *winner_msg = ({
        CYN "\n$N哈哈大笑，愉快地说道：承让了！\n\n" NOR,
        CYN "\n$N双手一拱，笑著说道：知道我的厉害了吧！\n\n" NOR,
        CYN "\n$N胜了这招，向后跃开三尺，叹道：真是拔剑四顾心茫然！\n\n" NOR,
        CYN "\n$n向后退了几步，说道：这场比试算我输了，下回看我怎么收拾你！\n\n" NOR,
        CYN "\n$n向后一纵，恨恨地说道：君子报仇，十年不晚！\n\n" NOR,
        CYN "\n$n向后退了几步，说道：今天算我输了，阁下武艺不凡，佩服，佩服！\n\n" NOR,
});

void create()
{
    seteuid(getuid());
    set("name", "战斗精灵");
    set("id", "combatd");
    set("chat_amount",1000000000);
}

string damage_msg(int damage, string type)
{
    string str;
    if( damage == 0 ) return "结果没有造成任何伤害。\n";
    switch( type )
    {
        case "擦伤":
        case "割伤":
            if( damage < 10 ) return "结果只是轻轻地划破$p的皮肉。\n";
            else if( damage < 20 ) return "结果在$p$l划出一道细长的血痕。\n";
            else if( damage < 40 ) return "结果「嗤」地一声划出一道伤口！\n";
            else if( damage < 80 ) return "结果「嗤」地一声划出一道血淋淋的伤口！\n";
            else if( damage < 160 ) return "结果「嗤」地一声划出一道又长又深的伤口，溅得$N满脸鲜血！\n";
            else return "结果只听见$n一声惨嚎，$w已在$p$l划出一道深及见骨的可怕伤口！！\n";
            break;
        case "刺伤":
            if( damage < 10 ) return "结果只是轻轻地刺破$p的皮肉。\n";
            else if( damage < 20 ) return "结果在$p$l刺出一个创口。\n";
            else if( damage < 40 ) return "结果「噗」地一声刺入了$n$l寸许！\n";
            else if( damage < 80 ) return "结果「噗」地一声刺进$n的$l，使$p不由自主地退了几步！\n";
            else if( damage < 160 ) return "结果「噗嗤」地一声，$w已在$p$l刺出一个血肉模糊的血窟窿！\n";
            else return "结果只听见$n一声惨嚎，$w已在$p的$l对穿而出，鲜血溅得满地！！\n";
             break;
        case "瘀伤":
            if( damage < 10 ) return "结果只是轻轻地碰到，比拍苍蝇稍微重了点。\n";
            else if( damage < 20 ) return "结果在$p的$l造成一处瘀青。\n";
        else if( damage < 40 ) return "结果一击命中，$n的$l登时肿了一块老高！\n";
            else if( damage < 80 ) return "结果一击命中，$n闷哼了一声显然吃了不小的亏！\n";
         else if( damage < 120 ) return "结果「砰」地一声，$n退了两步！\n";
         else if( damage < 160 ) return "结果这一下「砰」地一声打得$n连退了好几步，差一点摔倒！\n";
         else if( damage < 240 ) return "结果重重地击中，$n「哇」地一声吐出一口鲜血！\n";
         else return "结果只听见「砰」地一声巨响，$n像一捆稻草般飞了出去！！\n";
         break;
        case "内伤":
         if( damage < 10 ) return "结果只是把$n打得退了半步，毫发无损。\n";
         else if( damage < 20 ) return "结果$n痛哼一声，在$p的$l造成一处瘀伤。\n";
         else if( damage < 40 ) return "结果一击命中，把$n打得痛得弯下腰去！\n";
         else if( damage < 80 ) return "结果$n闷哼了一声，脸上一阵青一阵白，显然受了点内伤！\n";
         else if( damage < 120 ) return "结果$n脸色一下变得惨白，昏昏沉沉接连退了好几步！\n";
         else if( damage < 160 ) return "结果重重地击中，$n「哇」地一声吐出一口鲜血！\n";
         else if( damage < 240 ) return "结果「轰」地一声，$n全身气血倒流，口中鲜血狂喷而出！\n";
         else return "结果只听见几声喀喀轻响，$n一声惨叫，像滩软泥般塌了下去！！\n";
         break;
      default:
         if( !type ) type = "伤害";
         if( damage < 10 ) str =  "结果只是勉强造成一处轻微";
         else if( damage < 20 ) str = "结果造成轻微的";
         else if( damage < 30 ) str = "结果造成一处";
         else if( damage < 50 ) str = "结果造成一处严重";
         else if( damage < 80 ) str = "结果造成颇为严重的";
         else if( damage < 120 ) str = "结果造成相当严重的";
         else if( damage < 170 ) str = "结果造成十分严重的";
         else if( damage < 230 ) str = "结果造成极其严重的";
         else str =  "结果造成非常可怕的严重";
            return str + type + "！\n";
    }
}

string eff_status_msg(int ratio)
{
        if( ratio==100 ) return HIG "看起来气血充盈，并没有受伤。" NOR;
        if( ratio > 95 ) return HIG "似乎受了点轻伤，不过光从外表看不大出来。" NOR;
        if( ratio > 90 ) return HIY "看起来可能受了点轻伤。" NOR;
        if( ratio > 80 ) return HIY "受了几处伤，不过似乎并不碍事。" NOR;
        if( ratio > 60 ) return HIY "受伤不轻，看起来状况并不太好。" NOR;
        if( ratio > 40 ) return HIR "气息粗重，动作开始散乱，看来所受的伤著实不轻。" NOR;
        if( ratio > 30 ) return HIR "已经伤痕累累，正在勉力支撑著不倒下去。" NOR;
        if( ratio > 20 ) return HIR "受了相当重的伤，只怕会有生命危险。" NOR;
        if( ratio > 10 ) return RED "伤重之下已经难以支撑，眼看就要倒在地上。" NOR;
        if( ratio > 5  ) return RED "受伤过重，已经奄奄一息，命在旦夕了。" NOR;
            return RED "受伤过重，已经有如风中残烛，随时都可能断气。" NOR;
}

string status_msg(int ratio)
{
        if( ratio==100 ) return HIG "看起来充满活力，一点也不累。" NOR;
        if( ratio > 95 ) return HIG "似乎有些疲惫，但是仍然十分有活力。" NOR;
        if( ratio > 90 ) return HIY "看起来可能有些累了。" NOR;
        if( ratio > 80 ) return HIY "动作似乎开始有点不太灵光，但是仍然有条不紊。" NOR;
        if( ratio > 60 ) return HIY "气喘嘘嘘，看起来状况并不太好。" NOR;
        if( ratio > 40 ) return HIR "似乎十分疲惫，看来需要好好休息了。" NOR;
        if( ratio > 30 ) return HIR "已经一副头重脚轻的模样，正在勉力支撑著不倒下去。" NOR;
        if( ratio > 20 ) return HIR "看起来已经力不从心了。" NOR;
        if( ratio > 10 ) return RED "摇头晃脑、歪歪斜斜地站都站不稳，眼看就要倒在地上。" NOR;
            return RED "已经陷入半昏迷状态，随时都可能摔倒晕去。" NOR;
}

varargs void report_status(object ob, int effective)
{
    if( effective )
        message_vision("($N"+eff_status_msg((int)ob->query("eff_qi")*100/(int)ob->query("max_qi"))+")\n",ob);
      message_vision("($N"+status_msg((int)ob->query("qi")*100/(int)ob->query("max_qi"))+")\n",ob);
}

//该函数提供每招攻者攻击值ap,防者的轻功防御值dp.身法躲闪值pp,包括每招对双方的修正
varargs int skill_power(object ob, string skill, int usage)
{
   int status, level, power,mapped_dodge;
   if( !living(ob) ) return 0;
   level = ob->query_skill(skill);
   switch(usage)
   {
        case SKILL_USAGE_ATTACK:
        level += ob->query_temp("apply/attack");
      break;
    case SKILL_USAGE_DEFENSE:
        level += ob->query_temp("apply/defense");
      if(level < 0) level = 0;
            break;
    }
   if( !level ) return (int)ob->query("combat_exp") / 2;
//下面是从后面的do_attack传回的取值参数
   if(skill=="parry")
         power = (level / 3.0)*level/1000.0*level*(100 + ob->query_temp("down/parry"));
   else if(skill=="dodge")
   {
      if(!ob->query_skill_mapped("dodge"))
         mapped_dodge=0;
      else if(!intp(mapped_dodge=SKILL_D(ob->query_skill_mapped("dodge"))->query_dodge_level()))
         mapped_dodge=0;
      power = (level / 3.0)*level/1000.0*level*(100 + ob->query_temp("down/dodge")+mapped_dodge);
   }
   else
      power = (level / 3.0)*level/10.0*level;

   if (usage == SKILL_USAGE_ATTACK)
      return to_int((power + ob->query("combat_exp")) / 30.0 * (ob->query_str() + ob->query_temp("str")));
   else
      return to_int((power + ob->query("combat_exp")) / 30.0 * (ob->query_dex() + ob->query_temp("dex")));
}

varargs int do_attack(object me, object victim, object weapon, int attack_type)
{
   mapping my, your, prepare, action;
   string limb, *limbs, result;
   string attack_skill, force_skill, martial_skill, dodge_skill, parry_skill;
   mixed foo;
   int ap, dp, pp;
   int damage, damage_bonus, defense_factor;
   int cost;
   int wounded = 0;

   my = me->query_entire_dbase();//取进攻方的所有参数待用
   your = victim->query_entire_dbase();

   prepare = me->query_skill_prepare();//组合拳术
   if (!prepare) prepare = ([]);
   if( objectp(weapon) )
      attack_skill = weapon->query("skill_type");
   else if ( sizeof(prepare) == 0) attack_skill = "unarmed";
   else if ( sizeof(prepare) == 1) attack_skill = (keys(prepare))[0];
   else if ( sizeof(prepare) == 2) attack_skill = (keys(prepare))[me->query_temp("action_flag")];

   me->reset_action();
   action = me->query("actions");
   if( !mapp(action) )
   {
      me->reset_action();
     action = me->query("actions");
      if( !mapp(action) )
      {
         CHANNEL_D->do_channel( this_object(), "sys",sprintf("%s(%s): bad action = %O",
                                me->name(1), me->query("id"), me->query("actions", 1)));
         return 0;
      }
   }

   if (me->query_temp("action_flag") == 0)
    result = "\n" + action["action"] + "！\n";
   else result = "\n" + "紧跟着"+action["action"] + "!\n";//组合拳术连出两招信息

   limbs = victim->query("limbs");     //身体共16个部位
   limb = limbs[random(sizeof(limbs))];//随机取1个

   ap = skill_power(me, attack_skill, SKILL_USAGE_ATTACK);
   if( ap < 1) ap = 1;
   if (intp(action["dodge"]))
      victim->set_temp("down/dodge", action["dodge"]);//对被攻者身法进行修正
   else victim->set_temp("down/dodge",0);

   dp = skill_power(victim, "dodge", SKILL_USAGE_DEFENSE);
   if( dp < 1 ) dp = 1;
   if( victim->is_busy() ) dp = dp - dp/5;
// 用 AP/(AP+DP) 的值来判断是否打得中对方
// 由于AP和DP都大于0,所以我们既会打中别人,也有可能被别人打中
   if( random(ap + dp) < dp )            // 被攻者躲过这一击
   {
      dodge_skill = victim->query_skill_mapped("dodge");
      if( !dodge_skill ) dodge_skill = "dodge";
         result += SKILL_D(dodge_skill)->query_dodge_msg(limb,victim);//显示躲避信息
      if( dp < ap && (!userp(victim) || !userp(me))   //DP<AP且不是玩家对打
          &&random(your["jing"]*100/your["max_jing"] + your["int"]) > 50 )
      {
         your["combat_exp"] += 1;
         victim->improve_skill("dodge", 1);//攻击时轻功越小越易长exp和skill
      }
      if( (ap < dp) && !userp(me) )//AP<DP且攻击者是NPC (没意义，NPC不需要,可去掉)
      {
          if( random(my["int"]) > 15 ) my["combat_exp"] += 1;
          me->improve_skill(attack_skill, random(my["int"]));
      }
      damage = RESULT_DODGE;
   }
   else //被攻者没躲过这招
   {
      if (intp(action["parry"]))
         victim->set_temp("down/parry", action["parry"]);
      else victim->set_temp("down/parry",0);
      if( victim->query_temp("weapon") ) //防御者有武器
      {
         pp = skill_power(victim, "parry", SKILL_USAGE_DEFENSE);
         if( !weapon ) pp *= 2;  //攻击者空手，parry加倍
      }
      else   //防御者没有武器
      {
         if( weapon ) pp = 0;     //进攻者有武器，parry为零
         else pp = skill_power(victim, "parry", SKILL_USAGE_DEFENSE); //双方空手,应能招架,取parry值传回去.(by llm)
      }
      if( victim->is_busy() ) pp = pp - pp/5;
      if( pp < 1 ) pp = 1;
      if( random(ap + pp)< pp )    //架住这一招
      {
         parry_skill = victim->query_skill_mapped("parry");
         if( !parry_skill ) parry_skill = "parry";            //没有激发招架
// added by xker---------
         else
         {
            if(victim->query_temp("weapon"))    //有武器，招架信息取自该武器的特殊攻击
               parry_skill =  victim->query_skill_mapped((victim->query_temp("weapon"))->query("skill_type"));
            else parry_skill = "parry";//???我认为没兵器取拳脚进行招架
         }
         if(!parry_skill) parry_skill = "parry";  //不能省，防止取不到特殊攻击skill，否则下一行会执行错
         if(!SKILL_D(parry_skill)->query_parry_msg(victim))
			 result += SKILL_D("parry")->query_parry_msg(victim,weapon);//取parry.c的信息
         else
	         result += SKILL_D(parry_skill)->query_parry_msg(victim);
//--------------
         if( pp < ap && (!userp(victim) || !userp(me))//不是玩家对打
            &&random(your["jing"]*100/your["max_jing"] + your["int"]) > 50 )
         {
            your["combat_exp"] += random(2);
            victim->improve_skill("parry", 1);//招架时身法越高越易长exp和skill
         }
         damage = RESULT_PARRY;
      }
      else //如果被攻者接不住这招
      {
         damage = me->query_temp("apply/damage");
         damage = (damage + random(damage)) / 2;
         if( action["damage"] )
            damage += action["damage"] * damage / 100;//加上进攻方武功的伤害修正值
         damage_bonus = me->query_str();//加力由/inherit/skill/force.c中的hit_ob实现(继承)
         if( my["jiali"] && (my["neili"] > my["jiali"]) )
         {
            if( force_skill = me->query_skill_mapped("force") )
            {
                foo = SKILL_D(force_skill)->hit_ob(me, victim, damage_bonus, my["jiali"]);
                if( stringp(foo) ) result += foo;
                else if( intp(foo) ) damage_bonus += foo;
            }
         }
         if( action["force"] )
            damage_bonus += action["force"] * damage_bonus / 100;//武功中force是对臂力的修正
         if( martial_skill = me->query_skill_mapped(attack_skill) )
         {
            foo = SKILL_D(martial_skill)->hit_ob(me, victim, damage_bonus);
            if( stringp(foo) ) result += foo;
            else if(intp(foo) ) damage_bonus += foo;
         }
         if( weapon )
         {
            foo = weapon->hit_ob(me, victim, damage_bonus);
            if( stringp(foo) ) result += foo;
            else if(intp(foo) ) damage_bonus += foo;
         }
         else
         {
            foo = me->hit_ob(me, victim, damage_bonus);
            if( stringp(foo) ) result += foo;
            else if(intp(foo) ) damage_bonus += foo;
         }
         if( damage_bonus > 0 )
            damage += (damage_bonus + random(damage_bonus))/2;
         if( damage < 0 ) damage = 0;
            defense_factor = your["combat_exp"];
         while( random(defense_factor) > my["combat_exp"] )
         {
            damage -= damage / 3;
            defense_factor /= 2;
         }
//damage的实际伤害效果
         damage = victim->receive_damage("qi", damage*2/3, me );   //me是记住是谁最后伤害当前气
         if(random(damage) > (int)victim->query_temp("apply/armor")
            && ( (me->is_killing(victim->query("id")))             //kill状态下
           && ((!weapon) && !random(4) || weapon && !random(2) )
            || ( (!weapon) && !random(7) || weapon && !random(4) ) )  )
         {
               damage = (damage-(int)victim->query_temp("apply/armor"))*2/3;//过去的damage为负的BUG
               victim->receive_wound("qi",damage, me);//伤害有效气值
               wounded = 1;
         }
         result += damage_msg(damage, action["damage_type"]);

         if( !userp(me) || !userp(victim) ) //非玩家对打
         {
            if( (ap < dp)&&(random(my["jing"]*100/my["max_jing"] + my["int"]) > 30) )
            {
               my["combat_exp"] += 1;
               if( my["potential"] - my["learned_points"] < 100 )
               my["potential"] += 1;
               me->improve_skill(attack_skill, 1);//被打时悟性越大长exp和skill越快
            }
            if( random(your["max_qi"] + your["qi"]) < damage )
            {
               your["combat_exp"] += 1;
               if( your["potential"] - your["learned_points"] < 100 )
               your["potential"] += 1;
            }
         }
      }
   }
   if(victim->query_temp("weapon"))
      result = replace_string(result,"$W",(victim->query_temp("weapon")->name())); //招架者的武器
      result = replace_string( result, "$l", limb );
   if( objectp(weapon) )
      result = replace_string( result, "$w", weapon->name() );
   else if( stringp(action["weapon"]) )
      result = replace_string( result, "$w", action["weapon"] );
   else if( attack_skill == "finger" )
      result = replace_string( result, "$w", "手指" );
   else if( attack_skill == "leg" )
      result = replace_string( result, "$w", "腿" );

   message_vision(result, me, victim );

   if( wizardp(me) && (string)me->query("env/combat")=="verbose" )
   {
    if( damage > 0 )
        tell_object(me, sprintf( GRN "AP：%d，DP：%d，PP：%d，伤害力：%d\n" NOR,
            ap/100, dp/100, pp/100, damage));
      else
         tell_object(me, sprintf( GRN "AP：%d，DP：%d，PP：%d\n" NOR,
            ap/100, dp/100, pp/100));
   }

   if( damage > 0 )
   {
      report_status(victim, wounded);
      if( victim->is_busy() ) victim->interrupt_me(me);
      if( (!environment(me)->check_yanwu()&&!me->is_killing(your["id"])) &&
          (!victim->is_killing(my["id"])) &&
          victim->query("qi")*2 <= victim->query("max_qi")) //比试非对杀
      {
         me->remove_enemy(victim);
         victim->remove_enemy(me);
         message_vision( winner_msg[random(sizeof(winner_msg))], me, victim);//分出胜负
   }
   }
   if( functionp(action["post_action"]) )
      evaluate( action["post_action"], me, victim, weapon, damage);
   if( attack_type==TYPE_REGULAR
       &&damage < 1
       &&victim->query_temp("guarding") )
   {
      victim->set_temp("guarding", 0);
      if( random(my["dex"]) < 5 )     //身法很重要
      {
         message_vision("$N一击不中，露出了破绽！\n", me);
         do_attack(victim, me, victim->query_temp("weapon"), TYPE_QUICK);//反攻两次
      }
      else
      {
         message_vision("$N见$n攻击失误，趁机发动攻击！\n", victim, me);
         do_attack(victim, me, victim->query_temp("weapon"), TYPE_RIPOSTE);//反攻一次
      }
   }
}

void fight(object me, object victim)
{
    object ob;
   if( !living(me) ) return;

   if( victim->is_busy() || !living(victim) )
   {
    me->set_temp("guarding", 0);
      if( !victim->is_fighting(me) ) victim->fight_ob(me);
        do_attack(me, victim, me->query_temp("weapon"), TYPE_QUICK);

      if( me->is_fighting(victim) && victim->is_fighting(me))
        if( (!objectp(me->query_temp("weapon"))
        && sizeof(me->query_skill_prepare()) > 1)
         ||( objectp(me->query_temp("weapon"))
         &&(me->query_temp("weapon"))->query("skill_type") == "sword"
         && me->query_skill("pixie-jian", 1) >= 60
         && me->query_skill_mapped("sword") == "pixie-jian") )
      {
        me->set_temp("action_flag",1);
         do_attack(me, victim, me->query_temp("weapon"), TYPE_QUICK);
         me->set_temp("action_flag",0);
      }
   }
   else if( random( (int)victim->query_dex() * 3 ) > (int)me->query_str())
   {
    me->set_temp("guarding", 0);
      if( !victim->is_fighting(me) ) victim->fight_ob(me);
        do_attack(me, victim, me->query_temp("weapon"), TYPE_REGULAR);

      if( me->is_fighting(victim) &&victim->is_fighting(me))
      if( (!objectp(me->query_temp("weapon"))
        && sizeof(me->query_skill_prepare()) > 1)
         ||( objectp(me->query_temp("weapon"))
         &&(me->query_temp("weapon"))->query("skill_type") == "sword"
         && me->query_skill("pixie-jian", 1) >= 60
         && me->query_skill_mapped("sword") == "pixie-jian") )
      {
        me->set_temp("action_flag",1);
         do_attack(me, victim, me->query_temp("weapon"), TYPE_REGULAR);
         me->set_temp("action_flag",0);
      }
    }
   else if( !me->query_temp("guarding"))
   {
    me->set_temp("guarding", 1);
        message_vision( guard_msg[random(sizeof(guard_msg))], me, victim);
         return;
   }
   else return;
}

void auto_fight(object me, object obj, string type)
{
    if( !userp(me) && !userp(obj) ) return;//别让NPC自己打起来
   if( me->query_temp("looking_for_trouble") ) return;
       me->set_temp("looking_for_trouble", 1);

      // This call_out gives victim a chance to slip trough the fierce guys.
    call_out( "start_" + type, 0, me, obj);
}

void start_berserk(object me, object obj)
{
    int shen;
    if( !me || !obj ) return;                 // Are we still exist( not becoming a corpse )?
        me->set_temp("looking_for_trouble", 0);
    if(     me->is_fighting(obj)              // Are we busy fighting?
        ||      !living(me)                       // Are we capable for a fight?
        ||      environment(me)!=environment(obj) // Are we still in the same room?
        ||      environment(me)->query("sleep_room")
        ||      environment(me)->query("no_fight"))// Are we in a peace room?
            return;
    shen = (int)me->query("shen");
    if(shen < 0)
        shen = 0 - shen;
        message_vision("$N用一种异样的眼神扫视著在场的每一个人。\n", me);
    if( !userp(me) || (int)me->query("neili") > (random(shen) + shen) / 2 )
        return;
   if( shen > ((int)me->query("neili") * 5)&&!wizardp(obj) )
    {
        message_vision("$N对著$n喝道："+ RANK_D->query_self_rude(me)+"看你实在很不顺眼，去死吧。\n",me,obj);
      me->kill_ob(obj);
   }
   else
   {
    message_vision("$N对著$n喝道：喂！"+RANK_D->query_rude(obj)+"，"+RANK_D->query_self_rude(me)
        +"正想找人打架，陪我玩两手吧！\n",me,obj);
      me->fight_ob(obj);
   }
}

void start_hatred(object me, object obj)
{
    if( !me || !obj ) return;                      // Are we still exist( not becoming a corpse )?
    me->set_temp("looking_for_trouble", 0);
    if(     me->is_fighting(obj)                  // Are we busy fighting?
        ||      !living(me)                        // Are we capable for a fight?
        ||      environment(me)!=environment(obj)  // Are we still in the same room?
        ||      environment(me)->query("sleep_room")
        ||      environment(me)->query("no_fight"))// Are we in a peace room?
            return;
	if(me->query("can_speak"))
        message_vision( catch_hunt_msg[random(sizeof(catch_hunt_msg))], me, obj);
    else
        message_vision( catch_hunt_msg[random(2)], me, obj);
	me->kill_ob(obj);
}

void start_vendetta(object me, object obj)
{
    if( !me || !obj ) return;                   // Are we still exist( not becoming a corpse )?
        me->set_temp("looking_for_trouble", 0);
    if(     me->is_fighting(obj)                  // Are we busy fighting?
    ||      !living(me)                         // Are we capable for a fight?
    ||      environment(me)!=environment(obj)   // Are we still in the same room?
        ||      environment(me)->query("sleep_room")
    ||      environment(me)->query("no_fight")) // Are we in a peace room?
        return;
      me->kill_ob(obj);
}

void start_aggressive(object me, object obj)
{
    if( !me || !obj ) return;                      // Are we still exist( not becoming a corpse )?
        me->set_temp("looking_for_trouble", 0);
    if( me->is_fighting(obj)                       // Are we busy fighting?
        ||      !living(me)                         // Are we capable for a fight?
        ||      environment(me)!=environment(obj)   // Are we still in the same room?
        ||      environment(me)->query("sleep_room")
        ||      environment(me)->query("no_fight")) // Are we in a peace room?
        return;
      me->kill_ob(obj);
}

// This function is to announce the special events of the combat.
// This should be moved to another daemon in the future.
void announce(object ob, string event)
{
    switch(event)
   {
        case "dead":
            message_vision("\n$N死了。\n\n", ob);
            break;
        case "unconcious":
            message_vision("\n$N脚下一个不稳，跌在地上一动也不动了。\n\n", ob);
            break;
        case "revive":
            message_vision("\n$N慢慢睁开眼睛，清醒了过来。\n\n", ob);
            break;
   }
}

void winner_reward(object killer, object victim)
{
        killer->defeated_enemy(victim);
}


