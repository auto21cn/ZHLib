// sample master.c code
// xiake island master.c

inherit NPC;
inherit F_MASTER;

string ask_me();
int auto_perform();

void create()
{
        set_name("鲁有脚", ({"lu youjiao", "lu", "youjiao"}));
        set("title", "丐帮九袋长老");
        set("nickname", "掌棒龙头");
        set("gender", "男性");
        set("age", 45);
        set("long", 
                "鲁有脚虽然武功算不得顶尖高手，可是在江湖上却颇有声望。\n"
                "因为他在丐帮中有仁有义，行事光明磊落，深得洪七公的器重。\n");
        set("attitude", "peaceful");
        set("rank",9);
        set("str", 35);
        set("int", 21);
        set("con", 32);
        set("dex", 25);

        set("qi", 2500);
        set("max_qi", 2500);
        set("jing", 1200);
        set("max_jing", 1200);
        set("neili", 4000);
        set("max_neili", 4000);
        set("jiali", 80);
        
        set("combat_exp", 1000000);
        set("shen_type", 1);
        set("score", 25000);
        
        set_skill("force", 180);
        set_skill("jiaohua-neigong", 180);
        set_skill("unarmed", 180);
        set_skill("changquan", 150);
        set_skill("hand",160);
        set_skill("shexing-diaoshou",160);
        set_skill("dodge", 150);
        set_skill("feiyan-zoubi", 150);
        set_skill("parry", 170);
        set_skill("staff", 170);
        set_skill("begging", 120);
        set_skill("checking", 150);
        set_skill("jueming-tui", 180);

        map_skill("force", "jiaohua-neigong");
        map_skill("unarmed", "jueming-tui");
        map_skill("parry", "jueming-tui");
       map_skill("hand","shexing-diaoshou");
        map_skill("dodge", "feiyan-zoubi");
        create_family("丐帮", 18, "九袋长老");
        
        set("inquiry", ([
                "杖法图解" : (: ask_me :),
                "图解" : (: ask_me :),
                "密籍" : (: ask_me :),
                "密笈" : (: ask_me :),
                ]));

        set("book_count", 1);

        set("chat_chance_combat", 50);
        set("chat_chance_combat", 20);
        set("chat_msg_combat", ({
                (: perform_action, "unarmed.xianglong" :),
                (: exert_function, "recover" :),
        }) );

        setup();

        carry_object("/d/gaibang/obj/budai")->set_amount(8);
        carry_object("/d/gaibang/obj/budai")->wear();
        
}


void attempt_apprentice(object ob)
{
        if (ob->query("class")=="bonze") {
                if (ob->query("gender")=="女性")
                        command ("say 师太是是出家人，怎么能在本帮做叫化子呢？");
                return;
        }

        if ( (int)ob->query("int") >= 25 && !(int)ob->query("tianmo_jieti")) {
                command("say 我们丐帮的武艺一向以刚猛为主，" + 
                RANK_D->query_respect(ob) + "聪慧过人，似乎不宜学丐帮的功夫？");
                return;
        }

        if( ob->query("family/family_name") != "丐帮" )
        {
                if( ob->query("rank") > 1 ) {
                        command("say 本帮以忠义为先，可容不下你这种无信无义的家伙！\n");
                        return;
                }
        
                command("say 好吧，希望" + RANK_D->query_respect(ob) +
                "能好好学习本门武功，将来在江湖中闯出一番作为。");
                ob->set("rank", 1); 
                command("recruit " + ob->query("id"));
                ob->set("title", "丐帮一袋弟子");
        } 
        else
        {
                ob->set_temp("title", ob->query("title"));
                command("recruit " + ob->query("id"));
                ob->set("title", ob->query_temp("title"));
                ob->delete_temp("title");
        }
}

string ask_me()
{
        mapping fam; 
        object ob, me=this_object();

        if (!(fam = this_player()->query("family")) || fam["family_name"] != "丐帮")
                return RANK_D->query_respect(this_player())+"与本帮毫无渊源，怎么能开口向我要棒法图解？";

       if ((fam = this_player()->query("family")) || fam["family_name"] = "丐帮")
                return RANK_D->query_respect(this_player())+"请你去问彭有敬";
         
}

int accept_object(object me, object obj)
{

        object ob = this_player();

        if ( (obj->name() == "牛皮酒袋" || obj->name() == "花雕酒袋")
        && obj->query("liquid/type") == "alcohol" ) {
                call_out("drink_jiudai", 1, this_object(), ob, obj);
                return 1;
        }

        command( "say 这东西老叫化我不感兴趣，还是你自个儿留着吧。" );
        return 0;
}

int drink_jiudai(object me, object ob, object obj)
{
        if ( obj->query("liquid/remaining") >= 5 ) {
                message_vision("鲁有脚拿起酒袋一仰头，将整袋酒咕嘟咕嘟地一饮而尽。\n", me);
                command( "taste" );
                if ( ob->query("family/family_name") == "丐帮" ) {
                        command( "nod" );
                        command( "say 好！有什么问题你问吧。" );
                        ob->set_temp("lu", 1);
                }
                else {
                        command( "say 多谢这位"+RANK_D->query_respect(ob)+"。这酒真不坏。\n" );
                        command( "smile" );
                }
        }
        else if ( obj->query("liquid/remaining") == 0 ) {
                message_vision("鲁有脚大怒说道：你当老子傻的啊？拿个空酒袋来消遣老子？\n", me);
                if ( ob->query("family/family_name") == "丐帮" ) {
                        command( "slap " + obj->query("id") );
                        ob->set_temp("lu", 2);
                }
        }
        else {
                command( "say 嘿嘿，才这么点酒就想我指点你？太美了吧！");
        }

        remove_call_out("destroy_it");
        call_out("destroy_it", 1, obj);
        return 1;
}
        
void destroy_it(object obj)
{
        destruct(obj);
}


int auto_perform()
{
        object me=this_object();
        object weapon=me->query_temp("weapon");
        object opp=me->select_opponent();

        if ( !me->is_fighting() ) {
                if ( me->query("eff_qi") < me->query("max_qi") )
                        exert_function("heal");
                me->set("jiali", 50);

                return 1;
        }

        if ( !me->query_temp("powerup") ) {
                return exert_function("powerup");
        }

        if ( objectp(weapon) ) {
                if ( !me->query_temp("shengang") )
                        return exert_function("shengang");

                if ( weapon->query("skill_type") == "staff" )
                        return perform_action("staff.chan");
        }
        else {
                        return perform_action("strike.leiting");
        }
}

