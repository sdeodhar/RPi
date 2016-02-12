#include "MAIN.h"

void Calc_percentageFull(void)
{

}

void Disp_Mill_fill(void)
{

}

void setgainvoid()
{       
    int8u i;
    int16u max = data[0];
    for(i = 1; i < FFT_MAX_SIZE ; i++)
    {
         if(max < data[i])
            max = data[i];
    }
    if(max < 760)
    {
        cur_gain = 760 / (max/cur_gain);
    }
    else if(max > 896)
    {
        cur_gain = 896 / (max/cur_gain);
    }
    //assign value from table to correspond to case

    for(i = 0; i < 35; i++)
    {
        if( cur_gain >= gainarr[i] && cur_gain <= gainarr[i+1] )
        {
            if(cur_gain > ((gainarr[i]+gainarr[i+1])/2))
                cur_gain = gainarr[i+1];
            else
                 cur_gain = gainarr[i];

            break;
        }
    }

/******************************************      IMP NOTE     *******************************************************/
/********************************************************************************************************************/
/******************** PLEASE ADJUST S1M0 S1M1 S1M2 S2M0 S2M1 S2M2  AS PER TESTED BOARD PINS  ************************/

    switch(i)
    {
        case G0 : S1M0 = 0; S1M1 = 0; S1M2 = 0; S2M0 = 1; S2M1 = 1; S2M2 = 1; break;
        case G1 : S1M0 = 0; S1M1 = 0; S1M2 = 1; S2M0 = 1; S2M1 = 1; S2M2 = 1; break;
        case G2 : S1M0 = 0; S1M1 = 1; S1M2 = 0; S2M0 = 1; S2M1 = 1; S2M2 = 1; break;
        case G3 : S1M0 = 0; S1M1 = 1; S1M2 = 1; S2M0 = 1; S2M1 = 1; S2M2 = 1; break;
        case G4 : S1M0 = 1; S1M1 = 0; S1M2 = 0; S2M0 = 1; S2M1 = 1; S2M2 = 1; break;

        case G5 : S1M0 = 1; S1M1 = 0; S1M2 = 1; S2M0 = 1; S2M1 = 1; S2M2 = 1; break;
        case G6 : S1M0 = 1; S1M1 = 1; S1M2 = 0; S2M0 = 1; S2M1 = 1; S2M2 = 1; break;
        case G7 : S1M0 = 1; S1M1 = 1; S1M2 = 1; S2M0 = 1; S2M1 = 1; S2M2 = 1; break;
        case G8 : S1M0 = 0; S1M1 = 0; S1M2 = 0; S2M0 = 1; S2M1 = 1; S2M2 = 0; break;
        case G9 : S1M0 = 0; S1M1 = 0; S1M2 = 1; S2M0 = 1; S2M1 = 1; S2M2 = 0; break;

        case G10 : S1M0 = 0; S1M1 = 1; S1M2 = 0; S2M0 = 1; S2M1 = 1; S2M2 = 0; break;
        case G11 : S1M0 = 0; S1M1 = 1; S1M2 = 1; S2M0 = 1; S2M1 = 1; S2M2 = 0; break;
        case G12 : S1M0 = 1; S1M1 = 0; S1M2 = 0; S2M0 = 1; S2M1 = 0; S2M2 = 1; break;
        case G13 : S1M0 = 1; S1M1 = 0; S1M2 = 1; S2M0 = 1; S2M1 = 0; S2M2 = 1; break;
        case G14 : S1M0 = 1; S1M1 = 1; S1M2 = 0; S2M0 = 1; S2M1 = 0; S2M2 = 1; break;

        case G15 : S1M0 = 1; S1M1 = 1; S1M2 = 1; S2M0 = 1; S2M1 = 0; S2M2 = 1; break;
        case G16 : S1M0 = 0; S1M1 = 0; S1M2 = 0; S2M0 = 1; S2M1 = 0; S2M2 = 0; break;
        case G17 : S1M0 = 0; S1M1 = 0; S1M2 = 1; S2M0 = 1; S2M1 = 0; S2M2 = 0; break;
        case G18 : S1M0 = 0; S1M1 = 1; S1M2 = 0; S2M0 = 1; S2M1 = 0; S2M2 = 0; break;
        case G19 : S1M0 = 0; S1M1 = 1; S1M2 = 1; S2M0 = 1; S2M1 = 0; S2M2 = 0; break;

        case G20 : S1M0 = 1; S1M1 = 0; S1M2 = 0; S2M0 = 0; S2M1 = 1; S2M2 = 1; break;
        case G21 : S1M0 = 1; S1M1 = 0; S1M2 = 1; S2M0 = 0; S2M1 = 1; S2M2 = 1; break;
        case G22 : S1M0 = 1; S1M1 = 1; S1M2 = 0; S2M0 = 0; S2M1 = 1; S2M2 = 1; break;
        case G23 : S1M0 = 1; S1M1 = 1; S1M2 = 1; S2M0 = 0; S2M1 = 1; S2M2 = 1; break;
        case G24 : S1M0 = 0; S1M1 = 0; S1M2 = 0; S2M0 = 0; S2M1 = 1; S2M2 = 0; break;

        case G25 : S1M0 = 0; S1M1 = 0; S1M2 = 1; S2M0 = 0; S2M1 = 1; S2M2 = 0; break;
        case G26 : S1M0 = 0; S1M1 = 1; S1M2 = 0; S2M0 = 0; S2M1 = 1; S2M2 = 0; break;
        case G27 : S1M0 = 0; S1M1 = 1; S1M2 = 1; S2M0 = 0; S2M1 = 1; S2M2 = 0; break;
        case G28 : S1M0 = 1; S1M1 = 0; S1M2 = 0; S2M0 = 0; S2M1 = 0; S2M2 = 1; break;
        case G29 : S1M0 = 1; S1M1 = 0; S1M2 = 1; S2M0 = 0; S2M1 = 0; S2M2 = 1; break;

        case G30 : S1M0 = 1; S1M1 = 1; S1M2 = 0; S2M0 = 0; S2M1 = 0; S2M2 = 1; break;
        case G31 : S1M0 = 1; S1M1 = 1; S1M2 = 1; S2M0 = 0; S2M1 = 0; S2M2 = 1; break;
        case G32 : S1M0 = 0; S1M1 = 0; S1M2 = 0; S2M0 = 0; S2M1 = 0; S2M2 = 1; break;
        case G33 : S1M0 = 0; S1M1 = 0; S1M2 = 1; S2M0 = 0; S2M1 = 0; S2M2 = 0; break;
        case G34 : S1M0 = 0; S1M1 = 1; S1M2 = 0; S2M0 = 0; S2M1 = 0; S2M2 = 0; break;

        case G35 : S1M0 = 0; S1M1 = 1; S1M2 = 1; S2M0 = 1; S2M1 = 1; S2M2 = 1; break;
    }
}

