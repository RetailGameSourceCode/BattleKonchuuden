/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  System Name   : ALL SYSTEM                                               */
/*  Machine & OS  : Sony PlayStation / PlayStation OS ( R3000 )              */
/*  Language      : GNU C                                                    */
/*                                                                           */
/*  File Contents : FILE I/O LIBRARY                                         */
/*  File Attribute: SOURCE                                                   */
/*  File Name     : LIBFIO.C                                                 */
/*                                                                           */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/

/*----- Language Header Files -----*/
#include <sys/types.h>
#include <sys/file.h>
#include <libapi.h>
#include <libsn.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>
#include <libcd.h>
#include <libds.h>
#include <stdio.h>
#include <strings.h>

/*----- User Header     Files -----*/
#include "libfio.h"
#include "../libutl/libutl.h"

/*----- User External   Files -----*/
/* Non */

/*----- User Table      Files -----*/
#include "libfio.tbl"

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
FIO                     fio;

#define DS 1

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  GET MACHINE                                                              */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
int FioGetMachine()
{
   long            fd;

   if ( fio.dbg_flg == FIO_MC_CHK )
     {
       fd = open( fio.name, O_RDONLY );
       if ( fd < 0 )
         {
           fio.dbg_flg = FIO_MC_PS;
           printf( "Drive Mode: CD-ROM\n" );
         }
       else
         {
           fio.dbg_flg = FIO_MC_DEV;
           printf( "Drive Mode: Hard Disc\n" );
         }

       close( fd );
     }

   return( fio.dbg_flg );
}

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  READ STATUS                                                              */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
int FioReadStatus( int mode )
{
   int             rtn;

   if ( fio.cd_flg )
     {
       rtn = CdReadSync( mode, NULL );
       if ( rtn == 0 )
         {
           fio.cd_flg= FIO_CD_READY;
         }

       return( rtn );
     }
   else
     {
       return( FIO_CD_READY );
     }
}

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  NEXT DATA                                                                */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
static char *FioNextData( char *name, char *p )
{
   p = p + 8;

   while( *p >= ' ' )
     {
       *name = *p;
       ++name;
       ++p;
     }

   *name = '\0';

   return( p );
}

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  SEARCH DATA                                                              */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
static CdlFILE FioSearchData( char *filename, int lv, char **sp )
{
   char            *p, *pn, name[ 16 ];
   CdlFILE         file;

   pn = *sp;

/*----------------*/
loop:
   p = pn;
   if ( *p == 0 )
     {
       file.pos.track  = 0;
       file.pos.minute = 0xff;
       file.pos.second = 0xff;
       file.pos.sector = 0xff;
       file.size       = 0;
       return( file );
     }

   pn = FioNextData( name, p );
   if( *p != lv )  goto loop;

   if ( strcmp( filename, name ) != 0 )  goto loop;

   ++p;

   file.pos.track   = 1;
   file.pos.sector  = *p++;
   file.pos.second  = *p++;
   file.pos.minute  = *p++;
   file.size        = *p++;
   file.size       += (*p++) * 256;
   file.size       += (*p++) * 256 * 256;
   file.size       += (*p++) * 256 * 256 * 256;

   strcpy( file.name, name );

   *sp= pn;

   return( file );
}

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  CD SEARCH FILE                                                           */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
int FioCdSearchFile( CdlFILE *finfo, char *filename )
{
   int             dl, i;
   char            *sp, *filename_p;
   char            ff[ 16 ][ 16 ];

   dl         = 0;
   filename_p = filename;

   while ( *filename_p >= ' ' && *filename_p != ';' )
     {
       if ( *filename_p == '\\' )
         {
           i = 0;
           while ( 1 )
             {
               ++filename_p;

               if ( *filename_p == '\\' ||
                    *filename_p <   ' ' ||
                    *filename_p == ';' )
                 {
                   ff[ dl ][ i ] = '\0';

                   if ( ff[ dl ][ i - 1 ] == '.' )  ff[ dl ][ i - 1 ] = '\0';

                   break;
                 }

               ff[ dl ][ i++ ] = *filename_p;
             }
         }
       ++dl;
     }

   sp = fio.toc_buff;

   for ( i = 0; i < dl; i++ )
     {
       *finfo= FioSearchData( ff[ i ], i + 1, &sp );

       if ( finfo->pos.track == 0 )
         {
           printf( "TOC Can't Find %s\n", filename );
           return( 0 );
         }
     }

   CdIntToPos( CdPosToInt( &(finfo->pos) ) + 150, &(finfo->pos) );

   return( 1 );
}

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  READ CD                                                                  */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
int FioReadCD( char *filename, u_char *addr )
{
   char            tempfile[ 256 ], addname[ 256 ];
   CdlFILE         finfo;
   int             ns;

   if ( UtlComp( filename, "cdrom:", 6 ) == 0 )
     {
       strcpy( addname, filename );
     }
   else
     {
       strcpy( addname, "cdrom:" );
       strcat( addname, &filename[ UtlFindStr( filename, ":" ) ] );
       strcat( addname, ";1" );
     }

   tempfile[ 0 ] = '\\';
   strcpy( &tempfile[ 1 ], addname + UtlFindStr( addname, ":" ) );
   if ( UtlFindStr( tempfile,";" ) == 0 )  strcat( tempfile,";1" );

   if ( CdControlB( CdlSetmode, cdlmodespeed, NULL ) == 0 )
     {
       printf( "Can't CD Setmode %s\n", tempfile );
       return( -1 );
     }

   if ( FioCdSearchFile( &finfo, tempfile ) == 0 )
     {
       printf( "FioCdSearchFile Not Find %s\n", tempfile );
       return( -1 );
     }

   ns = ( finfo.size + SECT_SIZE - 1 ) / SECT_SIZE;
   if ( CdControl( CdlSeekL, (u_char *)&( finfo.pos ), NULL ) == 0 )
     {
       printf( "CdControl Error %s\n", tempfile );
       return( -1 );
     }

   if ( CdRead( ns, (u_long *)addr, CdlModeSpeed ) == 0 )
     {
       printf( "CdRead Request Error %s\n",tempfile );
       return( -1 );
     }

   fio.cd_flg = FIO_CD_ACTIVE;

   return( finfo.size );
}

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  SYNCRO READ CD                                                           */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
int FioSyncReadCD( char *filename, u_char *addr )
{
   char            tempfile[ 256 ];
   CdlFILE         finfo;
   int             ns, re_try;

   re_try        = 0;
   tempfile[ 0 ] = '\\';
   strcpy( &tempfile[ 1 ], (char *)filename );
   strcat( tempfile,";1" );

/*----------------*/
re_load:
   ++re_try;

   if ( re_try > 10 )
     {
       printf("Date Read Error %s\n",filename );
       return( -1 );
     }

   if ( CdControlB( CdlSetmode, cdlmodespeed, NULL ) == 0 )  goto re_load;

   VSync(3);

   if ( CdSearchFile( &finfo, tempfile ) == 0 )  goto re_load;

   printf( "%s %02x:%02x:%02x\n",
           tempfile,
           finfo.pos.minute,
           finfo.pos.second,
           finfo.pos.sector );

   ns = ( finfo.size + SECT_SIZE - 1 ) / SECT_SIZE;

   if ( CdControl( CdlSetloc, (u_char *)&(finfo.pos), 0 ) == 0 ) goto re_load;

   if ( CdRead( ns, (u_long *)addr, CdlModeSpeed ) == 0 )  goto re_load;

   if ( CdReadSync( 0, 0 ) != 0 )  goto re_load;

   return( finfo.size );
}

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  DIVIDE READ CD                                                           */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
int FioDivReadCD( char *filename, u_char *addr, int ss, int ns )
{
   char            tempfile[ 256 ], addname[ 256 ];
   CdlFILE         finfo;
   int             ws;

   if ( ns == 0 )  return( 0 );

   if ( UtlComp( filename, "cdrom:", 6 ) == 0 )
     {
       strcpy( addname, filename );
     }
   else
     {
       strcpy( addname, "cdrom:" );
       strcat( addname, &filename[ UtlFindStr( filename, ":" ) ] );
       strcat( addname, ";1" );
     }

   tempfile[ 0 ] = '\\';
   strcpy( &tempfile[ 1 ], addname + UtlFindStr( addname, ":" ) );
   if ( UtlFindStr( tempfile,";" ) == 0 )  strcat( tempfile,";1" );

   if ( CdControlB( CdlSetmode, cdlmodespeed, NULL ) == 0 )
     {
       printf( "Can't CD Setmode %s\n", tempfile );
       return( -1 );
     }

   if ( FioCdSearchFile( &finfo, tempfile ) == 0 )
     {
       printf( "FioCdSearchFile Not Find %s\n", tempfile );
       return( -1 );
     }

   ws = CdPosToInt( &finfo.pos ) + ss;
   CdIntToPos( ws, &finfo.pos );

   if ( CdControl( CdlSeekL, (u_char *)&( finfo.pos ), NULL ) == 0 )
     {
       printf( "CdControl Error %s\n", tempfile );
       return( -1 );
     }

   if ( CdRead( ns, (u_long *)addr, CdlModeSpeed ) == 0 )
     {
       printf( "CdRead Request Error %s\n",tempfile );
       return( -1 );
     }

   fio.cd_flg = FIO_CD_ACTIVE;

   return( finfo.size );
}

int FioDivReadCD2( char *filename, u_char *addr, int ss, int ns )
{
   char            tempfile[ 256 ], addname[ 256 ];
   CdlFILE         finfo;
   int             ws;

   if ( ns == 0 )  return( 0 );

   if ( UtlComp( filename, "cdrom:", 6 ) == 0 )
     {
       strcpy( addname, filename );
     }
   else
     {
       strcpy( addname, "cdrom:" );
       strcat( addname, &filename[ UtlFindStr( filename, ":" ) ] );
       strcat( addname, ";1" );
     }

   tempfile[ 0 ] = '\\';
   strcpy( &tempfile[ 1 ], addname + UtlFindStr( addname, ":" ) );
   if ( UtlFindStr( tempfile,";" ) == 0 )  strcat( tempfile,";1" );

#if DS
#else
   if ( CdControlB( CdlSetmode, cdlmodespeed, NULL ) == 0 )
     {
       printf( "Can't CD Setmode %s\n", tempfile );
       return( -1 );
     }
#endif

   if ( FioCdSearchFile( &finfo, tempfile ) == 0 )
     {
       printf( "FioCdSearchFile Not Find %s\n", tempfile );
       return( -1 );
     }

   ws = CdPosToInt( &finfo.pos ) + ss;
   CdIntToPos( ws, &finfo.pos );

   if ( CdControl( CdlSeekL, (u_char *)&( finfo.pos ), NULL ) == 0 )
     {
       printf( "CdControl Error %s\n", tempfile );
       return( -1 );
     }

   if ( CdRead( ns, (u_long *)addr, CdlModeSpeed ) == 0 )
     {
       printf( "CdRead Request Error %s\n",tempfile );
       return( -1 );
     }

   fio.cd_flg = FIO_CD_ACTIVE;

   return( finfo.size );
}

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  READ PC                                                                  */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
int FioReadPC( char *filename, u_char *addr )
{
   long            fd, readsize, cursize;
   char            tempname[ 256 ];

   if ( UtlComp( filename, "sim:", 4 ) == 0 )
     {
       strcpy( tempname, filename );
     }
   else
     {
       strcpy( tempname, "sim:" );
       strcat( tempname, &filename[ UtlFindStr( filename, ":" ) ] );
     }

   /* File Open */
   fd = open( tempname, O_RDONLY );
   if ( fd == -1 )
     {
       printf( "Failure, Open %s\n", tempname );
       return( -1 );
     }

   cursize = 0;

   while( 1 )
     {
       /* File Read */
       readsize = read( fd, SIM_BUF_ADDR, SIM_BUF_SIZE );

       cursize += readsize;
       if ( readsize == -1 )
         {
           printf( "Failure, Read %s\n", tempname );
           return( -1 );
         }

       bcopy( SIM_BUF_ADDR, addr, readsize );
       if ( readsize < SIM_BUF_SIZE )  break;

       addr = addr + SIM_BUF_SIZE;
     }

   /* File Close */
   close( fd );

   return( cursize );
}

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  DIVIDE READ PC                                                           */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
int FioDivReadPC( char *filename, u_char *addr, int ss, int ns )
{
   long            fd, readsize, cursize;
   char            tempname[ 256 ];
   int             ps, i;
   u_char          *buf_addr;

   if ( ns == 0 )  return( 0 );

   if ( UtlComp( filename, "sim:", 4 ) == 0 )
     {
       strcpy( tempname, filename );
     }
   else
     {
       strcpy( tempname, "sim:" );
       strcat( tempname, &filename[ UtlFindStr( filename, ":" ) ] );
     }

   /* File Open */
   fd = open( tempname, O_RDONLY );
   if ( fd == -1 )
     {
       printf( "Failure, Open %s\n", tempname );
       return( -1 );
     }

   cursize = 0;
   ps      = 0;

   lseek( fd, ss * SECT_SIZE, SEEK_SET );

   while( 1 )
     {
       /* File Read */
       readsize = read( fd, SIM_BUF_ADDR, SIM_BUF_SIZE );

       cursize += readsize;
       if ( readsize == -1 )
         {
           printf( "Failure, Read %s\n", tempname );
           return( -1 );
         }

       buf_addr = SIM_BUF_ADDR;

       for ( i = 0; i < SIM_BUF_SIZE; i+= SECT_SIZE )
         {
           bcopy( buf_addr, addr, SECT_SIZE );
           buf_addr += SECT_SIZE;
           addr     += SECT_SIZE;
           ++ps;

           if ( ps == ns )
             {
               /* File Close */
               close( fd );
               return( ps * SECT_SIZE );
             }
         }
     }
}

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  INITIALIZE CD                                                            */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
void FioInitCD( char *filename, u_char *toc_buf )
{
   fio.toc_buff = toc_buf;

   FioSyncReadCD( filename, fio.toc_buff );
}

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  INITIALIZE MACHINE                                                       */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
void FioInitMachine( char *filename, int flag )
{
   fio.dbg_flg = flag;

   if ( UtlComp( filename, "sim:", 4 ) == 0 )
     {
       strcpy( fio.name, filename );
     }
   else
     {
       strcpy( fio.name, "sim:" );
       strcat( fio.name, &filename[ UtlFindStr( filename, ":" ) ] );
     }

   FioGetMachine();
}

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  INITIALIZE BOOT DISC                                                     */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
void FioInitBootDisc( char *filename, u_char *buff )
{
#if 0
   if ( fio.dbg_flg == FIO_MC_PS )  FioSyncReadCD( filename, buff );
   else                             FioReadPC( filename, buff );
#endif

   FioSyncReadCD( filename, buff );

   /* Disc No. */
   UtlChar2Bin( 1, &buff[ UtlFindStr( buff, "=" ) ], (u_short *)&fio.disc );
   printf( "Disc No.%d\n", fio.disc );
}

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  READ FILE                                                                */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
int FioReadFile( char *filename, u_char *addr )
{
   int             rtn;

/*-----------*/
re_try:

   if ( fio.dbg_flg == FIO_MC_PS )  rtn = FioReadCD( filename, addr );
   else                             rtn = FioReadPC( filename, addr );

   if ( rtn < 0 )  goto re_try;

   if ( FioReadStatus( 0 ) != FIO_CD_READY )  goto re_try;

   return( rtn );
}

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  DIVIDE READ FILE                                                         */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
int FioDivReadFile( char *filename, u_char *addr, int ss, int ns )
{
   int             rtn;

/*-----------*/
re_try:

   if ( fio.dbg_flg == FIO_MC_PS )
     rtn = FioDivReadCD( filename, addr, ss, ns );
   else
     rtn = FioDivReadPC( filename, addr, ss, ns );

   if ( rtn < 0 )  goto re_try;

   if ( FioReadStatus( 0 ) != FIO_CD_READY )  goto re_try;

   return( rtn );
}

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  READ FILE [ NON BLOCK ]                                                  */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
int FioReadFile2( char *filename, u_char *addr )
{
   int             rtn;

   if ( fio.dbg_flg == FIO_MC_PS )  rtn = FioReadCD( filename, addr );
   else                             rtn = FioReadPC( filename, addr );

   return( rtn );
}

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  DIVIDE READ FILE [ NON BLOCK ]                                           */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
int FioDivReadFile2( char *filename, u_char *addr, int ss, int ns )
{
   int             rtn;

   if ( fio.dbg_flg == FIO_MC_PS )
     rtn = FioDivReadCD2( filename, addr, ss, ns );
   else
     rtn = FioDivReadPC( filename, addr, ss, ns );

   return( rtn );
}

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  WRITE PC                                                                 */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
int FioWritePC( char *filename, int len, u_char *addr )
{
   int             fd, rtn_len, code;

   /* File Initialize */
   fd = PCinit();
   if ( fd == -1 )  return( -1 );

   /* File Open */
   fd = PCopen( &filename[0], 0, O_RDWR );
   if ( fd == -1 )
     {
        fd = PCcreat( &filename[0], O_CREAT | O_RDWR );
        if ( fd == -1 )  return( -1 );
     }

   /* Write Data */
   rtn_len = PCwrite( fd, addr, (int)len );
   if ( rtn_len == 0 )  return( -1 );

   /* File Close */
   code    = PCclose( fd );

   return( rtn_len );
}
