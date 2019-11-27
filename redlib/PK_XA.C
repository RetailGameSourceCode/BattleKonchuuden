//
//	PS XA Driver Ver 1.0
//

#include	"pk_xa.h"

#define	MAX_ERROR	16

#define	s_char	signed char

volatile int	xa_time_work;
volatile int	xa_flame;
volatile s_char	xa_working_mode;
volatile int	xa_pno,xa_pno2;
volatile int	xa_vsync_f= 0;
volatile int	xa_error;

static u_char	nullparam[4]= {0,0,0,0};
static u_char	cdlmodespeed[4]= {CdlModeSpeed, 0,0,0};
static u_char	dparam[4]=  { CdlModeRT|CdlModeSF| CdlModeSpeed,0,0,0 };

static 	char	*secter_buffer;
static	CdlLOC	sloc, *xa_loc;
static	XA_DATA	*xa_data;

/* ============================================================ */

void	cddataread_close(void )
{
	SsSetSerialVol(SS_SERIAL_A, 0,0);
	xa_vsync_f= 0;
	CdReadyCallback(NULL);
	CdSyncCallback(NULL);
	CdControl(CdlPause, NULL,NULL);
	xa_flame= -1;
	xa_working_mode= XA_WM_READY;
	xa_error= 0;
}

/* --------------------------------------------------------------------- */

void cbdataread(u_char intr,u_char *result)
{
	if(intr == CdlDataReady) {
		if(xa_time_work <= 0) {
			cddataread_close();
			return;
		}
		CdGetSector(secter_buffer,SCTSIZE/sizeof(long));
	} else {
		++xa_error;
		if(xa_error > MAX_ERROR)
			cddataread_close();
	}
}

/* ----------- from VsyncFunction ---------- */

void XaVSyncJob(void ) {
	if(xa_vsync_f) {
		if(--xa_time_work <= 0) {
			cddataread_close();
			return;
		}
		++xa_flame;
	}
}

/* ----------------------------------------------- */

int		XaSeekS(int xa_no)
{
	if(xa_working_mode == XA_WM_PLAY)		return(0);


//	if(xa_loc[xa_tbl[xa_no].sfno.minute == 99)	return(0);


	CdIntToPos(
		CdPosToInt(&xa_loc[xa_data[xa_no].sfno])+xa_data[xa_no].offset
		,&sloc
	);

	CdControlF(CdlSeekL, (u_char *)&sloc);
	return(1);
}

/* ----------------------------------------------------------------------- */

void set_xa_mode(void ) {
	CdControlB(CdlSetmode,dparam, NULL);
	CdSync(0,NULL);
}

/* ----------------- */

void	xa_play(u_char	intr,u_char	*result);

void	xa_seek(int	xa_no)
{
	u_char	param[4];
	CdlFILE	finfo;
	short	xa_vol;

	xa_pno2= xa_no;

	SsSetSerialAttr (SS_SERIAL_A, SS_MIX, SS_SON);

	xa_vol= xa_data[xa_pno2].vol;
	SsSetSerialVol (SS_SERIAL_A, xa_vol,xa_vol);

//	if(xa_loc[xa_tbl[xa_no].sfno.minute == 99)	return;

	CdIntToPos(
		CdPosToInt(&xa_loc[xa_data[xa_no].sfno])+xa_data[xa_no].offset
		,&sloc
	);

	param[0] = 1;
	param[1] = xa_data[xa_no].ch % 16;
	CdControlB(CdlSetfilter , param, NULL);

	CdSyncCallback( xa_play );

	CdControlF(CdlSeekL, (u_char *)&sloc);
	xa_flame= 0;
	xa_working_mode= XA_WM_PLAY;
	xa_pno= -1;
}




/* ----------------------------------------------------- */

void	xa_play(u_char intr,u_char	*result)
{
	if( intr == CdlComplete ) {
		xa_time_work= xa_data[xa_pno2].time;
		CdSyncCallback( NULL );

		CdControlB(CdlSetmode,dparam, NULL);

		CdReadyCallback( cbdataread );
		CdControlB(CdlReadS,(u_char *)&sloc,NULL);
		xa_pno= xa_pno2;
		xa_vsync_f= 1;
	} else {
		printf("(T_T) can't xa_play\n");
		xa_working_mode= XA_WM_READY;
	}
}




void		XaInit(CdlLOC *xa_loc_address, XA_DATA *xa_data_address, char *buff)
{
	xa_loc= xa_loc_address;
	xa_data= xa_data_address;

	CdReadyCallback( NULL );
	CdSyncCallback( NULL );
	CdReadyCallback( NULL );

	CdControlB(CdlSetmode,cdlmodespeed,NULL);

	xa_working_mode= XA_WM_READY;
	CdDeMute();
	secter_buffer= buff;
	xa_error= 0;
	xa_vsync_f= 0;
}
