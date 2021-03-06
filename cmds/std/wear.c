// wear.c

#include <ansi.h>

inherit F_CLEAN_UP;

int do_wear(object me, object ob);

int main(object me, string arg)
{
        object ob, *inv;
        int i, count;

        if( !arg ) return notify_fail("你要穿戴什么？\n");
        
        if ( time() - me->query_temp("last_time/remove") < 5 )
                  return notify_fail("急什么？慢慢来。\n");     
        
        if(arg=="all") {
                inv = all_inventory(me);
                for(count=0, i=0; i<sizeof(inv); i++) {
                        if( inv[i]->query("equipped") ) continue;
                        if(do_wear(me, inv[i]) ) count ++;
                }
                write("Ok.\n");
                return 1;
        }

        if( !objectp(ob = present(arg, me)) )
                return notify_fail("你身上没有这样东西。\n");
                        
        if( ob->query("equipped") )
                return notify_fail("你已经装备着了。\n");

        return do_wear(me, ob);
}

int do_wear(object me, object ob)
{
        string str;

        if( ob->query("owner_id") && ob->query("owner_id") != getuid(me) )   {
                destruct(ob);
                return notify_fail("下次别乱偷别人的东西。\n");
        }

        if( ob->query("No_Wear") )
                return notify_fail("这件衣服不能再穿了！\n");
                
        if ( time() - me->query_temp("last_time/remove") < 6 )
                  return notify_fail("急什么？慢慢来。\n");

        if( ob->query("female_only")
        &&      (string)me->query("gender") != "女性" )
                return notify_fail("这是女人的衣衫，你一个大男人也想穿，羞也不羞？\n");

        if( ob->query("male_only")
        &&      (string)me->query("gender") != "男性" )
                return notify_fail("这是大男人的衣服，你一个姑娘家就不要胡闹了！\n");
  
  //add by wsw 20051010
  //加入装备绑定限制条件
  if (ob->query("changed") && (!ob->query("primitive_id") ||!ob->query("unique_code") ) && !wizardp(me)) 
  	return notify_fail("这件装备来历不明，不能使用！\n");
  if (ob->query("bind_id") && ob->query("bind_id") != getuid(me) ) 
  	return notify_fail("这不是你的兵器！\n");
  
                
  //加入装备条件限制 wsw于2003年11月
    if(ob->query("consistence")>0 && ob->query("consistence")<=0)
        return notify_fail("这件装备暂时不能穿了。\n");
// if (!wizardp(me)) {
    if( ob->query("weapon_wiel/exp")> me->query("combat_exp") )  return notify_fail("你的经验不够，请用ll命令查看装备要求。\n");
    if( ob->query("weapon_wiel/str")> me->query("str") )  return notify_fail("你的天赋不够，请用ll命令查看装备要求。\n");
    if( ob->query("weapon_wiel/con")> me->query("con") )  return notify_fail("你的天赋不够，请用ll命令查看装备要求。\n");
    if( ob->query("weapon_wiel/int")> me->query("int") )  return notify_fail("你的天赋不够，请用ll命令查看装备要求。\n");
    if( ob->query("weapon_wiel/dex")> me->query("dex") )  return notify_fail("你的天赋不够，请用ll命令查看装备要求。\n");
    if( ob->query("weapon_wiel/kar")> me->query("kar") )  return notify_fail("你的天赋不够，请用ll命令查看装备要求。\n");
    if( ob->query("weapon_wiel/max_jing")> me->query("max_qi") )  return notify_fail("你的最大气血不够，请用ll命令查看装备要求。\n");
    if( ob->query("weapon_wiel/max_qi")> me->query("max_jing") )  return notify_fail("你的精神不够，请用ll命令查看装备要求。\n");
    if( ob->query("weapon_wiel/skill")> me->query_skill(ob->query("skill_type"),1) )  return notify_fail("你的技能不够。\n");

        if( ob->wear() ) {
        	    if (ob->query("bind_type") >=1 && !ob->query("bind_id"))  ob->set("bind_id",getuid(me));//add by wsw 20051011
                if( !stringp(str = ob->query("wear_msg")) )
                        switch( ob->query("armor_type") ) {
                                case "cloth":
                                case "armor":
                                case "boots":
                                case "surcoat":
                                        str = YEL "$N穿上一" + ob->query("unit") + "$n。\n" NOR;
                                        break;
                                case "head":
                                case "neck":
                                case "wrists":
                                case "finger":
                                case "hands":
                                        str = YEL "$N戴上一" + ob->query("unit") + "$n。\n" NOR;
                                        break;
                                case "waist":
                                        str = YEL "$N佩上一" + ob->query("unit") + ob->query("name") + "。\n" NOR;
                                        break;
                                default:
                                        str = YEL "$N装备$n。\n" NOR;
                        }
                message_vision(str, me, ob);
                me->set_temp("last_time/wear",time());
                return 1;
        } else
                return 0;
}

int help(object me)
{
        write(@HELP
指令格式：wear|chuan <装备名称>
 
这个指令让你装备某件防具。
 
HELP
    );
    return 1;
}

