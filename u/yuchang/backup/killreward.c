//最后修改时间（请修改者注明）2000-11-25 llm(保护期玩家移到特殊地方)

#include <ansi.h>

inherit F_DBASE;

void create()
{
    seteuid(getuid());
    set("name", "死亡精灵");
    set("id", "killreward");
    set("chat_amount",1000000000);
}

void killer_reward(object killer, object victim)
{
    string msg,name,vmark,*atk;
    int level,exp,pot,score,i;
    mapping quest;
    float k;
    object pker;
    
    exp = victim->query("combat_exp");
//    killer->killed_enemy(victim);这个函数找不到出处，先注释了
    if(userp(victim))//玩家被杀
    {
        if(!killer->is_character())//不是生物
        {
            name = killer->query("short");
            switch(killer->query("why_die"))//这个是在具体的文件里加的
            {
                case "阵": msg="在某处困";break;
                case "摔": msg="在某处摔";break;
                case "毒": msg="中毒";break;
                default: msg="意外地";break;
            }
        }
        else//是生物
        {
            name = killer->name(1);
            switch(killer->query("race"))
            {
                case "野兽": msg = "咬";break;
                case "家畜": msg = "踩";break;
                case "飞禽": msg = "啄";break;
                case "昆虫": msg = "叮";break;
                default: msg = "杀";
            }
            msg = "被"+name+HIM+msg;
        }
        CHANNEL_D->do_channel(this_object(), "rumor",
            sprintf("据说%s%s死了。", victim->name(1),msg));  
        victim->add("die/times", 1);              //加一次被杀次数 by llm
        victim->set("die/name",name);  //记下最后一次死于谁手 by llm

        if (userp(killer))//杀手是玩家
        {
            victim->add("die/pk", 1);                //加一次被PK次数  by llm
            victim->set("die/name","某位玩家");      //覆盖前面的name by llm
//-----------by llm about 判断主动攻击 2000/9/4----------------
            if(pointerp(atk = victim->query_temp("attacker"))//被害人有被攻击过的人名单
                 &&member_array(killer->query("id"),atk)!=-1  //名单中有killer的id
                 &&!killer->query_temp("chaseing")  //不是因公追捕PKer者
            )
            {
                vmark = "";
                for(i=0; i<sizeof(atk); i++)
                {
                    if(atk[i]!=killer->query("id")) vmark += atk[i]+",";//统计其它的攻击者
//计算使用PK点数，by xker 2001/4/6---------------------------------------------------------
                    if(exp>14999)
                    {       
                        if(objectp(pker=find_player(atk[i])))
                        {
                            k=(pker->query("combat_exp")-exp)*1.0/(pker->query("combat_exp")+1000);
                            if(k<0) k = 0;
                            pker->add("pk_points", 0-to_int(192*sqrt(k)));
                            pker->save();
                        }
                        else
                        {
                            pker = new(USER_OB);
                            seteuid(atk[i]);
                            export_uid(pker);
                            seteuid(getuid());
                            pker->restore();
                            k=(pker->query("combat_exp")-exp)*1.0/(pker->query("combat_exp")+1000);
                            if(k<0)         k = 0;
                            pker->add("pk_points",0-to_int(192*sqrt(k)));
                            pker->save();
                            destruct(pker);
                        }
                    }
//----------------------------------------------------------------------------------------
                }
                write_file("/log/static/KILL_PLAYER",sprintf("%s(%s)kill%s(%s)in %s on %s(帮凶：%s)\n",
                    killer->name(1),killer->query("id"),victim->name(1), victim->query("id"),environment(victim)->query("short"),ctime(time())[4..23],vmark ));
                killer->apply_condition("killer", 2000);//增一倍通辑时间
                killer->add("PKS", 1);//这是真正的PK！
            }
            else//否则不算，记入另一个文件中
            {
                write_file("/log/static/NOT_PK",sprintf("%s(%s)kill%s(%s)in %s on %s\n",
                killer->name(1),killer->query("id"),victim->name(1), victim->query("id"),environment(victim)->query("short"),ctime(time())[4..23] ));
            }
//------主动攻击end-------by llm about 判断20岁下保护----------
            if(victim->query("age")<20)
            {
                if((time()-(int)victim->query("pk_time"))>86400)//被PK时间过了保护期，重新计时
                    victim->set("pk_time",time());
                else
                {
                    victim->set_temp("newdie",1);//这个记号可以移到非白无常之地
                    return;//直接返回，这就没有损失了
                }
            }
        }
        else //凶手不是玩家
	        log_file("static/PLAYER_DIE",sprintf("%s(%s)kill%s(%s)in %s on %s\n",
                name,killer->query("id"),victim->name(1), victim->query("id"),environment(victim)->query("short"),ctime(time()) ));
        if(!killer->query("quest_npc")
            ||(victim->query("quest_dg/name")!=killer->name(1)
            &&victim->query("quest_wg/quest")!=killer->name(1)
            &&victim->query("quest_df/name")!=killer->name(1)//不是正在执行杀手任务
            ))
        {
            victim->skill_death_penalty();//降武功
            victim->add("combat_exp", -(int)victim->query("combat_exp") / 50);
        }
        else     //kill clone_npc任务时死，不降skill，经验降得少
            victim->add("combat_exp", -(int)victim->query("combat_exp") / 200);
        if(victim->query("jobname")!="武官")
            victim->add("shen", -(int)victim->query("shen") / 10);
        if( victim->query("thief") )
            victim->set("thief", (int)victim->query("thief") / 2);
        if( (int)victim->query("potential") > (int)victim->query("learned_points"))
            victim->add("potential",((int)victim->query("learned_points") - (int)victim->query("potential"))/2 );
    }
    else if( interactive(killer))  //npc被玩家杀，npc被npc杀就不管啦！llm 2001/3/30改有关升降神的判断
    {
		killer->add("MKS", 1);//加MK一次
        if( stringp(vmark = victim->query("vendetta_mark")) )
			killer->add("vendetta/" + vmark, 1);//加仇恨记号，好象好处不大？by llm
		shen = (int)victim->query("shen");//取出被杀者的shen值备用
		if(killer->query("combat_exp") < victim->query("combat_exp"))
		{
	   		if(victim->query("shen") > 0)      //杀死正神NPC
	   		{
	   			if(killer->query("quest_dg/name")!=viticm->name(1)//不是独孤任务
	   				&&killer->query("quest_wg/name")!=viticm->name(1))//不是武官任务
	   		   	killer->add("shen", -(int)victim->query("shen") / 5);//降神
	   		}
    		else
    		{
    			if(killer->query("quest_df/name")!=viticm->name(1)//不是东方杀任务
                    killer->add("shen", -(int)victim->query("shen") / 10);
            }
        }
// 以下是任务中杀人的奖励
		if(mapp(quest = killer->query("quest_df")))    //魔
		{
        	if(quest["desc"] == "灭")
        	{
            	if((quest["name"] == "男子" && victim->query("gender") == "男性" && victim->query("per") >= 25) ||
               		(quest["name"] == "女子") && victim->query("gender") == "女性"||
                	(quest["type"] == "地点" &&  getuid(victim) == quest["dir"]))
            	{
               		if((quest["time"]-time()) < 0)
               		{
                  		killer->delete("quest_df");
                  		return ;
                  	}
               		else if(victim->query("race")=="野兽") return;
               		else
               		{
                  		level = (quest["level"]+1)*(60+random(40));
                  		exp = to_int(sqrt(to_float(victim->query("combat_exp"))));
                  		if(exp > level)   exp = level;
                  		pot = exp/(3+random(5));
                  		killer->add("potential",pot);
                  		killer->add("combat_exp",exp);
                  		tell_object(killer,"[1;37m\n你被奖励了：\n" +
                                  chinese_number(exp) + "点实战经验\n" +
                                  chinese_number(pot) + "点潜能\n\n[2;37;0m");
                        if(shen > 0&&flag) killer->add("shen", -shen/ 5);
                  		return ;
               		}
            	}
         	}
			if(quest["name"]==viticm->name(1)&&flag)
			{
				if(shen > 0) killer->add("shen", -shen/ 5);
				return;
			}   	
		}
		if(mapp(quest = killer->query("quest_dg")))    //侠
		{
        	if(quest["type"] == "杀" && victim->name(1) == quest["name"])
        	{
                if((i=killer->query_temp("questdg_times")) < 2)   i = 10-i;
            	else i = 1;
            	level = quest["level"]+1;
            	exp = level*quest["bonus"]*12/(i*(10+random(5)));
            	pot = level*quest["bonus"]/(3+random(3));
            	exp = exp*130/100;
            	pot = pot*130/100;   //平衡修正
            	killer->add("potential",pot);
            	killer->add("combat_exp",exp);
            	tell_object(killer,"[1;37m\n你被奖励了：\n" +
                            chinese_number(exp) + "点实战经验\n" +
                            chinese_number(pot) + "点潜能\n\n[2;37;0m");
            	killer->add_temp("questdg_times",1);
            	killer->delete("quest_dg");
            	if(shen < 0)
            		killer->add("shen", shen/10);//只加神
            	return ;
         	}
      	}
      	if(mapp(quest = killer->query("quest_wg")))    //军
      	{
			if(quest["type"]=="杀"&&quest["quest"]==victim->name(1))
			{
            	tell_object(killer,"恭喜你！你又为朝廷立了一功！\n");
				i = killer->query_temp("questwg_repeat");
            	if ( i < 2 )
				{
					exp=30+random((killer->query("jobrank")+1))*2;
					score=random((killer->query("jobrank")+1))*4+5;
				}
            	else
            	{
		           	if ( i < 6 ) level = 1;
		           	else if(i < 18 ) level = 2;
		           	else level = 4;
	            	exp=(killer->query("jobrank")+1)*quest["bonus"]*8*level/(10+random(10));
	            	score=((killer->query("jobrank")+1)*6+random(6*(killer->query("jobrank")+1)))*level;
	            }
            	pot = exp/(3+random(3+killer->query("jobrank")));
	         	
    	     	killer->add("combat_exp", exp);
        	 	killer->add("potential",pot);
        		killer->add("score",score);
         		tell_object(killer,HIW"你被奖励了：\n" +
            		chinese_number(exp) + "点实战经验\n"+
         			chinese_number(pot) + "点潜能\n" +
         			chinese_number(score)+"点武官评价。\n"NOR);
       	        killer->add_temp("questwg_repeat",1);
            	killer->set_temp("questwg_giveup_repeat",0);        
	         	killer->delete("quest_wg");
			}
			return;
    	}
    }
}
