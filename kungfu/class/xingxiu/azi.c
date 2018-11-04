//write by rama@sz, 28/02/2002
//Modified by Dumbness, 2003-6-9 21:38

#include <ansi.h>

inherit NPC;

int ask_ding(object me);
int do_sou(string arg);

void create()
{
        set_name("阿紫", ({ "a zi" }) );
        set("title","星宿派小师妹");        
        set("gender", "女性" );
        set("long","一位貌美如花的小姑娘，但是眼睛里面似乎透漏着一股邪气。\n");
        set("age",18);
        set("attitude", "peaceful");  
        set("shen_type", -1);  
        set("str", 18);  
        set("int", 28);  
        set("con", 20);  
        set("dex", 24);  
        set("eff_qi", 8000);  
        set("max_qi",8000); 
        set("neili", 10000);
        set("max_neili", 10000);  
        set("jiali", 100);  
        set("shen", 10000);  
        set("combat_exp", 1000000);  
        set("score", 10000);  
        set_skill("force", 200);  
        set_skill("huagong-dafa", 200);  
        set_skill("dodge", 200);  
        set_skill("feixing-shu", 200);  
        set_skill("poison", 200);  
        set_skill("zhaixinggong", 240);  
        set_skill("claw", 240);  
        set_skill("sanyin-wugongzhao", 240);  
        set_skill("strike", 230);  
        set_skill("chousui-zhang", 240);  
        set_skill("parry", 220);  
        set_skill("staff", 220);  
        set_skill("literate", 230);  
          
        map_skill("force", "huagong-dafa");  
        map_skill("dodge", "zhaixinggong");  
        map_skill("strike", "chousui-zhang");  
        map_skill("claw", "sanyin-wugongzhao");  
        map_skill("parry", "chousui-zhang");  
            
        prepare_skill("strike", "chousui-zhang");  
        prepare_skill("claw", "sanyin-wugongzhao");  
          
        create_family("星宿派", 2, "弟子");  

        set("inquiry", ([
                "name" : "你管不着。\n",
                "here" : "你这个人有病是不是，没看见我正忙着么？\n",
                "神木王鼎" : (: ask_ding :),
        ]) );

        set("auto_perform",1);
        setup();
        carry_object("/d/xingxiu/obj/yellow-cloth")->wear();  
        carry_object("/d/xingxiu/obj/bilinzhen");  
        carry_object("/d/xingxiu/obj/lianxindan");  

}
int ask_ding(object me)
{
        if(me->query_temp("sou/done")==1)
                return notify_fail("阿紫瞅了你一眼道：“你还想干什么？”\n");
        
        if(me->query("family/family_name") != "星宿派")
        {  
                say("阿紫说道：“这东西可不是给你用的。”\n");
                return 0;
        }  
        
        if ((int)me->query_temp("mark/ding") < 1)
                me->set_temp("mark/ding", 1 ); 
        
        me->add_temp("mark/ding", 1 );
        if ((int)me->query_temp("mark/ding") >= 5+random(5))
        {
                say("阿紫说道：你这个人怎么这么烦？神木王鼎就是不在我身上，不信你搜（sou）我好了。\n");
                add_action("do_sou","sou");
                return 1;
        }
        else
                say("阿紫说道：什么神木王鼎，我可没拿……，你别冤枉好人！\n");
        return 1;
}

int do_sou(string arg)
{
    object me,ob1,ob2;
    ob2=this_object();
    me = this_player();
    if( !arg || arg=="" )
        return 0;
    
    if( arg=="a zi" ) 
    {
        message("vision",
            me->name() + "狞笑着说道：“好，那我就不客气了。”\n",
            environment(me),({me}));
        ob2->kill_ob(me);
        ob2->set_temp("last_damage_from",me);
        me->set_temp("azi/killer2",1); 
  
        ob1=present("xiao feng");
        if(!ob1 && !me->query_temp("xiaofeng/done"))
        {
                say(HIY+"阿紫大声喊道：“姐夫救我，这个臭贼想非礼我！！”"NOR+"\n");
                ob1=new("/kungfu/class/xingxiu/xiaofeng");

                ob1->move(environment());
                message_vision(HIY+"\n忽地传来一声怒喝：“何人如此大胆!阿紫不用怕，有姐夫在看谁敢欺负你？”\n"+NOR,me);
                ob1->kill_ob(me);
                me->fight_ob(ob1);
                me->fight_ob(ob2);
                me->set_temp("xiaofeng/done",1);
                me->set_temp("sou/done",1);
                remove_action("do_sou","sou");          
                return 1; 
        }
        return 1;
    }
}

void accept_kill(object me)
{ 
        object ob;
        object ob1;
        if( is_fighting()) return;
        if(me->query_temp("you/done")==1 && me->query_temp("xiaofeng/done")==1)
        {
                this_object()->kill_ob(me);
                me->fight_ob(this_object());
        } 
        say("\n阿紫大叫：“救命啊，有人要杀我！！\n\n");
//      this_object()->kill_ob(me);
//      me->fight_ob(this_object());
        me->set_temp("azi/killer",1);
        this_object()->set_temp("last_damage_from",me);
        ob1=present("xiao feng");
        ob=present("you tanzhi");
        if(!ob && !me->query_temp("you/done") )
        {
                ob=new("/kungfu/class/xingxiu/you");
                ob->move(environment());
                ob->kill_ob(me);
                me->fight_ob(ob);
                message_vision("游坦之大喝一声，挡住了你的去路！\n",me);
                        
        }
        if(!ob1 && !me->query_temp("xiaofeng/done") )
        {
                ob1=new("/kungfu/class/xingxiu/xiaofeng");
                ob1->move(environment());
                ob1->kill_ob(me);
                me->fight_ob(ob1);
                message_vision("萧峰大喝一声，挡住了你的去路！\n",me);
        }
        return;
}

void accept_fight(object me)
{
        say("阿紫眼睛一瞪：“我才没空和你胡闹呢！”\n");
        return;
}

void die()
{
        
        ::die();
}

void unconcious()
{
        object me=this_object();
        me->add("qi",4000);
        me->add("jing",4000);
        ::unconcious();
}

