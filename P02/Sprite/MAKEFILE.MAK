menu.tex:
	timpos fixmenu.tim  384   0   0 480
	timpos fixmenu2.tim 320  40  16 480
	timpos fixb2b.tim   320   0   0 490
	timpos fix2.tim     356  40  32 480
	timpos fix.tim      448   0 256 480
	timpos menuheya.tim 320 256   0   0
	cmplz fixmenu.tim  fixmenu.lz
	cmplz fixmenu2.tim fixmenu2.lz
	cmplz fixb2b.tim   fixb2b.lz
	cmplz fix2.tim     fix2.lz
	cmplz fix.tim      fix.lz
	cmplz menuheya.tim menuheya.lz
	hdlink /n /l menu.lis
	copy menu.tex d:\98025\dt
	del *.lz

fixmenu.c: fixmenu.anm
	anm2c -u 384   0 -s fm fixmenu.anm

fixmenu2.c: fixmenu2.anm
	anm2c -u 320  40 -s fm2 fixmenu2.anm

fix.c: fix.anm
	anm2c -u   0   0 -s mfix fix.anm

