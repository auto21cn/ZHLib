//设置趣味任务奖励的文件

#define     SET_ITEM   "/quest/xquest/set_item.c"

string set_item(object me)
{

        // 完成一百个任务
        string *ob1_list = ({
                "/clone/fam/pill/renshen3",
                "/clone/fam/pill/lingzhi3",
                "/clone/fam/pill/xuelian3",
                "/clone/fam/pill/linghui1",
                "/clone/fam/pill/linghui1",
                "/clone/fam/pill/full1",
                "/clone/fam/pill/full1",
                "/clone/fam/pill/neili1",
                "/clone/fam/pill/neili1",
        });

         // 完成两百个任务
        string *ob2_list = ({
                "/clone/fam/pill/renshen4",
                "/clone/fam/pill/lingzhi4",
                "/clone/fam/pill/xuelian4",
                "/clone/fam/pill/linghui1",
                "/clone/fam/pill/linghui1",
                "/clone/fam/pill/full1",
                "/clone/fam/pill/full1",     
                "/clone/fam/pill/neili1",
                "/clone/fam/pill/neili1",       
        });

        // 完成三百个任务
        string *ob3_list = ({
                "/clone/fam/pill/yulu",
                "/clone/fam/pill/dimai",
                "/clone/fam/gift/str2",
                "/clone/fam/gift/int2",
                "/clone/fam/gift/con2",
                "/clone/fam/gift/dex2",
                "/clone/fam/pill/full1",
                "/clone/fam/pill/full1",
                "/clone/fam/pill/linghui1",
                "/clone/fam/pill/linghui2",
                "/clone/fam/pill/neili1",
                "/clone/fam/pill/neili2",
        });

        // 完成四百个任务
        string *ob4_list = ({               
                "/clone/fam/etc/lv7c",   //青龙牙
                "/clone/fam/etc/lv7d",    //如意通天镢
                "/clone/fam/item/yanluo",
                "/clone/fam/item/lihuo",
                "/clone/fam/etc/lv7a",   //5彩珠
                "/clone/fam/pill/full1",
                "/clone/fam/pill/full1",
                "/clone/fam/pill/linghui1",
                "/clone/fam/pill/linghui1",
                "/clone/fam/pill/linghui2",
                "/clone/fam/pill/linghui2",
                "/clone/fam/pill/neili2",
                "/clone/fam/pill/neili2",
        });

        // 完成五百个任务
        string *ob5_list = ({
                "/clone/fam/gift/str3",
                "/clone/fam/gift/int3",
                "/clone/fam/gift/con3",
                "/clone/fam/gift/dex3",
                "/clone/fam/pill/full1",
                "/clone/fam/pill/full1",
                "/clone/fam/pill/linghui1",
                "/clone/fam/pill/linghui1",
                "/clone/fam/pill/linghui2",
                "/clone/fam/pill/linghui2",
                "/clone/fam/pill/neili2",
                "/clone/fam/pill/neili2",   
        });

        string gift;

        if (me->query("xquest_count") == 100)
        {
                gift = ob1_list[random(sizeof(ob1_list))];

        } else

        if (me->query("xquest_count") == 200)
        {
                gift = ob2_list[random(sizeof(ob2_list))];

         } else

        if (me->query("xquest_count") == 300)
        {
                gift = ob3_list[random(sizeof(ob3_list))];
             } else

        if (me->query("xquest_count") == 400)
        {
                gift = ob4_list[random(sizeof(ob4_list))];
             } else

        if (me->query("xquest_count") == 500)
        {
                gift = ob5_list[random(sizeof(ob5_list))];
        }

        return gift;
}
