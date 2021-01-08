/*****************************************************************************
 * File name:   cpp2c.c
 * Developer:   Yaron Meister
 * Reviewer: 	Eran 
 * Date:        2019-02-27 16:36:20
 * Description: C source file of 'cpp to c'
 *****************************************************************************/
 
#include <stdio.h>      /*    printf    */
#include <stdlib.h>     /* EXIT_SUCCESS */

#include "utils.h"		/* 	   MAX		*/

/********************************* Macros *************************************/ 
enum call_function
{
	DTOR,
	DISPLAY,
	WASH
};

/******************************** Structs *************************************/
typedef struct public_transport
{
	void (**m_vtable)();
	int m_license_plate;
} pt_t;

typedef struct minibus
{
	pt_t m_pt;
	int m_num_seats;
} minibus_t;

typedef struct taxi
{
	pt_t m_pt;
} taxi_t;

typedef struct special_taxi
{
	taxi_t m_taxi;
} special_taxi_t;

typedef struct p_convoy
{
	pt_t m_pt;
	pt_t* m_pt1;
	pt_t* m_pt2;
	minibus_t m_minibus;
	taxi_t m_taxi; 
} p_convoy_t;

 
/************************** Forward Declarations ******************************/
/* Public Transport functions */
void PTCtor(pt_t* this);
void PTCopyCtor(pt_t* new, pt_t* old);
void PTDtor(pt_t* this);
void PTDisplay(pt_t* this);
void PrintCount();
int  GetID(pt_t* this);

/* Minibus functions */
void MiniCtor(minibus_t* this);
void MiniCopyCtor(minibus_t* new, minibus_t* old);
void MiniDtor(minibus_t* this);
void MiniDisplay(minibus_t* this);
void Wash(minibus_t* this, int minutes);

/* Taxi functions */
void TaxiCtor(taxi_t* this);
void TaxiCopyCtor(taxi_t* new, taxi_t* old);
void TaxiDtor(taxi_t* this);
void TaxiThisDisplay(taxi_t* this);

/* Special Taxi functions */
void STaxiCtor(special_taxi_t* this);
void STaxiCopyCtor(special_taxi_t* new, special_taxi_t* old);
void STaxiDtor(special_taxi_t* this);
void STaxiDisplay(special_taxi_t* this);

/* Public Convoy functions */
void PConvoyCtor(p_convoy_t* this);
void PConvoyCopyCtor(p_convoy_t* new, p_convoy_t* old);
void PConvoyDtor(p_convoy_t* this);
void PConvoyDisplay(p_convoy_t* this);

/* Print Info functions */
void PTPrintInfo(pt_t* pt);
void PrintInfo(void);
void MiniPrintInfo(minibus_t* minibus);
void IntPrintInfo(pt_t* pt, int i);

/* Non-member functions */
void TaxiDisplay(taxi_t* taxi);


/***************************** Global variables *******************************/
int g_s_count = 0;

void (*pt_vtable[])()   		 = {PTDtor, PTDisplay}; 
void (*mini_vtable[])() 		 = {MiniDtor, MiniDisplay, Wash};
void (*taxi_vtable[])() 		 = {TaxiDtor, TaxiThisDisplay};
void (*special_taxi_vtable[])()  = {STaxiDtor, STaxiDisplay}; 
void (*p_convoy_vtable[])() 	 = {PConvoyDtor, PConvoyDisplay};
								 
/*******************************************************************************
                                Main Function
*******************************************************************************/
int main(void)
{
	printf("\n*1. ========================================================*\n");
	/* Minibus m; */
	minibus_t m;
	MiniCtor(&m);

	printf("\n*2. ========================================================*\n");
	/* print_info(m); */
	MiniPrintInfo(&m);
 
 	printf("\n*3. ========================================================*\n");
 	/* print_info(3).display(); */
	pt_t pt; 
	IntPrintInfo(&pt, 3);	
 	PTDisplay(&pt);
	PTDtor(&pt);

	printf("\n*4. ========================================================*\n");
/* PublicTransport *array[] = { new Minibus(), new Taxi(), new Minibus() }; */
	pt_t* array[3];
	array[0] = (pt_t*)malloc(sizeof(minibus_t));
	MiniCtor((minibus_t*)array[0]);
	array[1] = (pt_t*)malloc(sizeof(taxi_t));
	TaxiCtor((taxi_t*)array[1]);
	array[2] = (pt_t*)malloc(sizeof(minibus_t));
	MiniCtor((minibus_t*)array[2]);

	printf("\n*5. ========================================================*\n");
	/*
	for (int i = 0; i < 3; ++i)
    {
        array[i]->display();
    }
    */
    for (int i = 0; i < 3; ++i)
	{
		(array[i])->m_vtable[DISPLAY](array[i]);
	}

	printf("\n*6. ========================================================*\n");
	/*
	for (int i = 0; i < 3; ++i) 
    {
        delete array[i];
    }
    */
    for (int i = 0; i < 3; ++i)
    {
    	(array[i])->m_vtable[DTOR](array[i]);
    	free(array[i]);
    }

    printf("\n*7. ========================================================*\n");
    /* PublicTransport arr2[] = { Minibus(), Taxi(), PublicTransport() }; */
    pt_t arr2[3];
    minibus_t mini;
    MiniCtor(&mini);
    PTCopyCtor(&arr2[0], &mini.m_pt);
    MiniDtor(&mini);

	taxi_t taxi;
    TaxiCtor(&taxi);
    PTCopyCtor(&arr2[1], &taxi.m_pt);
    TaxiDtor(&taxi);

	PTCtor(&arr2[2]);

	printf("\n*8. ========================================================*\n");
	/*
	for (int i = 0; i < 3; ++i) 
    {
        arr2[i].display();
    }
    */
    for (int i = 0; i < 3; ++i)
    {
		PTDisplay(&arr2[i]);
    }

    printf("\n*9. ========================================================*\n");
    /* print_info(arr2[0]); */
    PTPrintInfo(&arr2[0]);

    printf("\n*10. =======================================================*\n");
    /* PublicTransport::print_count(); */
    PrintCount();

    printf("\n*11. =======================================================*\n");
    /* Minibus m2; */
    minibus_t m2;
    MiniCtor(&m2);

    printf("\n*12. =======================================================*\n");
    /* m2.print_count(); */
    PrintCount();

    printf("\n*13. =======================================================*\n");
    /* Minibus arr3[4]; */
    minibus_t arr3[4];
    for (int i = 0; i < 4; ++i)
    {
    	MiniCtor(&arr3[i]);
    }

    printf("\n*14. =======================================================*\n");
	/* Taxi *arr4 = new Taxi[4]; */    
    taxi_t* arr4 = (taxi_t*)malloc(4 * sizeof(taxi_t));
    for (int i = 0; i < 4; ++i)
    {
    	TaxiCtor(&arr4[i]);
    }

	printf("\n*15. =======================================================*\n");
	/* delete[] arr4; */
	for (int i = 3; i >= 0; --i)
    {
    	TaxiDtor(&arr4[i]);
    }

    free(arr4);
    arr4 = NULL;

	printf("\n*16. =======================================================*\n");
	printf("%d\n", MAX(1, 2));
	printf("%d\n", MAX(1, (int)2.0));

	printf("\n*17. =======================================================*\n");
	/* SpecialTaxi st; */
	special_taxi_t st;
	STaxiCtor(&st);
	
	printf("\n*18. =======================================================*\n");
	/* taxi_display(st); */
	taxi_t taxi2;
	TaxiCopyCtor(&taxi2, (taxi_t*)&st);
	TaxiDisplay(&taxi2);
	TaxiDtor(&taxi2);

	printf("\n*19. =======================================================*\n");
    /* PublicConvoy *ts1 = new PublicConvoy(); */
	p_convoy_t* ts1 = (p_convoy_t *)malloc(sizeof(p_convoy_t));
	PConvoyCtor(ts1);

	printf("\n*20. =======================================================*\n");
    /* PublicConvoy *ts2 = new PublicConvoy(*ts1); */
	p_convoy_t* ts2 = (p_convoy_t*)malloc(sizeof(p_convoy_t));
	PConvoyCopyCtor(ts2, ts1);

	printf("\n*21. =======================================================*\n");
    /* ts1->display(); */
	((pt_t*)ts1)->m_vtable[DISPLAY](ts1);

	printf("\n*22. =======================================================*\n");
	/* ts2->display(); */
	((pt_t*)ts2)->m_vtable[DISPLAY](ts2);

	printf("\n*23. =======================================================*\n");
	/* delete ts1; */
	((pt_t*)ts1)->m_vtable[DTOR](ts1);
	free(ts1);

	printf("\n*24. =======================================================*\n");
	/* ts2->display(); */ 
	((pt_t*)ts2)->m_vtable[DISPLAY](ts2);

	printf("\n*25. =======================================================*\n");
	/* delete ts2; */
	((pt_t*)ts2)->m_vtable[DTOR](ts2);
	free(ts2);
	ts2 = NULL;

	printf("\n*26. =======================================================*\n");
	STaxiDtor(&st);

	for (int i = 3; i >= 0; --i)
    {
    	MiniDtor(&arr3[i]);
    }

    MiniDtor(&m2);

    for (int i = 2; i >= 0; --i)
    {
    	PTDtor(&arr2[i]);
    }

    MiniDtor(&m);

    return (EXIT_SUCCESS);
} 

/*******************************************************************************
                           Functions Implementations
*******************************************************************************/ 
/* Public Transport */ 
/******************************************************************************/ 
void PTCtor(pt_t* this)
{
	/* v-table */
	this->m_vtable = pt_vtable;	
	/* user-code */
	this->m_license_plate = ++g_s_count;
	printf("PublicTransport::Ctor()%d\n", this->m_license_plate);
}

/*************************                           **************************/
void PTCopyCtor(pt_t* new, pt_t* old)
{
	UNUSED_VAR(old);
	/* v-table */
	new->m_vtable = pt_vtable;
	/* user-code */
	new->m_license_plate = ++g_s_count;
	printf("PublicTransport::CCtor() %d\n", new->m_license_plate);
}

/*************************                           **************************/
void PTDtor(pt_t* this)
{
	--g_s_count;
	printf("PublicTransport::Dtor()%d\n", this->m_license_plate);

	this->m_vtable = NULL;
}

/*************************                           **************************/
void PTDisplay(pt_t* this)
{
	printf("PublicTransport::display(): %d\n", this->m_license_plate);
}

/*************************                           **************************/
void PrintCount()
{
	printf("s_count: %d\n", g_s_count);
}

/*************************                           **************************/
int GetID(pt_t* this)
{
	return (this->m_license_plate);
}


/* Minibus */ 
/******************************************************************************/ 
void MiniCtor(minibus_t* this)
{
	/* Base Ctor */
	PTCtor(&this->m_pt);
	/* v-table */
	this->m_pt.m_vtable = mini_vtable;
	/* user-code */													
	this->m_num_seats = 20;
	printf("Minibus::Ctor()\n");
}

/*************************                           **************************/
void MiniCopyCtor(minibus_t* new, minibus_t* old)
{
	/* Base CopyCtor */
	PTCopyCtor(&new->m_pt, &old->m_pt);
	/* v-table */
	new->m_pt.m_vtable = mini_vtable;
	/* user-code */
	new->m_num_seats = old->m_num_seats;
	printf("Minibus::CCtor()\n");
}

/*************************                           **************************/
void MiniDtor(minibus_t* this)
{
	printf("Minibus::Dtor()\n");

	PTDtor(&this->m_pt);
}

/*************************                           **************************/
void MiniDisplay(minibus_t* this)
{
	printf("Minibus::display() ID:%d", GetID(&this->m_pt));
	printf(" num seats:%d\n", this->m_num_seats);
}

/*************************                           **************************/
void Wash(minibus_t* this, int minutes)
{
	printf("Minibus::wash(%d) ID:%d\n", minutes, GetID(&this->m_pt));
}



/* Taxi */ 
/******************************************************************************/ 
void TaxiCtor(taxi_t* this)
{
	/* Base Ctor */
	PTCtor(&this->m_pt);
	/* v-table */
	this->m_pt.m_vtable = taxi_vtable;													
	/* user-code */
	printf("Taxi::Ctor()\n");
}

/*************************                           **************************/
void TaxiCopyCtor(taxi_t* new, taxi_t* old)
{
	/* Base CopyCtor */
	PTCopyCtor(&new->m_pt, &old->m_pt);
	/* v-table */
	new->m_pt.m_vtable = taxi_vtable;
	/* user-code */
	printf("Taxi::CCtor()\n");
}

/*************************                           **************************/
void TaxiDtor(taxi_t* this)
{
	printf("Taxi::Dtor()\n");

	PTDtor(&this->m_pt);
}

/*************************                           **************************/
void TaxiThisDisplay(taxi_t* this)
{
	printf("Taxi::display() ID:%d\n", GetID(&this->m_pt));
}




/* Special Taxi */ 
/******************************************************************************/ 
void STaxiCtor(special_taxi_t* this)
{
	/* Base Ctor */
	TaxiCtor(&this->m_taxi);
	/* user-code */
	printf("SpecialTaxi::Ctor()\n");
}

/*************************                           **************************/
void STaxiCopyCtor(special_taxi_t* new, special_taxi_t* old)
{}

/*************************                           **************************/
void STaxiDtor(special_taxi_t* this)
{
	printf("SpecialTaxi::Dtor()\n");

	TaxiDtor(&this->m_taxi);
}

/*************************                           **************************/
void STaxiDisplay(special_taxi_t* this)
{
	printf("SpecialTaxi::display() ID:%d\n", GetID(&this->m_taxi.m_pt));
}


/* Public Convoy */ 
/******************************************************************************/ 
void PConvoyCtor(p_convoy_t* this)
{
	/* Base Ctor */
	PTCtor(&this->m_pt);
	/* v-table */
	this->m_pt.m_vtable = p_convoy_vtable;
	/* Initialization list */
	this->m_pt1 = (pt_t*)malloc(sizeof(minibus_t));
	MiniCtor((minibus_t*)this->m_pt1);
	this->m_pt2 = (pt_t*)malloc(sizeof(taxi_t));
	TaxiCtor((taxi_t*)this->m_pt2);
	MiniCtor(&this->m_minibus);
	TaxiCtor(&this->m_taxi);
}

/*************************                           **************************/
void PConvoyCopyCtor(p_convoy_t* new, p_convoy_t* old)
{
	/* Base CopyCtor */
	PTCopyCtor(&new->m_pt, &old->m_pt);
	/* v-table */
	new->m_pt.m_vtable = p_convoy_vtable;

	/* Initialization list */
	new->m_pt1 = (pt_t*)malloc(sizeof(minibus_t));
	MiniCopyCtor((minibus_t*)new->m_pt1, (minibus_t*)old->m_pt1);

	new->m_pt2 = (pt_t*)malloc(sizeof(taxi_t));
	TaxiCopyCtor((taxi_t*)new->m_pt2, (taxi_t*)old->m_pt2);

	new->m_minibus = old->m_minibus;
	MiniCopyCtor(&new->m_minibus, &old->m_minibus);

	new->m_taxi = old->m_taxi;
	TaxiCopyCtor(&new->m_taxi, &old->m_taxi);
}

/*************************                           **************************/
void PConvoyDtor(p_convoy_t* this)
{
	MiniDtor((minibus_t*)this->m_pt1);
	free(this->m_pt1);
	TaxiDtor((taxi_t*)this->m_pt2);
	free(this->m_pt2);

	TaxiDtor(&this->m_taxi);
	MiniDtor(&this->m_minibus);

	PTDtor(&this->m_pt);
}

/*************************                           **************************/
void PConvoyDisplay(p_convoy_t* this)
{
	this->m_pt1->m_vtable[DISPLAY](this->m_pt1);	
	this->m_pt2->m_vtable[DISPLAY](this->m_pt2);
	MiniDisplay(&this->m_minibus);
	TaxiThisDisplay(&this->m_taxi);
}


/* Print Info functions */
/******************************************************************************/ 
void PTPrintInfo(pt_t* pt)
{
	pt->m_vtable[DISPLAY](pt);
}

/*************************                           **************************/
void PrintInfo(void)
{
	PrintCount();
}

/*************************                           **************************/
void MiniPrintInfo(minibus_t* minibus)
{
	((void (*)(minibus_t*, int))(((pt_t*)minibus)->m_vtable[WASH]))(minibus, 3);
}

/*************************                           **************************/
void IntPrintInfo(pt_t* pt, int i)
{
	UNUSED_VAR(i);

	minibus_t ret; 
	MiniCtor(&ret);

	printf("print_info(int i)\n");
	((pt_t*)&ret)->m_vtable[DISPLAY](&ret);	

	pt_t new;
	PTCopyCtor(&new, &ret.m_pt);
	MiniDtor(&ret);

	pt->m_vtable = new.m_vtable;	
	pt->m_license_plate = new.m_license_plate;
}

/* Non-member functions */
/******************************************************************************/ 
void TaxiDisplay(taxi_t* taxi)
{
	TaxiThisDisplay(taxi);
}





/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/ 

	
