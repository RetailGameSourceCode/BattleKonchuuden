/***************************************************************************************************
	åªç›ÇÃâÊñ ÇÇsÇhÇlÉtÉ@ÉCÉãÇ…óéÇ∆Ç∑
***************************************************************************************************/
void capture( void )
{
	RECT rect;
	long fd;
	char filename[32];

	static long tim_header[] = {
		0x00000010,
		0x00000002,
		320 * 240 * 2 + 12,
		0x00000000,
		0x00f00140,
	};
	static int tim_no = 0;

	if ( !PSDIDX ) {
		setRECT(&rect, 0, 0, 320, 240);
		StoreImage(&rect, (u_long *)0x80600000);
	}
	else {
		setRECT(&rect, 0, 240, 320, 240);
		StoreImage(&rect, (u_long *)0x80600000);
	}

	DrawSync( 0 );

	sprintf(filename, "sim:timdata\\scn%04d.tim", tim_no);
	if ( (fd = open(filename, O_WRONLY|O_CREAT)) == -1 ) {
		printf("can't open file\n");
	}
	else {
		write(fd, (void *)tim_header, sizeof( tim_header));
		write(fd, (void *)0x80600000, 320 * 240 * 2);
		close( fd );
		tim_no++;
		printf("captured %s\n", filename);
	}
}
