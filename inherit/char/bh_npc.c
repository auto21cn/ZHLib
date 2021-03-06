// Modified by lonely@yxcs
#include <ansi.h>
inherit NPC;
mapping sites = ([
	"baituo"  :      "欧阳世家",
	"emei"    :      "峨嵋派",
	"wudu"    :      "五毒教",
	"yihua"   :      "移花宫",
	"lingjiu" :      "灵鹫宫",
	"xuedao"  :      "血刀门",
	"xueshan" :      "雪山寺",
	"mingjiao":      "明  教",
	"wudang"  :      "武  当",
	"xingxiu" :      "星宿派",
	"honghua" :      "红花会",
	"hu"      :      "关外胡家",		
	"city2"   :      "天地会",
	"murong"  :      "慕容世家",
	"city"    :      "丐  帮",
	"taohua"  :      "桃花岛",
	"huashan" :      "华山派",
	"kunlun"  :      "昆仑派",
	"shenlong":      "神龙教",
	"shaolin"  :     "少林寺",
	"xiangyang":     "襄阳城",
	"xiaoyao" :      "逍遥派",
	"quanzhen":      "全真派",
	"lingxiao":      "灵宵城",
]);

void setup() 
{

        set("zhengzhao",1 + random(3));
        ::setup(); 
        call_out("init_npc", 0, this_object()); 
} 

void init_npc(object ob)
{
        string area_file;
        object area;

        if (! objectp(ob) || ! environment(ob)) return;
        set("max_zhongcheng", 90 + random(10)); 
        set("zhongcheng", 11 + random(21));

        area_file = domain_file(base_name(environment(ob)));
        if( stringp(area_file) && member_array(area_file,keys(sites))!=-1 )
        {
            ob->set("area",sites[area_file]);
            ob->set("area_file",base_name(environment(ob)));
            area=new("/clone/misc/area1");
            area->create(sites[area_file]);
            if( area->query("banghui") )
            {    
                set("no_clean_up",1);
                set("banghui",area->query("banghui"));
                set("zhongcheng",area->query("zhongcheng"));
            }
            set("kaifa",area->query("kaifa"));
            set("jizhi",area->query("jizhi"));
            destruct(area);            
        }
        return;
}

int do_jiaru(object target);
// this function is used to improve NPC's zhongcheng
// and to hire these NPC
int accept_object(object target,object obj)
{
        mapping data;
        string *who;
        string stuffid,stuffname;
        if(! query("zhengzhao"))        return 0;
        if(! target->query("banghui"))  {
                command("say 即然"+RANK_D->query_respect(target)
                +"如此客气，那我就收下了。\n");
                return 1;
        }
        if( target->query("banghui")==(string)this_object()->query("banghui")) {
                command("say 都是帮中兄弟，何必如此客气？\n");
                return 0;
        }
        if(query("zhengzhao")==1)       {
                command("say "+RANK_D->query_self(this_object())
                +"只对武功感兴趣，其他一概免谈。\n");
                return 0;
        }
    else
        if(query("zhengzhao")==2)       {
                if(query_temp("lonely/target")!=target) {
                        command("say 无功不受禄，不知"+RANK_D->query_respect(target)+"给我"+obj->query("name")+"有何用意？\n");

                        return 0;

                }
                if(!obj->query("money_id"))     {
                        command("say "+RANK_D->query_self_rude(this_object())
                        +"只对钱有兴趣，你的破玩意自己留着吧。\n");
                        return 0;
                }
                if(obj->value()<query_temp("money")*10) {
                        command("say 我不是说过了吗？"+
                        chinese_number(query_temp("money")/1000)
                        +"两黄金，少一下子也不行！\n");
                        return 0;
                }
                if(query("banghui")&&query("zhongcheng")>target->query_per())   {
                        command("say 若是收了你的钱，我如何对得起帮中其他弟兄？\n");
                        return 0;
                }
                return do_jiaru(target);
        }
    else
        if(query("zhengzhao")==3)       {
                data=query_temp("lonely/target");
                if(! mapp(data))        data=([]);
                who=keys(data);
                if(member_array(target->query("id"),who)==-1)        {
                        command("say 你我素不相识，为何给"+
                        RANK_D->query_self(this_object())+obj->query("name")+
                        "？\n");
                        return 0;
                }
                sscanf(data[target->query("id")],"%s:%s",stuffid,stuffname);
                if(stuffname != obj->query("name") ||
                        stuffid != obj->query("id"))    {
                        command("say "+RANK_D->query_respect(target)+
                        "，我想要的是"+stuffname+"("+
                        stuffid+")，不是"+obj->query("name")+
                        "("+obj->query("id")+")！\n");
                        return 0;
                }
                if(query("banghui")&&query("zhongcheng")>target->query_per())   {
                        command("say 若是收了你的东西，我如何对得起帮中其他弟兄？\n");
                        return 0;
                }
                return do_jiaru(target);
        }
}



int do_jiaru(object target)
{
        object lp_me,lp_target;
        object area;
        string bh_me,bh_target;
        mapping data;
        if(! (bh_target=target->query("banghui")))      {
                command("say 咦？你没有加入帮会，那我如何加入呢？\n");
                return 0;
        }
        if( bh_target==query("banghui"))        {
                command("say 咱们都是同帮弟兄，有事好商量嘛。\n");
                return 0;
        }
        if( sizeof(children(base_name(this_object())+".c")) > 2 || base_name(environment(this_object())) != query("area_file") ) {
                command("say "+RANK_D->query_self_rude(this_object())+
                "身体不适，有事下次再说吧。\n");
                return 0;
        }
        lp_target=new("/clone/misc/lingpai");
        lp_target->create(bh_target);
        if(lp_target->query("no_use"))  {
                destruct(lp_target);
                command("say 你的帮会文件有问题，快与巫师联系吧。\n");
                return 0;
        }
        data=lp_target->query("npc");
        if(! mapp(data))        data=([]);
        data+=([query("id"):query("name")]);
        lp_target->set("npc",data);
//        lp_target->save();
       if(!undefinedp(target->query("lonely_quest"))
        && target->query("lonely_quest/type")==4)       {
        target->set("lonely_quest/over",1);
        target->add("bunch/quest",1);
        tell_object(target,"你的任务已经完成，快回去交差吧。\n");
        }
       if( query("area") && query("area_file") )
        {
            data=lp_target->query("area");
            if(!mapp(data)) data=([]);
            data += ([query("area"):query("area_file")]);
            lp_target->set("area",data);

           area=new("/clone/misc/area1");
            area->create(query("area"));
            area->set("banghui",bh_target);
            area->set("npc",this_object()->query("id"));
            area->set("npc_room",base_name(environment(this_object())));
            if( query("kaifa") && query("jizhi") )
            {
                area->set("kaifa",query("kaifa") );
                area->set("jizhi",query("jizhi") );
            }
            area->save();
            destruct(area);
        }
        lp_target->save();
        destruct(lp_target);
        if((bh_me=query("banghui")))    {
                lp_me=new("/clone/misc/lingpai");
                lp_me->create(bh_me);
                if(! lp_me->query("no_use"))    {
              if( query("area") && query("area_file") )
              {
                  data=lp_me->query("area");
                  if(! mapp(data)) data=([]);
                  map_delete(data,query("area"));
                  lp_me->set("area",data);
                  data=lp_me->query("npc");
                  if(! mapp(data)) data=([]);
                  map_delete(data,query("id"));
                  lp_me->set("npc",data); 

                  lp_me->save();
                  destruct(lp_me);
              }
             }
        }
        set("banghui",bh_target);
        add("zhongcheng",(query("max_zhongcheng")-query("zhongcheng"))*10/100);
        set("no_clean_up",1);
        if( query_temp("lonely/target"))
               delete_temp("lonely/target");
        command("say 既然"+RANK_D->query_respect(target)+
                "如此看得起"+RANK_D->query_self(this_object())+
                "，那我也不能对不起你啊。\n");
        message_vision("$N决定加入帮会「"+target->query("banghui")+"」！\n",
                this_object());
        message("channel:rumor",YEL"【谣言四起】某人："+query("name")+
        "加入帮会「"+bh_target+"」！\n"NOR,users());
        if( query("area") && query("area_file"))
        message("channel:rumor",YEL"【谣言四起】某人："+query("area")+
        "被帮会「"+bh_target+"」吞并！\n"NOR,users());

        return 1;
}

void die()
{
        int kaifa;
        int kf;
        string banghui;
        object area;

        if(base_name(environment(this_object())) != query("area_file"))
        return ::die();

        if(! stringp(banghui=query("banghui")))
        return ::die();

        area=new("/clone/misc/area1");
        area->create(query("area"));
        if(area->query("no_use"))
        {
                destruct(area);
                return ::die();
        }

        kaifa=area->query("kaifa");
        kf=query("kaifa");
        if( kf==kaifa)
        {
                destruct(area);
                return ::die();
        }

        kaifa=kaifa-(random(10)+1);
        if(kaifa<=kf) kaifa=kf;

        area->set("kaifa",kaifa);
        area->save();
        destruct(area);

        message("channel:rumor",
                YEL"【谣言四起】某人：由于"+query("name")+
                "被杀，"+query("area")+"的开发度降为"+kaifa
                +"！\n"NOR,users());
        return ::die();
}
