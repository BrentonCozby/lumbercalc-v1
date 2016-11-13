#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "schematics.h"

// how to use this app:
// 1. navigate to the folder with lumbercalc-1.c
// 2. in the console, type ./lumbercalc-1

/*Planning:

Vision:
lumbercalc will be calculate the optimal number of planks of lumber to order, per size, depending on 
the number of pieces per measurement per plank size per build (bench or table, etc.c) needed and the
total number of builds needed.

It will do this by calculating the lowest amount of planks per plank size required to fit the total
amount of pieces per measurement per plank size needed, for each measurement.

It will also optimize the results so that the least amount of scrap wood is left over. It will do
this by comparing all the measurements needed and the pieces per measurement, and then using an if else
series similar to the one used in changecalc, it will calculate how to fit all the pieces per
measurement for the total number of benches into the least amount of planks. It will use code similar
to changecalc when calculating which mix of measurements to fit into a plank.

lumbercalc will have the cutlist with measurements & quantities for each schematic, stored in a structs,
which the user can call to be used by lumbercalc (instead of entering in all this information manually).
However, there will be an option that lets the user enter custom measurements.

lumbercalc will output the total number of planks to order per plank size

Steps to create:
1) define the needed variables
2) "How many builds of the schemtic do you need? In other words, how many benches/tables do you need?"
3) "I will now ask you for the measurements and the amounts that you need for 4 different plank sizes.
    Do you need planks of size 2x4? (y or n)"
4) "Give me one of the measurements for the 2x4 planks."
5) "How many pieces of that measurement do you need per schematic?"
6) "Does this plank size require another measurement? (y or n)"
7) if (y), ask for another measurement
8) if (n), move on to the next plank size
    1) "Do you need another plank size? (y or n)"
    2) if (y), copy steps 3 - 8
9) "Do you need planks of size 2x6? (y or n)"
    - if (y), repeat steps 4 - 8. else move on to next plank size
    - Repeat steps 3 - 9 for plank size 2x8 and 4x4
    - When user inputs "n" for the last question on plank size 4x4, move on to step 10
10) "Calculating your optimized lumber order..."
11)

*/

int CustomSchem(int lumber_size, int builds);
int Optimize_Custom(int builds, float piece_length, int piece_num, int lumber_size);
int Optimize_Schem(int builds, float piece_length, int piece_num, int lumber_size);

int main(void)
{
    lumber sizes[4];
    
    sizes[0].dimensions = "2x4";
    sizes[1].dimensions = "2x6";
    sizes[2].dimensions = "2x12";
    sizes[3].dimensions = "4x4";
    
    for (int i = 0; i <= 3; i++)
    {
        sizes[i].eight = 96;
        sizes[i].ten = 120;
        sizes[i].twelve = 144;
    }
    
    int* schem_i = malloc(sizeof(int));
    printf("\nWhich schematic do you need lumber for? Enter one of the following numbers:\n 1 for Concrete Simple Bench\n 2 for Backed Bench\n 3 for Picnic Table 2 legs\n 4 for Double Planter Box\n 10 for Other\n\n");
    scanf("%d", schem_i);
    
    int* builds = malloc(sizeof(int));
    printf("\nHow many builds of this schematic do you plan to build?\n");
    scanf("%d", builds);
    
    // Concrete Simple Bench
    if (*schem_i == 1)
    {
        int cut_quant = 3;
        
        float piece_length[cut_quant];
        int piece_num[cut_quant];
        int lumber_size[cut_quant];
        
        piece_length[0] = 36;
        piece_length[1] = 66;
        piece_length[2] = 72;
        
        piece_num[0] = 3;
        piece_num[1] = 2;
        piece_num[2] = 1;
        
        lumber_size[0] = 4;
        lumber_size[1] = 1;
        lumber_size[2] = 3;
        
        for (int i = 0; i < cut_quant; i++)
            Optimize_Schem(*builds, piece_length[i], piece_num[i], lumber_size[i]);
    }
    
    // Backed Bench
    if (*schem_i == 2)
    {
        int cut_quant = 4;
        
        float piece_length[cut_quant];
        int piece_num[cut_quant];
        int lumber_size[cut_quant];
        
        piece_length[0] = 60;
        piece_length[1] = 17;
        piece_length[2] = 35;
        piece_length[3] = 72;
        
        piece_num[0] = 7;
        piece_num[1] = 8;
        piece_num[2] = 2;
        piece_num[3] = 2;
        
        lumber_size[0] = 2;
        lumber_size[1] = 2;
        lumber_size[2] = 2;
        lumber_size[3] = 2;
        
        for (int i = 0; i < cut_quant; i++)
            Optimize_Schem(*builds, piece_length[i], piece_num[i], lumber_size[i]);
    }
    
    // Picnic Table 2 Legs
    if (*schem_i == 3)
    {
        int cut_quant = 5;
        
        float piece_length[cut_quant];
        int piece_num[cut_quant];
        int lumber_size[cut_quant];
        
        piece_length[0] = 66;
        piece_length[1] = 39.5;
        piece_length[2] = 34.5;
        piece_length[3] = 32;
        piece_length[4] = 96;
        
        piece_num[0] = 2;
        piece_num[1] = 4;
        piece_num[2] = 4;
        piece_num[3] = 2;
        piece_num[4] = 10;
        
        lumber_size[0] = 2;
        lumber_size[1] = 2;
        lumber_size[2] = 1;
        lumber_size[3] = 1;
        lumber_size[4] = 2;
        
        for (int i = 0; i < cut_quant; i++)
            Optimize_Schem(*builds, piece_length[i], piece_num[i], lumber_size[i]);
    }
    
    // Double Planter Box
    if (*schem_i == 4)
    {
        int cut_quant = 9;
        
        float piece_length[cut_quant];
        int piece_num[cut_quant];
        int lumber_size[cut_quant];
        
        piece_length[0] = 22.5;
        piece_length[1] = 21;
        piece_length[2] = 17;
        piece_length[3] = 14;
        piece_length[4] = 24;
        piece_length[5] = 96;
        piece_length[6] = 93;
        piece_length[7] = 45;
        piece_length[8] = 21;
        
        piece_num[0] = 26;
        piece_num[1] = 12;
        piece_num[2] = 8;
        piece_num[3] = 4;
        piece_num[4] = 8;
        piece_num[5] = 1;
        piece_num[6] = 1;
        piece_num[7] = 5;
        piece_num[8] = 14;
        
        lumber_size[0] = 1;
        lumber_size[1] = 1;
        lumber_size[2] = 1;
        lumber_size[3] = 1;
        lumber_size[4] = 1;
        lumber_size[5] = 1;
        lumber_size[6] = 1;
        lumber_size[7] = 1;
        lumber_size[8] = 1;
        
        for (int i = 0; i < cut_quant; i++)
            Optimize_Schem(*builds, piece_length[i], piece_num[i], lumber_size[i]);
    }
    
    // Custom Schematic
    if (*schem_i == 10)
    {
        int* lumber_num = malloc(sizeof(int));
        if (lumber_num == 0)
    	{
    		printf("ERROR: Out of memory\n");
    		return 1;
    	}
        
        printf("\nHow many different lumber sizes does this schematic need?\n");
        scanf("%d", lumber_num);
        
        for (int j = 0; j < *lumber_num; j++)
        {
            int* lumber_size = malloc(sizeof(int));
            if (lumber_size == 0)
    	    {
    		    printf("ERROR: Out of memory\n");
    		    return 1;
    	    }
            *lumber_size = 0;
            
            if (j == 0)
            {
                printf("\nWhich lumber size would you like to calculate first? Enter one of the following numbers:\n 1 for 2x4\n 2 for 2x6\n 3 for 2x12\n 4 for 4x4\n\n");
                scanf("%d", lumber_size);
            }
            else if (j == *lumber_num - 1)
            {
                printf("\nWhat is the final lumber size you would like to calculate? Enter one of the following numbers:\n 1 for 2x4\n 2 for 2x6\n 3 for 2x12\n 4 for 4x4\n\n");
                scanf("%d", lumber_size);
            }
            else
            {
                printf("\nWhich lumber size would you like to calculate next? Enter one of the following numbers:\n 1 for 2x4\n 2 for 2x6\n 3 for 2x12\n 4 for 4x4\n\n");
                scanf("%d", lumber_size);
            }
            CustomSchem(*lumber_size, *builds);
            
            free(lumber_size);
        }
        
        free(lumber_num);
    }
    
    // Calculations
    
    
    free(schem_i);
    free(builds);
}

//function formulas
int CustomSchem(int lumber_size, int builds)
{
    char* dim[4] = {"2x4", "2x6", "2x12", "4x4"};
    int* cut_num = malloc(sizeof(int));
    if (cut_num == 0)
	{
		printf("ERROR: Out of memory\n");
		return 1;
	}
    
    printf("\nHow many different cut lengths of size %s do you need?\n", dim[lumber_size - 1]);
    scanf("%d", cut_num);
    
    cut piece[*cut_num];
    
    for (int i = 0; i < *cut_num; i++)
    {
        if (lumber_size == 1)
        {
            piece[i].dimensions = "2x4";  
        }
        else if (lumber_size == 2)
        {
            piece[i].dimensions = "2x6";  
        }
        else if (lumber_size == 3)
        {
            piece[i].dimensions = "2x12";  
        }
        else if (lumber_size == 4)
        {
            piece[i].dimensions = "4x4";
        }
    }
    
    for (int i = 0; i < *cut_num; i++)
    {
        if (i == 0 && *cut_num == 1)
        {
            printf("\nWhat is the cut length for lumber size %s, in inches?\n", dim[lumber_size - 1]);
            scanf("%f", &(piece[i].length));
            
            if (((int)(10 * piece[i].length) % 10) == 0)
            {    
                printf("\nHow many cuts of size %sx%.0f do you need, per build?\n", dim[lumber_size - 1], piece[i].length);
                scanf("%f", &(piece[i].quantity));
            }
            else
            {
                printf("\nHow many cuts of size %sx%.1f do you need, per build?\n", dim[lumber_size - 1], piece[i].length);
                scanf("%f", &(piece[i].quantity));
            }
        }
        else if (i == 0 && *cut_num > 1)
        {
            printf("\nWhat is the cut length for lumber size %s, in inches?\n", dim[lumber_size - 1]);
            scanf("%f", &(piece[i].length));
            
            if (((int)(10 * piece[i].length) % 10) == 0)
            {    
                printf("\nHow many cuts of size %sx%.0f do you need, per build?\n", dim[lumber_size - 1], piece[i].length);
                scanf("%f", &(piece[i].quantity));
            }
            else
            {
                printf("\nHow many cuts of size %sx%.1f do you need, per build?\n", dim[lumber_size - 1], piece[i].length);
                scanf("%f", &(piece[i].quantity));
            }
        }
        else if (i == *cut_num - 1)
        {
            printf("\nWhat is the cut length for lumber size %s, in inches?\n", dim[lumber_size - 1]);
            scanf("%f", &(piece[i].length));
            
            if (((int)(10 * piece[i].length) % 10) == 0)
            {    
                printf("\nHow many cuts of size %sx%.0f do you need, per build?\n", dim[lumber_size - 1], piece[i].length);
                scanf("%f", &(piece[i].quantity));
            }
            else
            {
                printf("\nHow many cuts of size %sx%.1f do you need, per build?\n", dim[lumber_size - 1], piece[i].length);
                scanf("%f", &(piece[i].quantity));
            }
        }
        else
        {
            printf("\nWhat is the cut length for lumber size %s, in inches?\n", dim[lumber_size - 1]);
            scanf("%f", &(piece[i].length));
            
            if (((int)(10 * piece[i].length) % 10) == 0)
            {    
                printf("\nHow many cuts of size %sx%.0f do you need, per build?\n", dim[lumber_size - 1], piece[i].length);
                scanf("%f", &(piece[i].quantity));
            }
            else
            {
                printf("\nHow many cuts of size %sx%.1f do you need, per build?\n", dim[lumber_size - 1], piece[i].length);
                scanf("%f", &(piece[i].quantity));
            }
        }
        
        if (((int)(10 * piece[i].length) % 10) == 0)
        {
            printf("\nYour measurements and quantities:");
            for (int k = 0; k < *cut_num; k++)
                printf("\n%sx%.0f: %.0f\n", piece[i].dimensions, piece[i].length, piece[i].quantity);
        }
        else
        {
            printf("\nYour measurements and quantities:");
            for (int k = 0; k < *cut_num; k++)
                printf("\n%sx%.1f: %.0f\n", piece[i].dimensions, piece[i].length, piece[i].quantity);
        }
        
        Optimize_Custom(builds, piece[i].length, piece[i].quantity, lumber_size);
    }
    
    free(cut_num);
    
    return 0;
}

int Optimize_Custom(int builds, float piece_length, int piece_num, int lumber_size)
{
    char* dim[4] = {"2x4", "2x6", "2x12", "4x4"};
    
    lumber sizes[4];
    sizes[0].dimensions = "2x4";
    sizes[1].dimensions = "2x6";
    sizes[2].dimensions = "2x12";
    sizes[3].dimensions = "4x4";
    
    for (int i = 0; i <= 3; i++)
    {
        sizes[i].eight = 96;
        sizes[i].ten = 120;
        sizes[i].twelve = 144;
    }
    
    printf("\nQuantity of lumber size %s to order for this schematic:", dim[lumber_size - 1]);
    printf("\n   8-ft:  %2.0f  scrap:  %2.1f\"", ceil((piece_num * builds) / floor((sizes[lumber_size - 1].eight) / piece_length)), (sizes[lumber_size - 1].eight - (floor((sizes[lumber_size - 1].eight) / piece_length) * piece_length)));
    printf("\n  10-ft:  %2.0f  scrap:  %2.1f\"", ceil((piece_num * builds) / floor((sizes[lumber_size - 1].ten) / piece_length)), (sizes[lumber_size - 1].ten - (floor((sizes[lumber_size - 1].ten) / piece_length) * piece_length)));
    printf("\n  12-ft:  %2.0f  scrap:  %2.1f\"\n", ceil((piece_num * builds) / floor((sizes[lumber_size - 1].twelve) / piece_length)), (sizes[lumber_size - 1].twelve - (floor((sizes[lumber_size - 1].twelve) / piece_length) * piece_length)));
    
    int check = 0;
    printf("\n^^Did you write this down? If yes, enter 1. \n");
    scanf("%d", &check);
    
    while (check != 1)
    {
        printf("\nWRITE IT DOWN!! And then enter 1. \n");
        scanf("%d", &check);
    }    
    return 0;
}

int Optimize_Schem(int builds, float piece_length, int piece_num, int lumber_size)
{
    // initialize lumber variables from shematics.h
        char* dim[4] = {"2x4", "2x6", "2x12", "4x4"};
        
        lumber sizes[4];
        sizes[0].dimensions = "2x4";
        sizes[1].dimensions = "2x6";
        sizes[2].dimensions = "2x12";
        sizes[3].dimensions = "4x4";
        
        for (int i = 0; i <= 3; i++)
        {
            sizes[i].eight = 96;
            sizes[i].ten = 120;
            sizes[i].twelve = 144;
        }
        
        sizes[0].price_eight = 4.57;
        sizes[0].price_ten = 5.67;
        sizes[0].price_twelve = 6.97;
        sizes[1].price_eight = 5.97;
        sizes[1].price_ten = 7.47;
        sizes[1].price_twelve = 8.87;
        sizes[2].price_eight = 18.97;
        sizes[2].price_ten = 22.97;
        sizes[2].price_twelve = 28.57;
        sizes[3].price_eight = 8.67;
        sizes[3].price_ten = 12.77;
        sizes[3].price_twelve = 15.27;
    
    //Calculations
        float lum_quant_eight = ceil((piece_num * builds) / floor((sizes[lumber_size - 1].eight) / piece_length));
        float scrap_eight = (sizes[lumber_size - 1].eight - (floor((sizes[lumber_size - 1].eight) / piece_length) * piece_length));
        float total_scrap_eight = lum_quant_eight * scrap_eight;
        float total_price_eight = lum_quant_eight * sizes[lumber_size - 1].price_eight;
        
        float lum_quant_ten = ceil((piece_num * builds) / floor((sizes[lumber_size - 1].ten) / piece_length));
        float scrap_ten = (sizes[lumber_size - 1].ten - (floor((sizes[lumber_size - 1].ten) / piece_length) * piece_length));
        float total_scrap_ten = lum_quant_ten * scrap_ten;
        float total_price_ten = lum_quant_ten * sizes[lumber_size - 1].price_ten;
        
        float lum_quant_twelve = ceil((piece_num * builds) / floor((sizes[lumber_size - 1].twelve) / piece_length));
        float scrap_twelve = (sizes[lumber_size - 1].twelve - (floor((sizes[lumber_size - 1].twelve) / piece_length) * piece_length));
        float total_scrap_twelve = lum_quant_twelve * scrap_twelve;
        float total_price_twelve = lum_quant_twelve * sizes[lumber_size - 1].price_twelve;
    
    printf("\nQuantity of %ss to order for cut size %sx%2.1f\", quantity %d, builds %d:\n", dim[lumber_size - 1], dim[lumber_size - 1], piece_length, piece_num, builds);
    printf("\n   8-ft:  %2.0f   total scrap: %.1f\"   total cost: $%.2f   scrap/plank: %.1f\"", lum_quant_eight, total_scrap_eight, total_price_eight, scrap_eight);
    printf("\n  10-ft:  %2.0f   total scrap: %.1f\"   total cost: $%.2f   scrap/plank: %.1f\"", lum_quant_ten, total_scrap_ten, total_price_ten, scrap_ten);
    printf("\n  12-ft:  %2.0f   total scrap: %.1f\"   total cost: $%.2f   scrap/plank: %.1f\"\n", lum_quant_twelve, total_scrap_twelve, total_price_twelve, scrap_twelve);
    
    int check = 0;
    printf("\n^^Did you write this down? If yes, enter 1. \n");
    scanf("%d", &check);
    
    while (check != 1)
    {
        printf("\nWRITE IT DOWN!! And then enter 1. \n");
        scanf("%d", &check);
    }
    return 0;
}
