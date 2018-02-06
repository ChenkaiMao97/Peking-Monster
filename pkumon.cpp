#include"PKUmon.h"
#include<cstdlib>
studentData opponent(const playerData& I)
{
    int i[2], j, k;
    mon m[2];

    for(k=0;k<2;k++)
    {
        if(k==0)i[0] = rand()%COURSEAMOUNT+1;
        else do{i[1] = rand()%COURSEAMOUNT+1;}while(i[1]==i[0]);
        j = rand()%4+1;
        switch(i[k])
        {
        case 1://高等数学
            switch(j)
            {case 1:m[k] = Math_GDSX_1; break;
            case 2:m[k] = Math_GDSX_2; break;
            case 3:m[k] = Math_GDSX_3; break;
            case 4:m[k] = Math_GDSX_4; break;
            default:break;};break;
        case 2://线性代数
            switch(j)
            {case 1:m[k] = Math_XXDS_1; break;
            case 2:m[k] = Math_XXDS_2; break;
            case 3:m[k] = Math_XXDS_3; break;
            case 4:m[k] = Math_XXDS_4; break;
            default:break;};break;
        case 3://力学
            switch(j)
            {case 1:m[k] = PHYSICS_LX_1; break;
            case 2:m[k] = PHYSICS_LX_2; break;
            case 3:m[k] = PHYSICS_LX_3; break;
            case 4:m[k] = PHYSICS_LX_4; break;
            default:break;}break;
        case 4://电磁学
            switch(j)
            {case 1:m[k] = PHYSICS_DCX_1; break;
            case 2:m[k] = PHYSICS_DCX_2; break;
            case 3:m[k] = PHYSICS_DCX_3; break;
            case 4:m[k] = PHYSICS_DCX_4; break;
            default:break;}break;
        case 5://军事理论
            switch(j)
            {case 1:m[k] = POLITICS_JSLL_1; break;
            case 2:m[k] = POLITICS_JSLL_2; break;
            case 3:m[k] = POLITICS_JSLL_3; break;
            case 4:m[k] = POLITICS_JSLL_4; break;
            default:break;}break;
        case 6://近现代史纲要
            switch(j)
            {case 1:m[k] = POLITICS_JXDSGY_1; break;
            case 2:m[k] = POLITICS_JXDSGY_2; break;
            case 3:m[k] = POLITICS_JXDSGY_3; break;
            case 4:m[k] = POLITICS_JXDSGY_4; break;
            default:break;}break;
        default:break;
        };
    }

    backpack bag(m[0],m[1],rand()%4,rand()%2,rand()%2,rand()%1001);
    j = I.grade()-rand()%2;//student的年级不应该比玩家高
    j = j>1?j:1; j = j<4?j:4;
    bag.pocket[0]->setLevel(j*5-rand()%5);
    bag.pocket[1]->setLevel(j*5-rand()%5);
    return studentData(NULL,bag,j);
}
