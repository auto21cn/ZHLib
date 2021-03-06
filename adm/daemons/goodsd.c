// 英雄商店出售物品小型数据库系统

#include <ansi.h>

#define MEMBER_D              "/adm/daemons/memberd"
#define MLOG_BUY_DIR          "/data/member/mdata/log/log_buy/"
#define PASSWD                "#####FORZHONLINEIS2006MADEBYYUCHANG#####"

mapping goods = ([
      "obint9"                : "神恩通慧仙丹:10000:/clone/fam/gift/int3:object",
      "obcon9"                : "洗髓再造仙丹:10000:/clone/fam/gift/con3:object",
      "obstr9"                : "蚩尤诛元仙丹:10000:/clone/fam/gift/str3:object",
      "obdex9"                : "破阳无极仙丹:10000:/clone/fam/gift/dex3:object",
      "obint10"               : "神恩通慧仙丹Ⅱ型:20000:/clone/fam/gift/int4:object",
      "obcon10"               : "洗髓再造仙丹Ⅱ型:20000:/clone/fam/gift/con4:object",
      "obstr10"               : "蚩尤诛元仙丹Ⅱ型:20000:/clone/fam/gift/str4:object",
      "obdex10"               : "破阳无极仙丹Ⅱ型:20000:/clone/fam/gift/dex4:object",
      
      "obcint"                : "消慧丹:60000:/clone/fam/gift/cint:object",
      "obccon"                : "化骨丹:60000:/clone/fam/gift/ccon:object",      
      "obcdex"                : "落凤丹:60000:/clone/fam/gift/cdex:object",      
      "obcstr"                : "阴虚丹:60000:/clone/fam/gift/cstr:object",      
      
      "obzhenyu"              : "镇狱惊天丸:100000:/clone/fam/max/zhenyu:object",
      "oblongjia"             : "子午龙甲丹:60000:/clone/fam/max/longjia:object",
      "obxuanhuang"           : "玄黄紫箐丹:60000:/clone/fam/max/xuanhuang:object",
      "obtsxuantie"           : "天山玄铁:60000:/clone/fam/item/xuantie:object",
      "obhytianjing"          : "寰宇天晶:400000:/d/death/obj/tianjing:object",
      
      "yanlongjia"            : "炎龍聖甲:320000:/clone/fam/armor/yanlongjia:object",
      "zijiaojia"             : "紫蛟鳞甲:350000:/clone/fam/armor/zijiaojia:object",
      "shenhujia"             : "神虎战甲:350000:/clone/fam/armor/shenhujia:object",
      "fenghuangpf"           : "凤凰披风:400000:/clone/fam/armor/fenghuangjia:object",
      "shhuwan"               : "神虎护腕:68000:/clone/fam/armor/baihuwrists:object",
      "shyaodai"              : "神虎腰带:68000:/clone/fam/armor/baihuyaodai:object",
      "fhyaodai"              : "凤凰腰带:68000:/clone/fam/armor/fenghuangyaodai:object",
      "fhtouguan"             : "凤凰头冠:68000:/clone/fam/armor/fenghuanghead:object",
      "zjyaodai"              : "紫蛟腰带:68000:/clone/fam/armor/zijiaoyaodai:object",
      "zjtoulu"               : "紫蛟头颅:68000:/clone/fam/armor/zijiaohead:object",
      "ylyaodai"              : "炎龙腰带:68000:/clone/fam/armor/yanlongyaodai:object",
      "ylshenguan"            : "炎龙神冠:68000:/clone/fam/armor/yanlonghead:object",
      "qkwater"               : "乾坤圣水:20000:/clone/fam/item/bless_water:object",      
      
      "accuracy"              : "精准射击:50000:/kungfu/special/accuracy:special",
      "agile"                 : "如鬼似魅:50000:/kungfu/special/accuracy:special",
      "clever"                : "天赋聪颖:50000:/kungfu/special/accuracy:special",
      "constitution"          : "镇蕴七星:50000:/kungfu/special/constitution:special",
      "cunning"               : "八面玲珑:50000:/kungfu/special/cunning:special",
      "dexterity"             : "玲珑玉躯:50000:/kungfu/special/dexterity:special",
      "divine"                : "移经易脉:50000:/kungfu/special/divine:special",
      "energy"                : "聚魄还虚:50000:/kungfu/special/energy:special",
      "greedy"                : "饕餮转世:50000:/kungfu/special/greedy:special",
      "hatred"                : "杀气冲霄:50000:/kungfu/special/hatred:special",
      "health"                : "内敛乾坤:50000:/kungfu/special/health:special",
      "herb"                  : "本草知识:50000:/kungfu/special/herb:special",
      "intellect"             : "罡睿神慧:50000:/kungfu/special/intellect:special",
      "ironskin"              : "铜皮铁骨:50000:/kungfu/special/ironskin:special",
      "lucky"                 : "福星高照:50000:/kungfu/special/lucky:special",
      "might"                 : "狂暴铁拳:50000:/kungfu/special/might:special",
      "mystery"               : "玄黄聚纳:50000:/kungfu/special/mystery:special",
      "potential"             : "乾坤无量:50000:/kungfu/special/potential:special",
      "power"                 : "天神降世:50000:/kungfu/special/power:special",
      "self"                  : "小周天运转:50000:/kungfu/special/self:special",
      "strength"              : "麒麟血臂:50000:/kungfu/special/strength:special",
      "trick"                 : "鬼话连篇:50000:/kungfu/special/trick:special",
      "wrath"                 : "愤怒之心:50000:/kungfu/special/wrath:special",
      "youth"                 : "天颜永驻:50000:/kungfu/special/youth:special",

      "water"                 : "圣沐成功:30000:int:story",
      "sun"                   : "日炽成功:30000:str:story",
      "feng"                  : "凤舞成功:30000:dex:story",
      "lighting"              : "电击成功:30000:con:story",

      "manual1"               : "自选天赋:200000:manual:byadmin&newid",
      "manual2"               : "铸造武器时内功暴涨:400000:manual:byadmin",
      "manual3"               : "天煞孤星:2000000:manual:byadmin&newid",
      "manual4"               : "真命天子:2000000:manual:byadmin&newid",
      "manual5"               : "九级兵器:500000:manual:byadmin",
      "manual6"               : "十级兵器:2000000:manual:byadmin",
      "manual7"               : "青天甲:700000:manual:byadmin",      

]);

private string get_types(string types)
{
      switch(types)
      {
           case "object"             :    return HIC "物品" NOR;
           case "special"            :    return HIG "特殊技能" NOR;
           case "story"              :    return HIM "故事" NOR;
           case "byadmin"            :    return HIR "※" NOR;
           case "newid"              :    return HIY "★" NOR;
           case "byadmin&newid"      :    return HIR "※" HIY "★" NOR;
           default                   :    return HIR "未知" NOR;
      }
}

private void log_buyinfo(string id, string which, int value, object me)
{
      int flag;
      string strvalue;

      if (file_size(MLOG_BUY_DIR + id) == -1)
      {
          flag = 1;
      }
      else flag = 0;

      strvalue = sprintf("%d", value);

      write_file(MLOG_BUY_DIR + id, 
                 sprintf("%s(%s)于%s花费 %s YXB购买物品 %s 1。\n",
                 me->name(1), 
                 me->query("id"), 
                 MEMBER_D->bjtime(time(), 1),
                 strvalue,
                 which),
      flag);
      me->add("member/buy_times", 1);
      me->add("member/buy_value", value);
      me->set("member/last_buytime", time());
      me->set("member/last_buyob", which);
      me->set("member/last_buyvalue", strvalue);

      return;
}

/***************显示出售物品的详细清单********************************
*********************************************************************/
public void show_goods()
{
      string strtmp;
      int i;
      string *all, *items;

      all = keys(goods);
      
      write(HIY "英雄商店目前出售以下货物：\n" NOR);
      write(sprintf(HIW "%-22s%-22s%-23s%s\n" NOR, 
            "名  称", "代  号", "价  格( YXB)", "种  类"));                                           
      write(HIG "-------------------------------------------------------------------------------\n\n" NOR);
      for (i = 0; i < sizeof(all); i ++)
      {
           strtmp = "";
           items = ({});
           
           strtmp = goods[all[i]];         
           items = explode(strtmp, ":");
           if (sizeof(items) != 4)
           {
               write("strtmp made items != 4 is : " + strtmp + "\n");
               return;
           }
           write(sprintf(HIW "%-22s%-22s%-37s%s\n" NOR, 
                   items[0], all[i], HIY + items[1] + HIW, get_types(items[3])));
      }
      
      write(HIG "\n请使用 " + HIR + "member buy 物品代号 " + HIG + "来购买物品！\n" NOR);
      write(HIG "凡是种类带有" HIR "※" HIG "标记的服务均为须跟" HIW "ADMIN" HIG "联系手动实现。\n" NOR);
      write(HIG "凡是种类带有" HIY "★" HIG "标记的服务均为只对新ID开放。\n" NOR);
      write(HIG "关于物品的其他说明和限制请参见文件 " HIR "help hero_shop" HIG " 。\n" NOR);
      write(HIG "请认真阅读有关说明，购买前请考虑清楚， 如无差错，恕不退货！\n" NOR);
      write(HIG "-------------------------------------------------------------------------------\n\n" NOR);
}

/**************************购买物品********************
 1、检查是否为有效会员
 2、查询物品代号是否存在
 3、查询YXB是否足够
 4、购买成功
 5、写入购买记录文件
******************************************************/
public int buy_goods(string who, string which, object me)
{
     string *all, *items, *specials;
     string strtmp;
     int i, value, yxb;
     object buy_ob;
 
     if (! MEMBER_D->is_member(who))
     {
           write("对不起，只有会员才能享受此服务！请参见 " HIR "help member " NOR " ！\n");
           return 0;
     }
     
     if (! MEMBER_D->is_valib_member(who))
     {
           write("您的会员有效期已过， 请及时充值！\n");
           return 0;
     }

     all = keys(goods);
     if (member_array(which, all) == -1)
     {
           write("对不起，没有您要购买的物品 " + HIR + which + NOR + "， 请使用"
                 " member show goods 查询。\n" NOR); 
           return 0;

     }

     strtmp = goods[which];
     items = explode(strtmp, ":");
     sscanf(items[1], "%d", value);

     if (items[2] == "manual")
     {
          write("对不起，该服务必须由 admin 手动实现，请及时与 admin 联系！\n");
          return 0;
     }
     if (MEMBER_D->get_yxb(who) < value)
     {
            write("对不起，您的货币数量不够！\n");
            return 0;
     }
     
     switch(items[3])
     {
           case "object":
                buy_ob = new(items[2]);
                if (! objectp(buy_ob))
                {
                     write("复制物品失败，请与本站ADMIN联系！\n");
                     return 0;
                }
                buy_ob->move(me);
                MEMBER_D->add_yxb(who, -1 * value, PASSWD);
                log_buyinfo(who, items[0], value, me);
                write(HIG "购买成功， 您的购买记录已写入文件，请使用 " HIR "member show buy"
                      "info " HIG " 查询！ \n" NOR);
                write(HIC "您总共花费了 " HIY + value + HIC + " YXB, 祝您好运！\n" NOR);
                return 1;

           case "story":
                // 首先检查是否中过故事
                if (me->query("gift/" + which))
                {
                      write("您已经中过该故事了！\n");
                      return 0;
                }
                me->add("gift/" + which, 1);
                me->add(items[2], 1);
                MEMBER_D->add_yxb(who, -1 * value, PASSWD);
                log_buyinfo(who, items[0], value, me);

                write(HIG + items[0] + " ， 您的购买记录已写入文件，请使用 " HIR "member show buy"
                      "info " HIG " 查询！ \n" NOR);
                write(HIC "您总共花费了 " HIY + value + HIC + " YXB, 祝您好运！\n" NOR);
                return 1;

           case "special":
                // 首先检查是否有该special
                // 同时检查总共的special不能大于7
                if (! me->query("special_skill"))specials = 0;
                else specials = keys(me->query("special_skill"));
                if (1) // 正常出售
                {
                      if (sizeof(specials) > 0)
                      {
                            if (member_array(which, specials) != -1)
                            {
                                 write("对不起，您已经有这个特殊技能了！\n");
                                 return 0;
                            }
                            if (sizeof(specials) >= 7)
                            {
                                 write("对不起，一个帐号最多只能拥有七个特殊技能！\n");
                                 return 0;
                            }
                      }

                      me->set("special_skill/" + which, 1);
                      // 麒麟血臂增加1点膂力
                      if (which == "strength")
                            me->add("str", 1);

                      // 罡睿神慧增加1点悟性
                      if (which == "intellect")
                            me->add("int", 1);

                      // 镇蕴七星增加1点根骨
                      if (which == "constitution")
                            me->add("con", 1);

                      // 玲珑玉躯增加1点身法
                      if (which == "dexterity")
                            me->add("dex", 1);

                      MEMBER_D->add_yxb(who, -1 * value, PASSWD);
                      log_buyinfo(who, items[0], value, me);
                      write(HIG "购买成功， 您的购买记录已写入文件，请使用 " HIR "member show buy"
                            "info " HIG " 查询！ \n" NOR);
                      write(HIC "您总共花费了 " HIY + value + HIC + " YXB, 祝您好运！\n" NOR);
                      return 1;
                }
                else 
                {
                      write("暂时停止出售特殊技能！请谅解！\n");
                      return 0;
                }
          default:
                write("无效物品种类！\n");
                return 0;               
     }
}
