// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>
inherit NPC;

int is_bunch_npc() { return 1; }

int init_area_npc(object ob);
int do_join_bunch(object who);

void setup() 
{

        set("bunch/zhengzhao", 1 + random(3));
        ::setup(); 
        call_out("init_area_npc", 1, this_object());

} 
mixed accept_ask(object who, string topic)
{
        if (this_object()->is_quester())
                return QUEST_D->accept_ask(this_object(), who, topic);

        if (! this_object()->is_waiter()
           && (who->query("ultra_quest/next_npc") == this_object()->name()
           || who->query("ultra_quest/npc") == this_object()->name()))
                return ULTRA_D->ask_information(this_object(), who, topic);  
         if ( who->query("xquest/target_npc") == this_object()->name()
           || who->query("xquest/init_npc") == this_object()->name() )
                return XQUEST->accept_ask(this_object(),who, topic);
}

// 回覆任务人物的应酬
int need_accede(object who)
{
        if (! this_object()->is_waiter()
           && who->query("ultra_quest/quest/obj") == this_object()->name()
           && who->query("ultra_quest/next_npc") == this_object()->name())
                return ULTRA_D->need_accede(this_object(), who);
}

int init_area_npc(object ob)
{
        mapping bunch, sk;
        object area;
        int exp, level, i;
        string *ks;
        
        ob = this_object();

        if (! objectp(ob) || ! area = environment(ob)) 
               return 1;
        
        if (! area->is_area_room()) return 0;
        
        this_object()->set("bunch/area_file", base_name(area));
            
        if (! stringp(area->query("bunch/bunch_name"))) 
                return 0;
                
        if (area->query("bunch/npc_file") != base_name(ob))
                return 0;               
        
        bunch = ([ "bunch_name"       : area->query("bunch/bunch_name"),
                   "max_zhongcheng" : 100,
                   "zhongcheng" : area->query("bunch/zhongcheng") ]);
                           
        add("bunch", bunch);

        exp = BUNCH_D->query_bunch_fame(area) / 100;
        level = to_int(pow(to_float(exp), 1.0 / 3)) * 10 + 1;
                
        if (level < 100) level = 100;
        
        if (! mapp(sk = query_skills()))
        {
                set("combat_exp", 1000000 * level);
                set("max_qi", 400 * level);
                set("max_jing", 200 * level);
                set("max_neili", 420 * level);
                set("neili", 420 * level);
                set("level", level / 10);
                set("jiali", 7 * level);

                set_skill("force", level);
                set_skill("parry", level);
                set_skill("dodge", level);
                set_skill("sword", level);
                set_skill("cuff",  level);
                set_skill("strike", level);
                set_skill("huashan-neigong", level);
                set_skill("feiyan-huixiang", level);
                set_skill("huashan-jianfa", level);
                set_skill("hunyuan-zhang", level);
                set_skill("poyu-quan", level);

                map_skill("force", "huashan-neigong");
                map_skill("parry", "huashan-jianfa");
                map_skill("sword", "huashan-jianfa");
                map_skill("dodge", "feiyan-huixiang");
                map_skill("cuff" , "poyu-quan");
                map_skill("strike", "hunyuan-zhang");

                prepare_skill("cuff", "poyu-quan");
                prepare_skill("strike", "hunyuan-zhang");          
                
                return 1;     
        } 
         
        ks = keys(sk);

        for (i = 0; i < sizeof(ks); i++)
                set_skill(ks[i], level);   
        
        return 1;        
}

int accept_object(object who, object ob)
{
        int r; 
        mapping data;
        string  *obj;
        string  stuffid, stuffname;

        if (r = ::accept_object(who, ob))   
                return r;            
        
        if (this_object()->is_quester())
                return QUEST_D->accept_object(this_object(), who, ob);

        if (! this_object()->is_waiter()
           && (who->query("ultra_quest/next_npc") == this_object()->name()
           || who->query("ultra_quest/quest/obj") == this_object()->name()))
                return ULTRA_D->accept_object(this_object(), who, ob); 
         if ( who->query("xquest/target_npc") == this_object()->name()
           || who->query("xquest/init_npc") == this_object()->name() )
                return XQUEST->accept_object( who, ob, this_object() );

        if (who->query("bunch/bunch_name") == query("bunch/bunch_name")) 
        {
                command("say 都是帮中兄弟，何必如此客气？\n");
                return 0;
        }  

/*
        if (base_name(environment(this_object())) != query("bunch/area_file"))
        {
                command("say 我身体有点不适，你有事等我回去再说吧。\n");
                return 0;
        }
*/
                             
                             
        if (query("bunch/zhengzhao") == 1)       
        {
                command("say " + RANK_D->query_self(this_object()) +
                	"只对武功感兴趣，其他一概免谈。\n");
                return 0;
        }        

        if (query("bunch/zhengzhao") == 2)       
        {
                if (query_temp("invite/target") != who) 
                {
                        command("say 无功不受禄，不知" + 
                        	RANK_D->query_respect(who) + "给我" + ob->name() + 
                        	"有何用意？\n");
                        return 0;
		}       
		
                if (! ob->query("money_id"))     
                {
                        command("say " + RANK_D->query_self_rude(this_object()) +
                         	"只对钱有兴趣，你的破玩意自己留着吧。\n");
                        return 0;
                }       

                if (ob->value() < query_temp("invite/money") * 10) 
                {
                        command("say 我不是说过了吗？" +
                        	chinese_number(query_temp("invite/money") / 1000) +
                        	"两黄金，少一下子也不行！\n");
                        return 0;
                }
                
                if (query("bunch/bunch_name") && 
                    query("bunch/zhongcheng") > who->query("meili"))   
                {
                        command("say 若是收了你的钱，我如何对得起帮中其他弟兄？\n");
                        return 0;
                }
                
                return do_join_bunch(who);
        }
        
        if (query("bunch/zhengzhao") == 3)       
        {
                data = query_temp("invite/target");
                
                if (! mapp(data)) data = ([]);
                
                obj = keys(data);
                
                if (member_array(who->query("id"), obj) == -1)        
                {
                        command("say 你我素不相识，为何给" +
                        	RANK_D->query_self(this_object()) + ob->name() +
                        	"？\n");
                        return 0;
                }
                
                sscanf (data[who->query("id")], "%s:%s", stuffid, stuffname);
                
                if (stuffname != ob->query("name") 
                ||  stuffid != ob->query("id"))    
                {
                        command("say " + RANK_D->query_respect(who) +
                        	"，我想要的是" + stuffname + "(" +
                        	stuffid + ")，不是" + ob->query("name") +
                        	"(" + ob->query("id") + ")！\n");
                        return 0;
                }
                
                if (query("bunch/bunch_name") && 
                    query("bunch/zhongcheng") > who->query("meili"))     
                {
                        command("say 若是收了你的东西，我如何对得起帮中其他弟兄？\n");
                        return 0;
                }
                
                return do_join_bunch(who);
        }
}

int do_join_bunch(object who)
{
        string fname, bunch, area;
        
        if (! stringp(bunch = who->query("bunch/bunch_name")))      
        {
                command("say 咦？你没有加入帮会，那我如何加入呢？\n");
                return 0;
        }
        
        if (bunch == query("bunch/bunch_name"))        
        {
                command("say 咱们都是同帮弟兄，有事好商量嘛。\n");
                return 0;
        }
         
        area = base_name(environment(this_object()));
        
/*
       	if (sizeof(children(base_name(this_object()) + ".c")) > 2 ||
       	    area != query("bunch/area_file") ||
            ! environment(this_object())->is_area_room())
       	{
                command("say " + RANK_D->query_self_rude(this_object()) +
                	"身体不适，有事下次再说吧。\n");
                return 0;
        }
*/
        
        if (stringp(fname = query("bunch/bunch_name")))        
                BUNCH_D->remove_area_into_bunch(fname, area, this_object());

        command("say 既然" + RANK_D->query_respect(who) +
                "如此看得起" + RANK_D->query_self(this_object()) +
                "，那我也不能对不起你啊。\n");
        message_vision("$N决定加入帮会「" + bunch + "」！\n",
                this_object());

        BUNCH_D->add_area_into_bunch(bunch, area, this_object());
        
        if (query_temp("invite/target"))
               delete_temp("invite/target");
        
        set("no_clean_up", 1);
                       
        return 1;
}

void die()
{      
        object area; 
        int kaifa;

        area = environment(this_object());
        
        if (! area->is_area_room()) 
                return ::die();
                
        if (base_name(area) != query("bunch/area_file"))
                return ::die();

        if (area->query("bunch/npc_id") != query("id"))
                return ::die();
                 
        if (! stringp(query("bunch/bunch_name")))
                return ::die();                

        kaifa = area->query("bunch/kaifa");
        kaifa = kaifa - (random(10) + 1); 
        
        if (kaifa < 20) kaifa = 20;

        area->set("bunch/kaifa", kaifa);
        area->add("bunch/zhongcheng", -10);
        area->save();

        message("channel:rumor", HIM "【谣言四起】某人：由于" + query("name") + "被杀，" + 
                                 area->short() + "的开发度降为" + kaifa + "！\n" NOR, users());
                
        return ::die();
}
