//长安府任务发放者

#include <ansi.h>
inherit NPC;

#define NPC_FILE    __DIR__"npc"     //定义NPC数据库文件路径
#define PLACE_FILE  __DIR__"place"  //定义地点数据库文件路径

int ask_quest();
void whisper(object me, object ob);
void hunt(object me, object ob);
void patrol(object me, object ob);
string set_npc();
string set_place();
int job_ok();
int ask_cancel();
void reward(object me);
void item_reward(object me);

void create()
{
	set_name("梁兴禄", ({ "liang xinglu", "liang" }));
	set("title", "长安知府");
	set("gender", "男性");
	set("age", 43);
	set("str", 20);
	set("dex", 20);
	set("long", "长安城现任知府。\n");
	set("combat_exp", 50000);
	set("shen_type", 0);
	set("attitude", "heroism");
	set_skill("unarmed", 60);
	set_skill("force", 60);
	set_skill("sword", 60);
	set_skill("dodge", 60);
	set_skill("parry", 60);
	set_temp("apply/attack", 50);
	set_temp("apply/defense", 50);
	set_temp("apply/armor", 50);
	set_temp("apply/damage", 15);
	set("neili", 500); 
	set("max_neili", 500);
	set("jiali", 20);
       set("inquiry", ([                     
                       "任务"      : (: ask_quest :),
                       "工作"      : (: ask_quest :),
                       "quest"     : (: ask_quest :),
                       "完成"      : (: job_ok :),
                       "复命"      : (: job_ok :),
                       "取消"      : (: ask_cancel :),
                       "取消任务"  : (: ask_cancel :),
                       "cancel"   : (: ask_cancel :),
        ]));
	setup();
	carry_object("/d/changan/npc/obj/sword")->wield();
	carry_object("/d/changan/npc/obj/choupao")->wear();
}

//问线索，随机抽取任务
int ask_quest()
{      
   object me, ob;
   int exp;
   me = this_player();
   ob = this_object();
   exp = me->query("combat_exp");

   if ( me->query("changanjob") )
   {
         message_vision(HIC "$N" HIC "对$n说道：本府不是已经给你派发了差事，"
                        "完不成的话就先跟我取消。\n"NOR, ob, me);
         return 1;
   }
   if ( me->query("combat_exp") > 800000 )
   {
         message_vision(HIC "$N" HIC "对$n说道：你的江湖经验已经很高了，再在"
                        "衙门里也混不出个名堂了。\n"NOR, ob, me);
         return 1;
   }
   
   if ( time() - me->query("changanjob_last_cancel") < 60 )
   {
         message_vision(CYN "$N" CYN "盯着$n看了看，说道：“你刚取消过一次任务，"
                            "过一分钟再来吧。”\n"NOR, ob, me);
                        return 1;
    } else 
    me->delete("changanjob_last_cancel");

    if ( time() - me->query("cajb_total_ask/time") > 3600 * 24 )
    {
                me->delete("cajb_total_ask");
                me->set("cajb_total_ask/time", time());
    }
    else
    {
      if ( me->query("cajb_total_ask/total") >= 600 )             
      {
            message_vision(CYN "$N" CYN "盯着$n看了看，说道：“对不起，24小时内"
                            "只能领取600个任务！”\n"NOR,
                            ob, me);
                        return 1;
       }
    }

   me->add("cajb_total_ask/total", 1);

   message_vision(HIC "$N" HIC "对$n说道：嗯，既然你有心为衙门出力，我便给"
                  "你个差事。\n"NOR, ob, me);
   if ( exp >= 100000 )
   {
       switch(random(3))
        {    
         case 0 :
                 me->start_busy(2);                
                 call_other(__FILE__, "whisper", me, ob);
                 return 1;
         case 1 :             
                 me->start_busy(2);                
                 call_other(__FILE__, "patrol", me, ob);
                 return 1;                 
         case 2 :                              
                 me->start_busy(2);                  
                 call_other(__FILE__, "hunt", me, ob);  
                 return 1;                                
         default:
                 me->start_busy(2);               
                 call_other(__FILE__, "whisper", me, ob);
                 return 1;
        }
    } else
    if ( exp >= 50000 )
   {
       switch(random(2))
        {    
         case 0 :
                 me->start_busy(2);                
                 call_other(__FILE__, "whisper", me, ob);
                 return 1;
         case 1 :              
                 me->start_busy(2);                
                 call_other(__FILE__, "patrol", me, ob); 
                 return 1;                                                
         default:
                 me->start_busy(2);               
                 call_other(__FILE__, "whisper", me, ob);
                 return 1;
        }
    } else
    call_other(__FILE__, "whisper", me, ob);
    return 1;
}

void whisper(object me, object ob)
{
    string *wd, word;
    string npc, place, name, space;
    space = "                                                      ";
      
   wd = ({ "龙腾","虎跃","自强","栋梁","上进","不屈","不挠","安分","守己",
           "相助","互助","安家","立业","尊师","重道","创造","辉煌","正大",
           "光明","磊落","勇往","直前","尽善","尽美","果断","精诚","团结",
           "从容","精妙","汗马","功劳","发愤","图强","精益","求精","胆大",
           "心细","救死","扶伤","才华","翻天","覆地","百战","百胜","妙手",
           "回春","弘扬","正气","灿烂","辉煌","沧海","桑田","聚精","会神",
           "腾达","慷慨","名正","言顺","鼓舞","奋发","图强","丰功","伟绩",
           "必胜","信心","奉公","守法","道义","宏图","扶老","携幼","秉公",
           "惩腐","倡廉","惩恶","扬善","博大","精深","博学","诚实","守信",
           "诚意","德才","耐劳","坚强","坚韧","廉洁","奉公","守法","齐心",
           "协力","传统","美德","文明","礼貌","谦虚","奉献","爱岗","敬业",
           "爱心","和睦","安定","强国","勤奋","好学","求知","刻苦","聪明",
           "伶俐","敏锐","坚韧","挺拔","坚强","保家","为国","善良","除暴",
           "安良","孝顺","大度","大义","诚恳","诚实","真诚","信义","重情",
           "慈悲","追求","理想","无私","为国","为民","创新","敬仰","铁骨",
           "英明","谦恭","拼搏","鞠躬","尽瘁","呕心","沥血","安居","乐业",
           "真理","信念","振奋","振兴","忠诚","坦荡","洁身","自爱","勤俭",
           "宽容","忍让","谅解","谦卑","豪杰","无畏","攀登","探索","实践",
           "求实","活跃","毅力","坚毅","谨慎","图强","公正","严明","诚信",
           "求精","国富","民强","君子","杀敌","保家","为国","忠君","爱民",
           "扶弱","济贫","开拓","进取","求实","奋进","仁义","礼智","善德", 
           "立志","忠孝","敬老","爱幼","助人", });  

     word = wd[random(sizeof(wd))];

     npc = call_other(__FILE__, "set_npc");
     sscanf(npc, "%s/%s", place, name);

     if ( name == 0 || name == "" )
       {
            call_other(__FILE__,"whisper", me, ob);
            return;
       }  
     else
       {
            me->set("changanjob/kind", "whisper");                 
            me->set("changanjob/whisper", word);
            me->set("changanjob/place", place);
            me->set("changanjob/target", name);
            me->set("changanjob/time", time());

        //    if ( random(2) == 1 )
       //     word = word[0..1] + space[0..0] + word[2..3]; 
        /*  tell_object(me, WHT + ob->name() + "悄悄在你耳边说道：“" +
                     "其实"NOR HIG + place + WHT"的"HIG + name + NOR WHT"是"
                     "我门衙门派在黑社会的卧底，\n你帮我把这个月的接头暗号去告诉他。"
                     "暗号是：\n\n" + TEXT2PIC_D->Display(word) + "\n\n"WHT + 
                     "速去速回，不得有误！”\n"NOR); */ 
           word = space[0..random(20)] + word[0..1] + "\n\n" + 
                  space[0..random(20)] + word[2..3];

          tell_object(me, WHT + ob->name() + "悄悄在你耳边说道：“" +
                     "其实"NOR HIG + place + WHT"的"HIG + name + NOR WHT"是"
                     "我门衙门派在黑社会的卧底，\n你帮我把这个月的接头暗号去告诉他。"
                     "暗号是：\n\n" + word + "\n\n"WHT + "速去速回，不得有误！”\n"NOR);      
       }	
} 

string set_npc()
{
         string file, *lines, npc;

         file = read_file(NPC_FILE);
         lines = explode(file, "\n");
         npc = lines[random(sizeof(lines))];
         return npc;

 }

void patrol(object me, object ob)
{  
     string place, place1, place2;
     object gh;
     int i;

     message_vision(HIW "$N" HIW "说着便拿出一份公函交给$n。\n"NOR, ob, me);
     
     for( i=0; i < 5; i++ ) 
   	 {
    		 place = call_other(__FILE__, "set_place");
  		 sscanf(place, "%s/%s", place1, place2);

  		 if ( place2 == 0 || place2 == "" )
              {
                 call_other(__FILE__,"patrol", me, ob);
                 return;            
              }  
               else
              {
                 me->set("changanjob/place/"+ (i+1), place2);
              }
        }   

     me->set("changanjob/kind", "patrol");             
     me->set("changanjob/time", time());     
     gh = new(__DIR__"gonghan1");  
     for( i=0; i < 5; i++ )
        {
           gh->set("place/" + (i+1), me->query("changanjob/place/" + (i+1)));
        } 
     gh->set("owner", me->name());
     gh->move(me);
     me->set("changanjob/gonghan",gh);
}


void hunt(object me, object ob)
{  
     string place, place1, place2;
     object gh;

     place = call_other(__FILE__, "set_place");
     sscanf(place, "%s/%s", place1, place2);

     if ( place2 == 0 || place2 == "" )
       {
            call_other(__FILE__,"hunt", me, ob);
            return;
       }  
     else
       {    
            message_vision(HIW "$N" HIW "说着便拿出一份公函交给$n。\n"NOR, ob, me);
               gh = new(__DIR__"gonghan2");
               gh->set("owner", me->name());
               gh->set("place", place2);
               gh->move(me);

               me->set("changanjob/kind", "hunt");             
               me->set("changanjob/time", time());
               me->set("changanjob/place", place2);
               me->set("changanjob/gonghan",gh);

        }
}

string set_place()
{
         string file, *lines, where;

         file = read_file(PLACE_FILE);
         lines = explode(file, "\n");
         where = lines[random(sizeof(lines))];

         return where;

}


int job_ok()
{
	object me, ob, dz;
       int exp, pot, tihui, score, weiwang;
       string msg;
       me = this_player();
       ob = this_object();
       msg = "";

       if ( ! me->query("changanjob") ) 
       {
          message_vision(HIR"$N"HIR"对$n道：大胆刁民，本府何时给过你差事？\n"
                          NOR, ob, me); 
          return 1;
       }

       if ( time() - me->query("changanjob/time") > 600 )
       {		
           message_vision(HIR "$N" HIR "对$n大怒道：你怎么这么晚才来复命，办事效率太差了。\n" 
                           NOR, ob, me); 
          
          tell_object( me, CYN"\n这个任务由于你拖得太久，无法完成了，请取消吧。\n"NOR);
          return 1;
       }


       switch( me->query("changanjob/kind") )
        {    
        case "whisper" :
                me->start_busy(2);   
                if ( me->query("changanjob/whisper") )
                {
                   message_vision(HIR"$N"HIR"对$n大怒道：你都还没去传过口令，来复什么命！\n" 
                                  NOR, ob, me);
                   return 1;                    
                }
                if ( me->query("changanjob/ok") )
                {   
                    call_other(__FILE__,"reward", me);                   
                }      
                else
                {	
                   message_vision(HIR"$N"HIR"对$n大怒道：哼，你居然还有脸来复命！叫你" 
                           "传个暗语都传错，\n害得我们辛苦派去的卧底被自己人误杀了，"
                           "你奶奶个熊的！\n"NOR, ob, me);
                   tell_object(me, CYN"\n很不幸，这次任务你失败了，请取消吧。\n"NOR);
                }         
                return 1;
        case "patrol" :
                me->start_busy(2);   
                dz = me->query("changanjob/catch");
                if ( dz && objectp(present(dz->query("id"), environment(me))) )    
                {                    
                   message_vision(HIW"$N对$n大喜道：嗯，不错，这次抓来盗贼你功不可没，"
                                  "本府要给你赏赐。\n随即$N大喝一声：来人，速速将捉来的盗贼押下收监。\n"NOR
                                  HIY"\n只见几名衙役将" + dz->name() +  "押去了大牢。\n\n"NOR, ob, me);
                   GIFT_D->bonus(me, ([ "prompt" : "通过这次捉拿" + dz->name() +
                                                    HIG "的经历",
                                        "exp"    : random(100) + 200,
                                        "pot"    : random(100) + 100,
                                        "mar"    : random(30) + 30,
                                        "score"  : random(10) + 10, 
                                        "weiwang"  : random(10) + 10, ]), 1);                  
                   destruct(dz);
                   me->delete("changanjob/catch"); 
                } 
                message_vision(HIY"\n$N对$n道：公函中规定要巡逻的地点都已去过的话可将公函呈上来。\n"
                               NOR, ob, me);
                return 1;
        case "hunt" :
                me->start_busy(2);                
                if ( ! me->query("changanjob/ok") )    
                {      
                   message_vision(HIR"$N"HIR"对$n大怒道：你去剿杀过动物了吗?"
                   "不要企图蒙骗本府！\n"NOR, ob, me);
                   return 1;
                } else
                {
		     message_vision(HIY"\n$N对$n道：若已剿杀过动物便将公函呈上来，本府即刻予你赏赐。\n"
                               NOR, ob, me);
                 }
               return 1;
        } 
}

int ask_cancel()
{
	object me, ob;
       int score, weiwang;
       string msg;
       me = this_player();
       ob = this_object();       

       if ( ! me->query("changanjob") ) 
       {
          message_vision(HIR"$N"HIR"对$n道：大胆刁民，本府何时给过你差事？\n"
                          NOR, ob, me); 
          return 1;
       }
        //如果捉了贼的销毁掉
        if ( me->query("changanjob/catch") && 
             objectp(me->query("changanjob/catch"))  )
        destruct(me->query("changanjob/catch"));       
       // 上一份公函还在的话也销毁掉
        if ( me->query("changanjob/gonghan") && 
             objectp(me->query("changanjob/gonghan"))  )
        destruct(me->query("changanjob/gonghan"));    

         me->delete("changanjob");
         me->delete("changanjob_count");
         me->set("changanjob_last_cancel", time() );
         message_vision(HIY"$N"HIY"对$n道：这点小事都办不好，你可太没用了。\n"
                          NOR, ob, me); 
         tell_object(me, HIR"你的本次长安府任务取消了！\n"NOR);
        if ( me->query("weiwang") > 10000 && me->query("score") > 10000 )
        {
           me->add("weiwang", -100);
           me->add("score", -100);

           tell_object(me, HIR"\n你的阅历和江湖威望受到了一定损失！\n"NOR);
        }
         return 1;
}

int accept_object(object me, object ob)
{    
     int i, flag; 
     object dz;    
     flag = 1;

     if ( ob != me->query("changanjob/gonghan") )
     {  command("say 大胆刁民，你拿这个东西来莫非是想戏弄本府？"); 
        return 0; 
     }
     if ( ! me->query("changanjob") )
     {  command("say 本府何时给过你差事？"); 
        return 0; 
     }     
     if ( time() - me->query("changanjob/time") > 600 )
     {		
          message_vision(HIR"$N""对$n大怒道：公函本府收回了，但是你这么晚才来复命，本府不予赏赐。\n" 
                           NOR, this_object(), me);           
          me->delete("changanjob");          
          destruct(ob);
          return 1;
      }
      dz = me->query("changanjob/catch");
      if ( dz && objectp(present(dz->query("id"), environment(me))) )    
         {                    
             message_vision(HIW"$N对$n大喜道：嗯，不错，这次抓来盗贼你功不可没，"
                            "本府要给你赏赐。\n随即$N大喝一声：来人，速速将捉来的盗贼押下收监。\n"NOR
                            HIY"\n只见几名衙役将" + dz->name() +  "押去了大牢。\n\n"NOR, ob, me);
                   GIFT_D->bonus(me, ([ "prompt" : "通过这次捉拿" + dz->name() +
                                                    HIG "的经历",
                                        "exp"    : random(100) + 300,
                                        "pot"    : random(100) + 200,
                                        "mar"    : random(30) + 30,
                                        "score"  : random(10) + 10, 
                                        "weiwang"  : random(10) + 10, ]), 1);                  
                   destruct(dz);
                   me->delete("changanjob/catch"); 
          } 

     if ( me->query("changanjob/kind") == "patrol" )
     { 
        for( i=0; i < 5; i++ )
           {
             if ( ! ob->query("placeok/" + (i+1)) ) flag = 0;
           } 
        if ( flag == 0 )
           {
              message_vision(HIR"$N""对$n大怒道：公函上的记录显示你尚有地点未去巡查过，"
                             "岂可如此怠慢！\n" NOR, this_object(), me); 
              return 0;
           }
     } 
    call_other(__FILE__,"reward", me);
    destruct(ob);
    return 1;

} 

void reward(object me)
{                
        string msg;   
        object ob, pay; 
        int exp, pot, tihui, score,  weiwang;

        ob = this_object();

        exp = random(100) + 400;
        pot = random(100) + 300;                           
        score = random(20) + 30;
        weiwang = random(20) + 30; 

        if ( me->query("changanjob/kind") == "whisper" )
        {            
           if ( me->query("combat_exp") > 100000 )
           {
              exp = exp / 2;
              pot = pot / 2;
           }    
        } else
          tihui = 50 + random(50); 

        if ( me->query("changanjob/kind") == "patrol" )
        {
           exp = exp * 3;
           pot = pot * 3;
        }
        me->delete("changanjob");
        me->add("changanjob_count",1);   //累计完成数量增加一个
        if ( me->query("changanjob_count") > 500 )
        { me->set("changanjob_count",1); }     //累计超过500则变1

    /*    if ( me->query("changanjob_count") > 0 && 
             me->query("changanjob_count") % 10 == 0 )   //每完成10个奖励1.5倍
        {
            exp = exp * 3 / 2;
            pot = pot * 3 / 2;
            tihui = tihui * 3 / 2;
        } */

        if ( me->query("potential") >= me->query_potential_limit() )
        {  pot = 1; }
        if ( me->query("experience") >= me->query_experience_limit() && tihui > 0)
        {  tihui = 1; }       

        tell_object(me, HIC + ob->name() + "对你道：嗯，这次任务完成得不错，" 
                       "本府现下便给你赏赐。\n"NOR + HIW"你获得了赏银二十两。\n"NOR); 
        message("vision", HIC + ob->name() + "对" + me->name() +
                 "道：嗯，这次任务完成得不错，本府现下便给你赏赐。\n" NOR HIW 
                 + me->name() + "获得了赏银二十两。\n"NOR, environment(me), ({me})); 

        me->add("combat_exp", exp );
        me->add("potential", pot );
        me->add("experience", tihui);

        if ( me->query("gongxian") < 2000 )
            me->add("gongxian", 4+random(3));

        me->add("score", score);
        me->add("weiwang", weiwang);  
        pay = new("/clone/money/silver");
        pay->set_amount(20);
        pay->move(me, 1);         
        
        msg = HIG"\n通过这次锻炼，\n你获得了"NOR HIR + chinese_number(exp) + 
                   HIG"点经验，"NOR HIW + chinese_number(pot) + NOR HIG"点潜能，";
        if (tihui > 0) 
             msg += "以及"HIY + chinese_number(tihui) + HIG"点实战体会。"NOR;            
             msg += HIW"\n门派贡献、江湖阅历以及威望也都有了不同程度的提高。\n" NOR;
        tell_object( me, msg); 

   //    if ( me->query("changanjob_count") % 50 == 0 )  //每完成五十个任务给予item奖励
   //    call_other(__FILE__,"item_reward", me); 

}

void item_reward(object me)
{                
     /*   // 完成三十个任务
        string *ob2_list = ({
                "/clone/fam/pill/puti2",
                "/clone/fam/pill/sheli2",
                "/clone/fam/pill/linghui2",
                "/clone/fam/pill/food1",
                "/clone/fam/pill/neili2",
        });
        // 完成五十个任务
        string *ob3_list = ({
                "/clone/fam/pill/puti3",
                "/clone/fam/pill/sheli3",
                            "/clone/gift/cdiamond",
                            "/clone/gift/cagate",
                            "/clone/gift/ccrystal",
                            "/clone/gift/cjade", 
        }); */
        // 完成五十个任务
        string *ob4_list = ({
                "/clone/fam/pill/puti4",
                "/clone/fam/pill/sheli4",
                "/clone/fam/gift/str1",
                "/clone/fam/gift/int1",
                "/clone/fam/gift/con1",
                "/clone/fam/gift/dex1",
                "/clone/fam/item/handan",
                "/clone/fam/item/bixue",
                "/clone/fam/item/zijin",
                "/clone/fam/item/wujin",
                "/clone/fam/item/taijin",
                "/clone/fam/pill/renshen1",
                "/clone/fam/pill/lingzhi1",
                "/clone/fam/pill/xuelian1",
        });
        // 完成一百个任务
        string *ob5_list = ({
                "/clone/fam/etc/lv5a",
                "/clone/fam/etc/lv5b",
                "/clone/fam/etc/lv5c",
                "/clone/fam/etc/lv5d",
                "/clone/fam/etc/lv5e",
                "/clone/fam/pill/renshen2",
                "/clone/fam/pill/lingzhi2",
                "/clone/fam/pill/xuelian2",
        });
        // 完成一百五十个任务
        string *ob6_list = ({
                "/clone/fam/gift/str2",
                "/clone/fam/gift/int2",
                "/clone/fam/gift/con2",
                "/clone/fam/gift/dex2",
                "/clone/fam/pill/renshen3",
                "/clone/fam/pill/lingzhi3",
                "/clone/fam/pill/xuelian3",
                "/clone/fam/item/zhenlong",
                "/clone/fam/item/jiulei",
                "/clone/fam/item/panlong",
        });
        // 完成两百个任务
        string *ob7_list = ({
                "/clone/tattoo/buttock1",
                "/clone/tattoo/buttock2",
                "/clone/tattoo/buttock3",
                "/clone/tattoo/buttock4",
                "/clone/tattoo/buttock5",
                "/clone/tattoo/buttock6",
                "/clone/tattoo/buttock7",
                "/clone/tattoo/buttock8",
        });
        // 完成两百五十个任务
        string *ob8_list = ({
                "/clone/fam/gift/str2",
                "/clone/fam/gift/int2",
                "/clone/fam/gift/con2",
                "/clone/fam/gift/dex2",
                "/clone/fam/pill/renshen3",
                "/clone/fam/pill/lingzhi3",
                "/clone/fam/pill/xuelian3",
                "/clone/fam/etc/lv7a",
                "/clone/fam/etc/lv7b",
                "/clone/fam/etc/lv7c",
                "/clone/fam/etc/lv7d",
        });
        // 完成三百个任务
        string *ob9_list = ({
                "/clone/tattoo/body1",
                "/clone/tattoo/body2",
                "/clone/tattoo/body3",
                "/clone/tattoo/body4",
                "/clone/tattoo/body5",
                "/clone/tattoo/body6",
                "/clone/tattoo/body7",
                "/clone/tattoo/body8",
                "/clone/tattoo/body9",
                "/clone/tattoo/body10",
        });
        // 完成三百五十个任务
        string *ob10_list = ({
                "/clone/fam/pill/yulu",
                "/clone/fam/pill/dimai",
                "/clone/fam/pill/renshen4",
                "/clone/fam/pill/lingzhi4",
                "/clone/fam/pill/xuelian4",
                "/clone/fam/item/baxian",
                "/clone/fam/item/kunlun",
                "/clone/fam/item/haoyue",
                "/clone/fam/item/leihuo",
                "/clone/fam/item/yinzhu",
        });
        // 完成四百个任务
        string *ob11_list = ({
                "/clone/tattoo/spcs1",
                "/clone/tattoo/spcs2",
                "/clone/tattoo/spcs3",
                "/clone/tattoo/spcs4",
                "/clone/tattoo/spcs5",
                "/clone/tattoo/spcs6",
                "/clone/tattoo/spcs7",
                "/clone/tattoo/spcs8",
                "/clone/tattoo/spcs9",
                "/clone/tattoo/spcs10",
        });
        // 完成四百五十个任务
        string *ob12_list = ({
                "/clone/fam/skpaper/blade1",
                "/clone/fam/skpaper/claw1",
                "/clone/fam/skpaper/club1",
                "/clone/fam/skpaper/cuff1",
                "/clone/fam/skpaper/dagger1",
                "/clone/fam/skpaper/finger1",
                "/clone/fam/skpaper/hammer1",
                "/clone/fam/skpaper/hand1",
                "/clone/fam/skpaper/parry1",
                "/clone/fam/skpaper/staff1",
                "/clone/fam/skpaper/strike1",
                "/clone/fam/skpaper/sword1",
                "/clone/fam/skpaper/throwing1",
                "/clone/fam/skpaper/unarmed1",
                "/clone/fam/skpaper/whip1",                
        });
        // 完成五百个任务
        string *ob13_list = ({
                "/clone/fam/gift/str3",
                "/clone/fam/gift/int3",
                "/clone/fam/gift/con3",
                "/clone/fam/gift/dex3",
                "/clone/fam/item/yanluo",
                "/clone/fam/item/lihuo",
                "/u/sanben/obj/fig", 
        });
        string un, gift;
        object ob;

        if (me->query("changanjob_count") == 500)
        {
                gift = ob13_list[random(sizeof(ob13_list))];                
        } else
        if (me->query("changanjob_count") == 450)
        {
                gift = ob12_list[random(sizeof(ob12_list))];                
        } else
        if (me->query("changanjob_count") == 400)
        {
                gift = ob11_list[random(sizeof(ob11_list))];                
        } else
        if (me->query("changanjob_count") == 350)
        {
                gift = ob10_list[random(sizeof(ob10_list))];                
        } else
        if (me->query("changanjob_count") == 300)
        {
                gift = ob9_list[random(sizeof(ob9_list))];                
        } else
        if (me->query("changanjob_count") == 250)
        {
                gift = ob8_list[random(sizeof(ob8_list))];                
        } else
        if (me->query("changanjob_count") == 200)
        {
                gift = ob7_list[random(sizeof(ob7_list))];                
        } else
        if (me->query("changanjob_count") == 150)
        {
                gift = ob6_list[random(sizeof(ob6_list))];                
        } else
        if (me->query("changanjob_count") == 100)
        {
                gift = ob5_list[random(sizeof(ob5_list))];                
        } else
        if (me->query("changanjob_count") == 50)
        {
                gift = ob4_list[random(sizeof(ob4_list))];                
        }  /*else
        if (me->query("changanjob_count") == 50)
        {
                gift = ob3_list[random(sizeof(ob3_list))];                
        } else
        if (me->query("changanjob_count") == 30)
        {
                gift = ob2_list[random(sizeof(ob2_list))];               
        }  */

        ob = new(gift);
        ob->move(me);

        if (ob->query("base_unit"))
                un = ob->query("base_unit");
        else
                un = ob->query("unit");
   
        message("vision", HIC + this_object()->name() + "对" + me->name() +
                 "道：此次本府额外赏赐你一" + un + NOR + ob->name() +NOR
                 HIC"，以资鼓励。\n\n"NOR, environment(me), ({me})); 

        tell_object(me, HIC + this_object()->name() + "对你道：此次本府额外赏赐你一" 
                    + un + NOR + ob->name() +NOR HIC"，以资鼓励。\n\n"NOR  
                    HIG"你获得了一" + un + NOR + ob->name() + NOR HIG"。\n"NOR);
      
}


