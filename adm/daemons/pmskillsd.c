/************************炎黄自创武功系统核心文件*********************************
created by Rcwiz for YHONLINE
*******************************************************************************/

#pragma optimize
#pragma save_binary

inherit F_DBASE;

#include <ansi.h>
#include <localtime.h>

#define MEMBER_D                        "/adm/daemons/memberd" 
#define CND_EXP_1                       5000000
#define CND_POT_1                       10000
#define SK_FILE                         "/kungfu/skill/" + my_mkskill["skid"]
#define RATE                            10
#define MAX_POINT                       3000000.0000
#define VERSION                         "V 1.00"

// 返回熟练度的百分数（用于战斗函数调用）
public int get_point(int point)
{
    int pt;
    
    pt = (int)(point / MAX_POINT);

    return pt;
}
// 返回熟练度的百分数（用于显示）
public float get_point2(int point)
{
 	float fp = (float)point;
	return (float)(fp / MAX_POINT);   
}
// 返回最大熟练度
public int get_max_point()
{
	return MAX_POINT;
}
// 获取自创武功
public mixed get_pmsk_id(object me)
{
	mapping skills;
	string *my_skills;
	int i;

        skills = me->query_skills();
        if (! sizeof(skills))return 1;
        my_skills = keys(skills);
        
        // 获取自创武功
        for (i = 0; i < sizeof(my_skills); i ++)
        {
              if (("/kungfu/skill/" + my_skills[i])->playermake())
                    return my_skills[i];              
        }
        return 0;
}

string *can_make = ({
	"sword", "blade", "staff", "unarmed", "cuff", "whip",
	"strike", "hand", "club", "finger", "claw"
});

string *weapon_sk = ({
	"sword", "blade", "staff", "whip", "club"
});

mapping damage_type = ([
        "sword"            :    "刺伤",
        "blade"            :    "砍伤",
        "staff"            :    "挫伤",
        "unarmed"          :    "瘀伤",
        "cuff"             :    "瘀伤",
        "whip"             :    "抽伤",
        "strike"           :    "震伤",
        "hand"             :    "瘀伤",
        "club"             :    "挫伤",
        "finger"           :    "刺伤",
        "claw"             :    "抓伤"
]);       
        
mapping skill_feature = ([
        "dam"              :    "威猛型",
        "att"              :    "灵动型",
        "def"              :    "防御型"
]);

private void modify_file(object me, mapping my_mkskill, string strmsg_hitob, int flag);
public int create_actions(object me, string skname, string desc, string ctsk);
public show_pmsk(object me, string skid);

void create()
{
        seteuid(getuid());
        set("channel_id", "系统精灵");
        set("no_clean_up", 1);
        CHANNEL_D->do_channel(this_object(), "sys", "自创武功系统系统已经启动。");       
}

/***************************************************************************
  检查是否达到自创武功基本条件
****************************************************************************/
public int check_condition1(object me)
{
	string *my_skills;
	mapping skills;
	int i;
	/*
	if (! MEMBER_D->is_valib_member(me->query("id")))
	{
		write("对不起，自创武功系统只对有效会员开放。\n");
		return 0;		
        }
        */
	if (me->query("combat_exp") < CND_EXP_1)
	{
		write("你实战经验不足， 无法自创武功！\n");
		return 0;
	}
	if (me->add("potential", 0) < CND_POT_1)
	{
		write("你潜能不够，无法自创武功！\n");
		return 0;
	}
	if (me->query_skill("martial-cognize", 1) < 400)
	{
		write("你武学修养不足，无法自创武功！\n");
		return 0;		
	}
	if (! me->query("breakup"))
	{
		write("你未打通任督二脉，无法自创武功！\n");
		return 0;		
	}
	if (! ultrap(me))
	{
		write("你还是先成为武学大宗师再说吧！\n");
		return 1;
	}
	// 是否已经自创过武功
        skills = me->query_skills();
        if (! sizeof(skills))return 1;
        my_skills = keys(skills);

        for (i = 0; i < sizeof(my_skills); i ++)
        {
        	if (("/kungfu/skill/" + my_skills[i])->playermake())
        	{
        	      write("你已经自创过武功 " + my_skills[i] + " 了！\n");
        	      return 0;
        	}
        }
        if (me->query("pmskills"))
        {
        	write("对不起，你存在自创武功数据记录，可能你的自创武功被放弃掉，\n"
        	      "或者不存在，请与本站巫师联系，并清除冗余数据！\n");
        	return 0;
        }

        return 1;
}

/***************************************************************************
  检查是否达到自创武功基本条件，自创武功设置开始
****************************************************************************/
public int check_condition2(object me)
{
	write(HIG "\n请输入自创武功的种类，为以下任意一种：\n" NOR);
	write(HIR "sword、blade、staff、whip、finger、unarmed、"
	      "strike、hand、cuff、hand、claw、club\n" NOR);
        write(HIR "注意：选择类型前请确保你已装备相应武器或空手。\n" NOR);
	write(HIW "武功种类：" NOR);
        input_to("check_skilltype", me);
}
/***************************************************************************
  自创武功种类
****************************************************************************/
private void check_skilltype(string types, object me)
{
	int lvl1, lvl2;
	string sk_map;
	object weapon;
        mapping my_mkskill = ([]); // 自创武功信息

        if (! me || ! types || types == "")
                return;

        write(types + "\n");        
        if (member_array(types, can_make) == -1)
        {
        	write("自创武功种类不正确。\n");
        	return;
        }
        // 空手类
        if (member_array(types, weapon_sk) == -1)
        {
                if (me->query_temp("weapon"))
                {
                	write("你还是先把武器取下吧！\n");
                	return;
                }
        }         
        else // 兵器类
        {
                if (! objectp(weapon = me->query_temp("weapon")) ||
                    (string)weapon->query("skill_type") != types)
                {
                	write("你装备的武器不对。\n");
                	return;
                }
        }

        // 判断等级
        lvl1 = me->query_skill(types, 1);
        sk_map = me->query_skill_mapped(types);
        lvl2 = me->query_skill(sk_map, 1);        

        if (lvl1 < 420)
        {
        	write(HIG + CHINESE_D->chinese(types) + " 等级不足。\n" NOR);
        	return;
        }
        if (! stringp(sk_map))
        {
        	write(HIG "你必须先激发一种武功在 " + CHINESE_D->chinese(types) + " 上。\n" NOR);
        	return;
        }
        if (lvl2 < 420)
        {
        	write(HIG + CHINESE_D->chinese(sk_map) + " 等级不足。\n" NOR);
        	return;
        }
        if (me->query_skill("force") < 600 ||
            me->query_skill("parry") < 600 ||
            me->query_skill("dodge") < 600)
        {
        	write(HIG "有效内功、有效招架或有效轻功等级不足。\n" NOR);
        	return;
        }
        my_mkskill["types"] = types;
        write(HIG "\n请输入自创武功的英文名，如:wuming-jian 。\n" NOR);
        write(HIR "英文名长度必须为10~20个字符之间！\n" NOR);
        write(HIR "请勿输入容易引起混淆或不雅的英文名，一经发现立即删除。\n" NOR);
        write(HIW "英文名：" NOR);        
        input_to("get_skill_id", me, my_mkskill);
}
/***************************************************************************
  自创武功ID，对应文件名
****************************************************************************/
private void get_skill_id(string sk, object me, mapping my_mkskill)
{
        if (! me || ! sk || sk == "")
                return;
                
        if (CHINESE_D->check_chinese(sk))
        {
        	write("请用英文名。\n");
        	return;
        }      
        sk = filter_color(sk);
        sk = replace_string(sk, "\"", "");
        write(sk + "\n");
	if (file_size("/kungfu/skill/" + sk + ".c") != -1)
	{
		write(sk + " 已存在！\n");
		return;
        }
        if (sizeof(sk) < 10 || sizeof(sk) > 20)
        {
        	write("英文名长度必须为10~20个字符之间！\n");
        	return;
        }
        my_mkskill["skid"] = sk;
        write(HIG "\n请输入自创武功的中文名，如：无名剑法。\n" NOR);
        write(HIR "请勿输入容易引起混淆或不雅的中文名，一经发现立即删除。\n" NOR); 
        write(HIR "中文名必须为汉字长度必须为2~8个汉字之间。\n" NOR);
        write(HIW "中文名：" NOR);
        input_to("get_skill_name", me, my_mkskill);
}
/***************************************************************************
  自创武功中文名
****************************************************************************/
private void get_skill_name(string skname, object me, mapping my_mkskill)
{
        if (! me || ! skname || skname == "")
                return;
                	
        write(skname + "\n");
	if (! CHINESE_D->check_chinese(skname))
	{
		write("输入武功名必须为中文汉字！\n");
		return;
	}
	if (stringp(CHINESE_D->find_skill(skname)))
	{
		write("这个名字已经存在了，请重新选择其他中文名。\n");
		return;
	}

	if (sizeof(skname) < 4 || sizeof(skname) > 32)
	{
		write("中文名长度必须为2~16个汉字之间。\n");
		return;
	}
	my_mkskill["skname"] = skname;
	write(HIG "\n请为 " + HIW + skname + HIG" 指定如下的一种特性：\n" NOR);
	write(HIR "威猛型(1)  灵动型(2)  防御型(3) \n" NOR);
        write(HIR "威猛型：有较高的攻击力，以及攻击特效为追加攻击伤害。\n" NOR);
        write(HIR "灵动型：有较高的命中率，以及攻击特效为自动连招。\n" NOR);
        write(HIR "防御型：当激发为招架时有较高的防御，以及有防御特效\n"
                  "和特殊攻击特效（使对方busy），不受阴阳八卦的影响。\n" NOR);
	write(HIW "输入1~3：" NOR);
	input_to("get_skill_feature", me, my_mkskill, 0);
}
/***************************************************************************
  自创武功特性，可供外部调用, flag为0表示创造第一招 1表示增加招式
****************************************************************************/
private void get_skill_feature(string choice, object me, mapping my_mkskill, int flag)
{
	string feature;
        
        if (! me || ! choice || choice == "")
                return;

        write(choice + "\n");	
	switch(choice)
	{
		case "1":
		   feature = "dam";
		   break;
		case "2":
		   feature = "att";
		   break;
		case "3":
		   feature = "def";
		   break;
		default :
		   write("输入错误！\n");
		   return;
	}
	my_mkskill["feature"] = feature;
	write(HIG "\n请输入 " HIW + my_mkskill["skname"] + HIG " 特殊攻击描述。如：\n" NOR);
	write(HIR "$N一招攻出，竟卷起千层气浪，太玄内劲顿时源源不绝透过$w涌入$n体内！\n" NOR);
	write(HIR "其中“$N”为发招者，“$n”为受招者，$w为兵器名称。\n" NOR);
	write(HIR "描述长度最多不超过50个汉字。\n" NOR);
	write(HIG "所选择武功特性： " HIW + skill_feature[feature] + NOR + "\n");
	write(HIW "特效攻击描述：" NOR);
	input_to("get_skill_hitob", me, my_mkskill, flag);	

}
/***************************************************************************
  自创武功特殊攻击特效描述, flag --->>
****************************************************************************/
private void get_skill_hitob(string msg_hitob, object me, mapping my_mkskill, int flag)
{
	string strmsg_hitob;
        if (! me || ! msg_hitob || msg_hitob == "")
                return;

        msg_hitob = replace_string(msg_hitob, "\"", "");
        msg_hitob = filter_color(msg_hitob);
        write(msg_hitob + "\n");

	if (sizeof(msg_hitob) > 100)
	{
		write("特殊攻击描述最多为50个汉字。\n");
		return;
        }

        my_mkskill["msg_hitob"] = msg_hitob;
        my_mkskill["msg_hitob"] = 
        replace_string(my_mkskill["msg_hitob"], "$w", "\" + weapon->name() + HIR + \"");        
        switch(my_mkskill["feature"])
        {
        	case "dam":
                  strmsg_hitob = "mixed hit_ob(object me, object victim, int damage_bonus)\n"
                                 "{\n\tobject weapon;\n\n\t"
                                 "weapon = me->query_temp(\"weapon\");\n\t"
                                 "if (me->query(\"pmskills/point\") < PMSKILLS_D->get_m"
                                 "ax_point())\n\t\t"
                                 "me->add(\"pmskills/point\", 1);\n\n\tvictim->receive_wound"
                                 "(\"qi\", (int)(damage_bonus * 2 * PMSKILLS_D->get_point(me->qu"
                                 "ery(\"pmskills/point\"))), me);\n\n\tif (damage_bonus < "
                                 "160)return 0;\n\n\tif (random(3) || me->is_busy() || me"
                                 "->query(\"neili\") < 100)return 0;\n\t"
                                 "victim->receive_wound(\"qi\", (int)(damage_bonus / 2 + "
                                 "damage_bonus * PMSKILLS_D->get_point(me->query(\"pmskill"
                                 "s/point\")) * 2), me);\n\tme->add(\"neili\", -50);\n\n\tr"
                                 "eturn HIR \"" + my_mkskill["msg_hitob"] + "\\n\" NOR;\n}\n\n";
                  break;
        	case "att":
                  strmsg_hitob = "mixed hit_ob(object me, object victim, int damage_bonus)\n"
                                 "{\n\tint i, attack_time;\n\n\tobject weapon;\n\n\t"
                                 "weapon = me->query_temp(\"weapon\");\n\n\t"
                                 "attack_time = (int)(me->query_skill(\"" + my_mkskill["skid"] + 
                                 "\", 1) / 40);\n\n\tif (attack_time > 13)attack_time = 13;\n\n\t"
                                 "if (me->query(\"pmskills/point\") < PMSKILLS_D->get_m"
                                 "ax_point())\n\t\t"
                                 "me->add(\"pmskills/point\", 1);\n\n\tvictim->receive_wound"
                                 "(\"qi\", (int)(damage_bonus * PMSKILLS_D->get_point(me->qu"
                                 "ery(\"pmskills/point\")) / 3), me);\n\n\tif (damage_bonus < "
                                 "160 || ! living(victim))return 0;\n\n\tif (random(3) || me-"
                                 ">is_busy() || me->query_temp(\"pmskill/lian\") || me->query"
                                 "(\"neili\") < 100 )return 0;\n\t"  
                                 "message_vision(HIR \"\\n" + my_mkskill["msg_hitob"] + "\\n\" NOR,"
                                 " me, victim);\n\n\tme->start_busy(1 + random(attack_time));\n\n\t"
                                 "me->add(\"neili\", -50);\n\n\t"
                                 "me->set_temp(\"pmskill/lian\", 1);\n\t"
                                 "for (i = 0; i < attack_time; i++)\n\t"
                                 "{\n\t\tif (! me->is_fighting(victim))\n\t\t\tbreak;\n\n\t\t"
                                 "if (! victim->is_busy() && random(2))victim->start_busy(1);"
                                 "\n\n\t\tCOMBAT_D->do_attack(me, victim, weapon, 0);\n\t}\n\n\t"
                                 "me->delete_temp(\"pmskill/lian\");\n\n\treturn 1;\n\n\t"
                                 "\n}\n\n";

                 break;
               case "def":
                 strmsg_hitob = "mixed hit_ob(object me, object victim, int damage_bonus)\n"
                                "{\n\tint ap, dp;\n\tobject weapon;\n\n\t"
                                "weapon = me->query_temp(\"weapon\");\n\n\t"
                                "if (me->query(\"pmskills/point\") < PMSKILLS_D->get_m"
                                "ax_point())\n\t\t"
                                "me->add(\"pmskills/point\", 1);\n\n\tvictim->receive_wound"
                                "(\"qi\", (int)(damage_bonus * PMSKILLS_D->get_point(me->qu"
                                "ery(\"pmskills/point\")) / 3), me);\n\n\t"
                                "ap = me->query_skill(\"" + my_mkskill["types"] + "\");\n\t"
                                "dp = victim->query_skill(\"parry\");\n\n\t"
                                "if (ap / 2 + random(ap) <= dp)return 0;\n\n\t"
                                "if (! living(victim) || victim->is_busy() || random(4))return 0;\n\n\t"
                                "message_vision(HIR \"\\n" + my_mkskill["msg_hitob"] + "\\n\" NOR,"
                                " me, victim);\n\n\tme->add(\"neili\", -50);\n\n\t"
                                "victim->start_busy(2 + random(ap / 80));\n\n\t"
                                "return 0;\n}\n\n"
                                "int query_effect_parry(object attacker, object me)\n"
                                "{\n\treturn (100 + 150 * PMSKILLS_D->get_point(me->query("
                                "\"pmskills/point\")));\n}\n\n";
                 break;
              default: return;
        }
	write(HIG "\n请输入 " HIW + my_mkskill["skname"] + HIG " 特殊防御描述。如：\n" NOR);
	write(HIR "可是$n不闪不避，举剑闪电般使出「叠翠浮青」反削$N手腕，挡开了此招。\n" NOR);
	write(HIR "注意：其中$n代表自己，$N代表对方，$l代表对方身体部位。本系统不做语法检查，\n请认"
	          "真严格地按照该格式输入，否则后果自负！\n" NOR);
	write(HIR "招架描述必须为中文名且长度不超过40个汉字。\n" NOR);
	write(HIW "特殊防御描述一：" NOR);
        input_to("get_skill_validdamage", me, my_mkskill, strmsg_hitob, flag);

}
/***************************************************************************
  自创武功特殊防御描述 三招  flag --->>
****************************************************************************/
private void get_skill_validdamage(string validdamage_msg, object me, mapping my_mkskill, 
                                  string strmsg_hitob, int flag)
{
        if (! me || ! validdamage_msg || validdamage_msg == "")
                return;

        validdamage_msg = replace_string(validdamage_msg, "\"", "");
        validdamage_msg = filter_color(validdamage_msg);
        write(validdamage_msg + "\n");

	if (sizeof(validdamage_msg) > 80)
	{
		write("特殊防御描述长度必须小于40个汉字。\n");
		return;
        }
        if (! stringp(my_mkskill["validdamage_msg1"]))
        {
                my_mkskill["validdamage_msg1"] = validdamage_msg;
	        write(HIW "特殊防御描述二：" NOR);           
                input_to("get_skill_validdamage", me, my_mkskill, strmsg_hitob, flag);
                return;
        }
        else if (! stringp(my_mkskill["validdamage_msg2"]))
        {
                my_mkskill["validdamage_msg2"] = validdamage_msg;
	        write(HIW "特殊防御描述三：" NOR);                
                input_to("get_skill_validdamage", me, my_mkskill, strmsg_hitob, flag);
                return;        	
        }
        else if (! stringp(my_mkskill["validdamage_msg3"]))
        {
                my_mkskill["validdamage_msg3"] = validdamage_msg;
	        write(HIG "\n请输入 " HIW + my_mkskill["skname"] + HIG " 一个招式名称，如：有凤来仪 。\n" NOR);
	        write(HIR "招式名称必须为中文名且长度必须为2~8个汉字之间。\n" NOR);
	        write(HIW "招式名称：" NOR);
	        input_to("get_skill_action_name", me, my_mkskill, strmsg_hitob, flag);  
                return;
        }
        else    return;        
      
}
/***************************************************************************
  自创武功招式名, 可用于第一次创造武功和后来加入招式使用函数  flag --->>
****************************************************************************/
public void get_extern_action_name(object me, string ctsk)
{
	mapping my_mkskill = ([]);
	
	write(HIG "\n请输入 " HIW + CHINESE_D->chinese(ctsk) + HIG " 一个招式名称，如：有凤来仪 。\n" NOR);
	write(HIR "招式名称必须为中文名且长度必须为2~8个汉字之间。\n" NOR);
	write(HIW "招式名称：" NOR);
	input_to("get_skill_action_name", me, my_mkskill, 0, 1, ctsk);
	
}
public void get_skill_action_name(string action_skname, object me, mapping my_mkskill, 
                                  string strmsg_hitob, int flag, string ctsk)
{
        if (! me || ! action_skname || action_skname == "")
                return;

        write(action_skname + "\n");
	if (! CHINESE_D->check_chinese(action_skname))
	{
		write("输入招式名必须为中文汉字！\n");
		return;
	}
	if (sizeof(action_skname) < 4 || sizeof(action_skname) > 32)
	{
		write("招式名称长度必须为2~16个汉字之间。\n");
		return;
	}
	my_mkskill["action_skname"] = action_skname;
	write(HIG "\n请输入招式 " HIW + action_skname + HIG " 的描述，格式如下：\n" NOR);
	write(HIR "$N手中$w斜指，一招$NM，反身一顿，一刀向$n的$l撩去。\n" NOR);
	write(HIR "其中$N和$n分别代表发招者和受招者，$w代表发招者兵器，$l代表受招者\n"
	          "身体部位、$NM代表该招的招式名称(可省略)。本系统不做语法检查，请认\n"
	          "真严格地按照该格式输入，否则后果自负！\n" NOR);
	write(HIR "招式描述必须为中文名且长度不超过40个汉字。\n" NOR);
	write(HIW "招式描述：" NOR);
	input_to("get_skill_action_desc", me, my_mkskill, strmsg_hitob, flag, ctsk);
}
/***************************************************************************
  自创武功招式描述 flag --->>
****************************************************************************/
private void get_skill_action_desc(string action_desc, object me, mapping my_mkskill, 
                                   string strmsg_hitob, int flag, string ctsk)
{
        if (! me || ! action_desc || action_desc == "")
                return;
        
        action_desc = replace_string(action_desc, "\"", action_desc);
        action_desc = filter_color(action_desc);
        write(action_desc + "\n");

	if (sizeof(action_desc) > 80)
	{
		write("招式描述长度必须小于40个汉字。\n");
		return;
        }
        action_desc = replace_string(action_desc, 
                                     "$NM", 
                                     "「" + my_mkskill["action_skname"] + "」");
        my_mkskill["action_desc"] = action_desc;

        // 增加招式
        if (flag)
        {
              create_actions(me, 
                             my_mkskill["action_skname"], 
                             my_mkskill["action_desc"],
                             ctsk);
              return;
        }
        
	write(HIG "\n请输入招式 " HIW + my_mkskill["skname"] + HIG " 特殊招架描述，格式如下：\n" NOR);
	write(HIR "$n不退反进，使出恒山剑招「绵里藏针」，森森剑气充溢四周！架开了$N的这招。\n" NOR);
	write(HIR "$n不闪不避，举剑闪电般使出「叠翠浮青」反削$N的$l，想挡过此招。\n" NOR);
	write(HIR "注意：其中$n代表自己，$N代表对方，$l代表对方身体部位。本系统不做语法检查，\n请认"
	          "真严格地按照该格式输入，否则后果自负！该描述不支持$w参数！！！\n" NOR);
	write(HIR "招架描述必须为中文名且长度不超过40个汉字。\n" NOR);
	write(HIW "招架描述一：" NOR);
	input_to("get_skill_parrymsg", me, my_mkskill, strmsg_hitob, flag);
}
/***************************************************************************
  自创武功招式招架描述 一共三招 flag --->>
****************************************************************************/
private void get_skill_parrymsg(string parry_msg, object me, mapping my_mkskill, 
                                string strmsg_hitob, int flag)
{
        if (! me || ! parry_msg || parry_msg == "")
                return;

        parry_msg = replace_string(parry_msg, "\"", "");
        parry_msg = filter_color(parry_msg);
        write(parry_msg + "\n");

	if (sizeof(parry_msg) > 80)
	{
		write("招式描述长度必须小于40个汉字。\n");
		return;
        }
        if (! stringp(my_mkskill["parry_msg1"]))
        {
        	parry_msg = replace_string(parry_msg, "$w", "");
                my_mkskill["parry_msg1"] = parry_msg;
	        write(HIW "招架描述二：" NOR);                
                input_to("get_skill_parrymsg", me, my_mkskill, strmsg_hitob, flag);
                return;
        }
        else if (! stringp(my_mkskill["parry_msg2"]))
        {
        	parry_msg = replace_string(parry_msg, "$w", "");
                my_mkskill["parry_msg2"] = parry_msg;
	        write(HIW "招架描述三：" NOR);                
                input_to("get_skill_parrymsg", me, my_mkskill, strmsg_hitob, flag);
                return;        	
        }
        else if (! stringp(my_mkskill["parry_msg3"]))
        {
        	parry_msg = replace_string(parry_msg, "$w", "");
                my_mkskill["parry_msg3"] = parry_msg;
                modify_file(me, my_mkskill, strmsg_hitob, flag);
                return;
        }
        else    return;
}

/***************************************************************************
  信息收集完毕，创造武功
****************************************************************************/
private void modify_file(object me, mapping my_mkskill, string strmsg_hitob, int flag)
{
	string strtmp;
	string sk_map;
        string msg_validdamage;
        mapping basic_actions = ([]); // 参照武功信息
        
        write(my_mkskill["parry_msg1"] + "\n");
        write(my_mkskill["parry_msg2"] + "\n");
        write(my_mkskill["parry_msg3"] + "\n");      
        
	sk_map = me->query_skill_mapped(my_mkskill["types"]);
	
	if (! stringp(sk_map))
	{
		write("你必须先为 " + my_mkskill["types"] + " 激发一种特殊武功。\n");
		return;
	}
	basic_actions = ("/kungfu/skill/" + sk_map)->query_action(me);
	
	if (! mapp(basic_actions) || ! sizeof(basic_actions))
	{
		write("读取武功文件 " + sk_map + " 失败。\n");
		return;
	}
	// 根据自创武功特性给予修正
	switch(my_mkskill["feature"])
	{
		case "dam":
		   basic_actions["force"] += (basic_actions["force"] * 2 / RATE); 
		   basic_actions["damage"] += (basic_actions["damage"] * 2 / RATE);
		   break;

		case "att":
		   basic_actions["attack"] += (basic_actions["attack"] * 2 / RATE); 

		case "def":
		   basic_actions["parry"] += (basic_actions["parry"] * 2 / RATE);
		   break;

		default :
		   break;
	}

       msg_validdamage = "mixed valid_damage(object ob, object me, int damage, object weapon)\n"
                         "{\n\tmixed result;\n\tint ap, dp, mp;\n\tobject m_weapon;\n\n\t";
                          
       // 兵器类
       if (member_array(my_mkskill["types"], weapon_sk) != -1)
       {
             msg_validdamage += "if ((int) me->query_skill(\"" + my_mkskill["skid"] + "\", 1) < 300\n\t"
                                "|| ! (m_weapon = me->query_temp(\"weapon\"))\n\t"
                                "|| ! living(me)\n\t"
                                "|| m_weapon->query(\"skill_type\") != \"" + my_mkskill["t"
                                   "ypes"] + "\")\n\t\treturn;\n\n\t";
             my_mkskill["validdamage_msg1"] = 
             replace_string(my_mkskill["validdamage_msg1"], "$w", "\" + m_weapon->name() + HIC + \"");
             my_mkskill["validdamage_msg2"] = 
             replace_string(my_mkskill["validdamage_msg2"], "$w", "\" + m_weapon->name() + HIC + \"");
             my_mkskill["validdamage_msg3"] = 
             replace_string(my_mkskill["validdamage_msg3"], "$w", "\" + m_weapon->name() + HIC + \"");
                                   
       }
       else
       {
             msg_validdamage += "if ((int)me->query_skill(\"" + my_mkskill["skid"] + "\", 1) < 300\n\t"
                                " || ob->query_temp(\"weapon\")\n\t || ! living(me))\n\t\t"
                                "return;\n\n\t";
             my_mkskill["validdamage_msg1"] =                                 
             replace_string(my_mkskill["validdamage_msg1"], "$w", "");
             my_mkskill["validdamage_msg2"] = 
             replace_string(my_mkskill["validdamage_msg2"], "$w", "");
             my_mkskill["validdamage_msg3"] = 
             replace_string(my_mkskill["validdamage_msg3"], "$w", "");
       }

       msg_validdamage += "ap = me->query_skill(\"" + my_mkskill["skid"] + "\", 1)";
       if (my_mkskill["feature"] == "def")
               msg_validdamage += " + 50 + 100 * PMSKILLS_D->get_point(me->query(\"pmskills/"
               "point\"));\n\n\t";
       else    msg_validdamage += ";\n\n\t";

       msg_validdamage += "dp = ob->query_skill(\"force\", 1) + ob->query_dex() / 2;\n\n\t";
 
       if (my_mkskill["feature"] != "def")
       {
               msg_validdamage += "if (ob->query_skill(\"count\", 1) > 100)return;\n\n\t";
       }
       msg_validdamage += "if (ap / 2 + random(ap) < dp)\n\t{\n\t\t"
                          "result = ([ \"damage\": -damage ]);\n\t\t"
                          "switch (random(3))\n\t\t{\n\t\t"
                          "case 0:\n\t\t   result += ([\"msg\" : HIC \"" + 
                          my_mkskill["validdamage_msg1"] + "\\n\" NOR]);\n\t\t"
                          "break;\n\t\tcase 1:\n\t\t   result += ([\"msg\" : HIC \"" + 
                          my_mkskill["validdamage_msg2"] + "\\n\" NOR]);\n\t\t"
                          "break;\n\t\tdefault:\n\t\t   result += ([\"msg\" : HIC \"" + 
                          my_mkskill["validdamage_msg3"] + "\\n\" NOR]);\n\t\t"
                          "break;\n\t\t}\n\t\treturn result;\n\t}\n\n}\n\n";

	// 再次修正
	basic_actions["force"] += (basic_actions["force"]  / RATE);
	basic_actions["damage"] += (basic_actions["damage"] / RATE);
	basic_actions["attack"] += (basic_actions["attack"] / RATE);
	basic_actions["dodge"] += (basic_actions["dodge"]  / RATE);
	basic_actions["parry"] += (basic_actions["parry"]  / RATE);

	// 第一次自创武功
	if (! flag)
	{
	      // 写入头信息，并建立文件
	      strtmp =  "//      炎黄-玩家自创武功系统\n";
	      strtmp += "//      Made at " + MEMBER_D->bjtime(time(), 1) + " by Rcwiz\n";
	      strtmp += "//      " + SK_FILE + ".c" + "  " + my_mkskill["skname"] + "\n\n";
	      strtmp += "inherit SKILL;\n#include <ansi.h>\n\n";
	      strtmp += "#define PMSKILLS_D        \"/adm/daemons/pmskillsd\"\n\n";

	      strtmp += "string *parry_msg = ({\n";
	      strtmp += "HIG \"" + my_mkskill["parry_msg1"] + "\\n\" NOR,\n";
	      strtmp += "HIG \"" + my_mkskill["parry_msg2"] + "\\n\" NOR,\n";
	      strtmp += "HIG \"" + my_mkskill["parry_msg3"] + "\\n\" NOR,\n";
	      strtmp += "});\n\n";
              strtmp += "string query_parry_msg(object weapon)\n";
              strtmp += "{\n\treturn parry_msg[random(sizeof(parry_msg))];\n}\n\n";
	      strtmp += "int playermake(){ return 1; }\n";
	      strtmp += "string who_make(){ return \"" + me->query("id") + "\"; }\n\n";

	      if (! write_file(SK_FILE + ".c", strtmp, 1))
	      {
	      	   write("建立文件失败！\n");
	      	   return;
	      }
	      // action数据 可变信息
	      strtmp =  "//####actions start####\n";
	      strtmp += "mapping *action = ({\n";
	      strtmp += "([\t\"action\"     :  \"" + my_mkskill["action_desc"] + "\",\n";
	      strtmp += "  \t\"force\"      :  " + basic_actions["force"] + ",\n";
	      strtmp += "  \t\"attack\"     :  " + basic_actions["attack"] + ",\n";
	      strtmp += "  \t\"parry\"      :  " + basic_actions["parry"] +  ",\n";
	      strtmp += "  \t\"dodge\"      :  " + basic_actions["dodge"] + ",\n";
	      strtmp += "  \t\"damage\"     :  " + basic_actions["damage"] + ",\n";  
	      strtmp += "  \t\"skill_name\" :  \"" + my_mkskill["action_skname"] + "\",\n";                          
	      strtmp += "  \t\"damage_type\":  \"" + 
	                damage_type[my_mkskill["types"]] + "\",\n";
	      strtmp += "])\n});\n";
	      strtmp += "//####actions end####\n\n";
	      strtmp += "mixed get_actions(){ return action;}\n\n";
	      strtmp += "mixed get_actnames()\n{\n\tint i;\n\n\tstring *names;\n\n\t"
	                "names = ({});\n\n\t"
	                "for (i = sizeof(action) - 1; i >= 0; i--)\n\t\t"
	                "names += ({action[i][\"skill_name\"]});\n\n\t"
	                "return names;\n}\n\n";

	      // enable数据
	      strtmp += "int valid_enable(string usage)\n";
	      strtmp += "{\n\treturn usage == \"" + my_mkskill["types"] + "\" || "
	                "usage == \"parry\";\n}\n\n";

	      // 函数 mapping query_action(object me, object weapon)
	      if (my_mkskill["feature"] == "att")
	      {
	      strtmp += "mapping query_action(object me, object weapon)\n"
                        "{\n\tmapping act;\n\n\t"
                        "act = action[random(sizeof(action))];\n\n\t"
                        "act[\"attack\"] = \n\t"
                        "act[\"attack\"] + 50 + act[\"attack\"] * PMSKILLS_D->get"
                        "_point(me->query(\"pmskills/point\"));\n\n\t"
                        "return act;\n}\n\n";
              }
              else 
              {
              strtmp += "mapping query_action(object me, object weapon)\n"
                        "{\n\treturn action[random(sizeof(action))];\n}\n\n";
              }

              // 函数 valid_learn(object me)
              // 武器类skill
              if (member_array(my_mkskill["types"], weapon_sk) != -1)
              {
                        strtmp += "int valid_learn(object me)\n"
                        "{\n\tobject ob;\n\tif (! (ob = me->query_temp(\"we"
                        "apon\"))\n\t||  (string)ob->query(\"skill_type\") != "
                        "\"" + my_mkskill["types"] + "\")\n\t\treturn notif"
                        "y_fail(\"你使用的武器不对。\\n\");\n\tif (me->query_ski"
                        "ll(\"" + my_mkskill["types"] + "\", 1) < me->query"
                        "_skill(\"" + my_mkskill["skid"] + "\", 1))\n\t\tretu"
                        "rn notify_fail(\"你的" + 
                        CHINESE_D->chinese(my_mkskill["types"]) + 
                        "火候有限，无法领会更高深的" + my_mkskill["skname"] + 
                        "。\\n\");\n\treturn 1;\n}\n\n";
               }
               else // 空手类skill
               {
                        strtmp += "int valid_learn(object me)\n"
                        "{\n\tobject ob;\n\tif (me->query_temp(\"we"
                        "apon\")\n\t|| me->query(\"secondary_weapon\"))\n\t\treturn notif"
                        "y_fail(\"你必须空手练习。\\n\");\n\tif (me->query_ski"
                        "ll(\"" + my_mkskill["types"] + "\", 1) < me->query"
                        "_skill(\"" + my_mkskill["skid"] + "\", 1))\n\t\tretu"
                        "rn notify_fail(\"你的" + 
                        CHINESE_D->chinese(my_mkskill["types"]) + 
                        "火候有限，无法领会更高深的" + my_mkskill["skname"] + 
                        "。\\n\");\n\treturn 1;\n}\n\n";               	
               }

               // 函数query_skill_name(int level)
               strtmp += "string query_skill_name(int level)\n"
                         "{\n\tint i;\n\tfor (i = sizeof(action"
                         ")-1; i >= 0; i--)\n\t\tif (level >= ac"
                         "tion[i][\"lvl\"])\n\t\t\treturn action"
                         "[i][\"skill_name\"];\n}\n\n";

               // 函数int double_attack(){ return 1; }
               strtmp += "int double_attack(){ return 1; }\n\n";

               // 函数mixed hit_ob(object me, object victim, int damage_bonus)
               strtmp += strmsg_hitob;

               // 函数mixed valid_damage(object ob, object me, int damage, object weapon)
               strtmp += msg_validdamage;

               // 函数int practice_skill(object me)
               strtmp += "int practice_skill(object me)\n"
                         "{\n\treturn notify_fail(\"自创武学只能用"
                         "学(learn)的来提升等级。\\n\");\n}\n\n";

               // 函数int difficult_level()
               strtmp += "int difficult_level(){ return 2000;}\n\n";

               // 函数string perform_action_file(string action)
               strtmp += "string perform_action_file(string action)\n"
                         "{\n\treturn __DIR__\"" + my_mkskill["skid"] + 
                         "/\" + action;\n}\n\n";

	       write_file(SK_FILE + ".c", strtmp, 0);
	}
	// 添加到中文库
	CHINESE_D->add_translate(my_mkskill["skid"], my_mkskill["skname"]);
	
	// 设定等级
	me->set_skill(my_mkskill["skid"], me->query_skill(sk_map, 1) - 120);

	// 记录dbase数据
	me->set("pmskills/create_time", time());
	me->set("pmskills/types", my_mkskill["types"]);
	me->set("pmskills/feature", skill_feature[my_mkskill["feature"]]);
	me->set("pmskills/skid", my_mkskill["skid"]);
	me->set("pmskills/point", 0);
	
	// 扣除潜能
	me->add("potential", -1 * CND_POT_1);
	
	// 建立perform文件夹
	mkdir("/kungfu/skill/" + my_mkskill["skid"]);
	
	// 发布消息并记录
	CHANNEL_D->do_channel(this_object(), "rumor", "听说" + me->name(1) + HIM + 
	           "创出绝世武学 " + HIW + my_mkskill["skname"] + HIM + "，从此扬名"
	           "江湖。\n" NOR);

	log_file("/static/pmsk", me->query("id") + " created skill " + 
	         my_mkskill["skname"] + "(" + my_mkskill["skid"] + ") on " +
	         MEMBER_D->bjtime(time(), 1) + "\n");

	write(HIG "自创武功成功。\n" NOR);
	write(HIG "以后请使用 " HIR "pmsk show 武功英文名" HIG " 查看自创武功详细数据。\n" NOR);

	return;

}
/***************************************************************************
  信息收集完毕，增加招式
****************************************************************************/
public int create_actions(object me, string skname, string desc, string ctsk)
{
	mapping *acts, act;
	string strFile, strtmp;
	string sFile;
	int iSize, iItem, i;
	object obj;
	

	sFile = "/kungfu/skill/" + ctsk;
	if (me->add("potential", 0) < CND_POT_1)
	{
		write("你潜能不够，无法创造新的招式！\n");
		return 0;
	}
	if (! MEMBER_D->is_valib_member(me->query("id")))
	{
		write("对不起，自创武功系统只对有效会员开放。\n");
		return 0;		
        }
	if (file_size(sFile + ".c") == -1)
	{
		write("未找到指定文件！\n");
		return 0;
	}	
	
	acts = sFile->get_actions();

        if (sizeof(acts) >= 10)
        {
        	write("自创武功最多只能创造十个招式。\n");
        	return 0;
        }
	i = 1;
	strFile = "";
	while(1)
	{
		strtmp = read_file(sFile + ".c", i, 1);
		strFile += strtmp;
		if (strtmp == "//####actions start####\n")break;
	        i ++;
	        if (i > 100)
	        {
	      	    write("读取文件出错！\n");
	      	    return 0;
	        }
	}

        iSize = sizeof(acts);
        if (! acts || ! iSize )
        {
        	write("actions 数据无效！\n");
        	return 0;
        }
        
        strtmp = "";
        strFile += "mapping *action = ({\n";

        for (iSize = 0; iSize < sizeof(acts); iSize ++)
        {
              act = acts[iSize];
	      strtmp += "([\t\"action\"     :  \"" + act["action"] + "\",\n";
	      strtmp += "  \t\"force\"      :  " + act["force"] + ",\n";
	      strtmp += "  \t\"attack\"     :  " + act["attack"] + ",\n";
	      strtmp += "  \t\"parry\"      :  " + act["parry"] +  ",\n";
	      strtmp += "  \t\"dodge\"      :  " + act["dodge"] + ",\n";
	      strtmp += "  \t\"damage\"     :  " + act["damage"] + ",\n";  
	      strtmp += "  \t\"skill_name\" :  \"" + act["skill_name"] + "\",\n";                          
	      strtmp += "  \t\"damage_type\":  \"" + act["damage_type"] + "\",\n";
	      strtmp += "]),\n";
        }
        strFile += strtmp;
        
        strtmp = "";
        act["force"]  += random(10);
        act["damage"] += random(10);
        act["attack"] += random(10);                
        act["dodge"]  += random(10);
        act["parry"]  += random(10);
        
        strtmp += "([\t\"action\"     :  \"" + desc + "\",\n";
	strtmp += "  \t\"force\"      :  " + act["force"] + ",\n";
	strtmp += "  \t\"attack\"     :  " + act["attack"] + ",\n";
	strtmp += "  \t\"parry\"      :  " + act["parry"] +  ",\n";
	strtmp += "  \t\"dodge\"      :  " + act["dodge"] + ",\n";
	strtmp += "  \t\"damage\"     :  " + act["damage"] + ",\n";  
	strtmp += "  \t\"skill_name\" :  \"" + skname + "\",\n";                          
	strtmp += "  \t\"damage_type\":  \"" + act["damage_type"] + "\",\n";
	strtmp += "]),\n";

        strFile += strtmp;      
        strFile += "});\n//####actions end####\n";

        strtmp = "";
        while(1)
        {
        	strtmp = read_file(sFile + ".c", i, 1);
        	i ++;
        	if (strtmp == "//####actions end####\n")break;
        }
        strtmp = "";
        while(1)
        {
        	strtmp = read_file(sFile + ".c", i, 1);
        	if (! strtmp)break;
                strFile += strtmp;
                i ++;
        }

        if (! write_file(sFile + ".c", strFile, 1))
        {
        	write("写入文件失败！\n");
        	return 0;        	
        }
        if (obj = find_object(sFile))destruct(obj);

        me->add("potential", -1 * CND_POT_1);
        write("创建成功！\n");
        
        return 1;
}
/***************************************************************************
  外部调用：显示自创武功详细数据
****************************************************************************/
public show_pmsk(object me, string skid)
{
	mapping *acts;
	string *actnames;
	mapping performs;
	int i;
	
	//acts = ("/kungfu/skill/" + skid)->get_actions();
	actnames = ("/kungfu/skill/" + skid)->get_actnames();

	performs = me->query("pmskills/perform");

	write(BBLU + HIW "\t\t 炎黄英雄史自创武功系统个人数据\t\t   " + VERSION + " \n" NOR);
        write(HIW "≡---------------------------------------------------------------≡\n" NOR);
        //武功id， 武功中文名，招式数目，招式名称，绝招数目，绝招名称，熟练度
        write(HIY "WELCOME TO USE PMSK SYSTEM OF YHHERO AND HOPE YOU ALL GOES WELL.\n\n" NOR);
        write(sprintf(HIC "  武功代号：%-25s中文名称：%s\n" NOR, 
                      skid, 
                      CHINESE_D->chinese(skid)));
        write(sprintf(HIC "  武功属性：%-25s武功特性：%s\n" NOR, 
                      me->query("pmskills/types"), 
                      me->query("pmskills/feature")));                 
        write(sprintf(HIC "  创建时间：%-25s目前等级：%d\n" NOR, 
                      MEMBER_D->bjtime(me->query("pmskills/create_time"), 1), 
                      me->query_skill(skid, 1)));     
        write(sprintf(HIC "  招式总数：%-25d绝招总数：%d\n" NOR, 
                      sizeof(actnames),
                      sizeof(performs)));
        write(sprintf(HIY "\n  熟练度：%.1f ％\n\n" NOR,
                      get_point2(me->query("pmskills/point") * 100)));

        write(HIC "  招式列表：\n" NOR);
        write(HIC "  ˉˉˉˉˉˉ\n" NOR);
        for (i = 0; i < sizeof(actnames); i ++)
        {
              if (i % 2 == 0)write(sprintf(HIM "  %-35s" NOR, actnames[i]));
              else write(sprintf(HIM "%s\n" NOR, actnames[i])); 
        }
        if (i % 2)write("\n");
        write(HIC "\n  绝招列表：\n" NOR);
        write(HIC "  ˉˉˉˉˉˉ\n" NOR);                
        for (i = 0; i < sizeof(performs); i ++)
        {
              if (i % 2 == 0)write(sprintf(HIM "  %-35s" NOR, performs[i]));
              else write(sprintf(HIM "%s\n" NOR, performs[i])); 
        }
        write(HIG "\n  *请使用" HIR " pmsk ? " HIG " 查看pmsk指令的使用方法。\n\n" NOR);
        write(HIR "  *为避免带来不必要的麻烦请认真阅读自创武功帮助文件 " HIY "help pmskills\n\n" NOR);
        write(HIY "                (" HIR"YΨH" HIY ").YHHERO WIZARD GROUP http://yhhero."
              "vicp.net\n" NOR);
        write(HIW "≡---------------------------------------------------------------≡\n" NOR);
}
/***************************************************************************
  外部调用：忘却自创武功（删除）
****************************************************************************/
public int forget_pmsk(object me, string ctsk)
{
	object obj;

	obj = find_object("/kungfu/skill/" + ctsk);

	CHINESE_D->remove_translate(ctsk);
	me->delete_skill(ctsk);
	rm("/kungfu/skill/" + ctsk + ".c");
	"/cmds/wiz/rm"->rm_dir("/kungfu/skill/" + ctsk);
	me->delete("pmskills");

	if (obj)destruct(obj);
	me->save();
	write("OK.\n");

	return 1;
}
/***************************************************************************
  外部调用：显示所有自创武功
****************************************************************************/
public mixed show_all_pmsk(object me)
{
	mixed file;
	string *pmsk;
	int i, size;
	object obj;
	string fname;
	
	file = get_dir("/kungfu/skill/", -1);
	
	pmsk = ({});
        
	for(i = 0; i < sizeof(file); i ++)
	{
		fname = file[i][0];
		size = sizeof(fname);
		
		if (file_size("/kungfu/skill/" + fname) == -1 ||
		    file_size("/kungfu/skill/" + fname) == -2)
		       continue;
                
		if (fname[size - 2..size] != ".c")
		       continue;

		if (("/kungfu/skill/" + fname)->playermake())
		       pmsk += ({ file[i][0] });		
	}
	if (! sizeof(pmsk))
	{
		write("目前系统中无自创武功！\n");
		return 0;
	}
	write(HIY "系统中的自创武功列表：\n" NOR);
	write(sprintf(HIG "%-30s%-30s%-30s\n" NOR,
	              "武功代号", "中文名称", "创建者"));
	write(HIW "--------------------------------------------------------"
	      "---------------\n" NOR);	
	for (i = 0; i < sizeof(pmsk); i ++)
	{
	       write(sprintf(HIC "%-30s%-30s%-30s\n" NOR,
	                     pmsk[i][0..sizeof(pmsk[i]) - 3],
	                     CHINESE_D->chinese(pmsk[i][0..sizeof(pmsk[i]) - 3]),
	                     ("/kungfu/skill/" + pmsk[i])->who_make()));	       
        }
        write(HIW "---------------------------------------------------------"
              "--------------\n" NOR);
	return 1;
}