//开站加8点自由分配天赋的NPC

#include <ansi.h>

inherit NPC;

int ask_gift();
int do_add(string arg);
mixed ask_cancel();

int wuyi_tianfu();
int wuyi_qiaokeli();
int liwu_random();

mapping item_list = ([     
                "/clone/fam/gift/str3" : 100,
                "/clone/fam/gift/int3" : 100,
                "/clone/fam/gift/con3" : 100,
                "/clone/fam/gift/dex3" : 100,
                "/clone/fam/gift/str2" : 30,
                "/clone/fam/gift/int2" : 30,
                "/clone/fam/gift/con2" : 30,
                "/clone/fam/gift/dex2" : 30,
                "/clone/fam/gift/perwan" : 50,
                "/clone/fam/pill/full1" : 5,
                "/clone/fam/item/yanluo" : 80,
                "/clone/fam/item/lihuo" : 80,
                "/clone/fam/pill/linghui1" : 10,
                "/clone/fam/pill/linghui2" : 20,
                "/clone/fam/pill/yulu" : 40,
                "/clone/fam/pill/dimai" : 40,                
                "/clone/fam/pill/puti4" : 20,                  
                "/clone/fam/pill/renshen4" : 30,
                "/clone/fam/pill/lingzhi4" : 30,
                "/u/sanben/obj/fig" : 500,   
                "/clone/misc/jinzhuan" : 30,     
 ]);

void create()

{
    set_name(HIC"浪翻云"NOR, ({"zhyx_boss" }));
    set("title", HIW"［"HIG"黑榜高手"HIW"］"NOR);
    set("gender", "男性");
    set("age", 24);
    set("per", 40);
    set("str", 40);
    set("int", 40);
    set("con", 40);
    set("dex", 40);
    set("inquiry", ([
                  "天赋": (: ask_gift :),
                  "gift": (: ask_gift :),
                  "新手礼物": (: ask_gift :),
                  "取消任务": (: ask_cancel :),
            //      "五一金丹": (: wuyi_tianfu :),
            //      "五一巧克力": (: wuyi_qiaokeli :),
            //     "礼物": (: liwu_random :),
        ]));
    setup();
}

void init()
{
     object me;
     ::init();

        add_action("do_add", "add");
        add_action("do_change", "change");
        add_action("do_change", "duihuan");
        add_action("do_list", "list");

        if( interactive(me = this_player()) && !is_fighting() )
        {
                remove_call_out("greeting");
                call_out("greeting", 1, me);
        }

}

void greeting(object ob)

{
     object me;
     me=this_player();
     if (!ob || !present(ob, environment())) return;

            write(HIW"浪翻云说道：欢迎光临!"
                  "新玩家可以用"NOR HIG"ask zhyx_boss about 天赋"NOR
                  HIW"来要新手礼物。\n"NOR);
            return ;
}


int ask_gift()

{       int rmb;
        object me;

        me = this_player();
        rmb = me->query("gift/bobo/rmb");


      if ( me->query("gift/kaizhan") || me->query("gift/jindan") ||
           me->query("gift/bobo") )
      {
        tell_object(me,HIR"你已经有过新手礼物了！\n"NOR);

        if ( me->query("gift/bobo") )
           {
             tell_object(me,HIY"你还能修改" + chinese_number(rmb/2) +
             "次天赋！\n"NOR);
           }
        return 1;
      }

        if ( me->query("max_neili") < 500 ) me->set("max_neili",500);
        if ( me->query("max_jingli") < 300 ) me->set("max_jingli",300);
        me->add("combat_exp",10000);
        me->add("potential",20000);
        me->add("weiwang",100);
        me->add("score",100);

        if ( me->query_skill("dodge", 1) < 40 ) me->set_skill("dodge",40);
        if ( me->query_skill("parry", 1) < 40 ) me->set_skill("parry",40);
        if ( me->query_skill("force", 1) < 40 ) me->set_skill("force",40);
        if ( me->query_skill("unarmed", 1) < 40 ) me->set_skill("unarmed",40);
        if ( me->query_skill("strike", 1) < 40 ) me->set_skill("strike",40);
        if ( me->query_skill("sword", 1) < 40 ) me->set_skill("sword",40);
        if ( me->query_skill("martial-cognize",1) < 40 ) me->set_skill("martial-cognize",40);
        me->set("gift/kaizhan", 1);
        me->set("gift/jindan",2);
        me->set("gift/bobo",1);
        me->set("gift/bobo/rmb",12);

        tell_object(me,HIG"你的各项基本技能有了提高！\n"NOR
        HIY"你现在还可以自由分配"NOR HIR + "6" + NOR HIY
        "点天赋,格式为add xxx，"
        "各种属性对应英文如下：\n"NOR
                       HIY"膂力：【 " HIG "str" HIY " 】 "
                          "悟性：【 " HIG "int" HIY " 】 "
                          "根骨：【 " HIG "con" HIY " 】 "
                          "身法：【 " HIG "dex" HIY " 】\n");

        command("chat " "欢迎" +me->query("name")+"光临【中华英雄】\n",);

        log_file("static/kaizhan", sprintf("%s(%s) ask 泊泊天赋 at %s.\n",
                 me->name(1), me->query("id"), ctime(time())));

         return 1;

}

int do_add(string arg)

{               int x;
                object me;

                me=this_player();
                x=(me->query("gift/bobo/rmb"));

      if ( ! me->query("gift/bobo") )

      {
           tell_object(me,HIG"请先ask bobo about 天赋\n"NOR);
           return 1;
      }


      if (x<2)

      {    tell_object(me,HIR" 你不能再要求加天赋了\n"NOR);
           return 1;
      }

        if (! arg || ! stringp(arg)|| arg != "str" && arg != "int" &&
            arg != "con" && arg != "dex")

        {
               command("shake " + me->query("id"));
               command("say 你得告诉我要加哪个属性呀。" NOR);
                return 1;
        }     

        if (arg=="str")   

        {me->add("str", 1);

         command("tell " + me->query("id") +
                        " 你的膂力增加了一点\n");
                        me->add("gift/bobo/rmb", -2);
                         return 1;}

         if (arg=="int")   

        {me->add("int", 1);
        command("tell " + me->query("id") +
                        " 你的悟性增加了一点\n");
                        me->add("gift/bobo/rmb", -2);
                         return 1;}

         if (arg=="con")
        {me->add("con", 1);
        command("tell " + me->query("id") +
                        " 你的根骨增加了一点\n");
                        me->add("gift/bobo/rmb", -2);
                         return 1;}

         if (arg=="dex")
        {me->add("dex", 1);
         command("tell " + me->query("id") +
                        " 你的身法增加了一点\n");
                        me->add("gift/bobo/rmb", -2);
                         return 1;}
       return 1;
}

int liwu_random()
{
    object gift, bobo ,me;
    bobo = this_object();
    me = this_player();

    if ( me->query("liwu/2005random/get") )
     {
      command("say 你不是已经领到这次礼物了吗？\n");
      return 1;
     }
     else
     {
       me->set("liwu/2005random/get", 1);
       gift = new("/u/sanben/obj/xiaolong");
       gift->move(me);
       command("say 你好，祝你愉快！");
       message_vision(HIC "$N" HIC "拿出一个小笼包给$n。\n"NOR,bobo,me);
       return 1;
     }
}

int wuyi_qiaokeli()
{
    object gift, bobo ,me;
    bobo = this_object();
    me = this_player();

    if ( me->query("liwu/wuyi2005/get") )
     {
      command("say 你不是已经领到五一礼物了吗？\n");
      return 1;
     }
     else
     {
       me->set("liwu/wuyi2005/get", 1);
       gift = new("/u/sanben/obj/qiaokeli5_1");
       gift->move(me);
       command("say 祝你五一快乐！\n");
       message_vision(HIC "$N" HIC "拿出一颗五一巧克力给$n。\n"NOR,bobo,me);
       return 1;
     }
}

mixed ask_cancel()
{
              object me;
              me = this_player();

             if (! me->query("quest") && ! me->query("xquest") 
                 && ! me->query("changanjob"))
                         return "你没有任务在身呀！";

              if (me->query("balance") < 2000000)
                         return "你银行帐户存款不足支付手续费。";

              message_vision(HIY "$n" HIY "看看$N" HIY
                                 "，道：“好吧，你的任务消除了！”说罢对着$N"
                                 HIY "嘻嘻笑了几声。\n" NOR,
                                  me, this_object());
              
             me->delete("quest");
             me->delete("xquest");
             me->delete("changanjob");

             me->add("balance",-2000000);
              return 1;
}

int accept_object(object me, object ob)
{
   if ( ! ob->query("gft_pt") ) return 0;
   me->add("gift/gift_point", ob->query("gft_pt"));
   tell_object(me, HIG"你的奖品兑换点数增加了" + 
            chinese_number(ob->query("gft_pt")) + "点。\n"NOR);
   tell_object(me, HIG"你的奖品兑换点数现在总共为" + 
            chinese_number(me->query("gift/gift_point")) + "点。\n"NOR);
   destruct(ob);
   return 1;

}

int do_list()
{
   string msg, *item, name, space;
   int i, len, have;
   object ob;

    space = "                               ";
    

        item = keys(item_list);
        msg = HIC"         可兑换奖品列表:\n\n"NOR;

        for(i = 0; i < sizeof(item); i++)
        {
            ob = new(item[i]);
            name = ob->query("name");
            len = sizeof(name) - color_len(name);
            len = 14 - len;           
            msg += name + space[0..len] + 
                YEL"兑换所需点数:  "NOR HIG + item_list[item[i]] + "\n"NOR;            
            destruct(ob);
        }
        msg += HIG"\n你现在有" + this_player()->query("gift/gift_point") 
                  + "点奖励点数。\n"NOR;
        write(msg + "\n");
        return 1;
}


int do_change(string arg)
{
   string msg, *item, name, space;
   int i,have;
   object ob, me;
    
    me = this_player();

    if (! arg ) return notify_fail("你要兑换什么物品？可以用list查询。\n");    

    have = 0;    
    item = keys(item_list);

    for(i = 0; i < sizeof(item); i++)
    {
       ob = new(item[i]);
       name = ob->query("name");
       if ( filter_color(name) == arg ) 
       {
           have = 1;
           if ( me->query("gift/gift_point") < item_list[item[i]] ) 
               write(HIR"你的奖励点数不够兑换这个物品!\n"NOR);
           else
           {
              ob->move(this_player());
              command("say 好的，就兑换给你吧。");
              
              message_vision(HIC"$N" HIC"拿出一件物品给$n。\n"NOR, this_object(), me); 
       
              me->add("gift/gift_point", -item_list[item[i]] );

              if ( me->query("gift/gift_point") <= 0 )
                  me->delete("gift/gift_point");
              log_file("static/yc_gift", sprintf("%s(%s) 兑换%s at %s.\n",
               me->name(1), me->query("id"), ob->query("name"), ctime(time())));

              break; 
           }
           
       }
       destruct(ob);
    }
    if ( have == 0 )
        write(HIR"这里没有你要兑换的物品!\n"NOR);
    return 1;
}

