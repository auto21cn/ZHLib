#include <ansi.h>

mapping *quest = ({
        ([      "name":                 "少林寺",
                "dir":                  "shaolin",
                "dir1":                 "/kungfu/class/shaolin/",
                "time":                 800,
                "msg":                  "葵花太监恨恨的说：“凭什么少林寺的秃驴敢号称自己是武学正统，达摩那个老秃驴有什么了不起的？你给我到少林去，杀它个鸡犬不宁，给那帮秃驴点厉害瞧瞧！”",
                "type":                 "地点",
        ]),
        ([      "name":                 "武当",
                "dir":                  "wudang",
                "dir1":                 "/kungfu/class/wudang/",
                "time":                 900,
                "msg":                  "葵花太监冷笑着说：“武当那帮牛鼻子以为靠着张三丰这个老杂毛就可以耀武扬威了？凡是不听从我号令者唯有一个死，你去把武当血洗了吧！”",
                "type":                 "地点",
        ]),
        ([      "name":                 "桃花岛",
                "dir":                  "taohua",
                "dir1":                 "/kungfu/class/taohua/",
                "time":                 900,
                "msg":                  "葵花太监铁着脸一字一句的说：“桃花岛历来是我的死对头，黄老邪手下虽然也有个把高手，但是酒囊饭袋更多，你去桃花岛给黄老邪一点脸色看看！”",
                "type":                 "地点",
        ]),
        ([      "name":                 "白驼",
                "dir":                  "baituo",
                "dir1":                 "/kungfu/class/ouyang/",
                "time":                 900,
                "msg":                  "葵花太监挥着手不耐烦的说：“白驼山欧阳锋本人虽然马马虎虎，手下那帮弟子却着实稀松平常，溜须拍马功夫天下第一！你就去白驼山帮欧阳锋清理门户吧！”",
                "type":                 "地点",
        ]),
        ([      "name":                 "大理",
                "dir":                  "dali",
                "dir1":                 "/kungfu/class/dali/",
                "time":                 900,
                "msg":                  "葵花太监阴笑着对你说：“听说云南大理四季如春，花开遍地，那里的人生活太美好，自然就会平庸，你去大理转转，给那些愚民长长见识！”",
                "type":                 "地点",
        ]),
        ([      "name":                 "华山村",
                "dir":                  "village",
                "dir1":                 "",
                "time":                 700,
                "msg":                  "葵花太监若有所思的说：“华山村地方不大，刁民不少！宁可错杀一千，不可放过一个，杀尽华山村，给华东村，华西村一个最实在的警告！”",
                "type":                 "地点",
        ]),
        ([      "name":                 "恒山",
                "dir":                  "hengshan",
                "dir1":                 "",
                "time":                 800,
                "msg":                  "葵花太监低头寻思良久道：“北岳恒山百年前很是辉煌，现在没落至此，其门人子弟实在该承担主要责任，你就去把这帮没用的饭桶杀个人仰马翻吧！”",
                "type":                 "地点",
        ]),
        ([      "name":                 "衡山",
                "dir":                  "henshan",
                "dir1":                 "",
                "time":                 800,
                "msg":                  "葵花太监冷冷笑道：“南岳衡山除了野心大，武功实在稀松平常，里面的人物更是一个比一个不入流，去，血洗衡山，让他们也尝尝灭族的滋味！”",
                "type":                 "地点",
        ]),
        ([      "name":                 "华山",
                "dir":                  "huashan",
                "dir1":                 "/kungfu/class/huashan/",
                "time":                 800,
                "msg":                  "葵花太监怒气冲冲的说：“华山派岳不群这个伪君子又在假仁假义的说教，这狗贼手下的弟子也是不辨黑白，不明事理，你去封了华山派的嘴！”",
                "type":                 "地点",
        ]),
        ([      "name":                 "男子",
                "dir":                  "",
                "dir1":                 "",
                "time":                 700,
                "msg":                  "葵花太监尖声叫道：“那些小白脸整天晃来晃去不务正业，四处散布我的坏话，你赶快去把他们统统杀了！”",
                "type":                 "",
        ]),
        ([      "name":                 "女子",
                "dir":                  "",
                "dir1":                 "",
                "time":                 600,
                "msg":                  "葵花太监咬牙切齿的说：“我平素最痛恨的除了那些小白脸，还有就是女人！凭什么她们可以打扮的花枝招展，去，把她们统统都给我杀光！”",
                "type":                 "地点",
        ]),
        ([      "name":                 "古墓",
                "dir":                  "gumu",
                "dir1":                 "/kungfu/class/gumu/",
                "time":                 800,
                "msg":                  "葵花太监面色铁青冷冷对你说：“古墓派和全真派有重新联手的迹象，这对我大大的不利，你去把古墓屠个鸡犬不留，绝了全真派的后路！”",
                "type":                 "地点",
        ]),
        ([      "name":                 "全真",
                "dir":                  "quanzhen",
                "dir1":                 "/kungfu/class/quanzhen/",
                "time":                 800,
                "msg":                  "葵花太监长叹一声道：“我前日已经派人屠了古墓，全真派王重阳老牛鼻子又在闭关，这个眼中钉此时不拔更待何时？去把全真给我灭了！”",
                "type":                 "地点",
        ]),
        ([      "name":                 "峨嵋",
                "dir":                  "emei",
                "dir1":                 "/kungfu/class/emei/",
                "time":                 800,
                "msg":                  "葵花太监深吸了一口气道：“峨嵋派的灭绝老贼尼讲话动不动就正派邪派，我看这老尼姑本身就不是什么好东西，上梁不正下梁歪，你去把峨嵋给我杀个干干净净！”",
                "type":                 "地点",
        ]),
        ([      "name":                 "星宿",
                "dir":                  "xingxiu",
                "dir1":                 "/kungfu/class/xingxiu/",
                "time":                 800,
                "msg":                  "葵花太监哑然失笑道：“我听说星宿丁老怪最近又被弟子耍了，这个老杂毛爱听马屁终于听出事了，算了，你就帮帮他，去星宿教训教训那帮不孝弟子吧！”",
                "type":                 "地点",
        ]),
        ([      "name":                 "血刀门",
                "dir":                  "xuedao",
                "dir1":                 "/kungfu/class/xuedao/",
                "time":                 800,
                "msg":                  "葵花太监冷声长笑：“血刀门素然有意逐鹿中原，本来我对他们睁只眼闭只眼，没想前日居然胆敢杀了我安插在血刀门的密探，去给他们血的教训吧！”",
                "type":                 "地点",
        ]),
        ([      "name":                 "泰山",
                "dir":                  "taishan",
                "dir1":                 "",
                "time":                 700,
                "msg":                  "葵花太监不屑的摇头：“泰山派那帮蠢材年纪有了一把，混来混去还是一群跑龙套的，连我都看不下去了，你把他们送到阎王哪里跑龙套去吧！”",
                "type":                 "地点",
        ]),
        ([      "name":                 "灵鹫宫",
                "dir":                  "lingjiu",
                "dir1":                 "/kungfu/class/lingjiu/",
                "time":                 700,
                "msg":                  "葵花太监微微一笑：“灵鹫宫本来可以一统江湖，偏偏天山童姥那小女人误己于情情爱爱，真是头发长，见识短！灭了灵鹫，不要心慈手软！”",
                "type":                 "地点",
        ]),
        ([      "name":                 "襄阳",
                "dir":                  "xiangyang",
                "dir1":                 "",
                "time":                 600,
                "msg":                  "葵花太监沉思片刻，忽怒击一掌，恨恨道：“襄阳的百姓危难当头如此依赖郭靖夫妇，却无办点自救的举措，你去把襄阳给我血洗了！”",
                "type":                 "地点",
        ]),
        ([      "name":                 "北京",
                "dir":                  "beijing",
                "dir1":                 "",
                "time":                 900,
                "msg":                  "葵花太监格格一笑，轻轻说到：“皇上昨日出巡，北京城里居然有桀骜不驯之徒暗中辱骂皇上，宁可错杀一千，不可放过一个，你知道该怎么做了？”",
                "type":                 "地点",
        ]),
        ([      "name":                 "长安",
                "dir":                  "changan",
                "dir1":                 "",
                "time":                 800,
                "msg":                  "葵花太监悠悠的说：“长安十里繁华之地，男男女女都在温柔乡里、富贵场中，我倒是想看看这些良民最近生活如何，你去弄些头颅来给我看看血色就成！”",
                "type":                 "地点",
        ]),
        ([      "name":                 "成都",
                "dir":                  "city3",
                "dir1":                 "",
                "time":                 700,
                "msg":                  "葵花太监咬牙切齿的嘶喉：“前日我去成都，那里的刁民居然骂我是龟儿子，不让成都血流成河，难解我心头之气！如何？有困难么？好好去干！”",
                "type":                 "地点",
        ]),
        ([      "name":                 "大理",
                "dir":                  "dali",
                "dir1":                 "",
                "time":                 700,
                "msg":                  "葵花太监指指窗外一丛茶花，生气的说：“大理上月进贡来的茶花，至今尚未有开花的，想来是故意愚弄我，血洗大理！这就是愚弄我的下场！”",
                "type":                 "地点",
        ]),
        ([      "name":                 "黑木崖",
                "dir":                  "heimuya",
                "dir1":                 "",
                "time":                 700,
                "msg":                  "葵花太监轻笑着说：“东方不败躲在黑木崖干嘛？好久没见到他了，偷走了我的葵花宝典，也该付出点代价了，你去黑木崖走走，自己看着办好了。”",
                "type":                 "地点",
        ]),
        ([      "name":                 "杭州",
                "dir":                  "hangzhou",
                "dir1":                 "",
                "time":                 800,
                "msg":                  "葵花太监眯着眼睛说：“上有天堂，下有苏杭，杭州是个好地方那，听说西湖风光无限，不知道如果湖水都是红色看起来如何？你去杭州给西湖加点血色吧！”",
                "type":                 "地点",
        ]),
        ([      "name":                 "苏州",
                "dir":                  "suzhou",
                "dir1":                 "",
                "time":                 800,
                "msg":                  "葵花太监阴笑着说：“苏州的园林是一天比一天美丽了，号称人间天堂？我要叫他们知道我可以让天堂变成地狱！你去苏州造一个人间地狱出来吧！”",
                "type":                 "地点",
        ]),
        ([      "name":                 "扬州",
                "dir":                  "city",
                "dir1":                 "",
                "time":                 900,
                "msg":                  "葵花太监不屑的说：“扬州号称繁华要地，其实也就是一群娘们在卖弄风骚，什么丽春院丽夏院，你去把扬州给我铲平了，我叫他们去爽！”",
                "type":                 "地点",
        ]),
});

mapping query_questkill()
{
        return quest[random(sizeof(quest))];
}
