// auction.c

#include <ansi.h>

#ifndef AUCTION_D
#define AUCTION_D       "/adm/daemons/auctiond"
#endif

inherit F_CLEAN_UP;

int help(object me);
int to_money(string str);

int main(object me, string arg)
{
        object ob;
        string name, str;
        int money;

        if (! arg) return help(me);

        if (arg == "cancel")
        {
                AUCTION_D->cancel_auction(me);
                return 1;
        }
        
        if (arg == "check")
        {
                if (stringp(str = AUCTION_D->check_auction_info()))
                {
                        write(str);
                        return 1;
                }
                return notify_fail("目前没有任何东西正在拍卖。\n");
        }

        if (sscanf(arg, "%s for %s", name, str) == 2)
        {
                if (! objectp(ob = present(name, me)))
                        return notify_fail("你身上没有这个东西。\n");

                ob->set_amount(1);

                if (! intp(money = to_money(str)) || money <= 0)
                        return notify_fail("输入价格错误。\n");

                AUCTION_D->add_auction(me, ob, money);
                return 1;
        }

        if (sscanf(arg, "bid %s", str) == 1)
        {
                if (! intp(money = to_money(str)) || money <= 0)
                        return notify_fail("输入价格错误。\n");

                if (me->query("balance") < money)
                        return notify_fail("你的存款不足。\n");

                AUCTION_D->join_auction(me, money);
                return 1;
        }

        return help(me);
}

int to_money(string str)
{
        int money, gold, silver, coin;
        string type;

        if (sscanf(str, "%d gold %d silver %d coin",
                   gold, silver, coin) == 3)
                money = gold * 10000 + silver * 100 + coin;
                
        else if (sscanf(str, "%d gold %d silver",
                        gold, silver) == 2)
                money = gold * 10000 + silver * 100;

        else if (sscanf(str, "%d silver %d coin", 
                        silver, coin) == 2)
                money = silver * 100 + coin;

        else
        {
                if (sscanf(str, "%d %s", money, type) != 2)
                        return 0;

                switch (type)
                {
                case "gold": 
                        money *= 10000;
                        break;
                        
                case "silver":
                        money *= 100;
                        break;
                        
                case "coin":
                        break;
                        
                default: money = 0;
                }
        }
        return money;
}

int help(object me)
{
        write(@HELP
指令格式 : auction <物品> for <数量> <钱的种类>
           拍卖出一件物品。

           auction bid <数量> <钱的种类>
           参与叫价。
           
           auction check
           察看目前所有正在拍卖的物品。

           auction cancel
           取消自己所有物品的拍卖。
           取消拍卖时将根据你参与拍卖的所有物品价格之和的
           三十分之一的价格来作为违约金从存款中扣除。

HELP
    );
        return 1;
}
