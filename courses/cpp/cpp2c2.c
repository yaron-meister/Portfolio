/*****************************************************************************
 * File name:   cpp2c2.c
 * Developer:   Yaron Meister
 * Reviewer: 	Rachel
 * Date:        2019-03-05 12:55:23
 * Description: cpp2c #2 implementation
 *****************************************************************************/
 
#include <stdio.h>      /*    printf    */
#include <stdlib.h>     /* EXIT_SUCCESS */

#include "utils.h"		/*  UNUSED_VAR	*/

/********************************* Macros *************************************/ 
enum functions
{
	DTOR,
	DISPLAY,
	WASH
};

/******************************** Structs *************************************/
typedef struct public_transport
{
	void (**vtable)();
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

typedef struct public_convoy
{
	pt_t m_pt;
	pt_t* m_pt1;
	pt_t* m_pt2;
	minibus_t m_m;
	taxi_t m_t;
} p_convoy_t;

/************************** Forward Declarations ******************************/
/* Public-Transport functions */
void PTCtor(pt_t* this);
void PTDtor(pt_t* this);
void PTCopyCtor(pt_t* this, const pt_t* other);
void PTDisplay(pt_t* this);
void PrintCount();
int GetID(pt_t* this);

/* Minibus functions */
void MiniCtor(minibus_t* this);
void MiniCopyCtor(minibus_t* this, const minibus_t* other);
void MiniDtor(minibus_t* this);
void MiniDisplay(minibus_t* this);
void Wash(minibus_t* this, int minutes);

/* Taxi functions */
void TaxiCtor(taxi_t* this);
void TaxiCopyCtor(taxi_t* this, const taxi_t* other);
void TaxiDtor(taxi_t* this);
void TaxiThisDisplay(taxi_t* this);

/* Special-Taxi functions */
void STaxiCtor(special_taxi_t* this);
void STaxiCopyCtor(special_taxi_t* this, const special_taxi_t* other);
void STaxiDtor(special_taxi_t* this);
void STaxiDisplay(special_taxi_t* this);

/* Special-Taxi functions */
void PConvoyCtor(p_convoy_t* this);
void PConvoyDtor(p_convoy_t* this);
void PConvoyCopyCtor(p_convoy_t* this, const p_convoy_t* other);
void PConvoyDisplay(p_convoy_t* this);

/* Free functions */
int  Max(int num1, int num2);
void PTPrintInfo(pt_t* a);
void PrintInfo();
void MiniPrintInfo(minibus_t* m);
void IntPrintInfo(pt_t* ret, int i);
void TaxiDisplay(taxi_t* s);


/***************************** Global variables *******************************/
int s_count = 0;

void (*pt_vtable[])()   		 = {PTDtor, PTDisplay}; 
void (*mini_vtable[])() 		 = {MiniDtor, MiniDisplay, Wash};
void (*taxi_vtable[])() 		 = {TaxiDtor, TaxiThisDisplay};
void (*special_taxi_vtable[])()  = {STaxiDtor, STaxiDisplay}; 
void (*p_convoy_vtable[])() 	 = {PConvoyDtor, PConvoyDisplay};


/*******************************************************************************
                                Main Function
*******************************************************************************/
int main()
{
	printf("\n*1. ========================================================*\n");
 	minibus_t m;
 	MiniCtor(&m);

 	printf("\n*2. ========================================================*\n");
 	MiniPrintInfo(&m);

 	printf("\n*3. ========================================================*\n");
	pt_t return_pt; 	
 	IntPrintInfo(&return_pt, 3);
 	PTDisplay(&return_pt);
 	PTDtor(&return_pt);

 	printf("\n*4. ========================================================*\n");
 	pt_t* array[3]; 
 	array[0] = (pt_t*)malloc(sizeof(minibus_t));
 	MiniCtor((minibus_t*)array[0]);
 	array[1] = (pt_t*)malloc(sizeof(taxi_t));
 	TaxiCtor((taxi_t*)array[1]);
 	array[2] = (pt_t*)malloc(sizeof(minibus_t));
 	MiniCtor((minibus_t*)array[2]);

 	printf("\n*5. ========================================================*\n");
 	for (int i = 0; i < 3; ++i)
 	{
 		(array[i])->vtable[DISPLAY](array[i]);
 	}

 	printf("\n*6. ========================================================*\n");
	for (int i = 0; i < 3; ++i)
	{
		(array[i])->vtable[DTOR](array[i]); 	
		free(array[i]);
	}

 	printf("\n*7. ========================================================*\n");
 	pt_t arr2[3];

    minibus_t minibus;
    MiniCtor(&minibus);
    PTCopyCtor(&arr2[0], (pt_t*)&minibus);
    MiniDtor(&minibus);

	taxi_t taxi;
    TaxiCtor(&taxi);
    PTCopyCtor(&arr2[1], (pt_t*)&taxi);
    TaxiDtor(&taxi);

	PTCtor(&arr2[2]);

	printf("\n*8. ========================================================*\n");
	for (int i = 0; i < 3; ++i)
	{
		((pt_t*)&arr2[i])->vtable[DISPLAY](&arr2[i]);
	}

	printf("\n*9. ========================================================*\n");
	PTPrintInfo(&arr2[0]);

	printf("\n*10. =======================================================*\n");
	PrintCount();

	printf("\n*11. =======================================================*\n");
	minibus_t m2;
	MiniCtor(&m2);

	printf("\n*12. =======================================================*\n");
	PrintCount();

	printf("\n*13. =======================================================*\n");
	minibus_t arr3[4];
	for (int i = 0; i < 4; ++i)
	{
		MiniCtor(&arr3[i]);
	}

	printf("\n*14. =======================================================*\n");
	taxi_t* arr4 = (taxi_t*)malloc(4 * sizeof(taxi_t));
	for (int i = 0; i < 4; ++i)
	{
		TaxiCtor(&arr4[i]);
	}

	printf("\n*15. =======================================================*\n");
	for (int i = 3; i >= 0; --i)
	{
		((pt_t*)&arr4[i])->vtable[DTOR](&arr4[i]);
	}

	free(arr4);

	printf("\n*16. =======================================================*\n");
    printf("%d\n", Max(1, 2));
    printf("%d\n", Max(1, 2.0));

	printf("\n*17. =======================================================*\n");
	special_taxi_t st;
	STaxiCtor(&st);

	printf("\n*18. =======================================================*\n");
	taxi_t copy_taxi;
	TaxiCopyCtor(&copy_taxi, (taxi_t*)&st);
	TaxiDisplay(&copy_taxi);
	TaxiDtor(&copy_taxi);

	printf("\n*19. =======================================================*\n");
	p_convoy_t* ts1 = (p_convoy_t*)malloc(sizeof(p_convoy_t));
	PConvoyCtor(ts1);

	printf("\n*20. =======================================================*\n");
	p_convoy_t* ts2 = (p_convoy_t*)malloc(sizeof(p_convoy_t));
	PConvoyCopyCtor(ts2, ts1);

	printf("\n*21. =======================================================*\n");
	((pt_t*)ts1)->vtable[DISPLAY](ts1);

	printf("\n*22. =======================================================*\n");
	((pt_t*)ts2)->vtable[DISPLAY](ts2);

	printf("\n*23. =======================================================*\n");
	((pt_t*)ts1)->vtable[DTOR](ts1);
	free(ts1);

	printf("\n*24. =======================================================*\n");
	((pt_t*)ts2)->vtable[DISPLAY](ts2);

	printf("\n*25. =======================================================*\n");
	((pt_t*)ts2)->vtable[DTOR](ts2);
	free(ts2);

	printf("\n*26. =======================================================*\n");
    STaxiDtor(&st);

	for (int i = 3; i >= 0; --i)
    {
    	((pt_t*)&arr3[i])->vtable[DTOR](&arr3[i]);
    }

    MiniDtor(&m2);

    for (int i = 2; i >= 0; --i)
    {
    	(&arr2[i])->vtable[DTOR](&arr2[i]);
    }

    MiniDtor(&m);

    return (EXIT_SUCCESS);
} 

/*******************************************************************************
                           Functions Implementations
*******************************************************************************/  
/* Public-Transport functions */
/******************************************************************************/ 
void PTCtor(pt_t* this)
{
	this->vtable = pt_vtable;
	this->m_license_plate = ++s_count;
	printf("PublicTransport::Ctor()%d\n", this->m_license_plate);
}

/*******************                                      *********************/
void PTDtor(pt_t* this)
{
	--s_count;
	printf("PublicTransport::Dtor()%d\n", this->m_license_plate);
	this->vtable = 0;
}

/*******************                                      *********************/
void PTCopyCtor(pt_t* this, const pt_t* other)
{
	UNUSED_VAR(other);

	this->vtable = pt_vtable;
	this->m_license_plate = ++s_count;
	printf("PublicTransport::CCtor() %d\n", this->m_license_plate);
}

/*******************                                      *********************/
void PTDisplay(pt_t* this)
{
	printf("PublicTransport::display(): %d\n", this->m_license_plate);
}

/*******************                                      *********************/
void PrintCount()
{
	printf("s_count: %d\n", s_count);
}

/*******************                                      *********************/
int GetID(pt_t* this)
{
	return (this->m_license_plate);
}



/* Minibus functions */
/******************************************************************************/ 
void MiniCtor(minibus_t* this)
{
	PTCtor(&this->m_pt);
	this->m_pt.vtable = mini_vtable;
	this->m_num_seats = 20;
	printf("Minibus::Ctor()\n");
}

/*******************                                      *********************/
void MiniCopyCtor(minibus_t* this, const minibus_t* other)
{
	PTCopyCtor(&this->m_pt, &other->m_pt);
	this->m_pt.vtable = mini_vtable;
	this->m_num_seats = other->m_num_seats;
	printf("Minibus::CCtor()\n");
}

/*******************                                      *********************/
void MiniDtor(minibus_t* this)
{
	printf("Minibus::Dtor()\n");
	this->m_pt.vtable = pt_vtable;
	PTDtor(&this->m_pt);
}

/*******************                                      *********************/
void MiniDisplay(minibus_t* this)
{
	printf("Minibus::display() ID:%d", GetID(&this->m_pt));
	printf(" num seats:%d\n", this->m_num_seats);
}

/*******************                                      *********************/
void Wash(minibus_t* this, int minutes)
{
	printf("Minibus::wash(%d) ID:%d\n", minutes, GetID(&this->m_pt));
}



/* Taxi functions */
/******************************************************************************/ 
void TaxiCtor(taxi_t* this)
{
	PTCtor(&this->m_pt);
	this->m_pt.vtable = taxi_vtable;
	printf("Taxi::Ctor()\n");
}

/*******************                                      *********************/
void TaxiCopyCtor(taxi_t* this, const taxi_t* other)
{
	PTCopyCtor(&this->m_pt, &other->m_pt);
	this->m_pt.vtable = taxi_vtable;
	printf("Taxi::CCtor()\n");
}

/*******************                                      *********************/
void TaxiDtor(taxi_t* this)
{
	printf("Taxi::Dtor()\n");
	this->m_pt.vtable = pt_vtable;
	PTDtor(&this->m_pt);
}

/*******************                                      *********************/
void TaxiThisDisplay(taxi_t* this)
{
	printf("Taxi::display() ID:%d\n", GetID(&this->m_pt));
}



/* Special-Taxi functions */
/******************************************************************************/ 
void STaxiCtor(special_taxi_t* this)
{
	TaxiCtor(&this->m_taxi);
	this->m_taxi.m_pt.vtable = special_taxi_vtable;
	printf("SpecialTaxi::Ctor()\n");
}

/*******************                                      *********************/
void STaxiCopyCtor(special_taxi_t* this, const special_taxi_t* other)
{
	TaxiCopyCtor(&this->m_taxi, &other->m_taxi);
	this->m_taxi.m_pt.vtable = special_taxi_vtable;
	printf("SpecialTaxi::CCtor()\n");	
}

/*******************                                      *********************/
void STaxiDtor(special_taxi_t* this)
{
	printf("SpecialTaxi::Dtor()\n");
	this->m_taxi.m_pt.vtable = taxi_vtable;
	TaxiDtor(&this->m_taxi);	
}

/*******************                                      *********************/
void STaxiDisplay(special_taxi_t* this)
{
	printf("SpecialTaxi::display() ID:%d\n", GetID(&this->m_taxi.m_pt));
}



/* Public-Convoy functions */
/******************************************************************************/ 
void PConvoyCtor(p_convoy_t* this)
{
	PTCtor(&this->m_pt);
	this->m_pt.vtable = p_convoy_vtable;

	this->m_pt1 = (pt_t*)malloc(sizeof(minibus_t));
	MiniCtor((minibus_t*)this->m_pt1);

	this->m_pt2 = (pt_t*)malloc(sizeof(taxi_t));
	TaxiCtor((taxi_t*)this->m_pt2);

	MiniCtor(&this->m_m);
	TaxiCtor(&this->m_t);	
}

/*******************                                      *********************/
void PConvoyDtor(p_convoy_t* this)
{
	this->m_pt.vtable = pt_vtable;
	
	MiniDtor((minibus_t*)this->m_pt1);
	free(this->m_pt1);

	TaxiDtor((taxi_t*)this->m_pt2);
	free(this->m_pt2);

	TaxiDtor(&this->m_t);
	MiniDtor(&this->m_m);
	PTDtor(&this->m_pt);
}

/*******************                                      *********************/
void PConvoyCopyCtor(p_convoy_t* this, const p_convoy_t* other)
{
	PTCopyCtor(&this->m_pt, &other->m_pt);
	this->m_pt.vtable = p_convoy_vtable;

	this->m_pt1 = (pt_t*)malloc(sizeof(minibus_t));
	MiniCopyCtor((minibus_t*)this->m_pt1, (minibus_t*)other->m_pt1);

	this->m_pt2 = (pt_t*)malloc(sizeof(taxi_t));
	TaxiCopyCtor((taxi_t*)this->m_pt2, (taxi_t*)other->m_pt2);

	this->m_m = other->m_m;
	MiniCopyCtor(&this->m_m, &other->m_m);

	this->m_t = other->m_t;
	TaxiCopyCtor(&this->m_t, &other->m_t);
}

/*******************                                      *********************/
void PConvoyDisplay(p_convoy_t* this)
{
	(this->m_pt1)->vtable[DISPLAY](this->m_pt1);
	(this->m_pt2)->vtable[DISPLAY](this->m_pt2);
	MiniDisplay(&this->m_m);
	TaxiThisDisplay(&this->m_t);
}



/* Free functions */
/******************************************************************************/
int Max(int num1, int num2)
{
	return ((num1 >= num2) ? num1 : num2); 
}

/******************************************************************************/
void PTPrintInfo(pt_t* a)
{
	a->vtable[DISPLAY](a);
}

/******************************************************************************/
void PrintInfo()
{
	PrintCount();
}

/******************************************************************************/
void MiniPrintInfo(minibus_t* m)
{
	((void (*)(minibus_t*, int))(((pt_t*)m)->vtable[WASH]))(m, 3);
}

/******************************************************************************/
void IntPrintInfo(pt_t* return_pt, int i)
{
	UNUSED_VAR(i);

	minibus_t ret;
	MiniCtor(&ret);

	printf("print_info(int i)\n");
	MiniDisplay(&ret);

	pt_t copy;
	PTCopyCtor(&copy, (pt_t*)&ret);
	MiniDtor(&ret);

	return_pt->vtable = copy.vtable;
	return_pt->m_license_plate = copy.m_license_plate;
}

/******************************************************************************/
void TaxiDisplay(taxi_t* s)
{
	TaxiThisDisplay(s);
}

/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/ 
