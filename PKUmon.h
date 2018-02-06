#ifndef PKUMON_H
#define PKUMON_H

#include"Battle.h"//各个数据头文件的包含关系为Constant.h->Skill.h->Monster.h->AIDecision.h->People.h->Battle.h->PKUmon.h

//skill的构造需要注明升级的级别数
#define Math_JX skill("极限",40,0,0.1,1.5,new skill(Math_JX_XFJX),6)
#define Math_JX_XFJX skill("旭峰极限",50,0,0.2,1.5)
#define Math_QD skill("求导",40,0,0.1,1.5,new skill(Math_QD_GJDS),6)
#define Math_QD_GJDS skill("高阶导数",50,0,0.1,1.5)
#define Math_PDS skill("偏导数",120,20,0.2,2.0,new skill(Math_PDS_PWFFC),12)
#define Math_PDS_PWFFC skill("偏微分方程",140,25,0.1,2.0)
#define Math_TYJF skill("椭圆积分",120,15,0.1,2.0,new skill(Math_TYJF_GSYX),12)
#define Math_TYJF_GSYX skill("高斯游戏",150,20,0.1,2.0)
#define Math_GDSX_1 mon(new MathMonIcon(),"高等数学",400,70,new skill(Math_JX),new skill(Math_PDS),500)
#define Math_GDSX_2 mon(new MathMonIcon(),"高等数学",400,70,new skill(Math_JX),new skill(Math_TYJF),500)
#define Math_GDSX_3 mon(new MathMonIcon(),"高等数学",400,70,new skill(Math_QD),new skill(Math_PDS),500)
#define Math_GDSX_4 mon(new MathMonIcon(),"高等数学",400,70,new skill(Math_QD),new skill(Math_TYJF),500)

#define Math_XXYS skill("线性映射",40,0,0.3,1.5,new skill(Math_XXYS_KNYS),6)
#define Math_XXYS_KNYS skill("可逆映射",50,0,0.3,1.5)
#define Math_SSJ skill("上三角",40,0,0.2,1.5,new skill(Math_SSJ_DJH),6)
#define Math_SSJ_DJH skill("对角化",50,0,0.2,1.5)
#define Math_BZXL skill("本征向量",180,25,0.1,2.0,new skill(Math_BZXL_GYBZXL),12)
#define Math_BZXL_GYBZXL skill("广义本征向量",200,30,0.1,2.0)
#define Math_FNJ skill("复内积",140,25,0.2,2.0,new skill(Math_FNJ_SNJ),12)
#define Math_FNJ_SNJ skill("实内积",160,30,0.2,2.0)
#define Math_XXDS_1 mon(new MathMonIcon(),"线性代数",300,80,new skill(Math_XXYS),new skill(Math_BZXL),600)
#define Math_XXDS_2 mon(new MathMonIcon(),"线性代数",300,80,new skill(Math_XXYS),new skill(Math_FNJ),600)
#define Math_XXDS_3 mon(new MathMonIcon(),"线性代数",300,80,new skill(Math_SSJ),new skill(Math_BZXL),600)
#define Math_XXDS_4 mon(new MathMonIcon(),"线性代数",300,80,new skill(Math_SSJ),new skill(Math_FNJ),600)

#define PHYSICS_ZDZ skill("质点组",40,0,0.2,1.5,new skill(PHYSICS_ZDZ_GTDL),6)
#define PHYSICS_ZDZ_GTDL skill("刚体动力",50,0,0.3,1.5)
#define PHYSICS_XZD skill("谐振动",40,0,0.3,1.5,new skill(PHYSICS_XZD_ZNZD),6)
#define PHYSICS_XZD_ZNZD skill("阻尼振动",50,0,0.4,1.5)
#define PHYSICS_CLLX skill("材料力学",140,20,0.1,2.0,new skill(PHYSICS_CLLX_LTLX),12)
#define PHYSICS_CLLX_LTLX skill("流体力学",160,25,0.2,2.0)
#define PHYSICS_LLZBH skill("洛伦兹变换",120,15,0.4,2.0,new skill(PHYSICS_LLZBH_DCCZL),12)
#define PHYSICS_LLZBH_DCCZL skill("电磁场张量",180,30,0.9,2.0)
#define PHYSICS_LX_1 mon(new PhysicsMonIcon(),"力学",350,70,new skill(PHYSICS_ZDZ),new skill(PHYSICS_CLLX),450)
#define PHYSICS_LX_2 mon(new PhysicsMonIcon(),"力学",350,70,new skill(PHYSICS_ZDZ),new skill(PHYSICS_LLZBH),450)
#define PHYSICS_LX_3 mon(new PhysicsMonIcon(),"力学",350,70,new skill(PHYSICS_XZD),new skill(PHYSICS_CLLX),450)
#define PHYSICS_LX_4 mon(new PhysicsMonIcon(),"力学",350,70,new skill(PHYSICS_XZD),new skill(PHYSICS_LLZBH),450)

#define PHYSICS_JDC skill("静电场",40,0,0.3,1.5,new skill(PHYSICS_JDC_JBDC),6)
#define PHYSICS_JDC_JBDC skill("交变电场",50,0,0.2,1.5)
#define PHYSICS_JCC skill("静磁场",40,0,0.1,1.5,new skill(PHYSICS_JCC_JBCC),6)
#define PHYSICS_JCC_JBCC skill("交变磁场",50,0,0.6,1.5)
#define PHYSICS_DCJZ skill("电磁介质",120,20,0.2,2.0,new skill(PHYSICS_DCJZ_FXXJZ),12)
#define PHYSICS_DCJZ_FXXJZ skill("非线性介质",150,25,0.2,2.0)
#define PHYSICS_MKSW skill("麦克斯韦",130,20,0.4,2.0,new skill(PHYSICS_MKSW_PMXB),12)
#define PHYSICS_MKSW_PMXB skill("平面谐波",150,25,0.3,2.0)
#define PHYSICS_DCX_1 mon(new PhysicsMonIcon(),"电磁学",500,60,new skill(PHYSICS_JDC),new skill(PHYSICS_DCJZ),550)
#define PHYSICS_DCX_2 mon(new PhysicsMonIcon(),"电磁学",500,60,new skill(PHYSICS_JDC),new skill(PHYSICS_MKSW),550)
#define PHYSICS_DCX_3 mon(new PhysicsMonIcon(),"电磁学",500,60,new skill(PHYSICS_JCC),new skill(PHYSICS_DCJZ),550)
#define PHYSICS_DCX_4 mon(new PhysicsMonIcon(),"电磁学",500,60,new skill(PHYSICS_JCC),new skill(PHYSICS_MKSW),550)

#define POLITICS_SZBF skill("孙子兵法",40,0,0.2,1.5,new skill(POLITICS_SZBF_MZDSX),6)
#define POLITICS_SZBF_MZDSX skill("毛泽东思想",50,0,0.4,1.5)
#define POLITICS_JXHZZ skill("机械化战争",40,0,0.3,1.5,new skill(POLITICS_JXHZZ_XXHZZ),6)
#define POLITICS_JXHZZ_XXHZZ skill("信息化战争",50,0,0.5,1.5)
#define POLITICS_ZGWZ skill("中国武装",140,25,0.2,2.0,new skill(POLITICS_ZGWZ_SJZL),12)
#define POLITICS_ZGWZ_SJZL skill("世界战略",150,25,0.2,2.0)
#define POLITICS_JXDL skill("军训队列",120,15,0.6,2.0,new skill(POLITICS_JXDL_JXSDSJ),12)
#define POLITICS_JXDL_JXSDSJ skill("军训实弹射击",130,25,0.3,2.0)
#define POLITICS_JSLL_1 mon(new PoliticsMonIcon(),"军事理论",450,60,new skill(POLITICS_SZBF),new skill(POLITICS_ZGWZ),500)
#define POLITICS_JSLL_2 mon(new PoliticsMonIcon(),"军事理论",450,60,new skill(POLITICS_SZBF),new skill(POLITICS_JXDL),500)
#define POLITICS_JSLL_3 mon(new PoliticsMonIcon(),"军事理论",450,60,new skill(POLITICS_JXHZZ),new skill(POLITICS_ZGWZ),500)
#define POLITICS_JSLL_4 mon(new PoliticsMonIcon(),"军事理论",450,60,new skill(POLITICS_JXHZZ),new skill(POLITICS_JXDL),500)

#define POLITICS_YPZZ skill("鸦片战争",40,0,0.2,1.5,new skill(POLITICS_YPZZ_XHGM),6)
#define POLITICS_YPZZ_XHGM skill("辛亥革命",50,0,0.3,1.5)
#define POLITICS_WSYD skill("五四运动",40,0,0.1,1.5,new skill(POLITICS_WSYD_FFXSZZ),6)
#define POLITICS_WSYD_FFXSZZ skill("反法西斯战争",50,0,0.2,1.5)
#define POLITICS_XZGCL skill("新中国成立",120,20,0.3,2.0,new skill(POLITICS_XZGCL_SNWG),12)
#define POLITICS_XZGCL_SNWG skill("十年文革",140,25,0.3,2.0)
#define POLITICS_GGKF skill("改革开放",140,30,0.2,2.0,new skill(POLITICS_GGKF_ZGM),12)
#define POLITICS_GGKF_ZGM skill("中国梦",150,30,0.3,2.0)
#define POLITICS_JXDSGY_1 mon(new PoliticsMonIcon(),"近现代史纲要",550,60,new skill(POLITICS_YPZZ),new skill(POLITICS_XZGCL),450)
#define POLITICS_JXDSGY_2 mon(new PoliticsMonIcon(),"近现代史纲要",550,60,new skill(POLITICS_YPZZ),new skill(POLITICS_GGKF),450)
#define POLITICS_JXDSGY_3 mon(new PoliticsMonIcon(),"近现代史纲要",550,60,new skill(POLITICS_WSYD),new skill(POLITICS_XZGCL),450)
#define POLITICS_JXDSGY_4 mon(new PoliticsMonIcon(),"近现代史纲要",550,60,new skill(POLITICS_WSYD),new skill(POLITICS_GGKF),450)

//构建函数
#define COURSEAMOUNT 6
studentData opponent(const playerData&);

//人物库
#define B_1 mon(PHYSICS_DCX_3,2)
#define B_2 mon(PHYSICS_DCX_2,3)
#define B_3 mon(PHYSICS_DCX_4,4)
#define B_Bag backpack(B_1,B_2,B_3,2,1,1,700)
#define _B_ characterData("B",B_Bag,new superSkill)

#define D_1 mon(Math_GDSX_3,5)
#define D_2 mon(PHYSICS_LX_2,6)
#define D_3 mon(POLITICS_JSLL_1,6)
#define D_Bag backpack(D_1,D_2,D_3,3,2,1,1500)
#define _D_ characterData("D",D_Bag,new superSkill)

#endif
