/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  System Name   : ALL SYSTEM                                               */
/*  Machine & OS  : Sony PlayStation / PlayStation OS ( R3000 )              */
/*  Language      : GNU C                                                    */
/*                                                                           */
/*  File Contents : UTILITY LIBRARY                                          */
/*  File Attribute: SOURCE                                                   */
/*  File Name     : LIBUTL.C                                                 */
/*                                                                           */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/

/*----- Language Header Files -----*/
#include <stddef.h>
#include <libgte.h>

/*----- User Header     Files -----*/
/* Non */

/*----- User External   Files -----*/
/* Non */

/*----- User Table      Files -----*/
#include "libutl.tbl"

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  CHARCTER STRING TO BINARY ( WORD TYPE )                                  */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
void UtlChar2Bin( u_short len, u_char *fr_dt, u_short *to_dt )
{
   u_short         i, j;

   *to_dt = 0;

   for ( i= ( 5 - len ), j = 0; i < 5; i++ )
     {
       ( *to_dt ) += ( ( fr_dt[ j ] & 0x0f ) * ( tbl[ i ] ) );
       j++;
     }

}

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  BINARY TO CHARCTER STRING ( WORD TYPE )                                  */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
void UtlBin2Char( u_short len, u_short dt_wd, u_char *to_dt )
{
   u_short         i, j, wk_len;

   wk_len = 5 - len;

   for ( i = 0; i < len; i++ )
     {
       to_dt[ i ] = '0';
     }

   for ( i = 0, j = 0; i < 5; i++ )
     {
       if ( dt_wd == 0 ) break;

       if ( i >= wk_len )
         {
           to_dt[ j ] = ascii[ ( dt_wd / tbl[ i ] ) ];
           j++;
         }

       dt_wd = dt_wd % tbl[ i ];
     }

}

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  HEX TYPE CHARCTER STRING TO BINARY ( WORD TYPE )                         */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
void UtlHexChar2Bin( u_short len, u_char *fr_dt, u_short *to_dt )
{
   u_short         i, j;

   *to_dt = 0;

   for ( i = 0 ; i < len; i++ )
     {
       for ( j = 0; j<16; j++ )
         {
           if ( ( fr_dt[ i ] == hex_tbl [ j ] ) ||
                ( fr_dt[ i ] == hex_tbl2[ j ] ) )
             {
               *to_dt = ( *to_dt * 16 ) + j; 
               break;
             }
         }
     }
}

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  HEX TYPE BINARY TO CHARCTER STRING ( WORD TYPE )                         */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
void UtlHexBin2Char( u_short len, u_short fr_dt, u_char *to_dt )
{
   u_short         i, j;

   for ( i = 0; i < len; i++ )
     {
       j     = fr_dt % 16;
       fr_dt = fr_dt / 16;

       to_dt[ len - 1 - i ] = hex_tbl[ j ];
     }
}

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  CHARCTER STRING TO BINARY ( DWORD TYPE )                                 */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
void UtlChar2Fig( u_short len, u_char *fr_dt, u_long *to_dt )
{
   u_short         i, j;

   *to_dt = 0l;

   for ( i = ( 10 - len ), j = 0; i < 10; i++, j++ )
     {
       ( *to_dt ) += ( ( ( u_long )fr_dt[j] & 0x0000000f ) * ( tbl_1[i] ) );
     }
}

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  HEX TYPE CHARCTER STRING TO BINARY ( DWORD TYPE )                        */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
void UtlHexChar2Fig( u_short len, u_char *fr_dt, u_long *to_dt )
{
   u_short         i, j;

   *to_dt = 0l;

   for ( i = ( 8 - len ); i < 8; i++ )
     {
       for ( j = 0 ; j < 16; j++ )
         {
           if (( fr_dt[ i ] == hex_tbl [ j ] ) ||
               ( fr_dt[ i ] == hex_tbl2[ j ] ))
             {
               *to_dt = ( *to_dt * 16l ) + ( u_long )j; 
               break;
             }
         }
     }
}

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  BINARY TO CHARCTER STRING ( DWORD TYPE )                                 */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
void UtlFig2Char( u_short len, u_long fr_dt, u_char *to_dt )
{
   u_short         i, j, wk_len;

   for ( i = 0; i < len; i++ )
     {
       to_dt[ i ] = '0';
     }

   wk_len = 10 - len;

   for ( i = 0, j = 0; i < 10; i++ )
     {
       if ( fr_dt == 0 ) break;

       if ( i >= wk_len )
         {
           to_dt[ j ] = ascii[ ( ( u_long )fr_dt / tbl_1[ i ] ) ];
           j++;
         }

       fr_dt = fr_dt % tbl_1[ i ];
     }
}

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  PACK TO UNPACK                                                           */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
void UtlPack2Unpack( u_short len, u_char *fr_dt, u_char *to_dt )
{
   u_short         i, j;

   j = 0;

   for ( i = 0, j = 0; i < len ; i++, j+=2 )
     {
       to_dt[  j  ] = ((fr_dt[i] >> 4   ) | 0x30);
       to_dt[ j+1 ] = ((fr_dt[i] &  0x0f) | 0x30);
     }
}

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  UNPACK TO PACK                                                           */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
void UtlUnpack2Pack( u_short len, u_char *fr_dt, u_char *to_dt )
{
   u_short         wk_len, i, j, k, max_len;

   wk_len = len / ( u_short )2;

   if (( len % ( u_short )2 ) != 0 )
     {
         to_dt[ 0 ] = ( fr_dt[ 0 ] & 0x0f );
         j = 1;
     }
   else  j = 0;

   if ( wk_len != 0 )
     {
       k = j;
       max_len = wk_len + j;
       for ( i = j; i < max_len; i++ )
         {
           to_dt[ i ] = (( fr_dt[ k ] << 4 ) | ( fr_dt[ k+1 ] & 0x0f ));
           k +=2;
         }
     }
}

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  SORT                                                                     */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
void UtlSort( u_char act, u_short len, u_char *dt )
{
   u_char          wk;
   u_short         i, k;

   for ( i = 0; i < len ; i++ )
     {
       for ( k = ( i+1 ); k < len ; k++ )
          {
            if ( act == '+' )
              {
                if ( dt[i] <= dt[k] ) continue;
              }
            else
              {
                if ( dt[i] >= dt[k] ) continue;
              }

            wk    = dt[i];
            dt[i] = dt[k];
            dt[k] = wk;
          }
     }
}

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  STRING COMPARE                                                           */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
u_char UtlComp( u_char *cmp1, u_char *cmp2, u_short cnt )
{
   u_short         i;

   for ( i = 0; i < cnt; i++ )
     {
       if ( cmp1[ i ] > cmp2[ i ] ) return ( 2 );     /* A > B (2)         */
       if ( cmp1[ i ] < cmp2[ i ] ) return ( 1 );     /* A < B (1)         */
     }

  return ( 0 );
}

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  FIND STRING                                                              */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
int UtlFindStr( char *str1, char *str2 )
{
   int             i;
   char            *s1, *s2;

   for ( i = 0; str1[ i ]; i++ )
     {
       if ( str1[ i ] == *str2 )
         {
           for ( s1 = &str1[ i + 1 ], s2 = str2 + 1; *s2; s1++, s2++ )
             {
               if( *s1 != *s2 )  goto non_eq;
             }

           return( i + 1 );                           /* Found               */
         }

/*----------------*/
non_eq:
     }

   return( 0 );                                       /* Not Found           */
}

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  COSIGN SCROLL                                                            */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
short UtlCosScroll( short a, short b, short total_time, short timer )
{
   short           dist, cent;
   long            l;

   if ( total_time == 0 )  return( a );

   dist = abs( a - b );
   cent = ( a + b ) >> 1;

   if ( a < b )  timer = total_time - timer;

   /* PlayStation Pai [ ONE / 2 ] */
   l = rcos( ( timer * ( ONE / 2 ) ) / total_time ) * ( dist / 2 ) ;
   l >>= 12;

   return( ( short ) l + cent );
}

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  SIGN SCROLL                                                              */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
short UtlSinScroll( short a, short b, short total_time, short timer )
{
   short           dist, cent;
   long            l;

   if ( total_time == 0 )  return( a );

   dist = abs( a - b );
   cent = ( a + b ) >> 1;

   if ( a < b )  timer = total_time - timer;

   /* PlayStation Pai [ ONE / 2 ] */
   l = rsin( ( timer * ( ONE / 2 ) ) / total_time ) * ( dist / 2 ) ;
   l >>= 12;

   return( ( short ) l + cent );
}
