#include <ansi.h>
inherit ROOM;

       void create() 
       { 
                   set("short", HIY "\n\n中 华 购 物 中 心" NOR);
                   set("long", HIG "这里是中华会员购物中心，只见这里"
                               "四周宽敞明亮，不远处\n整齐地摆放着很多"
                               "自动售货机(ASM)。\n" NOR
                   );
                   set("exits", ([
                          "out"  :  "/d/city/guangchang",
                   ]));

                   set("no_fight", 1); 
                   set("item_desc", ([ 
                          "asm"  :    "机器屏幕上显示：" HIM + BLINK" 请插入(insert)你的会员卡 " NOR 
                                      "的字样，机器上\n布满着各种奇怪的按扭。\n",
                   ]));

                   setup();     
       } 


void init()
{
        add_action("do_insert", "insert");
        add_action("do_pull", "pull");
        add_action("do_list", "list");
        add_action("do_buy", "want");
        
}
int do_insert(string arg)
{
        object me, ob;
        me = this_player();

        if (! arg || arg == "")
                return 0;

        if (arg == "card" || arg == "zhyx card")
        {
                if (! ob = present("zhyx card", me)) return 0;

                if (me->query("temp/insert"))
                        return notify_fail("卡还没取呢!\n");

                if (me->is_busy())
                {
                        return notify_fail("你正忙着呢。\n");
                        return 1; 
                }
                destruct(ob);
                write(HIW "你将卡片插入自动售货机...\n" NOR);
                write(HIY "中华自动售货机正在读取你卡上的数据，请稍后...\n" NOR);
                me->set("temp/insert", 1);
                call_out("show", 4 + random(2));
                return 1;
        }
}

//数据读取完毕，允许购物
int show()
{  
   int rmb;
   object me = this_player();
   rmb = this_player()->query("rmb");
   tell_object(me, HIC "你目前的存款为" + chinese_number(rmb) + "圆人民币。\n" NOR);
   write(HIG "数据读取成功，请输入(list)显示可以购买的物品，输入(want)购买物品。\n" NOR);
   this_player()->set("temp/can_pull", 1);
     
   return 1; 
}

int do_list()
{
   string msg;
   if (! this_player()->query("temp/insert"))
   {
           write("请先插入会员卡。\n");
           return 1;
   }
  msg = HIC "【名称】                           \t【作用】            【成功率】                【价格】\n\n" NOR;
  msg +=HIG "神力丸(Shenli wan)                     增加先天臂力            40%                    ￥ 2.00\n";
  msg +=HIG "白虎赐元丹(Baihu dan)                  增加先天臂力            70%                    ￥ 5.00\n";
  msg +=HIG "蚩尤诛元仙丹(Zhuyuan xiandan)          增加先天臂力            85%                    ￥10.00\n";
  msg +=HIW "增慧丹(Zenghui dan)                    增加先天悟性            40%                    ￥ 2.00\n";
  msg +=HIW "青龙炼睿丹(Qinglong dan)               增加先天悟性            70%                    ￥ 5.00\n";
  msg +=HIW "神恩通慧仙丹(Tonghui xiandan)          增加先天悟性            85%                    ￥10.00\n";
  msg +=HIY "福寿膏(Fushou gao)                     增加先天身法            40%                    ￥ 2.00\n";
  msg +=HIY "朱雀玲珑丹(Zhuque dan)                 增加先天身法            70%                    ￥ 5.00\n";
  msg +=HIY "破阳无极仙丹(Wuji xiandan)             增加先天身法            85%                    ￥10.00\n";
  msg +=HIR "壮骨粉(Zhuanggu fen)                   增加先天根骨            40%                    ￥ 2.00\n";
  msg +=HIR "玄武铸骨丹(Xuanwu dan)                 增加先天根骨            70%                    ￥ 5.00\n";
  msg +=HIR "洗髓再造仙丹(Xisui xiandan)            增加先天根骨            85%                    ￥10.00\n\n\n" NOR;
  
  write(msg);
  return 1;

}

int do_pull(string arg)
{
        object me,ob;
        int rmb;
        me = this_player();

        if (! arg || (arg != "card" && arg != "zhyx card"))
                return 1;

        if (me->is_busy())
        {
                return notify_fail("你正忙着呢。\n");
        }
        // 判断卡片是否未取出
        if (me->query("temp/insert") && me->query("temp/can_pull"))
        {      
                rmb = me->query("rmb");
                tell_object(me, HIC "你目前的存款为" + chinese_number(rmb) + "圆人民币。\n" NOR);
                write(HIW "你将卡片从中华自动售货机中取出。\n" NOR);
                ob = new("/clone/gift/hycard.c");
                ob->move(me);
                me->delete("temp/insert");
                return 1;
        }
        write(HIR "操作错误!\n" NOR);
        return 1;
}


int do_buy(string arg)
{
    object me, ob;
    int rmb, feng,sun,lighting,water;
    
    me = this_player();
    rmb = me->query("rmb");
    
    if (! arg || arg == "") return 1;
    
    if (arg == "shenli dan")
    {
          if (rmb < 2)
          { 
              write("对不起,你的卡上余额已不足,请尽快充值!\n" NOR);
              return 1;
          }
          ob = new("/clone/fam/gift/str1");
          ob->move(me);
          me->add("rmb", -2); 
          write(HIG "你买下一颗神力丸！\n" NOR);       
    } 
    else  if (arg == "baihu dan")
    {
          if (rmb < 5)
          { 
              write("对不起,你的卡上余额已不足,请尽快充值!\n" NOR);
              return 1;
          }
          ob = new("/clone/fam/gift/str2");
          ob->move(me);
          me->add("rmb", -5);  
          write(HIG "你买下一颗白虎赐元丹！\n" NOR);
    }    
    else if (arg == "zhuyuan xiandan")
    {
          if (rmb < 10)
          { 
              write("对不起,你的卡上余额已不足,请尽快充值!\n" NOR);
              return 1;
          }
          ob = new("/clone/fam/gift/str3");
          ob->move(me);
          me->add("rmb", -10);  
          write(HIG "你买下一颗蚩尤诛元仙丹！\n" NOR);
    }    
    else if (arg == "zenghui dan")
    {
          if (rmb < 2)
          { 
              write("对不起,你的卡上余额已不足,请尽快充值!\n" NOR);
              return 1;
          }
          ob = new("/clone/fam/gift/int1");
          ob->move(me);
          me->add("rmb", -2);  
          write(HIG "你买下一颗增慧丹！\n" NOR);
    }        
    else if (arg == "qinglong dan")
    {
          if (rmb < 5)
          { 
              write("对不起,你的卡上余额已不足,请尽快充值!\n" NOR);
              return 1;
          }
          ob = new("/clone/fam/gift/int2");
          ob->move(me);
          me->add("rmb", -5);  
          write(HIG "你买下一颗青龙炼睿丹！\n" NOR);
    }        
    else if (arg == "tonghui xiandan")
    {
          if (rmb < 10)
          { 
              write("对不起,你的卡上余额已不足,请尽快充值!\n" NOR);
              return 1;
          }
          ob = new("/clone/fam/gift/int3");
          ob->move(me);
          me->add("rmb", -10);        
          write(HIG "你买下一颗神恩通慧仙丹！\n" NOR);
    }        
    else if (arg == "fushou gao")
    {
          if (rmb < 2)
          { 
              write("对不起,你的卡上余额已不足,请尽快充值!\n" NOR);
              return 1;
          }
          ob = new("/clone/fam/gift/dex1");
          ob->move(me);
          me->add("rmb", -2);        
          write(HIG "你买下一块福寿膏！\n" NOR);
    }        
    else if (arg == "zhuque dan")
    {
          if (rmb < 5)
          { 
              write("对不起,你的卡上余额已不足,请尽快充值!\n" NOR);
              return 1;
          }
          ob = new("/clone/fam/gift/dex2");
          ob->move(me);
          me->add("rmb", -5);    
          write(HIG "你买下一颗朱雀玲珑丹！\n" NOR);      
    }        
    else if (arg == "wuji xiandan")
    {
          if (rmb < 10)
          { 
              write("对不起,你的卡上余额已不足,请尽快充值!\n" NOR);
              return 1;
          }
          ob = new("/clone/fam/gift/dex3");
          ob->move(me);
          me->add("rmb", -10); 
          write(HIG "你买下一颗破阳无极仙丹！\n" NOR);     
    }        
    else if (arg == "zhuanggu fen")
    {
          if (rmb < 2)
          { 
              write("对不起,你的卡上余额已不足,请尽快充值!\n" NOR);
              return 1;
          }
          ob = new("/clone/fam/gift/con1");
          ob->move(me);
          me->add("rmb", -2); 
          write(HIG "你买下一包壮骨粉！\n" NOR);       
    }        
    else if (arg == "xuanwu dan")
    {
          if (rmb < 5)
          { 
              write("对不起,你的卡上余额已不足,请尽快充值!\n" NOR);
              return 1;
          }
          ob = new("/clone/fam/gift/con2");
          ob->move(me);
          me->add("rmb", -5);    
          write(HIG "你买下一颗玄武铸骨丹！\n" NOR);
    }        
    else if (arg == "xisui xiandan")
    {
          if (rmb < 10)
          { 
              write("对不起,你的卡上余额已不足,请尽快充值!\n" NOR);
              return 1;
          }
          ob = new("/clone/fam/gift/con3");
          ob->move(me);
          me->add("rmb", -10);      
          write(HIG "你买下一颗洗髓再造仙丹！\n" NOR);
    }        
    else{
          write(HIR "操作错误！\n" NOR);
          return 1;
    }
    write(HIG "操作完成! 离开前请记得取出(pull)卡片。\n");
    rmb = me->query("rmb");
    tell_object(me, HIC "你目前的存款为" + chinese_number(rmb) + "圆人民币。\n" NOR);
    if (me->query("rmb") < 10) 
          write(HIY "你的余额已不多，为避免给你带来的不便，请及时充值。\n" NOR);
    return 1;
}



